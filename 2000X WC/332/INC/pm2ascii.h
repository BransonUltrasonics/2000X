/* $Header:   L:/pvcs/1000/psos332/archives/inc/PM2ASCII.H_v   2.2   01 Aug 1996 14:50:28   BKYMER  $ */
#ifndef CONVERT_PM_VALUE_TO_ASCII_H
#define CONVERT_PM_VALUE_TO_ASCII_H
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:   convert_pm_value_to_ascii

   Filename:      pm2asci.h


            Written by: Mark Lazarewicz 
                  Date: 03/13/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       0           03/13/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------

 Function prototype for utility that converts Parameter Manager value to ASCII

 ------------------------------ INCLUDE FILES ----------------------------------
*/



/*
 ------------------------------- DEFINES ---------------------------------------
*/
#define MAX_PARAMETER_STRING_SIZE 8
#define MAX_PARAMETER_VALUE_SIZE  MAX_PARAMETER_STRING_SIZE

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef char PARAMETER_STRING_TYPE[MAX_PARAMETER_STRING_SIZE];

typedef packed enum
   {
   PARAMETER_TYPE_UNKNOWN = 0u,
   PARAMETER_TYPE_UINT8,
   PARAMETER_TYPE_SINT8,
   PARAMETER_TYPE_UINT16,
   PARAMETER_TYPE_SINT16,
   PARAMETER_TYPE_UINT32,
   PARAMETER_TYPE_SINT32,
   PARAMETER_TYPE_FLOAT,
   PARAMETER_TYPE_DFLOAT,
   PARAMETER_TYPE_QFLOAT,
   PARAMETER_TYPE_STRING = 255
   } PARAMETER_DATA_TYPE_TYPE;


/* possible basic C types a parameter could be - size = 4 bytes */
typedef union
  {
  PARAMETER_STRING_TYPE size_string;
  UINT8            size_uint8;
  SINT8            size_sint8;
  UINT16           size_uint16;
  SINT16           size_sint16;
  UINT32           size_uint32;
  SINT32           size_sint32;
  FLOAT            size_float;
  DFLOAT           size_dfloat;
  } PARAMETER_VALUE_TYPE;

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/
void ConvertPmValueToAscii(
   BYTE                                *string_ptr,                /* Put ASCII conversion here      */
   PARAMETER_DATA_TYPE_TYPE            pm_data_type,               /* Parameter data type            */
   PARAMETER_VALUE_TYPE                *parameter_ptr);            /* Parameter value                */


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  

