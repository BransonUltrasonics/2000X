/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/HostCommand.h_v   1.22   12 Sep 2008 21:34:10   pdwivedi  $ */
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
   1.7		 09/20/05	BWadia		Added #defines
   1.8		 10/14/05	Bwadia		Added CharRec function for DataLogger utility.
   1.9		 10/24/05	BWadia		Added #defines for Power Match Curve
   1.10		 10/28/05	BWadia		Added #defines for Sequencing Preset.
   1.11		 01/03/06	BWadia		Added #defines for Error beep, generate alarm
   1.12		 01/13/06	BWadia		Dummy Check In.
   1.13		 01/13/06	BWadia		Added #defines for ViewPreset
   1.14		 02/07/06	BWadia		Added #define GetWeldingStatus
   1.15      03/27/07   BSahu       Added #define GetQualityLimits_FunId
   1.16      10/23/07   PDwivedi    Added #define GetSysVariable_FunId ,GetEptrVariable_FunId for Multilang Support.
   1.17      01/11/08   PDwivedi    Added #defines.   
   1.18		 04/04/08	PDwivedi    Added #define.
   1.19      06/06/08   PDwivedi    Added #define for Alarm & PMC Screen command.
   1.20      08/01/08   PDwivedi    Added #define for printing & USB Screen.
   1.21      09/02/08   PDwivedi    Added #define for Reset Button.
   1.22      09/12/08   PDwivedi    Added changes for Tracker issues of round 2 testing for version LangTestJ.
*/
// HostCommand.h: interface for the CHostCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOSTCOMMAND_H__1C6E4F17_E9CF_4BA0_B848_C3D57BA47C77__INCLUDED_)
#define AFX_HOSTCOMMAND_H__1C6E4F17_E9CF_4BA0_B848_C3D57BA47C77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GetQualityLimits_FunId	137
#define PowerSupply_FunId		   280
#define GetMenuAddress_FunId	   1000
#define GetMenuData_FunId		   1001
#define GetSubMenuData_FunId	   1002
#define SetTime_FunId			   1003
#define SetDate_FunId			   1004
#define GetChoice_FunId			   1005
#define GetAlpha_FunId			   1006
#define SetAlpha_FunId			   1007
#define GetVariable_FunId		   1008
#define SetVariable_FunId		   1009
#define SetRadio_FunId			   1010
#define GetToggle_FunId			   1011
#define GetRadioMenu_FunId		   1012
#define GetRadioLarge_FunId	   1013
#define SetRadioLarge_FunId	   1014
#define VGAButton_FunId			   1015
#define GetPollingData_FunId	   1016
#define GetWeldResults_FunId	   1017
#define SetPassword_FunId		   1018
#define PresetScrButton_FunId    1019
#define GetPasswordMenus_FunId	1020
#define GetAlarmMenu_FunId		   1021
#define GetAlarmObject_FunId	   1022
#define GetWeldStateString_FunId 1023
#define GetWeldData				   1024
#define GetWeldSetup_FunId		   1025
#define WeldDataHeadings_FunId   1026
#define PrintingParameter_FunId  1027
#define UpLoadPreset_FunId		   1028
#define DownLoadPresetFun_Id	   1029
#define PowerMatchCurve_FunId 	1030
#define SequencingPreset_FunId	1031
#define ErrorBeep_FunId			   1032
#define GenerateAlarm_FunId		1033
#define GETUSBVIEWPRESET_FunId	1034
#define GETPSVIEWPRESET_FunId	   1035
#define GetWeldingStatus		   1036

#define GetPollingData_FunResponse 1038

#define GetEptrVariable_FunId    1050
#define SetValue_FunID           1051 
#define GetVariableData_FunID    1052
#define GetBottomMenuData_FunID  1053

#define GetWeldData_FunID		  1054
#define GetWeldStateStrings_FunId 1055	
#define PowerMatchCurve_FunctionId 	1056
#define GETPSVIEWPRESETSCREEN_FunId	   1057
#define GetAlarmSetupFlag      1058
#define GetAlarmMenuItems_FunId     1059
#define GetWeldSetupPrint_FunID  1060
#define GETUSBVIEWPRESETFunId	   1061
#define RESETALARMS_FUNID        1062
#define STATEMACHINE_ENABLED     1063

#define GetSysVariable_FunId     1100

#define ERASESEQUENCE			01
#define CONTINUESEQUENCE		02
#define EDITSEQUENCE		   	03
#define GetChoice_length		5
#define GetVariable_length		4
#define SETUPSTARTPAGE			1
#define SETUPENDPAGE			   5
#define DUPSSTARTPAGE			5
#define DUPSENDPAGE				6
#define WELDDATAID				7
#define GRAPHID					8
#define HORNSCANPRINTTEXTID	9
#define PMCENABLEDISABLE		01
#define PMCCLEARGRAPH			02
#define PMCADDAVGGRAPH			03
#define PMCGETAVGGRAPH			04

class CHostCommand  
{
	
	enum {	ACK = 0x06,
		NAK = 0x15,
		DLE = 0x10,
		STX = 0x02,
		ETX = 0x03 };
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
public:
	unsigned char * buffer;
	short code;	
	bool CharRec(unsigned char ch);
	bool StartWeldDataCharReceived(unsigned char ch);
	int x;
	static char AckNak() ;
	bool CharReceived(unsigned char ch);
	void SetData(short c, unsigned char *data, int length);
	unsigned char * GetData() const;
	unsigned char * GetBuffer() const;
	DWORD GetBufLength() const;
	int GetDataLength() const;
	CHostCommand(bool addAck);
	CHostCommand(short code1, unsigned char * data, int length);
	~CHostCommand();
	static bool ack;
protected:
	static bool dle;
	
	unsigned char * d;
	int len;
	CHANNEL_STATE state;		// receiver state machine
	unsigned char DispLock;
		// host command code
	unsigned char * rxbuf;		// receiver buffer data (for data part of command)
	short rxindex;			// pointer into receiver buffer
	char checksum;			// host command checksum
};

#endif // !defined(AFX_HOSTCOMMAND_H__1C6E4F17_E9CF_4BA0_B848_C3D57BA47C77__INCLUDED_)
