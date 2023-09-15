/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/HostCommand.cpp_v   1.8   Feb 07 2006 17:39:54   bwadia  $ */
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
   1.2       05/19/05   Aare        Added complete revision header.
   1.3		 07/25/05	BWadia		Added AckNak() function.
   1.4		 08/08/05	Bwadia		Added StartWeldDataCharReceived Function
   1.5		 08/12/05	Bwadia		Added 'dle' member Variable
   1.6		 09/19/05	Bwadia		Added DisplayLock To CHANNEL_STATE
   1.7		 10/14/05	Bwadia		Added CharRec function for DataLogger utility.
   1.8		02/07/06	BWadia		Stored Host command's FuntionID in variable 'code'
*/

// HostCommand.cpp: implementation of the CHostCommand class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "HostCommand.h"
#include "Application.h"

#define LEN_AND_FUN_NUM_LENGTH	4

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CHostCommand::CHostCommand(bool addAck)
{
	state = STATE_WAIT_ACKNAK;
	rxbuf = 0;
	buffer = 0;
	if (addAck)
		CharReceived(ACK);
}
bool CHostCommand::ack;
bool CHostCommand::dle;

/******************************************************************************/
/*  this function prepares the host command for the data that is to be sended */
/*  to the welder.															  */
/******************************************************************************/
CHostCommand::CHostCommand(short code1, unsigned char * data, int length)
{
	len = length + 9;
	buffer = new unsigned char[len];
	unsigned char * p = buffer;
	char checksum = 0x00;
	char ch;
	code =code1;
	length += LEN_AND_FUN_NUM_LENGTH;

	*p++ = DLE;
	*p++ = STX;

	ch = length >> 8;
	*p++ = ch;
	checksum ^= ch;

	ch = length & 0xFF;
	*p++ = ch;
	checksum ^= ch;

	ch = code1 >> 8;
	*p++ = ch;
	checksum ^= ch;

	ch = code1 & 0xFF;
	*p++ = ch;
	checksum ^= ch;

	length -= LEN_AND_FUN_NUM_LENGTH;

	d = p;
	for (int i = 0; i < length; i++)
		{
		ch = *data++;
		*p++ = ch;
		checksum ^= ch;
		}

	*p++ = checksum;
	*p++ = DLE;
	*p++ = ETX;
}

CHostCommand::~CHostCommand()
{
	delete buffer;
}


DWORD CHostCommand::GetBufLength() const
{
	return len;
}

int CHostCommand::GetDataLength() const
{
	return len - 10;
}

unsigned char * CHostCommand::GetBuffer() const
{
	return buffer;
}

unsigned char * CHostCommand::GetData() const
{
	return d;
}
/******************************************************************************/
/* the function is called when any character is received fron the welder      */
/* it look at each received byte, put it into right place in the host command */
/* and return true if host comand is complete.                                */
/******************************************************************************/

