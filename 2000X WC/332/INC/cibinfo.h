/* $Header:   K:\APPS\PVCS Pro\332new\INC\CIBINFO.H_V   2.8   May 10 1999 14:53:54   lmarkure  $ */
#ifndef CIB_INFO_TYPE_H
#define CIB_INFO_TYPE_H
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: cib_info_type

   Filename: cibinfo.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date         Author          Description
    ==========      ========     ======          ===========
      0            02/08/96      Mark Lazarewicz Initial release 
      1            06/18/96      MAL             Welder protocol
      2            08/11/96      MAL             warnings
      3            04/04/97      LAM             chged wisp
	  2.6		   04/19/99		 OFI			 Changed for DIAB
	  2.7          05/04/99      LAM             fixed packed for DIAB
	  2.8          05/10/99      LAM             added max and min for packed
------------------------------- DESCRIPTION -----------------------------------


 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h" /*   general hardware defines...   */

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define CIB_INFORMATION_SIZE  sizeof(CIB_INFO_TYPE)

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/* This field describes the data contained in the CIB by idenifying the which OSI layer */
/* it is associated with it. */
typedef  enum
   {
   CIBA_TX = 0,
   CIB3_TX = 3,
   CIB4_TX = 4,
   CIB5_TX = 5,
   CIB6_TX = 6,
   CIB7_TX = 7,
   CIBA_RX = 8,
   CIB3_RX = 11,
   CIB4_RX = 12,
   CIB5_RX = 13,
   CIB6_RX = 14,
   CIB7_RX = 15
   } CIB_TYPE_TYPE;

typedef enum
   {
   CIB_INTERFACE_DIST_PORT   = 0,  
   CIB_INTERFACE_LAN_PORT    = 1,   /* .. entries in this typedef (i.e. 0,  .. */
   CIB_INTERFACE_PSTN_PORT   = 2,   /* .. 1, and 2.                            */
   CIB_INTERFACE_USER_PORT   = 3,
   CIB_INTERFACE_UAR         = 9,   /* Indicates UAR needs to be sent          */
   NUMBER_OF_CIB_INTERFACES,
   CIB_INTERFACE_SIZER     = 255u
   } CIB_INTERFACE_TYPE_TYPE;

/* List of the available protocols for the welder station */
typedef enum
   {
   CIB_PROTOCOL_UNDEFINED = 0,
   CIB_PROTOCOL_WEDLC_FS  = 1,
   CIB_PROTOCOL_WEDLC_FA  = 2,
   CIB_PROTOCOL_WEDLC_HX  = 3,
   CIB_PROTOCOL_WEDLC_HC  = 4,
   CIB_PROTOCOL_WEDLC_HN  = 5,
   CIB_PROTOCOL_DRC_I     = 6,
   CIB_PROTOCOL_DRC_II    = 7,
   CIB_PROTOCOL_TRC       = 8,
   CIB_PROTOCOL_ASCII     = 9,
   CIB_PROTOCOL_UAR       = 11,       /* Indicates UAR needs to be sent              */
                                      /* A station parameter defines actual protocol */
   CIB_PROTOCOL_FIPS      = 12,
   CIB_PROTOCOL_NUP       = 13,
   CIB_PROTOCOL_SERVICE   = 14,
   CIB_PROTOCOL_ASCII_IPS = 15,       /*                                */
   CIB_PROTOCOL_SLOAD     = 16,       /* S-Record download                           */
   CIB_PROTOCOL_WISP      = 58,
   
   NUMBER_OF_CIB_PROTOCOLS,
   CIB_PROTOCOL_SIZER    = 255u
   } CIB_PROTOCOL_TYPE_TYPE;

/*
 * Define the buffer size required for each type
 * NOTE: Partition sizes must be a power of 2
 */
#define PROTO_UNDEFINED_BUFFER_SIZE                 256
#define PROTO_WEDLC_FS_BUFFER_SIZE                 2048

#define PROTO_WEDLC_HX_BUFFER_SIZE                 2048

