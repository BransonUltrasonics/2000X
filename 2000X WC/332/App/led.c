/* $Header:   K:/APPS/PVCS Pro/332new/App/LED.C_V   2.36   Apr 11 2003 08:57:30   BKymer  $ */
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
  Name: led.c

 -------------------------------- REVISIONS ------------------------------------

   Revision #     Date        Author    Description
   ----------     -------     ------    -----------
    0             12/4/95     LAM       Initial
    1             8/22/96     LAM       added 2c changes
    2             10/22/96    LAM       fixed upper 4 leds
    3             11-02-96    BEKymer   Make Reset Led blink
    4             01-28-97    LAM       deleted unused vars
    5             01-31-97    PhilJ     Added defines for LeftRight
                                        Led.
    6             05-01-97    BEKymer   Put in hooks for blinking bargraph
    7                         KevinD.   Hooks for dumb terminal
    8.2.15        05-28-97    BEKymer   Fix DTLEDBits so upper 4 leds work
    9             08-08-97    KevinD.   Fixed led bits to work both ways
    2.18          08-22-97    LAM       Fixed led bits and added zero led
    2.19          08-22-97    LAM       Fixed led percent table- zero led
    2.20          09-08-97    BEKymer   Initialize GlobalPowerPercent so it
                                        has a value if GetLedStatus is called
                                        before UpdateBarGraph at power up.
                                        Remove Code to deal with BarGraph
                                        binking
    2.21          09-10-97    LAM       added dtoutput.h
    2.22          10-08-97    LAM       fixed dimming leds at end of cycle
    2.23          10-15-97    LAM       fixed dimming leds when using DT
    2.24          11-11-97    KevinD.   Fix for DCS #1079
    2.25          11-14-97    KevinD.   reFix for DCS #1079
    2.26          11-19-97    BEKymer   Add Update to DTLEDBits in GetLedStatus
    2.27          12-29-97    BJB       Deleted uses of DTEnabled.
                                        Doesn't include dtoutput.h.
    2.28          12-29-97    BJB       Sends messages to terminal to blink
                                         alarm text.
    2.29          01-23-98    BJB       Turns terminal ALARM text on as soon
                                         as RESETLED received so it's visible
                                         if cycling fast.
    2.30          08-19-98    BJB       Changed some terminal function calls
                                         to their new names.
                                        Deleted support for blinking ALARM msg
                                         from GetLedStatus(), now it's in
                                         TermMsInt().
    2.31          09-02-98    BJB       Doesn't turn terminal ALARM message on
                                         in here, RESETLED affects just LED.
                                        Uses new defines for up & down LED
                                         bits.
    2.32          11-06-00    BEKymer   Require reset after estop removed.  Reset led
                                         blinks after estop removed.  Now, while estop
                                         active, navigation can occur and values can be
                                         changed.  In future, consider masking all keys
                                         but reset after estop removed, until reset
                                         is pressed.
    2.33          11-09-00    AT        Switched back to version 2.31 (8L12)
    2.34          11-15-00    AT        Changed UINT16 ResetLedRequiredState from static to global.
    2.34.1        01-15-02    BEKymer   Swapped right and left code in LedOn array
    2.35          04-11-03    BEKymer   Move 2.34.3.0 to tip as 2.35 for 8.10 build
    
    
 ------------------------------- DESCRIPTION -----------------------------------

  UpdateLed is called from the Display Manager. CheckLedStatus is called from
  the welder ISR.



 ----------------------------- INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "332.h"
#include "qsm.h"
#include "led.h"


/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/

#define RESETBLINKRATE     10   /* # of calls Reset led is on/off   */
#define BARGRAPHBLINKRATE   5   /* # of calls Bargraph is on/off    */


/*
 ------------------------------- LOCAL DATA ------------------------------------
*/
UINT8 ScrollingDown;
UINT8 ScrollingUp;
UINT16 DTLEDBits;

static UINT16 LedUpperBits;
static UINT16 LedLowBits;
UINT16 ResetLedRequiredState = FALSE;    /* FALSE:off   TRUE:on */
static UINT16 ResetLedCurrentState = FALSE; /* FALSE:off   TRUE:on */
static UINT16 ResetTimer;

//static UINT16 BargraphTimer;
 // static UINT16 BargraphRequiredState = FALSE;       /* FALSE:off   TRUE:on */
 // static UINT16 BargraphCurrentState = FALSE;        /* FALSE:off   TRUE:on */
 // static UINT16 BargraphBlinkFlag;
static SINT16 GlobalPowerPercent = 0;


static UINT16 LedOn[] =
{
    0x0100,         /* Reset Led                 */
    UPLEDBIT,       /* Scroll Up Led             */
    DOWNLEDBIT,     /* Scroll Down Led           */
    0x4000,         /* Scroll Right Led          */
    0x2000,         /* Scroll Left Led           */
    0x0800,         /* Off Led                   */
    0x6000,         /* Scroll Left/Right Led on  */
    0x0010,         /* 0% On                     */
    0x6f10,         /* All leds (except bar) on  */
};

static UINT16 LedOff[] =
{
    0x0feff,        /* Reset Led                 */
    ~UPLEDBIT,      /* Scroll Up Led             */
    ~DOWNLEDBIT,    /* Scroll Down Led           */
    0x0bfff,        /* Scroll Right Led          */
    0x0dfff,        /* Scroll Left Led           */
    0x0f7ff,        /* Off Led                   */
    0x09fff,        /* Scroll Left/Right Led off */
    0x0ffef,        /* 0% Off                    */
    0x090ef,        /* All leds (except bar) off */
};

