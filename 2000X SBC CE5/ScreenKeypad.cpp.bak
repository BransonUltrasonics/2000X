/* $Header:   D:/databases/VMdb/archives/2000 RVTS/ScreenKeypad.cpp_v   1.29.1.15.1.0   17 Jul 2013 11:42:36   hasanchez  $ */
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
  1.5       05/19/05 Aare        Added complete revision header.
  1.6		   07/25/05	BWadia		Added Function for password Screen 
									      and added asian Language Strings.
  1.7		   08/16/05	Bwadia		Added Chinese Language Strings
  1.8		   09/19/05	BWadia		Modified VariableEntryMode Function For Printing
									      Added HSC Related Functions 
  1.9		   10/14/05	BWadia		Edited VGAVarEntryMode function for USB parameters.
  1.10		10/24/05	BWadia		Edited Draw() for Preset Name
  1.11		12/07/05	BWadia		Modified for Tracker issue 4005,3978,4030,4026.
  1.12		12/20/05	BWadia		Modified  for Tracker issue 3976
  1.13		01/02/06	BWadia		Modified for tracker issue 3954.
  1.14		02/07/07	BWadia		Took care of printing parameters after coldstart
  1.15		04/13/06	YGupta		Modified SendCommandForPassword function for Actuator change password.
  1.16      05/19/06 YGupta      Modified string StrM3_3 for japanese language.
  1.17		09/18/06	BSahu		   Modified ProcessPressedAlphaKey() to handle
								         ESC On PASSWORD Keypad.
  1.18		12/20/06	BSahu     	Modified VGAVarEntryMode Function for DisplayLock Issue.
  1.19		01/03/07	BSahu     	Modified VGAVarEntryMode Function for DisplayLock Issue.
  1.20		01/08/07	BSahu		   Modified VarFormatTable Structure For 2-Decimal Issue.
  1.21		01/10/07	BSahu		   Modified VarFormatTable Structure For 3-Decimal Issue.
  1.22		02/01/07	BSahu		   Modified Strings StrME_4 and StrME_5 For Display Errors 
  1.23		03/12/07	BSahu		   Modified ProcessPressedAlphakey() for Write in Field.
  1.25      03/27/07 BSahu       Modified VGAVarEntryMode() And ProcessPressedAlphakey()
                                 Function For VQS Applicaton
  1.26      05/23/07 BSahu       Modified ProcessPressedAlphakey() for Tracker issue 4117,
                                 VGAVarEntryMode() for print button on RunScreen.
  1.27      06/07/07 BSahu       Modified CScreenKeypad() for SBC String update.
  1.28      06/07/07 BSahu       Modified Str_PrintWeldHistory for SBC String update.
  1.29      06/11/07 BSahu       Modified VGAVarEntryMode() for tracker issue 4169.
  1.29.1.0  10/23/07 PDwivedi    Modified ConvertInternalExternal function for MultiLang Support.
  1.29.1.1  01/11/08 PDwivedi    Modified Constructor,Enter keypad for all type of Objects.
  1.29.1.2	04/04/08 PDwivedi	   Removinf All Local Strings & added more functions.	
  1.29.1.3  04/14/08 PDwivedi	   Modify VGAVarEntryMode(KeyPad_ENTRY) case for MultiLangSupport.
  1.29.1.4  06/06/08 PDwivedi	   Modify CScreenKeypad() & VGAVarEntryMode(KeyPad_ENTRY) for Save Scan result, Preparing MenuPointer List.
  1.29.1.5  08/01/08 PDwivedi    Removed Local Strings & call local functions.
  1.29.1.6  08/08/08 PDwivedi    Final Code Clean up.
  1.29.1.7  08/26/08	PDwivedi    Added DisplayLock condition & HandleEnterOnPassword for Configure Actuator.
  1.29.1.8  09/02/08 PDwivedi    ModiFy HandleEnterOnPassword & Added new strings for Velocity On/Off.
  1.29.1.9  09/04/08 PDwivedi    Modify InsertProperUnits & SendPasswordCommand for tracker Issues.
  1.29.1.10 09/09/08 PDwivedi    Added changes for String Debug Menu.
  1.29.1.11 09/12/08 PDwivedi    Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.29.1.12 10/01/08 PDwivedi	   ModiFy HandleEnterOnPassword for Configure S-Beam Password.
  1.29.1.13 10/22/09 Pdwivedi    ModiFy SendCommandForPassword for ConfigMicroBeam password. 
  1.29.1.14 11/06/09 PDwivedi    Added changes for showing String Number.
  1.29.1.15 06/08/10 PDwivedi    ModiFy SendCommandForPassword for standard actuator.

*/	

// ScreenKeypad.cpp: implementation of the CScreenKeypad class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "SBC.h"
#include "Application.h"
#include "ScreenKeypad.h"
#include "ChildView.h"
//#include "VGAListBox.h"
#include "VgaMenu.h"
#include "VgaMenuItem.h"
#include "VgaVariable.h"
#include "RadioMenu.h"
#include "VgaAlphanumeric.h"
#include "VgaButton.h"
#include "Time.h"
#include "Date.h"
#include "VgaSubMenu.h"
#include "VgaBottomMenu.h"

//#include "VgaButton.h"

extern CChildView::PrintValues Setup,WeldHistory,PowerGraph,ColDistance,VelocityGraph,
			ForceGraph,AmplitudeGraph,FrequencyGraph,PrintSequence,Welddata;

extern CChildView::USBValues  USBWelddata,USBPowerGraph,USBColDistance,USBVelocityGraph,
			USBForceGraph,USBAmplitudeGraph,USBFrequencyGraph;

#define strnset _strnset

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CChildView::PrintingSetup PrintSetup;
extern CList<CString,CString> tempRunScreenList;
extern POSITION RunScreenTemp_pos;
extern POSITION HistoryTemp_pos;
extern CList<CString,CString> tempHistoryList;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 CScreenKeypad::CScreenKeypad()
{

	
}
 CString CScreenKeypad::StrME_1,CScreenKeypad::Str_Off,CScreenKeypad::StrME_2,
    CScreenKeypad::StrME_3,CScreenKeypad::StrME_4,CScreenKeypad::StrME_5,
    CScreenKeypad::Str_Reenter,CScreenKeypad::StrPassTitle,CScreenKeypad::StrEnterPass,
    CScreenKeypad::StrConfirmPass,CScreenKeypad::StrPassIncorrect;	
 CString CScreenKeypad::StrME_1ID,CScreenKeypad::StrME_2ID,CScreenKeypad::StrME_3ID,
    CScreenKeypad::StrME_4ID,CScreenKeypad::StrME_5ID,CScreenKeypad::Str_ReenterID,
    CScreenKeypad::StrPassTitleID,CScreenKeypad::StrEnterPassID,
    CScreenKeypad::StrConfirmPassID,CScreenKeypad::StrPassIncorrectID,
    CScreenKeypad::Str_OffID,CScreenKeypad::HornTitleID;
   int     CScreenKeypad::NoOfWeldresult=0;
	bool    CScreenKeypad::Qualityflag=false;
   int     CScreenKeypad::IsPassword_Accepted=0;
	CString CScreenKeypad::TempPassword;
	char	CScreenKeypad::EditLine[LINESIZE]="           ";
	int 	CScreenKeypad::TypedVal = 0;
	CRect	CScreenKeypad::PressedKeyRect=CRect(0,0,0,0);
    bool    CScreenKeypad::DPFlag = false;
    int     CScreenKeypad::DecimalCount = 0;
    int		CScreenKeypad::DigitCounter = 0;
	int		CScreenKeypad::pointer;
    int		CScreenKeypad::TotalDigits = 0;
    bool	CScreenKeypad::MaxDigitFlag = false;
    static enum CScreenKeypad::FIRSTKEYPRESS FirstKeyPress = CScreenKeypad::KEY_NONE;	
	bool	CScreenKeypad::ErrorDisplayed ;
	bool	CScreenKeypad::pressed=false;
	char	CScreenKeypad::FILLCHAR =' ';
	bool	CScreenKeypad::OnKeypadScreen = false;
	int		CScreenKeypad:: PrevPressedAlphaNumKey=KEYPAD_NONE;
	int		CScreenKeypad:: Index=0;             
	int		CScreenKeypad:: MaxDigit=0;      
	int		CScreenKeypad::  KeyCount;					/*Store the key pressed count of same key*/
	char	CScreenKeypad:: AlphaBuf[LINESIZE+1];       /*Original value buffer*/
	char    CScreenKeypad:: OutputLine[LINESIZE+1]="_"; 
    bool    CScreenKeypad:: EntryFlag=false;       /*TRUE when value is entered successfully.*/
	
	static struct  CScreenKeypad::ALPHA_NUM_KEY AlphaNumKeyProp[] = {
		{3,"0YZ "},  //for this key pressed =0
		{3,"1/# "},   //for this key pressed =1...
		{4,"2ABC"},//2
		{4,"3DEF"},//3
		{4,"4GHI"},//4
		{4,"5JKL"},//5
		{4,"6MNO"},//6
		{4,"7PQR"},//7
		{4,"8STU"},//8
		{4,"9VWX"} };//9

      static struct  CScreenKeypad::ALPHA_NUM_KEY AlphaNumKeyPropSmallCase[] = {
		{3,"0yz "},  //for this key pressed =0
		{3,"1/# "},   //for this key pressed =1...
		{4,"2abc"},//2
		{4,"3def"},//3
		{4,"4ghi"},//4
		{4,"5jkl"},//5
		{4,"6mno"},//6
		{4,"7pqr"},//7
		{4,"8stu"},//8
		{4,"9vwx"} };//9

  static struct CScreenKeypad::var_format_def2 VarFormatTable[] =
{
 {{ "%   ", 3, 0,  1, FALSE, 1,  1 }, { "%   ", 3, 0,  1, FALSE,   1,    1 }},
  {{ "lb  ", 4, 0,  1, FALSE, 1, 10 }, { "N   ", 4, 0,  1, FALSE,4448,10000 }},
  {{ "lb  ", 4, 1,  1, FALSE, 1,  1 }, { "N   ", 4, 0,  1, FALSE,4448,10000 }},
  {{ "s   ", 2, 3,  1, FALSE, 1,  1 }, { "s   ", 2, 3,  1, FALSE,   1,    1 }},
  {{ "PSI ", 3, 1,  1, FALSE, 1,  1 }, { "kPa ", 3, 0,  1, FALSE, 689, 1000 }},
  {{ "in  ", 1, 4,  1, FALSE, 1,  1 }, { "mm  ", 3, 2,  1, FALSE, 254, 1000 }},
  /* DISTANCE3, requires special handling for 7-character strings */
  {{ "in  ", 1, 4,  1, FALSE, 1,  1 }, { "mm  ", 3, 3,  1, FALSE, 254,  100 }},
  {{ "Hz  ", 5, 0,  1, FALSE, 1,  1 }, { "Hz  ", 5, 0,  1, FALSE,   1,    1 }},
  {{ "Hz  ", 4, 0,  1,  TRUE, 1,  1 }, { "Hz  ", 4, 0,  1,  TRUE,   1,    1 }},
  {{ "J   ", 3, 1,  1, FALSE, 1,  1 }, { "J   ", 3, 1,  1, FALSE,   1,    1 }},
  {{ "    ", 9, 0,  1, FALSE, 1,  1 }, { "    ", 9, 0,  1, FALSE,   1,    1 }},
  {{ "in/s", 2, 1,  1, FALSE, 1, 10 }, { "mm/s", 4, 0,  1, FALSE, 254, 1000 }},
  {{ "W   ", 4, 0,  1, FALSE, 1,  1 }, { "W   ", 4, 0,  1, FALSE,   1,    1 }},
  {{ "    ", 5, 0,  1, FALSE, 1,  1 }, { "    ", 5, 0,  1, FALSE,   1,    1 }},
  {{ "    ", 2, 0,  1, FALSE, 1,  1 }, { "    ", 2, 0,  1, FALSE,   1,    1 }},
  {{ "%   ", 3, 1,  1, FALSE, 1,  1 }, { "%   ", 3, 1,  1, FALSE,   1,    1 }},
  {{ "J   ", 5, 0,  1, FALSE, 1, 10 }, { "J   ", 5, 0,  1, FALSE,   1,   10 }},
  {{ "    ", 4, 0,  1, FALSE, 1,  1 }, { "    ", 4, 0,  1, FALSE,   1,    1 }},
  {{ "s   ", 8, 3,  1, FALSE, 1,  1 }, { "s   ", 8, 3,  1, FALSE,   1,    1 }},
  {{ "um  ", 3, 0,  1, FALSE, 1,  1 }, { "um  ", 3, 0,  1, FALSE,   1,    1 }},
  {{ "W   ", 4, 0,  1, FALSE, 1,  1 }, { "W   ", 4, 0,  1, FALSE,   1,    1 }}
};

    static struct CScreenKeypad::var_format_AmpPower VarFormatTableAmpPower[] =
	{
		  {{ "%   ", 3, 1,  1, FALSE, 1,  1 }, { "W   ", 4, 0,  1, FALSE,  CChildView::PeakPowerWattsMax,    1000 }},
		  {{ "%   ", 3, 0,  1, FALSE, 1,  1 }, { "um  ", 3, 0,  1, FALSE,  1,    1 }}
	};
/*
CString CScreenKeypad::StrME_4[]   =   {    
		"Min Value     ",
        "Min Wert      ",
        "Valor min     ",
        "Valore min    ",
        "Val. Min.     ",  
		L"\x6700\x5c0f\x503c\x0020\x0020",
        L"\x6700\x5c0f\x503c\x0020\x0020",
		L"\x6700\x5c0f\x5024\x0020\x0020\x0020\x0020\x0020\x0020",
		L"\xcd5c\xc18c\xce58\x0020\x0020\x0020\x0020\x0020\x0020\x0020\x0020"};
	
CString CScreenKeypad::StrME_5[]   =   {   
			"Max Value     ",
            "Max Wert      ",
            "Valor max     ",
            "Valore max    ",
            "Val. Max.     " , 
			L"\x6700\x5927\x503c\x0020\x0020",
			L"\x6700\x5927\x503c\x0020\x0020",
			L"\x6700\x5927\x5024\x0020\x0020\x0020\x0020\x0020\x0020",
			L"\xcd5c\xb300\xce58\x0020\x0020\x0020\x0020\x0020\x0020\x0020\x0020"};
								

 CString CScreenKeypad::Str_Reenter[]= { 
		 "Reenter Value",
         "Neu Wert eing",
         "Reintr. Valor",
         "Valore del rientro",
         "Resaisir val.",
         L"\x518d\x52a0\x5165\x6570\x503c\x0",
         L"\x91cd\x65b0\x8f38\x5165\x6578\x503c\x0",
         L"\x5024\x3092\x518d\x5165\x529b",
         L"\xac12\x0020\xb2e4\xc2dc\x0020\xc785\xb825" };
											 
 							
 CString CScreenKeypad:: StrInvalidEntry[] =  {
		 "Invalid Entry",
         "Eintrag ungltig",
         "Entrada Invalida",
         "Ingresso non valido",
         "Erreur d'entre",
         L"\x65e0\x6548\x767b\x5f55\x0",
         L"\x7121\x6548\x8f38\x5165\x0",
         L"\x7121\x52b9\x306a\x5165\x529b",
         L"\xbaa8\xd6a8\xac12\x0020\xc785\xb825" };*/

 
 struct CScreenKeypad::VInf VarInfo;
 static struct CScreenKeypad::AInf AlphaInfo;
 


CScreenKeypad::~CScreenKeypad()
{
	CScreenKeypad::Qualityflag=false;
	
}

/*********************************************************************************************/
/* this function is called when keypad list is prepared for any variable, alpha numeric       */
/* date or time object.																		  */
/* arg1: type of the object																	  */
/* arg2: pointer to the structure of the respestive object									  */
/* arg3: data for the object																  */
/* arg4: object text to be displayed as the keypad title.									  */
/*																							  */
/**********************************************************************************************/

CScreenKeypad::CScreenKeypad(int type1,int Pointer,unsigned char *&data,CString* Object_Text)
{
	/*	CString TimeTitle[]={
									 "Time",
									 "Zeit",
									 "Tiem",
									 "Tempo",
									 "Temps",
									 L"\x65f6\x95f4\x0",
									 L"\x6642\x9593\x0",
									 L"\x6642\x9593",
									 L"\xc2dc\xac04" };

        
		CString DateTitle[]={
									"Date",
									"Datum",
									"Fecha",
									"Data",
									"Date",
									L"\x65e5\x671f\x0",
									L"\x65e5\x671f\x0",
									L"\x65e5\x4ed8",
									L"\xb0a0\xc9dc\x0020" };
	   
     CString Str_PrintWeldHistory[] = {
         "Print Weld History",
         "Drucke Datenbank",
         "Impr. Hist. Sold",
         "Stamp Stor saldatr",
         "Imp. Histor. Soud",
         L"\x71a\x63a5\x5386\x53f2\x8bb0\x5f55\x0",
         L"\x7194\x63a5\x8a18\x934\x0",
         L"\x6eb6\x7740\x5c65\x6b74\x0",
         L"\xc6a9\xcc29\x020\xd788\xc2a4\xd1a0\xb9ac\x0" };
	CChildView::IsTwoSecExpired = true;
	KeyOffFlag=false;
	InitializedValues();
	OutputLine[LINESIZE] = 0;
	FirstKeyPress = KEY_NONE;
	VarInfo.Value= -1;//VarInfo.Value;
	type=type1;
	pointer=Pointer;
	Object_Text_pointer=Object_Text;
	VarInfo.Metric=CChildView::metric;

	if (type==CVgaMenuItem::HHMM)
	{
		VarInfo.Keypad_title =TimeTitle[CChildView::Language_Index];
		strcpy(CScreenKeypad:: OutputLine,"HH:MM");
		VarInfo.Disable=0;
	}
	
	if(type==CVgaMenuItem::DATE)
	{
		VarInfo.Keypad_title =DateTitle[CChildView::Language_Index];
		if (CChildView::metric== false)
          strcpy( OutputLine,"MM/DD/YY"); 
		else
          strcpy( OutputLine,"DD/MM/YY");
		VarInfo.Disable=0;
	}

	if(type==CVgaMenuItem::VGA_PRESETSAVEASSIGN)
		{
			PresetPointer = Pointer;
			OutputLine[0] ='_';
			OutputLine[1] ='\0';
			AlphaInfo.Hide=false;
			VarInfo.Disable=0;
			AlphaInfo.MaxLength=10;
			pointer=CVgaMenuItem::VGAPointer;
			CVgaMenuItem::VGAPointer=0;
			
		}


	  if(type == VGA_PASSWORD)
	  {
			PressedKeyRect=CRect(0,0,0,0);
			OutputLine[0] ='_';
			OutputLine[1] ='\0';
			AlphaInfo.Hide=true;
			VarInfo.Disable=0;
			AlphaInfo.MaxLength=12;
		}
	if(type==SaveScanA||type == SaveScanB || type==SaveScanC)
	{
	CString	Str_HornId[] = {
						 "Horn ID",
						 "Sonotroden Nr.",
						 "Cabezal ID",
						 "ID sonotrodo",
						 "ID Sono",
						 L"\x710a\x5934\x6807\x5fd7\x53f7\x0020\x0",
						 L"\x710a\x982d\x8fa8\x8b58\x0020\x0",
						 L"\xff8e\xff70\xff9d\x0049\x0044\x0",
						 L"\xd63c\x0020\x0049\x0044\x0" 
						};
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		AlphaInfo.Alpha_Keypad_title=Str_HornId[CChildView::Language_Index];
		AlphaInfo.Current_Alpha_Value =*Object_Text_pointer;
		AlphaInfo.MaxLength=10;
		AlphaInfo.Hide=false;
		VarInfo.Disable=0;
	}

	if(type==CVgaMenuItem::ALPHA)
	{
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		int Titlelength =40;
		AlphaInfo.Alpha_Keypad_title=CVgaMenuItem::GetString(data,Titlelength);
		AlphaInfo.Current_Alpha_Value = CVgaMenuItem::GetString(data,Titlelength);
		int lengthDummy = IntegerLength;
		AlphaInfo.MaxLength=CVgaMenuItem::Convert_Char_To_Integer(data, lengthDummy, CORDLENGTH)-1;//GetInteger(data,2)-1;
     // printf("\n AlphaInfo.MaxLength=%d",AlphaInfo.MaxLength);
		union {
				bool hid;
				int integer;
				} hide_union;
		hide_union.integer=CVgaMenuItem::Convert_Char_To_Integer(data, lengthDummy, CORDLENGTH);//GetInteger(data,2);
		AlphaInfo.Hide=hide_union.hid;
		AlphaInfo.PARAM_ID =CVgaMenuItem::Convert_Char_To_Integer(data, lengthDummy, CORDLENGTH);//GetInteger(data,2);
		VarInfo.Disable=0;
	}
	/*getting variable information.* /
	if(type==CVgaMenuItem::VARIABLE)
	{
		AlphaInfo.Hide=false;
		int length =40;
		VarInfo.Keypad_title = CVgaMenuItem::GetString(data,length);
		VarInfo.Format=GetInteger(data,CORDLENGTH);//	Variable format, enum FORMAT 2 bytes
		//TRACE("\n\n\n\n\n\n\n\n format is   %d \n\n\n\n\n\n\n\n",VarInfo.Format);
		VarInfo.Digits=GetInteger(data,CORDLENGTH);//	Number of digits to display
		VarInfo.NewVal = GetInteger(data,IntegerLength);	//	Current value
		VarInfo.MinVal = GetInteger(data,IntegerLength)	;//	Minimum value
		VarInfo.MaxVal = GetInteger(data,IntegerLength)	;//Maximum value
		VarInfo.ID = GetInteger(data,CORDLENGTH);	//Variable ID
		VarInfo.Disable	= GetInteger(data,CORDLENGTH);//TRUE if variable can be disabled
		VarInfo.Disableflag = GetInteger(data,CORDLENGTH) ;//flag	Pointer to disable/enable flag
		VarInfo.Bitmask= GetInteger(data,CORDLENGTH)	;//Bit used for this variable enable
		struct var_format_def1 *FormatPtr;
		if (VarInfo.Metric)                         /* Point to format info * / 
			FormatPtr = &VarFormatTable[ VarInfo.Format].Metric;
		else
			FormatPtr = &VarFormatTable[ VarInfo.Format].English;
		
		if(VarInfo.ID==CVgaMenuItem::PRINT_WELDRESULT)
         VarInfo.Keypad_title=Str_PrintWeldHistory[CChildView::Language_Index];
      /* Get variable info for the selected item* /
		VarInfo.MinVal = ConvertInternalExternal( VarInfo.MinVal,(FORMAT)VarInfo.Format );
		VarInfo.MaxVal = ConvertInternalExternal( VarInfo.MaxVal,(FORMAT)VarInfo.Format);
		VarInfo.NewVal = ConvertInternalExternal( VarInfo.NewVal,(FORMAT)VarInfo.Format);
		
		/* Convert energey format if it's too large to show to one * /
		/* decimal place. * /
		if (VarInfo.Format == ENERGY && (VarInfo.NewVal >= 10000 ||
				VarInfo.MaxVal >= 10000 || VarInfo.MinVal >= 10000))
			ConvertVariableFormat( ENERGY, ENERGYDIV10 );      
      
		if (VarInfo.Digits)  /* Find where on line to put # * /
		{
			VarInfo.StartPos = (LINESIZE - VarInfo.Digits);
			VarInfo.Size = LINESIZE + 1 - VarInfo.StartPos;
		}
		else
		{
			VarInfo.Size = VarSize( (FORMAT)VarInfo.Format );
			VarInfo.StartPos = LINESIZE + 1 - VarInfo.Size;
		}
	    /* Some special rules on value entry if sign display is forced */
	    /* (as for FREQOFFSET format).  Value being entered is stored */
		/* as an absolute value during the entry process, with the sign */
		/* contained in VarInfo.Sign.  Sign will stay the same as it */
		/* was when item was selected, unless Inc/Dec keys used. * /
	    if (FormatPtr->ShowSign)
		{
		 if (VarInfo.NewVal < 0)
		 {
			VarInfo.NewVal = - VarInfo.NewVal;
			VarInfo.Sign = -1;
		 }
		 else
			VarInfo.Sign = 1;
		}
		else
			VarInfo.Sign = 0;	       

		if (VarInfo.Disable)
			VarInfo.Disableflag&= ~(VarInfo.Bitmask);
	       
		char ValueLine[LINESIZE+1] = "                    "; /* 20 spaces * /
		SINT32 NewVal;
		char *TempValueLine;
		if (VarInfo.Sign == -1)
			NewVal = -VarInfo.NewVal;
		else
			NewVal = VarInfo.NewVal;
      
	   FormatNum( NewVal,  ValueLine);
       TempValueLine = SplitString(ValueLine, " ", Temp_Str);
	   TRACE(_T("Current Value    %s        "),Temp_Str);
	}*/
}

