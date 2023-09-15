/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/CommPort.cpp_v   1.20   18 Nov 2009 19:22:04   pdwivedi  $ */
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
  1.4		   07/25/05	BWadia		Added Queues and events for polling Command.
  1.5		   08/08/05	BWadia		Edited ReadResponse Function For Ethernet data
  1.6		   08/12/05	Bwadia		Interchanged the Event Number For Polling And EnHostCommand Function
  1.7		   09/19/05	Bwadia		Removed Trace Statements
  1.8		   10/28/05	BWadia		Modify SendUiHostCommand() function to clear unused buffer.
  1.9		   11/08/05	BWadia		Modify SendUiHostCommand() function to delete previous commands and responses
  1.10		12/07/05	BWadia		Modified for Tracker issue 4010.
  1.11		02/07/06	Bwadia		Added function ReadUiChar() and ReadUiResponse()
  1.12		04/13/06	YGupta		Modified ReadCharacter function for LargeWaitingTime.
  1.13      05/18/06 YGupta      Modified wait for polling to 1 Second.
  1.14		05/24/06	YGupta		Modified SendPollingHostCommand function for OnPollingTime.
  1.15		05/26/06	YGupta		Modified SendPollingHostCommand function for PollingTimeOnMsgScrn.
  1.16		03/07/07	BSahu		   Modified CCommPort() Contructor For AutoRun Issue.
  1.17		05/04/07	BSahu		   Modified CCommPort() Contructor (Tracker - 4107).
  1.18      04/14/08 PDwivedi	   Modify ReadUiCharacter() & ReadCharacter for MultiLangSupport.
  1.19      08/08/08 PDwivedi    Final Code Clean up.
  1.20      11/18/09 PDwivedi    Added changes for Faster Serial Communication.

*/


// CommPort.cpp: implementation of the CCommPort class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Application.h"
#include "CommPort.h"
#include "HostCommand.h"
#include "ChildView.h"
//#include "VGAButtons.h"
//#include "VGABottomHalf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCommPort * CCommPort::thisPtr;
bool CCommPort::CommPortNotready=true;

CCommPort::CCommPort(const CString & port, int speed)
{
	state = STATE_WAIT_ACKNAK;
	rxbufsize = sizeof(rxbuf);
	thisPtr = this;
	started = false;

   do
   {
	handle = CreateFile(port, GENERIC_READ | GENERIC_WRITE,
		0, 0, OPEN_EXISTING, 0, 0);
   }while(handle == INVALID_HANDLE_VALUE);
	if (handle == INVALID_HANDLE_VALUE)
	{
		CommPortNotready=true;
		return;
	}
	else
		CommPortNotready=false;

	SetupComm(handle, 4096, 4096);
	DCB dcb;
	BOOL b = GetCommState(handle, &dcb);
	DWORD err = GetLastError();
	dcb.BaudRate = speed;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = FALSE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	dcb.fDsrSensitivity = FALSE;
	b = SetCommState(handle, &dcb);
	err = GetLastError();
	PurgeComm(handle, PURGE_TXCLEAR | PURGE_RXCLEAR);

	COMMTIMEOUTS tm = { 1/*10*/, 1/*10*/,1/* 10*/, 1/*10*/, 1/*10*/ };	// one millisecond for timeout
	SetCommTimeouts(handle, &tm);
	AfxBeginThread(Thread, 0 );
}
bool CCommPort::OnPollingTime=true;
CCommPort::~CCommPort()
{
}

int CCommPort::ReadCharacter()
{
	int retries = 100;//250
	if((!OnPollingTime)||(CChildView::PollingTimeOnMsgScrn))
		retries=500;
/*	if(CVGABottomHalf::HornDownScreen)
		retries = 25;*/
	if((CChildView::LargeWaitingTime)||(CChildView::ColdStartInProcess))//(CVGAButtons::ColdStartInProcess))
		retries = 3000;
	for (int i = 0; i < retries; i++)
	{
		DWORD recvd;
		char ch;
		ReadFile(handle, &ch, 1, &recvd, 0);
		if (recvd == 1)
		{
			i = ch;
			return i & 0xFF;
		}
		Sleep(10/*20*/);
	}
	return -1;
}

