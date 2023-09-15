/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUCMAL.C_V   1.24   02 Sep 2008 21:05:36   nhahmed  $ */
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

/*--------------------------- MODULE DESCRIPTION ---------------------------*/

/*   Module name:     CYCLE_MODIFIED_ALARM_TEXT                             */
/*                                                                          */
/*   Filename:        menucmal.c                                            */
/*                                                                          */
/*   Function name:                                                         */
/*                                                                          */
                                  
/*------------------------------- REVISIONS --------------------------------*/

/*   Revision #   Date       Author      Description                        */
/*   ==========   ========   ======      ===========                        */
/*      1.0       07-11-97   BEKymer     Initial Version                    */
/*      1.1       09-02-97   BEKymer     Added TriggerLostMenuHold          */
/*      1.2       10-07-97   BJB         Deleted CMxStepAtxxxxx menu items, */
/*                                       can use same menu items as on weld */
/*                                       setup menu. (CM4, 6, 8, 11)        */
/*      1.3       11-18-97   LAM         replaced finalresults with weldingresults*/
/*      1.4       02-06-98   BJB         Changed type of CM11Actual to      */
/*                                        PERCENTX10.                       */
/*      1.5       02-17-98   BEKymer     Add alarm CM15-CM20                */
/*      1.6       05-28-98   BEKymer     Add text line to CM8 info          */
/*      1.7       08-10-98   BEKymer     Rename ActualCollapse to Actual    */
/*                                       TotalCollapse                      */
/*      1.8       10-06-98   BEKymer     For alarm CM8 display ActualWeld   */
/*                                       Collapse instead of ActualTotalCol.*/
/*                                       Also remove 'Actual=End of Hold'   */
/*      1.9       11-23-98   BEKymer     Add additional information for CM22*/
/*                                       (added at the last minute again)   */
/*      1.10      11-25-98   LAM         chged CM22 to actualforceend       */
/*      1.11      05-13-99   OFI         Add CM5,CM7,CM10,CM13,CM23         */                                                          
/*                                       No Force Alarms                    */
/*      1.12      05-18-99   JZ          changed ActualForceEnd to          */
/*                                       WeldForceEnd                       */
/*      1.13      05-24-99   JZ          corrected name ForceStepAtCol      */
/*      1.13.1.1  07-06-99   JZ          corrected CM13, 23                 */
/*      1.14      11-02-99   OFI         Corrected model number, actuator   */
/*                                       type and operator level for CM5,CM7*/
/*                                       CM10,CM13,CM23                     */
/*      1.15      11-04-99   OFI         Replaced tabs with spaces          */
/*      1.16.6.1  02-08-00   JZ          removed DVS, added mask1, Cond1, mask2, Cond2 */
/*      1.16.6.2  02-23-00   OFI         removed 'User experience level' from menu strucutures */
/*      1.17      04-05-00   JZ          merged Lang to trunk               */
/*      1.18      05-26-00   SCM         Checked in for testing by Laura, John.*/
/*      1.19      06-28-00   BEKymer     Changed all MODEL to LEVEL         */
/*      1.20      01-16-01   BEKymer     Added argument to TEXT and SUBMENU structure calls  */
/*      1.21      04-06-04  VSharma      Added MenuCM17MemoryReset.         */
/*                                       Removed CM17AmpNotReachedSub Menu. */
/*      1.22      07-21-04   JOY         Changed min. Act.type required for textCM_17A, textCM_17B,*/
/*                                       textCM_17C.                        */
/*      1.23      01-12-06   Bwadia      Added VGAExit button               */
/*      1.24      09-02-08   NHAhmed     CleanUp for multi-language support.*/
/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with the cycle modified Alarms and their submenus        */



/*----------------------------- INCLUDE FILES ------------------------------*/
