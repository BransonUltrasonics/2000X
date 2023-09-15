/* $Header:   D:/databases/VMdb/2000Series/INC/BATTRAM.H_V   2.29   16 Jul 2013 11:45:32   hasanchez  $ */
#ifndef BATTRAM_H
#define BATTRAM_H 

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
      0            12/12/94      Mark Lazarewicz Initial release 
      1            03/14/96      Mark L          Added System Log
      2            04/17/96      Mark L          Add Param Log
      3            04/29/96      LAM             Add CheckBattramDefaults
      4            06/19/96      LAM             Deleted BattramInit
      5            06/26/96      LAM             deleted nvm_type.h
      6            09/25/96      PJ              Moved defines from battram.c
                                                 to battram.h.
      7            01/02/97      PJ              Changed value of WELD_DATA_SIZE.
      8            01/16/97      PJ              Changed initialization address.
      9            03/24/97      PJ              Redefined WELD_DATA_SIZE
      10           03/31/97      PJ              Redefined WELD_DATA_SIZE and
                                                 BATTRAM_INIT_ADDRESS.
      12           07/30/98      BJB             CheckBattramDefaults() modified
                                                 to return BOOLEAN.
     2.13          04/19/99      OFI             Changed for DIAB
     2.15          07-12-00      BEKymer         Completely redefine BBR assignments
     2.16          07-13-00      BEKymer         Remove the " #include testype.h"
     2.17          07-14-00      BEKymer         Added WELD_DATA_SIZE_800
     2.18          08-04-00      JLH             Added defines to support converting V600 and V702 presets to V800.
     2.19          08-08-00      BEKymer         Changed BBR800_ALARM_SIZE from 0x40 to 0x80
                                                 Changed BBR800_HORNSCAN_SIZE from 0x10 to 0x40
                                                 Used defines instead of numbers to aid in the defining of
                                                 the Starting locations for each preset.
     2.20          08-12-00      SCM             Changed BBR800_HORNSCAN_SIZE to 0x80 and removed BBR800_DUPSINFO_START.
     2.21          08-15-00      AT              Changed BBR800_DUPSLOCK_SIZE to 40 (decimal). The rest of data is still
                                                 at same location as before (DUPSLOCK_START + 0x40).
     2.22          08-29-00      JLH             Moved DEPOT_FLAGS structure from battram.c to battram.h.
     2.23          09-11-00      BEKymer         Fixed compilier check for BBR800_DUPSLOCK_SIZE (instead of 0x040)
                                                  Cleaned up all references to BBR800_DUPSLOCK_SIZE
                                                  Add prototype for FixBattRam(void)
     2.24          06-14-01      BEKymer         Add prototype for ClearOutBattRam()
     2.25          08-08-03      JOY             Added chunk to store Touch Screen Calib. points
                                                 starting from BBR800_QVGACALIBSCRN_START.
     2.27          02-25-04      BEKymer         For #define BBR800_UNUSED_SIZE use
                                                  (BBR800_SYSTEM_START + BBR800_SYSTEM_SIZE)
                                                  instead of BBR800_PRESET_START.  Same thing,
                                                  except BBR800_PRESET_START isn't defined
                                                  when needed.
     2.28          03-26-04      LAM             merged 2.27 with added 8 more bytes to the RTC so the battery can be
 
	                                                read
     2.29	   06-26-13      HSanchezZ       add the Preset_RUNNING to the vector as definition.

----------------------------- DESCRIPTIONS ------------------------------------

   This file contains the function prototype and related definitions for the 
   battram module.

---------------------------- INCLUDE FILES ------------------------------------
*/

#include "portable.h"
#ifndef PRESET_H
#include "preset.h"
#endif
#include "weld_obj.h"


/* -------------------------------DEFINES  ------------------------------------- */

#define START_MINIMAL_APP  TRUE

/* ----------  These defines are for Version 8.00  ---------- */

