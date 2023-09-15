/* $Header:   L:/pvcs/1000/psos332/archives/inc/FLASH.H_v   2.1   01 Aug 1996 14:49:42   BKYMER  $ */
#ifndef  FLASH_DEFINES_H 
#define  FLASH_DEFINES_H
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
/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Flash memory #defines

   Filename: flash.h


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            04/04/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by the flash erase and write
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define FLASH_PROGRAM_SETUP_COMMAND  0x40 /* puts the flash is write mode */

/*
 * stops program command and prepare the part for a read in order to verify the write
 */
#define FLASH_PROGRAM_VERIFY_COMMAND 0xc0 

#define FLASH_ERASE_COMMAND	     0x20 /* erase command */


#define FLASH_ERASE_SETUP_COMMAND    0x20 /* set up for erase command */

/*
 * terminates the erase command and prepares the chip for erase verification
 */
#define FLASH_ERASE_VERIFY_COMMAND   0xa0 

/*
 * terminate programming and puts the chip back into read mode
 */
#define FLASH_RESET_COMMAND	     0xff 

/*
 * maximum number of times a location my be pulsed at one time to program it
 */
#define FLASH_MAX_PROGRAM_ATTEMPTS    25

/*
 * maximum number of times a part may be pulsed at one time to erase it
 */
#define FLASH_MAX_ERASE_ATTEMPTS     1000

#define APP_SW_VERSION_OFFSET      0x447



/* supposed to be 1 uS per count, but add a little extra    */
/* any extra will not hurt the part                         */
#define FLASH_PROG_TIME         15	/* 10 micro seconds */
#define FLASH_VERIFY_SETUP_TIME 12      /* 6 micro seconds  */
#define FLASH_ERASE_TIME        14000

/* F29040 defintions */
#define FLASH040_COMPLETE_BIT_MASK     0x80   /* DQ7, bit 7 */
#define FLASH040_TOGGLE_BIT_MASK       0x40   /* DQ6, bit 6 */
#define FLASH040_TIMEOUT_BIT_MASK      0x20   /* DQ5, bit 5 */
#define FLASH040_SECTOR_ERASE_BIT_MASK 0x08   /* DQ3, bit 5 */

#define FLASH040_ERASE_COMPLETE        0x80
#define FLASH040_ERASE_IN_PROGRESS     0x0
#define FLASH040_OPERATION_TIMEOUT     0x20

/* This mask is used to determine which part is being accessed.  The upper
 * The lower bit determines which part, odd or even.  This is used to mask
 * the incoming address and or in the appropriate flash command.  
 */
#define FLASH_PART_SELECT_MASK      0xF00001


#define FLASH040_WRITE_CMD_ADDR_1       (0x5555 << 0x1)
#define FLASH040_WRITE_CMD_ADDR_2       (0x2AAA << 0x1)
#define FLASH040_WRITE_CMD_ADDR_3       (0x5555 << 0x1)

#define FLASH040_WRITE_CMD_DATA_1       0xAA
#define FLASH040_WRITE_CMD_DATA_2       0x55
#define FLASH040_WRITE_CMD_DATA_3       0xA0

#define FLASH040_READ_CMD_ADDR_1        (0x5555 << 0x1)
#define FLASH040_READ_CMD_ADDR_2        (0x2AAA << 0x1)
#define FLASH040_READ_CMD_ADDR_3        (0x5555 << 0x1)

#define FLASH040_READ_CMD_DATA_1        0xAA
#define FLASH040_READ_CMD_DATA_2        0x55
#define FLASH040_READ_CMD_DATA_3        0xF0

#define FLASH040_CHIP_ERASE_CMD_ADDR_1  (0x5555 << 0x1)
#define FLASH040_CHIP_ERASE_CMD_ADDR_2  (0x2AAA << 0x1)
#define FLASH040_CHIP_ERASE_CMD_ADDR_3  (0x5555 << 0x1)
#define FLASH040_CHIP_ERASE_CMD_ADDR_4  (0x5555 << 0x1)
#define FLASH040_CHIP_ERASE_CMD_ADDR_5  (0x2AAA << 0x1)
#define FLASH040_CHIP_ERASE_CMD_ADDR_6  (0x5555 << 0x1)

#define FLASH040_CHIP_ERASE_CMD_DATA_1  0xAA
#define FLASH040_CHIP_ERASE_CMD_DATA_2  0x55
#define FLASH040_CHIP_ERASE_CMD_DATA_3  0x80
#define FLASH040_CHIP_ERASE_CMD_DATA_4  0xAA
#define FLASH040_CHIP_ERASE_CMD_DATA_5  0x55
#define FLASH040_CHIP_ERASE_CMD_DATA_6  0x10

#endif
