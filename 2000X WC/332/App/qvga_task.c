/* $Header:   D:/SWLab/VMdb/2000Series/App/qvga_task.c_v   1.35   Mar 24 2006 12:52:04   bwadia  $ */
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
 ---------------------------- MODULE DESCRIPTION -------------------------------
            
   Module name: 

   Filename:  qvga_task.c

            Written by: Shishir Madhugiri 
                  Date: 03/05/03 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      1.0          03/05/03       SCM       Initial Version
      1.1          03/20/03       SCM       Added the QVGA handler, Touch screen handler
                                            and intialized the interrupt vector.
      1.2          04/14/03       SCM       Added test code for India. India will replace 
                                            this code with the actual code after testing. 
      1.5          05/28/03       SCM       Added qvgataskid to fix build related problem.
      1.8          06/23/03       JOY       Moved Language strings to "menutext.c".
      1.9          07/25/03       SCM       Checked in for Laura's build.
      1.10         07/30/03       JOY       Added 4 sec of delay, it is required in case of
                                            AE/AO/HH type of Actuators.    
      1.11         07/31/03       JOY       Added QVGA H/W Checking and updated 'QVGAHwAvail' falg.
                                            Initialized BAT Ram Screen Calib points, if it is not
                                            initialized before or Ram is corrupted.
      1.12         09/11/03       JOY       Startup menu is initialized depending on config
                                            -Start Screen setup.
      1.13         09/19/03       JOY       PowerUp Screen-2 is added.
      1.14         09/30/03       JOY       Added security check for Coldstart.
      1.16         10/06/03       JOY       Middle Seg yellow Background stored in ROM.
      1.17         10/14/03       JOY       QVGA image storing is skipped, if it is 
                                            -already stored.
      1.18         10/23/03       JOY       TheMainMenu replaced by QVGATheMainMenu.
                                            'QVGAHwAvail' Flag is made FALSE at powerup.
      1.19         10/30/03       JOY       Removed 'QVGAHwPowerup' Flag.
      1.20         11/14/03       SCM       Added QVGAPresentFlag Flag.
      1.21         06/25/04       JOY       Added new function 'QVGAStoreScrnImage()' to 
                                            Store QVGA screen image.
      1.22         09/06/04       JOY       Checked out for testing.
      1.23         09/09/04       JOY       Removed test code.
      1.24         05-12-05       Aare      First implementation of RVTS task.
      1.25
                   05-12-05       Aare      RVTS task seems to work, test code all removed.
      1.26         05-23-05       Bwadia    Removed copied code form command.c and 
                                            replaced the same with function call
      1.27         07-25-05       Bwadia    QVGA clean up and RVTS messages handling
      1.28         07-28-05       Bwadia    Weld data message command coming from weld
                                            manager supported in RVTS message queue.
      1.29         08-12-05       Bwadia    Added support for export weld data for 
                                            RVTS handler task
      1.30         08-19-05       Bwadia    IsHWConfigured function used to check for
                                            VGA hardware presence 
      1.31         10-11-05       Bwadia    NackError initialized to zero
      1.32         11-22-05       Bwadia    START_WELD_DATA case modified in 
                                            RvtsHandlerTask()  
	  1.33         02-23-06       Bwadia    Modified for tracker issue 4086. Bar graph leds
	                                        scrolls when VGA is powering up.     
	  1.34         02-27-06       LAM       Slowed down the scrolling
      1.35         03-22-06       Bwadia    Scrolling LEDs done only once at power up
 ------------------------------- DESCRIPTION -----------------------------------

 ------------------------------- PSEUDO CODE -----------------------------------       

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>                         /* psos definitions                 */
#include <string.h>
#include "names.h"                        /* psos object definitions          */
#include "opcodes.h"                      
#include "commnmsg.h"                     /* Common message definition        */
#include "ck_qsend.h"                     /* contains function interface      */
#include "beep.h"
#include "qvga_task.h"
#include "bsp.h"
#include <bspfuncs.h>
#include "root.h"
#include "qvga_uart.h"
#include "ticks.h"  
#include "qvgamenu.h"
#include "drawscrn.h" 
#include "util.h"
#include "menu.h" 
#include "led.h"

