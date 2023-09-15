// EnumCondition.cpp: implementation of the CEnumCondition class.
//
//////////////////////////////////////////////////////////////////////
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
  1.0       10/23/07	   PDwivedi  Added Initial Version.
  1.1       01/11/08    PDwivedi  Added cases to Evaluate(). 
  1.2		   04/04/08	   PDwivedi  Modify Evaluate For MultiLang Support.
  1.3       04/14/08    PDwivedi	 Adding condition for Coldstart in  MultiLang Support.
  1.4       06/06/08    PDwivedi	 Modified Evaluate for function execution while checking condition.
  1.5       06/12/08    PDwivedi	 Modified AddPowerGraph & SendCommandForViewGraph for Graph & PMC Screen.
  1.6       08/01/08    PDwivedi  Added new function for USB & printing.
  1.7       08/04/08    PDwivedi  Added new function for Color setup screen.
  1.8       08/08/08    PDwivedi  Final Code Clean up.
  1.9       08/26/08	   PDwivedi  Modify Evaluate() for handling Nck.
  1.10      09/02/08    PDwivedi  Modify ProcessAlarmMenu for Reset Button.
  1.11      09/09/08    PDwivedi  Added changes for Tracker issues.
  1.12      09/12/08    PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
  1.13      10/01/08    PDwivedi	 Modified Evaluate for calibration BUG00422.
  1.14      11/07/08    PDwivedi  Added changes for Controllevel & Actuator issues.
  1.15      09/22/09    PDwivedi  Modify Evaluate() for Micro Actuator.
  1.16      09/25/09    PDwivedi  Modify GetPSPresetScrn,GetCurrentPresetScrn function 
                                  for View current Preset screen bug.
  1.17      11/06/09    PDwivedi  Added changes for Graph Screen Fatal Bug .
  1.18      11/18/09    PDwivedi  Added changes for Updating AlarmUpdateRequired Flag.
  1.19      10/13/10    PDwivedi  Added new Member like AddStartUpVersion,AddSystemVersion and
                                  and GetNKBinDate.
*/

#include "stdafx.h"
#include "SBC.h"
#include "EnumCondition.h"
#include "Variable.h"
#include "HostCommand.h"
#include "VgaMenuItem.h"
#include "VgaMenu.h"
#include "Toggle.h"
#include "Text.h"
#include "VgaVariable.h"
#include "ScreenKeypad.h"
#include "Date.h"
#include "Time.h"
#include "VgaChoice.h"
#include "RadioMenu.h"
#include "VgaButton.h"
#include "ListBox.h"
#include "VgaAlphanumeric.h"
#include "VgaSubMenu.h"
#include "BottomHalf.h"
#include "VgaRadioButton.h"
#include "VgaBottomMenu.h"
#include "RunScreen.h"
#include "WeldingHistory.h"
#include "LocalChoice.h"
#include "VgaViewPreset.h"
#include "TextBox.h"
#include "VgaTitle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CChildView::PrintingSetup PrintSetup;
extern void SetGraphObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph);

CEnumCondition::CEnumCondition()
{

}

CEnumCondition::~CEnumCondition()
{

}

