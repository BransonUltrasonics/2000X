/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/TcpSocket.h_v   1.3   Aug 08 2005 08:50:00   bwadia  $ */
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

// TcpSocket.h: interface for the CTcpSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPSOCKET_H__C9D1249C_35DE_45BC_AC6F_511A37C1C9D4__INCLUDED_)
#define AFX_TCPSOCKET_H__C9D1249C_35DE_45BC_AC6F_511A37C1C9D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTcpSocket  
{
public:
	int Read(char * buf, int len);
	int Write(const char * buf, int len);
	bool IsClosed() const;
	void FdClr(fd_set & set) const;
	void FdSet(fd_set & set) const;
	bool IsSet(fd_set & set) const;
	CTcpSocket();
	virtual ~CTcpSocket();
	SOCKET fd;
protected:
	void Close();
	void SetBufferSizes();
	bool Ioctl(long cmd, u_long *argp);
	bool SetSockOpt(int name, const void * value, int len);
	void NonBlock();

};

#endif // !defined(AFX_TCPSOCKET_H__C9D1249C_35DE_45BC_AC6F_511A37C1C9D4__INCLUDED_)