CScreenKeypad::CScreenKeypad(int type1,unsigned char *&data,CString* Object_Text,int ID,CVgaMenuItem *ptr)
{
	CChildView::IsTwoSecExpired = true;
   ShiftKeyEnable=false;
	KeyOffFlag=false;
	InitializedValues();
	OutputLine[LINESIZE] = 0;
	FirstKeyPress = KEY_NONE;
	VarInfo.Value= -1;//VarInfo.Value;
	type=type1;
   ID_type=ID;
	pointer=(int)ptr;
//   printf("\n pointer=%d",pointer);
	Object_Text_pointer=Object_Text;
	VarInfo.Metric=CChildView::metric;
   
   if (type==CVgaMenu::HHMM)//VgaMenu::HHMM)
	{
		CVgaTime *PtrTime=(CVgaTime *)ptr;
      
      VarInfo.Keypad_title =PtrTime->text;
      VariableTitleID = PtrTime->textID;
      Str_Curr=PtrTime->CurrentString ;
      Str_CurrID=PtrTime->CurrentStringID;
      Str_New=PtrTime->NewString ;
      Str_NewID=PtrTime->NewStringID;
		strcpy(CScreenKeypad:: OutputLine,"HH:MM");
		VarInfo.Disable=0;
	}
   if(type==CVgaMenu::DATE)//CVgaMenuItem::DATE)
	{
		CDate *ptrDate=(CDate *)ptr;
      VarInfo.Keypad_title = ptrDate->text ;
      VariableTitleID =ptrDate->textID;
      Str_Curr=ptrDate->CurrentString ;
      Str_CurrID=ptrDate->CurrentStringID;
      Str_New=ptrDate->NewString ;
      Str_NewID=ptrDate->NewStringID;
		if (CChildView::metric== false)
          strcpy( OutputLine,"MM/DD/YY"); 
		else
          strcpy( OutputLine,"DD/MM/YY");
		VarInfo.Disable=0;
	}
   /*getting variable information.*/
   if(type==CVgaMenu::VARIABLE)
	{
		CVgaVariable *ptrvariable =(CVgaVariable *)ptr;
      AlphaInfo.Hide=false;
		int length =40;
      Str_Curr=ptrvariable->CurrentString ;
      Str_CurrID=ptrvariable->CurrentStringID;
      Str_New=ptrvariable->NewString ;
      Str_NewID=ptrvariable->NewStringID;
		VarInfo.Keypad_title = ptrvariable->Keypad_title ;
      VariableTitleID =ptrvariable->textID;
		VarInfo.Format=ptrvariable->Format;//	Variable format, enum FORMAT 2 bytes
		//TRACE("\n\n\n\n\n\n\n\n format is   %d \n\n\n\n\n\n\n\n",VarInfo.Format);
		VarInfo.Digits= ptrvariable->Digits ;//	Number of digits to display
		VarInfo.NewVal = ptrvariable->NewVal ;	//	Current value
		VarInfo.MinVal = ptrvariable->MinVal ;//	Minimum value
		VarInfo.MaxVal = ptrvariable->MaxVal ;//Maximum value
		VarInfo.ID = ptrvariable->ID ;	//Variable ID
		VarInfo.Disable	= ptrvariable->Disable ;//TRUE if variable can be disabled
		VarInfo.Disableflag = ptrvariable->DisableFlag ; //flag	Pointer to disable/enable flag
		VarInfo.Bitmask = ptrvariable->Bitmask ;//Bit used for this variable enable
      VarInfo.FunName = ptrvariable->FunName;
		struct var_format_def1 *FormatPtr;
		if (VarInfo.Metric)                         /* Point to format info */
			FormatPtr = &VarFormatTable[ VarInfo.Format].Metric;
		else
			FormatPtr = &VarFormatTable[ VarInfo.Format].English;
		
		/*
		if ( VarInfo.Format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( VarInfo.Format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
		*/

		/*if(VarInfo.ID==CScreenObject::PRINT_WELDRESULT)
         VarInfo.Keypad_title=Str_PrintWeldHistory[CChildView::Language_Index];*/
      /* Get variable info for the selected item*/
		VarInfo.MinVal = ConvertInternalExternal( VarInfo.MinVal,(FORMAT)VarInfo.Format );
		VarInfo.MaxVal = ConvertInternalExternal( VarInfo.MaxVal,(FORMAT)VarInfo.Format);
		VarInfo.NewVal = ConvertInternalExternal( VarInfo.NewVal,(FORMAT)VarInfo.Format);
		
		/* Convert energey format if it's too large to show to one */
		/* decimal place. */
		if (VarInfo.Format == ENERGY && (VarInfo.NewVal >= 10000 ||
				VarInfo.MaxVal >= 10000 || VarInfo.MinVal >= 10000))
			ConvertVariableFormat( ENERGY, ENERGYDIV10 );      
      
		if (VarInfo.Digits)  /* Find where on line to put # */
		{
			VarInfo.StartPos = (LINESIZE - VarInfo.Digits);
			VarInfo.Size = LINESIZE + 1 - VarInfo.StartPos;
		}
		else
		{
			VarInfo.Size = VarSize( (FORMAT)VarInfo.Format );
			VarInfo.StartPos = LINESIZE + 1 - VarInfo.Size;
		}
	    /* Some special rules on value entry if sign display is forced */
	    /* (as for FREQOFFSET format).  Value being entered is stored */
		/* as an absolute value during the entry process, with the sign */
		/* contained in VarInfo.Sign.  Sign will stay the same as it */
		/* was when item was selected, unless Inc/Dec keys used. */
	    if (FormatPtr->ShowSign)
		{
		 if (VarInfo.NewVal < 0)
		 {
			VarInfo.NewVal = - VarInfo.NewVal;
			VarInfo.Sign = -1;
		 }
		 else
			VarInfo.Sign = 1;
		}
		else
			VarInfo.Sign = 0;	       

		if (VarInfo.Disable)
			VarInfo.Disableflag&= ~(VarInfo.Bitmask);
	   
//      printf("\n VarInfo.Disableflag in constructor=%d",VarInfo.Disableflag);
		char ValueLine[LINESIZE+1] = "                    "; /* 20 spaces */
		SINT32 NewVal;
		char *TempValueLine;
		if (VarInfo.Sign == -1)
			NewVal = -VarInfo.NewVal;
		else
			NewVal = VarInfo.NewVal;
      
	   FormatNum( NewVal,  ValueLine);
       TempValueLine = SplitString(ValueLine, " ", Temp_Str);
	   TRACE(_T("Current Value    %s        "),Temp_Str);
	}
   if(type==CVgaMenu::ALPHA)
	{
		CVgaAlphanumeric *ptrAplhanumeric =(CVgaAlphanumeric *)ptr;
      OutputLine[0] ='_';
		OutputLine[1] ='\0';
		int Titlelength =40;
      Str_Curr=ptrAplhanumeric->CurrentString ;
      Str_New=ptrAplhanumeric->NewString ;
		AlphaInfo.Alpha_Keypad_title=ptrAplhanumeric->TitleKeyPad ;
      AlphaTitleID=ptrAplhanumeric->textID;
		AlphaInfo.Current_Alpha_Value = ptrAplhanumeric->CurrentAlphaValue;
		int lengthDummy = IntegerLength;
		AlphaInfo.MaxLength=ptrAplhanumeric->CharAllowed ; 
      union {
				bool hid;
				int integer;
				} hide_union;
		hide_union.integer= ptrAplhanumeric->CharHidden ; 
      AlphaInfo.Hide=hide_union.hid;
      AlphaInfo.MenuNak=ptrAplhanumeric->MenuNak;
      AlphaInfo.MenuAck=ptrAplhanumeric->MenuAck;
      AlphaInfo.FunName = ptrAplhanumeric->FunName;
      VarInfo.Disable=0;
	}
   if(type == VGA_PASSWORD)
	  {
		//printf("\n VGA_PASSWORD");	
		PressedKeyRect=CRect(0,0,0,0);
			OutputLine[0] ='_';
			OutputLine[1] ='\0';
			AlphaInfo.Hide=true;
			VarInfo.Disable=0;
			AlphaInfo.MaxLength=12;
         PassWordMenu="";
         if((pointer!=0)&&(pointer!=1))
         {
            //printf("\n (pointer!=0)&&(pointer!=1)");
            switch(ptr->GetType())
            {
               case CVgaMenu::SUBMENU:
                  {
                     CVgaSubMenu *ptr1=(CVgaSubMenu *)ptr;
                     PassWordMenu=ptr1->submenu;
                  }
               break;
               case CVgaMenu::BottomMenu_Id:
                  {
                     CVgaBottomMenu *Bottom=(CVgaBottomMenu *)ptr;
                     PassWordMenu=Bottom->BottomSubmenu;
                  }
               break;
               case CVgaMenu::VGA_Button_OBJECT:
                  {
                     CVgaButton * VgaButtonptr=(CVgaButton *)ptr;
                     PassWordMenu=VgaButtonptr->MenuName;
                  }
                  break;
            }
         }
      }
   if(type==SaveScanA||type == SaveScanB || type==SaveScanC)
	{
	/*CString	Str_HornId[] = {
						 "Horn ID",
						 "Sonotroden Nr.",
						 "Cabezal ID",
						 "ID sonotrodo",
						 "ID Sono",
						 L"\x710a\x5934\x6807\x5fd7\x53f7\x0020\x0",
						 L"\x710a\x982d\x8fa8\x8b58\x0020\x0",
						 L"\xff8e\xff70\xff9d\x0049\x0044\x0",
						 L"\xd63c\x0020\x0049\x0044\x0" 
						};*/
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		AlphaInfo.Alpha_Keypad_title=CChildView::thisPtr->Str_HornId;//Str_HornId[CChildView::Language_Index];
      AlphaInfo.Current_Alpha_Value =*Object_Text_pointer;
		AlphaInfo.MaxLength=10;
		AlphaInfo.Hide=false;
		VarInfo.Disable=0;
	}
   
}
/*****************************************************************************/
/* This function draws the keypad screen for variable or alphanumeric menu   */
/* item. The function display the title information as well as the current   */
/* value of the variable in the current value box. It draws the keypad button*/ 
/* in Released format                                                        */
/*                                                                           */
/* Parameters                                                                */
/* *pDC : Device context object to draw keypad                               */
/*****************************************************************************/


void CScreenKeypad::Draw(CDC *pDC)
{
/*   CString StrPassTitle[] =  {    
		 "Password",
         "Passwort",
         "Cntrsena",
         "Password",
         "M. Passe",
         L"\x5bc6\x7801\x0",
         L"\x5bc6\x78bc\x0",
         L"\xff8a\xff9f\xff7d\xff9c\xff70\xff84\xff9e",
         L"\xd328\xc2a4\xc6cc\xb4dc"  };


  CString  StrEnterPass[] =  {   
		 "Enter Password",
         "Passwort eingeben",
         "Entrar contrasea",
         "Inserisci Password",
         "Entrer mot de passe",
         L"\x767b\x5f55\x5bc6\x7801\x0",
         L"\x8f38\x5165\x5bc6\x78bc\x0",
         L"\xff8a\xff9f\xff7d\xff9c\xff70\xff84\xff9e\x5165\x529b",
         L"\xd328\xc2a4\xc6cc\xb4dc\x0020\xc785\xb825"   };
 
 CString StrConfirmPass[] =  {   
		 "Confirm Password",
         "Passwort besttigen",
         "Confirm. Contrasea",
         "Conferma Password",
         "Confirmer mot de p.",
         L"\x786e\x8ba4\x5bc6\x7801\x0",
         L"\x78ba\x8a8d\x5bc6\x78bc\x0",
         L"\xff8a\xff9f\xff7d\xff9c\xff70\xff84\xff9e\x78ba\x8a8d",
         L"\xd328\xc2a4\xc6d0\xb4dc\x0020\xd655\xc778"  };*/

 

    /*Draw bounding rectangle */
	pDC->SelectObject(&CVgaMenuItem::penBlack1);
	pDC->Rectangle(99+XOFFSET,43+YOFFSET,537+XOFFSET,419+YOFFSET);
	CVgaMenuItem::DrawRect(pDC, Blue,  Bounding_Rect);//bounding RECT BLUE
   
	//Draw current value rectangle
	if(type != VGA_PASSWORD)
    	CVgaMenuItem::DrawRect(pDC, White,  Current_Value_Rect);
	
	//new value rect
	CVgaMenuItem::DrawRect(pDC, White,  New_Value_Rect);
	
   /*	if(type == CScreenObject::VGA_PRESETSAVEASSIGN)
	{
		CVgaMenuItem::DrawText(pDC, Bigfont, White,
							Keypad_Title_Rect, StrM3_3[CChildView::Language_Index],true);
		CVgaMenuItem::DrawText(pDC, SmallFont, White, Current_Value_String_Rect,
								Str_CurrPresetName[CChildView::Language_Index],false);
		CVgaMenuItem::DrawText(pDC, SmallFont, White, New_Value_String_Rect, 
								Str_NewPresetName[CChildView::Language_Index],false);

	    CVgaMenuItem::DrawText(pDC,SmallFont, Black, Current_Value_Rect,
								(CVGAListBox::CurrentPresetName) ,false);
	}*/
   CString VariableTitle=VarInfo.Keypad_title;
   CString AlphaTitle=AlphaInfo.Alpha_Keypad_title;
   CString TempTitlePass = StrPassTitle;
   CString TempEnterPass = StrEnterPass;
   CString TempConfirmPass = StrConfirmPass;
   CString TempCurr = Str_Curr;
   CString TempNew = Str_New;
   if(CChildView::thisPtr->StringDebugFlag)
   {
      VariableTitle=VariableTitleID + _T(" ") + VarInfo.Keypad_title;
      if((type==CVgaMenu::ALPHA))
      {
         AlphaTitle = AlphaTitleID+ _T(" ") + AlphaInfo.Alpha_Keypad_title;
      }
      else
         AlphaTitle = HornTitleID + _T(" ") + AlphaInfo.Alpha_Keypad_title;
      TempTitlePass = StrPassTitleID + _T(" ")+ StrPassTitle;
      TempEnterPass = StrEnterPassID + _T(" ")+ StrEnterPass;
      TempConfirmPass= StrConfirmPassID + _T(" ")+ StrConfirmPass;
      TempCurr= Str_CurrID + _T(" ")+ Str_Curr;
      TempNew = Str_NewID + _T(" ")+ Str_New;
   }
	if(type == VGA_PASSWORD)
	{
		CVgaMenuItem::DrawText(pDC, Bigfont, White,Keypad_Title_Rect, 
								TempTitlePass/*[CChildView::Language_Index]*/,true);

      if(pointer!=1)
		    CVgaMenuItem::DrawText(pDC, SmallFont, White,New_Value_String_Rect, 
									TempEnterPass/*[CChildView::Language_Index]*/,false);
		else
			 CVgaMenuItem::DrawText(pDC, SmallFont, White,New_Value_String_Rect,
										TempConfirmPass/*[CChildView::Language_Index]*/,false);
	}
	else if((type!=CVgaMenu::ALPHA)&&(type!=SaveScanA)&&(type != SaveScanB)&&( type!=SaveScanC))
		CVgaMenuItem::DrawText(pDC, Bigfont, White,Keypad_Title_Rect, 
											VariableTitle,true);
	else if((type==CVgaMenu::ALPHA)||(type==SaveScanA||type == SaveScanB || type==SaveScanC))
	{
	  CVgaMenuItem::DrawText(pDC, Bigfont, White,Keypad_Title_Rect,
									AlphaTitle,true);

	  CVgaMenuItem::DrawText(pDC, SmallFont, Black, Current_Value_Rect,
								AlphaInfo.Current_Alpha_Value ,false);
	}
   if(type == CVgaMenu::DATE)//CScreenObject::DATE)
   {
      CString text_obj=*Object_Text_pointer;
	  text_obj.Delete(0,2);
	  CVgaMenuItem::DrawText(pDC, SmallFont, White, Current_Value_String_Rect,
								TempCurr/*Str_CurrDate[CChildView::Language_Index]*/,false);
	  CVgaMenuItem::DrawText(pDC, SmallFont, White, New_Value_String_Rect, 
								TempNew/*Str_NewDate[CChildView::Language_Index]*/,false);
	  CVgaMenuItem::DrawText(pDC, SmallFont, Black, Current_Value_Rect,
																	text_obj ,false);
   }
   else if(type == CVgaMenu::HHMM)//CScreenObject::HHMM)
   {
	   CString text_obj=*Object_Text_pointer;
	   text_obj.Delete(0,2);
	   CVgaMenuItem::DrawText(pDC, SmallFont, White, Current_Value_String_Rect, 
									TempCurr/*Str_CurrTime[CChildView::Language_Index]*/,false);
	   CVgaMenuItem::DrawText(pDC, SmallFont, White, New_Value_String_Rect, 
								TempNew/*Str_NewTime[CChildView::Language_Index]*/,false);
	   CVgaMenuItem::DrawText(pDC, SmallFont, Black, Current_Value_Rect,text_obj ,false);
   }
   else if(/*(type != CVgaMenuItem::VGA_PRESETSAVEASSIGN)&&*/(type != VGA_PASSWORD))
   {
      
	  CVgaMenuItem::DrawText(pDC, SmallFont, White, Current_Value_String_Rect,
								TempCurr/*StrCurrentValue[CChildView::Language_Index]*/,false);
	   CVgaMenuItem::DrawText(pDC, SmallFont, White, New_Value_String_Rect, 
									TempNew/*StrNewValue[CChildView::Language_Index]*/,false);
	}
 	CRect keypadrect;
	pDC->SetBkMode(TRANSPARENT);
	int left =Left_Of_Keys;
	int top=Top_CoOrdinate_Key;
  
   char strline3[][4]={" /#","abc","def","ghi","jkl","mno","pqr","stu", "vwx"," + ",
													   " yz"," - ","<--","   ","ENT","OFF"};
   char strline1[][4]={" /#","ABC","DEF","GHI","JKL","MNO","PQR","STU", "VWX"," + ",
													   " YZ"," - ","<--","   ","ENT","OFF"};
   
   char strline2[][4]={" 1 "," 2 "," 3 "," 4 "," 5 "," 6 "," 7 "," 8 "," 9 ","INC",
												" 0 ","DEC", "ESC", " ",NULL,NULL,NULL,NULL};
	int count=0;int keyid=0;

	if((type ==CVgaMenu::ALPHA)||(type == VGA_PASSWORD)/*||(type == CVgaMenuItem::VGA_PRESETSAVEASSIGN)*/
		||(type==SaveScanA||type == SaveScanB || type==SaveScanC))
	{
		if(ShiftKeyEnable)
      {
         strcpy(strline3[9],"-->");
		   strcpy(strline3[11],"   ");
		   strcpy(strline2[9],"   ");
		   strcpy(strline2[11],"SFT");
      }
      else
      {
      strcpy(strline1[9],"-->");
		strcpy(strline1[11],"   ");
		strcpy(strline2[9],"   ");
		strcpy(strline2[11],"SFT");
      }
	}
	for(int j=0;j<TOTAL_KEYPAD_ROW;j++)
	{
	  for(int k=0;k<TOTAL_KEYPAD_COLOUMN;k++)
	  {
		keypadrect=CRect(left,top,left+Width_Of_Key,top+Width_Of_Key);
		OffsetRect(pDC,&keypadrect,CChildView::Color_Array[Gray]);
		pressed = false;
		Draw_Pressed_Released_Button(pDC, &keypadrect);
		if(j!=4)
		{
			if(j==3 && k==0 &&((type ==CVgaMenuItem::ALPHA)||(type == VGA_PASSWORD)
				/*||(type == CVgaMenuItem::VGA_PRESETSAVEASSIGN)*/
				||(type==SaveScanA||type == SaveScanB || type==SaveScanC)))
         {
				if(ShiftKeyEnable)
            CVgaMenuItem::DrawText(pDC, SmallFont,Black,keypadrect,
													strline3[count],true);
            else
            CVgaMenuItem::DrawText(pDC, SmallFont,Black,keypadrect,
													strline1[count],true);
         }
			else
			{
				if(ShiftKeyEnable)
            {
               CVgaMenuItem::DrawText(pDC, SmallFont,Black,CRect(left+YOFFSET,
																	top+XOFFSET,
																	left+50+YOFFSET,
																	top+30+XOFFSET), 
																	strline3[count],true);
            }
            else
            {
            CVgaMenuItem::DrawText(pDC, SmallFont,Black,CRect(left+YOFFSET,
																	top+XOFFSET,
																	left+50+YOFFSET,
																	top+30+XOFFSET), 
																	strline1[count],true);
            }
				CVgaMenuItem::DrawText(pDC, SmallFont, Black,CRect(left+YOFFSET,
																	top+20+XOFFSET,
																	left+50+YOFFSET,
																	top+50+XOFFSET),	
            													strline2[count],true);
            
			}
		}
		else
      {
			if((j==4)&&(k==0))
         {
            if(ShiftKeyEnable)
               CVgaMenuItem::DrawText(pDC, SmallFont,Black,CRect(left+YOFFSET,
																	   top+XOFFSET,
																	   left+50+YOFFSET,
																	   top+30+XOFFSET), 
																	   strline3[count],true);
            
            else
               CVgaMenuItem::DrawText(pDC, SmallFont,Black,CRect(left+YOFFSET,
																	   top+XOFFSET,
																	   left+50+YOFFSET,
																	   top+30+XOFFSET), 
																	   strline1[count],true);
			   CVgaMenuItem::DrawText(pDC, SmallFont, Black,CRect(left+YOFFSET,
																	   top+20+XOFFSET,
																	   left+50+YOFFSET,
																	   top+50+XOFFSET),	
																	   strline2[count],true);
         }
         else
         {
            if(ShiftKeyEnable)
               CVgaMenuItem::DrawText(pDC, SmallFont,Black,keypadrect,strline3[count],true);
            else
               CVgaMenuItem::DrawText(pDC, SmallFont,Black,keypadrect,strline1[count],true);
         }
      }
		left+=Width_Of_Key + Gap_Of_Key;
		count++;
	  }
	  left=Left_Of_Keys;
	  top+=Width_Of_Key + Gap_Of_Key;
	}
	///DRAWING DECIMAL POINT
	CVgaMenuItem::DrawRect(pDC, Black,  CRect(420+YOFFSET,375+XOFFSET,
												420+YOFFSET+3,375+XOFFSET+3));
	
	//drawing rect of "off"
	if((VarInfo.Disable==1)&&(VarInfo.ID!=1)/*&& (VarInfo.ID != CVgaMenuItem::XXCANTCHANGEXX ) &&
		(VarInfo.ID != CVgaMenuItem::PRETRIGDIST) &&(VarInfo.ID != CVgaMenuItem::FORCESTEPFLAG) && 
		(VarInfo.ID != CVgaMenuItem::AMPLITUDESTEPFLAG)*/ )
    {
		CVgaMenuItem::DrawRect(pDC, Gray,  Button_Off_Rect);
		CVgaMenuItem::DrawText(pDC, SmallFont,Black,OFF_Rect,Str_Off/* "OFF"*/,true);
		Draw_Pressed_Released_Button(pDC, &OFF_Rect);
	}
	if(type!=CVgaMenu::VARIABLE)
		CVgaMenuItem::DrawText(pDC, SmallFont,Black,New_Value_Rect, OutputLine,false); 
	else
		CVgaMenuItem::DrawText(pDC,SmallFont,Black,New_Value_Rect, EditLine,false);
	if(ErrorDisplayed)
		ErrorDisplayed=false;
	if(type==CVgaMenu::VARIABLE)
	{ 	
		DisplayVGAMinMax(pDC);
	   CVgaMenuItem::DrawText(pDC, SmallFont, Black,Current_Value_Rect,Temp_Str ,false);
		VGADisplayCurrentNewValue(pDC);/*Display the Existing Value*/
	}
}

