/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/Queue.cpp_v   1.2   Jul 25 2005 09:30:18   bwadia  $ */
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

// Queue.cpp: implementation of the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Queue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CQueue::CQueue()
{
	mutex.Unlock();
//	dataAvailable.ResetEvent();
}

CQueue::~CQueue()
{
}
/*
HANDLE CQueue::event() const
{
	return dataAvailable;
}
*/
void CQueue::AddCommand(CHostCommand *command)
{
	mutex.Lock();
	queue.AddHead(command);
	mutex.Unlock();
}

CHostCommand * CQueue::GetCommand()
{
	mutex.Lock();
	CHostCommand * command = 0;
	if (queue.GetCount() > 0)
		command = queue.RemoveHead();
	mutex.Unlock();
	return command;
}
/*
void CQueue::PulseEvent()
{
	dataAvailable.PulseEvent();
}

void CQueue::WaitEvent()
{
	WaitForSingleObject(dataAvailable, INFINITE);
}
*/