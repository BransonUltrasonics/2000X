/* $Header:   D:/SWLab/VMdb/2000Series/App/ALRMINFO.C_V   1.56.1.1   02 Sep 2008 21:05:24   nhahmed  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,1996,1997       */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                           */
/*                                                                          */
/*************************                         **************************/
                                
/*--------------------------- MODULE DESCRIPTION ---------------------------*/

/*   Module name:     SETUP_ALARM_INFO                                      */
/*                                                                          */
/*   Filename:        alrminfo.c                                            */
/*                                                                          */
/*   Function name:                                                         */


/*-------------------------------- REVISIONS -------------------------------*/


/****************************************************************************/ 
/*                                                                          */
/* Revision  Date      Author    Description                                */
/* ========  ========  =======   ===========                                */
/*   1.0     07-18-97  BEKymer   Initial Version                            */
/*   1.1     07-24-97  BEKymer   Comment out unused sub menu structures     */
/*   1.3     08-12-97  BEKymer   Add additional info for EQ4                */
/*   1.4     08-23-97  NWu       Chngd SE74 to Alarm 1.01                   */
/*   1.5     09-03-97  BEKymer   Changed text string in SE259               */
/*   1.6     09-22-97  BEKymer   Added additional info for EQ21             */
/*   1.7     11-03-97  BEKymer   Change text for EQ4 (was mixed with others)*/
/*   1.8     02-11-98  BEKymer   Add additional info for SE270              */
/*   1.9     03-10-98  BEKymer   Update comments in extern strings          */
/*                                                                          */
/*-----------04-14-98--BEKymer---Start of release 2.5 coding changes--------*/
/*   1.10    04-16-98  BEKymer   Uncomment alarms SE251 & SE257             */
/*                               Fix DCS # 1974, change Abs->Col in         */
/*                               MenuSE22 and MenuSE23                      */
/*   1.11    04-28-98  BEKymer   Change title line for EQ4, EQ1 and EQ21 to */
/*                               Failure of: as per spec.                   */
/*                               Added additional information for alarms:   */
/*                               SE271 - SE277.                             */
/*                               Removed SE277.                             */
/*   1.12    05-14-98  BEKymer   Added additional information for SE43      */
/*   1.13    05-29-98  BEKymer   Added additional information for SE120     */
/*   1.14    06-10-98  BEKymer   Add 'Recal Actuator' text to EQ4 alarm     */
/*   1.15    06-16-98  BEKymer   Jump one menu level higher for alarm EQ4   */
/*   1.16    06-24-98  BJB       Changed NORMAL to BASIC.                   */
/*   1.17    08-21-98  LAM       jump directly to calibration screen after  */
/*                               dooropen alarm                             */
/*   1.18    09-17-98  BEKymer   Change add'l info for EQ4 for AE vs AED    */
/*   1.19    11-02-98  LAM       made sure calibration sequence will be     */
/*                               removed                                    */
/*   1.20    05-07-99  JZ        Changed WeldForceStep1 to WeldForceA       */
/*                                       WeldForceStep2 to WeldForceB       */
/*   1.21    05-19-99  OFI       Put new alarm menus SE73,SE111,SE177, SE179*/
/*                               SE181, SE183-187,SE193-194,SE200-209,SE214,*/
/*                              SE217,SE219,SE227, SE233,SE239-243,SE245-247*/
/*                               SE260-262,SE277.                           */
/*   1.22    05-27-99  OFI       Put New variable MaximumForceInfo,         */
/*                               ErrorCodeInfo, ErrorCode,GoToHorndown,     */   
/*                               text AdjSystemRegulator, and extern        */
/*                               MaximumForce.                              */
/*   1.25.1.1 07-07-99 JZ        added MenuEQ25                             */
/*   1.27     08-03-99 JZ        fixed Error Code text                      */
/*   1.28     08-16-99 JZ        added WeldForceSetupMenu_info, WeldForceA_info*/
/*   1.29     08-31-99 JZ        removed SetPressureToggle and added        */
/*                               GoToHorndown call in SE261                 */
/*   1.30     10-28-99 JZ        removed commented code                     */
/*   1.31     10-29-99 OFI       Changed Model5 to Model1 in ErrorCodeInfo  */
/*   1.32     11-04-99 OFI       Replaced tabs with spaces                  */
/*   1.33     11-04-99 JZ        renamed WeldForceSetupMenu_info to         */
/*                               WeldForceSetupMenuInfo, and WeldForceA_info*/
/*                               to WeldForceAInfo                          */
/*   1.34     02-09-00 OFI       Deleted additional info from menus SE22,23,68,69*/
/*   1.35     04-05-00 JZ        deleted DVS, added Mask1, Cond1, Mask2, Cond2  */
/*                               deleted 'User experience level' from menu strucutures */
/*                               add empty menu SE258                       */
/*                               merged Lang to trunk                       */
/*   1.36     05-26-00 SCM       Checked in for testing by Laura,John.      */
/*   1.37     06-14-00 SCM       Removed unused variable 'LangIndex'.       */
/*   1.38     06-28-00 BEKymer   Changed all MODEL to LEVEL                 */
/*   1.39     10-04-00 BEKymer   Change all references to manual section    */
/*                                7.6 to section 7.5                        */
/*   1.39.1.0 04-24-01 LAM       Added additional info for SE46 Alarm       */
/*   1.39.1.1 05-01-01 LAM       renamed PresetRecalled to ExtPresetRecalled*/
/*   1.40     01-08-01 BEKymer   Added argument to function call in TEXT    */
/*                                and SUBMENU structures, also a little     */
/*                                general cleanup and realignment           */
/*   1.41     10-05-01 LAM       merged 8.3S with preset cleanup            */
/*   1.42     03-09-04 SCM       Fixed pointer problem in menu structure    */
/*                               'ExtPresetRecalled' by type casting to     */
/*                               (SINT32 *)                                 */
/*   1.43     04-06-04 VSharma   Added additional information for SE289,    */
/*                                SE290,SE291,SE292,SE293,SE294,NC14,NC15.  */
/*   1.44     04-19-04 VSharma   Added MenuEQ19.                            */
/*   1.45     05-03-04 VSharma   Removed MenuEQ19. Modified MenuSE295.      */
/*   1.46     05-17-04 VSharma   Modified 'ExtPresetRecalled' struct.       */
/*   1.47     06-23-04 JOY       CHOICE 'ExtGlobalPrinting' added to MenuSE270 */
/*   1.48     07-29-04 JOY       Added Menu MenuSE296ExtSigSetup.           */
/*   1.49     10-11-05 Bwadia    VGA exit button added to all alarm menus   */
/*   1.50     10-28-05 Bwadia    SE299 alarm menu added for empty sequence  */
/*   1.51     11-02-05 Aare      Added #define because of renamed variable in menu2.c */
/*   1.52     12-20-05 Bwadia    USB not present alarm menu added           */
/*                               Modified for tracker issue 4029            */
/*   1.53     01-18-07 NHAhmed   Changes for Setup Alarm SE298.             */
/*   1.54     03-27-07 NHAhmed   Changes for Setup Alarm SE112, SE113,SE114,*/
/*                               SE115, SE122, SE229,SE232,SE236,SE258      */
/*   1.55     05-04-07 NHAhmed   Additional Information for Setup Alarms.   */
/*                               (Tracker #4125, #4135)                     */
/*   1.56     05-23-07 NHAhmed   Additional Information for Setup AlarmsSE297*/
/*   1.57     10-22-07 NHAhmed   Changes done for LangTest phase 0           */
/*   1.58     09-02-08 NHAhmed   CleanUp for multi-language support.        */

/****************************************************************************/


/*------------------------------ DESCRIPTION -------------------------------*/

/* This file deals with setup alarm additional information submenus         */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include <prepc.h>
#include "menu.h"
#include "error.h"
#include "genalarm.h"
#include "keypad.h"                                  
#include "display.h"
#include "sc.h"
#include "param.h"
#include "state.h"
#include "preset.h"

/*------------------------------ LOCAL DATA -------------------------------*/

MENUEND endlistai = { TRUE };

// variable was reworked and renamed in menu2.c, this is a quick fix so
// we don't have to change 100 variable names
#define PretrigDist varPretrigDist

/*----------------------------- EXTERNAL DATA ------------------------------*/
enum ERRORCODE_ARG ErrorCode;
UINT16 ErrorCodeFlag;
extern SINT32 MaximumForce;
extern INBITS Inp;

extern SETUPS_Ver800  CurrentPreset;

/*
 ------------------------------- EXTERNAL FUNCTION -------------------------------
*/

void EnterUserIOAlarmsMenu (UINT32 Dummy);
void ExitMenuAndEnableWeld (void);
/*
 ---------------------------------- CODE ---------------------------------------
*/