/*****************************************************************************************************/
/* the function checks the position of the mouse click. if the user has clicked on any keypad button */
/* then this function draws that keypad button in the pressed state.                                 */
/*																									 */
/*****************************************************************************************************/
void CScreenKeypad::DrawPressedkey(CPoint point, CDC *pDC)
{
	PressedKeyRect=CRect(0,0,0,0);
	int left =Left_Of_Keys;
	int top=Top_CoOrdinate_Key;
	CRect keyrect;
	for(int j=0;j<TOTAL_KEYPAD_ROW;j++)
	{
		for(int k=0;k<TOTAL_KEYPAD_COLOUMN;k++)
		{
			keyrect=CRect(left,top,left+Width_Of_Key,top+Width_Of_Key);
			if(keyrect.PtInRect(point))
			{
				PressedKeyRect =keyrect;
				pressed=true;
				Draw_Pressed_Released_Button(pDC,&keyrect);
				break;
			}
			left+=Width_Of_Key + Gap_Of_Key;
		}
		left=Left_Of_Keys;
		top+=Width_Of_Key + Gap_Of_Key;
	}
	if(((VarInfo.Disable==1)&&(VarInfo.ID!=1)
		/*&& (VarInfo.ID != CVgaMenuItem::XXCANTCHANGEXX ) 
		&& (VarInfo.ID != CVgaMenuItem::PRETRIGDIST      ) 
		&& (VarInfo.ID != CVgaMenuItem::FORCESTEPFLAG    ) 
		&& (VarInfo.ID != CVgaMenuItem::AMPLITUDESTEPFLAG)*/ )
		&& OFF_Rect.PtInRect(point))
	{
		PressedKeyRect =OFF_Rect;
		pressed=true;
		Draw_Pressed_Released_Button(pDC,&OFF_Rect);
	}
}

/**********************************************************************************/
/* this function is called when the user releases the left mouse button if		  */
/* keypad is active. if the user has pressed any button then this function draws  */
/* that button in the released state.											  */
/**********************************************************************************/

void CScreenKeypad::Draw_Pressed_Released_Button(CDC *pDC, CRect rect)
{
	CPen * oldPen;
	if (pressed)
		oldPen = pDC->SelectObject(&CVgaMenuItem::penBlack1);
	else
		oldPen = pDC->SelectObject(&CVgaMenuItem::penWhite1);
	pDC->MoveTo(rect.left, rect.top );
	pDC->LineTo(rect.right , rect.top );
	pDC->MoveTo(rect.left + 1 , rect.top + 1);
	pDC->LineTo(rect.right , rect.top + 1);
	pDC->MoveTo(rect.left , rect.top );
	pDC->LineTo(rect.left , rect.bottom );
	pDC->MoveTo(rect.left + 1 , rect.top + 1 );
	pDC->LineTo(rect.left + 1 , rect.bottom );
	if (pressed)
		oldPen = pDC->SelectObject(&CVgaMenuItem::penWhite1);
	else
		oldPen = pDC->SelectObject(&CVgaMenuItem::penBlack1);
	pDC->MoveTo(rect.right - 1 , rect.top );
	pDC->LineTo(rect.right - 1 , rect.bottom );
	pDC->MoveTo(rect.right - 2 , rect.top + 1 );
	pDC->LineTo(rect.right - 2 , rect.bottom );
	pDC->MoveTo(rect.left , rect.bottom - 1 );
	pDC->LineTo(rect.right , rect.bottom - 1 );
	pDC->MoveTo(rect.left + 1 , rect.bottom - 2 );
	pDC->LineTo(rect.right , rect.bottom - 2 );
	pDC->SelectObject(oldPen);
}


void CScreenKeypad::OffsetRect(CDC *pDC,CRect rect, COLORREF col)
{
	CRect r(rect);
	r.OffsetRect(XOFFSET, YOFFSET);
	pDC->FillSolidRect(&r,col);
}

/********************************************************************************************************/
/* This function is called when the user clicks on keypad. the function checks the key pressed key and  */
/* calls the function ProcessKeypad() for its processing												*/
/********************************************************************************************************/
bool CScreenKeypad::MouseClick(const CPoint &point, CChildView *view,CDC*pDC )
{
	if(pressed==true)
	pressed=false;
	Draw_Pressed_Released_Button(pDC, PressedKeyRect);
	int left =Left_Of_Keys;
	int top=Top_CoOrdinate_Key;
	int i=0;
	CRect keypadrect;
	for(int j=0;j<TOTAL_KEYPAD_ROW;j++)
	{
		for(int k=0;k<TOTAL_KEYPAD_COLOUMN;k++)
		{
			keypadrect=CRect(left,top,left+Width_Of_Key,top+Width_Of_Key);
			if(keypadrect==PressedKeyRect)
			{
				i++;
				if(ProcessKeypad(j,k,view,pDC))
					view->Invalidate();
				break;									
			}
			if(i>0)
				break;
			left+=Width_Of_Key + Gap_Of_Key;
		}
		left = Left_Of_Keys;
		top += Width_Of_Key + Gap_Of_Key;
	}
	if(((VarInfo.Disable==1)&&(VarInfo.ID!=1)
	/*	&& (VarInfo.ID != CVgaMenuItem::XXCANTCHANGEXX )
		&& (VarInfo.ID != CVgaMenuItem::PRETRIGDIST      ) 
		&& (VarInfo.ID != CVgaMenuItem::FORCESTEPFLAG    ) 
		&& (VarInfo.ID != CVgaMenuItem::AMPLITUDESTEPFLAG)*/ ) 
		&& (PressedKeyRect==OFF_Rect))
			ProcessKeypad(5,0,view,pDC);
	return 0;
}


/****************************************************************************/
/* This function processes the keypad screen entries. It checks for INC/DEC */
/* key pressed or Digits key pressed and process them accordingly. It will  */
/* remain in the function unless and until ENT or ESC key is pressed on the */
/* keypad. One can also get out from this function by pressing bottom button*/
/*                                                                          */
/****************************************************************************/
bool CScreenKeypad::ProcessKeypad(int x, int y,CChildView *view,CDC *pDC)
{
	int key_no[][3]={1,2,3,4,5,6,7,8,9,10,0,11,12,13,14,15};
	bool exit;
	if(type!=CVgaMenuItem::VARIABLE)
		exit=ProcessPressedAlphakey( key_no[x][y] , type,view,pDC);
	else
		exit =VGAVarEntryMode( key_no[x][y],pDC,view);
	if(exit)
		OnKeypadScreen_flag=false;
	return exit;
}