/***************************************************************************************/
/*                                                                                   */
/* Function to check Enumvariable conditions like ControlLevel,Actuator,Securitylevel 
/* and Enable Flag. 							
/*************************************************************************************/
bool CEnumCondition::Evaluate(CVgaMenuItem *item) const
{
   switch(enumflagvalue)
		{
		case 0:
		{
			item->AccessLevel=EnumValue;
			if(EnumValue> CChildView::Securitylevel)//Checking Securitylevel
			{
        										
				return false;
			}
		}
		break;
		case 1:
		{
			if(CChildView::ControlLevel < EnumValue)//Checking ControlLevel
			{
				return false;
			}
		 }
		break;
		case 2:
			{
				if (!(EnumValue & CChildView::Actuator)) //Checking Actuator
				{
					return false;
				}
			}
		break;
		case 3://Checking Enable Flag
			{
				if(EnableCommand)
				{
					int length =3;
					unsigned char data1[3];
					union 
							{
								short i;
								char c[2];
							} u;
						 u.i=StringID;
					data1[1]=u.c[0];
					data1[0]=u.c[1];
               if(EnumValue!=0)
               {
                  if((EnumValue & CChildView::Actuator)==CChildView::Actuator)
                     data1[2]=(char)CalibMenuIndexAED;
                  else
                     data1[2]=(char)CalibMenuIndex;
               }
               else
                  data1[2]=(char)0;

					unsigned char * data = (unsigned char *) &data1[0];
					//Send Command if enable flag is true
					CHostCommand * request = new CHostCommand(GetEptrVariable_FunId,data,length);
					CHostCommand * response = app->SendUiHostCommand(request);
					if(response)
					{
						char ch=CHostCommand::AckNak();
						data = response->GetData();
						length = response->GetDataLength();
						if(ch==theApp.ACK)
						{
							int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
							if(ID==!StringID)//If ID doesn't match, delete response
							{
							  delete response;
							  return false;
							}
							int Datatype=*data++;length--;
							bool Eptr;
							union 
							{
								bool i;
								char c;
							} u;
							u.c = *data++;length--;
							Eptr=u.i;
							if(Eptr==false)
							{
							delete response; 
							return false;
							}
							else
							{
            
								switch(Datatype)
								{
									case 0:// if nothing
										{
											switch(item->GetType())
											{
												case CVgaMenu::VGA_Button_OBJECT:
												{
													CVgaButton *ptr=(CVgaButton *)item;
													ptr->EnumID=ID;
												}
												break;
                                 
											}
											
										}
										break;
									case 1:
									case 2:
									{
										int OneByteValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
										
										switch(item->GetType())
										{
											case CVgaMenu::TEXT:
											{
												CText *ptr=(CText *)item;
												char TempArray[10];
												CString Temp=_itoa(OneByteValue,TempArray,10);
												ptr->text += Temp;
												ptr->EnumID=ID;
											}
											break;
											case CVgaMenu::RADIOMENU:
											{
												CRadioMenu *ptr=(CRadioMenu *)item;
												ptr->VarText= " > ";
												for(int i=0;i<=MAXRADIOITEMS;i++)
												{
													if(i==OneByteValue)
													{
														ptr->RadioIndex = OneByteValue;
														ptr->EnumID=ID;
                                          ptr->VarText = ptr->RadioMenuStr[i];
													}
												}
                                 
											}
											break;
                              }
                  
									 }
									 break;
									 case 3:
									 case 4:
										{
											int TwoByteValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
											switch(item->GetType())
											{
												case CVgaMenu::CHOICE:
												{
													CVgaChoice *ptr1=(CVgaChoice *)item;
													ptr1->EnumID=ID;
													ptr1->Choice_value=TwoByteValue;
													if(TwoByteValue)
													{
														ptr1->ChoiceText = "=" + ptr1->ChoiceText2;
													}
													else
													{
														ptr1->ChoiceText = "=" + ptr1->ChoiceText1;
													}
												}
												break;
												case CVgaMenu::TOGGLE:
												{
													CToggle *ptr=(CToggle *)item;
													ptr->EnumID=ID;
													if(TwoByteValue)
													{
														ptr->Toggle_Value=true;  
														ptr->Toggle_Text = "=" + ptr->Toggle_Text1 ;
													}
													else
													{
														ptr->Toggle_Value=false;  
														ptr->Toggle_Text = "=" + ptr->Toggle_Text2 ;
													}
                                       /*if(ptr->FunName!="")
                                       {
                                          void *ptr1;
                                          void (*rmn)(int);
                                          if(functionCall.Lookup(ptr->FunName,ptr1))
		                                    {
			                                     rmn = (void (*)(int))ptr1;
			                                     rmn(ptr->Toggle_Value);
                                          }
                                       }*/
												}
												break;
												case CVgaMenu::RADIOMENU:
												{
													CRadioMenu *ptr=(CRadioMenu *)item;
													ptr->VarText= " > ";
													ptr->EnumID=ID;
                                    
													for(int i=0;i<=MAXRADIOITEMS;i++)
													{
														if(i==TwoByteValue)
														{
															ptr->RadioIndex = TwoByteValue;
															ptr->VarText = ptr->RadioMenuStr[i];
														}
														
													}
                                    
												  
												}
												break;
												case CVgaMenu::TEXT:
												{
													char TempArray[10];
													CText *ptr=(CText *)item;
													CString Temp=_itoa(TwoByteValue,TempArray,10);
													ptr->text += Temp;
													ptr->EnumID=ID;
												}
												break;
												 case CVgaMenu::VGA_Button_OBJECT:
												{
													char TempArray[10];
													CVgaButton *ptr=(CVgaButton *)item;
												    ptr->EnumID=ID;
													CString Temp=_itoa(TwoByteValue,TempArray,10);
													ptr->SubText= Temp;	
												
												 }
												 break;
												case CVgaMenu::SUBMENU:
													{
														CChildView::CurrentPresetNum = TwoByteValue;
														if(CChildView::CurrentPresetNum ==0)
															CChildView::CurrentPresetNum =1;
                                       
													}
													break;
												case  CVgaMenu::TITLE:
													{
                                       		CChildView::CurrentSequencePreset =TwoByteValue;
                                             if(CChildView::CurrentSequencePreset==0)
                                                CChildView::CurrentSequencePreset=1;
															CListBoxObject::SequencingScreen=true;
													}
													break;
											}
										}
										break;
										case 5:
										case 6:
										{
											switch(item->GetType())
											{
												case CVgaMenu::VARIABLE:
												{
													int ShowValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
													CVgaVariable *ptr=(CVgaVariable *)item;
													if(ShowValue)
													{
														int DisableFlag=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
														int FourBytes=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
														char TempArray[LINESIZE+1]="                    ";
														ptr->NewVal = FourBytes;
														FourBytes = CScreenKeypad::ConvertInternalExternal( FourBytes,(CScreenKeypad::FORMAT)ptr->Format);
														CString Temp;
														bool Insertunitflag1=false;
														int type=item->GetType();
                                          ptr->Insertunitflag=false;
                                          
                                          Insertunitflag1=CScreenKeypad::InsertProperUnits(ptr,(CScreenKeypad::FORMAT)ptr->Format,type);
                                          ptr->Keypad_title = ptr->text ;
														int Format1=ptr->Format;
														if (ptr->Format == CScreenKeypad::ENERGY && (FourBytes >= 10000))
														{
															FourBytes = CScreenKeypad::ConvertExternalInternal( FourBytes, CScreenKeypad::ENERGY );
															FourBytes = CScreenKeypad::ConvertInternalExternal( FourBytes, CScreenKeypad::ENERGYDIV10 );
															Format1 = CScreenKeypad::ENERGYDIV10;
														}
														Temp=CScreenKeypad::FormatNumber(FourBytes,TempArray,(CScreenKeypad::FORMAT)Format1/*ptr->Format*/,ptr->Unitshow,ptr->Insertunitflag);
														Temp.TrimLeft ();
														Temp.TrimRight ();
                                    
														
														if(ptr->TextType)
														{
															ptr->Variable_Text="";
                                             ptr->text=CVgaMenuItem::GetString(data,length);
															ptr->Variable_Text+=Temp;
															ptr->Variable_Text+="W";
													   }
														else
														{
															ptr->Variable_Text="";
															
															if ((ptr->Disable))
															{
																ptr->DisableFlag=DisableFlag;
																if(((DisableFlag & ptr->Bitmask) == ptr->Bitmask))
																{
                                                   ptr->Variable_Text= " = "+ CScreenKeypad::Str_Off;
																}
																else 
																{
																	ptr->Variable_Text= " = " +Temp; 
																}
												 
															}
															else
															{
                                                
																ptr->Variable_Text= " = " +Temp;
															}
														}
														ptr->EnumID=ID;
													}
													else
													{
														ptr->EnumID=ID;
                                          int type=item->GetType();
                                          ptr->Insertunitflag=false;
													   CScreenKeypad::InsertProperUnits(ptr,(CScreenKeypad::FORMAT)ptr->Format,type);
														ptr->Variable_Text=" = "+CString("***");
													}
												}
												break;
											
											}
										}
										break;
										case 7:
										{
											switch(item->GetType())
											{
												case CVgaMenu::TOGGLE:
												{
													CToggle *ptr=(CToggle *)item;
													ptr->EnumID=ID;
													bool metric;
													union 
													  {
														  bool i;
														  char c;
													  } u;
													  u.c = *data++;length--;
														metric=u.i;
													  if(metric==true)
														{
														  ptr->Toggle_Value=true; 
														  ptr->Toggle_Text = " = "+ ptr->Toggle_Text1 ;
														}
														else
														{
															ptr->Toggle_Value=false;
															ptr->Toggle_Text = " = " + ptr->Toggle_Text2 ;
														}
                                         /* if(ptr->FunName!="")
                                          {
                                             void *ptr1;
                                             void (*rmn)(int);
                                             if(functionCall.Lookup(ptr->FunName,ptr1))
		                                       {
			                                        rmn = (void (*)(int))ptr1;
			                                        rmn(ptr->Toggle_Value);
                                             }
                                          }*/
												}
											   break;
                                 }

										}
										break;
										case 8:
											{
												switch(item->GetType())
												{
													case CVgaMenu::TEXT:
													{
														CText *ptr=(CText *)item;
														CString str=CVgaMenuItem::GetString(data,length);
														ptr->SubText = str;
														ptr->EnumID=ID;
													}
													break;
													case CVgaMenu::VGA_Button_OBJECT:
													{
														CVgaButton *ptr=(CVgaButton *)item;
														
														CString str=CVgaMenuItem::GetString(data,length);
														ptr->EnumID=ID;
														ptr->text = str;
														
													}
													break;
                                       case CVgaMenu::TITLE:
												   {
													   CVgaTitle *ptr=(CVgaTitle *)item;
                                          ptr->text=CVgaMenuItem::GetString(data,length);
												   }
												   break;
												}

											}
											break;
										case 9:
										 {
											int DateArray[20];
											char TempArray[10];
											switch(item->GetType())
											{
												case CVgaMenu::DATE:
												{
													CDate *ptr=(CDate *)item;
													int lengthofData=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
													ptr->EnumID=ID;
													if(ptr->RectShow)
														ptr->Date_Text=" > ";
													else
														ptr->Date_Text=" ";
													for(int j=0;j<lengthofData;j++)
													{
														if(j!=0)
														{
															ptr->Date_Text+="/";
														}
														DateArray[j]=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
														CString TempDay=_itoa(DateArray[j],TempArray,10);
														if(TempDay.GetLength() ==1)
															TempDay = "0"+TempDay;
														ptr->Date_Text+=TempDay;
													}
													 
												}
												break;
												case CVgaMenu::HHMM:
													{
														CVgaTime *ptr=(CVgaTime *)item;
														int lengthofData=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
														ptr->Time_Text=" > ";
														ptr->EnumID=ID;
														for(int i=0;i<lengthofData;i++)
														{
															if(i!=0)
															{
																ptr->Time_Text +=":";
															}
															DateArray[i]=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
															CString TempTime=_itoa(DateArray[i],TempArray,10);
															if(TempTime.GetLength() ==1)
																TempTime = "0"+TempTime;
															ptr->Time_Text+=TempTime;
															
														}
													}
													break;
												case CVgaMenu::VGA_LISTBOX:
													{
														CListBoxObject *ptr=(CListBoxObject *)item;
														ptr->EnumID=ID;
														if(length>1)
														{
															if(ptr->Type == PRESETINFOSCREEN)
															{
																for(int i=0;i<(ptr->TotalText-2);i++)
																{
																	ptr->ListBoxText[i]="";
																	CString Str=" : "+ CVgaMenuItem::GetString(data, length);
																	ptr->ListBoxText[i]=ptr->PresetInfoText[i] + Str;
																	ptr->ListBoxText[i].TrimLeft();
																	ptr->ListBoxText[i].TrimRight();
																}
																int PresetVerify=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
																if(PresetVerify)
																{
																	CString Str= ptr->PresetInfoText[ptr->TotalText-1] ;   
																	ptr->ListBoxText[ptr->TotalText-2]=  Str ; 
																}
																else
																{
																	CString Str = ptr->PresetInfoText[ptr->TotalText-2]; 
																	ptr->ListBoxText[ptr->TotalText-2] =  Str ;       
																}
																ptr->ListBoxText[ptr->TotalText-2].TrimLeft();
																ptr->ListBoxText[ptr->TotalText-2].TrimRight();
																ptr->ListBoxText [ptr->TotalText-1]="";
															}
															else
															{
																ptr->CurrentRunningSequencePreset=CChildView::CurrentSequencePreset ;
                                                for(int i=0;i<ptr->TotalText;i++)
																{
																	ptr->ListBoxText[i]=CVgaMenuItem::GetString(data, length);
																	ptr->ListBoxText[i].TrimLeft();
																	ptr->ListBoxText[i].TrimRight();
																 }
															}
														}
														else
														{
															for(int i=0;i<ptr->TotalText;i++)
															{
																ptr->ListBoxText[i]="";
															 }
														}
													}
													break;
												case CVgaMenu::ALPHA:
													{
														CVgaAlphanumeric *ptr=(CVgaAlphanumeric *)item;
														CString str=CVgaMenuItem::GetString(data,length);
														ptr->EnumID=ID;
														ptr->Alpha_Text = "=" + str;
														ptr->CurrentAlphaValue = str;
													}
													break;
												case CVgaMenu::TEXT:
													{
														CText *ptr=(CText *)item;
														CString str=CVgaMenuItem::GetString(data,length);
														ptr->SubText = str;
													ptr->EnumID=ID;
													}
													break;   
												case CVgaMenu::VGA_Button_OBJECT:
												{
													CVgaButton *ptr=(CVgaButton *)item;
													ptr->EnumID=ID;
                                       ptr->SubText="";
													CString str=CVgaMenuItem::GetString(data,length);
                                       str.TrimLeft();
													str.TrimRight();
													ptr->SubText = " " + str;
													
												}
												break;
											}

									 }
									 break;

								}
                     }
						}
                  else
                  {
                     CChildView::thisPtr->ProcessNak(data,length,0,0);
                  }
                  delete response;
					}
               
					return true;
				}
				else
				{
					switch(item->GetType())
				   {
					   case CVgaMenu::VGABottomHalfObject:
					   {
						   CBottomHalf *ptr=(CBottomHalf *)item;
						   ptr->EnumID = StringID;
					   }
					   break;
					   case CVgaMenu::VGA_Button_OBJECT:
						{
							CVgaButton *ptr=(CVgaButton *)item;
							ptr->EnumID=StringID;
					    
					   }
					   break;
                  case CVgaMenu::CHOICE:
                  {
                     CLocalChoice *ptr=(CLocalChoice *)item;
                     ptr->EnumID=StringID;
                  }
                  break;
                  default:
                     item->EnumID =StringID;
				   }
                                    
				}
         
			}
			break;
		case 4://Checking USB present or not.
			{
				switch(item->GetType())
				{
					case CVgaMenu::VGA_Button_OBJECT:
					{		        
						CVgaButton *ptr=(CVgaButton *)item;
                  void *pointer;
                  bool (*rmn)(CVgaButton *);
                  if(functionCall.Lookup(FunName,pointer))
		            {
                      rmn = (bool (*)(CVgaButton *))pointer;
			             return rmn(ptr);
                  }
					}
					break;
               case CVgaMenu::CHOICE:
               {
                  CLocalChoice *ptr=(CLocalChoice *)item;
                  void *pointer;
                  bool (*rmn)(CLocalChoice *);
                  if(functionCall.Lookup(FunName,pointer))
		            {
			             rmn = (bool (*)(CLocalChoice *))pointer;
			             return rmn(ptr);
                  }
               }
               break;
				}
			}
			break;
		case 5:
			{
				switch(item->GetType())
				{
					case CVgaMenu::VGARUNSCREENOBJECT:
					{		        
						CRunScreen *ptr=(CRunScreen *)item;
						int length =VARMAXMINLENGTH;
						unsigned char data1[2];
						union 
								{
									short i;
									char c[2];
								} u;
							 u.i= ptr->RunID ;
						data1[1]=u.c[0];
						data1[0]=u.c[1];

						unsigned char * data = (unsigned char *) &data1[0];
						//Send Command if enable flag is true
						CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
						CHostCommand * response = app->SendUiHostCommand(request);
						if(response)
						{
							char ch=CHostCommand::AckNak();
							data = response->GetData();
							length = response->GetDataLength();
							if(ch==theApp.ACK)
							{
								ptr->Displayable_columns=*data++;length--;
								ptr->Parameter_ID=new int[ptr->Displayable_columns];
								for(int param=0;param<ptr->Displayable_columns;param++)	//Storing parameters ID.
								{
									ptr->Parameter_ID[param]=*data++;
									length--;
								}
								ptr->ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
								ptr->TotalCycles=*data++;//Numbers of cycle for which weld data is to be shown.
								length--;
								
								while(ptr->WeldDataList.GetCount()>0)
									delete ptr->WeldDataList.RemoveHead();
								
								for(int cycle =0;cycle<ptr->TotalCycles;cycle++)
								{
									CWeldingData * obj = new CWeldingData(data, length);
									ptr->WeldDataList.AddTail(obj);
								}
								
							}
							delete response;
							return true;
						}
					}
					break;
				}
			}
			break;
		}
   return true;
}