/*                            [14]   [15]                */
/*                            ----   ----                */

UINT16 LedTable[21][2] = {{0x0080, 0x0000}, /* 0% Off  */
{0x0080, 0x0001},       /* 5%  */
{0x0080, 0x0003},       /* 10%  */
{0x0080, 0x0007},       /* 15%  */
{0x0080, 0x000f},       /* 20%  */
{0x0080, 0x001f},       /* 25%  */
{0x0080, 0x003f},       /* 30%  */
{0x0080, 0x007f},       /* 35%  */
{0x0080, 0x00ff},       /* 40%  */
{0x0080, 0x01ff},       /* 44%  */
{0x0080, 0x03ff},       /* 50%  */
{0x0080, 0x07ff},       /* 55%  */
{0x0080, 0x0fff},       /* 60%  */
{0x0080, 0x1fff},       /* 65%  */
{0x0080, 0x3fff},       /* 70%  */
{0x0080, 0x7fff},       /* 75%  */
{0x0080, 0xffff},       /* 80%  */
{0x0081, 0xffff},       /* 85%  */
{0x0083, 0xffff},       /* 90%  */
{0x0087, 0xffff},       /* 95%  */
{0x008f, 0xffff}};      /* 100%  */


/*
 ---------------------------------- CODE ---------------------------------------
*/
//#define INCLUDE_UNIT_TEST 1



#if INCLUDE_UNIT_TEST
void TestBarGraph(void);

#endif

void UpdateLED(enum LEDS Led, UINT8 OffOn)
{

    if (Led <= ALLLEDS)
    {
        if (OffOn == OFF)
        {
            DTLEDBits &= (LedOff[Led]); /* BEK  05-28-97 */
        }
        else
        {
            DTLEDBits |= (LedOn[Led]);  /* BEK  05-28-97 */
        }

        LedUpperBits &= 0x008F; /* % leds */
        LedUpperBits |= (DTLEDBits & 0xFFF0);

        if (Led == RESETLED)
        {
            if (OffOn == ON)
            {
                ResetLedRequiredState = TRUE;
                ResetLedCurrentState = TRUE;
            }
            else
            {
                ResetLedRequiredState = FALSE;
                ResetLedCurrentState = FALSE;
            }
            ResetTimer = 0;
        }
    }
}


void GetLedStatus(void)
{

    QsmMap->TxdData[14] = LedUpperBits;
    QsmMap->TxdData[15] = LedLowBits;
    if (ResetLedRequiredState == TRUE)
    {
        if (ResetTimer++ >= RESETBLINKRATE)
        {
            ResetTimer = 0;
            switch (ResetLedCurrentState)
            {
            case FALSE: /* Currently Off, need to turn on  */
                LedUpperBits |= LedOn[RESETLED];
                DTLEDBits |= LedOn[RESETLED];
                ResetLedCurrentState = TRUE;
                break;

            case TRUE:  /* Currently on, need to turn off  */
                LedUpperBits &= LedOff[RESETLED];
                DTLEDBits &= LedOff[RESETLED];
                ResetLedCurrentState = FALSE;
                break;
            }
        }
    }
// if (BargraphBlinkFlag == TRUE) {
    // if (BargraphRequiredState == TRUE) {
    // if (BargraphTimer++ >= BARGRAPHBLINKRATE) {
    // BargraphTimer = 0;
    // switch (BargraphCurrentState) {
    // case FALSE:               /* Currently Off, need to turn on  */
    // LedUpperBits &= 0xfff0;       /* Strip off lower bits     */
    // LedUpperBits |= LedTable[GlobalPowerPercent][0];
    // LedLowBits = LedTable[GlobalPowerPercent][1];
    // BargraphCurrentState = TRUE;
    // break;
    //
    // case TRUE:                /* Currently on, need to turn off  */
    // LedUpperBits &= 0xfff0;       /* Strip off lower bits     */
    // LedUpperBits |= LedTable[0][0];
    // LedLowBits = LedTable[0][1];
    // BargraphCurrentState = FALSE;
    // break;
    // }
    // }
    // }
    // }
}



void UpdateBarGraph(SINT16 PowerPercent)
{
    GlobalPowerPercent = PowerPercent;
    if (PowerPercent > 0)
    {
        PowerPercent = (PowerPercent / 5);
        if (PowerPercent > 20)
            PowerPercent = 20;
    }
    else
    {
        PowerPercent = 0;
    }
    LedUpperBits &= 0xfff0; /* Strip off lower bits     */
    LedUpperBits |= LedTable[PowerPercent][0];  /* Add in new proper bits   */
    LedLowBits = LedTable[PowerPercent][1];
}

#if INCLUDE_UNIT_TEST

UINT16 PowerPercent;


void TestBarGraph(void)
{


    QsmMap->Spcr2.Newqp = 13;
    QsmMap->Spcr2.Endqp = 15;

// these two signals are inverted in hardware

    QsmMap->Spcr0.Cpol = 1;
    QsmMap->Spcr0.Cpha = 0;

//

    QsmMap->Spcr0.Spbr = 8;
    QsmMap->Spcr1.Dsckl = 3;/* CHGED??? 6 */

    QsmMap->Spcr0.Bits = 16;/* Number of bits per transfer */

//  QsmMap->TxdData[13] = 0; /* Configure bargraph */
    QsmMap->TxdData[14] = LedTable[PowerPercent][0];
    QsmMap->TxdData[15] = LedTable[PowerPercent++][1];
    if (PowerPercent >= 21)
        PowerPercent = 0;
}

#endif