/***************************************************************************/
/*Description:-                                                            */
/*  This function is processing the Alpha key pressed on the keypad screen.*/
/*  On pressing the key again with in one sec key toggling will take place.*/
/*  Else on pressing other key the char will display on the next position. */
/*Arg1:Which Alpha key is pressed on the keypad screen.                    */
/***************************************************************************/
void CScreenKeypad::VGAAlphaEntryMode(int KeyPressed,CChildView *view,CDC *pDC)
{
	char AlphaNumChar;
   
	TRACE(_T("PrevPressedAlphaNumKey IS %d AND KEYPRESSED  IS %d"),PrevPressedAlphaNumKey,KeyPressed);
    if(PrevPressedAlphaNumKey != KeyPressed || CChildView::IsTwoSecExpired)
    /*Store and display the same key to next cloumn if 1 sec are elapsed 
    or the pressed key is not same as prev. pressed key.*/
	{

      
	   KeyCount = 1;
	   if(PrevPressedAlphaNumKey != KEYPAD_NONE )/*Esc if value is entered at
                                              0th index of OutputLine Buffer*/
	   {
        if(AlphaInfo.Hide && OutputLine[MaxDigit] != '_' &&
           OutputLine[MaxDigit] != '*' )
         OutputLine[MaxDigit] = '*';
	      Index++;/*Increment the index value*/
	      MaxDigit++;
        
	   }

	   if(KeyPressed==KEYPAD_DEC)
		  AlphaNumChar=' ';
	   else
      {
	      if(ShiftKeyEnable)
            AlphaNumChar = AlphaNumKeyPropSmallCase[KeyPressed].CharValue[KeyCount-1];
         else
         AlphaNumChar = AlphaNumKeyProp[KeyPressed].CharValue[KeyCount-1];
      }
       //Storing the char value on array and display it on screen*/
	   OutputLine[MaxDigit] = AlphaNumChar;
	   AlphaBuf[Index] = AlphaNumChar;/*store the value in original buffer*/
	   OutputLine[MaxDigit+1] = FILLCHAR;
	   OutputLine[MaxDigit+2] = NUL;
	 	DrawString(pDC, OutputLine);
	}
	else if(!CChildView::IsTwoSecExpired && PrevPressedAlphaNumKey == KeyPressed)
	{
      
      /*Toggle the key and store the next char of AlphaNumKeyProp*/
	   	if((KeyCount<AlphaNumKeyProp[KeyPressed].NumChar)||(KeyCount<AlphaNumKeyPropSmallCase[KeyPressed].NumChar))
		{
	      
         KeyCount++;/*Count no. of times the same key pressed.*/
	      if(KeyPressed==KEYPAD_DEC)
			 AlphaNumChar=' ';
		   else
         {
	       if(ShiftKeyEnable)
            AlphaNumChar = AlphaNumKeyPropSmallCase[KeyPressed].CharValue[KeyCount-1];
          else
            AlphaNumChar = AlphaNumKeyProp[KeyPressed].CharValue[KeyCount-1];
         }
		 
		  /*Alter the value of array depending on KeyCount*/
         OutputLine[MaxDigit] = AlphaNumChar;
	      AlphaBuf[Index] = AlphaNumChar;
	      OutputLine[MaxDigit+1] = FILLCHAR;
	      OutputLine[MaxDigit+2] = FILLCHAR;
	      OutputLine[MaxDigit+3] = NUL;
	      DrawString(pDC, OutputLine);
		}
	   else/*Make the index of AlphaNumKeyProp to 1 and
        store values with initialized index*/
	   {
	     KeyCount = 1;
		  if(KeyPressed==KEYPAD_DEC)
			 AlphaNumChar=' ';
		  else
        {
		     if(ShiftKeyEnable)
            AlphaNumChar = AlphaNumKeyPropSmallCase[KeyPressed].CharValue[KeyCount-1];
           else
            AlphaNumChar = AlphaNumKeyProp[KeyPressed].CharValue[KeyCount-1];
        }
          /*Alter the value of array depending on KeyCount*/
	      OutputLine[MaxDigit] = AlphaNumChar;
	      AlphaBuf[Index] = AlphaNumChar;
	      OutputLine[MaxDigit+1] =FILLCHAR;
	      OutputLine[MaxDigit+2] = NUL;
       	DrawString(pDC, OutputLine);
	   }
	}/*end of else if*/
	CChildView::InitialiseTimer(AlphaEntryTimer,2000);
	DrawString(pDC, OutputLine);
	PrevPressedAlphaNumKey =KeyPressed;
    /*Store the currently pressed key */
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function is processing the valid key pressed on the keypad screen.*/
/*  For any alpha key it will call the QVGAAlphaEntryMode, for Enter key   */
/*  will enter the name if it is not null.On pressing ESC it will erase    */
/*  the last entered character.                                            */
/***************************************************************************/
bool CScreenKeypad::ProcessPressedAlphakey(int KeyPressed, int type,CChildView *view,CDC *pDC)
{
   bool Exit = FALSE;/*Return TRUE on pressing ENT or ESC at first time.*/
   switch(KeyPressed)
    {
	    case KEYPAD_0:
		case KEYPAD_1:
		case KEYPAD_2:
		case KEYPAD_3:
		case KEYPAD_4:
		case KEYPAD_5:
		case KEYPAD_6:
		case KEYPAD_7:
		case KEYPAD_8:
		case KEYPAD_9:
           if((type == CVgaMenu::ALPHA)/*||(type == CVgaMenuItem::VGA_PRESETSAVEASSIGN)*/
			   ||(type == VGA_PASSWORD)||(type==SaveScanA)||(type == SaveScanB )||( type==SaveScanC))//_ALPHA
           {
	           //printf("\n MaxDigit=%d",MaxDigit);
              if(MaxDigit < AlphaInfo.MaxLength ||
				  (MaxDigit <= AlphaInfo.MaxLength && !CChildView::IsTwoSecExpired
	                && PrevPressedAlphaNumKey == KeyPressed))
              {
	             
                 /* Make Release Beep */
                 //TouchScrnBeep(6);
                 VGAAlphaEntryMode(KeyPressed,view,pDC);
              }          
              else
              {
                 /* After entering max char it should beep*/
     	         //TouchScrnBeep(10);
                 //ERRORBEEP;
				  CChildView::ErrorBeep();
              }
     	      
           }/*End of type _ALPHA  */
           else if(type == CVgaMenu::HHMM)
			 VGATimeEntry(KeyPressed,pDC);           
           else if(type == CVgaMenu::DATE)//_DATE
			 VGADateEntry(KeyPressed,pDC);
	      
	    break;
        case KEYPAD_DEC:
			/*if((type == CScreenObject::ALPHA)||(type == CScreenObject::VGA_PRESETSAVEASSIGN)
			   ||(type==SaveScanA)||(type == SaveScanB )||( type==SaveScanC))//_ALPHA
           {
	          if(MaxDigit < AlphaInfo.MaxLength ||
				  (MaxDigit <= AlphaInfo.MaxLength && !CChildView::IsTwoSecExpired
	                && PrevPressedAlphaNumKey == KeyPressed))
              {
	             
                 // Make Release Beep 
                 //TouchScrnBeep(6);
                 VGAAlphaEntryMode(KeyPressed,view,pDC);
              }          
              else
              {
                 // After entering max char it should beep
     	         //TouchScrnBeep(10);
                 //ERRORBEEP;
				  CChildView::ErrorBeep();
              }
     	      
           }
		  else if((type == VGA_PASSWORD))*/
			  // CChildView::ErrorBeep();
           ShiftKeyEnable=!ShiftKeyEnable;
           view->Invalidate();
		  break;
        case KEYPAD_INC:  /* Move cursor right by one position */
        
           if(/*(type == CVgaMenuItem::VGA_PRESETSAVEASSIGN )||*/ (type == CVgaMenu::ALPHA)
			   ||(type == VGA_PASSWORD)||(type==SaveScanA)||(type == SaveScanB )|| (type==SaveScanC))//_ALPHA
           {
              if( MaxDigit < AlphaInfo.MaxLength && !CChildView::IsTwoSecExpired) 
				  //&&  PrevPressedAlphaNumKey != KEYPAD_NONE)
              {
                 /*Make the prev entered char to * for password entry*/
                  if(AlphaInfo.Hide)
            	     OutputLine[MaxDigit] = '*';
                 
				      CChildView::IsTwoSecExpired=true;
                  CChildView::KillTimers(AlphaEntryTimer);
             
                 /*Display the cursor at next position if cursor is not displayed*/
                 if(MaxDigit == (AlphaInfo.MaxLength - 1))                 
                   OutputLine[MaxDigit + 1] = ' ';
                 else                
		            OutputLine[MaxDigit + 1] = '_';
                 OutputLine[MaxDigit+2] = FILLCHAR;
		           OutputLine[MaxDigit+3] = NUL;
				     DrawString(pDC, OutputLine);	
				   
                 if((CChildView::IsTwoSecExpired && (OutputLine[MaxDigit + 1] == '_')) 
					 ||MaxDigit == (AlphaInfo.MaxLength - 1) 
					 ||(PrevPressedAlphaNumKey == KEYPAD_INC))
                  //  Beep(ERRORBEEP);
                 PrevPressedAlphaNumKey = KeyPressed;
                 
              }
              else if(MaxDigit < AlphaInfo.MaxLength && CChildView::IsTwoSecExpired)
                 
				  //(MaxDigit <= AlphaInfo.MaxLength && !CChildView::IsTwoSecExpired
	           //     && PrevPressedAlphaNumKey == KeyPressed))
              {
	             KeyPressed = KEYPAD_DEC;
                VGAAlphaEntryMode(KeyPressed,view,pDC);
              }  
              else
              {
                 //TouchScrnBeep(10);
				    CChildView::ErrorBeep();
                 //ERRORBEEP;
              }   
			  	//CChildView::InitialiseTimer(AlphaEntryTimer,2000);           
             /*Initialize the timer*/
	       }
           else
           {
              //TouchScrnBeep(10);
              //ERRORBEEP;
			   CChildView::ErrorBeep();
           }
        break;
        
        case KEYPAD_POINT:
           if(/*(type == CVgaMenuItem::VGA_PRESETSAVEASSIGN ||*/(type ==  CVgaMenu::ALPHA
			   ||(type == VGA_PASSWORD)||(type==SaveScanA)||(type == SaveScanB )|| (type==SaveScanC)) && MaxDigit < (AlphaInfo.MaxLength-1))//alpha
           {
             
             /* Make Release Beep */
            // TouchScrnBeep(6);
             if(PrevPressedAlphaNumKey != KEYPAD_NONE )/*Esc if value is entered at
                                              0th index of OutputLine Buffer*/
	         {
	            if(AlphaInfo.Hide && OutputLine[MaxDigit] != '_' && 
                                  OutputLine[MaxDigit] != '*')
                   OutputLine[MaxDigit] = '*';
                Index++;/*Increment the index value*/
	            MaxDigit++;
             }
             OutputLine[MaxDigit] = '.';
	         AlphaBuf[Index] = '.';
	         OutputLine[MaxDigit+1] = FILLCHAR;
	         OutputLine[MaxDigit+2] = FILLCHAR;
	         OutputLine[MaxDigit+3] = NUL;
	         DrawString(pDC, OutputLine);
				PrevPressedAlphaNumKey =  KeyPressed; 
           }
           else
           {
              /* After entering max char it should beep*/
     	     // TouchScrnBeep(10);
            // ERRORBEEP;
			   CChildView::ErrorBeep();
           }
        break;
        
        case KEYPAD_ENT:
			{
            if(CChildView::thisPtr->DisplayLockFlag )/* Display Lock Active ?*/
             {
                CChildView::thisPtr->ErrorBeep();
                CVgaMenu *menu;
                if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
                {
			         CChildView::thisPtr->AccessLevelSystem=OPERATOR;
                  CChildView::thisPtr->menusname.AddTail(theApp.menuName);
                  CChildView::thisPtr->menus.AddTail(page_no);
                  CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
                  page_no=1;
                  CChildView::thisPtr->ModifyObjectList(menu);   
                  theApp.menuName=CVgaBottomMenu::mainMenuID;
                  theApp.MenuPointer=menu;   
                }                
				    CChildView::thisPtr->Invalidate();
                OnKeypadScreen_flag = false;
                Exit = true;
                break;
             }

	      TRACE(_T("\n AlphaBuf IS %s"),AlphaBuf);
		   if((type==SaveScanA)||(type == SaveScanB )|| (type==SaveScanC))
		   {
				CChildView::IsTwoSecExpired=true;
				VGAAlphaEntry(pDC);
				HandleEnterOnSaveScanKeypad(view,pDC);
		   }
		   if(type ==VGA_PASSWORD)
		   {
			    CChildView::IsTwoSecExpired=true;
				VGAAlphaEntry(pDC);
		   		HandleEnterOnPassword(view, pDC);
		   }
		  
		   
         
           if(( /*type == CVgaMenuItem::VGA_PRESETSAVEASSIGN ||*/type ==  CVgaMenu::ALPHA)
			   && AlphaBuf[0] != NUL && OutputLine[0]!='_' )//alpha
	       {
	          /* Make Release Beep */
              //TouchScrnBeep(6);
              AlphaBuf[++Index] = NULL;
	          
			  unsigned char data[26];
			  unsigned char * alpha_data = (unsigned char *) &data[0];
			  union 
	         {
		         short i;
		         char c[2];
	         } u;
	         u.i=ID_type;
            alpha_data[1]=u.c[0];
	         alpha_data[0]=u.c[1];
           // CScreenObject::Convert_Integer_To_Char(pointer, alpha_data);
			  int length_alpha=0;
			  while(AlphaBuf[length_alpha]!='\0')
			  	length_alpha++;
           alpha_data[2]=(char)length_alpha;
			  for(int J=0;J<length_alpha;J++)
					alpha_data[3+J]=AlphaBuf[J];
			  length_alpha =length_alpha+3;
			  Index=-1;
			  CHostCommand * request = new CHostCommand(SetValue_FunID, alpha_data, length_alpha);
			  CHostCommand * response = app->SendUiHostCommand(request);
			  if (response)
			  {		
					char ch=CHostCommand::AckNak();
               alpha_data = response->GetData();
		         length_alpha = response->GetDataLength();
               if(ch==ACK)
					{
					
                  if(type ==CVgaMenu::ALPHA)
						{
							CString output=(CString)AlphaBuf;
							output = "= " + output;
							output.Delete(output.GetLength(),1);
                     
							if(output.GetLength() !=1)
								*Object_Text_pointer=output;
							else
								*Object_Text_pointer=	AlphaInfo.Current_Alpha_Value;
						}
				
						ERRORBEEP;	
						MaxDigit=-1;
						delete response;
						AlphaBuf[0] = NULL;
						OutputLine[0] =NULL;
						if(type ==CVgaMenuItem::ALPHA)
						Exit = TRUE; /* Enter keypressed */ 

					/*	if(AlphaInfo.PARAM_ID ==CVgaMenuItem::PSSERIALNUMBER)
							view->GetPowerSupplyName();*/
                  CVgaMenu * menu;
                  void *ptr;
                  void (*rmn)(int);
                  if(functionCall.Lookup(AlphaInfo.FunName,ptr))
		            {
			            rmn = (void (*)(int))ptr;
                     int Address=(int)this;
                    // printf("\n call function of variable");
			            rmn(Address);
                  }
                  if(AlphaInfo.MenuAck!="")
                  {
                     if (theApp.menus.Lookup(AlphaInfo.MenuAck, menu))
		               {
			               //view->menusname.AddTail(theApp.menuName);
                        //view->menus.AddTail(page_no);
                        page_no=1;
                        CChildView::thisPtr->ModifyObjectList(menu);
                        theApp.menuName = AlphaInfo.MenuAck;
                        theApp.MenuPointer=menu;
		               }		
	               }
                  CChildView::thisPtr->Invalidate();
					}
               else
               {
                  CChildView::thisPtr->ProcessNak(alpha_data,length_alpha,pointer,0);
               }
				}
			  /* if(type ==CScreenObject::VGA_PRESETSAVEASSIGN)
			   {
				   POSITION pos = view->menuEntryList.GetHeadPosition();
				   while(pos)
				   {
					   CScreenObject *Object = view->menuEntryList.GetNext(pos);
					   if(Object->GetType()==CScreenObject::VGA_PRESETSAVEASSIGN)
					   {
						   CVGAButtons *obj = (CVGAButtons*)Object;
						   obj->SendCommandForVGAButtons(PresetScrButton_FunId,view);
                     view->SaveVQSData();
						   break;
					   }
				   }
				   Exit = TRUE;
			   }*/
             
	      }
         
           if(type == CVgaMenu::HHMM && OutputLine[0] != '_' && OutputLine[0] !='H')//TIME
           /*Validate the entered value & store if valid*/
              UpdateTimeIfValid(pDC);
           
           if(type == CVgaMenu::DATE && OutputLine[0] != '_'
			   && OutputLine[0] != 'D' && OutputLine[0] != 'M')//_DATE
           /*Validate the entered value & store if valid*/
              UpdateDateIfValid(pDC);
           if(ErrorDisplayed)
              Exit = FALSE;
           else
              Exit = TRUE; /* Enter key]pressed */
        }
        break;

        case KEYPAD_ESC:
            /* Make Release Beep */
          //  TouchScrnBeep(6);
           if(CChildView::thisPtr->DisplayLockFlag )/* Display Lock Active ?*/
             {
              CChildView::thisPtr->ErrorBeep();  
              CVgaMenu *menu;
                if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
                {
			         CChildView::thisPtr->AccessLevelSystem=OPERATOR;
                  CChildView::thisPtr->menusname.AddTail(theApp.menuName);
                  CChildView::thisPtr->menus.AddTail(page_no);
                  CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
                  page_no=1;
                  CChildView::thisPtr->ModifyObjectList(menu);   
                  theApp.menuName=CVgaBottomMenu::mainMenuID;
                  theApp.MenuPointer=menu;   
                }                
				    CChildView::thisPtr->Invalidate();
                OnKeypadScreen_flag = false;
                Exit = true;
                break;
             }
            /* If ESC key is pressed before any value is entered 
            then keypad pop up should exit */
            if((type ==  CVgaMenu::ALPHA)/*||(type == CVgaMenuItem::VGA_PRESETSAVEASSIGN)*/
				||(type == VGA_PASSWORD)||(type==SaveScanA)||(type == SaveScanB )|| (type==SaveScanC))//_ALPHA//_ALPHA
            {
                if( (AlphaBuf[0] == NUL)||(AlphaBuf[0] =='_')
					||(OutputLine[0] == NUL)||(OutputLine[0] =='_'))
				{
					AlphaBuf[0] = NULL;
					OutputLine[0] ='_';
					FirstKeyPress = KEY_NONE;
					Exit = TRUE;
				   if((type ==VGA_PASSWORD)&&(pointer !=1)&&(pointer !=0))
               {
                  theApp.menuName=view->menusname.RemoveTail();
                  page_no=view->menus.RemoveTail();
                  theApp.MenuPointer=view->menupointers.RemoveTail();
               }
					//view->PopMenu(true);
              // CVgaMenu * menu1;
                //page_no=1;
               //page_no=view->menus.RemoveTail();
		         // if (theApp.menus.Lookup(theApp.menuName, menu1))
                {
			         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			         
                }
				}
                else
                {
                   KeyCount = 1;
                   PrevPressedAlphaNumKey = KEYPAD_ESC;
                   OutputLine[MaxDigit] = '_';
                   /* Display the cursor on prev position and decrement
                      the index value*/
                   OutputLine[MaxDigit+1] = FILLCHAR;
                   OutputLine[MaxDigit+2] = FILLCHAR;
                   OutputLine[MaxDigit+3] = NUL;
                   if(MaxDigit) MaxDigit--;
                   /*Not increment the index if 1st column is empty*/
                   if(OutputLine[0] == '_')
                   PrevPressedAlphaNumKey = KEYPAD_NONE;
                  
                   AlphaBuf[Index] = NUL;
                   if(Index) 
					   Index--;
                 	DrawString(pDC, OutputLine);
				 }
            }
            else if(type == CVgaMenu::HHMM )//_HHMM
            {
               if( OutputLine[0] == '_'|| OutputLine[0] == 'H')
                   Exit = TRUE;
               else
               { 
                  /* Display the cursor on prev position and decrement
                      the index value*/
                  if(MaxDigit == 3) MaxDigit--;
                  OutputLine[--MaxDigit] = '_';
                  OutputLine[MaxDigit+1] = ' ';
                  OutputLine[MaxDigit+2] = ' ';
                  OutputLine[2] = ':';
                  OutputLine[5] = NULL;
                  DrawString(pDC, OutputLine);
               }
            }
            else if(type ==CVgaMenu::DATE )//_DATE
            {
               if( OutputLine[0] == '_'|| OutputLine[0] == 'M'|| OutputLine[0] == 'D')
                   Exit = TRUE;
               else
               { 
                  /* Display the cursor on prev position and decrement */
                  /* the index value*/
                  if(MaxDigit == 3 || MaxDigit == 6) MaxDigit--;
                  OutputLine[--MaxDigit] = '_';
                  OutputLine[MaxDigit+1] = ' ';
                  OutputLine[MaxDigit+2] = ' ';
                  OutputLine[2] = '/';
                  OutputLine[5] = '/';
                  OutputLine[8] = NULL;
                  DrawString(pDC, OutputLine);
			   }
            }
        break;
        
        default:
           /* Touched the Invalid Key */
          // if(!PRESSES)
           {                    
              //TouchScrnBeep(10);
             // ERRORBEEP;
			   CChildView::ErrorBeep();
           }
	    break;
    }/*end of switch case  */ 
   return(Exit);			            
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function sends the host command to update date , if the all the   */
/*   variables are entered and value entered for every variable is valid.  */                                             
/***************************************************************************/
void CScreenKeypad::UpdateDateIfValid(CDC *pDC)
{
int Day, Month, Year;
    if (VarInfo.Metric == FALSE)
    {
       //Convert the variables from string to integer type.
       Month = myatoi(&OutputLine[0]);
       Day =  myatoi(&OutputLine[3]);
       Year = myatoi(&OutputLine[6]);
    }   
    else
    {
       /*Convert the variables from string to integer type.*/
       Day = myatoi(&OutputLine[0]);
       Month =  myatoi(&OutputLine[3]);
       Year = myatoi(&OutputLine[6]);
    }
    if(CheckForValidDate(OutputLine, Day, Month, Year))
    /*Check if all the variables are entered with valid value.*/
    {
		int length = DATE_LENGTH;
		unsigned char data[DATE_LENGTH];
		unsigned char * date_data = (unsigned char *) &data[0];
		union 
	   {
		   short i;
		   char c[2];
	   } u;
	   u.i=ID_type;
      date_data[1]=u.c[0];
	   date_data[0]=u.c[1];
      date_data[2]=(char)3;
      date_data[3]=(char)Month;TRACE(_T("\n %d") ,date_data[3]);
		date_data[4]=(char)Day;TRACE(_T("\n %d") ,date_data[4]);
		date_data[5]=(char)Year;TRACE(_T("\n %d") ,date_data[5]);
		TRACE(_T("\n %d") ,date_data[6]);

		CHostCommand * request = new CHostCommand(SetValue_FunID, date_data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			char ch=CHostCommand::AckNak();
			if(ch=ACK)
			{
				CString outputdate=(CString)OutputLine;
				outputdate="> "+outputdate;
				*Object_Text_pointer=outputdate;
				/*updating the date to system date*/
					SYSTEMTIME xyz;
					GetLocalTime(&xyz);
					xyz.wYear=Year+2000;
					xyz.wMonth=Month;
					xyz.wDay=Day;
					SetLocalTime(&xyz);
               int ID=CVgaMenuItem::Convert_Char_To_Integer(date_data,length,2);
               
			}
			ERRORBEEP;
			//	Exit = TRUE;
			delete response;	
		}
		ErrorDisplayed = false;
		OutputLine[0] ='_';
	OutputLine[1] ='\0';
	MaxDigit=0;
	EntryFlag = true;
	}
	else
    {
		 CDate *ptrDate=(CDate *)pointer;
       /*Display the error screen and initialize the variables and */
       /*Refresh the screen.                                       */
     	 CVgaMenuItem::DrawRect(pDC,Blue, New_Value_String_Rect);

       CString TempReenterText = ptrDate->Str_Reenter;
       if(CChildView::thisPtr->StringDebugFlag)
         TempReenterText = ptrDate->Str_ReenterID + _T(" ")+ ptrDate->Str_Reenter;

		CVgaMenuItem::DrawText(pDC, SmallFont, White, 
			New_Value_String_Rect, TempReenterText/*Str_Reenter[CChildView::Language_Index]*/,false);

      	CVgaMenuItem::DrawRect(pDC, Red, Error_rect);
      
         CString TempInvalidText = ptrDate->StrInvalidEntry;
       if(CChildView::thisPtr->StringDebugFlag)
         TempInvalidText = ptrDate->StrInvalidEntryID + _T(" ")+ ptrDate->StrInvalidEntry;

		CVgaMenuItem::DrawText(pDC, SmallFont, White, 
			Error_Str_rect, TempInvalidText/*StrInvalidEntry[CChildView::Language_Index]*/,true);

	    ErrorDisplayed = true;
       //TouchScrnBeep(10);
       //ERRORBEEP;  
		CChildView::ErrorBeep();
       PrevPressedAlphaNumKey = KEYPAD_NONE;
       Index = 0;
       MaxDigit = 0;
       KeyCount = 1;
       EntryFlag = false;
	   OutputLine[MaxDigit] = '_';
       OutputLine[MaxDigit+1] = FILLCHAR;
	    if (VarInfo.Metric== false)
          DrawString (pDC, "MM/DD/YY"); 
       else
          DrawString (pDC, "DD/MM/YY");
	   }
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function is stored to send the host comand ,if the all the        */
/*  variables are entered and value entered for    */
/*  every variable is valid.                                               */
/***************************************************************************/
void CScreenKeypad::UpdateTimeIfValid(CDC *pDC)
{

    bool Valid = true;
    bool EmptyColumn = false;
    int i;
    int  Hour, Min;
    /*Convert the variables fron string to integer type.*/
    Hour= myatoi(&OutputLine[0]);
    Min=  myatoi(&OutputLine[3]);
    for(i = 0; i < MAXTIMECHAR; i++)
    /*Check if any value is not entered.*/
    {
       if(OutputLine[i] == '_')
       {
          Valid = false;
          EmptyColumn = true;
          break;
       }
    }
    if ( EmptyColumn || Min < MinLimit_Minute || Min > MaxLimit_Minute || 
         Hour < MinLimit_Hour || Hour > MaxLimit_Hour)
         /*Check for the valid entry of all variables.*/ 
       Valid = false;
    if (Valid)
    {
		int length =IntegerLength+1;
		unsigned char data[IntegerLength+1];
		unsigned char * date_data = (unsigned char *) &data[0];
	//	CScreenObject::Convert_Integer_To_Char(pointer, date_data);
		union 
	   {
		   short i;
		   char c[2];
	   } u;
	   u.i=ID_type;
      date_data[1]=u.c[0];
	   date_data[0]=u.c[1];
      date_data[2]=(char)2;
      date_data[3]=(char)Hour;TRACE(_T("\n %d") ,date_data[4]);
		date_data[4]=(char)Min;TRACE(_T("\n %d") ,date_data[5]);
      
		CHostCommand * request = new CHostCommand(SetValue_FunID, date_data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{		
			char ch=CHostCommand::AckNak();
			if(ch=ACK)
			{
				length = response->GetDataLength();//Getting Length.
		      date_data = response->GetData();//Getting Data
            CString outputtime=(CString)OutputLine;
				outputtime="> "+outputtime;
				*Object_Text_pointer=outputtime;

				/*updating the Time to system date*/
				SYSTEMTIME xyz;
				GetLocalTime(&xyz);
				xyz.wHour=Hour;
				xyz.wMinute=Min;
				SetLocalTime(&xyz);
            int ID=CVgaMenuItem::Convert_Char_To_Integer(date_data,length,2);
        	}
			ERRORBEEP;
			delete response;	
		} 
		ErrorDisplayed = false;
	   /* Make Release Beep */
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		MaxDigit=0;
       EntryFlag = true;
    }
    else
    { 
       CVgaTime *PtrTime=(CVgaTime *)pointer;
		/*Display the error screen,initialize the variables and */
       /*Refresh the screen.                                   */
       CVgaMenuItem::DrawRect(pDC, Blue, New_Value_String_Rect);
         
       CString TempReenterText = PtrTime->Str_Reenter;
       if(CChildView::thisPtr->StringDebugFlag)
         TempReenterText = PtrTime->Str_ReenterID + _T(" ")+ PtrTime->Str_Reenter;

		 CVgaMenuItem::DrawText(pDC,SmallFont, White, 
					New_Value_String_Rect, TempReenterText/*Str_Reenter[CChildView::Language_Index]*/,false);
      // DrawString(&ErrorStrProp, StrInvalidEntry[LangIndex]);
			CVgaMenuItem::DrawRect(pDC, Red, Error_rect);

      CString TempInvalidText = PtrTime->StrInvalidEntry;
       if(CChildView::thisPtr->StringDebugFlag)
         TempInvalidText = PtrTime->StrInvalidEntryID + _T(" ")+ PtrTime->StrInvalidEntry;

		CVgaMenuItem::DrawText(pDC, SmallFont, White, Error_Str_rect, 
							TempInvalidText/*StrInvalidEntry[CChildView::Language_Index]*/,true);
       ErrorDisplayed = true;
       //TouchScrnBeep(10);
      // ERRORBEEP;  
	   CChildView::ErrorBeep();
       PrevPressedAlphaNumKey = KEYPAD_NONE;
       Index = 0;
       MaxDigit = 0;
       KeyCount = 1;
       EntryFlag = false;
       AlphaBuf[Index] = NUL;
       OutputLine[MaxDigit] = '_';
       OutputLine[MaxDigit+1] = FILLCHAR;
	   DrawString (pDC, "HH:MM");
	}
 
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function is processing the key pressed on the keypad screen for   */
/*  time entry.On pressing the key the respective char value is stored to  */
/*  the string for the specified var and the cursur will move to the next  */
/*  column.                                                                */
/*Arg1:Which Alpha key is pressed on the keypad screen.                    */
/***************************************************************************/
void CScreenKeypad::VGATimeEntry(int KeyPressed,CDC *pDC)
{
   char AlphaNumChar;
   UINT8    i;  
   if(MaxDigit < MAXTIMECHAR)/*Value of Hour & minute is not entered*/
   {
      /* Make Release Beep */
      //TouchScrnBeep(6);
      for(i = MaxDigit; i < MAXDATECHAR; i++)
         OutputLine[i] = FILLCHAR; 
      if(ShiftKeyEnable)
         AlphaNumChar = AlphaNumKeyPropSmallCase[KeyPressed].CharValue[KeyCount-1];
      else
         AlphaNumChar = AlphaNumKeyProp[KeyPressed].CharValue[0];
      /*Storing the char value on array and display it on screen*/
	  OutputLine[MaxDigit] = AlphaNumChar;
      OutputLine[DAYCHAR] = ':';      
      MaxDigit++;
      if( MaxDigit == DAYCHAR )   MaxDigit++;
      OutputLine[MaxDigit] = '_';/*Display the cursor to the next column*/
      OutputLine[MAXTIMECHAR] = NUL;
      DrawString(pDC, OutputLine);
   }
   else
   { 
    //  TouchScrnBeep(10);
      //ERRORBEEP;
	   CChildView::ErrorBeep();
   }  
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function is processing the key pressed on the keypad screen for   */
/*  date entry.On pressing the key the respective char value is stored to  */
/*  the string for the specified var and the cursur will move to the next  */
/*  column.                                                                */
/*Arg1:Which Alpha key is pressed on the keypad screen.                    */
/***************************************************************************/
void CScreenKeypad::VGADateEntry(int KeyPressed,CDC *pDC)
{
   char AlphaNumChar; 
   UINT8    i;
   if(MaxDigit < MAXDATECHAR)/*If value of Day,month & Year is not entered.*/
   {
      /* Make Release Beep */
     // TouchScrnBeep(6);
      for(i = MaxDigit; i < MAXDATECHAR; i++)
         OutputLine[i] = FILLCHAR; 
      if(ShiftKeyEnable)
          AlphaNumChar = AlphaNumKeyPropSmallCase[KeyPressed].CharValue[KeyCount-1];
      else
         AlphaNumChar = AlphaNumKeyProp[KeyPressed].CharValue[0] ;
      OutputLine[MaxDigit] = AlphaNumChar;
      MaxDigit++;
      OutputLine[DAYCHAR] = '/';/*store the break char b/w the variables.*/
      OutputLine[MAXTIMECHAR] = '/';
      if( MaxDigit == DAYCHAR || MaxDigit == MAXTIMECHAR )   MaxDigit++;      
      OutputLine[MaxDigit] = '_';
      OutputLine[MAXDATECHAR] = NULL;
		DrawString(pDC, OutputLine);
   }
   else
   { 
      //TouchScrnBeep(10);
     // ERRORBEEP;
	   CChildView::ErrorBeep();
   }
}

int CScreenKeypad::myatoi(char s[])
{
   int i,n;
   i = 0;
   for(n=0;s[i] >= '0' && s[i] <= '9'; i++)
      n = 10 * n + s[i] - '0';
   return n;

}

/***************************************************************************/
/*Description:-                                                            */
/*  This function will check that the value entered for the date variables */
/*  is valid or not.This will also take care of the date for the leap year.*/
/*Arg1:Pointer to the output line                                          */
/*Arg2:Entered value of date.                                              */
/*Arg3:Entered value of the Month.                                         */
/*Arg4:Entered value of the year.                                          */
/*Return:                                                                  */
/*  Return TRUE if all the entered variables are valid.                    */
/***************************************************************************/
bool CScreenKeypad::CheckForValidDate(char *OutputLine, int Day, int Month, int Year)
{
	bool Valid =true;
    bool EmptyColumn = false;
    UINT8 i;
	/*Store the max. days for particular months.*/
    UINT16 MonthLength[12]={ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        
    for( i = 0; i < MAXDATECHAR; i++)
    /*Check if any value is not entered.*/
    {
       if(OutputLine[i] == '_')//coz _ 'll dos't appear on screen of date is completly entered 
       {
          Valid = false;
          EmptyColumn = true;
          break;
       }
    }
    if(!EmptyColumn)
    {
       if ( CheckForLeapYear(Year) )
          MonthLength[1] = LEAPYEARVALUE;//if leap year then make if 29
       /*Check for the valid entry of all variables.*/ 
       if ( Month < MinLimit_Month || Month > MaxLimit_Month )
          Valid = false;
       else if ( Day < MinLimit_Day || Day > MonthLength[Month-1] )
          Valid =false;
    }
    return ( Valid );
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function will check whether the entered value of the year is      */
/*  a leap year or not.                                                    */
/*Return:                                                                  */
/*  Return TRUE if the year is a leap year.                                */
/***************************************************************************/
bool CScreenKeypad::CheckForLeapYear(int Year)
{
	bool  Result;
    Year += CENTURY;
    
    if ( (Year%4) )         
       Result = false;      
    else if ( !(Year%400) ) 
       Result = true;       
    else if ( !(Year%100) ) 
       Result = false;      
    else                    
       Result = true;       
    
    return ( Result );
}

/***************************************************************************/
/*Descriptions:                                                            */
/*  This function handles entry of an alphanumeric data item.  The Alpha   */
/*  Num keys on the keypad enter the values in NewVlaueEntry Box if Enter  */
/*  is pressed validate the data & change into the return string value.    */
/*  For Date & Time only Numeric Values will be allowed.                   */
/*                                                                         */
/* Parameters:                                                             */
/* *pDC  - pointer to the device context                                   */                                       
/***************************************************************************/
void CScreenKeypad::VGAAlphaEntry(CDC *pDC)
{

	if(  PrevPressedAlphaNumKey != KEYPAD_NONE &&
       OutputLine[MaxDigit+1] != '_' && CChildView::IsTwoSecExpired)// &&
         //  !ExitFlag)        
	    {
	        /*Make the prev entered char to * for password entry*/
            if(AlphaInfo.Hide==true)
            	OutputLine[MaxDigit] = '*';
            /*Display the cursor at next position if cursor is not displayed*/                
		    if(MaxDigit < (AlphaInfo.MaxLength - 1))
		          OutputLine[MaxDigit + 1] = '_';
            if(MaxDigit == (AlphaInfo.MaxLength - 1))/*Don't display the cursor after*/
               OutputLine[MaxDigit+1] = FILLCHAR;   /*entering max char.      */
            OutputLine[MaxDigit+2] = FILLCHAR;
		    OutputLine[MaxDigit+3] = NUL;
          	DrawString(pDC, OutputLine);
		}
}


/***************************************************************************/
/* The function handles digit entry done through keypad screen. Also if the*/
/* value entered is correct, a host command is send so that the preset is  */
/* updated with the new value. If the value entered is above or below      */
/* permissible limts an error message box is displayed                     */                  
/*                                                                         */  
/*  Parameters:                                                            */
/*    KeyPressed - Points to the keypressed on Keypad                      */
/*    *pDC  - Device context object                                        */
/*  Note: Due to strange behavior of ENERGY format, it's possible for      */
/*  format type to change while inside this function.                      */
/*                                                                         */
/***************************************************************************/
bool CScreenKeypad::VGAVarEntryMode(int KeyPressed,CDC *pDC,CChildView *view)
{
  // STRING_PROPERTY StrProp;
   enum ERRORCODES MinMaxNoVal;
   SINT16    x;	
   bool Exit = FALSE;
  int flag;
           
   switch(KeyPressed)
   {
      /* Tests for validity of Inc/Dec: Don't allow Inc/Dec if */
      /* ClearKey pressed (NewVal == -1).  Don't allow Inc if */
      /* at max unless sign is -1, in which case NewVal is */
      /* really at min, so Inc is okay.  Don't allow Dec if at */
      /* min if sign is 0.  If sign is +-1, then allowed range */
      /* of values is -max <= NewVal <= max, so Dec is okay */
      /* unless sign is -1 and NewVal is at max. */
      case KEYPAD_INC:
      case KEYPAD_DEC:
         if (FirstKeyPress == KEY_INC_DEC || FirstKeyPress == KEY_NONE)  	
		{
            
			if (VarInfo.Disable) /* Make sure item enabled */
			 VarInfo.Disableflag &= ~(VarInfo.Bitmask);
           
//			printf("\n VarInfo.Disableflag in INC/DEC=%d",VarInfo.Disableflag);
         if ((VarInfo.NewVal == -1) || 
				 ((KeyPressed == KEYPAD_INC) && 
                 (VarInfo.NewVal == VarInfo.MaxVal) && 
				 (VarInfo.Sign!=-1))||
                 //(VarInfo.->Sign != -1)) ||
                 ((KeyPressed == KEYPAD_DEC) && 
                 (VarInfo.NewVal == VarInfo.MinVal) && 
                 (!VarInfo.Sign)) ||
                 ((KeyPressed == KEYPAD_DEC) && 
                 (VarInfo.NewVal == VarInfo.MaxVal) && 
                 (VarInfo.Sign==-1)))
            {             
              // TouchScrnBeep(10);
              // ERRORBEEP;
				 CChildView::ErrorBeep();
            }
            else
            {
               if(ErrorDisplayed)
               {
                 strnset(EditLine, FILLCHAR, LINESIZE);/* Clear out working buffer */
                 EditLine[0] = '_';
                 EditLine[LINESIZE] = 0;
               	 CVgaMenuItem::DrawRect(pDC, Blue, Error_rect);
	             DisplayVGAMinMax(pDC);
				 DrawString(pDC, EditLine);
                 ErrorDisplayed = FALSE;
               }
               /* Call to the Key Increment/Decrement function */
               
               /* Make Release Beep */
              // TouchScrnBeep(6);
               FirstKeyPress = KEY_INC_DEC;
               VGAVarEntryIncDecMode( KeyPressed,pDC);
            }
         } 
         else
         {
            //TouchScrnBeep(10);
            ERRORBEEP;
         }		                              
         break;
             
      case KEYPAD_OFF:
         if((VarInfo.Disable == 1)&&(VarInfo.ID!=1) /*&&(VarInfo.ID !=CVgaMenuItem::XXCANTCHANGEXX)*/)
         {
             /* Make Release Beep */
             //TouchScrnBeep(6);
			 if(ErrorDisplayed)
            {
               strnset(EditLine, FILLCHAR, LINESIZE);/* Clear out working buffer */
               EditLine[0] = '_';
               EditLine[LINESIZE] = 0;
               CVgaMenuItem::DrawRect(pDC,Blue, Error_rect);
               DisplayVGAMinMax(pDC);
			   DrawString(pDC, EditLine);
               ErrorDisplayed = FALSE;
            }
            KeyOffFlag=true;
             FirstKeyPress = KEY_OFF;
             VarInfo.Disableflag |= VarInfo.Bitmask;
//             printf("\n off key pressed");
//             printf("\n VarInfo.Disableflag=%d",VarInfo.Disableflag);
             CVgaMenuItem::DrawRect(pDC, White,  New_Value_Rect);
             CVgaMenuItem::DrawText(pDC, SmallFont,Black,New_Value_Rect, Str_Off +"                 "/*"OFF                 "*/,false);
         }
         else
         {
            //TouchScrnBeep(10);
            //ERRORBEEP;
			  CChildView::ErrorBeep();
         }
	     break;
         
      case KEYPAD_ESC:
         /* Make Release Beep */
         //TouchScrnBeep(6);
        if(CChildView::thisPtr->DisplayLockFlag )/* Display Lock Active ?*/
          {
            CChildView::thisPtr->ErrorBeep();  
            CVgaMenu *menu;
             if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
             {
			      CChildView::thisPtr->AccessLevelSystem=OPERATOR;
               CChildView::thisPtr->menusname.AddTail(theApp.menuName);
               CChildView::thisPtr->menus.AddTail(page_no);
               CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
               page_no=1;
               CChildView::thisPtr->ModifyObjectList(menu);   
               theApp.menuName=CVgaBottomMenu::mainMenuID;
               theApp.MenuPointer=menu;   
             }                
				 CChildView::thisPtr->Invalidate();
             OnKeypadScreen_flag = false;
             Exit = true;
             break;
          }
         /*If ESC key is pressed before any value is entered then keypad
         pop up should exit*/
		  if(ErrorDisplayed)
            {
               strnset(EditLine, FILLCHAR, LINESIZE);//Clear out working buffer 
               EditLine[0] = '_';
			   EditLine[1] = '\0';
               EditLine[LINESIZE] = 0;
               CVgaMenuItem::DrawRect(pDC,Blue, Error_rect);
               DisplayVGAMinMax(pDC);
			   DrawString(pDC, EditLine);
               ErrorDisplayed = FALSE;
			   FirstKeyPress = KEY_NONE;
			   VarInfo.Value = -1;
            }
         else if(FirstKeyPress == KEY_NONE)
         {
			 Exit = TRUE;
			 //view->PopMenu(true);
        //  theApp.menuName=view->menusname.RemoveTail();
         // CVgaMenu * menu1;
          //page_no=1;
		   // if (theApp.menus.Lookup(theApp.menuName, menu1))
          {
			   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			   
          }
         }
         else
         {
            VarInfo.Value = -1;  /* Reserved to mean "illegal value" */
            strnset(EditLine, FILLCHAR, LINESIZE);/* Clear out working buffer*/
            EditLine[LINESIZE] = 0;
            KeyOffFlag=false;
            /* Initialize all digit entry variables */
            TypedVal = 0;
            DPFlag = FALSE;
            DecimalCount = 0;
            DigitCounter = 0;
            TotalDigits = 0;
            MaxDigitFlag = FALSE;
            FirstKeyPress = KEY_NONE;
			DrawString(pDC, "_");
         }
         break;

      case KEYPAD_0:
      case KEYPAD_1:
      case KEYPAD_2:
      case KEYPAD_3:
      case KEYPAD_4:
      case KEYPAD_5:
      case KEYPAD_6:
      case KEYPAD_7:
      case KEYPAD_8:
      case KEYPAD_9:
      case KEYPAD_POINT:
		  TRACE(_T("\n TOTAL DIGITS IS %d"),TotalDigits);
         if (FirstKeyPress == KEY_NUMBER || FirstKeyPress == KEY_NONE) 
         {
            FirstKeyPress = KEY_NUMBER;
            
            if (VarInfo.Disable) /* Make sure item enabled */
               VarInfo.Disableflag &= ~(VarInfo.Bitmask);
            
//            printf("\n VarInfo.Disableflag in num key is pressed=%d",VarInfo.Disableflag);
            if(ErrorDisplayed)
            {
               strnset(EditLine, FILLCHAR, LINESIZE);/* Clear out working buffer */
               EditLine[0] = '_';
               EditLine[LINESIZE] = 0;
               CVgaMenuItem::DrawRect(pDC,Blue, Error_rect);
               DisplayVGAMinMax(pDC);
			   DrawString(pDC, EditLine);
               ErrorDisplayed = FALSE;
            }
            
            if (TotalDigits == 0) /* If first digit entered */
            {
               if (VarInfo.Sign)
               {
                  if (VarInfo.Sign == 1)
                  {
                     TotalDigits++;
                     EditLine[0] = '+';
                  } 
                  else EditLine[0] = '-';
               }
              VarInfo.Value = 0;
               /* Since entry value currently zero, drop to ENERGY if 
                  ENERGYDIV10 */
				if (VarInfo.Format == ENERGYDIV10)
                  ConvertVariableFormat( ENERGYDIV10, ENERGY);
            }   
            if (KeyPressed != KEYPAD_POINT) /* Digits key pressed */
            {
               /* Here's that ENERGY special case again.  Go to ENERGYDIV10 */
               /* when user tries to enter too many digits to the left of */
               /* the decimal point. */
               if (VarInfo.Format == ENERGY && MaxDigitFlag && !DPFlag)
               {
                  ConvertVariableFormat( ENERGY, ENERGYDIV10);
                  MaxDigitFlag = FALSE;
               }
               if (!MaxDigitFlag) /* Check for Max digit entry allowed */
               {
                  /* Make Release Beep */
                  //TouchScrnBeep(6);
                  
                  EditLine[TotalDigits++]  = '0' + KeyPressed;
                  EditLine[TotalDigits] = '_';
                  EditLine[TotalDigits+1] = 0;                  
                  DrawString(pDC, EditLine);
				   TypedVal = (10 * TypedVal) + (KeyPressed - KEYPAD_0);
                  DigitCounter++;
                  /* Next compute NewVal, as we would try to store it at */
                  /* this moment, from TypedVal, DPFlag, and DecimalCount. */
                  VarInfo.NewVal = TypedVal;
                  if (DPFlag) /* Are values entered after decimal point*/
                  {
                     DecimalCount++;   /* # of digits after decimal point */
                    
                    /*
                     if (VarInfo.Format == POWERWATTS && !CChildView::PeakPowerMicrons)
					{
 						for(x=DecimalCount;
 							x<(VarFormatTableAmpPower[POWER].Percent.RightDigits);
 							x++)
                         VarInfo.NewVal *= 10;
 						if(DigitCounter >= VarFormatTableAmpPower[POWER].Percent.RightDigits)
                         MaxDigitFlag = TRUE; // Max Number of digits entered
					}
                    else
                    */ 
                    
                    if(VarInfo.Metric)
					{

						for(x=DecimalCount;
							x<(VarFormatTable[VarInfo.Format].Metric.RightDigits);
							x++)
                        VarInfo.NewVal *= 10;
						if(DigitCounter >= VarFormatTable[VarInfo.Format].Metric.RightDigits)
                        MaxDigitFlag = TRUE; /* Max Number of digits entered */
					}
					else if(!VarInfo.Metric)
					{
						for(x=DecimalCount;
							x<(VarFormatTable[VarInfo.Format].English.RightDigits);
							x++)
                        VarInfo.NewVal *= 10;
						if(DigitCounter >= VarFormatTable[VarInfo.Format].English.RightDigits)
                        MaxDigitFlag = TRUE; /* Max Number of digits entered */
					}
				 }
              else
               {	
                  /*
                  if (VarInfo.Format == POWERWATTS && !CChildView::PeakPowerMicrons)
					{
						for(x=DecimalCount;
							x<(VarFormatTableAmpPower[POWER].Percent.RightDigits);
							x++)
                      VarInfo.NewVal *= 10;
						if(DigitCounter >= VarFormatTableAmpPower[POWER].Percent.LeftDigits)
                      MaxDigitFlag = TRUE; // Max Number of digits entered 
					}
                  else 
                  */
                  
                  if(VarInfo.Metric)
					{
                     for (x=0; x<VarFormatTable[VarInfo.Format].Metric.RightDigits; x++)
                        VarInfo.NewVal *= 10;
                     if(DigitCounter >= VarFormatTable[VarInfo.Format].Metric.LeftDigits)
                        MaxDigitFlag = TRUE; /* Max Number of digits entered */
					}
				  else if(!VarInfo.Metric)
                  {
                     for (x=0; x<VarFormatTable[VarInfo.Format].English.RightDigits; x++)
                        VarInfo.NewVal *= 10;
                     if(DigitCounter >= VarFormatTable[VarInfo.Format].English.LeftDigits)
                        MaxDigitFlag = TRUE; /* Max Number of digits entered */
                  }
			   }
			   }
               }
              
            else /* Point key pressed */
            {
			 
			 /*
			 if (VarInfo.Format == POWERWATTS && !DPFlag &&
						((!CChildView::PeakPowerMicrons && VarFormatTableAmpPower[POWER].Percent.RightDigits )))
			 {

                 DPFlag = TRUE;
                 if((VarInfo.Sign && (TotalDigits == 1))||
                    (TotalDigits == 0))
                    EditLine[TotalDigits++] = '0';
                 EditLine[TotalDigits++] = '.';
                 EditLine[TotalDigits] = '_';
                 EditLine[TotalDigits+1] = 0;
                 DrawString(pDC, EditLine);
				  MaxDigitFlag = FALSE;
                 DigitCounter = 0;
			 }
			 else
			 */	
			 
			 if(!VarInfo.Metric)
			 {
               if (VarFormatTable[VarInfo.Format].English.RightDigits && !DPFlag)
               {
                  /* Make Release Beep */
                 // TouchScrnBeep(6);
                  
                  DPFlag = TRUE;
                  if((VarInfo.Sign && (TotalDigits == 1))||
                     (TotalDigits == 0))
                     EditLine[TotalDigits++] = '0';
                  EditLine[TotalDigits++] = '.';
                  EditLine[TotalDigits] = '_';
                  EditLine[TotalDigits+1] = 0;                  
                  DrawString(pDC, EditLine);
				  MaxDigitFlag = FALSE;
                  DigitCounter = 0;
               }
			   else 
               {
                 // TouchScrnBeep(10);
                //  ERRORBEEP;
				    CChildView::ErrorBeep();
               }
			 }
			  else if(VarInfo.Metric)
			  {

			  if (VarFormatTable[VarInfo.Format].Metric.RightDigits && !DPFlag)
               {
                  /* Make Release Beep */
                 // TouchScrnBeep(6);
                  
                  DPFlag = TRUE;
                  if((VarInfo.Sign && (TotalDigits == 1))||
                     (TotalDigits == 0))
                     EditLine[TotalDigits++] = '0';
                  EditLine[TotalDigits++] = '.';
                  EditLine[TotalDigits] = '_';
                  EditLine[TotalDigits+1] = 0;                  
                  DrawString(pDC, EditLine);
				   MaxDigitFlag = FALSE;
                  DigitCounter = 0;
               }
			 else 
               {
                 // TouchScrnBeep(10);
               //  ERRORBEEP;
				  CChildView::ErrorBeep();
               }
			  
			  }

            }
         }
      break;
		                  
      case KEYPAD_ENT:
      if(CChildView::thisPtr->DisplayLockFlag )/* Display Lock Active ?*/
          {
             CChildView::thisPtr->ErrorBeep();
             CVgaMenu *menu;
             if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
             {
			      CChildView::thisPtr->AccessLevelSystem=OPERATOR;
               CChildView::thisPtr->menusname.AddTail(theApp.menuName);
               CChildView::thisPtr->menus.AddTail(page_no);
               CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
               page_no=1;
               CChildView::thisPtr->ModifyObjectList(menu);   
               theApp.menuName=CVgaBottomMenu::mainMenuID;
               theApp.MenuPointer=menu;   
             }                
				 CChildView::thisPtr->Invalidate();
             OnKeypadScreen_flag = false;
             Exit = true;
             break;
          }
		if (((VarInfo.NewVal > VarInfo.MaxVal) || /* Error chk */
            (VarInfo.NewVal < VarInfo.MinVal) ||
            (VarInfo.Value == -1))&&(KeyOffFlag==false))
        {
           if (VarInfo.Value == -1)
              MinMaxNoVal = NOVALUE;
           else if (VarInfo.NewVal > VarInfo.MaxVal)
              MinMaxNoVal = MAXRANGE;
           else MinMaxNoVal = MINRANGE;

           /* Another ugly kludge.  System can't display Max */
           /* for ENERGY type because it won't fit in space */
           /* allowed.  So need to convert to ENERGYDIV10 */
           /* before calling DisplayMinMaxError().  It's okay */
           /* to do this because we aren't going to keep any */
           /* of the VarInfo data anyway. */

           if (VarInfo.Format == ENERGY)
           {
              VarInfo.Value = 0;     /* Don't try to convert -1 */
              ConvertVariableFormat( ENERGY, ENERGYDIV10 );
           }
		  
           DisplayVGAMinMaxError(MinMaxNoVal,pDC); /* Display Err Msg */
           CVgaMenuItem::DrawRect(pDC,Blue, New_Value_String_Rect);
           CString TempReenter = Str_Reenter;
           if(CChildView::thisPtr->StringDebugFlag)
               TempReenter = Str_ReenterID + _T(" ")+ Str_Reenter;
           
           CVgaMenuItem::DrawText(pDC, SmallFont, White, 
									New_Value_String_Rect, 
									TempReenter/*[CChildView::Language_Index]*/,false);
           ErrorDisplayed = TRUE;
           TypedVal = 0;
           DPFlag = FALSE;
           DecimalCount = 0;
           DigitCounter = 0;
           TotalDigits = 0;
           MaxDigitFlag = FALSE;
		   
          /* Convert energey format if it's too large to show to one 
          /* decimal place. */
          if (VarInfo.Format == ENERGY && VarInfo.NewVal >= 10000)
            ConvertVariableFormat( ENERGY, ENERGYDIV10 );      
        }
      /*else if(VarInfo.ID==PRINTING_WELDRESULT)
			{	//printf("Inside the else if(VarInfo.ID==CScreenObject::PRINT_WELDRESULT) \n");
				OnKeypadScreen_flag=true;   

				CString PrinterPower_str;

				PrinterPower_str= tempRunScreenList.GetNext(RunScreenTemp_pos);

				CScreenKeypad::NoOfWeldresult=VarInfo.NewVal;
               if(!view->PrinterPresent)
			      {//	printf("inside  if(!view->PrinterPresent) \n");
				      view->ShowMessageScreen(PrinterPower_str);
                  break;
			      }
			      else
               {
					  //printf("inside  if(!view->PrinterPresent) == false \n");
				      view->BuildPrintList(PRINT_HISTORY_DATA);
               }
               
               Exit = TRUE;
				      
			}*/
        else  /* Entered value within permissible limits*/
		   {
			   void *ptr;
            void (*rmn)(int);
            if(functionCall.Lookup(VarInfo.FunName,ptr))
		      {
			      rmn = (void (*)(int))ptr;
               int Address=(int)this;
              // printf("\n call function of variable");
			      rmn(Address);
            }
            /* if(VarInfo.ID==CScreenObject::FORCEGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
					   ForceGraph.PrintSampleDisable=true;//value is dissabled
				   else
				   {
					   ForceGraph.BaseCount=view->UniversalCount;
						   if(view->ExtPreset)
						   ForceGraph.Ba  seCount=view->UniversalCount;
					   ForceGraph.PrintSampleValue	=VarInfo.NewVal;
					   ForceGraph.PrintSampleDisable	=false;
				   }
			   }
			   else if(VarInfo.ID== CScreenObject::DISTANCEGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
					   ColDistance.PrintSampleDisable	=true;//value is dissabled
				   else
				   {
					   ColDistance.BaseCount=view->UniversalCount;
						   if(view->ExtPreset)
						   ColDistance.BaseCount=view->UniversalCount;
					   ColDistance.PrintSampleValue	=VarInfo.NewVal;
					   ColDistance.PrintSampleDisable	=false;
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::AMPLITUDEGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
					   AmplitudeGraph.PrintSampleDisable=true;//value is dissabled
				   else
				   {
					   AmplitudeGraph.BaseCount=view->UniversalCount;
						   if(view->ExtPreset)
						   AmplitudeGraph.BaseCount=view->UniversalCount;
					   AmplitudeGraph.PrintSampleValue=VarInfo.NewVal;
					   AmplitudeGraph.PrintSampleDisable=false;
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::POWERGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
					   PowerGraph.PrintSampleDisable=true;//value is dissabled
				   else
				   {
					   PowerGraph.BaseCount=view->UniversalCount;
						   if(view->ExtPreset)
						   PowerGraph.BaseCount=view->UniversalCount;
					   PowerGraph.PrintSampleValue=VarInfo.NewVal;
					   PowerGraph.PrintSampleDisable=false;
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::VELOCITYGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
				   VelocityGraph.PrintSampleDisable=true;//value is dissabled
				   else
				   {
					   VelocityGraph.BaseCount=view->UniversalCount;
						   if(view->ExtPreset)
						   VelocityGraph.BaseCount=view->UniversalCount;
				   VelocityGraph.PrintSampleValue	=VarInfo.NewVal;
					   VelocityGraph.PrintSampleDisable=false;
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::WELDHISTORYSAMPLE)
			   {
				   if(KeyOffFlag)
				   WeldHistory.PrintSampleDisable	=true;//value is dissabled
				   else
				   {
					   WeldHistory.BaseCount=view->UniversalCount;
						   if(view->ExtPreset)
						   WeldHistory.BaseCount=view->UniversalCount;
					   WeldHistory.PrintSampleValue	=VarInfo.NewVal;
					   WeldHistory.PrintSampleDisable=false;
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::SETUPPRESETSAMPLE)
			   {
				   if(KeyOffFlag)
				   Setup.PrintSampleDisable=true;//	value is dissabled
				   else
				   {
					   Setup.BaseCount=view->UniversalCount;
						   if(view->ExtPreset)
					   Setup.BaseCount=view->UniversalCount;
				   Setup.PrintSampleValue=VarInfo.NewVal;
				   Setup.PrintSampleDisable	=false;
				   }
			   }
			   
			   else if(VarInfo.ID==CScreenObject::SEQPRESETSAMPLE)
			   {
				   if(KeyOffFlag)
				   PrintSequence.PrintSampleDisable=true;//	value is dissabled
				   else
				   {
					   PrintSequence.BaseCount=view->UniversalCount;
					   if(view->ExtPreset)
						   PrintSequence.BaseCount=view->UniversalCount;
					   PrintSequence.PrintSampleValue=VarInfo.NewVal;
					   PrintSequence.PrintSampleDisable	=false;
				   }
			   }


  
			   else if(VarInfo.ID==CScreenObject::FREQUENCYGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
				   FrequencyGraph.PrintSampleDisable=true;//	value is dissabled
				   else
				   {
					   FrequencyGraph.BaseCount=view->UniversalCount;
						   if(view->ExtPreset)
						   FrequencyGraph.BaseCount=view->UniversalCount;
					   FrequencyGraph.PrintSampleValue=VarInfo.NewVal;
					   FrequencyGraph.PrintSampleDisable	=false;
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::WELDSUMMARYSAMPLE)
			   {
				   if(KeyOffFlag)
				   Welddata.PrintSampleDisable=true;//	value is dissabled
				   else
				   {					
					   Welddata.BaseCount=view->UniversalCount+1-VarInfo.NewVal;
						   if(view->ExtPreset)
						   Welddata.BaseCount=view->UniversalCount+1-VarInfo.NewVal;
					   Welddata.PrintSampleValue=VarInfo.NewVal;
					   Welddata.PrintSampleDisable=false;
					   
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::LINESPERPAGE)
			   {
					   PrintSetup.WeldsPerPage=VarInfo.NewVal;
				   
			   }
            else if(VarInfo.ID==CScreenObject::VGA_USBFORCEGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
					   USBForceGraph.USBSampleDisable=true;//value is dissabled
				   else
				   {
					   USBForceGraph.BaseCount=view->UniversalCount;
					   USBForceGraph.USBSampleValue	=VarInfo.NewVal;
					   USBForceGraph.USBSampleDisable	=false;
					   
				   }
			   }
			   else if(VarInfo.ID== CScreenObject::VGA_USBDISTANCEGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
					   USBColDistance.USBSampleDisable	=true;//value is dissabled
				   else
				   {
					   USBColDistance.BaseCount=view->UniversalCount;
					   USBColDistance.USBSampleValue	=VarInfo.NewVal;
					   USBColDistance.USBSampleDisable	=false;
					   
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::VGA_USBAMPLITUDEGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
					   USBAmplitudeGraph.USBSampleDisable=true;//value is dissabled
				   else
				   {
					   USBAmplitudeGraph.BaseCount=view->UniversalCount;
					   USBAmplitudeGraph.USBSampleValue=VarInfo.NewVal;
					   USBAmplitudeGraph.USBSampleDisable=false;
					   
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::VGA_USBPOWERGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
					   USBPowerGraph.USBSampleDisable=true;//value is dissabled
				   else
				   {
					   USBPowerGraph.BaseCount=view->UniversalCount;
					   USBPowerGraph.USBSampleValue=VarInfo.NewVal;
					   USBPowerGraph.USBSampleDisable=false;
						   
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::VGA_USBVELOCITYGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
				   USBVelocityGraph.USBSampleDisable=true;//value is dissabled
				   else
				   {
					   USBVelocityGraph.BaseCount=view->UniversalCount;
				   USBVelocityGraph.USBSampleValue	=VarInfo.NewVal;
					   USBVelocityGraph.USBSampleDisable=false;
					   
				   }
			   }
		   
		   
			   else if(VarInfo.ID==CScreenObject::VGA_USBFREQUENCYGRAPHSAMPLE)
			   {
				   if(KeyOffFlag)
				   USBFrequencyGraph.USBSampleDisable=true;//	value is dissabled
				   else
				   {
					   USBFrequencyGraph.BaseCount=view->UniversalCount;
					   USBFrequencyGraph.USBSampleValue=VarInfo.NewVal;
					   USBFrequencyGraph.USBSampleDisable	=false;
					   
				   }
			   }
			   else if(VarInfo.ID==CScreenObject::VGA_USBWELDDATASAMPLE)
			   {
				   if(KeyOffFlag)
				   USBWelddata.USBSampleDisable=true;//	value is dissabled
				   else
				   {					
					   USBWelddata.BaseCount=view->UniversalCount+1-VarInfo.NewVal;
					   USBWelddata.USBSampleValue=VarInfo.NewVal;
					   USBWelddata.USBSampleDisable=false;
					   
				   }
			   }
			   else if((VarInfo.ID== CScreenObject::VQSWELDTIMEP)||(VarInfo.ID== CScreenObject::VQSWELDTIMEM)||
				   (VarInfo.ID==CScreenObject::VQSENERGYM)||(VarInfo.ID== CScreenObject::VQSENERGYP)||
				   (VarInfo.ID== CScreenObject::VQSPEAKPOWM)||(VarInfo.ID== CScreenObject::VQSPEAKPOWP)||
				   (VarInfo.ID==CScreenObject::VQSTOTDISTM)||(VarInfo.ID== CScreenObject::VQSTOTDISTP) ||
				   (VarInfo.ID==CScreenObject::VQSWELDCOLP)||(VarInfo.ID== CScreenObject::VQSWELDCOLM) ||
				   (VarInfo.ID==CScreenObject::VQSTOTABSP)||(VarInfo.ID== CScreenObject::VQSTOTABSM) ||
				   (VarInfo.ID==CScreenObject::VQSFORCEP)||(VarInfo.ID== CScreenObject::VQSFORCEM) ||
               (VarInfo.ID==CScreenObject::VQSCYCLETIMEP)||(VarInfo.ID== CScreenObject::VQSCYCLETIMEM))
			   {

               CScreenKeypad::Qualityflag=true;
               CChildView::MaxPreset=1;
			   }*/
				   
		      if (VarInfo.Sign == -1)
                VarInfo.NewVal = -VarInfo.NewVal;
		      VarInfo.NewVal = ConvertExternalInternal(VarInfo.NewVal,(FORMAT)VarInfo.Format);
		      flag = VarInfo.Disable? VarInfo.Disableflag : false;
		      if((VarInfo.Value != VarInfo.NewVal)|| (flag == VarInfo.Disableflag)
               ||((VarInfo.NewVal == 0)&&(VarInfo.MinVal == 0)))
              {
			      /*Sending Host Command to save Entered Value.*/
        		  // int length =12;
               int length =8;
		         unsigned char data[9];
		         unsigned char * date_data = (unsigned char *) &data[0];
		         union 
	            {
		            short i;
		            char c[2];
	            } u;
	            u.i=ID_type;
//               printf("\n ID_type=%d",ID_type);
               date_data[1]=u.c[0];
	            date_data[0]=u.c[1];
               union {
						    int disable_flag;
						    char x[IntegerLength];
						   } dsb;
				   dsb.disable_flag=VarInfo.Disableflag;
               data[3]=(char)dsb.x[0];
	    		   data[2]=(char)dsb.x[1];
               union {
						   int Variable_Value;
						   char y[IntegerLength];
						   } v;
				   v.Variable_Value=VarInfo.NewVal;
               for (int j = 0; j <IntegerLength ; j++)
					    date_data[7-j]=(char)v.y[j];
				/*   unsigned char data[15];

				   union {
						   int Variable_pointer;
						    char x[IntegerLength];
						   } u;
				   u.Variable_pointer=pointer;
				   for (int i = 0; i < IntegerLength; i++)
				   {
					    data[i]=(char)u.x[i];
				   }
				   union {
						   int Variable_Value;
						   char y[IntegerLength];
						   } v;
				   v.Variable_Value=VarInfo.NewVal;
				   for (int j = 0; j <IntegerLength ; j++)
					    data[7-j]=(char)v.y[j];
				   union {
						    int format_Value;
						   char z[IntegerLength];
						   } w;
				   w.format_Value=VarInfo.Format;
				   data[8]=(char)w.z[2];
				   data[9]=(char)w.z[3];
				   union {
						    int disable_flag;
						    char x[IntegerLength];
						   } dsb;
				   dsb.disable_flag=VarInfo.Disableflag;
				   data[10]=(char)dsb.x[1];
	    		   data[11]=(char)dsb.x[0];*/
				  // unsigned char * date_data = (unsigned char *) &data[0];

				   CHostCommand * request = new CHostCommand(SetValue_FunID, date_data, length);
				   CHostCommand * response = app->SendUiHostCommand(request);
				   /*if(VarInfo.ID==COLDSTART_INPROCESSID)//CScreenObject::BUCMENU)
					   CChildView::LargeWaitingTime=true;*/
				   if (response)
				   {	
					   CChildView::LargeWaitingTime=false;
					   char ch=CHostCommand::AckNak();
					   date_data=response->GetData();
					   length = response->GetDataLength(); 
					   if(ch==ACK)
					   {
							   
                     /*if(VarInfo.ID==COLDSTART_INPROCESSID)//CScreenObject::BUCMENU)
							   {
								   CChildView::ColdStartInProcess=true;//CVGAButtons::ColdStartInProcess=true;
							   }*/
							  /* CString output=(CString)EditLine;
                        output = "= " + output;
							   output.Delete(output.GetLength()-1,1);
                        if ((VarInfo.Disable)&&((VarInfo.Disableflag & VarInfo.Bitmask) == VarInfo.Bitmask))
								{
									*Object_Text_pointer= "= Off";
								}
                        else
                        {
							      CVgaVariable *ptrvariable =(CVgaVariable *)pointer;
                           char TempArray[LINESIZE+1]="                    ";
                           VarInfo.NewVal = CScreenKeypad::ConvertInternalExternal( VarInfo.NewVal,(CScreenKeypad::FORMAT)ptrvariable->Format);
                           CString Temp=CScreenKeypad::FormatNumber(VarInfo.NewVal,TempArray,(CScreenKeypad::FORMAT)ptrvariable->Format,ptrvariable->Unitshow,ptrvariable->Insertunitflag);
								   Temp.TrimLeft ();
                           Temp.TrimRight ();
                           ptrvariable->NewVal=VarInfo.NewVal;
                           *Object_Text_pointer=" = "+Temp;
                        }*/
							   ERRORBEEP;
                       //  CVgaMenu * menu;
                      //  if (theApp.menus.Lookup(theApp.menuName, menu))
		                  {
                           view->ModifyObjectList(theApp.MenuPointer);
                        }
							   //	Exit = TRUE;
							   delete response;
							   if(CScreenKeypad::Qualityflag==true)
							   {
                           view->SendCommandForQualityWindow(CChildView::MaxPreset);
                           CScreenKeypad::Qualityflag=false;
							   }
							  /* int last_address = 	view->menus.RemoveTail();
							   int Fun_Id = 	view->menus.RemoveTail();
							   int last_page=view->menus.RemoveTail();
							   if(Fun_Id==GetChoice_FunId)
							   {
								   int length1 =5;
								   unsigned char data1[6];
								   unsigned char *Choice_Data1 = (unsigned char *) &data1[0];
								   CScreenObject::Convert_Integer_To_Char(last_address, Choice_Data1);
								   Choice_Data1[4]=(char)(1);
								   for(int p=0;p<5;p++)
									   TRACE(_T("\n data for choice is=%d"),Choice_Data1[p]);


								   CHostCommand * Request = new CHostCommand(GetChoice_FunId, Choice_Data1, length1);
								   CHostCommand * REsponse = app->SendUiHostCommand(Request);
								   if (REsponse)
								   {
									   Choice_Data1 = REsponse->GetData();
									   length1 = REsponse->GetDataLength();
									   TRACE(_T("\n LENGTH IS****%d"),length1);
									   *Choice_Data1++;
									   length1--;
									   view->CreateObjectList(Choice_Data1,length1);
									    page_no=last_page;
									   view->menus.AddTail(last_page);
									   view->menus.AddTail(GetChoice_FunId);
									   view->menus.AddTail(last_address);
									   delete REsponse;
								   }
							   }
							   else
							   {
								   view->BuildMenu(Fun_Id,last_address);
								   int address=view->menus.RemoveTail();
								   view->menus.RemoveTail();
								   view->menus.RemoveTail();
								   if(address == view->mainMenuAddress)
								   {
									   page_no=1;
									   view->menus.AddTail(page_no);
									   view->menus.AddTail(GetMenuData_FunId);
									   view->menus.AddTail(view->mainMenuAddress);
								   }
								   else
								   {
									   page_no=last_page;
									   view->menus.AddTail(last_page);
									   view->menus.AddTail(Fun_Id);
									   view->menus.AddTail(last_address);
								   }
							   }*/
                        
							   Exit = TRUE; /* Enter keypressed */    
									   
							  /* if(VarInfo.ID==CScreenObject::VGA_PMCUPPERBAND)
								   view->UpperPMCLimit=VarInfo.NewVal;
			    
							   if(VarInfo.ID==CScreenObject::VGA_PMCLOWERBAND)
								   view->LowerPMCLimit=VarInfo.NewVal;*/
					   }
					   else if(ch==NAK)
						   view->ProcessNak(date_data,length,0,0 );
						   
				   }
				   else 
				   {
				   //view->PopMenu(true);
               theApp.menuName=view->menusname.RemoveTail();
               page_no=view->menus.RemoveTail();
               theApp.MenuPointer=view->menupointers.RemoveTail();
             //  CVgaMenu * menu1;
               //page_no=1;
		        // if (theApp.menus.Lookup(theApp.menuName, menu1))
		         {
			         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			         
		         }
				   CChildView::LargeWaitingTime=false;
				   }
			   }
		   }
           break;
        default:                
           //TouchScrnBeep(10);  /* Inappropriate keypress, beep */
           break;
      }/*End of Inner Switch*/
      return(Exit);

}

/***************************************************************************/
/*                                                                         */
/*  This function handles entry of VARIABLE values using the Increase/     */
/*  Decrease keys.  It is called when an Inc or Dec key is pressed at an   */
/*  appropriate time during value entry.  When this function is called,    */
/*  there must be a number displayed on the screen in the appropriate      */
/*  position, and it must be legal to increment or decrement (depending on */
/*  which key was pressed) by at least one unit.                           */
/*                                                                         */
/*  While inside this function, the Inc/Dec keys may be used to adjust the */
/*  value of the variable. 												   */
/*                                                                         */
/*  Parameters:                                                            */
/*                                                                         */
/*    KeyPressed - which key is pressed on the keypad screen               */ 
/*      pDC  - pointer to device context                                  */                                                                    
/*  Note: Due to strange behavior of ENERGY format, it's possible for      */
/*  format type to change while inside this function.                      */
/*                                                                         */
/***************************************************************************/
void CScreenKeypad::VGAVarEntryIncDecMode(int KeyPressed,CDC *pDC)
{
   char   ValueLine[LINESIZE+1] = "                    ";
   SINT32  MinVal, MaxVal, Temp;
   char   *TempValueLine;
   char   TempLine[LINESIZE+1] = "                    ";

   if (VarInfo.NewVal != -1)
   {
      if (VarInfo.Sign)  /* For items with sign display, use real range */
      {
         MaxVal = VarInfo.MaxVal;
         MinVal = -VarInfo.MaxVal;
         if (VarInfo.Sign == -1)
            VarInfo.NewVal = -VarInfo.NewVal;
      }
      else
      {
         MaxVal = VarInfo.MaxVal;
         MinVal = VarInfo.MinVal;
      }

      Temp = VarInfo.NewVal;

      if (KeyPressed == KEYPAD_INC)
      {
          VarInfo.NewVal += VarFormatTable[VarInfo.Format].English.Increment;
          if (VarInfo.NewVal > MaxVal) /* Check for value above maximum*/
             VarInfo.NewVal = MaxVal; 
      }
      else
      {
          VarInfo.NewVal -= VarFormatTable[VarInfo.Format].English.Increment;
          if (VarInfo.NewVal < MinVal) /* Check for value below minimum*/
              VarInfo.NewVal = MinVal;
      }

      if (Temp == VarInfo.NewVal)    /* Couldn't change */
         ERRORBEEP;
      else
      {
         /* Miserable kludge: Format of ENERGY items can change */
         /* depending on value.  If over 1000.0J, need to use */
         /* ENERGYDIV10.  Do this by convert to internal, then */
         /* switch formats & convert to external.  Same idea */
         /* going from ENERGYDIV10 to ENERGY. */
         if (VarInfo.Format == ENERGY && VarInfo.NewVal >= 10000)
             ConvertVariableFormat( ENERGY, ENERGYDIV10 );

         else if(VarInfo.Format == ENERGYDIV10 && VarInfo.NewVal < 1000)
                 ConvertVariableFormat( ENERGYDIV10, ENERGY );

        FormatNum(VarInfo.NewVal,ValueLine);
		VarInfo.Value=0;
        TempValueLine = SplitString(ValueLine, " ",TempLine);         
        strcat (TempLine, "_");
		strcpy(EditLine,TempLine);
        DrawString(pDC, TempLine);
      }
      if (VarInfo.Sign)            /* If sign displayed, convert back to */
      {                             /* absolute value. */
         if (VarInfo.NewVal < 0)
         {
            VarInfo.NewVal = -VarInfo.NewVal;
            VarInfo.Sign = -1;
         }
         else
            VarInfo.Sign = 1;
      }
   }
   else
   {
     // TouchScrnBeep(10);
   }

}

/***************************************************************************/
/*                                                                         */
/*  Converts the item described by *VarInfo from one "format" to another,  */
/*  by converting to the internal storage units and then to the other      */
/*  format.  MinVal, MaxVal, NewVal, and FormatPtr are affected (but       */
/*  string size is assumed to be the same).  This function is primarily    */
/*  used when an item needs to be converted from ENERGY to ENERGYDIV10 and */
/*  vice versa because the value of the item has become too high or too    */
/*  low.                                                                   */
/*                                                                         */
/***************************************************************************/

void CScreenKeypad::ConvertVariableFormat(enum FORMAT Format1, enum FORMAT Format2)
{
   VarInfo.MinVal = ConvertExternalInternal( VarInfo.MinVal, Format1 );
   VarInfo.MinVal = ConvertInternalExternal( VarInfo.MinVal, Format2);
   VarInfo.NewVal = ConvertExternalInternal( VarInfo.NewVal, Format1 );
   VarInfo.NewVal = ConvertInternalExternal( VarInfo.NewVal, Format2 );
   VarInfo.MaxVal = ConvertExternalInternal( VarInfo.MaxVal, Format1 );
   VarInfo.MaxVal = ConvertInternalExternal( VarInfo.MaxVal, Format2);
   VarInfo.Format = Format2;
}


/****************************************************************************/
/*                                                                          */
/* Converts the value passed in to internal storage units.  Passed number   */
/* is binary form of what was entered or displayed, minus a decimal point.  */
/* Conversion may scale by factors of ten or convert units, but end result '*/
/* is suitable for storage.                                                 */
/*                                                                          */
/****************************************************************************/
int CScreenKeypad::ConvertExternalInternal(SINT32 Number, enum FORMAT format)
{ 
	bool Metric=VarInfo.Metric;
 SINT32 RetVal;
   struct var_format_def1 *FormatPtr;

   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;
      
      /*
		if ( format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
	  */
	  
   /* Perform conversion from displayed units to stored units */

   if (Number < 0)
      RetVal = 0-((((0-Number) * FormatPtr->ConvDiv) +
    (FormatPtr->ConvMult/2))/(FormatPtr->ConvMult));
   else
      RetVal = ((Number * FormatPtr->ConvDiv) +
    (FormatPtr->ConvMult/2))/(FormatPtr->ConvMult);

   return( RetVal );
}


/****************************************************************************/
/*                                                                          */
/* Converts the value passed in, which is in the specified format, into a   */
/* form that can be displayed.  This may involve scaling by factors of ten  */
/* or unit conversions.  The end result is a SINT32 that can be converted  '*/
/* to ASCII and displayed, with a decimal point placed as determined by the */
/* format.                                                                  */
/*                                                                          */
/****************************************************************************/
int CScreenKeypad::ConvertInternalExternal(SINT32 Value, enum FORMAT format)
{
	 bool Metric=CChildView::metric;//VarInfo.Metric;
int RetVal;
   struct var_format_def1 *FormatPtr;

   if (Metric)//CChildView::metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;

   /* Perform conversion from stored units to displayed units */
   
    /*
		if ( format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
	*/
		
		
   if (Value < 0)
      RetVal = 0 - ((((0-Value)*FormatPtr->ConvMult) + (FormatPtr->ConvDiv/2))/
        FormatPtr->ConvDiv);
   else
      RetVal = ((Value*FormatPtr->ConvMult) + (FormatPtr->ConvDiv/2))/
        FormatPtr->ConvDiv;

   return( RetVal );
}

/****************************************************************************/
/*Description:-                                                             */
/* A series of calls to this function breaks the input string (Split_str) in*/
/* to sequence of tokens each of which is delimited by the characters in    */
/* second string (Split_Char) and splited token is available in             */
/* 'Splited_Str' string                                                     */
/*Return Value:-                                                            */
/* SINT8 *retPtr : pointer to the string from where next token needs to be  */
/*                Parsed.                                                   */
/****************************************************************************/
char* CScreenKeypad::SplitString(char Split_Str[], char Split_Char[], char Splited_Str[])
{
 char *retPtr;
   unsigned int Index;
   unsigned int Index1;
   bool break_str;
   int count =0;
   bool SkipChar = true;
   
   for (Index=0; Index < strlen(Split_Str); Index++)
   {
      break_str = false;
      for(Index1 =0; Index1 < strlen(Split_Char); Index1++)
      {
         
         if(Split_Str[Index] == Split_Char[Index1] )
         {
           break_str = TRUE;
           break;
         }         
      }
      if(break_str == FALSE) 
      {
        
        Splited_Str[count]= Split_Str[Index];
        count++;
        SkipChar = FALSE;
      }
      else 
      {
         if(SkipChar == FALSE)
         {
         Splited_Str[count] = NUL;
         retPtr = &Split_Str[Index];
         break;
         }          
      }
   }
   if(Index == strlen(Split_Str))
   {
      retPtr = NULL_PTR;
      if(count== 0) Splited_Str[0]=NUL;
      else Splited_Str[count] = NUL;
   }
   return(retPtr);  
}

/****************************************************************************/
/*                                                                          */
/* Converts the given number into an ASCII string showing a variable of the */
/* given format. The string is written to the supplied String[] right-      */
/* justified and with spaces filling in unused space to the left.           */
/* Conversion to displayable units is assumed to have been done.            */
/*                                                                          */
/* Input Parameters:                                                        */
/*                                                                          */
/*    Value - Value to display                                              */
/*    String[] - Output string                                              */
/*                                                                          */
/****************************************************************************/
void CScreenKeypad::FormatNum(int Number,char String[])
{
	//int Number=VarInfo.NewVal;
   int MaxLen=VarInfo.Size;
   bool Metric=VarInfo.Metric;
   UINT8 ChrCount, Digits;
   char *cptr;
   char SignChr;
   struct var_format_def1 *FormatPtr;

   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[ VarInfo.Format].Metric;
   else
      FormatPtr = &VarFormatTable[ VarInfo.Format].English;
      
      /*
		if ( VarInfo.Format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( VarInfo.Format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
	   */

   if (Number < 0)
   {
      Number = -Number;
      SignChr = '-';
   }
   else
      SignChr = '+';

   cptr = String;
   for (ChrCount=0; ChrCount<MaxLen; ChrCount++)  /* Blank out input string */
      *cptr++ = ' ';

   cptr = &String[MaxLen-1];      /* Point to last chr in string */
   ChrCount = MaxLen;     /* Should already have this, but do anyway */
   Digits = FormatPtr->RightDigits;
   if (Digits)          /* If necessary, write digits to right of decimal */
   {
      while (ChrCount && Digits)
      {
         *cptr-- = (Number%10) + '0';
         Number /= 10;
         ChrCount--;
         Digits--;
      }
      if (ChrCount)
      {
         *cptr-- = '.';
         ChrCount--;
      }
   }
   if (ChrCount)     /* Write left part if space in string */
   {
      //Digits = VarFormatTable[VarInfo.Format].English.LeftDigits; /* Max # of digits to write this step */
	  Digits = FormatPtr->LeftDigits;
      if (Digits > ChrCount)  /* Don't write more than there's space for */
         Digits = ChrCount;
      if (Number)
      {
         while (Digits && Number)
         {
            *cptr-- = (Number%10) + '0';
            Number /= 10;
            Digits--;
            ChrCount--;
         }
      }
      else
      {
         *cptr-- = '0';   /* Always one chr left of decimal point */
         ChrCount--;
      }
   }
   if (ChrCount && (FormatPtr->ShowSign || SignChr == '-'))
      *cptr = SignChr;     /* Add sign */
}

CString CScreenKeypad::FormatNumber(int Number,char String[],enum FORMAT format,bool ChkUnitflag,bool Insertunitflag1)
{
	//int Number=VarInfo.NewVal;
   //int MaxLen=VarInfo.Size;
   
  // int MaxLen=VarInfo.Size;
   bool Metric=CChildView::metric;//VarInfo.Metric;
   UINT8 ChrCount, Digits;
   char *cptr;
   char *UnitText;
   char SignChr;
   struct var_format_def1 *FormatPtr;

   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;

      /*
		if ( format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
	  */	
		
   int RetVal = FormatPtr->RightDigits;

   if (RetVal)
      RetVal += 1;

   if (FormatPtr->ShowSign)   /* Count sign if display always forced */
      RetVal += 1;

   RetVal += FormatPtr->LeftDigits;
    int MaxLen=RetVal;
   if (Number < 0)
   {
      Number = -Number;
      SignChr = '-';
   }
   else
      SignChr = '+';

   UnitText=FormatPtr->Units ;
   cptr = String;
   for (ChrCount=0; ChrCount<MaxLen; ChrCount++)  /* Blank out input string */
      *cptr++ = ' ';

   cptr = &String[MaxLen-1];      /* Point to last chr in string */
   ChrCount = MaxLen;     /* Should already have this, but do anyway */
   Digits = FormatPtr->RightDigits;
   if (Digits)          /* If necessary, write digits to right of decimal */
   {
      while (ChrCount && Digits)
      {
         *cptr-- = (Number%10) + '0';
         Number /= 10;
         ChrCount--;
         Digits--;
      }
      if (ChrCount)
      {
         *cptr-- = '.';
         ChrCount--;
      }
   }
   if (ChrCount)     /* Write left part if space in string */
   {
      //Digits = VarFormatTable[VarInfo.Format].English.LeftDigits; /* Max # of digits to write this step */
	  Digits = FormatPtr->LeftDigits;
      if (Digits > ChrCount)  /* Don't write more than there's space for */
         Digits = ChrCount;
      if (Number)
      {
         while (Digits && Number)
         {
            *cptr-- = (Number%10) + '0';
            Number /= 10;
            Digits--;
            ChrCount--;
         }
      }
      else
      {
         *cptr-- = '0';   /* Always one chr left of decimal point */
         ChrCount--;
      }
      
   }
   
   /*Digits = FormatPtr->RightDigits;
   if (Digits)          /* If necessary, write digits to right of decimal * /
   {
      while (ChrCount && Digits)
      {
         *cptr-- = (Number%10) + '0';
         Number /= 10;
         ChrCount--;
         Digits--;
      }
      if (ChrCount)
      {
         *cptr-- = '.';
         ChrCount--;
      }
   }
   if (ChrCount)     /* Write left part if space in string * /
   {
      //Digits = VarFormatTable[VarInfo.Format].English.LeftDigits; /* Max # of digits to write this step * /
	  Digits = FormatPtr->LeftDigits;
      if (Digits > ChrCount)  /* Don't write more than there's space for * /
         Digits = ChrCount;
      if (Number)
      {
         while (Digits && Number)
         {
            *cptr-- = (Number%10) + '0';
            Number /= 10;
            Digits--;
            ChrCount--;
         }
      }
      else
      {
         *cptr-- = '0';   /* Always one chr left of decimal point * /
         ChrCount--;
      }
   }*/
   if (ChrCount && (FormatPtr->ShowSign || SignChr == '-'))
      *cptr = SignChr;     /* Add sign */
   CString str=String;
   str.TrimLeft ();
   str.TrimRight ();
   if((ChkUnitflag)/*&&(!Insertunitflag1)*/)
   {
      CString temp=UnitText;
      temp.TrimLeft ();
      temp.TrimRight ();
      str+=temp;
   }
   return str;
}

bool CScreenKeypad::InsertProperUnits(CVgaMenuItem *ptr,enum FORMAT format,int type)
{
   CVgaVariable *pointer1;
   CRadioMenu *pointer2;
   CString str;
   if(type==CVgaMenu::VARIABLE)
   {
      pointer1=(CVgaVariable *)ptr;
      str=pointer1->text;
   }
   else
   {
      pointer2=(CRadioMenu *)ptr;
      str=pointer2->text;
   }
   
   
   struct var_format_def1 *FormatPtr;
   char *UnitText;
   if (CChildView::metric)                 /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;
    
      /*
		if ( format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
	  */ 	
		
   int Index=0;
   
   while (str.GetAt(Index) && (str.GetAt(Index) != '('))
      Index++;
   //printf("\n Index=%d",Index);
   UnitText = FormatPtr->Units;
   bool Flag;

   if(type==CVgaMenu::VARIABLE)
      Flag=pointer1->Insertunitflag;
   else
      Flag=pointer2->Insertunitflag;
   
   if(!Flag)
   {
      if ((str.GetAt(Index) == '('))
      {
        // printf("\n str.GetAt(Index) == '&'");
         Index++;
         for (int ChrCount=0; (ChrCount < 4) && (str.GetAt(Index) != ')'); ChrCount++)
            str.SetAt(Index++,*UnitText++);
         
         if(type==CVgaMenu::VARIABLE)
            pointer1->text=str;
         else
            pointer2->text=str;
         return true;
      }
      
   }
   else
   {
      return false;
   }
   return false;
}

CString CScreenKeypad::InsertWeldParamUnit(CString string,enum FORMAT format)
{
   struct var_format_def1 *FormatPtr;
   char *UnitText;
   if (CChildView::metric)                 /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;

      /*
		if ( format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
	  */
	  	
   int Index=0;
    
   while (string.GetAt(Index) && (string.GetAt(Index) != '&'))
      Index++;
   UnitText = FormatPtr->Units;
   if ((string.GetAt(Index) == '&'))
   {
       for (int ChrCount=0; (ChrCount < 4) && (string.GetAt(Index) == '&'); ChrCount++)
         string.SetAt(Index++,*UnitText++);
   }
   return string;
}

CString CScreenKeypad::InsertWeldParamUnitsString(bool metric,enum FORMAT format)
{
   struct var_format_def1 *FormatPtr;
   char *UnitText;
   if (metric)                 /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;
      
      /*
		if ( format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
	  */	

   UnitText = FormatPtr->Units;
   return UnitText;
}

void CScreenKeypad::DrawString(CDC *pDC, char string[])
{
	CVgaMenuItem::DrawRect(pDC, White,  New_Value_Rect);
	CRect r(New_Value_Rect);
	r.OffsetRect(XOFFSET, YOFFSET);
   CFont KeypadFont;
   KeypadFont.CreateFont(20 , 8, 0, 0, FW_NORMAL,//FW_ULTRALIGHT,
         FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
         DEFAULT_QUALITY, FF_DONTCARE,_T("Arial"));
	CFont *OldFont=pDC->SelectObject(&KeypadFont);
	pDC->SetTextColor(Black);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(string,r,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
   pDC->SelectObject(OldFont);
	KeypadFont.DeleteObject();
}

/***************************************************************************/
/*  This function will display the passed error code on the keypad screen  */
/*  Three errors messages are displayed                                    */
/*    Value below minimum                                                  */
/*    Value above Maximum                                                  */
/*    No value entered                                                     */
/*                                                                         */
/* Parameters:                                                             */
/*   Ecode - Error code for the type of error to be displayed              */
/*   *pDC  -   Pointer to the device context object                        */   
/***************************************************************************/
void CScreenKeypad::DisplayVGAMinMaxError(enum ERRORCODES ECode,CDC *pDC)
{
	  CChildView::ErrorBeep();
	/*CString  StrME_1[]  =   {   
		 "Value Below Minimum ",
         "Wert unter Minimum  ",
         "Valor Por Debajo Mn ",
         "Valore Sotto Minimo ",
         "Val. Inf Au Minimum ",
         L"\x6700\x4f4e\x503c\x0",
         L"\x4f4e\x65bc\x6700\x4f4e\x503c\x0",
         L"\x5024\x304c\x6700\x5c0f\x5024\x4ee5\x4e0b",
         L"\xcd5c\xc18c\xce58\xbcf4\xb2e4\x0020\xb0ae\xc740\xac12"  };

 CString StrME_2[]   =   {   
		 "Value Above Maximum ",
         "Wert ueber Maximum  ",
         "Valor Por Encim Max ",
         "Valore Sopr Massimo ",
         "Val. Sup Au Maximum ",
         L"\x6700\x9ad8\x503c\x0",
         L"\x9ad8\x65bc\x6700\x9ad8\x503c\x0",
         L"\x5024\x304c\x6700\x5927\x5024\x4ee5\x4e0a",
         L"\xcd5c\xace0\xce58\xbcf4\xb2e4\x0020\xb192\xc740\xac12"  };

 CString StrME_3[]   =   {     
		 "No Value Entered    ",
         "Kein Wert eingegeb. ",
         "Ningun val intro    ",
         "Nessun val inserito ",
         "Aucune Val. Entree  ",
         L"\x65e0\x6570\x503c\x8f93\x5165\x0",
         L"\x7121\x6578\x503c\x8f38\x5165\x0",
         L"\x5024\x304c\x5165\x529b\x3055\x308c\x3066\x3044\x307e\x305b\x3093",
         L"\xac12\xc774\x0020\xc785\xb825\xb418\xc9c0\x0020\xc54a\xc74c" };*/

 /* CString StrPassIncorrect[] =   {      
		 "Password Incorrect  ",
         "Passwort falsch     ",
         "Contrasena Incorrec.",
         "Password errata     ",
         "Mot Passe Incorr.   ",
         L"\x5bc6\x7801\x4e0d\x6b63\x786e\x0",
         L"\x5bc6\x78bc\xe030\x6b63\x78ba\x0",
         L"\xff8a\xff9f\xff7d\xff9c\xff70\xff84\xff9e\x304c\x9593\x9055\x3063\x3066\x3044\x307e\x3059",
         L"\xd328\xc2a4\xc6cc\xb4dc\x0020\xbd88\xc77c\xce58"};
												 
 CString StrBlankLine[] = {	 "                    ",
											 "                    ",
											 "                    ",
									         "                    ",
											 "                    " ,
											 "                    ",
											 "                    ",
											 "                    ",
											 "                    "	};*/
	
	
	char ValueBuffer[LINESIZE+1];
    SINT32 MaxVal, MinVal;
   if (VarInfo.Sign == -1)
   {
      MaxVal = -VarInfo.MinVal;
      MinVal = -VarInfo.MaxVal;
   }
   else
   {
      MaxVal = VarInfo.MaxVal;
      MinVal = VarInfo.MinVal;
   }
   CVgaMenuItem::DrawRect(pDC,Red, Error_rect);
   CString TempTextME1=StrME_1,TempTextME2=StrME_2,TempTextME3=StrME_3,
      TempPassIncorrect=StrPassIncorrect;
   if(CChildView::thisPtr->StringDebugFlag)
   {
      TempTextME1=StrME_1ID + _T(" ") + StrME_1;
      TempTextME2=StrME_2ID + _T(" ") + StrME_2;
      TempTextME3=StrME_3ID + _T(" ") + StrME_3;
      TempPassIncorrect = StrPassIncorrectID + _T(" ") + StrPassIncorrect;
   }
   switch (ECode)
   {
      case MINRANGE:                 /* Value entered is below minimum */
       CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect,
						TempTextME1/*[CChildView::Language_Index]*/,true);/* Minimum Value string */
      break;

      case MAXRANGE:                 /* Value entered is above maximum */
        CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect,
									TempTextME2/*[CChildView::Language_Index]*/,true);
	  break;
      
      case NOVALUE:
			CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect, 
										TempTextME3/*[CChildView::Language_Index]*/,true);
         break;
	  case PassInvalid:
			CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect, 
									TempPassIncorrect/*[CChildView::Language_Index]*/,true);
         break;

      default:
        CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect,"                    " 
										/*StrBlankLine[CChildView::Language_Index]*/,true);
         break;
   }
  if(type != VGA_PASSWORD)
   {
	FormatNum(VarInfo.MinVal,&ValueBuffer[LINESIZE-VarInfo.Size]); /* Get minimum value */
   CString MinValueString =StrME_4;//[CChildView::Language_Index];
   if(CChildView::thisPtr->StringDebugFlag)
   {
      MinValueString = StrME_4ID + _T(" ") + StrME_4;
   }
   
   for(int i=(LINESIZE-VarInfo.Size);i<(LINESIZE);i++)
		MinValueString+=ValueBuffer[i];
	CVgaMenuItem::DrawText(pDC, SmallFont, White, Min_Value_Str_rect,
						MinValueString,false);
   FormatNum(VarInfo.MaxVal, &ValueBuffer[LINESIZE-VarInfo.Size]); /* Get maximum value */
   CString MaxValueString =StrME_5;//[CChildView::Language_Index];
   if(CChildView::thisPtr->StringDebugFlag)
   {
      MaxValueString = StrME_5ID + _T(" ") + StrME_5;
   }
   for(int j=(LINESIZE-VarInfo.Size);j<(LINESIZE);j++)
		MaxValueString+=ValueBuffer[j];
   CVgaMenuItem::DrawText(pDC, SmallFont, White, Max_Value_Str_rect, 
						MaxValueString,false);
   }
  // TouchScrnBeep(10);  /* Beep for the error */
   ERRORBEEP;
}


/***************************************************************************/
/*  This function will display the Min:/Max Value on the keypad screen     */
/*                                                                         */
/* Parameters:                                                             */
/*   Varinfo - Pointer to various context information of a variable entry  */   
/***************************************************************************/
void CScreenKeypad::DisplayVGAMinMax(CDC *pDC)
{
	char ValueBuffer[LINESIZE+1];
    SINT32 MaxVal, MinVal;
   if (VarInfo.Sign == -1)
   {
      MaxVal = -VarInfo.MinVal;
      MinVal = -VarInfo.MaxVal;
   }
   else
   {
      MaxVal = VarInfo.MaxVal;
      MinVal = VarInfo.MinVal;
   }
   FormatNum(VarInfo.MinVal,&ValueBuffer[LINESIZE-VarInfo.Size]); /* Get minimum value */

   CString MinValueString =StrME_4;//[CChildView::Language_Index];
   if(CChildView::thisPtr->StringDebugFlag)
   {
      MinValueString = StrME_4ID + _T(" ") + StrME_4;
   }

   for(int i=(LINESIZE-VarInfo.Size);i<(LINESIZE);i++)
		MinValueString+=ValueBuffer[i];

   
   CVgaMenuItem::DrawText(pDC, SmallFont, White, Min_Value_Str_rect,
									MinValueString,false);
   FormatNum(VarInfo.MaxVal,&ValueBuffer[LINESIZE-VarInfo.Size]); /* Get maximum value */
   CString MaxValueString =StrME_5;//[CChildView::Language_Index];
   if(CChildView::thisPtr->StringDebugFlag)
   {
      MaxValueString = StrME_5ID + _T(" ") + StrME_5;
   }
   for(int j=(LINESIZE-VarInfo.Size);j<(LINESIZE);j++)
		MaxValueString+=ValueBuffer[j];
	CVgaMenuItem::DrawText(pDC, SmallFont, White, Max_Value_Str_rect,
							MaxValueString,false);
}

/****************************************************************************/
/*                                                                          */
/* Returns the maximum # of characters that should be allocated to display  */
/* a value in the given format.  If the # of characters to the right of the */
/* decimal point is nonzero, a character is added to allow space for the '.'*/
/* Note that space is not provided for a sign character (+ or -) unless     */
/* the format always includes a sign.                                       */
/*                                                                          */
/****************************************************************************/
int CScreenKeypad::VarSize(enum FORMAT format)

{
   UINT8 RetVal;
   struct var_format_def1 *FormatPtr;

   if (VarInfo.Metric)
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;
     
      /*
		if ( format ==MICRONS)
		{
			if(CChildView::AmplitudeMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		}
		if ( format ==POWERWATTS)
		{
			VarFormatTableAmpPower[POWER].Unit.ConvMult=CChildView::PeakPowerWattsMax;
			if(CChildView::PeakPowerMicrons==false)
				FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
			else
				FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		}
	  */
	  	
   RetVal = FormatPtr->RightDigits;

   if (RetVal)
      RetVal += 1;

   if (FormatPtr->ShowSign)   /* Count sign if display always forced */
      RetVal += 1;

   RetVal += FormatPtr->LeftDigits;
   return( RetVal );
}

int CScreenKeypad::GetInteger(unsigned char *&data, int bytes)
{
	if(bytes == 2)
	{
		union {
				 int i;
				 unsigned char c[IntegerLength];
				} u;
		u.c[0]=0;
		u.c[1]=0;
		for (int i = 2; i < IntegerLength; i++)
		{
			unsigned char x=*data++;
			u.c[i] = x;
		}
		return ntohl(u.i);
	}
	else
	{
		 union {
				int i;
				char c[IntegerLength];
				} u;
		for (int i = 0; i < IntegerLength; i++)
			u.c[i] = *data++;
		return ntohl(u.i);
	}
}

/***************************************************************************/
/*                                                                         */
/*  Displays the number whose information is provided in Current and New   */
/*  value rectangle.                                                       */
/*                                                                         */
/*  Parameters                                                             */
/*  VarInfo - Pointer to various context information of a variable entry   */ 
/*                                                                         */
/***************************************************************************/

void CScreenKeypad::VGADisplayCurrentNewValue(CDC *pDC)
{
   char ValueLine[LINESIZE+1] = "                    "; /* 20 spaces */
   SINT32 NewVal;
   if (VarInfo.Sign == -1)
      NewVal = -VarInfo.NewVal;
   else
      NewVal = VarInfo.NewVal;

   FormatNum( NewVal,  ValueLine);
     CVgaMenuItem::DrawRect(pDC,White,  New_Value_Rect);///new value rect
  if((TotalDigits==0)&&(FirstKeyPress != KEY_INC_DEC ))
  {
	strcpy(ValueLine, "_");   
	CVgaMenuItem::DrawText(pDC, SmallFont, Black, 
							New_Value_Rect,ValueLine ,false);
  }
  else
	   DrawString(pDC, EditLine);
   if (VarInfo.Disable)
      VarInfo.Disableflag &= ~(VarInfo.Bitmask);
//   printf("\n VarInfo.Disableflag in display");
} /*End of function*/


void CScreenKeypad::CopyString(char *dest, char *source)
{
	for(int i=0;i<LINESIZE;i++)
		*(dest++)=*(source++);
	*(++dest)='\0';
}



/***************************************************************************/
/*                                                                         */
/*   Handle Enter on Password Keypad screen.Check if no value enter,Check  */
/*   for both password (entered and confirm password) will be same.        */
/***************************************************************************/
void CScreenKeypad::HandleEnterOnPassword(CChildView *view, CDC *pDC)
{
	if(AlphaBuf[0] ==NULL)
	{
	   DisplayVGAMinMaxError(NOVALUE,pDC); 
	   ErrorDisplayed = TRUE;
	}
	else if(pointer==0)//password entered for first time to set password.
	{
		//CChildView::LargeWaitingTime=true;
	   SendCommandForPassword(view,SetValue_FunID,pDC);
	   ErrorDisplayed = TRUE;
	   //CChildView::LargeWaitingTime=false;
	}

	else if(pointer ==1)//second time password entered to confirm the set password.
	{
		if(TempPassword == AlphaBuf)//password matched.
			SendCommandForPassword(view,SetValue_FunID,pDC);//ErrorDisplayed = TRUE;
		else
		{
			DisplayVGAMinMaxError(PassInvalid,pDC); 
			ErrorDisplayed = TRUE;InitializedValues();
		}
	}
	else if((pointer !=1)&&(pointer !=0))//password entered for secure menus.
		SendCommandForPassword(view,SetValue_FunID,pDC);
}


/****************************************************************************/
/*                                                                          */
/*   Send Hostcommand for password entered and show appropriate screens		*/
/*   according to the response.											    */
/****************************************************************************/
void CScreenKeypad::SendCommandForPassword(CChildView *view,int FunID,CDC *pDC)
{
	unsigned char data[26];
	int length_pass=0;
   bool VelocityOn=false,TempFlagDebugOn=false,TempFlagDebugOff=false;
	while(AlphaBuf[length_pass]!='\0')//Getting Length of password.
		length_pass++;
/*	if(FunID==GetPasswordMenus_FunId)
	{
		data[0]=(char)length_pass;
		for(int J=0;J<length_pass;J++)
			data[1+J]=AlphaBuf[J];
		length_pass =length_pass+1;
	}
	else*/
	{
		union 
		   {
			   short i;
			   char c[2];
		   } u;
	    u.i=ID_type;
      data[1]=u.c[0];
		data[0]=u.c[1];
//      printf("\n ID=%d",ID_type);
      
		data[2]=(char)length_pass+1;
//      printf("\n length_pass=%d",length_pass);
      if(pointer==0)//Enter Password Keypad Screen.
      {
//         printf("\n pointer is Zero");
         data[3]=(char)01;
      }
		else if(pointer==1)//Confirm Password Keypad Screen.
      {
//         printf("\n pointer in one");
         data[3]=(char)02;
      }
      else
      {
         data[3]=(char)00;//Branson Menu & protected menu.
      }
		for(int J=0;J<length_pass;J++)
			data[4+J]=AlphaBuf[J];
		length_pass = length_pass+4;



		char PasswordAed[]="534922868726";
		char PasswordAef[]="634922868726";
      char PassConfigAEFSBeam[]="266344672326";
      char PassConfigAEDSBeam[]="266344572326";
      char PassConfigMICROSbeam[]="266344772326";

		int temp=length_pass-4;
		if(temp == 12)
		{
			int match=0;
			for(int t=0;t<temp;t++)
			{
				if((AlphaBuf[t]==PasswordAed[t])||(AlphaBuf[t]==PasswordAef[t])
               ||(AlphaBuf[t]==PassConfigAEFSBeam[t])||(AlphaBuf[t]==PassConfigAEDSBeam[t])||
               (AlphaBuf[t]==PassConfigMICROSbeam[t]))
					match++;
			}
			if(match==temp)
			{
			 //   printf("\n match");
            CChildView::LargeWaitingTime=true;			
			}

		}

      char PassConfigMicroSpecial[]="101134290";
      char PassConfigMicroOriginal[]="159134348";

		temp=length_pass-4;
		if(temp == 9)
		{
			int match=0;
			for(int t=0;t<temp;t++)
			{
				if((AlphaBuf[t]==PassConfigMicroSpecial[t])
             ||(AlphaBuf[t]==PassConfigMicroOriginal[t]))
					match++;
			}
			if(match==temp)
			{
			 //   printf("\n match");
            CChildView::LargeWaitingTime=true;			
			}

		}
      
      char PasswordVelocityOn[]="6060099456";
		char PasswordVelocityOff[]="6030399654";
      int templen=length_pass-4;
		if(templen == 10)
		{
			int match=0;
			for(int t=0;t<temp;t++)
			{
				if((AlphaBuf[t]==PasswordVelocityOn[t])||(AlphaBuf[t]==PasswordVelocityOff[t]))
					match++;
			}
			if(match==templen)
			{
			   VelocityOn=true;			
			}

		}

      char PasswordStringDebugOn[]="101";
		char PasswordStringDebugOff[]="102";
      templen=length_pass-4;
		if(templen == 3)
		{
			int match=0;
			for(int t=0;t<temp;t++)
			{
				if(AlphaBuf[t]==PasswordStringDebugOn[t])
					match++;
			}
			if(match==templen)
			{
			   TempFlagDebugOn=true;			
			}
         match=0;
         for( t=0;t<temp;t++)
			{
            if(AlphaBuf[t]==PasswordStringDebugOff[t])
               match++;
         }
         if(match==templen)
			{
			   TempFlagDebugOff=true;			
			}

		}

	}

	for(int q=0;q<length_pass;q++)
		TRACE(_T("data is ********%d"),data[q]);
	unsigned char * pass_data = (unsigned char *) &data[0];
	Index=-1;
	CHostCommand * request = new CHostCommand(FunID, pass_data, length_pass);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		pass_data = response->GetData();//Getting Data.
		int length = response->GetDataLength();//Getting Length.
//		printf("\n length in receieve=%d",length);
      char ch=CHostCommand::AckNak();
		if(ch==ACK)
		{
//		printf("\n Ack in password");
         OnKeypadScreen_flag=false;
			ErrorDisplayed = false;
			if(length>0)
			{
			//   printf("\n length>0");
            IsPassword_Accepted = *pass_data++;length--;
//            printf("\n IsPassword_Accepted=%d",IsPassword_Accepted);
            CString MessageString,Temprory;
           //char TempArray1[10];
            if(IsPassword_Accepted==1)
            {
               /*int ID=CVgaMenuItem::Convert_Char_To_Integer(pass_data,length,2);
               Temprory=_itoa(ID,TempArray1,10);
              // Temprory=_itoa(PASSACCEPTID,TempArray1,10);
               MessageString=CVgaMenuItem ::LinearSearch(Temprory);*/
               MessageString=CChildView::thisPtr->Str_PassAccp;
               if(PassWordMenu!="")
               {
                  CVgaMenu * menu;
                  theApp.menuName = PassWordMenu;
                  if(PassWordMenu != CVgaBottomMenu::WeldResults_ID)
                     CChildView::RunResultScreen=false;
                  
                  if (theApp.menus.Lookup(theApp.menuName, menu))
		            {
                      theApp.MenuPointer=menu;
                  }
               }
            }
            else if(IsPassword_Accepted==2)
            {
               /*int ID=CVgaMenuItem::Convert_Char_To_Integer(pass_data,length,2);
               Temprory=_itoa(ID,TempArray1,10);
              // Temprory=_itoa(PASSREJID,TempArray1,10);
               MessageString=CVgaMenuItem ::LinearSearch(Temprory);*/
               MessageString=CChildView::thisPtr->Str_PassRej;
            }
            else if(IsPassword_Accepted==3)
            {
               /*int ID=CVgaMenuItem::Convert_Char_To_Integer(pass_data,length,2);
               Temprory=_itoa(ID,TempArray1,10);
               //Temprory=_itoa(SECRETFUNID,TempArray1,10);
              // CString Temp=_itoa(EXECUTEID,TempArray1,10);
               MessageString=CVgaMenuItem ::LinearSearch(Temprory);//+ " " +CVgaMenuItem ::LinearSearch(Temp);*/
               MessageString=CChildView::thisPtr->Str_Secret;
            }
            switch(IsPassword_Accepted)
            {
            case 1:
            case 2:
               {
				      CVgaMenuItem::DrawRect(pDC, CChildView::Back_Color, CRect(0,40,640,440));
				      CVgaMenuItem::DrawRect(pDC, Black, CRect(119,119,521,361));
				      CVgaMenuItem::DrawRect(pDC, Blue,MessageRect  );
				      CVgaMenuItem::DrawText(pDC, Bigfont, White, MessageRect,
																      MessageString,true);
				      view->DisableFlag = true;
				      ErrorDisplayed = true;
                 // view->Invalidate ();
                  CChildView::InitialiseTimer(PasswordTimer,MESSAGESCRNTIME);
               }
               break;
            case 3:
            {
               CVgaMenuItem::DrawRect(pDC, CChildView::Back_Color, CRect(0,40,640,440));
				   CVgaMenuItem::DrawRect(pDC, Black, CRect(119,119,521,361));
				   CVgaMenuItem::DrawRect(pDC, Blue,MessageRect  );
				   CVgaMenuItem::DrawText(pDC, Bigfont, White, MessageRect,
																   MessageString,true);
				   view->DisableFlag = true;
				   ErrorDisplayed = true;
              // view->Invalidate ();
               theApp.GetSystemVariable();
               view->ModifyObjectList(theApp.MenuPointer);
               CChildView::InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
             }
            break;
            case 4:
               {
                  int ID=CVgaMenuItem::Convert_Char_To_Integer(pass_data,length,2);
                  //printf("\n Id in case4=%d",ID);
                  char TempArray[10];
				      CString Temp=_itoa(ID,TempArray,10);
                  CVgaMenu * menu;
                  if (theApp.menus.Lookup(Temp, menu))
		            {
			            view->menusname.AddTail(theApp.menuName);
                     view->menus.AddTail(page_no);
                     view->menupointers.AddTail(theApp.MenuPointer);
                     page_no=1;
                     theApp.GetSystemVariable();
                     view->ModifyObjectList(menu);   
			            theApp.menuName = Temp;
                     theApp.MenuPointer=menu;
                     view->Invalidate();
		            }	
               }
               break;
            }
            /*CVgaMenu * menu;
            if (theApp.menus.Lookup(theApp.menuName, menu))
		      {
			      page_no=1;  
               printf("\n menu found");
               CChildView::thisPtr->ModifyObjectList(menu);
               theApp.GetSystemVariable();
			   }*/
           
            /*if (theApp.menus.Lookup(theApp.menuName, menu))
		      {
			      page_no=1;
               CChildView::thisPtr->ModifyObjectList(menu);   
			   }*/
            while (view->keypadList.GetCount())
						delete view->keypadList.RemoveHead();
			 //  view->Invalidate();
            /*	if(FunID ==GetPasswordMenus_FunId)
				{
					int TimeForMessage = CScreenObject::Convert_Char_To_Integer(pass_data,length,CORDLENGTH);
					IsPassword_Accepted = *pass_data++;
					CString MessageString = CScreenObject::GetString(pass_data,length);
					CScreenObject::DrawRect(pDC, CChildView::Back_Color, CRect(0,40,640,440));
					CScreenObject::DrawRect(pDC, Black, CRect(119,119,521,361));
					CScreenObject::DrawRect(pDC, Blue,MessageRect  );
					CVgaMenuItem::DrawText(pDC, Bigfont, White, MessageRect,
																	MessageString,true);
					view->DisableFlag = true;
					ErrorDisplayed = true;
					CChildView::InitialiseTimer(PasswordTimer,TimeForMessage);
				}
				else
				{
					int type = *pass_data++;*pass_data--;
					if(type ==CScreenObject::VGAMsgScrnObject)
					{	
			 			while(view->menuEntryList.GetCount()>2)
							delete view->menuEntryList.RemoveTail();
						while (length>0)
						{
							CScreenObject * object = CScreenObject::CreateObject(pass_data, length,view);
							view->menuEntryList.AddTail(object);
						}
						CScreenObject::DrawRect(pDC, CChildView::Back_Color, CRect(0,40,640,440));
						if(FunID==SetPassword_FunId)
						{

							view->GetWeldDataIdArray(true);
							view->GetGraphWeldDataIdArray(true);
						}
					}
					/*else if(type ==CScreenObject::VGAPointerObject)//Branson Menu
					{
						CScreenObject * object = CScreenObject::CreateObject(pass_data, length,view);
						view->BuildMenu(GetMenuData_FunId,CScreenObject::VGAPointer);

					}
					
				}*/
			 }
         
		}
		else	//nak
      {
   //		printf("\n nak in password");
         view->ProcessNak(pass_data,length,pointer,ID_type);
      }
		delete response;
	}
  // printf("\n process complete");
   if((CChildView::LargeWaitingTime==true)||(VelocityOn==true))
   {
      theApp.GetSystemVariable();
      view->GetWeldDataIdArray(true);
		view->GetGraphWeldDataIdArray(true);
   }
   else 
   {
      if(TempFlagDebugOn)
         CChildView::thisPtr->StringDebugFlag=true;
      else if(TempFlagDebugOff)
         CChildView::thisPtr->StringDebugFlag=false;
   }

	CChildView::LargeWaitingTime=false;
}

/*******************************************************/
/*                                                     */
/*   Initialized all the variables for Keypad screen.  */
/*   .											       */
/*******************************************************/
void CScreenKeypad::InitializedValues()
{
	for(int len=0;len<(LINESIZE+1);len++)
		AlphaBuf[len] = NULL;

	TotalDigits=0;
	EditLine[LINESIZE] = 0;
	TypedVal = 0;
	DPFlag = FALSE;
	DecimalCount = 0;
	DigitCounter = 0;
	TotalDigits = 0;
	MaxDigitFlag = FALSE;
	EditLine[0]='\0';
	FIRSTKEYPRESS FirstKeyPress = CScreenKeypad::KEY_NONE;	
	PrevPressedAlphaNumKey=CScreenKeypad::KEYPAD_NONE;
	Index=0;             
	MaxDigit=0;     
	KeyCount=0;          
	EntryFlag=false; 
}

/************************************************************************/
/* This function will handle Enter pressed by user on SaveScanKeypad.   */
/* Function will store the ID of scan graph to text file.				*/
/************************************************************************/
void CScreenKeypad::HandleEnterOnSaveScanKeypad(CChildView *view, CDC *pDC)
{		
	CFile f;
	CFileException e;
	CString Path;
	switch(type)
	{
		case SaveScanA:
		{
			#ifndef _WIN32_WCE
				Path = "c:\\HornScanA.txt";
			#else
				Path = _T("Disk\\HornScanA.txt");
			#endif
		}
		break;
		case SaveScanB:
		{
			#ifndef _WIN32_WCE
				Path = "c:\\HornScanB.txt";
			#else
				Path = _T("Disk\\HornScanB.txt");
			#endif
		}
		break;
		case SaveScanC:
		{
			#ifndef _WIN32_WCE
				Path = "c:\\HornScanC.txt";
			#else
				Path = _T("Disk\\HornScanC.txt");
			#endif
		}
		break;
	}
	if( !f.Open( Path,CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
		#ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE("\n !! GENERIC");
		else if(e.m_cause==CFileException::badPath   )
			TRACE("\n !! bad path");
		else if(e.m_cause==CFileException::tooManyOpenFiles    )
			TRACE("\n !! too many files open");
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE("\n !! file not found");
		else if(e.m_cause==CFileException::accessDenied       )
			TRACE("\n !! access denied");
		else if(e.m_cause==CFileException::diskFull      )
			TRACE("\n !! disc full");
		else if(e.m_cause==CFileException::invalidFile   )
			TRACE("\n !! invalid file");
		afxDump << "File could not be opened " << e.m_cause << "\n";
		#endif
	}
	else
	{
		int length =2;
		unsigned char data1[2];
		data1[0]=(char)ID_type;//HornScan_RequestValue;
		data1[1]=(char)0;
		unsigned char * data = (unsigned char *) &data1[0];

		CHostCommand * request = new CHostCommand(GetWeldData_FunID/*GetWeldResults_FunId*/, data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			char ch=CHostCommand::AckNak();
			data = response->GetData();//Getting Data.
			 length = response->GetDataLength();//Getting Length.
			 if(ch==ACK)//If Ack.
			 {		
				unsigned char *c =new unsigned char[length];
				unsigned char * alpha_data ;
				int length_alpha=0;
				while(AlphaBuf[length_alpha]!='\0')
			  		length_alpha++;
				alpha_data =new unsigned char[length_alpha+4];
			//	alpha_data[0]=(unsigned char)CChildView::Language_Index;
				/*alpha_data[1]*/alpha_data[0]=(unsigned char)length_alpha;
				for(int J=1/*2*/;J<=length_alpha+1;J++)
					alpha_data[J]=(unsigned char)AlphaBuf[J-1/*2*/];
				alpha_data[length_alpha+1/*2*/]='\0';

				for(int i=0;i<length;i++)
				c[i]=*data++;
				f.Write(alpha_data,length_alpha+1/*2*/);
				LONG IDLength =length_alpha+1/*2*/;
				f.Seek(IDLength, CFile::begin );
				f.Write(c,length);
				delete []c;delete []alpha_data;
			 }
		}
		f.Close();
	}
//	view->PopMenu(true);
	view->Invalidate();
}


void CScreenKeypad::SetVariableStrings(CXmlElement * e)
{
	POSITION pos = e->children.GetHeadPosition();
	while (pos)
    {
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		CString Temp=element->GetAttribute("stringId");
		if (tag == "variable1")
      {
			StrME_4ID=Temp;
         StrME_4=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="variable2")
      {
			StrME_5ID=Temp;
         StrME_5=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="variable3")
      {
			StrME_1ID=Temp;
         StrME_1=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="variable4")
      {
			StrME_2ID=Temp;
         StrME_2=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="variable5")
      {
			StrME_3ID=Temp;
         StrME_3=CVgaMenuItem ::LinearSearch(Temp);
      }
		else if(tag=="variable6")
      {
			Str_ReenterID=Temp;
         Str_Reenter=CVgaMenuItem ::LinearSearch(Temp);
      }
      else if(tag=="variable7")
			CChildView::thisPtr->StrPage=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable8")
      {
			StrPassTitleID=Temp;
         StrPassTitle=CVgaMenuItem ::LinearSearch(Temp);
      }
      else if(tag=="variable9")
      {
			StrEnterPassID=Temp;
         StrEnterPass=CVgaMenuItem ::LinearSearch(Temp);
      }
      else if(tag=="variable10")
      {
			StrConfirmPassID=Temp;
         StrConfirmPass=CVgaMenuItem ::LinearSearch(Temp);
      }
      else if(tag=="variable11")
			CChildView::thisPtr->CycleCountString=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable12")
      {
			StrPassIncorrectID=Temp;
         StrPassIncorrect=CVgaMenuItem ::LinearSearch(Temp);
      }
      else if(tag=="variable13")
      {
			HornTitleID=Temp;
         CChildView::thisPtr->Str_HornId=CVgaMenuItem ::LinearSearch(Temp);
      }
      else if(tag=="variable14")
      {
			Str_OffID=Temp;
         Str_Off=CVgaMenuItem ::LinearSearch(Temp);
      }
      else if(tag=="variable15")
			CChildView::thisPtr->PrinterPower_str_Online=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable16")
			CChildView::thisPtr->PrinterPower_str_Offline=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable17")
			CChildView::thisPtr->Str_Save=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable18")
			CChildView::thisPtr->Str_Exit=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable19")
			CChildView::thisPtr->Str_PassAccp=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable20")
			CChildView::thisPtr->Str_PassRej=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable21")
			CChildView::thisPtr->Str_Secret=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable22")
			CChildView::thisPtr->Str_Parallel=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable23")
			CChildView::thisPtr->Str_Series=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable24")
         CChildView::thisPtr->Str_PMCGraphs=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable25")
         CChildView::thisPtr->StrCurrent=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable26")
         CChildView::thisPtr->Str_PwrAvg=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable27")
         CChildView::thisPtr->Str_PMCWeld=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable28")
         CChildView::thisPtr->Str_PMCCycles=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable29")
         CChildView::thisPtr->Str_NoValidGraph=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable30")
         CChildView::thisPtr->Str_Frequency=CVgaMenuItem ::LinearSearch(Temp);
      else if(tag=="variable31")
         CChildView::thisPtr->Str_DigitalTuneSett=CVgaMenuItem ::LinearSearch(Temp);
		else
			ASSERT(FALSE);
	}
}

void ForceGraphPrintSample(int Address)
{
 //  printf("\n ForceGraphPrintSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
//		printf("\n  disable");
      ForceGraph.PrintSampleDisable=true;//value is dissabled
   }
	else
	{
//		printf("\n not disable");
      ForceGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
		   ForceGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		ForceGraph.PrintSampleValue	=VarInfo.NewVal;
		ForceGraph.PrintSampleDisable	=false;
	}
}

void DistanceGraphPrintSample(int Address)
{
 //  printf("\n DistanceGraphPrintSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
//		printf("\n  disable");
      ColDistance.PrintSampleDisable	=true;//value is dissabled
   }
	else
	{
//		printf("\n not disable");
      ColDistance.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
		   ColDistance.BaseCount=CChildView::thisPtr->UniversalCount;
		ColDistance.PrintSampleValue	=VarInfo.NewVal;
		ColDistance.PrintSampleDisable	=false;
	}
}

void AmplitudeGraphPrintSample(int Address)
{
//	printf("\n AmplitudeGraphPrintSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
//		printf("\n disable");
      AmplitudeGraph.PrintSampleDisable=true;//value is dissabled
   }
	else
	{
//		printf("\n not disable");
      AmplitudeGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
			AmplitudeGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		AmplitudeGraph.PrintSampleValue=VarInfo.NewVal;
		AmplitudeGraph.PrintSampleDisable=false;
	}	
}

void PowerGraphPrintSample(int Address)
{
//	printf("\n PowerGraphPrintSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
//		printf("\n disable");
      PowerGraph.PrintSampleDisable=true;//value is dissabled
   }
	else
	{
//		printf("\n not disable");

      PowerGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
			PowerGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		PowerGraph.PrintSampleValue=VarInfo.NewVal;
		PowerGraph.PrintSampleDisable=false;
	}

}