#define SIZE_OF_WELD_DATA          (sizeof(WELD_DATA))
#define NMBR_OF_WELD_HISTORY       50
#define SIZE_OF_COMPRESSED_PRESET  454
#define BBR_INIT_VALUE             0x5555
#define BBR800_START_ADDRESS       0x0168000
#define BBR800_SIZE                0x7FF0      /* 32k - 16 bytes for RTC */
#define MAX_BBR800_ADDRESS         (BBR800_START_ADDRESS + BBR800_SIZE) - 1

/* The first chunk is for pSOS */
#define BBR800_PSOS_START          BBR800_START_ADDRESS
#define BBR800_PSOS_SIZE           0x0100      /* 256 bytes */

/* The next chunk is system stuff like DUPS, alarm mask and BUC menus */
#define BBR800_SYSTEM_START        (BBR800_PSOS_START + BBR800_PSOS_SIZE)
#define BBR800_SYSTEM_SIZE         0x0800      /* 2048 bytes */

/*---------  These are sub sections of the System stuff  --------*/

#define BBR800_ALARM_START         BBR800_SYSTEM_START
#define BBR800_ALARM_SIZE          0x080       /* 128 bytes */

#define BBR800_DUPSLOCK_START      (BBR800_ALARM_START + BBR800_ALARM_SIZE)
#define BBR800_DUPSLOCK_SIZE       0x040       /* 64 bytes */

#define BBR800_DUPS2COP_START      (BBR800_DUPSLOCK_START + BBR800_DUPSLOCK_SIZE)
#define BBR800_DUPS2COP_SIZE       0x040       /* 64 bytes */

#define BBR800_COP2DUPS_START      (BBR800_DUPS2COP_START + BBR800_DUPS2COP_SIZE)
#define BBR800_COP2DUPS_SIZE       0x020       /* 32 bytes */

#define BBR800_HORNSCAN_START      (BBR800_COP2DUPS_START + BBR800_COP2DUPS_SIZE)
#define BBR800_HORNSCAN_SIZE       0x080       /* 128 bytes */

#define BBR800_DUPSBACKUP_START    (BBR800_HORNSCAN_START + BBR800_HORNSCAN_SIZE)
#define BBR800_DUPSBACKUP_SIZE     0x010       /* 16 bytes */

#define BBR800_BUCMENU_START       (BBR800_DUPSBACKUP_START + BBR800_DUPSBACKUP_SIZE)
#define BBR800_BUCMENU_SIZE        0x080       /* 128 bytes */

#define BBR800_DEPOT_START         (BBR800_BUCMENU_START + BBR800_BUCMENU_SIZE)
#define BBR800_DEPOT_SIZE          0x08        /* 8 bytes */

/* The next Chunk is used to Save QVGA Calib. Co-Ordinates */
#define BBR800_QVGASCRNCLAIB_START (BBR800_DEPOT_START + BBR800_DEPOT_SIZE)
#define BBR800_QVGASCRNCALIB_SIZE  0x40        /*64 Bytes*/

#define BBR800_UNUSED_START        (BBR800_QVGASCRNCLAIB_START + BBR800_QVGASCRNCALIB_SIZE)
#define BBR800_UNUSED_SIZE         (BBR800_SYSTEM_START + BBR800_SYSTEM_SIZE - BBR800_UNUSED_START)

/*---------  End of System stuff  ----------*/

/* The next chunk is for system configuration */
#define BBR800_CONFIG_START        (BBR800_SYSTEM_START + BBR800_SYSTEM_SIZE)
#define BBR800_CONFIG_SIZE         0x0400       /* 1024 bytes */

/* The next chunk is for presets */
#define BBR800_PRESET_START        (BBR800_CONFIG_START + BBR800_CONFIG_SIZE)
#define BBR800_PRESET_SIZE         0x4000       /* 16384 bytes */

/* Here are the individual starting locations for each preset */

