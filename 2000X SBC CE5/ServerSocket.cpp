/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/ServerSocket.cpp_v   1.2   Jul 25 2005 09:55:10   bwadia  $ */
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
*/

// ServerSocket.cpp: implementation of the CServerSocket class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Application.h"
#include "ServerSocket.h"
#include "Connection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CServerSocket::CServerSocket(int port)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == INVALID_SOCKET)
		{
		app->Trace("Ethernet: CServerSocket::ctor: socket");
		exit(1);
		}
	ReuseAddress();
	Linger();
	Bind(port);
	NonBlock();
	Listen();

	sockaddr_in addr;
	int len = sizeof(addr);
	if (getsockname(fd, (sockaddr *) &addr, &len) == SOCKET_ERROR)
		app->Trace("getsockname error");
	CString s;
	s.Format(_T("%d.%d.%d.%d:%d"), addr.sin_addr.S_un.S_un_b.s_b1, addr.sin_addr.S_un.S_un_b.s_b2, addr.sin_addr.S_un.S_un_b.s_b3, addr.sin_addr.S_un.S_un_b.s_b4, addr.sin_port);
	app->Trace(s);
}

CServerSocket::~CServerSocket()
{
}

void CServerSocket::Bind(int port)
{
	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	if (bind(fd, (const struct sockaddr *) &sa, sizeof(sa)) == SOCKET_ERROR)
		{
		app->Trace("Ethernet: CServerSocket::Bind");
		exit(1);
		}
}

void CServerSocket::ReuseAddress()
{
	BOOL opt = TRUE;
	if (!SetSockOpt(SO_REUSEADDR, &opt, sizeof(opt)))
		{
		app->Trace("Ethernet: CServerSocket::ReuseAddress");
		exit(1);
		}
}

void CServerSocket::Listen()
{
	if (listen(fd, 50) == SOCKET_ERROR)
		{
		app->Trace("Ethernet: CServerSocket::Listen");
		exit(1);
		}
}

void CServerSocket::Linger()
{
	LINGER ld;
	ld.l_onoff = 1;
	ld.l_linger = 1000;
	if (!SetSockOpt(SO_LINGER, &ld, sizeof(ld)))
		{
		app->Trace("Ethernet: CServerSocket::Linger");
		exit(1);
		}
}

int CServerSocket::Select(fd_set &input) const
{
	return select(0, &input, 0, 0, 0);
}

CConnection * CServerSocket::Accept(sockaddr_in &sock)
{
	int size = sizeof(sock);
	SOCKET afd = accept(fd, (struct sockaddr *) &sock, &size);
	if (afd == INVALID_SOCKET)
		return 0;
	CConnection * client = new CConnection(afd);
	return client;
}
