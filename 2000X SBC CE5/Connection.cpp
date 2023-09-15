/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/Connection.cpp_v   1.5   Oct 14 2005 16:22:22   bwadia  $ */
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
  1.2		07/25/05	BWadia	Added Initial Version
  1.3		10/14/05	BWadia	Modify CharReceived function for DataLogger utility.
*/

// Connection.cpp: implementation of the CConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "Connection.h"
#include "HostCommand.h"

#define DLE	0x10

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CConnection::CConnection(SOCKET fd) : CClientSocket(fd)
{
	SetBufferSizes();
	request = 0;
	state = STATE_NORMAL;
}

CConnection::~CConnection()
{
	Close();
}

void CConnection::ProcessInput()
{
	if (!ProcessInputEx())
		CloseConnection();
}

//	EOF - return false;
//	data - return true;
bool CConnection::ProcessInputEx()
{
	for (;;)
		{
		char ch;
		int ret = recv(fd, &ch, sizeof(ch), 0);
		if (ret == 0)		// EOF, connection closed
			break;
		if (ret < 0)		// error of some kind
			{
			int error = WSAGetLastError();
			if ((error == WSAEWOULDBLOCK) || (error == WSAEINTR))
				return true;	// ok with these errors
			// here we don't know what happened, so let's just report the error
			CString s;
			s.Format(_T("TCPSocket::read: error %d - disconnecting..."), error);
			app->Trace(s);
			break;
			}
		CharReceived(ch);
		}
	return false;
}

void CConnection::CloseConnection()
{
	Close();
}

void CConnection::CharReceived(char ch)
{
	CString s;
	s.Format(_T("Received '%c'"), ch);
	app->Trace(s);
	if (!request)
		request = new CHostCommand(true);
	if (request->CharRec(ch))	// got full packet?
	{
		CHostCommand * response = app->SendEnHostCommand(request);
		request = 0;	// this request was deleted, allocate new next time
		
		// no more request, clear the pointer for next pass
		request = 0;
		if (response)
		{
			app->Trace("Sending response back to ethernet");
			char ch = response->AckNak();
			int length =response->GetBufLength();
			if(ch != DLE) //Which will come in case of StartWeldData command.
				send(fd, &ch, 1, 0);
			
		
			char * buf = (char *) response->GetBuffer();
			send(fd, buf, length, 0);
			delete response;
		}
	}
}