#define PRESET_0_START             (BBR800_PRESET_START + (PRESET_0 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_1_START             (BBR800_PRESET_START + (PRESET_1 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_2_START             (BBR800_PRESET_START + (PRESET_2 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_3_START             (BBR800_PRESET_START + (PRESET_3 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_4_START             (BBR800_PRESET_START + (PRESET_4 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_5_START             (BBR800_PRESET_START + (PRESET_5 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_6_START             (BBR800_PRESET_START + (PRESET_6 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_7_START             (BBR800_PRESET_START + (PRESET_7 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_8_START             (BBR800_PRESET_START + (PRESET_8 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_9_START             (BBR800_PRESET_START + (PRESET_9 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_10_START            (BBR800_PRESET_START + (PRESET_10 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_11_START            (BBR800_PRESET_START + (PRESET_11 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_12_START            (BBR800_PRESET_START + (PRESET_12 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_13_START            (BBR800_PRESET_START + (PRESET_13 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_14_START            (BBR800_PRESET_START + (PRESET_14 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_15_START            (BBR800_PRESET_START + (PRESET_15 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_16_START            (BBR800_PRESET_START + (PRESET_16 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_17_START            (BBR800_PRESET_START + (PRESET_17 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_18_START            (BBR800_PRESET_START + (PRESET_18 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_19_START            (BBR800_PRESET_START + (PRESET_19 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_20_START            (BBR800_PRESET_START + (PRESET_20 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_21_START            (BBR800_PRESET_START + (PRESET_21 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_22_START            (BBR800_PRESET_START + (PRESET_22 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_23_START            (BBR800_PRESET_START + (PRESET_23 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_24_START            (BBR800_PRESET_START + (PRESET_24 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_25_START            (BBR800_PRESET_START + (PRESET_25 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_26_START            (BBR800_PRESET_START + (PRESET_26 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_27_START            (BBR800_PRESET_START + (PRESET_27 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_28_START            (BBR800_PRESET_START + (PRESET_28 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_29_START            (BBR800_PRESET_START + (PRESET_29 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_30_START            (BBR800_PRESET_START + (PRESET_30 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_31_START            (BBR800_PRESET_START + (PRESET_31 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_32_START            (BBR800_PRESET_START + (PRESET_32 * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_MIN_START           (BBR800_PRESET_START + (PRESET_MIN * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_MAX_START           (BBR800_PRESET_START + (PRESET_MAX * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_CLDSTRT_START       (BBR800_PRESET_START + (PRESET_COLDSTART * SIZE_OF_COMPRESSED_PRESET))
#define PRESET_RUNNING    	       (BBR800_PRESET_START + (PRESET_RUNNING * SIZE_OF_COMPRESSED_PRESET))

/* The next chunk is to save the horn scan graph*/
#define BBR800_HORNGRAPH_START     (BBR800_PRESET_START + BBR800_PRESET_SIZE)
#define BBR800_HORNGRAPH_SIZE      0x0640       /* 1600 bytes)                               */

/* The next chunk is not assigned */
#define BBR800_NOTASSIGNED_START     (BBR800_HORNGRAPH_START + BBR800_HORNGRAPH_SIZE)
//#define BBR800_NOTASSIGNED_SIZE      0x0ACC      /* 2764 bytes */ // Keep this for later
#define BBR800_NOTASSIGNED_SIZE      0x0CC0      /* 3264 bytes */
#define BBR800_NOTASSIGNED_SIZE_1135 0x0CC0      /* 3264 bytes */

/* The last usable chunk is for weld history */
#define BBR800_HISTORY_START_1135  (BBR800_NOTASSIGNED_START + BBR800_NOTASSIGNED_SIZE_1135)
#define BBR800_HISTORY_START       (BBR800_NOTASSIGNED_START + BBR800_NOTASSIGNED_SIZE)
#define BBR800_HISTORY_SIZE        0x1FF0       /* 8176 bytes */
#define WELD_DATA_SIZE_800         (NMBR_OF_WELD_HISTORY * SIZE_OF_WELD_DATA)

