// ListBox.cpp: implementation of the CListBox class.
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
  1.0       01/11/08	PDwivedi  Added Initial Version.
  1.1       08/01/08 PDwivedi  Modified Draw for USBPresetScrn.
  1.2       09/12/08 PDwivedi  Added changes for Tracker issues of round 2 testing for version LangTestJ.
*/
#include "stdafx.h"
#include "SBC.h"
#include "ListBox.h"
#include "XmlElement.h"
#include "Variable.h"
#include "Toggle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString CListBoxObject::CurrentPresetName;
CString CListBoxObject::CurrentSequencePresetName;
bool CListBoxObject::SequencingScreen=false;

CListBoxObject::CListBoxObject(CXmlElement * e)
{
  
	ListBox_Color = _ttoi(e->GetAttribute("Color"));//Fillcolor for list box rectangle.
	/*Storing Co-ordinates for list box.*/
	X1_CoOrdinate =  _ttoi(e->GetAttribute("X1"));
	Y1_CoOrdinate = _ttoi(e->GetAttribute("Y1"));
	X2_CoOrdinate =  _ttoi(e->GetAttribute("X2"));
	Y2_CoOrdinate =  _ttoi(e->GetAttribute("Y2"));

	TotalText = _ttoi(e->GetAttribute("TotalText"));//Number of text to be display.
	
   ListBoxText.SetSize(TotalText+1);
   PresetInfoText.SetSize (TotalText);
   Type=_ttoi(e->GetAttribute("type"));
   MaxPreset=_ttoi(e->GetAttribute("MaxPresetDisplay")); 
   if(Type==PRESETINFOSCREEN)
   {
      PresetInfoText[0]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID1"));
      PresetInfoText[1]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID2"));
      PresetInfoText[2]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID3"));
      PresetInfoText[3]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID4"));
      PresetInfoText[4]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID5"));
   }
	RectShow=false;
   POSITION pos = e->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		if (tag == "condition")
      {
         AddCondition(element);
      }
		else
			ASSERT(FALSE);
	}
	rect = CRect(X1_CoOrdinate-1,Y1_CoOrdinate-1,X2_CoOrdinate+1,Y2_CoOrdinate+1);

}

CListBoxObject::~CListBoxObject()
{
//	delete []ListBoxText;
   if(ListBoxText.GetSize()>0)
      ListBoxText.RemoveAll();
   if(PresetInfoText.GetSize()>0)
      PresetInfoText.RemoveAll();
	SequencingScreen=false;
}