bool RefreshCheck(CVgaButton *ptr)
{
   if(CChildView::thisPtr->AutoRefreshon)
   {
      ptr->IsDraw =false;
      ptr->RectShow =false;
	   return false;
   }
   else
   {
      if(CChildView::thisPtr->AlarmCount)
      {
         ptr->IsDraw =false;
         ptr->RectShow =false;
         return false;
      }
      else
      {
         ptr->IsDraw=true;
         ptr->RectShow =true;
         return true;
      }
      
   }
}

bool ScanAOnOff(CLocalChoice *ptr)
{
   ptr->ChoiceText=" > ";
   if(CChildView::thisPtr->ScanA_On)
   {
      ptr->ChoiceText += ptr->ChoiceText2 ;
   }
   else
   {
      ptr->ChoiceText += ptr->ChoiceText1 ;
   }
   return true;
}

bool ScanBOnOff(CLocalChoice *ptr)
{
   ptr->ChoiceText=" > ";
   if(CChildView::thisPtr->ScanB_On)
   {
      ptr->ChoiceText +=ptr->ChoiceText2 ;
   }
   else
   {
      ptr->ChoiceText +=ptr->ChoiceText1 ;
   }
   return true;
}

bool ScanCOnOff(CLocalChoice *ptr)
{
   ptr->ChoiceText=" > ";
   if(CChildView::thisPtr->ScanC_On)
   {
      ptr->ChoiceText += ptr->ChoiceText2 ;
   }
   else
   {
      ptr->ChoiceText += ptr->ChoiceText1 ;
   }
   return true;
}