CHostCommand * CCommPort::SendUiHostCommand(CHostCommand *command)
{
	while(uiRxQueue.queue.GetCount()>0)
	{
		delete uiRxQueue.queue.RemoveTail();
	
	}
	
	uiTxQueue.AddCommand(command);
	uiRxEvent.ResetEvent();
	uiTxEvent.SetEvent();

	if(!started)
	{
		WaitForSingleObject(uiRxEvent, 3000);
		uiTxEvent.SetEvent();
	}
   int timeout = 5000;
   if((CChildView::LargeWaitingTime)||(CChildView::ColdStartInProcess))//(CVGAButtons::ColdStartInProcess))
		timeout = 30000;

	WaitForSingleObject(uiRxEvent,timeout);

	uiRxEvent.ResetEvent();
	CHostCommand * response = uiRxQueue.GetCommand();

	return response;
}

bool CCommPort::SendRequest(CHostCommand *request)
{
	unsigned char * cmd = request->GetBuffer();
	DWORD length = request->GetBufLength();

	DWORD dw;
   WriteFile(handle, cmd, length, &dw, 0);
	/*if (WriteFile(handle, cmd, length, &dw, 0)== 0)
		{
		CString s;
		s.Format(_T("WriteFile error %d"), GetLastError());
		
		app->Trace(s);
		}
	else
		{
		CString s;
		s.Format(_T("WriteFile OK %d"), dw);

		app->Trace(s);
		}*/
	FlushFileBuffers(handle);
	if (length != dw)	
	{
		return false;
	}
	return true;
}

bool CCommPort::ReadResponse(CHostCommand *response)
{
//	TRACE(_T("Rx: "));
	int i = 0;
	for (;;)
	{
		int ch = ReadCharacter();
		//TRACE(_T("%02X "), ch & 0xFF);
		/*This case will execute in cas of StartWeldData command.*/
		if(i==0 && ch == DLE)
		{
			while(!(response->StartWeldDataCharReceived(ch & 0xFF)))
			{
				ch = ReadCharacter();
			//	TRACE(_T("%02X "), ch & 0xFF);
			}
			return true;
		}
		i++;
		if (i >= 32)
		{
			i = 1;
			//TRACE(_T("\n  : "));
		}
		if (ch == -1)	// timeout
			return false;
		if (response->CharReceived(ch & 0xFF))
		{
		/*	if(CHostCommand::ack==true)
				TRACE(_T("\n  : ACK\n"));
			else
				TRACE(_T("\n  : NAK!\n"));*/
			return true;
		}
	}
}

CHostCommand * CCommPort::SendEnHostCommand(CHostCommand *request)
{
	enTxQueue.AddCommand(request);
	enRxEvent.ResetEvent();
	enTxEvent.SetEvent();
	if (!started)
	{
		WaitForSingleObject(enRxEvent, 5000);
		enTxEvent.SetEvent();
	}
	WaitForSingleObject(enRxEvent, 1000);
	enRxEvent.ResetEvent();
	CHostCommand * response = enRxQueue.GetCommand();
	return response;
}

void CCommPort::Thread()
{
	exitEvent.ResetEvent();
	started = true;
	for (;;)
		{	
		HANDLE event[4];
		event[0] = exitEvent;
		event[1] = uiTxEvent;
		event[2] = PollingTxEvent;
		event[3] = enTxEvent;
	
	
		DWORD dw = WaitForMultipleObjects(sizeof(event) / sizeof(HANDLE),
			event, FALSE, INFINITE);
		if (dw == WAIT_OBJECT_0)
			break;
		if (dw == (WAIT_OBJECT_0 + 1))
			SendUiHostCommand();
		if (dw == (WAIT_OBJECT_0 + 2))
			SendPollingHostCommand();
		if (dw == (WAIT_OBJECT_0 + 3))
			SendEnHostCommand();
		
	}
}

UINT CCommPort::Thread(LPVOID)
{
	thisPtr->Thread();
	return 0;
}

void CCommPort::SendUiHostCommand()
{
	CHostCommand * command = uiTxQueue.GetCommand();
	
	if (!command)
	{
		uiTxEvent.ResetEvent();
		return;
	}
	short CommandFunID = command->code;//*((short*)command+6);
	for (int i = 0; i < 1; i++)
	{
		if (!SendRequest(command))
			break;
		CHostCommand * response = new CHostCommand(false);

		if (ReadUiResponse(response))
		{
				
				delete command;
				uiRxQueue.AddCommand(response);
					/*clear buffer*/
			   char ch;
		       DWORD recvd=1;
		       while(recvd)
			     ReadFile(handle, &ch, 1, &recvd, 0);

				uiRxEvent.SetEvent(); 
				return;
		}
			
		delete response;
	}
	delete command;
	uiRxQueue.AddCommand(0);
	uiRxEvent.SetEvent();
}