/**********************************************************************************/
/*                                                                                */ 
/*  This function Draws a CVGAListBox object When any CVGAListBox type object     */
/*  is found in menu/submenu item list for current page .						  */
/*																				  */
/**********************************************************************************/
void CListBoxObject::Draw(CDC *pDC)
{
	
/*Draw list box rectangle with list box color*/
	DrawRect(pDC, Black, CRect(X1_CoOrdinate-1,Y1_CoOrdinate-1,
								X2_CoOrdinate+1,Y2_CoOrdinate+1));
	DrawRect(pDC, ListBox_Color, CRect(X1_CoOrdinate,Y1_CoOrdinate,
										X2_CoOrdinate,Y2_CoOrdinate));

	int Y_CoOrdinate = Y1_CoOrdinate;
//	switch(ID)
//	{
	//	case  VGA_PRESETNAME:
		{
			int j=0,MaxPresetDisplay=0;
         MaxPresetDisplay=MaxPreset;
       //  int ViewUSBPreset;
         /*if(Type==1)
			    MaxPresetDisplay=MAX_PRESETS_DISPLAYED;
         else if(Type==0)
         {
             MaxPresetDisplay =  TotalText;
         }
         else if(Type==2)
         {
            MaxPresetDisplay=MAX_PRESETS_DISPLAYED-1;
         }
			if((SequencingScreen)&&(Type==1))
				MaxPresetDisplay-=1;//Draw only 10 presets on Sequencing screen.*/
			if(Type==PRESETSCREEN)
         {
            if(CChildView::CurrentPresetNum >MaxPresetDisplay)
				   j = CChildView::CurrentPresetNum -MaxPresetDisplay;
         }
         else if(Type==SEQUENCESCREEN)
         {
            if(CChildView::CurrentSequencePreset >10)//(MAX_PRESETS_DISPLAYED-1)
				j = (CChildView::CurrentSequencePreset -10);//MAX_PRESETS_DISPLAYED-1
         }
         else if(Type==USBPRESETSCREEN)
         {
            if((CChildView::SelectedUSBPreset==0)&&(CChildView::USBPresetNames.GetCount()>0))
               CChildView::SelectedUSBPreset=1;
            if(CChildView::SelectedUSBPreset >MaxPresetDisplay)
               j = CChildView::SelectedUSBPreset -MaxPresetDisplay;
			  // ViewUSBPreset = MaxPresetDisplay;
            if(CChildView::TotalUSBPreset<MaxPresetDisplay)
               MaxPresetDisplay = CChildView::TotalUSBPreset;
         }
         else if(Type==POWERPRESETSCREEN)
         {
            if(CChildView::SelectedPowerPreset >MaxPresetDisplay)
				   j = CChildView::SelectedPowerPreset -MaxPresetDisplay;
         }
						
			for(int i=0;i<MaxPresetDisplay;i++)
			{
				/*Draw green background and "<"	mark on current Preset.*/			
				if((CChildView::CurrentPresetNum == (j+1))&&(Type==PRESETSCREEN))
				{
					//Drawing HighLight Background.
					DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate,
												Y_CoOrdinate,
												X2_CoOrdinate,
												Y_CoOrdinate+31));
					//Drawing "<" mark on current preset.
				/*	DrawText(pDC, SmallFont, CChildView::TextColor,CRect(X1_CoOrdinate+180,
																			Y_CoOrdinate,	
																			X2_CoOrdinate,
														     Y_CoOrdinate+31), " < ",false);*/
					CurrentPresetName = ListBoxText[j];
					CurrentPresetName.Delete(0,2);
				}
            else if((CChildView::CurrentSequencePreset == (j+1))&&(Type==SEQUENCESCREEN))//&&(CVfdToggle::SequencingON==true))
            {
               
					   //Drawing Background on Current Selected Preset.
					   DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate+15,
												   Y_CoOrdinate,
												   X2_CoOrdinate-5,
												   Y_CoOrdinate+31));
					   CurrentSequencePresetName = ListBoxText[j];
					   CurrentSequencePresetName.Delete(0,CurrentSequencePresetName.Find(L".",0));
					   
				 }
            else if((CChildView::SelectedPowerPreset == (j+1))&&(Type==POWERPRESETSCREEN))
				{
					//Drawing HighLight Background.
					DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate,
												Y_CoOrdinate,
												X2_CoOrdinate,
												Y_CoOrdinate+31));
				}
            else if((CChildView::SelectedUSBPreset == (j+1))&&(Type==USBPRESETSCREEN))
            {
               DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate,
												Y_CoOrdinate,
												X2_CoOrdinate,
												Y_CoOrdinate+31));
            }
            	//Drawing "<" mark on current Running preset.
            if(Type==SEQUENCESCREEN)
            {
				   if(CurrentRunningSequencePreset/*CChildView::CurrentSequencePreset*/ == (j+1)&&(CToggle::SequencingON))
					   DrawText(pDC, SmallFont, CChildView::TextColor,CRect(X1_CoOrdinate,
																			   Y_CoOrdinate,	
																			   X1_CoOrdinate+10,
														        Y_CoOrdinate+31), " > ",false);
            }
            if(Type==USBPRESETSCREEN)
            {
               char Number[5] ;
				   sprintf(Number,"%d  ",j+1);
               CString Name="";
               if(CChildView::USBPresetNames.GetCount()>0)
               {
               //   printf("\n name");
               Name = Number+ CChildView::USBPresetNames.GetAt(CChildView::USBPresetNames.FindIndex(j));
				   DrawText(pDC, SmallFont, CChildView::TextColor, 
					   CRect(X1_CoOrdinate+20,Y_CoOrdinate,X1_CoOrdinate+196,Y_CoOrdinate+31),
					   Name,false);
               }
            }
            else
            {
				   DrawText(pDC, SmallFont, CChildView::TextColor, 
					   CRect(X1_CoOrdinate+20,Y_CoOrdinate,X1_CoOrdinate+196,Y_CoOrdinate+31),
					   ListBoxText[j],false);
            }
				Y_CoOrdinate +=ListBox_OneLineHeight;
				j++;
			}
		}
	/*	break;
	   case VGA_PRESETINFO:
		{
			/*Drawing Preset informations.* /
			for(int i=0;i<TotalText;i++)
			{
				DrawText(pDC, SmallFont, CChildView::TextColor, CRect(X1_CoOrdinate,
										Y_CoOrdinate,X2_CoOrdinate,Y_CoOrdinate+31),
										ListBoxText[i],true);
				Y_CoOrdinate +=ListBox_OneLineHeight;
			}
		}
		break;
			case VGA_SEQUENCELIST:
		{
			int j=0;
			if(CChildView::CurrentSequencePreset >10)//(MAX_PRESETS_DISPLAYED-1)
				j = (CChildView::CurrentSequencePreset -10);//MAX_PRESETS_DISPLAYED-1
						
			for(int i=0;i<MAX_PRESETS_DISPLAYED-1;i++)
			{
				//Draw green background and "<"	mark on current Preset.			
				if((CChildView::CurrentSequencePreset == (j+1)))//&&(CVfdToggle::SequencingON==true))
				{
					//Drawing Background on Current Selected Preset.
					DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate+15,
												Y_CoOrdinate,
												X2_CoOrdinate-5,
												Y_CoOrdinate+31));
					CurrentSequencePresetName = ListBoxText[j];
					CurrentSequencePresetName.Delete(0,CurrentSequencePresetName.Find(L".",0));
					
				}
					//Drawing "<" mark on current Running preset.
  				if((CurrentRunningSequencePreset == (j+1))&&(CVfdToggle::SequencingON==true))
					DrawText(pDC, SmallFont, CChildView::TextColor,CRect(X1_CoOrdinate,
																			Y_CoOrdinate,	
																			X1_CoOrdinate+10,
														     Y_CoOrdinate+31), " > ",false);
					
				
				DrawText(pDC, SmallFont, CChildView::TextColor, 
					CRect(X1_CoOrdinate+20,Y_CoOrdinate,X1_CoOrdinate+196,Y_CoOrdinate+31),
					ListBoxText[j],false);
				Y_CoOrdinate +=ListBox_OneLineHeight;
				j++;
			}
		}
		break;
	}*/

}

bool CListBoxObject::MouseClick(const CPoint &p, CChildView *view)
{
	return false;
}