/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/TcpSocket.cpp_v   1.2   Jul 25 2005 09:57:16   bwadia  $ */
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

// TcpSocket.cpp: implementation of the CTcpSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "TcpSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpSocket::CTcpSocket()
{
}

CTcpSocket::~CTcpSocket()
{
}

void CTcpSocket::NonBlock()
{
	unsigned long val = 1;
	Ioctl(FIONBIO, &val);
}

bool CTcpSocket::SetSockOpt(int name, const void *value, int len)
{
	return setsockopt(fd, SOL_SOCKET, name, (const char *) value, len) == 0;
}

bool CTcpSocket::Ioctl(long cmd, u_long *argp)
{
	return ioctlsocket(fd, cmd, argp) == 0;
}

bool CTcpSocket::IsSet(fd_set &set) const
{
	return FD_ISSET(fd, &set) != FALSE;
}

void CTcpSocket::FdSet(fd_set &set) const
{
	FD_SET(fd, &set);
}

void CTcpSocket::FdClr(fd_set &set) const
{
	FD_CLR(fd, &set);
}

bool CTcpSocket::IsClosed() const
{
	return fd == INVALID_SOCKET;
}

void CTcpSocket::SetBufferSizes()
{
	int opt = 16 * 1024;	// 16K for transmit
	if (!SetSockOpt(SO_SNDBUF, &opt, sizeof(opt)))
		app->Trace("Ethernet: TCPSocket::SetBufferSizes send\n");
	opt = 1024;		// 1K for receive
	if (!SetSockOpt(SO_RCVBUF, &opt, sizeof(opt)))
		app->Trace("Ethernet: TCPSocket::SetBufferSizes recv\n");
}

void CTcpSocket::Close()
{
	if (fd != INVALID_SOCKET)
		{
		closesocket(fd);
		fd = INVALID_SOCKET;
		}
}

int CTcpSocket::Write(const char * buf, int len)
{
	int result = send(fd, buf, len, 0);
	if (result > 0)		// Write was successful
		return result;
	if (result == 0)	// This should never happen!
		{
		app->Trace("Ethernet: Huh?? write() returned 0??? Please report this!");
		return -1;
		}
	int error = WSAGetLastError();	// Transient error?
	if ((error == WSAEWOULDBLOCK) || (error == WSAEINTR))
		return 0;
	// Must be a fatal error.
	return -1;
}

int CTcpSocket::Read(char * buf, int len)
{
//	return >= 0 - OK
//	return -1 - EOF
/*
	int ret = recv(fd, buffer, 250, 0);
	if (ret > 0)	// Read was successful.
		return ret;
	// read() returned 0, meaning we got an EOF.
	if (ret == 0)
		{
		app->Trace("Ethernet: WARNING: EOF on socket read (connection broken by peer)\n");
		return -1;
		}
	// read returned a value < 0: there was an error of some kind
	int error = WSAGetLastError();
	if ((error == WSAEWOULDBLOCK) || (error == WSAEINTR))
		return 0;	// ok with these errors
	// here we don't know what happened, so let's just report the error
	app->Trace("Ethernet: TCPSocket::read: error - disconnecting...\n");
*/
	return -1;
}
