/* $Header:   L:/pvcs/1000/psos332/archives/inc/parmdata.h_v   2.2   18 Sep 1996 10:16:20   lmarkure  $ */
#ifndef PARAMETER_ATTRIBUTES_TYPE_H
#define PARAMETER_ATTRIBUTES_TYPE_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: PARAMETER_ATTRIBUTES_TYPE

   Filename: parameter_attributes_type.h 


            Written by:  
                  Date: 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       1            9/07/96       LAM         deleted paramngr.h

----------------------------- DESCRIPTION -----------------------------------
 Parameter attributes are those qualities of a parameter required by the
 parameter_manager to perform its specified actions.

---------------------------- INCLUDE FILES ----------------------------------
*/
#include "names.h"               /* SOURCE_TASK_ID             */
/*
 --------------------------------- DEFINES -------------------------------------
*/                                         
                   
/* Indicates no task notification is required    */
/* This define must have an invalid p_t_id value */
#define NO_NOTIFICATION MAX_NUMBER_OF_TASKS

/* operator defines */
#define   DO_NOT_CHECK_PARAMETER_RANGE   0
#define   CHECK_RANGE_AND_MASK           CHECK_PARAMETER_RANGE  /* logical AND bit mask */
#define   DO_NOT_WRITE_PARAMETER_TO_NVM  0               /* logical AND bit mask */
#define   WRITE_NVM_AND_MASK             WRITE_NVM
#define   APPL_AND_USER_WRITE_ALLOWED    0
#define   APPL_WRITE_ONLY_AND_MASK       APPL_WRITE_ONLY
#define   SET_TO_DEFAULT_ALLOWED         0
#define   DO_NOT_SET_TO_DEFAULT_AND_MASK DO_NOT_SET_TO_DEFAULT

#define MAX_PARAMETER_STRING_SIZE 8
#define MAX_PARAMETER_VALUE_SIZE  MAX_PARAMETER_STRING_SIZE
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
/* indication for range checking and write to NVM for a parameter */
/* all additional operators must existist in an exclusive bit     */
typedef packed enum
   {                     
   CHECK_PARAMETER_RANGE        = 0x1,    /* bit 0 */
   WRITE_NVM                    = 0x2,    /* bit 1 */
   APPL_WRITE_ONLY              = 0x4,    /* bit 2 */
   DO_NOT_SET_TO_DEFAULT        = 0x8     /* bit 3 */
   } PARAMETER_OPERATOR_TYPE;              


typedef char PARAMETER_STRING_TYPE[MAX_PARAMETER_STRING_SIZE];

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

/* all attributes for a parameter */                                                                         
typedef struct 
   {
   PARAMETER_DATA_TYPE_TYPE     data_type;
   PARAMETER_OPERATOR_TYPE      operator; 
   PARAMETER_VALUE_TYPE         min_limit;
   PARAMETER_VALUE_TYPE         max_limit;
   PARAMETER_VALUE_TYPE         default_value;
   SOURCE_TASK_ID_TYPE          notification_task;
   } PARAMETER_ATTRIBUTES_TYPE;  
           


#endif /* PARAMETER_ATTRIBUTES_TYPE_H */






