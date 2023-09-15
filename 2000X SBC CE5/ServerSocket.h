/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/ServerSocket.h_v   1.3   Jul 25 2005 09:56:04   bwadia  $ */
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
  1.2       05/19/05  Aare        Added complete revision header.
*/

// ServerSocket.h: interface for the CServerSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERSOCKET_H__E8A31428_E0A8_4F03_8BB8_1185C1F0DA25__INCLUDED_)
#define AFX_SERVERSOCKET_H__E8A31428_E0A8_4F03_8BB8_1185C1F0DA25__INCLUDED_

#include "TcpSocket.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConnection;

class CServerSocket : public CTcpSocket  
{
public:
	CConnection * Accept(struct sockaddr_in & sock);
	int Select(fd_set & input) const;
	CServerSocket(int port);
	virtual ~CServerSocket();

protected:
	void Linger();
	void Listen();
	void ReuseAddress();
	void Bind(int port);
};

#endif // !defined(AFX_SERVERSOCKET_H__E8A31428_E0A8_4F03_8BB8_1185C1F0DA25__INCLUDED_)
