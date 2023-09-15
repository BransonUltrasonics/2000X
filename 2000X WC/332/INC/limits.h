/* $Header:   D:/databases/VMdb/2000Series/INC/LIMITS.H_V   2.10.1.0.1.1   Dec 14 2017 13:08:04   RCHAPA  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/***************************************************************************/
/*                                                                         */
/*  These defines are the bit assignments for both Reject and Suspect      */
/*  limits.  BIT0 is reserved for globally enabling or disabling all       */
/*  limits within the group.  BIT15 is unused.                             */
/*                                                                         */
/*  Notes: The M prefix in each name stands for Minus and the P stands     */
/*         for Plus.  For example, MTIMEBIT is the minus time bit.         */
/*                                                                         */
/*         The FORCE define is for Max Force during the weld cycle.        */
/*                                                                         */
/* Revision  Date      Author     Description                              */
/* ========  ========  =========  ===========                              */
/*   2.2     05-14-98  BEKymer    Moved distance stuff from MODEL3MASK to  */
/*                                MODEL4MASK to align models to marketing  */
/*                                and their swapping of model 3 & 4.       */
/*   2.3     07-10-98  BEKymer    Remove unused TECMODEMASK                */
/*                                Add M/PFORCEBIT to all weld modes,       */
/*                                except CONT                              */
/*   2.4     07-24-98  BEKymer    Add missing limits to ground detect mode */
/*   2.5     02-09-00  OFi        Added MCOLDISTBIT and PCOLDISTBIT to     */
/*                                COLLMODEMASK                             */
/*   2.6     06-29-00  BEKymer    Changed all MODEL_MASK to CTRL_LEVEL_MASK*/
/*   2.8     09-10-05  Aare       Checked in so that 'get' wouldn't        */
/*                                overwrite it.                            */
/*   2.9     03-27-07  NHAhmed    Added #define MTOTCYCLETIMEBIT,          */
/*                                PTOTCYCLETIMEBIT,MWELDCOLLAPSEBIT,       */
/*                                PWELDCOLLAPSEBIT                         */
/*   2.10    03-28-07  YGupta     Modified define for VQSLimits Variables. */
/*   2.12    10-18-12  JWang      Modified define for reject or suspect    */
/*                                limits in Absolute Mode.                 */
/*   2.10.1.0.1.0	 04-13-17 HASanchez   Modified define and reorder according 
 * 								  the rest of the other defines            */
/***************************************************************************/

#define MENERGYBIT    BIT1
#define PENERGYBIT    BIT2
#define MPKPOWERBIT   BIT3
#define PPKPOWERBIT   BIT4
#define MCOLDISTBIT   BIT5
#define PCOLDISTBIT   BIT6
#define MABSDISTBIT   BIT7
#define PABSDISTBIT   BIT8
#define MTRIGDISTBIT  BIT9 
#define PTRIGDISTBIT  BIT10
#define MFORCEBIT     BIT11
#define PFORCEBIT     BIT12
#define MTIMEBIT      BIT13
#define PTIMEBIT      BIT14
#define MSBLFREQBIT   BIT19
#define PSBLFREQBIT   BIT20

#define MTOTCYCLETIMEBIT  BIT9
#define PTOTCYCLETIMEBIT  BIT10
#define MWELDCOLLAPSEBIT  BIT0 
#define PWELDCOLLAPSEBIT  BIT15

/***************************************************************************/
/*                                                                         */
/*  This set of masks is used to eliminate those reject or suspect limits  */
/*  which are invalid in certain weld modes.                               */
/*                                                                         */
/***************************************************************************/

#define TIMEMODEMASK    (MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define ENERGYMODEMASK  (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define PKPOWERMODEMASK (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define COLLMODEMASK    (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT| MCOLDISTBIT | PCOLDISTBIT)
#define ABSMODEMASK     (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT | MABSDISTBIT | PABSDISTBIT)
#define GNDDETMODEMASK  (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define CONTMODEMASK    (MPKPOWERBIT | PPKPOWERBIT)

#define ALLMODEMASK     (MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT | MTIMEBIT | PTIMEBIT)


/***************************************************************************/
/*                                                                         */
/*  This set of masks is used to eliminate those reject or suspect limits  */
/*  which are not valid for certain products or models.                    */
/*                                                                         */
/***************************************************************************/

#define CTRL_LEVEL_tMASK      (0)
#define CTRL_LEVEL_eMASK      (CTRL_LEVEL_tMASK | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MTIMEBIT | PTIMEBIT)
#define CTRL_LEVEL_eaMASK      (CTRL_LEVEL_eMASK)
#define CTRL_LEVEL_dMASK      (CTRL_LEVEL_eaMASK | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define CTRL_LEVEL_fMASK      (CTRL_LEVEL_dMASK)
                            
