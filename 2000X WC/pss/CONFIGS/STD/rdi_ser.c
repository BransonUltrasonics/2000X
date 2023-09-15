/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\rdi_ser.c_v   1.0   Mar 29 1999 13:41:02   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/rdi_ser.c (std) 1.20 98/03/26 15:32:26 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/rdi_ser.c                                    */
/*   DATE:    98/03/26                                                 */
/*   PURPOSE: Remote Debug Interface Serial Driver for pROBE+.         */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1995, Integrated Systems, Inc.           */
/*                      ALL RIGHTS RESERVED                            */
/*                                                                     */
/*   Permission is hereby granted to licensees of Integrated Systems,  */
/*   Inc. products to use or abstract this computer program for the    */
/*   sole purpose of implementing a product based on Integrated        */
/*   Systems, Inc. products.   No other rights to reproduce, use,      */
/*   or disseminate this computer program, whether in part or in       */
/*   whole, are granted.                                               */
/*                                                                     */
/*   Integrated Systems, Inc. makes no representation or warranties    */
/*   with respect to the performance of this computer program, and     */
/*   specifically disclaims any responsibility for any damages,        */
/*   special or consequential, connected with the use of this program. */
/*                                                                     */
/*---------------------------------------------------------------------*/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#ifdef __cplusplus
    #if __cplusplus
