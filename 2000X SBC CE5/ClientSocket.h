/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/ClientSocket.h_v   1.2   Jul 25 2005 09:12:30   bwadia  $ */
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

// ClientSocket.h: interface for the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_CLIENTSOCKET_H__DB386F53_5508_4E80_967C_8FC5C8FD7DCC__INCLUDED_)
#define AFX_CLIENTSOCKET_H__DB386F53_5508_4E80_967C_8FC5C8FD7DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcpSocket.h"

class CClientSocket : public CTcpSocket
{
public:
	CClientSocket(SOCKET afd);
	virtual ~CClientSocket();

protected:
};

#endif // !defined(AFX_CLIENTSOCKET_H__DB386F53_5508_4E80_967C_8FC5C8FD7DCC__INCLUDED_)