#define WELD_DATA_0_START          (BBR800_HISTORY_START + (WELD_DATA_0 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_1_START          (BBR800_HISTORY_START + (WELD_DATA_1 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_2_START          (BBR800_HISTORY_START + (WELD_DATA_2 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_3_START          (BBR800_HISTORY_START + (WELD_DATA_3 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_4_START          (BBR800_HISTORY_START + (WELD_DATA_4 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_5_START          (BBR800_HISTORY_START + (WELD_DATA_5 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_6_START          (BBR800_HISTORY_START + (WELD_DATA_6 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_7_START          (BBR800_HISTORY_START + (WELD_DATA_7 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_8_START          (BBR800_HISTORY_START + (WELD_DATA_8 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_9_START          (BBR800_HISTORY_START + (WELD_DATA_9 *  SIZE_OF_WELD_DATA))
#define WELD_DATA_10_START         (BBR800_HISTORY_START + (WELD_DATA_10 * SIZE_OF_WELD_DATA))
#define WELD_DATA_11_START         (BBR800_HISTORY_START + (WELD_DATA_11 * SIZE_OF_WELD_DATA))
#define WELD_DATA_12_START         (BBR800_HISTORY_START + (WELD_DATA_12 * SIZE_OF_WELD_DATA))
#define WELD_DATA_13_START         (BBR800_HISTORY_START + (WELD_DATA_13 * SIZE_OF_WELD_DATA))
#define WELD_DATA_14_START         (BBR800_HISTORY_START + (WELD_DATA_14 * SIZE_OF_WELD_DATA))
#define WELD_DATA_15_START         (BBR800_HISTORY_START + (WELD_DATA_15 * SIZE_OF_WELD_DATA))
#define WELD_DATA_16_START         (BBR800_HISTORY_START + (WELD_DATA_16 * SIZE_OF_WELD_DATA))
#define WELD_DATA_17_START         (BBR800_HISTORY_START + (WELD_DATA_17 * SIZE_OF_WELD_DATA))
#define WELD_DATA_18_START         (BBR800_HISTORY_START + (WELD_DATA_18 * SIZE_OF_WELD_DATA))
#define WELD_DATA_19_START         (BBR800_HISTORY_START + (WELD_DATA_19 * SIZE_OF_WELD_DATA))
#define WELD_DATA_20_START         (BBR800_HISTORY_START + (WELD_DATA_20 * SIZE_OF_WELD_DATA))
#define WELD_DATA_21_START         (BBR800_HISTORY_START + (WELD_DATA_21 * SIZE_OF_WELD_DATA))
#define WELD_DATA_22_START         (BBR800_HISTORY_START + (WELD_DATA_22 * SIZE_OF_WELD_DATA))
#define WELD_DATA_23_START         (BBR800_HISTORY_START + (WELD_DATA_23 * SIZE_OF_WELD_DATA))
#define WELD_DATA_24_START         (BBR800_HISTORY_START + (WELD_DATA_24 * SIZE_OF_WELD_DATA))
#define WELD_DATA_25_START         (BBR800_HISTORY_START + (WELD_DATA_25 * SIZE_OF_WELD_DATA))
#define WELD_DATA_26_START         (BBR800_HISTORY_START + (WELD_DATA_26 * SIZE_OF_WELD_DATA))
#define WELD_DATA_27_START         (BBR800_HISTORY_START + (WELD_DATA_27 * SIZE_OF_WELD_DATA))
#define WELD_DATA_28_START         (BBR800_HISTORY_START + (WELD_DATA_28 * SIZE_OF_WELD_DATA))
#define WELD_DATA_29_START         (BBR800_HISTORY_START + (WELD_DATA_29 * SIZE_OF_WELD_DATA))
#define WELD_DATA_30_START         (BBR800_HISTORY_START + (WELD_DATA_30 * SIZE_OF_WELD_DATA))
#define WELD_DATA_31_START         (BBR800_HISTORY_START + (WELD_DATA_31 * SIZE_OF_WELD_DATA))
#define WELD_DATA_32_START         (BBR800_HISTORY_START + (WELD_DATA_32 * SIZE_OF_WELD_DATA))
#define WELD_DATA_33_START         (BBR800_HISTORY_START + (WELD_DATA_33 * SIZE_OF_WELD_DATA))
#define WELD_DATA_34_START         (BBR800_HISTORY_START + (WELD_DATA_34 * SIZE_OF_WELD_DATA))
#define WELD_DATA_35_START         (BBR800_HISTORY_START + (WELD_DATA_35 * SIZE_OF_WELD_DATA))
#define WELD_DATA_36_START         (BBR800_HISTORY_START + (WELD_DATA_36 * SIZE_OF_WELD_DATA))
#define WELD_DATA_37_START         (BBR800_HISTORY_START + (WELD_DATA_37 * SIZE_OF_WELD_DATA))
#define WELD_DATA_38_START         (BBR800_HISTORY_START + (WELD_DATA_38 * SIZE_OF_WELD_DATA))
#define WELD_DATA_39_START         (BBR800_HISTORY_START + (WELD_DATA_39 * SIZE_OF_WELD_DATA))
#define WELD_DATA_40_START         (BBR800_HISTORY_START + (WELD_DATA_40 * SIZE_OF_WELD_DATA))
#define WELD_DATA_41_START         (BBR800_HISTORY_START + (WELD_DATA_41 * SIZE_OF_WELD_DATA))
#define WELD_DATA_42_START         (BBR800_HISTORY_START + (WELD_DATA_42 * SIZE_OF_WELD_DATA))
#define WELD_DATA_43_START         (BBR800_HISTORY_START + (WELD_DATA_43 * SIZE_OF_WELD_DATA))
#define WELD_DATA_44_START         (BBR800_HISTORY_START + (WELD_DATA_44 * SIZE_OF_WELD_DATA))
#define WELD_DATA_45_START         (BBR800_HISTORY_START + (WELD_DATA_45 * SIZE_OF_WELD_DATA))
#define WELD_DATA_46_START         (BBR800_HISTORY_START + (WELD_DATA_46 * SIZE_OF_WELD_DATA))
#define WELD_DATA_47_START         (BBR800_HISTORY_START + (WELD_DATA_47 * SIZE_OF_WELD_DATA))
#define WELD_DATA_48_START         (BBR800_HISTORY_START + (WELD_DATA_48 * SIZE_OF_WELD_DATA))
#define WELD_DATA_49_START         (BBR800_HISTORY_START + (WELD_DATA_49 * SIZE_OF_WELD_DATA))