void CCommPort::SendEnHostCommand()
{
	CHostCommand * command = enTxQueue.GetCommand();
	if (!command)
	{
		enTxEvent.ResetEvent();
		return;
	}
	for (int i = 0; i < 1; i++)
	{
		if (!SendRequest(command))
			continue;
		CHostCommand * response = new CHostCommand(false);
		if (ReadResponse(response))
		{
			delete command;
			enRxQueue.AddCommand(response);
			enRxEvent.SetEvent();
			return;
		}
		delete response;
	}
	delete command;
	enRxQueue.AddCommand(0);
	enRxEvent.SetEvent();
}




CHostCommand * CCommPort::SendPollingHostCommand(CHostCommand *command)
{

	int Pollingtime = 1000;
	if((!OnPollingTime)||(CChildView::PollingTimeOnMsgScrn))
		Pollingtime=5000;
	/*if(CVGABottomHalf::HornDownScreen)
		Pollingtime = 500;*/
	PollingTxQueue.AddCommand(command);

		while(PollingRxQueue.queue.GetCount()>0)
		{
		delete PollingRxQueue.queue.RemoveTail();
		}

	PollingRxEvent.ResetEvent();
	PollingTxEvent.SetEvent();

	if(!started)
	{

		WaitForSingleObject(PollingRxEvent,Pollingtime);
		PollingTxEvent.SetEvent();
	}
	WaitForSingleObject(PollingRxEvent,Pollingtime);
	PollingRxEvent.ResetEvent();
	CHostCommand * response = PollingRxQueue.GetCommand();
	return response;
}


void CCommPort::SendPollingHostCommand()
{
	CHostCommand * command = PollingTxQueue.GetCommand();
	if (!command)
	{
		PollingTxEvent.ResetEvent();
		return;
	}
	for (int i = 0; i <1; i++)
	{
		if (!SendRequest(command))
			continue;
		CHostCommand * response = new CHostCommand(false);
		if (ReadResponse(response))
		{
			delete command;
			PollingRxQueue.AddCommand(response);
			/*clear buffer*/
			char ch;
		    DWORD recvd=1;
		    while(recvd)
			  ReadFile(handle, &ch, 1, &recvd, 0);

			PollingRxEvent.SetEvent();
			return;
		}
		delete response;
	}
	delete command;
	PollingRxQueue.AddCommand(0);
	PollingRxEvent.SetEvent();return;
}


bool CCommPort::ReadUiResponse(CHostCommand *response)
{
//	TRACE(_T("Rx: "));
	int i = 0;
	for (;;)
	{
		int ch = ReadUiCharacter();
		//TRACE(_T("%02X "), ch & 0xFF);
		/*This case will execute in cas of StartWeldData command.*/
		if(i==0 && ch == DLE)
		{
			while(!(response->StartWeldDataCharReceived(ch & 0xFF)))
			{
				ch = ReadUiCharacter();
				//TRACE(_T("%02X "), ch & 0xFF);
			}
			return true;
		}
		i++;
		if (i >= 32)
		{
			i = 1;
		//	TRACE(_T("\n  : "));
		}
		if (ch == -1)	// timeout
			return false;
		if (response->CharReceived(ch & 0xFF))
		{
		/*	if(CHostCommand::ack==true)
				TRACE(_T("\n  : ACK\n"));
			else
				TRACE(_T("\n  : NAK!\n"));*/
			return true;
		}
	}
}


int CCommPort::ReadUiCharacter()
{
	int retries = 250;//150;
	if((CChildView::LargeWaitingTime)||(CChildView::ColdStartInProcess))//(CVGAButtons::ColdStartInProcess))
		retries = 1500;
	for (int i = 0; i < retries; i++)
	{
		DWORD recvd;
		char ch;
		ReadFile(handle, &ch, 1, &recvd, 0);
		if(recvd == 1)
		{
			i = ch;
			return i & 0xFF;
		}
		Sleep(20);
	}
	return -1;
}