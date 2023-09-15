/* $Header:   L:/pvcs/1000/psos332/archives/inc/PRESET0.H_v   2.1   01 Aug 1996 14:47:00   BKYMER  $ */
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
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Preset0                                                     */
/*                                                                          */
/* Filename:    Preset0.c                                                   */
/*                                                                          */
/* Function Name: Save/recall setups                                        */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   03-22-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date        Author       Description                         */
/*  =========  =========   ===========  ===========                         */
/*     0       11-03-95    BEKymer      Original write of code              */
/*     1       03-25-96    BEKymer      Convert to run under pSOS           */
/*     2       04-12-96    LAM          Remove Save/Write Preset            */
/*     3       04-29-96    BEK          Add Copyright notice                */
/*     4       05-01-96    LAM          Remove Verify Preset                */
/*     5       05-15-96    BEKymer      Add proper function prototyping     */
/*                                                                          */
/*                                                                          */




/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void WriteSetup(void);
void ReadSetup(void);
