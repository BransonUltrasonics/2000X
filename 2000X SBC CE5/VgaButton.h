// VgaButton.h: interface for the CVgaButton class.
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
  1.1       01/11/08    PDwivedi  Added Member Declarations.  
  1.2		   04/04/08	   PDwivedi  Added Member Variables.
  1.3       04/14/08	   PDwivedi  Added Member Function for Windows Exit.
  1.4       04/14/08	   PDwivedi  Removing function no longer needed. 
  1.5       08/01/08    PDwivedi  Added member for drawing Arrow.
  1.6       08/08/08    PDwivedi  Final Code Clean up.
*/

#if !defined(AFX_VGABUTTON_H__1233EE4C_1F55_45C1_B860_3C25D3CE762C__INCLUDED_)
#define AFX_VGABUTTON_H__1233EE4C_1F55_45C1_B860_3C25D3CE762C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;
class CVgaScreenSetup;
class CVgaButton : public CVgaMenuItem  
{
public:
   CVgaButton(CXmlElement * e);
   CVgaButton(CString str,int X1,int Y1,int X2,int Y2,CString Fun);
   virtual ~CVgaButton();
   int X1,Y1,X2,Y2;
   CRect Rect;
   CString FunName;
   CString MenuName;
   CString MenuNak;
  // void SendCommandForVGAButtonsPreset();
  // void SendCommandForVGAButtonsSavePreset();
   bool ArrowType;
   bool ArrowTypeDown;
   bool ScreenArrowUp;
   bool ScreenArrowDown;
   bool LeftArrow;
   bool RightArrow;
   CString argument;
   CString SubText;
   void DrawArrow(CPoint Start, CPoint Middle, CPoint End,CDC *pDC);

  // void ExitWindowProgram();
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

};

#endif // !defined(AFX_VGABUTTON_H__1233EE4C_1F55_45C1_B860_3C25D3CE762C__INCLUDED_)
