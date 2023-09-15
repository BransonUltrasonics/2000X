/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/Queue.h_v   1.2   Jul 25 2005 09:31:18   bwadia  $ */
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

// Queue.h: interface for the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUEUE_H__D7157E8D_5951_4CFC_9245_08F123EC3129__INCLUDED_)
#define AFX_QUEUE_H__D7157E8D_5951_4CFC_9245_08F123EC3129__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHostCommand;

class CQueue  
{
public:
//	void WaitEvent();
//	void PulseEvent();
	CHostCommand * GetCommand();
	void AddCommand(CHostCommand * command);
//	HANDLE event() const;
	CQueue();
	~CQueue();
CTypedPtrList<CPtrList, CHostCommand *> queue;
protected:
	
	CMutex mutex;
//	CEvent dataAvailable;
};

#endif // !defined(AFX_QUEUE_H__D7157E8D_5951_4CFC_9245_08F123EC3129__INCLUDED_)