/* outbound message */

/* inbound message  */
#include "genrlmsg.h"   
#include "touchmsg_qvga.h"
#include "screenmsg_touch.h"
#include "weld_msg.h"
#include "DrawScrn.h" 
#include "param.h"
#include "rtclock.h"
#include "ascii.h"
#include "getmsg.h"
#include "command.h"
#include "ipsatype.h"

/*
 ------------------------------ DEFINES -------------------------------------
*/
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

extern UART_CHANNEL channelA;
extern UART_CHANNEL channelB;
extern CONFIGSETUP CurrentSetup;
extern BOOLEAN ForceDigitalTuneTest;

/*
  -------------------------EXTERNAL FUNCTION DEFINITION----------------------
*/
void VgaInt(void);
void Init_68681_VGA(void);
void VGAAlarmReset (UINT32 dummy);
void ProcessRvtsMenuTaskMsg(UINT32 RvtsMessage);

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/

extern UINT32          NackError;
extern RTC RTCMenu;
extern INBITS Inp;

RVTS_MSG_QUEUE_TYPE RvtsMsgQueue;

UINT16 ProcessHostCommand (UINT32 Value32, UINT16 Function, UINT8  *DataPointer,
                           UINT16 CommandCount, UINT8 * AckBuf, SOURCE_TASK_ID_TYPE Source_Task);  
UINT16 ProcessVGAHostCommand(UINT32 Value32, UINT16 Function, UINT8  *DataPointer,
                           UINT16 CommandCount);
                                          

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/

UINT32 semcount=1;
static UINT32 PsosReturnVal;


/*
 ------------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/
       
UINT32 RvtsQid;
UINT32 RvtsTaskId;
RVTS_MSG_QUEUE_TYPE RvtsMsgQueue;
UINT8 VGAAckBuf[MAXACKLENGTH];
       
UINT32 qvgasemid;
UINT32 QvgaQid;
BOOLEAN StartwithRunMenu;
BOOLEAN QVGAHwAvail = FALSE;
BOOLEAN VGAWelderStateChange = FALSE;
BOOLEAN VGATestKeyPressed = FALSE;
BOOLEAN VGAEstopOn = FALSE;
BOOLEAN VGAEstopOff = FALSE;
BOOLEAN VGAEstopReset = FALSE; 
BOOLEAN VGACalibKey = FALSE;
BOOLEAN VGACalAborted = FALSE;
BOOLEAN VGAWeldStartData = FALSE;
BOOLEAN VGACommStarted = FALSE;
/*************/
BOOLEAN QVGAColdStart;
BOOLEAN QVGAPowerUpDelay;
UINT32 qvgataskid;
/*************/

/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/
                              
/*
 ---------------------------------- CODE ---------------------------------------
*/

void VgaSerialMessageQueue(UART_CHANNEL * channel, UINT8 * data, UINT16 length)
{
   UINT16 i;

   for (i = 0; i < length; i++)
      FifoWriteWait(channel, *data++);
}