bool CHostCommand::CharReceived(unsigned char ch)
{
	bool commandCompleted = false;

	switch (state)
		{
	case STATE_WAIT_ACKNAK :
		if (ch == ACK)
		{
			dle=false;
			ack = true;
		}
		else if (ch == NAK)
			ack = false;
		else if(ch==DLE)			// none of the above
		{
			state = STATE_WAIT_STX;
			ack = false;
			dle=true;
			break;
		}
		else
			break;
		state = STATE_WAIT_FIRST_DLE;
		break;

	case STATE_WAIT_FIRST_DLE :
		if (ch == DLE)
			state = STATE_WAIT_STX;
		else
			state = STATE_WAIT_ACKNAK;
		break;

	case STATE_WAIT_STX :
		if (ch == STX)
			state = STATE_WAIT_LENGTH1;
		else
			state = STATE_WAIT_ACKNAK;
		checksum = 0;
		break;

	case STATE_WAIT_LENGTH1 :
		len = ch << 8;
		checksum ^= ch;
		state = STATE_WAIT_LENGTH2;
		break;

	case STATE_WAIT_LENGTH2 :
		len |= ch;
		checksum ^= ch;
		state = STATE_WAIT_CODE1;
		break;

	case STATE_WAIT_CODE1 :
		code = ch << 8;
		checksum ^= ch;
		state = STATE_WAIT_CODE2;
		break;

	case STATE_WAIT_CODE2 :
		code |= ch;
		checksum ^= ch;
		state = STATE_WAIT_DISPLOCK;
		break;

	case STATE_WAIT_DISPLOCK:
		DispLock = ch;
		rxindex = 0;
		len -= 5;//LEN_AND_FUN_NUM_LENGTH;
		// could be leftover from previous atempt
		if (buffer)
			delete buffer;
		if (len == 0)		// no data, just length and code
			{
			buffer = new unsigned char[10];
			state = STATE_WAIT_CRC;
			}
		else
			{
			buffer = new unsigned char[len +10];
			state = STATE_WAIT_DATA;
			}

		d = buffer;
		*d++ = DLE;
		*d++ = STX;
		*d++ = (len + LEN_AND_FUN_NUM_LENGTH+1) >> 8;
		*d++ = (len + LEN_AND_FUN_NUM_LENGTH+1);
		*d++ = code >> 8;
		*d++ = code & 0xFF;
		*d++ = DispLock;

		rxbuf = buffer + 7;//six for DLE,STX,length and Code.
		break;

	case STATE_WAIT_DATA :
		rxbuf[rxindex++] = ch;
		checksum ^= ch;
		if (rxindex >= len)
			state = STATE_WAIT_CRC;
		break;

	case STATE_WAIT_CRC :
		len += 10;
		checksum ^= ch;
		rxbuf[rxindex++] = ch;
		state = STATE_WAIT_SECOND_DLE;
		break;

	case STATE_WAIT_SECOND_DLE :
		rxbuf[rxindex++] = ch;
		if (ch == DLE)
			state = STATE_WAIT_ETX;
		else
			state = STATE_WAIT_ACKNAK;
		break;

	case STATE_WAIT_ETX :
		rxbuf[rxindex++] = ch;
		if (ch == ETX)
			commandCompleted = true;
		state = STATE_WAIT_ACKNAK;
		break;

	default :
		state = STATE_WAIT_ACKNAK;

		}
		return commandCompleted;
}
/*
void CHostCommand::SetData(short c, unsigned char *data, int length)
{
	buffer = new unsigned char[length + 9];
	d = buffer + 6;
	memcpy(d, data, length);
	len = length + 9;
	code = c;
}*/


/***********************************************************************/
/* This function returns wether acknowledgment is received from welder */
/************************************************************************/

char CHostCommand::AckNak() 
{
	if (ack)
		return ACK;
	else if(dle)
		return DLE;
	else
		return NAK;
}

bool CHostCommand::StartWeldDataCharReceived(unsigned char ch)
{
	bool commandCompleted = false;

	switch (state)
	{
	case STATE_WAIT_ACKNAK :
			if (buffer)			// could be leftover from previous attempt
				delete buffer;
			dle=true;
			ack=false;
			state = STATE_WAIT_STX;
			break;
	
	case STATE_WAIT_STX :
		if (ch == STX)
			state = STATE_WAIT_LENGTH1;
		else
			state = STATE_WAIT_ACKNAK;
		checksum = 0;
		break;

	case STATE_WAIT_LENGTH1 :
		len = ch << 8;
		checksum ^= ch;
		state = STATE_WAIT_LENGTH2;
		break;

	case STATE_WAIT_LENGTH2 :
		len |= ch;
		checksum ^= ch;
		state = STATE_WAIT_CODE1;
		break;

	case STATE_WAIT_CODE1 :
		code = ch << 8;
		checksum ^= ch;
		state = STATE_WAIT_CODE2;
		break;

	case STATE_WAIT_CODE2 :
		code |= ch;
		checksum ^= ch;
		rxindex = 0;
		
		if (len == 4)		// no data, just length and code
			{
			buffer = new unsigned char[9]; //Nine for command format.
			state = STATE_WAIT_CRC;
			}
		else
			{
			buffer = new unsigned char[len +7];
			state = STATE_WAIT_DATA;
			}

		d = buffer;
		*d++ = DLE;
		*d++ = STX;
		*d++ = len>> 8;
		*d++ = len;
		*d++ = code >> 8;
		*d++ = code & 0xFF;
		rxbuf = buffer + 6;
		break;

	case STATE_WAIT_DATA :
		rxbuf[rxindex++]=ch;
		checksum ^= ch;
		if (rxindex >len)
		{
			commandCompleted = true;
		len+=7;
		}
	break;

	default :
		state = STATE_WAIT_ACKNAK;
	}
	return commandCompleted;
}