void VelocityGraphPrintSample(int Address)
{
//   printf("\n VelocityGraphPrintSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
//	   printf("\n disable");
      VelocityGraph.PrintSampleDisable=true;//value is dissabled
   }
	else
	{
//		printf("\n not disable");
      VelocityGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
			VelocityGraph.BaseCount=CChildView::thisPtr->UniversalCount;
	   VelocityGraph.PrintSampleValue	=VarInfo.NewVal;
		VelocityGraph.PrintSampleDisable=false;
	}

}

void WeldHistoryPrintSample(int Address)
{
//   printf("\n WeldHistoryPrintSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
//		printf("\n disable");
      WeldHistory.PrintSampleDisable=true;//value is dissabled
   }
	else
	{
//		printf("\n not disable");
      WeldHistory.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
			WeldHistory.BaseCount=CChildView::thisPtr->UniversalCount;
		WeldHistory.PrintSampleValue	=VarInfo.NewVal;
		WeldHistory.PrintSampleDisable=false;
	}

}


void SetUpPrintSample(int Address)
{
 //  printf("\n SetUpPrintSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
 //     printf("\n disable");
		Setup.PrintSampleDisable=true;//	value is dissabled
   }
	else
	{
//		printf("\n not disable");
      Setup.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
		   Setup.BaseCount=CChildView::thisPtr->UniversalCount;
		Setup.PrintSampleValue=VarInfo.NewVal;
		Setup.PrintSampleDisable=false;
	}

}

