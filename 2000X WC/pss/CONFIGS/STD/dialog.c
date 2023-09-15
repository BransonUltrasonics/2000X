/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\dialog.c_v   1.0   Mar 29 1999 13:40:58   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/dialog.c (std) 3.43 98/02/11 19:12:05 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/dialog.c                                     */
/*   DATE:    98/02/11                                                 */
/*   PURPOSE: Startup configuration dialog                             */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*          Copyright 1991 - 1996, Integrated Systems, Inc.            */
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
/***********************************************************************/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author 	Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI 	Original Version

 */
#include "sys_conf.h"
#include <types.h>

ULONG Dialog (void);

#if SC_STARTUP_DIALOG
#include "bsp.h"
#include <bspfuncs.h>
#include <apdialog.h>
#include <sysvars.h>
#include <version.h>
#include <stdarg.h>
#include <pna.h>
#include <types.h>

/*---------------------------------------------------------------------*/
/* Prototypes of External Functions                                    */
/*---------------------------------------------------------------------*/
extern void Prompt(char *, PARM_TYPE, void *);
extern ULONG Print(char *format, ...);

#if BSP_NEW_SERIAL
    #define SerialPollConsts ProbeConsts
    #define SerialPollConin  ProbeConin
    #define SerialPollOn     ProbeEntry
#endif

extern ULONG SerialPollConsts(ULONG);
extern UCHAR SerialPollConin(void);


/*---------------------------------------------------------------------*/
/* Prototypes of Local Functions                                       */
/*---------------------------------------------------------------------*/
#if (BSP_LAN1 && SC_PNA)
static void PrintLan1Params(void);
#endif
#if BSP_SMEM
static void PrintNismParams(UCHAR *NodeNrPrinted);
#endif
#if (BSP_SMEM && SC_PNA)
static void GetSmemParams(UCHAR *GotNodeNr);
#endif

#define INC_BAUD_RATE(x)  x = x != 38400 ? (x << 1) : 57600

/***********************************************************************/
/*        copy: Copy memory                                            */
/*                                                                     */
/*      INPUTS: dstp = pointer to destination                          */
/*              srcp = pointer to source                               */
/*              str_len = number of bytes to copy                      */
/*                                                                     */
/***********************************************************************/
static void copy(void *dstp, void *srcp, long str_len)
{
char *dst, *src;

dst = (char *)dstp;
src = (char *)srcp;
while (str_len--)
   *dst++ = *src++;
}