bool CurrentScanOnOff(CLocalChoice *ptr)
{
   ptr->ChoiceText=" > ";
   if(CChildView::thisPtr->CurrentScan_On)
   {
      ptr->ChoiceText +=ptr->ChoiceText2 ;
   }
   else
   {
      ptr->ChoiceText +=ptr->ChoiceText1 ;
   }
   return true;
}

bool AddPowerGraph(CVgaButton *ptr)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION pos1=menu->items.GetHeadPosition();
   CChildView::thisPtr->ViewGraphWeldData=0;
	CVgaDrawGraph::GraphCount=0;
   while(theApp.GraphsDataList.GetCount()>0)
	    theApp.GraphsDataList.RemoveHead();
   unsigned char RequestType = (char)(2);
   int length =2;
   unsigned char data1[2];
   data1[0]=(char)RequestType;
   data1[1]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
	   char ch=CHostCommand::AckNak();
	   data = response->GetData();//Getting Data.
	    length = response->GetDataLength();//Getting Length.
	    if(ch==theApp.ACK)//If Ack.
	    {		//store graph data
		    while ((pos1)&&(length>0))
          {
             object= menu->items.GetNext(pos1);
	          if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
             {
                CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                if((ValueAfterParamID==ptr->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
                {
                
                   ptr->GraphData.graph_type=ValueAfterParamID;
                   SetGraphObjectMember(data,length,ptr);
                   theApp.GraphsDataList.AddTail(ptr);
                }
                else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr->GraphType)
                {
                   ptr->GraphData.graph_type=ValueAfterParamID;
                   for(int i=0;i<20;i++)
		                 ptr->GraphData.SystemPressure[i]='\0';
	                ptr->AlreadyPrinted=false;
	                ptr->Lang_Index=0;//CChildView::Language_Index;
	                ptr->No_Graph_String=" ";
                   ptr->GraphCount++;
	                ptr->GraphData.GraphNum =ptr->GraphCount;
          
                   for( i=0;i<20;i++)
		               ptr->GraphData.GRAPHTITLE[i]='\0';
                   for( i=0;i<20;i++)
		               ptr->GraphData.CycleCount[i]='\0';
                   ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                   theApp.GraphsDataList.AddTail(ptr);
                }
                else
                {
                   *data--;length++;
                   *data--;length++;
                }
             }
          }
		 }
	    else 
		   CChildView::thisPtr->ErrorBeep();
	    delete response;
      }
      return true;
}

