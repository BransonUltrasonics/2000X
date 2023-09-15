/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/EtherPort.h_v   1.3   Aug 08 2005 08:55:40   bwadia  $ */
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

// EtherPort.h: interface for the CEtherPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ETHERPORT_H__83BE352A_A69E_49F3_9A3C_C862AD3B657E__INCLUDED_)
#define AFX_ETHERPORT_H__83BE352A_A69E_49F3_9A3C_C862AD3B657E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CServerSocket;
class CConnection;

class CEtherPort  
{
public:
	void Stop();
	CEtherPort();
	virtual ~CEtherPort();
	CTypedPtrArray<CPtrArray, CConnection *> clients;
protected:
	void CleanupConnections();
	void ProcessInput();
	void ProcessExceptions();
	void NewConnection();
	void AcceptNewConnections();
	bool PollNonblock();
	void PrepareFDSets();
	void SleepIfNoClients();
	void Thread();
	static UINT Thread(LPVOID);

	static CEtherPort * thisPtr;
	CServerSocket * server;
	
	int port;
	fd_set input_set;
	fd_set output_set;
	fd_set exc_set;
	volatile bool stop;
};

#endif // !defined(AFX_ETHERPORT_H__83BE352A_A69E_49F3_9A3C_C862AD3B657E__INCLUDED_)