/***********************************************************************/
/* SysVarsPrint: Print out the current values of SysVars               */
/*                                                                     */
/***********************************************************************/
static void SysVarsPrint(void)
{
#if SC_PNA
UCHAR SmNodeDisplayed;
#endif

char *ptr, AppName[80];

#ifdef SC_APP_NAME
    copy(AppName, SC_APP_NAME, 80);
#else
    copy(AppName, "Application", 80);
#endif

Print("----------------------------------------------------------------"
      "----------\n");

/*---------------------------------------------------------------------*/
/* Print out the operating mode (SysVars.DebugMode)                    */
/*---------------------------------------------------------------------*/
#if SC_PROBE
Print("START-UP MODE:\n");
switch(SysVars.DebugMode)
    {
    case DBG_SA:
        Print("  Boot into pROBE+ stand-alone mode\n");
        break;
    case DBG_XS:
        Print("  Boot into pROBE+ and wait for host debugger via a"
              " serial connection\n");
        break;
#if SC_PNA
    case DBG_XN:
        Print("  Boot into pROBE+ and wait for host debugger via a"
         " network connection\n");
        break;
#endif
#if (SC_PSOS || SC_PSOSM)
    case DBG_AP:
        Print("  Run the %s\n", AppName);
        break;
#endif
    default:
        Print("  Unsupported debug mode\n");
        break;
    }
#else
SysVars.DebugMode = DBG_AP;   /* without pROBE, there's really only one choice... */
#endif

/*---------------------------------------------------------------------*/
/* Print out the networking-related parameters                         */
/*---------------------------------------------------------------------*/
#if SC_PNA
    Print("NETWORK INTERFACE PARAMETERS:\n");
    SmNodeDisplayed = 0;

#   if BSP_LAN1
        PrintLan1Params();
#   endif

#   if BSP_SMEM
        PrintNismParams(&SmNodeDisplayed);
#   endif

#   if (!BSP_LAN1 && !BSP_SMEM)
        Print("  (Board has no network interfaces)\n");
#   endif

    if (SysVars.DefGtwyIP)
        Print("  IP address of default gateway to other networks is %I\n",
              SysVars.DefGtwyIP);
#endif

/*---------------------------------------------------------------------*/
/* Print out the multi-processing (pSOS+m) parameters                  */
/*---------------------------------------------------------------------*/
#if (SC_PSOSM || BSP_SMEM)
Print("MULTIPROCESSING PARAMETERS:\n");
if (SysVars.Kism)
    {
    Print("  This will be node %d in a %d-node pSOS+m system\n",
          SysVars.SmNode, SysVars.Kism);
    Print("  KI directory will be at bus address 0x%x \n",
          SysVars.KismDiraddr);
    }
else
    Print("  This board is currently configured as a single "
          "processor system\n");
#endif

/*---------------------------------------------------------------------*/
/* Print out the hardware-specific parameters                          */
/*---------------------------------------------------------------------*/
Print("HARDWARE PARAMETERS:\n");
Print("  Serial channels will use a baud rate of %d\n", SysVars.DefBaud);
#if BSP_VME
    Print("  This board's memory will reside at 0x%x on the VME bus\n",
          SysVars.VmeBaseAddr);
#endif

#if BSP_PARMS
    BspPrint(BspVars, (void *)Print);
#endif

/*---------------------------------------------------------------------*/
/* Print out application-specific parameters                           */
/*---------------------------------------------------------------------*/
#if SC_APP_PARMS
    if (SysVars.DebugMode == DBG_AP)
        {
        ptr = AppName;
        while (*ptr)       /* Convert application name to upper case */
            {
            if ((*ptr >= 'a') && (*ptr <= 'z'))
                *ptr = *ptr - 0x20;
            ptr++;
            }
        Print("%s PARAMETERS:\n", AppName);
        AppPrint(AppVars, Print);
        }
#endif

Print("  After board is reset, start-up code will wait %d seconds\n",
      SysVars.StartupDelay);

Print("----------------------------------------------------------------"
      "----------\n");
}

/***********************************************************************/
/* PrintLan1Params: Print the current value of LAN-related system      */
/*                  variables                                          */
/*                                                                     */
/*        NOTE: Prints the following members of SysVars: Lan1,         */
/*              Lan1IP, Lan1SubnetMask                                 */
/*                                                                     */
/***********************************************************************/
#if (BSP_LAN1 && SC_PNA)
static void PrintLan1Params(void)
{
if (SysVars.Lan1)
    {
    if (SysVars.Lan1IP == 0)
        Print("  LAN IP address will be obtained from RARP \n");
    else
        Print("  IP address on LAN is %I\n", SysVars.Lan1IP);

    if (SysVars.Lan1SubnetMask)
        Print("  LAN interface's subnet mask is 0x%x\n",
              SysVars.Lan1SubnetMask);
    }
else
    Print("  LAN interface is disabled\n");
}
#endif

/***********************************************************************/
/* PrintNismParams: Print the current value of SMNI-related system     */
/*                  variables                                          */
/*                                                                     */
/*      INPUTS: *NodeNrPrinted = TRUE if node nr has been displayed    */
/*               already                                               */
/*                                                                     */
/*     OUTPUTS: *NodeNrPrinted = set to TRUE if this routine           */
/*               displays the node number.                             */
/*        NOTE: Prints the following members of SysVars: Nism,         */
/*              NismIP, NismSubnetMask, NismDiraddr.  Also (maybe)     */
/*              SmNode.                                                */
/*                                                                     */
/***********************************************************************/
#if BSP_SMEM
static void PrintNismParams(UCHAR *NodeNrPrinted)
{
if (SysVars.Nism)
    {
    Print("  IP address on shared memory is %I\n", SysVars.NismIP);
    if (SysVars.NismSubnetMask)
        Print("  Shared memory interface's subnet mask is 0x%x\n",
              SysVars.NismSubnetMask);
    Print("  Bus address of SMNI directory is 0x%x\n", SysVars.NismDiraddr);
    if (*NodeNrPrinted == 0)
        {
        Print("  This is node number %d in the shared memory system\n",
              SysVars.SmNode);
        *NodeNrPrinted = 1;
        }
    }
else
    Print("  Shared memory interface is disabled\n");
}
#endif

