/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/CommPort.h_v   1.8   Mar 08 2007 15:30:14   bsahu  $ */
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
  1.3       05/19/05  Aare        Added complete revision header.
  1.4		07/25/05	BWadia		Added Queues and events for polling Command.
  1.5		09/19/05	BWadia		Added DispLock state in Channel State.
  1.6		02/07/06	Bwadia		Added function ReadUiChar() and ReadUiResponse()
  1.7		05/24/06	YGupta		Added Variable OnPollingTime.
  1.8		03/07/07	BSahu		Added Variable CommPortNotready.
*/

// CommPort.h: interface for the CCommPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMPORT_H__D10DE348_0BFE_46FD_AEDE_2753B1750730__INCLUDED_)
#define AFX_COMMPORT_H__D10DE348_0BFE_46FD_AEDE_2753B1750730__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Queue.h"

class CCommPort  
{
	enum CHANNEL_STATE {
		STATE_WAIT_ACKNAK,	// waiting for ACK or NAK
		STATE_WAIT_FIRST_DLE,	// waiting for first DLE
		STATE_WAIT_STX,		// waiting for STX after DLE
		STATE_WAIT_LENGTH1,	// waiting for upper byte of length
		STATE_WAIT_LENGTH2,	// waiting for lower byte of length
		STATE_WAIT_CODE1,	// waiting for upper byte of command code
		STATE_WAIT_CODE2,	// waiting for lower byte of command code
		STATE_WAIT_DISPLOCK,
		STATE_WAIT_DATA,
		STATE_WAIT_CRC,
		STATE_WAIT_SECOND_DLE,	// waiting for second DLE
		STATE_WAIT_ETX,		// waiting for ETX after DLE
		};
	enum {	ACK = 0x06,
		NAK = 0x15,
		DLE = 0x10,
		STX = 0x02,
		ETX = 0x03 };
public:
	CQueue uiRxQueue;	
	CHostCommand * SendEnHostCommand(CHostCommand *request);
	CHostCommand * SendUiHostCommand(CHostCommand *command);
	CHostCommand * SendPollingHostCommand(CHostCommand *command);
	CCommPort(const CString & port, int speed);
	virtual ~CCommPort();
	static bool OnPollingTime;
	static bool CommPortNotready;
protected:
	bool started;
	void SendUiHostCommand();
	void SendEnHostCommand();
	
	void SendPollingHostCommand();
	static UINT Thread(LPVOID);
	void Thread();
	int ReadCharacter();
	int ReadUiCharacter();
	bool ReadResponse(CHostCommand * response);
	bool ReadUiResponse(CHostCommand * response);
	bool SendRequest(CHostCommand *request);

	static CCommPort * thisPtr;
	HANDLE handle;
	CQueue PollingTxQueue;		// Polling thread transmit queue
	CQueue PollingRxQueue;		// Polling thread receive queue
	CQueue enTxQueue;		// En thread transmit queue
	CQueue enRxQueue;		// En thread receive queue
	CQueue uiTxQueue;		// UI thread transmit queue
		// UI thread receive queue
	CEvent PollingTxEvent;
	CEvent PollingRxEvent;
	CEvent enTxEvent;
	CEvent enRxEvent;
	CEvent uiTxEvent;
	CEvent uiRxEvent;
	CEvent exitEvent;
	unsigned char rxbuf[12800];	// receiver buffer data (for data part of command)
	short rxbufsize;		// receiver buffer size
	CHANNEL_STATE state;		// receiver state machine
	short length;			// host command length
	short code;			// host command code
	short rxindex;			// pointer into receiver buffer
	char checksum;			// host command checksum
	bool ack;			// true if response was ACK
};

#endif // !defined(AFX_COMMPORT_H__D10DE348_0BFE_46FD_AEDE_2753B1750730__INCLUDED_)
