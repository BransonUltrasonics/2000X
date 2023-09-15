/* $Header:   D:/SWLab/VMdb/2000Series/INC/qvgamenu.h_v   1.21   Oct 22 2007 19:01:12   YGupta  $ */
#ifndef QVGAMENU_H
#define QVGAMENU_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
------------------------------ MODULE DESCRIPTION -----------------------------

------------------------------ REVISIONS --------------------------------------

   Revision #      Date          Author          Description
   ==========      ========      ======          ===========
     1.0           04/17/03       SCM            Initial release
     1.4           28/06/03       JOY            Added enum 'CONFIRM_SCREEN_TYPE'.
                                                 Added TEST_SCREEN, DIAG_SCREEN,
                                                 HORN_SCAN_SCREEN, HORN_SCAN_GRAPH_SCREEN,
                                                 MESSAGE_SCREEN, CONFIRM_SCREEN. to the SCREEN_TYPE
                                                 enum.
     1.5          07/15/03        JOY            'STATUSITEM_GAP' is increased.
                                                 Added define 'COLOR_LIGHTGREY'.
                                                 Added confirm type 'CONFIRM_CALIB_RESET'.
     1.6          07/31/03        JOY            'QVGACALIB_KEY' moved to keypad.h file.
                                                 Added 'HORNDOWN_SCREEN'.
                                                 Added 'ALARM_MENU_SCREEN'.
     1.7          08/28/03        JOY            Added 'ESTOP_SCREEN'.
     1.8          09/06/03        JOY            Added 'POPUP_EXIT_BUTTON'.
     1.9          09/18/03        JOY            Added 'POPUP_MENU_SCREEN'.
                                                 Added  'BUTTON_STATE' struct.
     1.10         09/27/03        JOY            Added  'RADIOLARGE_SCREEN'.
     1.11         10/16/03        JOY            Changed Button periphery to 5 pixels.
     1.12         10/24/03        JOY            Added 'CONFIRM_REPLACE_COLOUMN'.
     1.13         02/25/04        VSharma        Added 'CONFIRM_RESTORE_DEFAULTS'.
     1.14         03/03/04        VSharma        Added 'CONFIRM_WRITE_ALL_PRESET'.
                                                 Added enum TESTING_PRESET_TYPE.
     1.15         07/28/04        JOY            Added define SAVE_BUTTON.
     1.16         08/24/04        JOY            MAX_MENUITEMS_PER_SCREEN  to 8.
                                                  Added Define CONFIRM_RESTORE_USER_IO.
     1.17         08/27/04        JOY            Changed MENU_ITEM_GAP.
     1.18         08/31/04        JOY            Updated enum 'SCREEN_ALIGN'.
     1.19         09/21/04        JOY            Modified define STATUSITEM_Y.      
     1.20         07/25/05        Bwadia         QVGA clean up
     1.21         10-22-07        NHAhmed        Changes done for LangTest phase 0

*/      


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "portable.h"
#include "menu.h"
#include "drawscrn.h"
#include "qvga_task.h"
#include "touchmsg_qvga.h"


extern SINT16 MenuButtonWidthInc;
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
#define MIDDLE_SEGMENT_START        (SINT16)22
#define MIDDLE_SEGMENT_END          (SINT16)211

#define RUN_BUTTON            0
#define MAIN_BUTTON           1
#define SETUP_BUTTON          2
#define GRAPH_BUTTON          3
#define QVGAESTOP_PRESSED    0xDF
#define GOBACK_BUTTON        0xF0
#define GONEXT_BUTTON        0xF1
#define EXIT_BUTTON          0xF2
#define BOTTOM_STATUS_BUTTON 0xF3
#define POPUP_EXIT_BUTTON    0xF4
#define SAVE_BUTTON          0xF5    
#define BUTTON_NONE          0xFF

#define MAX_MENUITEMS_PER_SCREEN    8
#define MAX_ITEMS_5ROW_SCREEN       10
#define MENUITEM_MIDDLE_X   (SINT16)116
#define MENUITEM_Y          (SINT16)38
#define MENU_5ROW_Y         (SINT16)35 
#define MENUITEM_LEFT_X     (SINT16)8
#define MENUITEM_RIGHT_X    (SINT16)173
#define MENUITEM_GAP         17
#define MENU_5ROW_GAP        11
#define MENUITEM_GAP_DIAG    11
#define MENUITEM_HEIGHT      20
#define MENUITEM_WIDTH       MenuButtonWidthInc+85

#define MAX_STATUSITEMS_PER_SCREEN    20
#define STATUSITEM_MIDDLE_X   (SINT16)116
#define STATUSITEM_Y          (SINT16)40 
#define STATUSITEM_LEFT_X     (SINT16)8
#define STATUSITEM_RIGHT_X    (SINT16)173
#define STATUSITEM_GAP           6
#define STATUSITEM_HEIGHT        9

#define RADIOITEM_MIDDLE_X   (SINT16)116
#define RADIOITEM_Y          (SINT16)38 
#define RADIOITEM_LEFT_X     (SINT16)20
#define RADIOITEM_RIGHT_X    (SINT16)185
#define RADIOITEM_GAP         17
#define RADIOITEM_HEIGHT      20
#define RADIOITEM_WIDTH       85