/***********************************************************************/
/*    snmsk_ok: Determine whether a subnet mask is valid               */
/*                                                                     */
/*      INPUTS: ip = IP address of interface                           */
/*              snmsk = Subnet mask to check                           */
/*                                                                     */
/*     RETURNS: TRUE if subnet mask is valid, FALSE if not             */
/*       NOTES: To be valid, subnet mask must meet the following       */
/*              conditions:                                            */
/*                1) All bits which are set must be to the left of     */
/*                   all bits which are clear.                         */
/*                2) If bits are set, they must cover all of the       */
/*                   "host" bits in the network address.               */
/*                3) 0 is considered a valid subnet mask.              */
/*                                                                     */
/***********************************************************************/
#if SC_PNA
static UCHAR snmsk_ok(ULONG ip, ULONG snmsk)
{
int bitpos;
int nr_onebits;

/*---------------------------------------------------------------------*/
/* Subnet mask of 0 is OK                                              */
/*---------------------------------------------------------------------*/
if (snmsk == 0) return 1;

/*---------------------------------------------------------------------*/
/* Check that all bits which are set are higher-order than those which */
/* aren't set.  In other words, all 1 bits must come before all of the */
/* 0 bits.                                                             */
/*---------------------------------------------------------------------*/
bitpos = 31;
nr_onebits = 0;
while ((bitpos >= 0) && (((snmsk >> bitpos) & 1) == 1))
    {
    bitpos--;
    nr_onebits++;
    }

while ((bitpos >= 0) && (((snmsk >> bitpos) & 1) == 0))
    bitpos--;

if (bitpos != -1) return 0;

/*---------------------------------------------------------------------*/
/* Finally, check that the subnet mask is correct for the class of     */
/* network that "ip" belongs to.                                       */
/*---------------------------------------------------------------------*/
if (IN_CLASSC(ip) && (nr_onebits < 24)) return 0;
if (IN_CLASSB(ip) && (nr_onebits < 16)) return 0;
if (IN_CLASSA(ip) && (nr_onebits <  8)) return 0;

return 1;
}
#endif


/***********************************************************************/
/* GetLan1Params: Get the parameters for the LAN interface             */
/*                                                                     */
/*     OUTPUTS:  SysVars.Lan1, SysVars.Lan1IP, and                     */
/*               SysVars.Lan1SubnetMask are updated                    */
/*                                                                     */
/***********************************************************************/
#if (SC_PNA && BSP_LAN1)
static void GetLan1Params(void)
{
UCHAR ans, ErrFlag;

/*---------------------------------------------------------------------*/
/* Find out if they want a LAN interface at all.                       */
/*---------------------------------------------------------------------*/
Prompt("Do you want a LAN interface? ", FLAG, &(SysVars.Lan1));

/*---------------------------------------------------------------------*/
/* LAN IP address                                                      */
/*---------------------------------------------------------------------*/
if (SysVars.Lan1)
    Prompt("This board's LAN IP address(0.0.0.0 = RARP)?",
           IP, &(SysVars.Lan1IP));

/*---------------------------------------------------------------------*/
/* LAN Subnet mask                                                     */
/*---------------------------------------------------------------------*/
if (SysVars.Lan1)
    {
    ans = 'N';
    if (SysVars.Lan1SubnetMask == 0)
        Prompt("Use a subnet mask for the LAN interface? ", CHAR, &ans);
    else
        ans = 'Y';

    if ((ans == 'Y') || (ans == 'y'))
        {
        do
            {
            Prompt("Subnet mask for LAN (0 for none)?",
              IP, &(SysVars.Lan1SubnetMask));
            ErrFlag = FALSE;
            if (!snmsk_ok(SysVars.Lan1IP, SysVars.Lan1SubnetMask))
                {
                Print("That is not a valid subnet mask\a\n");
                ErrFlag = TRUE;
                }
            } while (ErrFlag);
        }
    }
}
#endif