#define PROTO_ASCII_BUFFER_SIZE                       1         /* NOTE: Doesn't use a partition  */
#define PROTO_RSS_N_BUFFER_SIZE                    4096
#define PROTO_UAR_BUFFER_SIZE                       128
#define PROTO_FIPS_BUFFER_SIZE                      128


/* List of types of addresses available in the cib_address field */
typedef enum
   {
   CIB_INDIVIDUAL_ADDRESS = 0,
   CIB_SECTOR_ADDRESS     = 1,
   CIB_ALL_CALL_ADDRESS   = 2,
   CIB_ADDRESS_TYPE_SIZER = 255u
   } CIB_ADDRESS_TYPE_TYPE;

/* Address field */
typedef UINT16 CIB_ADDRESS_TYPE;

/* ATC ID field */
typedef UINT8  CIB_ATC_ID_TYPE;

/* System ID field */
typedef UINT8  CIB_SYSTEM_ID_TYPE;

/* MUX ID field */
typedef UINT8  CIB_MUX_ID_TYPE;

/* types of Minor alarms */
typedef enum
   {
   NO_CIB_MINOR_ALARM = 0,
   CIB_MINOR_ALARM    = 1
   } CIB_MINOR_ALARM_TYPE;

/* types of Major alarms */
typedef enum
   {
   NO_CIB_MAJOR_ALARM = 0,
   CIB_MAJOR_ALARM    = 1
   } CIB_MAJOR_ALARM_TYPE;

/* CIB control fields */
typedef __packed__(4,1) struct
   {
   CIB_INTERFACE_TYPE_TYPE cib_interface_type;
   CIB_PROTOCOL_TYPE_TYPE  cib_protocol_type;
   CIB_ADDRESS_TYPE_TYPE   cib_address_type;
   CIB_ATC_ID_TYPE         cib_atc_id;
   CIB_ADDRESS_TYPE        cib_address;
   CIB_SYSTEM_ID_TYPE      cib_system_id;
   CIB_MUX_ID_TYPE         cib_mux_id;
   UINT8                   cib_alarms_unused : 6;
   UINT8                   cib_major_alarms  : 1;
   UINT8                   cib_minor_alarms  : 1;
   } CIB_CONTROL_TYPE;

/* types of compression used in station */
typedef enum
   {
   CIB_COMPRESSION_OFF   = 0,
   CIB_COMPRESSION_1     = 1,
   CIB_COMPRESSION_2     = 2,
   CIB_COMPRESSION_3     = 3,
   CIB_COMPRESSION_4     = 4,
   CIB_COMPRESSION_SIZER = 255u
   } CIB_COMPRESSION_CONTROL_TYPE;

/* types of fragmentation used in station */
typedef enum
   {
   CIB_MIDDLE_FRAGMENT_TYPE = 0,
   CIB_LAST_FRAGMENT_TYPE   = 1,
   CIB_FIRST_FRAGMENT_TYPE  = 2,
   CIB_SINGLE_FRAGMENT_TYPE = 3,
   CIB_FRAGMENT_SIZER       = 255u
   } CIB_FRAGMENT_TYPE;

/* Layer control fields for CIB */
typedef __packed__(4,1) struct
   {
   CIB_COMPRESSION_CONTROL_TYPE cib_compression_control; /* 1 byte */
   CIB_FRAGMENT_TYPE            cib_fragment_type;       /* 1 byte */
   } CIB_LAYER_CONTROL_TYPE;

/* Data length field */
typedef UINT16 CIB_DATA_LENGTH_TYPE;

/* Structure of the entire CIB Information */
typedef __packed__(4,1) struct
   {
   CIB_TYPE_TYPE           cib_type;           
   CIB_CONTROL_TYPE        cib_control;        /* 9 bytes */
   CIB_LAYER_CONTROL_TYPE  cib_layer_control;  /* 2 bytes */
   CIB_DATA_LENGTH_TYPE    cib_data_length;    /* 2 bytes */
   } CIB_INFO_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

#endif /* CIB_INFO_TYPE_H */