/*--------------- These defines are kept for compatable with older revisions only -------------*/

#define SRAM_EVT_START_OFFSET      0x00100        /* SRAM on every addresses only */

/*----------  Version 6.00  ----------*/

#define BBR_START_ADDRESS_600      0x168000
#define WELD_DATA_START_600        (BBR_START_ADDRESS_600 + 0x06400)    /* SRAM on every addresses only */
#define WELD_DATA_SIZE_600         (50 * sizeof(WELD_DATA_600))
#define BBR_INIT_ADDR_VER600       (WELD_DATA_START_600 + WELD_DATA_SIZE_600 + 2) 
#define V600_PRESET_START          (BBR_START_ADDRESS_600 + SRAM_EVT_START_OFFSET)



/*----------  Version 7.02  ----------*/

#define BBR_START_ADDRESS_702      0x168000
#define WELD_DATA_START_702        (BBR_START_ADDRESS_702 + 0x06400)    /* SRAM on every addresses only */
#define WELD_DATA_SIZE_702         (50 * sizeof(WELD_DATA_702))
#define BBR_INIT_ADDR_VER702       (WELD_DATA_START_702 + WELD_DATA_SIZE_702 + 2) 
#define V702_PRESET_START          (BBR_START_ADDRESS_702 + SRAM_EVT_START_OFFSET)
 


/*----------  Here is an attempt to keep the programmer honest  ----------*/