/***********************************************************************/
/* SysVarsChange: Interactively lead the user through the system       */
/*                variables, allowing the option of changing each that */
/*                is relevant.                                         */
/*                                                                     */
/*        NOTE: Exact sequence of questions depends on the values of   */
/*              the parameters.  For example, if they say NO to an     */
/*              Ethernet interface, we don't ask them for an IP        */
/*              address to use on the Ethernet.                        */
/*                                                                     */
/***********************************************************************/
static ULONG SysVarsChange(void)
{
ULONG OperatingMode, MaxAnswer, baud, changed;
UCHAR FirstTime, ErrFlag, ans;
char AppName[80];
UCHAR GotNodeNumber;

GotNodeNumber = 0;
#ifdef SC_APP_NAME
    copy(AppName, SC_APP_NAME, 80);
#else
    copy(AppName, "Application", 80);
#endif

FirstTime = TRUE;
changed = NO;

for (;;)
    {
    if (!FirstTime) SysVarsPrint();
    FirstTime = FALSE;

    /*-----------------------------------------------------------------*/
    /* First, see if they even want to go through with this.  If not,  */
    /* then we're all done.                                            */
    /*-----------------------------------------------------------------*/
    do
        {
        ans = 'M';
        ErrFlag = FALSE;

        Prompt("(M)odify any of this or (C)ontinue?", CHAR, &ans);

        if ((ans == 'C') || (ans == 'c'))
            {
            Delay100ms();    /* Pause so <CR> echo can finish */
            return(changed);
            }

        if ((ans != 'M') && (ans != 'm'))
            {
            Print("Please answer with 'M' to modify or 'C' to continue\a\n");
            ErrFlag = TRUE;
            }
        } while (ErrFlag);

    changed = YES;

    Print("\nFor each of the following questions, you can press <Return>"
          " to select the\n"
          "value shown in braces, or you can enter a new value.\n\n");

    /*-----------------------------------------------------------------*/
    /* Operating mode                                                  */
    /*-----------------------------------------------------------------*/
#   if SC_PROBE
#       if !SC_PNA
           if (SysVars.DebugMode == DBG_AP) SysVars.DebugMode = 3;
#       endif
        do
            {
            Print("How should the board boot?\n");
            Print("  1. pROBE+ stand-alone mode\n");
            Print("  2. pROBE+ waiting for host debugger via "
                  "serial connection\n");
            MaxAnswer = 2;
#           if SC_PNA
                Print("  3. pROBE+ waiting for host debugger via "
                      "a network connection\n");
                MaxAnswer = 3;
#               if (SC_PSOS || SC_PSOSM)
                    Print("  4. Run the %s\n", AppName);
                    MaxAnswer = 4;
#               endif
#           elif (SC_PSOS || SC_PSOSM)
                Print("  3. Run the %s\n", AppName);
                MaxAnswer = 3;
#           endif

            OperatingMode = (ULONG)SysVars.DebugMode;
            Prompt("\nWhich one do you want?", DECIMAL, &OperatingMode);
            SysVars.DebugMode = (UCHAR)OperatingMode;

            if ((OperatingMode == 0) || (OperatingMode > MaxAnswer))
                Print("Please enter a number in the range 1-%d\a\n",
                      MaxAnswer);
            } while ((OperatingMode == 0) || (OperatingMode > MaxAnswer));

#       if !SC_PNA
           if (OperatingMode == 3) SysVars.DebugMode = DBG_AP;
#       endif
#   endif


    /*-----------------------------------------------------------------*/
    /* Network interface parameters                                    */
    /*-----------------------------------------------------------------*/
#   if SC_PNA
        Print("\nNETWORK INTERFACE PARAMETERS:\n");
        GotNodeNumber = 0;

#       if BSP_LAN1
            GetLan1Params();
#       endif

#       if BSP_SMEM
            GetSmemParams(&GotNodeNumber);
#       endif

#       if (!BSP_LAN1 && !BSP_SMEM)
            Print("  (Board has no network interfaces)\n");
#       endif

        ans = SysVars.DefGtwyIP ? 'Y' : 'N';
        Prompt("Should there be a default gateway for packet routing? ",
              CHAR, &ans);
        if ((ans == 'Y') || (ans == 'y'))
            Prompt("What is its IP address?", IP, &(SysVars.DefGtwyIP));
        else
            SysVars.DefGtwyIP = 0;
#   endif

    /*-----------------------------------------------------------------*/
    /* Multiprocessing (pSOS+m) parameters                             */
    /*-----------------------------------------------------------------*/
#if (SC_PSOSM || BSP_SMEM)
    Print("MULTIPROCESSING PARAMETERS:\n");
    ans = SysVars.Kism ? 1 : 0;
    Prompt("Do you want to configure a multiprocessing pSOS+m system?",
           FLAG, &ans);

    if (ans == 0)
        SysVars.Kism = 0;
    else
        {
        Prompt("How many pSOS+m nodes will it contain?", DECIMAL,
               &(SysVars.Kism));

        if (GotNodeNumber && (SysVars.Kism != 0))
            {
            Print("You made this node %d when configuring the SMNI, "
                  "so the SMKI will also use that node number\n",
                  SysVars.SmNode);
            }
        else if (SysVars.Kism != 0)
            {
            do
                {
                Prompt("Which node should this CPU be?", DECIMAL,
                       &(SysVars.SmNode));
                if (SysVars.SmNode == 0)
                    Print("0 is not a valid node number!\a\n");
                if (SysVars.SmNode > SysVars.Kism)
                    Print("Maximum node number is %d\a\n", SysVars.Kism);
                } while ((SysVars.SmNode == 0)
                  || (SysVars.SmNode > SysVars.Kism));
            }
        if (SysVars.Kism != 0)
            Prompt("Bus address of the SMKI directory", HEX,
               &(SysVars.KismDiraddr));
        }
#endif

    /*-----------------------------------------------------------------*/
    /* Hardware-related parameters                                     */
    /*-----------------------------------------------------------------*/
    Print("HARDWARE PARAMETERS:\n");
    do
        {
        Prompt("Baud rate for serial channels", DECIMAL,
               &(SysVars.DefBaud));
        ErrFlag = TRUE;

        baud = BSP_SERIAL_MINBAUD;
        for (; baud <= BSP_SERIAL_MAXBAUD;)
            {
            if (baud == SysVars.DefBaud)
                {
                ErrFlag = FALSE;
                break;
                }
            INC_BAUD_RATE(baud);
            }

        if (ErrFlag)
            {
            Print("Valid baud rates are:");
            baud = BSP_SERIAL_MINBAUD;
            ans = 0;
            for (; baud <= BSP_SERIAL_MAXBAUD;)
                {
                if (ans == 8) 
                   Print("\a\n                     ");
                ans++;
                Print(" %d", baud);
                INC_BAUD_RATE(baud);
                }
            Print("\a\n");
            }
        } while (ErrFlag);

#   if BSP_VME
        Prompt("Bus address of this board's dual-ported memory", HEX,
               &(SysVars.VmeBaseAddr));
#   endif

#   if BSP_PARMS
        BspModify(BspVars, (void *)Print, (void *)Prompt);
#   endif

    /*-----------------------------------------------------------------*/
    /* Application-dependent parameters                                */
    /*-----------------------------------------------------------------*/
#   if SC_APP_PARMS
        if (SysVars.DebugMode == DBG_AP)
            {
            char *ptr = AppName;

            while (*ptr)       /* Convert app name to upper case */
                {
                if ((*ptr >= 'a') && (*ptr <= 'z'))
                    *ptr = *ptr - 0x20;
                ptr++;
                }
            Print("%s PARAMETERS:\n", AppName);
            AppModify(AppVars, Print, Prompt);
            }
#   endif /* SC_APP_PARMS */

    /*-----------------------------------------------------------------*/
    /* Reset delay - don't allow 0 because then it would become        */
    /* impossible to ever change the configuration parameters again!   */
    /*-----------------------------------------------------------------*/
    Prompt("How long (in seconds) should CPU delay before starting up?",
           DECIMAL, &(SysVars.StartupDelay));
    if (SysVars.StartupDelay == 0)
        {
        Print("Minimum delay is 1 second!\a\n");
        SysVars.StartupDelay = 1;
        }
    Print("\n");
    }
}