bool AddAvgPowerGraph(CVgaButton *ptr)
{
   POSITION pos1 = theApp.GraphsDataList.GetHeadPosition();
	if(theApp.GraphsDataList.GetCount())
	if((theApp.GraphsDataList.GetCount()==1)&& CChildView::thisPtr->PMCScreen)//&&(GraphDataList.GetHead()->GraphData.graph_type == CScreenObject::VGA_POWERGRAPH)
	{
		CVgaMenu * menu;
      menu=theApp.MenuPointer;
      CVgaMenuItem *object;
      POSITION POSI=menu->items.GetHeadPosition(); 
      int length =1;
	   unsigned char data1=(char)04;
	   unsigned char * data = (unsigned char *) &data1;

	   CHostCommand * request = new CHostCommand(PowerMatchCurve_FunctionId, data, length);
	   CHostCommand * response = app->SendUiHostCommand(request);
	   if (response)
	   {
		   char ch=CHostCommand::AckNak();
		   data = response->GetData();//Getting Data.
		    length = response->GetDataLength();//Getting Length.
		    if(ch==theApp.ACK)//If Ack.
		    {	   //store graph data

			   while ((POSI)&&(length>0))
            {
                object= menu->items.GetNext(POSI);
	             if(object->GetType()==CVgaMenu::VGA_GRAPH_OBJECT)
                {
                      CVgaDrawGraph * ptr = (CVgaDrawGraph *)object;
						    int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                      if(ValueAfterParamID==NO_VALID_GRAPH)
                      {
                         delete response;
                         return true;
                      }
                      if(ValueAfterParamID==ptr->GraphType)
                      {
                        ptr->GraphData.graph_type=ValueAfterParamID;
                        int TempVar =*data++;
	                     if(TempVar>0)
		                     CChildView::thisPtr->PMCDisable =true;
	                     else
		                     CChildView::thisPtr->PMCDisable =false;
	                     length--;
	                     ptr->PMCCycleCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
	                     int TimeCount =CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
	                     CChildView::thisPtr->LowerPMCLimit=*data++;
	                     length--;
	                     CChildView::thisPtr->UpperPMCLimit=*data++;
                        length--;
	                     ptr->GraphData.DataLength=0;

	                     if(ptr->PMCCycleCount !=0)
	                     {
		                     short graphdatalength=0;
		                     for(short len=0;len<400;len++)
		                     {
			                     if(*data!=0xFF)
			                     {
				                     ptr->GraphData.graphdata[len]=(short)*data++;
				                     graphdatalength++;
			                     }
			                     else
				                     *data++;
			                     length--;
		                     }
		                     ptr->GraphData.DataLength=graphdatalength;
		                     
		                     
	                     }
	                     if(ptr->GraphData.DataLength==0)
	                     {
		                     CChildView::thisPtr->LowerPMCLimit=0;
		                     CChildView::thisPtr->UpperPMCLimit=0;
	                     
	                     }
	                     CChildView::thisPtr->PMCMaxVdata=*data++;

	                     length--;length--;
                        ptr->RecalculateAverageGraph(CChildView::thisPtr);
                        theApp.GraphsDataList.AddTail(ptr);
                     }
                     else
                     {
                        *data--;length++;
                        *data--;length++;
                     }
               
                  }
              }	
          }
          else
          {
              CChildView::thisPtr->ErrorBeep();
          }
          delete response;
      }
					 
	}
   return true;
}

bool ProcessAlarmMenu(CVgaButton *pointer)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object=0;
   bool show=false;
   while(theApp.GraphsDataList.GetCount()>0)
		  theApp.GraphsDataList.RemoveHead();
   POSITION pos=menu->items.GetHeadPosition();
   while(pos)
   {
      object=menu->items.GetNext(pos);
      if((object->EnumID==-1)||(object->PSType==CVgaMenu::BottomMenu_Id))
         object->IsDraw=true;
      else  
      {
         object->IsDraw=false;
      }
   }
   if(theApp.menuName!=CVgaBottomMenu::WeldResults_ID)
      CChildView::thisPtr->RunResultScreen=false;
   CHostCommand * request = new CHostCommand(GetAlarmSetupFlag, 0, 0);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{		
		char ch=CHostCommand::AckNak();
      CChildView::thisPtr->IsAlarmScreen =true;
      CChildView::thisPtr->AlarmUpdateRequired=false;
      unsigned char *data = response->GetData();
		int length = response->GetDataLength();
      int AlarmBit=0,position=0,location=0;
      int Temprory=0,TitlePosition=0;
		if(ch==theApp.ACK)
      {
         int NoOfFlags=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
         int *FlagArray=new int[NoOfFlags];
         TitlePosition=0;
         bool SetupAlarmFlag=false;
         for(int i=0;i<NoOfFlags;i++)
         {
            FlagArray[i]=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            AlarmBit=FlagArray[i];
            for(int j=0;j<=31;j++)
            { 
              Temprory=AlarmBit%2;
              AlarmBit=(AlarmBit)/2;
            
              if(Temprory == 1)
              { 
                 location = position;
                 POSITION pos=menu->items.GetHeadPosition();
                  while(pos)
                  {
                     object=menu->items.GetNext(pos);
                     if(object->GetType()==CVgaMenu::VGA_Button_OBJECT)
                     {
                        CVgaButton *ptr=(CVgaButton *)object;
                        if(location==ptr->EnumID)
                        {
                            ptr->IsDraw=true;
                            if(pointer==ptr)
                              show=true;
                            break;
                        }
                        
                     }
                  }
                  if((i>=0)&&(i<SETUP_ALARM_END))
                  {
                     TitlePosition=SETUP_ALARM;
                     SetupAlarmFlag=true;
                  }
                  else
                  {
                     if(!SetupAlarmFlag)
                        TitlePosition=i-SETUP_ALARM_END;
                  }
              }
              position++;
             }
            
         }
         delete []FlagArray;
         POSITION pos=menu->items.GetHeadPosition();
         while(pos)
         {
            object=menu->items.GetNext(pos);
            if(object->GetType()==CVgaMenu::TITLE)
            {
               CVgaTitle *ptr=(CVgaTitle *)object;
               CString str=ptr->TitleArray[TitlePosition];
               ptr->text=ptr->TitleArray[TitlePosition];
               object->IsDraw=true;
               break;
            }
         }
      }
      delete response;
   }
   return show;   
}

