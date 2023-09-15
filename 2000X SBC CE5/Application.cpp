/* $Header:   D:/databases/VMdb/archives/2000 RVTS/Application.cpp_v   1.33.1.9.2.11.1.3.1.1.2.2.5.0   Oct 23 2017 16:36:20   RCHAPA  $ */
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
Revision #           Date          Author        Description
----------           --------      ----------    -------------------------------------
  1.5                05/23/05      BWadia        Added complete revision header.
  1.6		         07/25/05	   BWadia	 	 Added SendPolling,SendUI,SendEnHostCommand Functions.
  1.7		         09/19/05	   Bwadia	 	 Updated GetBottomMenuAddress Function.
  1.8		         10/14/05	   BWadia		 Edited GetBottomMenuAddress function to set System Time.
  1.9		         10/24/05	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1.0e
  1.10          	 10/28/05	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1.0f
  1.11	          	 11/07/05	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1.0g
  1.12	         	 11/08/05	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1_MH01
  1.13	         	 12/20/05	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1_MH02
  1.14	         	 01/02/06	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1_MH03
  1.15	         	 01/02/06	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1_MH04
  1.16	         	 02/07/06	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1_MH05
  1.17	         	 02/14/06	   BWadia		 Edited GetBottomMenuAddress function for SBC Version 1_MH06
  1.18	         	 02/22/06	   Bwadia		 Updated GetBottomMenuAddress Function.
  1.17	         	 12/26/06	   BSahu		 Edited Version String for SBC Version 1.1a
  1.21               02/06/07      LAM           Edited Version String for SBC Version 1.1b
  1.22               02/07/07      BSahu         Edited Version String for SBC Version 1.1c
  1.23               02/13/07      LAM           Edited Version String for SBC Version 10.2c
  1.24               02/27/07      BSahu         Edited Version String for SBC Version 10.2d
  1.25               03/08/07      BSahu         Edited Version String for SBC Version 10.2e. And Modified
									             InitTasks() for AutoRun Issue.
  1.26               03/12/07      BSahu         Edited Version String for SBC Version 10.3a
  1.27               04/05/07      BSahu         Edited Version String for SBC Version 10.3b
  1.28               05/04/07      BSahu         Edited Version String for SBC Version 10.3c And Modified Inittask()
                                                 (Tracker Issue -4107).
  1.29               06/01/07      LAM           Edited Version String for SBC Version 10.3d
  1.30               06/11/07      LAM           Edited Version String for SBC Version 10.3e
  1.31               06/26/07	   LAM           Edited Version String for SBC Version 10.3 official build
  1.32               06/28/07      PDwivedi      Edited Version String for SBC Version 10.3f   
  1.33               07/16/07      LAM           Edited Version String for SBC Version 10.30 official build   
  1.33.1.0           04/16/08      PDwivedi      Edited GetBottomMenuAddress() function for MultiLangSupport.
  1.33.1.1           06/12/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestB.
  1.33.1.2           09/02/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestF.
  1.33.1.3           09/04/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestG.
  1.33.1.4           09/09/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestH.
  1.33.1.5           09/12/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestJ.
  1.33.1.6           09/24/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestK.
  1.33.1.7           10/01/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestL.
  1.33.1.8           10/06/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestM.
  1.33.1.9           11/07/08      PDwivedi      Edited GetBottomMenuAddress() function for LangTestN.
  1.33.1.9.2.0       09/22/09      PDwivedi      Edited GetBottomMenuAddress() function for MICRO_11.10A.
  1.33.1.9.2.1       10/22/09      PDwivedi      Edited GetBottomMenuAddress() function for MICRO_11.10B.
  1.33.1.9.2.2       11/06/09      PDwivedi      Edited GetBottomMenuAddress() function for MICRO_11.10C.
  1.33.1.9.2.3       11/18/09      PDwivedi      Edited GetBottomMenuAddress() function for MICRO_11.10D.
  1.33.1.9.2.4       12/07/09      YGupta        Edited GetBottomMenuAddress() function for MICRO_11.10.
  1.33.1.9.2.5       01/25/10      PDwivedi      Edited GetBottomMenuAddress() function for MICRO_11.12.
  1.33.1.9.2.6       05-14-10      BEKymer       Changed Version string to 11.13 for Japanese font release
  1.33.1.9.2.7       06-08-10      PDwivedi      Changed Version string to 11.20A for Standard Micro.
  1.33.1.9.2.8       10-13-10      PDwivedi      Changed Version string to 11.20B for Standard Micro.
  1.33.1.9.2.9       12-9-10       PDwivedi      Changed Version string to 11.20C for Standard Micro Act Recal Issue.
  1.33.1.9.2.10      12-28-10      PDwivedi      Changed Version string to 11.20I for USB History Data Swap Issue.
  1.33.1.9.2.11.1.3  07-29-13      GButron       Changed Version string to 11.33 for frequency offset issue.
  1.33.1.9.2.11.1.4  11/25/13      HsanchezZ     Changed Version string to 11.33E for print the weld data on sample and on error and fix on Horn scan Graph. 
  1.33.1.9.2.11.1.5  02/24/14      HsanchezZ     Changed Version string to 11.33
  1.33.1.9.2.11.1.3.1.1.2.2  02/24/14      HsanchezZ     Changed Version string to 11.34
  1.33.1.9.2.11.1.3.1.1.2.3  10/02/17      RChapa     	 Changed Version string to 11.35
