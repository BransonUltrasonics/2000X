/* $Header:   D:/SWLab/VMdb/archives/2000 RVTS/ScreenKeypad.h_v   1.10.1.7   06 Nov 2009 17:13:16   pdwivedi  $ */
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
  1.4       05/19/05	Aare        Added complete revision header.
  1.5		   07/25/05	BWadia		Added Function for password Screen 
									      and added asian Language Strings.
  1.6		   09/19/05	BWadia		Added HSC Related Functions 
  1.7		   10/14/05	BWadia		Added Defines.
  1.8		   10/24/05	BWadia		Added DISTANCE3 in enum FORMAT 
  1.9       03/27/07 BSahu       Added Declaration For QualityFlag.
  1.10      05/23/07 BSahu       Added Declaration For NoOfWeldresult
  1.10.1.0  10/23/07 PDwivedi    Make ConvertInternalExternal function Static for MultiLang Support.
  1.10.1.1  01/11/08 PDwivedi    Added Function declartions.
  1.10.1.2  04/04/08 PDwivedi    Added Member Variables.
  1.10.1.3  04/14/08 PDwivedi    Added Member Variables for MutiLangSupprt.
  1.10.1.4  08/01/08 PDwivedi    Added Member Variables for Local Strings.
  1.10.1.5  08/08/08 PDwivedi    Final Code Clean up.
  1.10.1.6  08/26/08	PDwivedi    Added FunName for AlplhaNumeric Item.
  1.10.1.7  11/06/09 PDwivedi    Added changes for showing String Number.

*/

// ScreenKeypad.h: interface for the CScreenKeypad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENKEYPAD_H__8177D0BE_80C4_484F_A575_4D65FB2CFCBF__INCLUDED_)
#define AFX_SCREENKEYPAD_H__8177D0BE_80C4_484F_A575_4D65FB2CFCBF__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChildView;

#define	TOTAL_KEYPAD_COLOUMN	3
#define TOTAL_KEYPAD_ROW		5
#define DAYCHAR			2
#define LEAPYEARVALUE	29
#define MAXTIMECHAR		5
#define MAXDATECHAR		8
#define NUL             0x00
#define LINESIZE        20
#define MinLimit_Year   0                     
#define MinLimit_Month  1                   
#define MinLimit_Day    1                    
#define MinLimit_Hour   0                     
#define MinLimit_Minute 0   
#define MaxLimit_Year   99                      
#define MaxLimit_Month  12                                                   
#define MaxLimit_Day    31                                                     
#define MaxLimit_Hour   23                                                    
#define MaxLimit_Minute 59  
#define CENTURY         2000  
#define NULL_PTR        0L  
#define Bounding_Rect				CRect(100, 44,536,418)
#define Current_Value_Rect			CRect(118,100,294,136)
#define New_Value_Rect				CRect(118,180,294,216)
#define Keypad_Title_Rect			CRect(100, 48,536, 65)
#define Current_Value_String_Rect	CRect(118, 75,235,100)
#define New_Value_String_Rect		CRect(118,155,235,180)
#define Button_Off_Rect				CRect(176,354,234,412)
#define Error_rect					CRect(104,232,320,350)
#define Error_Str_rect				CRect(104,232,320,271)
#define Min_Value_Str_rect			CRect(120,271,320,310)
#define Max_Value_Str_rect			CRect(120,310,320,350)
#define OFF_Rect					CRect(176,354,234,412)
#define MessageRect					CRect(120,120,520,360)
#define Left_Of_Keys			326
#define	Top_CoOrdinate_Key		74
#define	Width_Of_Key	58
#define	Gap_Of_Key		12
#define COLDSTART_INPROCESSID  307

class CVgaMenuItem;
class CXmlElement;

class CScreenKeypad  
{
public:
   bool KeyOffFlag;
   bool ShiftKeyEnable;
   static int NoOfWeldresult;
	static char	AlphaBuf[LINESIZE+1];       /*Original value buffer*/
	static int IsPassword_Accepted;
   static bool Qualityflag;
   static void SetVariableStrings(CXmlElement * e);
   static CString StrME_1,StrME_2,StrME_3,StrME_4,StrME_5,Str_Reenter,StrPassTitle,
      StrEnterPass,StrConfirmPass,StrPassIncorrect,Str_Off;
   static CString StrME_1ID,StrME_2ID,StrME_3ID,StrME_4ID,StrME_5ID,Str_ReenterID,
      StrPassTitleID,StrEnterPassID,StrConfirmPassID,StrPassIncorrectID,Str_OffID,HornTitleID;
   CString Str_Curr,Str_CurrID;
   CString Str_New,Str_NewID;
   CString VariableTitleID,AlphaTitleID;
   static CString TempPassword;
   CString PassWordMenu;
	CScreenKeypad(int type1,int Pointer,unsigned char *&data,CString* Object_Text);
   CScreenKeypad(int type1,unsigned char *&data,CString* Object_Text,int ID,CVgaMenuItem *ptr);
   virtual ~CScreenKeypad();
	static void VGAAlphaEntry(CDC *pDC);
	bool MouseClick(const CPoint &p, CChildView *view,CDC *pDC);
	void Draw(CDC *pDC);
	void DrawPressedkey(CPoint point, CDC *pDC);
	