#define DIAG_MENUITEM_Y      (SINT16)30 

#define NUM_BOTTOM_STATUS_BUTTON    4

#define FONT_16X10         1
#define FONT_13X8          2

#define COLOR_NONE         (SINT16)-1

#define PRESSED   'T'
#define RELEASED  'R'

#define SCAN_NONE           (UINT8)0xFF
#define REFRESH_SCAN_STATUS (UINT8)0xFE

/*
 Checks the QVGA touch position(x,y) within (x1,y1) and (x2,y2), if condition
 satisfies returns TRUE else FALSE.
*/

#define IS_TOUCHED(x,y,x1,x2,y1,y2)  ((x > (x1-5) && x < (x2+5)) && (y > (y1-5) && y < (y2+5)))? TRUE:FALSE 
/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
typedef struct
   {
   SINT16   X;
   SINT16   Y;
   }XY_CORDINATE;

typedef struct
   {
   SINT16   X;
   SINT16   Y;
   UINT8 ItemState;
   }MENUITEM_PROPERTY;
      
typedef struct 
   {
   UINT16  SelectedItem;
   UINT16  SelectedPage;
   MENU *MenuPtr;
   } QVGA_MENU_INFO;
   
typedef struct
   {
   SINT16  X;
   SINT16  Y;
   UINT16  Width;
   UINT16  Height;
   UINT8   State;
   UINT8   *ButtonStatePtr;
   } BUTTON_STATE;

typedef enum
   {
   NO_SCREEN,
   MENU_SCREEN,
   POPUP_MENU_SCREEN,
   ALARM_MENU_SCREEN,
   STATUS_SCREEN,
   RADIO_SCREEN,
   RADIOLARGE_SCREEN,
   GRAPH_SCREEN,
   KEYPAD_SCREEN,
   WELD_RESULT_SCREEN,
   SCREEN_SETUP_SCREEN,
   PRESET_SCREEN,
   CONFIRM_SCREEN,
   TEST_SCREEN,
   DIAG_SCREEN,
   HORN_SCAN_SCREEN,   
   HORN_SCAN_GRAPH_SCREEN,
   MESSAGE_SCREEN,
   HORNDOWN_SCREEN,
   ESTOP_SCREEN 
   } SCREEN_TYPE;
   
typedef enum 
   {
   MIDDLE_ALIGN,
   LEFT_RIGHT_ALIGN,
   MIDDLE_ALIGN_5ROW,
   LEFT_RIGHT_ALIGN_5ROW
   } SCREEN_ALIGN; 
   
typedef enum
   {
   CONFIRM_NONE = 0,
   CONFIRM_PRESET_CLEAR,
   CONFIRM_PRESET_SAVE,
   CONFIRM_COLD_START,
   CONFIRM_ACTCOLD_START,
   CONFIRM_PRESET_SAVEMANUEL,
   CONFIRM_CALIB_RESET,
   CONFIRM_WELDCOUNTER_RESET,
   CONFIRM_REPLACE_COLUMN,
   CONFIRM_RESTORE_DEFAULTS,
   CONFIRM_WRITE_ALL_PRESET,
   CONFIRM_RESTORE_USER_IO
   } CONFIRM_SCREEN_TYPE; 
   
typedef enum 
   {
   TOP_MIDDLE_SEG = 1,
   MIDDLE_SEG,
   COMPLETE_SEG
   }REDRAW_SEG;   

typedef enum 
   {
   UNIQUEPRESET = 1,
   ALARMPRESET,
   COLDSTARTPRESET
   }TESTING_PRESET_TYPE;

/*******************************************************************************/
/*                   AHL Mode (Gunze Original Mode)                            */
/*******************************************************************************/


/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/
void QVGADisplayMenu (void);

UINT8 QVGAShowMenuItems(MENU MenuItems[], UINT16 NumMenuItems);

UINT8 GetCurDispItems (UINT16 MaxItems);


void DrawTitle_StatButton (SINT8 title[], UINT16 MaxMenuItems);

void GetDispCoordinate( UINT8 ItemNum );

void DisplayItem (MENU MenuItems[], SINT8 Buffer[], UINT8 SelectedItem,
                   UINT8 ItemNum );
BOOLEAN ProcessMenuItem ( MENU MenuItems[], TOUCH_HANDLER_MSG *TouchMsg,
                          UINT16 NumMenuItems, UINT16 SelectedItem);
                              
UINT16 ProcessRadioItem (MENU LocalMenuItems[], QVGA_MSG_QUEUE_TYPE  QVGAMsgQueue,
                         UINT16 MaxMenuItems, UINT8  RadioItems ); 
 
BOOLEAN IsBottomButtonPressed (TOUCH_HANDLER_MSG *TouchPos);
                         
SCREEN_TYPE GetCurrentScreenType(void);

void ParseMenuLine(SINT8 MenuLine[], SINT8 NameStr[], SINT8 ValStr[]);

void QVGAFillInSpecialChrs(SINT8 *string);

BOOLEAN ProcessPopupExitButton(TOUCH_HANDLER_MSG *TouchMsg);
                              
#endif