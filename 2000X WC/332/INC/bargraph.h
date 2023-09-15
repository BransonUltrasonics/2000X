/* $Header:   L:/pvcs/1000/psos332/archives/inc/BARGRAPH.H_v   2.1   01 Aug 1996 14:52:38   BKYMER  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*     Structures:                                                          */                                                                   
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                          History of changes                              */
/*                          ------------------                              */
/*                                                                          */
/* Rev  Who Date     Description of change                                  */
/* ---- --- -------- ------------------------------------------------------ */
/*                                                                          */


/*  barClearMask is used to clear the display locations within the ram	    */
/*  for the display drivers without interfering with the other bits in the  */
/*  displayRegister data structure.					    */

/*  The barSet[] and dotSet[] values are used to mask in display data into  */
/*  the display ram for the LED bargraphs.				    */
/* There are 21 values for barSet. The 20 lamps, and all lamps off */



unsigned long barSet[21] =
{
    0x00000000,  /* All lamps off */
    0x00000100,  /* Lamp 1 On */
    0x00000300,  /* Lamps 1-2 On */
    0x00000700,  /* Lamps 1-3 On */
    0x00000F00,  /* Lamps 1-4 On */
    0x00001F00,  /* Lamps 1-5 On */
    0x00003F00,  /* Lamps 1-6 On */
    0x00007F00,  /* Lamps 1-7 On */
    0x0000FF00,  /* Lamps 1-8 On */
    0x0001FF00,  /* Lamps 1-9 On */
    0x0003FF00,  /* Lamps 1-10 On */
    0x0007FF00,  /* Lamps 1-11 On */
    0x000FFF00,  /* Lamps 1-12 On */
    0x001FFF00,  /* Lamps 1-13 On */
    0x003FFF00,  /* Lamps 1-14 On */
    0x007FFF00,  /* Lamps 1-15 On */
    0x00FFFF00,  /* Lamps 1-16 On */
    0x01FFFF00,  /* Lamps 1-17 On */
    0x03FFFF00,  /* Lamps 1-18 On */
    0x07FFFF00,  /* Lamps 1-19 On */
    0x0FFFFF00	  /* Lamps 1-20 On */
};

unsigned short LedOn[6] =
{
   0xd0,         /* Reset Led */
   0xa0,         /* Scroll Up Led */
   0x90,         /* Scroll Down Led */
   0xe0,         /* Scroll Up/Down Led */
   0xc0,         /* Off Led */
   0xb0          /* Unused Led */
};

unsigned short LedOff[6] =
{
   0x0f,         /* Reset Led */
   0x0f,         /* Scroll Up Led */
   0x0f,         /* Scroll Down Led */
   0x0f,         /* Scroll Up/Down Led */
   0x0f,         /* Off Led */
   0x0f          /* Unused Led */
};