	typedef   int      UINT8;  
	typedef   UINT8    BYTE;            /* 8-bit  unsigned quantity  */
	typedef   int      UINT16;          /* 16-bit unsigned quantity  */
	typedef   int      UINT32;          /* 32-bit unsigned quantity  */
	typedef   char     SINT8;           /* 8-bit  signed quantity    */
	typedef   int      SINT16;          /* 16-bit signed quantity    */
	typedef   int      SINT32;     

	enum ERRORCODES
			{
				TIMERFAILED1 = 1,    /* No timers available             */
                TIMERFAILED2,        /* Time requested was 0            */
                MINRANGE,
                MAXRANGE,
                IDXRANGE,            /* Index out of range              */
                PTRRANGE,            /* Pointer out of range            */
				NOVALUE	,			/* No value entered after ClearKey */
				PassInvalid
			};          

	enum KEYPADID 
		{
			KEYPAD_0 = 0,
			KEYPAD_1,
			KEYPAD_2,
			KEYPAD_3,
			KEYPAD_4,
			KEYPAD_5,
			KEYPAD_6,
			KEYPAD_7,
			KEYPAD_8,
			KEYPAD_9,
			KEYPAD_INC,
			KEYPAD_DEC,
			KEYPAD_ESC,
			KEYPAD_POINT,
			KEYPAD_ENT,
			KEYPAD_OFF,
			KEYPAD_NONE,
		};
	
	enum FORMAT {                     /*  US Format (units)  SI Format (units) */
	   PERCENT,                       /*        xxx     %          xxx     %   */
	   FORCE,                         /*       xxxx    lb         xxxx     N   */
	   FORCEDIV10,                    /*     xxxx.x    lb         xxxx     N   */
	   TIME,                          /*     xx.xxx     S       xx.xxx     S   */
	   PRESSURE,                      /*        xxx    PSI         xxx   KPA   */
	   DISTANCE,                      /*     x.xxxx    in      xxx.xxx    mm   */
	   DISTANCE3,                     /*     x.xxxx    in       xx.xxx    mm   */
	   FREQUENCY,                     /*      xxxxx    Hz        xxxxx    Hz   */
	   FREQOFFSET,                    /*       Sxxx    Hz         Sxxx    Hz   */
	   ENERGY,                        /*     xxxxxx     j       xxxxxx     j   */
	   COUNTER,                       /*  xxxxxxxxx          xxxxxxxxx         */
	   VELOCITY,                      /*      xx.xx  in/s        xxx.x  mm/s   */
	   WATTS,                         /*      xxxx   W            xxxx  W      */
	   BARGRAPH,                      /* [____|____]        [____|____]        */
	   TIMEDATE,                      /* xx:xx xx/xx/xx                        */
	   PERCENTX10,
	   ENERGYDIV10,
	   INTEGER,
	   LONGTIME,
	   MICRONS,
	   POWERWATTS
	};
	enum FORMAT_AMP_PWR {  
		POWER,
		MIC
	};

	enum FIRSTKEYPRESS
	{
		KEY_NONE = 0,
		KEY_INC_DEC,
		KEY_NUMBER,
		KEY_OFF,
	};

	struct var_format_def1
	{
		SINT8   Units[5];       /* Name of units, up to 4 chrs */
		UINT8   LeftDigits;     /* Max # of digits left of decimal point */
		UINT8   RightDigits;    /* # of digits right of decimal point */
		UINT8   Increment;      /* Change in value with + or - keypress */
		BOOLEAN ShowSign;       /* TRUE to display + or - sign */
		SINT32  ConvMult;       /* Conversion multiplier */
		SINT32  ConvDiv;        /* Conversion divisor */
	};

	struct var_format_def2
	{
		struct var_format_def1 English;
		struct var_format_def1 Metric;
	};
	struct var_format_AmpPower
	{
		struct var_format_def1 Percent;
		struct var_format_def1 Unit;
	};
static struct VInf
	{
		int		Length	;				//	Text length in characters
		CString Keypad_title;			//	string, total count Length * BytesPerChar
		UINT16		Format	;			//	Variable format, enum FORMAT
		UINT16		Digits	;			//	Number of digits to display
		bool		Metric	;			//	TRUE - use metric formatting
		SINT32		Value;				//	Current value
		SINT32		MinVal	;			//	Minimum value
		SINT32		MaxVal	;			//	Maximum value
		SINT32		ID	;				//	Variable ID
		SINT16		Disable	;			//	TRUE if variable can be disabled
		SINT16		Disableflag ;		//	flag	Pointer to disable/enable flag
		SINT16		Bitmask	;			//	Bit used for this variable enable
		SINT32		NewVal;				//	
		int			 Sign;				//	 +-1 for formats which show sign, else 0 */
		UINT8		 Size;				/* Max # of chrs in ASCII representation */
		UINT16		StartPos;			/* Position on line where # should appear */
      CString    FunName;
	};
	struct AInf
	{
		CString Alpha_Keypad_title;
		CString		Current_Alpha_Value;
		int		MaxLength;
		bool	Hide;
		int		PARAM_ID;
      CString MenuNak;
      CString MenuAck;
      CString    FunName;
	 };

