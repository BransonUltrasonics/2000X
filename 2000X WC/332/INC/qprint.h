/* $Header:   L:/pvcs/1000/psos332/archives/inc/QPRINT.H_v   2.1   01 Aug 1996 14:50:46   BKYMER  $ */
#ifndef SERVICE_SERIAL_H
#define SERVICE_SERIAL_H 

/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Filename:      qprint.h


            Written by: Mark Lazarewicz 
                  Date: 02/21/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            02/21/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------

   Contains definitions and prototypes required for service_serial.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"                /* basic system definitions              */
#include <psos.h>                    /* this is needed 'cause of the T_ refs. */
#include "root.h"                    /* contains task level defines           */

/*
 --------------------------------- DEFINES -------------------------------------
*/


/* "QueuePrint" routine return codes are strictly from pSOS+ */

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
 
/* This is the structure that is passed into the service task                 */
/*                                                                            */
/* NOTE: This structure is limited to 16 bytes in size by pSOS+ task          */
/*       parameter passing conventions.                                       */
typedef struct
    {
    struct d_dev dev;               /* Physical device driver to use          */
    SINT8 * queue_name;             /* Physical queue (in/out) to use         */
    SINT8 * task_name;              /* Task name to create                    */
    } SERIAL_TASK_PARAMS_TYPE;


/*
 * Define the size of the memory allocated for private use and the size of the
 * buffers to be created within that memory. It is assumed that the buffer size
 * (SERIAL_BUFFER_SIZE) is always large enough to hold any serial message.
 *
 * NOTE: SERIAL_BUFFER_SIZE must be a power of 2 and > 4.
 */
#define SERIAL_BUFFER_SIZE                  256
#define SERIAL_BUFFER_PARTITION_ALLOC_SIZE   32 * SERIAL_BUFFER_SIZE

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*                                                                            */
/* Usage: status = QueuePrint(qid, "num: %d, str: %s, char: %c", a, b, c);   */
/*                                                                            */
/* Note:  when the variable list is substituted within the format string, the */
/*        expansion (characters added to the format string during variable    */
/*        substitution) must not exceed 128 bytes, otherwise an unrecoverable */
/*        error will be logged.                                               */
/*                                                                            */
UINT32 QueuePrint(
    UINT32 queue_id,
    const SINT8 *format_string,
    ...
    );

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* SERVICE_SERIAL_H */