void SequencePrintSample(int Address)
{
//	printf("\n SequencePrintSample");    
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
//		printf("\n value is disabled");
      PrintSequence.PrintSampleDisable=true;//	value is dissabled
   }
	else
	{
//		printf("\n value is not disdabled");
      PrintSequence.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
			PrintSequence.BaseCount=CChildView::thisPtr->UniversalCount;
		PrintSequence.PrintSampleValue=VarInfo.NewVal;
		PrintSequence.PrintSampleDisable	=false;
	}
}

void FrequencyGraphPrintSample(int Address)
{
 //  printf("\n FrequencyGraphPrintSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
   {
//		printf("\n disable");
      FrequencyGraph.PrintSampleDisable=true;//	value is dissabled
   }
	else
	{
//		printf("\n not disable");
      FrequencyGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		if(CChildView::thisPtr->ExtPreset)
			FrequencyGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		FrequencyGraph.PrintSampleValue=VarInfo.NewVal;
		FrequencyGraph.PrintSampleDisable	=false;
	}

}

void WeldSummaryPrint(int Address)
{
 //  printf("\n WeldSummaryPrint");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
	if(ptr->KeyOffFlag)
   {
//	   printf("\n disable");
      Welddata.PrintSampleDisable=true;//	value is dissabled
   }
	else
	{					
//		printf("\n not disable");
      Welddata.BaseCount=CChildView::thisPtr->UniversalCount+1-VarInfo.NewVal;
		if(CChildView::thisPtr->ExtPreset)
			Welddata.BaseCount=CChildView::thisPtr->UniversalCount+1-VarInfo.NewVal;
		Welddata.PrintSampleValue=VarInfo.NewVal;
		Welddata.PrintSampleDisable=false;
		
	}
}