	struct ALPHA_NUM_KEY
	{
	  int NumChar;
	  SINT8  CharValue[5];
	};
static int ConvertInternalExternal( SINT32 Value, enum FORMAT format );
static int ConvertExternalInternal( SINT32 Number, enum FORMAT format );
static void FormatNum(SINT32 Number,  char String[] );
static CString FormatNumber(SINT32 Number,  char String[] ,enum FORMAT format,bool ChkUnitflag,bool Insertunitflag1);
static bool InsertProperUnits(CVgaMenuItem *ptr,enum FORMAT format,int type);
static CString InsertWeldParamUnit(CString string,enum FORMAT format);
static CString InsertWeldParamUnitsString(bool metric,enum FORMAT format);
protected:

	CScreenKeypad();
	enum 
	{
		ACK = 0x06,
		NAK = 0x15
	};


private:
	//static CString StrWeldsPerPage[9];
//	static CString StrME_4[9];
//	static CString StrME_5[9];
//	static CString  Str_Reenter[9];
//	static CString 	StrInvalidEntry[9];
	static int pointer;
	static bool pressed;
	static bool OnKeypadScreen; 
	static bool ErrorDisplayed;
	static CRect PressedKeyRect;
	static int		PrevPressedAlphaNumKey;
	static int		MaxDigit;
	static int		TypedVal ;
    static int		DecimalCount;
    static int		DigitCounter;
    static int		TotalDigits ;
	static int    KeyCount; 
	static int    Index;  
	static bool  EntryFlag;       /*TRUE when value is entered successfully.*/
    static bool		MaxDigitFlag ;
	static bool		DPFlag;
    static char		EditLine[LINESIZE];
	static char		FILLCHAR;
	static char	OutputLine[LINESIZE+1];      /*Display buffer char displayed'*'-*/
                                             /*   in case of Password Entry*/
	
	char Temp_Str[21];
	char buffer[25];
	CString* Object_Text_pointer;
	int PresetPointer;
	int type;
   int ID_type;
	void SendCommandForPassword(CChildView *view,int FunID,CDC *pDC);
	void HandleEnterOnPassword(CChildView *view,CDC *pDC);
	void HandleEnterOnSaveScanKeypad(CChildView *view,CDC *pDC);
	void CopyString(char *dest,char   *source);
	void VGADisplayCurrentNewValue(CDC *pDC);
	void DisplayVGAMinMax(CDC *pDC);
	void ConvertVariableFormat(enum FORMAT Format1,enum FORMAT Format2);
	void VGAVarEntryIncDecMode(int KeyPressed,CDC *pDC);
	void UpdateDateIfValid(CDC *pDC);
	
	void Draw_Pressed_Released_Button(CDC *pDC,CRect rect);
	void OffsetRect(CDC *pDC, CRect rect, COLORREF col);
	void VGADateEntry( int KeyPressed,CDC *pDC);
	void VGATimeEntry(int KeyPressed,CDC *pDC);
	void DisplayVGAMinMaxError(enum ERRORCODES ECode,CDC *pDC);
	void VGAAlphaEntryMode(int KeyPressed,CChildView *view,CDC *pDC);
	void UpdateTimeIfValid(CDC *pDC);
	static void DrawString(CDC *pDC, char string[20]);
	

	char* SplitString(char Split_Str[],char Split_Char[], char Splited_Str[]);
	bool ProcessPressedAlphakey(int KeyPressed,int type,CChildView *view,CDC *pDC);
	bool VGAVarEntryMode( int KeyPressed,CDC *pDC,CChildView *view );
	bool ProcessKeypad(int x, int y, CChildView *view,CDC *pDC);
	bool CheckForLeapYear(int  Year);
	bool CheckForValidDate(char* OutputLine,int Day, int Month,int Year);
	
	int myatoi(char s[]);
	int GetInteger(unsigned char *&data, int bytes);
	int VarSize(enum FORMAT format);
	
	void InitializedValues();
};

#endif // !defined(AFX_SCREENKEYPAD_H__E92BFF74_AA6F_11D9_B39E_00B0D02A48D6__INCLUDED_)