/***********************************************************************/
/*      Dialog: Conduct the start-up configuration dialog              */
/*                                                                     */
/***********************************************************************/
ULONG Dialog(void)
{
ULONG timeleft, changed;

/*---------------------------------------------------------------------*/
/* Print out the current values.                                       */
/*---------------------------------------------------------------------*/
Print("\n\n\npSOSystem V%s\n", VERSION_STRING);
Print("%s\n", COPYRIGHT);
SysVarsPrint();

/*---------------------------------------------------------------------*/
/* Wait for user to enter input - if a character is received, do the   */
/* dialog thing.  We check for a character 10 times per second.        */
/*---------------------------------------------------------------------*/
Print("To change any of this, press any key within %d seconds\n",
      SysVars.StartupDelay);
timeleft = SysVars.StartupDelay * 10;

/*---------------------------------------------------------------------*/
/* Print() may call SeialPollOff(), so we have to call SerialPollOn()  */
/* here to make sure the serial driver and device in polling mode.     */
/*---------------------------------------------------------------------*/
SerialPollOn();

changed = NO;

while (timeleft > 0)
    {
    if (SerialPollConsts(0))
        {
        UCHAR db;
 
        /**************************************************************/
        /* Because we send a lot of messages out, some hosts may send */
        /* XON/XOFF to the board.  We have to filter such characters  */
        /* out. Normally, XON is defined as DC3 and XOFF is defined   */
        /* as DC1, but the hosts may use other characters for         */
        /* XON/XOFF, so we will discard all characters which are      */
        /* smaller than 0x20 (space) and not equal to '\t', '\n' and  */
        /* '\r'.                                                      */
        /**************************************************************/
        db = SerialPollConin() & 0x7f;
        if(db >= ' ' || db == '\t' || db == '\n' || db == '\r')
           {
           Print("\n");
           changed = SysVarsChange();
           break;
           }
        }
    else
        {
        timeleft--;
        Delay100ms();
        }
    }
return(changed);
}