void WeldPerPagePrint(int Address)
{
 //  printf("\n WeldPerPagePrint");
   PrintSetup.WeldsPerPage=VarInfo.NewVal;
}


void USBForceSampleGraph(int Address)
{
//   printf("\n USBForceSampleGraph");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
		USBForceGraph.USBSampleDisable=true;//value is dissabled
	else
	{
		USBForceGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBForceGraph.USBSampleValue	=VarInfo.NewVal;
		USBForceGraph.USBSampleDisable	=false;
		
	}
}

void USBColDistanceGraph(int Address)
{
//   printf("\n USBColDistanceGraph");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
		USBColDistance.USBSampleDisable	=true;//value is dissabled
	else
	{
		USBColDistance.BaseCount=CChildView::thisPtr->UniversalCount;
		USBColDistance.USBSampleValue	=VarInfo.NewVal;
		USBColDistance.USBSampleDisable	=false;
		
	}
}

void USBAmplitudeGraphSample(int Address)
{
//   printf("\n USBAmplitudeGraphSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
		USBAmplitudeGraph.USBSampleDisable=true;//value is dissabled
	else
	{
		USBAmplitudeGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBAmplitudeGraph.USBSampleValue=VarInfo.NewVal;
		USBAmplitudeGraph.USBSampleDisable=false;
		
	}
}