bool SendCommandForViewGraphs(CVgaButton *ptr)           
{
      CVgaMenu * menu;
      menu=theApp.MenuPointer;
      CVgaMenuItem *object;
      POSITION pos1=menu->items.GetHeadPosition();
      CChildView::thisPtr->ViewGraphWeldData=0;
		CVgaDrawGraph::GraphCount=0;
		if(CChildView::thisPtr->AutoRefreshon)
		{
         CVgaDrawGraph::GraphCount=0;
			while(theApp.GraphsDataList.GetCount()>0)
				 theApp.GraphsDataList.RemoveHead();
			unsigned char RequestType = (char)(CChildView::thisPtr->GraphOneRequestValue +CChildView::thisPtr->GraphTwoRequestValue);
			int length =2;
			unsigned char data1[2];
			data1[0]=(char)RequestType;
			data1[1]=(char)0;
			unsigned char * data = (unsigned char *) &data1[0];

			CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
			CHostCommand * response = app->SendUiHostCommand(request);
			if (response)
			{
				char ch=CHostCommand::AckNak();
				data = response->GetData();//Getting Data.
				 length = response->GetDataLength();//Getting Length.
				 if(ch==theApp.ACK)//If Ack.
				 {		//store graph data
				    while ((pos1)&&(length>0))
                {
                   object= menu->items.GetNext(pos1);
	                if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
                   {
                      CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                      int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                      if((ValueAfterParamID==ptr->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
                      {
                         ptr->GraphData.graph_type=ValueAfterParamID;
                         SetGraphObjectMember(data,length,ptr);
                         theApp.GraphsDataList.AddTail(ptr);
                      }
                      else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr->GraphType)
                      {
                         ptr->GraphData.graph_type=ValueAfterParamID;
                         for(int i=0;i<20;i++)
		                       ptr->GraphData.SystemPressure[i]='\0';
	                      ptr->AlreadyPrinted=false;
	                      ptr->Lang_Index=0;//CChildView::Language_Index;
	                      ptr->No_Graph_String=" ";
                         ptr->GraphCount++;
	                      ptr->GraphData.GraphNum =ptr->GraphCount;
                      
                         for( i=0;i<20;i++)
		                     ptr->GraphData.GRAPHTITLE[i]='\0';
                         for( i=0;i<20;i++)
		                     ptr->GraphData.CycleCount[i]='\0';
                         ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                         theApp.GraphsDataList.AddTail(ptr);
                         break;
                      }
                      else
                      {
                         *data--;length++;
                         *data--;length++;
                      }
                   }
                }
					 POSITION pos = theApp.GraphsDataList.GetHeadPosition();
					 while(pos)
					 {
						CVgaDrawGraph *Graph= theApp.GraphsDataList.GetNext(pos);
						if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue)
							Graph->GraphData.GraphNum=1;
						else if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue)
						Graph->GraphData.GraphNum=2;
						else 
							Graph->GraphData.GraphNum=0;
					 }
				 }
				 else 
					CChildView::thisPtr->ErrorBeep();
				 delete response;
			}
		CChildView::thisPtr->Invalidate();
	}
	else
	{
      pos1=menu->items.GetHeadPosition();
      CVgaDrawGraph::GraphCount=0;
		while(theApp.GraphsDataList.GetCount()>0)
			 theApp.GraphsDataList.RemoveHead();
		unsigned char RequestType = (char)126;//(CChildView::GraphOneRequestValue +CChildView::GraphTwoRequestValue);
		int length =2;
		unsigned char data1[2];
		data1[0]=(char)RequestType;
		data1[1]=(char)0;
		unsigned char * data = (unsigned char *) &data1[0];

		CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			
			char ch=CHostCommand::AckNak();
			data = response->GetData();//Getting Data.
			 length = response->GetDataLength();//Getting Length.
			 if(ch==theApp.ACK)//If Ack.
			 {		//store graph data
				CChildView::thisPtr->ViewGraphGlobalCount=CChildView::thisPtr->UniversalCount;
				while ((pos1)&&(length>0))
            {
               object= menu->items.GetNext(pos1);
	            if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
               {
                   CVgaDrawGraph * ptr = (CVgaDrawGraph *)object;
						 int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                   if((ValueAfterParamID==ptr->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
                   {
                      ptr->GraphData.graph_type=ValueAfterParamID;
                      SetGraphObjectMember(data,length,ptr);
                      theApp.GraphsDataList.AddTail(ptr);
                   }
                   else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr->GraphType)
                   {
                      ptr->GraphData.graph_type=ValueAfterParamID;
                      for(int i=0;i<20;i++)
		                  ptr->GraphData.SystemPressure[i]='\0';
	                   ptr->AlreadyPrinted=false;
	                   ptr->Lang_Index=0;//CChildView::Language_Index;
	                   ptr->No_Graph_String=" ";
                      ptr->GraphCount++;
	                   ptr->GraphData.GraphNum =ptr->GraphCount;
                      for( i=0;i<20;i++)
		                  ptr->GraphData.GRAPHTITLE[i]='\0';
                      for( i=0;i<20;i++)
		                  ptr->GraphData.CycleCount[i]='\0';
                      ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                      theApp.GraphsDataList.AddTail(ptr);
                   }
                   else
                   {
                      *data--;length++;
                      *data--;length++;
                   }
                }
             }
				 POSITION pos = theApp.GraphsDataList.GetHeadPosition();
				 while(pos)
				 {
					CVgaDrawGraph *Graph= theApp.GraphsDataList.GetNext(pos);
					if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue)
						Graph->GraphData.GraphNum=1;
					else if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue)
					Graph->GraphData.GraphNum=2;
					else 
						Graph->GraphData.GraphNum=0;
				 }
            }
				else 
					CChildView::thisPtr->ErrorBeep();
				delete response;

          /****************************/
	         int length =CORDLENGTH;
		      unsigned char data1[CORDLENGTH];
		      data1[0]=(char)01;//(++TotalGraphRequestValue);
		      data1[1]=(char)01;
		      unsigned char * data = (unsigned char *) &data1[0];
		      request = new CHostCommand(GetWeldData_FunID, data, length);
		      response= app->SendUiHostCommand(request);
		      if(response)
		      {
			      char ch=CHostCommand::AckNak();
			      data = response->GetData();//Getting Data.
			      length = response->GetDataLength();//Getting Length.
			      
			      if(ch==theApp.ACK)
			      {
				      //view->ViewGraphWelddataLength=length;
				      CChildView::thisPtr->ViewGraphWeldData=response;
			      }
			      //delete view->ViewGraphWeldData;
		      }
		}
	  CChildView::thisPtr->Invalidate();
   }
   return true;
}


bool ProcessAlarmExit(CVgaButton *ptr)
{
   ptr->IsDraw=true;
	ptr->SetType(CVgaMenu::VGA_VGAEXITBUTTON);
   ptr->PSType=CVgaMenu::VGA_Button_OBJECT;
   return true;
}