/* Check the programmer.  See if all individual system stuff sizes added up are still less then the full system chunk */
#if (BBR800_ALARM_SIZE+BBR800_DUPSLOCK_SIZE+BBR800_DUPS2COP_SIZE+BBR800_COP2DUPS_SIZE+BBR800_HORNSCAN_SIZE+BBR800_DUPSINFO_SIZE+BBR800_DUPSBACKUP_SIZE+BBR800_BUCMENU_SIZE+BBR800_DEPOT_SIZE) > BBR800_SYSTEM_SIZE
#error Individual entries have exceeded the space allocated for system stuff in battram.h!
#endif

/* Here add the size for each major section and ensure they still fit within the full 32K */

#if (BBR800_PSOS_SIZE+BBR800_SYSTEM_SIZE+BBR800_CONFIG_SIZE+BBR800_PRESET_SIZE+BBR800_HORNGRAPH_SIZE+BBR800_NOTASSIGNED_SIZE+BBR800_HISTORY_SIZE) > BBR800_SIZE
#error BBR allocation has exceeded its physical size in battram.h!
#endif

/* Now lets check the preset size */

#if (36 * SIZE_OF_COMPRESSED_PRESET) > BBR800_PRESET_SIZE
#error Total size of presets is too large for space allocated for presets!
#endif

/*-------------------------- TYPE DECLARATIONS --------------------------------*/
typedef  enum
      {
      BBR_STATUS_OK = 1u,               /* Successful access to sram */
      BBR_STATUS_BAD_ARG,               /* Out of bound argument     */
      }  BBR_STATUS_TYPE;  

typedef  enum
      {
      BBR_READ = 0u,                    /* Request to read data from nvm */
      BBR_WRITE                         /* Request to write data into nvm*/
      }  BBR_ACCESS_TYPE;

typedef __packed__(2,1) struct {
    SINT16  WasADepot;               /* Was unit ever configured as a depot */
    SINT16  IsADepot; } DEPOT_FLAGS; /* Is unit configured as a depot now   */

typedef enum {
    PSOS_SECTION = 1u,                  /* Access to the pSOS section */
    SYSTEM_SECTION,                     /* Access to entire system section */
    ALARM_SECTION,                      /* Access to alarm masks for customer specials */
    DUPSLOCK_SECTION,                   /* Access to lock information about DUPS presets */
    DUPS2COP_SECTION,                   /* Access to DUPS to COP preset mapping array */
    COP2DUPS_SECTION,                   /* Access to COP to DUPS preset mapping array */
    HORNSCAN_SECTION,                   /* Access to frequency results of horn scan */
    DUPSINFO_SECTION,                   /* Access to results of sonics from DUPS */
    DUPSBACKUP_SECTION,                 /* Access to 4 DUPS parameters that used can be changed */
    BUCMENU_SECTION,                    /* Access to parameters only available in BUC menu */
    DEPOT_SECTION,                      /* Access to configuration information to disable 'Checksum' */
    SYSTEM_UNUSED_SECTION,              /* Access to still unused system stuff section */
    CONFIG_SECTION,                     /* Access to the system configuration section */
    PRESET_SECTION,                     /* Access to the preset section */
    HORN_SECTION,                       /* Access to the horn scan section */
    NOTASSIGNED_SECTION,                /* Access to the unassigned section */
    HISTORY_SECTION                     /* Access to the weld history section */
    } BBR_SECTION_TYPE;
 


#endif /* BBR_H */


/* ------------------------- FUNCTION PROTOTYPES ------------------------------ */

BBR_STATUS_TYPE  BattramAccess(  
                               BBR_ACCESS_TYPE  Request,     
                               BBR_SECTION_TYPE SecID,   
                               UINT8            *DataPointer,
                               UINT32           Offset,     
                               UINT16           ByteCount   );

BOOLEAN CheckBattramDefaults(void);
BOOLEAN IsStartModeMinMode(void);
void FixBattRam(void);
void ClearOutBattRam(void);