void USBPowerGraphSample(int Address)
{
//   printf("\n USBPowerGraphSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
		USBPowerGraph.USBSampleDisable=true;//value is dissabled
	else
	{
		USBPowerGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBPowerGraph.USBSampleValue=VarInfo.NewVal;
		USBPowerGraph.USBSampleDisable=false;
			
	}
}

void USBVelocityGraphSample(int Address)
{
//   printf("\n USBVelocityGraphSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
	    USBVelocityGraph.USBSampleDisable=true;//value is dissabled
	else
	{
		USBVelocityGraph.BaseCount=CChildView::thisPtr->UniversalCount;
	   USBVelocityGraph.USBSampleValue	=VarInfo.NewVal;
		USBVelocityGraph.USBSampleDisable=false;
		
	}
}

void USBFrequencyGraphSample(int Address)
{
//   printf("\n USBFrequencyGraphSample");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
	   USBFrequencyGraph.USBSampleDisable=true;//	value is dissabled
	else
	{
		USBFrequencyGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBFrequencyGraph.USBSampleValue=VarInfo.NewVal;
		USBFrequencyGraph.USBSampleDisable	=false;
		
	}
}

void USBWeldData(int Address)
{
//   printf("\n USBWeldData");
   CScreenKeypad *ptr=(CScreenKeypad*)Address;
   if(ptr->KeyOffFlag)
	   USBWelddata.USBSampleDisable=true;//	value is dissabled
	else
	{					
		USBWelddata.BaseCount=CChildView::thisPtr->UniversalCount+1-VarInfo.NewVal;
		USBWelddata.USBSampleValue=VarInfo.NewVal;
		USBWelddata.USBSampleDisable=false;
		
	}
}

void ModifyPowerSupplyName(int Address)
{
    CChildView::thisPtr->GetPowerSupplyName();
}

void PrintRunScreenWeldData(int Address)
{     
//  printf("IN \n");
  CString StrM5_35;
  HistoryTemp_pos=NULL;
  RunScreenTemp_pos = tempRunScreenList.GetHeadPosition();
 // printf("A\n");
  StrM5_35=tempRunScreenList.GetNext(RunScreenTemp_pos);

  if(CChildView::thisPtr->PrinterPresent)
	  CChildView::thisPtr->ShowMessageScreen(StrM5_35);

   OnKeypadScreen_flag=true;   
   CString PrinterPower_str;
   PrinterPower_str= tempRunScreenList.GetNext(RunScreenTemp_pos);

	CScreenKeypad::NoOfWeldresult=VarInfo.NewVal;
	if(!CChildView::thisPtr->PrinterPresent)
      CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
   else
      CChildView::thisPtr->BuildPrintList(PRINT_HISTORY_DATA);
   
   while (CChildView::thisPtr->keypadList.GetCount())
	   delete CChildView::thisPtr->keypadList.RemoveHead();
   CChildView::thisPtr->Invalidate();
   //Exit = TRUE;
}

void SendVQSLimitQualityCommand(int Address)
{
   CScreenKeypad::Qualityflag=true;
   CChildView::thisPtr->MaxPreset=1;
}

void ProcessDebugMenuScreen(int Address)
{
   CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
   CChildView::thisPtr->menusname.AddTail(theApp.menuName);
   CChildView::thisPtr->menus.AddTail(page_no);
 
}