/***********************************************************************/
/* GetSmemParams: Prompt for the SMNI parameters                       */
/*                                                                     */
/*      INPUTS: *GotNodeNumber = non-zero if node number has already   */
/*                               been obtained                         */
/*     OUTPUTS: *GotNodeNumber = non-zero if node number has been      */
/*                               obtained.                             */
/*                                                                     */
/***********************************************************************/
#if (BSP_SMEM && SC_PNA)
static void GetSmemParams(UCHAR *GotNodeNumber)
{
UCHAR ans, ErrFlag;

/*---------------------------------------------------------------------*/
/* Find out if they want a shared memory interface at all              */
/*---------------------------------------------------------------------*/
Prompt("Do you want a shared memory network interface? ", FLAG,
       &(SysVars.Nism));

if (SysVars.Nism == 0) return;

/*---------------------------------------------------------------------*/
/* Shared memory IP address                                            */
/*---------------------------------------------------------------------*/
Prompt("IP address for shared memory?", IP, &(SysVars.NismIP));

/*---------------------------------------------------------------------*/
/* Shared memory subnet mask                                           */
/*---------------------------------------------------------------------*/
ans = 'N';
if (SysVars.NismSubnetMask == 0)
    Prompt("Use a subnet mask for the shared memory interface? ", CHAR,
           &ans);
else
    ans = 'Y';

if ((ans == 'Y') || (ans == 'y'))
    {
    do
        {
        Prompt("Subnet mask for shared memory interface (0 for none)?",
               HEX, &(SysVars.NismSubnetMask));
        ErrFlag = FALSE;
        if (!snmsk_ok(SysVars.Lan1IP, SysVars.Lan1SubnetMask))
            {
            Print("That is not a valid subnet mask\a\n");
            ErrFlag = TRUE;
            }
        } while (ErrFlag);
    }

/*---------------------------------------------------------------------*/
/* Node number                                                         */
/*---------------------------------------------------------------------*/
if (*GotNodeNumber == 1)
    Print("REMINDER: This will be node # %d in the shared memory system\n",
       SysVars.SmNode);
else
    {
    while (*GotNodeNumber == 0)
        {
        Prompt("Which node number in the shared memory system is this? ",
               DECIMAL, &(SysVars.SmNode));
        if (SysVars.SmNode == 0)
            Print("0 is not a valid node number!\a\n");
        else if (SysVars.SmNode > SMEM_MAXNODES)
            Print("Max allowable node number is %d!\a\n", SMEM_MAXNODES);
        else
            *GotNodeNumber = 1;
        }
    }

/*---------------------------------------------------------------------*/
/* Address of directory                                                */
/*---------------------------------------------------------------------*/
Prompt("Bus address of the SMNI directory? ", HEX, &(SysVars.NismDiraddr));
}
#endif

#else
ULONG Dialog(void){return(NO);}                /* To avoid compiler warnings */
#endif /* SC_STARTUP_DIALOG */
