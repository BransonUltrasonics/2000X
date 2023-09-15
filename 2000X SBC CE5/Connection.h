/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/Connection.h_v   1.2   Jul 25 2005 09:21:20   bwadia  $ */
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

// Connection.h: interface for the CConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTION_H__159C1FFE_31DD_45AA_A467_1E667DB45C4C__INCLUDED_)
#define AFX_CONNECTION_H__159C1FFE_31DD_45AA_A467_1E667DB45C4C__INCLUDED_
#include "ClientSocket.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHostCommand;

class CConnection : public CClientSocket  
{
	enum {
		COM_PORT_OPTION	= 44,
		SET_BAUDRATE	= 1,
		SET_DATASIZE	= 2,
		SET_PARITY	= 3,
		SET_STOPSIZE	= 4,

		SE	= 240,
		SB	= 250,
		WILL	= 251,
		WONT	= 252,
		DO	= 253,
		DONT	= 254,
		IAC	= 255,
		};
	enum CONN_STATE {
		STATE_NORMAL,
		STATE_NORMAL2,
		STATE_IAC,
		STATE_SINGLE,
		STATE_SB,
		STATE_COMPORT,
		STATE_WAITIAC,
		STATE_SE
		};
public:
	void CloseConnection();
	void ProcessInput();
	CConnection(SOCKET fd);
	virtual ~CConnection();

protected:
	CONN_STATE state;
	CHostCommand * request;
	void CharReceived(char ch);
	char delimiter;
	bool ProcessInputEx();
	char inbuf[4096];
	int inbuflen;
	char outbuf[4096];
	int outbuflen;
};

#endif // !defined(AFX_CONNECTION_H__159C1FFE_31DD_45AA_A467_1E667DB45C4C__INCLUDED_)