bool CHostCommand::CharRec(unsigned char ch)
{
	bool commandCompleted = false;

	switch (state)
		{
	case STATE_WAIT_ACKNAK :
		if (ch == ACK)
		{
			dle=false;
			ack = true;
		}
		else if (ch == NAK)
			ack = false;
		else if(ch==DLE)			// none of the above
		{
			state = STATE_WAIT_STX;
			ack = false;
			dle=true;
			break;
		}
		else
			break;
		state = STATE_WAIT_FIRST_DLE;
		break;

	case STATE_WAIT_FIRST_DLE :
		if (ch == DLE)
			state = STATE_WAIT_STX;
		else
			state = STATE_WAIT_ACKNAK;
		break;

	case STATE_WAIT_STX :
		if (ch == STX)
			state = STATE_WAIT_LENGTH1;
		else
			state = STATE_WAIT_ACKNAK;
		checksum = 0;
		break;

	case STATE_WAIT_LENGTH1 :
		len = ch << 8;
		checksum ^= ch;
		state = STATE_WAIT_LENGTH2;
		break;

	case STATE_WAIT_LENGTH2 :
		len |= ch;
		checksum ^= ch;
		state = STATE_WAIT_CODE1;
		break;

	case STATE_WAIT_CODE1 :
		code = ch << 8;
		checksum ^= ch;
		state = STATE_WAIT_CODE2;
		break;

	case STATE_WAIT_CODE2 :
		code |= ch;
		checksum ^= ch;
		rxindex = 0;
		len -= LEN_AND_FUN_NUM_LENGTH;
		// could be leftover from previous atempt
		if (buffer)
			delete buffer;
		if (len == 0)		// no data, just length and code
			{
			buffer = new unsigned char[9];
			state = STATE_WAIT_CRC;
			}
		else
			{
			buffer = new unsigned char[len + 9];
			state = STATE_WAIT_DATA;
			}

		d = buffer;
		*d++ = DLE;
		*d++ = STX;
		*d++ = (len + LEN_AND_FUN_NUM_LENGTH) >> 8;
		*d++ = (len + LEN_AND_FUN_NUM_LENGTH);
		*d++ = code >> 8;
		*d++ = code & 0xFF;

		rxbuf = buffer + 6;//six for DLE,STX,length and Code.
		break;

	case STATE_WAIT_DATA :
		rxbuf[rxindex++] = ch;
		checksum ^= ch;
		if (rxindex >= len)
			state = STATE_WAIT_CRC;
		break;

	case STATE_WAIT_CRC :
		len += 9;
		checksum ^= ch;
		rxbuf[rxindex++] = ch;
		state = STATE_WAIT_SECOND_DLE;
		break;

	case STATE_WAIT_SECOND_DLE :
		rxbuf[rxindex++] = ch;
		if (ch == DLE)
			state = STATE_WAIT_ETX;
		else
			state = STATE_WAIT_ACKNAK;
		break;

	case STATE_WAIT_ETX :
		rxbuf[rxindex++] = ch;
		if (ch == ETX)
			commandCompleted = true;
		state = STATE_WAIT_ACKNAK;
		break;

	default :
		state = STATE_WAIT_ACKNAK;

		}
		return commandCompleted;
}