extern "C" {
    #endif
#endif

#include <sys_conf.h>
#include <bsp.h>

#if ((!BSP_NEW_SERIAL) && SC_PROBE && SC_PROBE_DEBUG && SC_RBUG_PORT)
#include <psos.h>
#include <drv_intf.h>
#include "bsp.h"
#include <bspfuncs.h>
#include <configs.h>
#include <prepc.h>
#include <types.h>

#define RDIPollInit   SerialPollInit
#define RDIPollSts    SerialPollHststs
#define RDIPollIn     SerialPollHstin
#define RDIPollOut    SerialPollHstout
#define RDIPollOn     SerialPollOn
#define RDIPollOff    SerialPollOff
#define RDI_CHANNEL   DEV_SERIAL+SC_RBUG_PORT

#define RETRY_COUNT   20

/***********************************************************************/
/* Error Codes Used for K_FATAL.                                       */
/***********************************************************************/
#define    RDI_NODRV      0x1001  /* No Driver Present for This mode.  */
#define    RDI_INIT       0x1002  /* Driver Initialization Failed.     */
#define    RDI_READ       0x1003  /* Driver Reading Failed.            */
#define    RDI_WRITE      0x1004  /* Driver Writing Failed.            */
#define    RDI_CNTRL      0x1005  /* Driver Control Failed.            */

#define    SMC            0
#define    TMC            1

#define    SUCCESS        0
#define    FAILURE       -1
 
#define    MAX_PKT        3000

/***********************************************************************/
/* Function Code Definitions.                                          */
/***********************************************************************/
#define    Init           0
#define    Open           1
#define    Close          2
#define    Read           3
#define    Write          4
#define    Switch         5
#define    Ioctl          6

/***********************************************************************/
/* Static Data Structures required by this Layer.                      */
/***********************************************************************/
static struct cnsl_ctl_iopb cntrl_parms;
static unsigned char RDIBuffer[MAX_PKT];
static ULONG bytes_pending=0;
static ULONG found_eop=0;
static UCHAR eorchar;

/***********************************************************************/
/* RDISerialDrv: Serves as a intermediate Layer between pROBE+ RBUG    */
/*               and Serial Drivers (Both Lower Level and Console Int. */
/*               Driven Module).                                       */
/*                                                                     */
/* INPUTS      : mode = Communication mode either SMC or TMC.          */
/*               func = Function Code.                                 */
/*               vals = Pointer to a unsigned long array containing    */
/*                                                                     */
/*                      For Init : Long Wrod is the End Of Record Char.*/
/*                                                                     */
/*                      For Read : First Long Wrod is "buffer" to read */
/*                                 to.                                 */
/*                                 Second Long Word is number of bytes */
/*                                 Read.                               */
/*                                                                     */
/*                      For Write: First Long Wrod is "buff" to write  */
/*                                 from.                               */
/*                                 Second Long Word is number of bytes */
/*                                 Write.                              */
/*                                                                     */
/***********************************************************************/
unsigned long
RDISerialDrv (
              unsigned long mode,
              unsigned long func,
              unsigned long *vals
             )
{
void *dummy;
ULONG iopb[4];
UCHAR *buf;
ULONG ret=SUCCESS;
int idx;

    if (mode == TMC)
        {
        /*********************************************************/
        /* Task Mode Communication (TMC).                        */
        /*********************************************************/
        
        switch (func)
            {
            case Switch:
                   /**********************************************/
                   /* Call the RDIPollOff() function to Switch   */
                   /* mode from Polling to Interrupt Driven.     */
                   /**********************************************/
                   RDIPollOff();
                   break;

            case Init:
                   /**********************************************/
                   /* Save the EOR character in the Static Var.  */
                   /**********************************************/
                   eorchar = *((unsigned char *) vals);

                   /**********************************************/
                   /* Initialize The Driver.                     */
                   /**********************************************/
                   if (de_init(RDI_CHANNEL, 0, iopb, &dummy))
                       k_fatal(RDI_INIT, 0);

                   /**********************************************/
                   /* Get the Console Default Properties.        */
                   /**********************************************/
                   cntrl_parms.function = CNSL_GET_PARMS;
                   if (de_cntrl(RDI_CHANNEL, &cntrl_parms, &dummy))
                       k_fatal(RDI_CNTRL, 0);

                   /**********************************************/
                   /* Change the Console Default Properties to   */
                   /* pROBE Needs and Set the Properties using   */
                   /* Device Control routine.                    */
                   /**********************************************/
                   cntrl_parms.function = CNSL_SET_PARMS;
                   cntrl_parms.u.parms.binmode = TRUE;
                   cntrl_parms.u.parms.echo    = FALSE;
                   cntrl_parms.u.parms.nlconv  = FALSE;
                   cntrl_parms.u.parms.eorchar = eorchar;
                   cntrl_parms.u.parms.nonblock= FALSE;
                   if (de_cntrl(RDI_CHANNEL, &cntrl_parms, &dummy))
                       k_fatal(RDI_CNTRL, 0);

                   break;

            case Read:
                   iopb[0] = vals[1];
                   iopb[1] = vals[0];

                   /**********************************************/
                   /* Read from the Device.                      */
                   /**********************************************/
                   if (de_read(RDI_CHANNEL, iopb, &ret))
                       k_fatal(RDI_READ, 0);

                   break;

            case Write:
                   iopb[0] = vals[1];
                   iopb[1] = vals[0];

                   /**********************************************/
                   /* Write to the Device.                       */
                   /**********************************************/
                   if (de_write(RDI_CHANNEL, iopb, &ret))
                       k_fatal(RDI_WRITE, 0);

                   break;

            case Open:
            case Close:
                   /**********************************************/
                   /* Open and Close are not used to control the */
                   /* Device. So return SUCCESS.                 */
                   /**********************************************/
                   ret = 0;
                   break;

            default:
                   /**********************************************/
                   /* Return Error Code for Illegal Function Code*/
                   /**********************************************/
                   ret = FAILURE;
                   break;

            }
        }
    else if (mode == SMC)
        {
        /*********************************************************/
        /* System Mode Communication (TMC).                      */
        /*********************************************************/
        
        switch (func)
            {
            case Switch:
                   /**********************************************/
                   /* Call the RDIPollOn() function to Switch    */
                   /* mode from Interrupt Driven to Polling.     */
                   /**********************************************/
                   RDIPollOn();
                   break;

            case Init:
                   /**********************************************/
                   /* Save the EOR character in the Static Var.  */
                   /**********************************************/
                   eorchar = *((unsigned char *) vals);

                   /**********************************************/
                   /* Initialize The Driver for Polling Mode.    */
                   /* And Switch OFF the Serial Interrupts.      */
                   /**********************************************/
                   RDIPollInit();
                   RDIPollOn();
                   bytes_pending = 0;
                   found_eop=0;

                   break;

            case Read:
                   buf = (unsigned char *) vals[0];
                   /**********************************************/
                   /* If no. of characters to be read is NULL    */
                   /* Return SUCCESS.                            */
                   /**********************************************/
                   if (vals[1] == 0)
                       return ret;

                   /**********************************************/
                   /* If we Already have complete packet then    */
                   /* copy the Local buffer to Caller buffer and */
                   /* return the size of the packet.             */
                   /**********************************************/
                   if (found_eop)
                       {
                       memcpy(buf, RDIBuffer, (size_t)bytes_pending); 
                       ret = bytes_pending;
                       bytes_pending = 0;
                       found_eop=0;
                       }
                   /**********************************************/
                   /* If we do not have complete packet then     */
                   /* Read from the Channel.                     */
                   /**********************************************/
                   else
                       {
                       buf = (unsigned char *) &RDIBuffer[bytes_pending];
                       for (idx = 0; idx < RETRY_COUNT && !found_eop;
                           idx++)
                           {
                           while (RDIPollSts(0) == 1)
                               {
                               *buf = RDIPollIn();
                               bytes_pending++;
                               if (*buf == eorchar)
                                   found_eop = 1;
                               buf++;
                               }
                           }
                       }
                   break;

            case Write:
                   /**********************************************/
                   /* Write all the Characters in polled mode.   */
                   /**********************************************/
                   buf = (unsigned char *) vals[0];
                   ret = vals[1];

                   while (ret--)
                       RDIPollOut(*buf++);
                   ret=0;

                   break;

            default:
                   /**********************************************/
                   /* Return Error Code for Illegal Function Code*/
                   /**********************************************/
                   ret = FAILURE;
                   break;

            }
        }

    return ret;
}
#else

static void rdi_dummy(void);

static void rdi_dummy() {}

#endif /* SC_PROBE && SC_PROBE_DEBUG  && SC_RBUG_PORT */
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