/******************************************************************************
 This routine is the handler for the host commands coming through the QVGA UART.
 Processes messages from Weld manager, Touch Screen handlers, Horn Scan, Horn 
 down and Test.
/******************************************************************************/
void RvtsHandlerTask(void)
{
   UART_CHANNEL * channel;
   UINT16          CommandCount;
   UINT16          i;
   UINT32          Value32;
   UINT32          *Host32;
   SINT8 intmask = 0x22;
   UINT16          Function;
 
   t_ident(RVTS_TASK, 0, &RvtsTaskId);
   q_ident(RVTS_Q, Q_NODE_0, &RvtsQid);
   // Install the vector (29). 
   SysSetVector(V_QVGAINT, VgaInt, NORMAL_WRAPPER);
   // Initialize the 68681 UART
   Init_68681_VGA();
   // ok, we're done with initialization
   UpdateHWConfiguration(VGA, FALSE);           
   
   while (TRUE)
   {
         q_receive(RvtsQid, Q_WAIT, Q_WAIT_FOREVER, &RvtsMsgQueue);
         switch (RvtsMsgQueue.generic.common.opcode)
         {
            case OP_TOUCH_SCRN_MSG_READY:
		       if(!VGACommStarted)
		       {
		          VGACommStarted = TRUE;
			      UpdateBarGraph(0);
			   }
               channel = RvtsMsgQueue.RvtsMsg.channel;
               /* initialize queue send indicator and byte check each pass */
               NackError = 0;    /* Assume valid command */
               CommandCount = channel->length + 9;
               /* The majority of commands have 1 32-bit parameter. */
               /* Computing Value32 here saves space by not doing it repeatedly later. */
               Host32 = (UINT32 *) channel->rxbuf;
               Value32 = *Host32;

               Function = channel->code;
               /* Test Code*/
               //SerialMessageQueue("Before\r\n", 8);
      
               if (Function < VGA_HOST_COMMAND)
               /*Welder Host command */
               i = ProcessHostCommand(Value32, Function, 
                                       (UINT8 *) channel->rxbuf,
                                       CommandCount, VGAAckBuf, 
                                       RvtsMsgQueue.generic.common.source_task );
               else
               /*VGA host command for display on SBC*/
               i = ProcessVGAHostCommand(Value32, Function, 
                                         (UINT8 *) channel->rxbuf,
                                         CommandCount);
               VgaSerialMessageQueue(channel, VGAAckBuf, i);
               /* Test Code*/
               //SerialMessageQueue("After\r\n", 7);
               break;
            
            case OP_WELDER_STATE_CHANGE:   //Welder State Change message
               VGAWelderStateChange = TRUE;
               break; 
            
            case START_WELD_DATA:   //Send Weld data
               Host32 = (UINT32 *) RvtsMsgQueue.host_cmd.data_pointer;
               Value32 = *Host32;
               NackError = 0;
               CommandCount = (RvtsMsgQueue.host_cmd.byte_count+9);
               Function = RvtsMsgQueue.generic.common.opcode;

               i = ProcessHostCommand(Value32, Function, 
                                       (UINT8 *) RvtsMsgQueue.host_cmd.data_pointer,
                                       CommandCount, VGAAckBuf, 
                                       RvtsMsgQueue.generic.common.source_task );
               VgaSerialMessageQueue(&channelA, VGAAckBuf, i);
               VgaSerialMessageQueue(&channelB, VGAAckBuf, i);
               break; 

            case OP_FRONT_PANEL_KEYPRESS:         
            
               switch (RvtsMsgQueue.FPKeyMsg.key)
               {
                  case TestKey:    // Test Key Pressed
                     ForceDigitalTuneTest = FALSE;
                     VGATestKeyPressed = TRUE;
                  break;
               
                  case ESTOPMSGON:   // Emergency Stop Pressed
                     VGAAlarmReset(0);                  
                     VGAEstopOn = TRUE;
                     VGAEstopOff = FALSE;
                     VGAEstopReset = FALSE; 
                  break;
               
                  case ESTOPMSGOFF:    // Emergency Stop Released   
                     VGAEstopOn = FALSE;
                     VGAEstopOff = TRUE;
                     VGAEstopReset = FALSE; 
                  break;
               
                  case ESTOPMSGRESET:    // Reset Key pressed after Emergency Stop
                     VGAEstopReset = TRUE; 
                     VGAEstopOff = FALSE;
                     VGAEstopOn = FALSE;
                  break;
               
                  case QVGACALIB_KEY:   // Move to next Calibration menu
                     VGACalibKey = TRUE;
                  break;

                  case CALIBRATION_ABORTED:  // Calibration Aborted
                     VGACalAborted = TRUE;
                  break;                              
               }
               break;  

            case OP_QVGAMENUTASK_MSG:   // Horn Down Messages
               Value32 = RvtsMsgQueue.MenuTaskMsg.message;         
               ProcessRvtsMenuTaskMsg(Value32);
               break;
         }
   } //End of while
}

/*=========================================================================*/
/******************************END******************************************/
/*=========================================================================*/