bool GetCurrentPresetScrn(CVgaButton *ptr)
{
   char TempArray[10];
	CString Temp=_itoa(ptr->EnumID,TempArray,10);
   Temp=CVgaMenuItem ::LinearSearch(Temp);
   CChildView::thisPtr->ShowMessageScreen(Temp/*StrM5_35[CChildView::Language_Index]*/);
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object=0;
   CVgaMenuItem *ViewPresetobject=0;
   POSITION pos=menu->items.GetHeadPosition();
   while(pos)
   {
      object= menu->items.GetNext(pos);
      if(object->GetType()!=CVgaMenu::VGA_ALARMBUTTON)
      {
         if(object->PSType==CVgaMenu::COLORSETUP_ID)
         {
            ViewPresetobject = object;
            CVgaViewPreset *ptr=(CVgaViewPreset *)object;
            while (ptr->ViewPresetTextList.GetCount())
		         delete ptr->ViewPresetTextList.RemoveHead();
            CChildView::thisPtr->Total_Objects=0;
            ptr->Page_No=ONE;
            object->SetPageNum(0);
            object->IsDraw=true;
            //break;
         }
         else if((object->GetType()==CVgaMenu::TITLE)||(object->PSType==CVgaMenu::BottomMenu_Id)/*||(object->GetType()==CVgaMenu::TOGGLE)*/)
		   {
           object->IsDraw=true;
         }
         else
         {
            object->IsDraw=false;
         }
      }
   }
   ptr->IsDraw=false;
	page_no=ONE;
	int length=2;
	unsigned char data1[CORDLENGTH];
	data1[ZERO]=(char)1;
	data1[ONE]=(char)0;
	unsigned char * data = (unsigned char *) &data1[ZERO];
	CHostCommand * request = new CHostCommand(GETPSVIEWPRESETSCREEN_FunId, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{		
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		while (length>ZERO)
		{	
			// Preparing list.//
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         CPrintText * object1 = new CPrintText(data, length,true,ID);
			CVgaViewPreset *obj = (CVgaViewPreset*)ViewPresetobject;
			obj->ViewPresetTextList.AddTail(object1);
		}
		delete response;
	}
	//Call function to arrange the co-ordinates of object to show on screen.//
	((CVgaViewPreset*)ViewPresetobject)->ArrangeCoOrdinate();
	//	CChildView::thisPtr->Invalidate();
      return false;
}

bool EnableColdStartFlag(CVgaButton *ptr)
{
   CChildView::LargeWaitingTime=true;
   CChildView::ColdStartInProcess=true;
   return false;
}

bool DisableColdStartFlag(CVgaButton *ptr)
{
   CChildView::ColdStartInProcess=false;
   CChildView::LargeWaitingTime=false;
   CChildView::thisPtr->GetPrintingParameters(true);
   if(PrintSetup.IsPrinting)
		CChildView::thisPtr->CheckPrinterStatus();
   CChildView::thisPtr->MaxPreset=1;
   CChildView::thisPtr->SendCommandForQualityWindow(CChildView::MaxPreset);
   theApp.GetSystemVariable();
   return false;
}

bool GetPrinterInfo(CVgaButton *ptr)
{
   if(CChildView::thisPtr->PrinterPresent== PRINTERONLINE)
   {
      ptr->text=CChildView::thisPtr->PrinterPower_str_Online;
   }
	else
   {
      ptr->text=CChildView::thisPtr->PrinterPower_str_Offline;
   }
   return true;
}

void AutoRefreshGraph(int ToggleValue)
{
   if(ToggleValue)
		CChildView::thisPtr->AutoRefreshon=true;
	else
		CChildView::thisPtr->AutoRefreshon=false;
}

void ProcessSequence(int ToggleValue)
{
   if(ToggleValue)
   {
      CToggle::SequencingON=true;
   }
	else
   {
      CToggle::SequencingON=false;
   }
}

bool USBCheckFunction(CVgaButton *ptr)
{
   if(!CChildView::thisPtr->ISUSBPresent)
	{
		ptr->IsDraw =false;
		return false;
	}
   else
   {
      ptr->IsDraw =true;
      return true;
   }
   
}

void ReadUSBStoredPresetStrings(CChildView *view)
{
   view->CreateFolder(true);
	CString PSName =view->PowerSupply;
	CString	Path=CChildView::LastUSBPresetFolder;//"USBDisk\\"+PSName + "\\Preset.log";
	if(!view->IsFolderPresent(Path,"Presets"))
	{
		CString TempPath= Path;
		CreateDirectory(TempPath,NULL);	
	}

	 WIN32_FIND_DATA FindFileData;
   HANDLE hFind = INVALID_HANDLE_VALUE;
  
   CString DirSpec;  
   DirSpec=Path+_T("\\*.log");
   hFind = FindFirstFile(DirSpec, &FindFileData);
   CChildView::thisPtr->TotalUSBPreset=0;
   CString FileName;
   if(view->ValidFolderName(FindFileData.cFileName, USBPRESETSCRN))
   {
		FileName=FindFileData.cFileName;
		if(FileName.Find(_T("Preset"),0)!=(-1))
		{
			if(FileName.GetLength()>10)
			{
				FileName.Delete(0,6);
				int t =FileName.Find(_T(".log"),0);
				if(t!=(-1))
					FileName.Delete(t,4);
				
            CChildView::thisPtr->USBPresetNames.AddTail(FileName);
				CChildView::thisPtr->TotalUSBPreset++;
			}
		}
		
	}
	while (FindNextFile(hFind, &FindFileData) != 0) 
    {
		FileName=FindFileData.cFileName;
		if(view->ValidFolderName(FindFileData.cFileName, USBPRESETSCRN))
		{
			if(FileName.Find(_T("Preset"),0)!=(-1))
			{
				if(FileName.GetLength()>10)
				{
					FileName.Delete(0,6);
					int t =FileName.Find(_T(".log"),0);
					if(t!=(-1))
						FileName.Delete(t,4);
				   
					CChildView::thisPtr->USBPresetNames.AddTail(FileName);
					CChildView::thisPtr->TotalUSBPreset++;
				}
			}
		}
	}
}

bool CopyPowerPresetToList(CVgaButton *ptr)
{
   CVgaMenu *menu1=theApp.MenuPointer;
   CVgaMenuItem * Object;
   POSITION pos = menu1->items.GetHeadPosition();
   while(pos)
   {
      Object = menu1->items.GetNext(pos);
      if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
      {
         CListBoxObject *obj=(CListBoxObject*)Object;
         for(int i =0;i<obj->TotalText;i++)
				CChildView::thisPtr->PSPresetText[i]= obj->ListBoxText[i];
         break;
      }
   }
   while(CChildView::thisPtr->USBPresetNames.GetCount())
		CChildView::thisPtr->USBPresetNames.RemoveHead();  
   ReadUSBStoredPresetStrings(CChildView::thisPtr);
   return true;
}

bool GetPSPresetScrn(CVgaButton *ptr)
{
   char TempArray[10];
	CString Temp=_itoa(ptr->EnumID,TempArray,10);
   Temp=CVgaMenuItem ::LinearSearch(Temp);
   CChildView::thisPtr->ShowMessageScreen(Temp/*StrM5_35[CChildView::Language_Index]*/);
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object=0;
   CVgaMenuItem *ViewPresetobject=0;
   POSITION pos=menu->items.GetHeadPosition();
   while(pos)
   {
      object= menu->items.GetNext(pos);
      if(object->GetType()!=CVgaMenu::VGA_ALARMBUTTON)
      {
         if(object->PSType==CVgaMenu::COLORSETUP_ID)
         {
            ViewPresetobject = object;
            CVgaViewPreset *ptr=(CVgaViewPreset *)object;
            while (ptr->ViewPresetTextList.GetCount())
		         delete ptr->ViewPresetTextList.RemoveHead();
            CChildView::thisPtr->Total_Objects=0;
            ptr->Page_No=ONE;
            object->SetPageNum(0);
            object->IsDraw=true;
            //break;
         }
         else if((object->GetType()==CVgaMenu::TITLE)||(object->PSType==CVgaMenu::BottomMenu_Id)/*||(object->GetType()==CVgaMenu::TOGGLE)*/)
		   {
           object->IsDraw=true;
         }
         else
         {
            object->IsDraw=false;
         }
      }
   }
   ptr->IsDraw=false;
	page_no=ONE;
	int length=2;
	unsigned char data1[CORDLENGTH];
	data1[ZERO]=(char)1;
   data1[ONE]=(char)CChildView::thisPtr->SelectedPowerPreset;
	unsigned char * data = (unsigned char *) &data1[ZERO];
	CHostCommand * request = new CHostCommand(GETPSVIEWPRESETSCREEN_FunId, data, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{		
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
      if(ch==theApp.ACK)
		while (length>ZERO)
		{	
			// Preparing list.//
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         CPrintText * object1 = new CPrintText(data, length,true,ID);
			CVgaViewPreset *obj = (CVgaViewPreset*)ViewPresetobject;
			obj->ViewPresetTextList.AddTail(object1);
		}
		delete response;
	}
	//Call function to arrange the co-ordinates of object to show on screen.//
	((CVgaViewPreset*)ViewPresetobject)->ArrangeCoOrdinate();
	//	CChildView::thisPtr->Invalidate();
      return false;
}

bool GetUSBPresetScrn(CVgaButton *ptr)
{
   char TempArray[10];
	CString Temp=_itoa(ptr->EnumID,TempArray,10);
   Temp=CVgaMenuItem ::LinearSearch(Temp);
   CChildView::thisPtr->ShowMessageScreen(Temp/*StrM5_35[CChildView::Language_Index]*/);
   CString PresetNameStr =CChildView::USBSelectedPresetName;
	CString	pFileName=CChildView::LastUSBPresetFolder + "\\Preset"+CChildView::USBSelectedPresetName+".log";
	CFile f;
	CFileException e;
	char ch1=0;
	if( f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
      CVgaMenu * menu;
      menu=theApp.MenuPointer;
      CVgaMenuItem *object=0;
      CVgaMenuItem *ViewPresetobject=0;
      POSITION pos=menu->items.GetHeadPosition();
      while(pos)
      {
         object= menu->items.GetNext(pos);
         if(object->GetType()!=CVgaMenu::VGA_ALARMBUTTON)
         {
            if(object->PSType==CVgaMenu::COLORSETUP_ID)
            {
               ViewPresetobject=object;
               CVgaViewPreset *ptr=(CVgaViewPreset *)object;
               while (ptr->ViewPresetTextList.GetCount())
		            delete ptr->ViewPresetTextList.RemoveHead();
               CChildView::thisPtr->Total_Objects=0;
               ptr->Page_No=ONE;
               object->SetPageNum(0);
               object->IsDraw=true;
              // break;
            }
            else if((object->GetType()==CVgaMenu::TITLE)||(object->PSType==CVgaMenu::BottomMenu_Id)/*||(object->GetType()==CVgaMenu::TOGGLE)*/)
		      {
              object->IsDraw=true;
            }
            else
            {
               object->IsDraw=false;
            }
         }
      }
      ptr->IsDraw=false;
	   page_no=ONE;
      int  size= SIZEOFPRESETDATA;
		int ObjectSize = sizeof(bool)+ sizeof(char)+ size + sizeof(char);
		int StartingPointer =sizeof(bool)+ sizeof(char);//(SelectedUSBPreset-1)*ObjectSize+
		char ch[SIZEOFPRESETDATA+2] ;
		ch[0]=(char)1;
		f.SeekToBegin();
		int length =(f.GetLength());
		if((length> ObjectSize))
		{
			f.Close();
			CChildView::ErrorBeep();
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
			CChildView::thisPtr->Invalidate();
			return false;
		}
      if((length==(PRESETSIZE_WITHOUTDUPS+3))||(length==ObjectSize))
	   {
		   f.Seek(StartingPointer, CFile::begin );
		   int t=f.Read(&ch[1],length-3);
							   
		   length = length-2;
		   bool GotResponse =false;
	      unsigned char * data = (unsigned char *) &ch[0];
	      CHostCommand * request = new CHostCommand(GETUSBVIEWPRESETFunId, data, length);
	      CHostCommand * response = app->SendUiHostCommand(request);
	      if(response)
	      {		
		      char ch=CHostCommand::AckNak();
		      data = response->GetData();
		      length = response->GetDataLength();
            if(ch==theApp.ACK)
            {
		         GotResponse=true;
               while (length>ZERO)
		         {	
			         // Preparing list.//
                  int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                  CPrintText * object1 = new CPrintText(data, length,true,ID);
			         CVgaViewPreset *obj = (CVgaViewPreset*)ViewPresetobject;
			         obj->ViewPresetTextList.AddTail(object1);
		         }
		         delete response;
            }
	      }
	      //Call function to arrange the co-ordinates of object to show on screen.//
	      ((CVgaViewPreset*)ViewPresetobject)->ArrangeCoOrdinate();
		   //   CChildView::thisPtr->Invalidate();
      }
   }
   return false;
}


bool ProcessColorSetupScreen(CVgaButton *ptr)
{
   CVgaMenu *menu=theApp.MenuPointer;
   CVgaMenuItem *object= 0;
   POSITION pos = menu->items.GetHeadPosition();
   while (pos)
	{
		object = menu->items.GetNext(pos);
		int type = object->GetType();
      if(type==CVgaMenu::VGATEXTBOX)
      {
         CTextBox *Textptr=(CTextBox *)object;
         Textptr->BoxColor=CChildView::thisPtr->Highlight_Color;
         break;
      }
   }
   return true;
}

bool ProcessUSBGraphButtonDisplay(CVgaButton *ptr)
{
   if(CChildView::thisPtr->EnableUSBGraph)
   {
      ptr->IsDraw =true;
      ptr->RectShow =1;
      return true;
   }
   else
   {
      ptr->RectShow =0;
      ptr->IsDraw =false;
      return false;
   }
}


bool AddStartUpVersion(CVgaButton *ptr)
{
   ptr->SubText = CChildView::thisPtr->StartUpVerFileName;
   ptr->IsDraw =true;
   return true;
}

bool AddSystemVersion(CVgaButton *ptr)
{
   ptr->SubText = CChildView::thisPtr->SystemVerFileName;
   ptr->IsDraw =true;
   return true;
}

bool GetNKBinDate(CVgaButton *ptr)
{
   CFileStatus status;
   CFile f;    
	CFileException e;
   
	TCHAR* pFileName;
	#ifndef _WIN32_WCE
	pFileName = _T("c:\\NK.bin");
	#else
	pFileName = _T("Disk\\NK.bin");
	#endif

  if( CFile::GetStatus( pFileName, status ) )   // A static function.
  {
      char TempArray[10];
      CString Day=_itoa(status.m_mtime.GetDay(),TempArray,10);
      Day +="/";
      CString Month=_itoa(status.m_mtime.GetMonth(),TempArray,10);
      Month +="/";
      CString Year=_itoa(status.m_mtime.GetYear(),TempArray,10);
      if(CChildView::metric)
	       ptr->SubText = (Day + Month+ Year);
	   else
	       ptr->SubText = (Month + Day + Year);
      
  }
  ptr->IsDraw =true;
  return true;
}