*/

// Application.cpp : implementation file

#include "stdafx.h"
#include "Application.h"
#include "CommPort.h"
#include "EtherPort.h"
#include "ChildView.h"
#include "HostCommand.h"
#include "ServerSocket.h"
#include "Connection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CApplication

CApplication * app;

CApplication::CApplication()
{
	app = this;
}

BEGIN_MESSAGE_MAP(CApplication, CWinApp)
	//{{AFX_MSG_MAP(CApplication)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*This Version String needs to be changed when ever */
/*there is a new version level assigned	.			*/
char Version[7]="11.35K";


void CApplication::InitTasks()
{

		CString port = GetProfileString(_T("Setup"), _T("Port"), _T("\\\\.\\COM1"));
		int speed = GetProfileInt(_T("Setup"), _T("Speed"), CBR_19200);
		#ifndef _WIN32_WCE
			com = new CCommPort("\\\\.\\com2", CBR_9600);
		#else
			com = new CCommPort("\\com2:", CBR_19200);
		#endif
			ether = new CEtherPort();
	
}

int CApplication::ExitInstance() 
{
//	com->Stop();
//	ether->Stop();
//	Sleep(1000);
	delete com;
	delete ether;
	return CWinApp::ExitInstance();
}

bool CApplication::GetBottomMenuAddress(bool *Start_Screen,int *WeldResults_Address,int *mainMenuAddress,int *WeldSetup_Address,int *GraphsMenu_Address,int *Langauage_Index,bool * metric)
{
	if(CCommPort::CommPortNotready)
		return false;
	char data1[8];
	for(int i=0;i<6;i++)
		data1[i]=Version[i];
	unsigned char *data=(unsigned char*) &data1[0];
	int length = 6;
	CHostCommand * command = new CHostCommand(GetMenuAddress_FunId, data, length);
	CHostCommand * response = com->SendUiHostCommand(command);
	if (!response)
		return false;
	if(response->code!=GetMenuAddress_FunId)
	{
		delete response;
		return false;
	}
	char ch=CHostCommand::AckNak();
	data = response->GetData();//Getting Data.
	length = response->GetDataLength();//Getting Length.
	if(ch==ACK)//If Ack.
	{	
	//	data = response->GetData();
		*Langauage_Index=*data++;
		union 
		{
			bool i;
			char c;
		} v;
		v.c = *data++;
		*Start_Screen=v.i;
		delete response;
		return true;
	 }
	 else
	 {
		 delete response;
		 return false;
	 }
}


CHostCommand * CApplication::SendUiHostCommand(CHostCommand *request)
{
	int FunctionID= request->code;
	CHostCommand *response =  com->SendUiHostCommand(request);
	if(response)
	{
		int ResponseCode=response->code;
		if(ResponseCode!=FunctionID)
		{
			/* here send this command again to get correct function number*/
			delete response;
			return 0;
		}
		else
			return response;
	}
	
	return response;
	
}

CHostCommand * CApplication::SendEnHostCommand(CHostCommand *request)
{
	int FunctionID= request->code;
	
	CHostCommand *response =  com->SendEnHostCommand(request);
		return response;
}

CHostCommand * CApplication::SendPollingHostCommand(CHostCommand *request)
{
	int FunctionID= request->code;
	CHostCommand *response =  com->SendPollingHostCommand(request);
	
	if(response)
	{
		int ResponseCode=response->code;
		if(ResponseCode!=FunctionID)
		{	/* here send this command again to get correct function number*/
			delete response;
			return 0;
		}
		else
			return response;
	}
	return response;
	
}

void CApplication::SendWeldData(unsigned char *&data,int length)
{	
	for (int i = 0; i <=ether->clients.GetUpperBound();i++)
		send(ether->clients.GetAt(i)->fd, (char* )data, length, 0);
	
}
