// BitCondition.cpp: implementation of the CBitCondition class.
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
  1.1       04/04/08	   PDwivedi  Modify Evaluate() to store mode.
  1.2       08/26/08	   PDwivedi  Modify Evaluate() to check SW & HW Configutation.
 */

#include "stdafx.h"
#include "SBC.h"
#include "BitCondition.h"
#include "Variable.h"
#include "VgaMenuItem.h"
#include "VgaMenu.h"
#include "VgaButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBitCondition::CBitCondition()
{
	Mask1=0;
	Mask2=0;
}

CBitCondition::~CBitCondition()
{

}

/*************************************************************************************/
/*                                                                                   */
/*Function to check Bitvariables conditions like weld mode & VGA,DEPO conditions. 
/*  							
/*************************************************************************************/

bool CBitCondition::Evaluate(CVgaMenuItem *item) const
{
	bool ret=true;
	switch(CaseValue)
	{
	case 0:
	{
		if ((Mask1!=0)  && ((Mask1 & Cond1)!= (CChildView::HWconfiguration & Mask1)))
			ret = false;

		if ((Mask2!=0)  && ((Mask2 & Cond2)!= (CChildView::SWconfiguration & Mask2)))
			ret = false;


	}
	break;
	case 1:
	{
		/*checking Weld mode */
		switch((item->GetType()))
		{
		case CVgaMenu::VGA_Button_OBJECT:
		{
			CVgaButton *ptr=(CVgaButton *)item;
			ptr->ModeSet=bitValue;
		}
		break;
		}
		if((CChildView::WeldMode != (bitValue & CChildView::WeldMode)) &&
				(bitValue != 0xFF))
		{
			ret=false;
		}
		else
		{
			ret=true;
		}

	}
	break;
	default:
		break;
	}
	return ret;
}
