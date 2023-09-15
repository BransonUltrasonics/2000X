/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/EtherPort.cpp_v   1.2   Jul 25 2005 09:23:14   bwadia  $ */
/******************************************************************************/ 
/*                                                                            */
/*                                                                            */
/*      Copyright (c) Branson Ultrasonics Corporation, 2005                   */
/*     This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior       */
/*   written consent of Branson Ultrasonics Corporation.                      */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/******************************************************************************/ 
/*
Revision #    Date      Author    Description
----------  --------  ----------  -------------------------------------
  1.1       05/19/05  Aare        Added complete revision header.
   1.2		07/25/05	BWadia		Added Initial Version
*/

// EtherPort.cpp: implementation of the CEtherPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "EtherPort.h"
#include "ServerSocket.h"
#include "Connection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEtherPort * CEtherPort::thisPtr;

CEtherPort::CEtherPort()
{
	thisPtr = this;
	server = new CServerSocket(4000);
	AfxBeginThread(Thread, 0);
}

CEtherPort::~CEtherPort()
{
	delete server;
	
}

UINT CEtherPort::Thread(LPVOID)
{
	thisPtr->Thread();
	return 0;
}

void CEtherPort::Thread()
{
	app->Trace("Ethernet: Opening serial server connection.");
	stop = false;
	while (!stop)
		{
		SleepIfNoClients();
		PrepareFDSets();
		if (!PollNonblock())
			{
			app->Trace("Ethernet: Select poll nonblock.");
			return;
			}
		AcceptNewConnections();
		ProcessExceptions();
		ProcessInput();
		Sleep(100);
		}
	app->Trace("Ethernet: Closing server connection.");
}

void CEtherPort::SleepIfNoClients()
{
	if (clients.GetSize() == 0)
		{
		app->Trace("Ethernet: No connections. Going to sleep.");
		FD_ZERO(&input_set);
		server->FdSet(input_set);
		if (server->Select(input_set) < 0)
			app->Trace("Ethernet: Sleep: Select error");
		else
			app->Trace("Ethernet: New connection. Waking up.");
		}
}

void CEtherPort::PrepareFDSets()
{
	FD_ZERO(&input_set);
	FD_ZERO(&output_set);
	FD_ZERO(&exc_set);

	server->FdSet(input_set);

	for (int i = 0; i < clients.GetSize(); i++)
		{
		CConnection * connection = clients[i];
		connection->FdSet(input_set);
		connection->FdSet(output_set);
		connection->FdSet(exc_set);
		}
}

bool CEtherPort::PollNonblock()
{
	struct timeval null_time = { 0, 0 };
	if (select(0, &input_set, &output_set, &exc_set, &null_time) < 0)
		return false;
	return true;
}

void CEtherPort::AcceptNewConnections()
{
	if (server->IsSet(input_set))
		NewConnection();
}

void CEtherPort::NewConnection()
{
	struct sockaddr_in peer;
	CConnection * newClient = server->Accept(peer);
	if (!newClient)
		{
		app->Trace("Ethernet: Accept error.");
		return;
		}
	clients.Add(newClient);
	app->Trace("Ethernet: Got new connection.");
}

void CEtherPort::ProcessExceptions()
{
	for (int i = 0; i < clients.GetSize(); i++)
		{
		CConnection * client = clients[i];
		if (client->IsSet(exc_set))
			{
			client->FdClr(input_set);
			client->FdClr(output_set);
			client->CloseConnection();
			}
		}
	CleanupConnections();
}

void CEtherPort::ProcessInput()
{
	for (int i = 0; i < clients.GetSize(); i++)
		{
		CConnection * client = clients[i];
		if (client->IsSet(input_set))
			client->ProcessInput();
		}
	CleanupConnections();
}

void CEtherPort::CleanupConnections()
{
	for (int i = clients.GetUpperBound(); i >= 0; i--)
		{
		CConnection * client = clients[i];
		if (client->IsClosed())
			{
			delete client;
			clients.RemoveAt(i);
			}
		}
}

void CEtherPort::Stop()
{
	stop = true;
}
