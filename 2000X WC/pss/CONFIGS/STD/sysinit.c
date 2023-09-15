 /* @(#) pSOSystem/68K V2.2.2: configs/sysinit.c (68k ghs) 3.208 98/06/18 15:16:22 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  configs/std/sysinit.c                                    */
/*   DATE:    98/06/18                                                 */
/*   PURPOSE: Main system configuration file                           */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1998, Integrated Systems, Inc.           */
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
/*                                                                     */
/*   This code in this module controls the configuration of the        */
/*   operating system.  Many configurations are possible, based on     */
/*   these inputs:                                                     */
/*     * Options selected in "sys_conf.h"                              */
/*     * The capabilities of the board-support package being used,     */
/*       as defined in "bsp.h"                                         */
/*     * Answers given to questions in the startup configuration       */
/*       dialog, if it is enabled                                      */
/*                                                                     */
/***********************************************************************/
#if __cplusplus
extern "C" {
#endif

#define _SYSINIT_C 1
#include "sys_conf.h"
#include "bsp.h"
#include <bspfuncs.h>
#include <pna.h>
#include <configs.h>
#include <sysvars.h>
#include <apdialog.h>
#include <version.h>
#include <machine.h>
#include "xception.h"
#include "serial.h"


#if (VERSION != BSP_VERSION)
    #error "BSP_VERSION and pSOSystem VERSION do not match!"
#endif

#if SC_PSOS && SC_PSOSM
    #error "Cannot use both pSOS+ and pSOS+m!"
#endif

#if ((BSP_CPU == 68000) || (BSP_CPU == 68302))

     #if SC_PSOSM
         #define PSOS_INIT psos0m_init
     #else
         #define PSOS_INIT psos0_init
     #endif

#elif ((BSP_CPU == 68010) || (BSP_CPU == 68332) || (BSP_CPU == 68340) || \
     (BSP_CPU == 68070))

     #if SC_PSOSM
         #define PSOS_INIT psos1m_init
     #else
         #define PSOS_INIT psos1_init
     #endif

#elif ((BSP_CPU == 68020) || (BSP_CPU == 68030) || (BSP_CPU == 68040))

     #if SC_PSOSM
         #define PSOS_INIT psos2m_init
     #else
         #define PSOS_INIT psos2_init
     #endif

#elif (BSP_CPU == 68060)
 
     #if SC_PSOSM
         #define PSOS_INIT psos6m_init
     #else
         #define PSOS_INIT psos6_init
     #endif

#elif (BSP_CPU == 68360)

     #if SC_PSOSM
         #define PSOS_INIT psos360m_init
     #else
         #define PSOS_INIT psos360_init
     #endif

#endif 
static void Delay5sec(void);

extern ULONG Dialog(void);

/*---------------------------------------------------------------------*/
/* Compile-time checks                                                 */
/*---------------------------------------------------------------------*/
#if (SC_DEV_SERIAL && BSP_SERIAL)
    #if(SC_DEV_SERIAL > SC_DEVMAX)
        #error "SC_DEV_SERIAL cannot be > SC_DEVMAX"
    #endif
#endif
#if SC_DEV_TIMER
    #if(SC_DEV_TIMER > SC_DEVMAX)
        #error "SC_DEV_TIMER cannot be > SC_DEVMAX"
    #endif
    #if (!SC_PSOS && !SC_PSOSM)
        #error "Must have pSOS+ or pSOS+m in system to use tick timer!"
    #endif
#endif
#if SC_DEV_RAMDISK
    #if(SC_DEV_RAMDISK > SC_DEVMAX)
        #error "SC_DEV_RAMDISK cannot be > SC_DEVMAX"
    #endif
#endif
#if (SC_DEV_SCSI && BSP_SCSI)
    #if(SC_DEV_SCSI > SC_DEVMAX)
        #error "SC_DEV_SCSI cannot be > SC_DEVMAX"
    #endif
#endif
#if (SC_DEV_TFTP)
    #if(SC_DEV_TFTP > SC_DEVMAX)
        #error "SC_DEV_TFTP cannot be > SC_DEVMAX"
    #endif
#endif

/*---------------------------------------------------------------------*/
/* Backward compatibility for renamed define in sys_conf.h             */
/*---------------------------------------------------------------------*/
#if !defined(SC_SD_DEBUG_MODE) && defined(SE_DEBUG_MODE)
    #define SC_SD_DEBUG_MODE SE_DEBUG_MODE
#endif

/*---------------------------------------------------------------------*/
/* External function declarations                                      */
/*---------------------------------------------------------------------*/
extern ULONG Print(char *format, ...);

//#if !BSP_NEW_SERIAL
//    extern void SerialSetup(ULONG, ULONG, ULONG);
//#endif

#define MAGIC 0x05291989
#define ALIGN(addr, boundary) ((addr + boundary - 1) & ~(boundary - 1))

extern UCHAR FreeMemStart[];
#if (GHS || __DIAB)
extern UCHAR TextEnd[];
extern UCHAR DataStart[];
extern UCHAR DataEnd[];
#endif	/* GHS || __DIAB */

extern const char MemErrMsg[] =
  "System Initialization Failed: insufficient memory available!";

NV_Parms NVVars;

#define  PROBE_CON_SER_PORT  SC_PROBE_CONSOLE

#if BSP_NEW_SERIAL
    /*-----------------------------------------------------------------*/
    /* Set up the non pSOS port array.                                 */
    /*-----------------------------------------------------------------*/
    int Non_pSOSChan[SC_NumNon_pSOSChan+2];
    int NumNon_pSOSChan;
    int SysBaud;
    int SysConsole;
#endif

#if ((BSP_CPU == 68040) && (BSP_FPU))
    extern void psos4_fline(void), psos4_bsun(void), psos4_inex(void),
                psos4_dz(void),    psos4_unfl(void), psos4_operr(void),
                psos4_ovfl(void),  psos4_snan(void), psos4_unsupp(void);
#endif

#if ((BSP_CPU == 68060) && (BSP_FPU))
    extern void psos6_fline(void), psos6_inex(void), psos6_dz(void),
                psos6_unfl(void), psos6_operr(void), psos6_ovfl(void),
                psos6_snan(void), psos6_unsupp(void),psos6_effadd(void);
#endif


#ifdef EXCLUDED_VECTORS
    extern const USHORT ExcludedVectors[] = {EXCLUDED_VECTORS, 0};
#else
    extern const USHORT ExcludedVectors[] = {0, 0};
#endif

//extern UCHAR *BspSetup(UCHAR *,  NODE_CT *);
extern UCHAR *PnaSetup(UCHAR *,  NODE_CT *);
extern UCHAR *PrepcSetup(UCHAR *,  NODE_CT *);
extern UCHAR *PsosSetup(UCHAR *,  NODE_CT *);
extern UCHAR *PhileSetup(UCHAR *,  NODE_CT *);
extern UCHAR *PrpcSetup(UCHAR *,  NODE_CT *);
extern UCHAR *ProbeSetup(UCHAR *,  NODE_CT *);
extern UCHAR *PmontSetup(UCHAR *, NODE_CT *);
extern UCHAR *PseSetup(UCHAR *,  NODE_CT *);
#if (SC_PX)
extern UCHAR *PxSetup(UCHAR *,  NODE_CT *);
#endif

#if ((SC_PSOS == USEROM) || (SC_PSOSM == USEROM))

#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PSOS or SC_PSOSM USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

ULONG (*pSOS_tmp)(void);
#else
extern void PSOS_INIT(void);
#endif

#if (SC_PROBE == USEROM)

#if (SC_BOOT_ROM == YES)
#error "Must not use SC_PROBE USEROM with SC_BOOT_ROM code"
#endif /* SC_BOOT_ROM */

ULONG (*pROBE_tmp)(void);
#else
extern long pROBE_Init(void);  /* pROBE+ initialization entry point */
#endif

static const struct SD_parms SysVarsDefaults =
    {
    SC_SD_DEBUG_MODE,
    0, 0, 0,
    SD_STARTUP_DELAY,
    SD_DEF_BAUD,
    SD_VME_BASE_ADDR,
    SD_DEF_GTWY_IP,
    SD_LAN1,
    0, 0, 0,
    SD_LAN1_IP,
    SD_LAN1_SUBNET_MASK,
    SD_SM_NODE,
    SD_NISM,
    0, 0, 0,
    SD_NISM_IP,
    SD_NISM_SUBNET_MASK,
    SD_NISM_DIRADDR,
    SD_KISM,
    SD_KISM_DIRADDR
    };

#if BSP_NEW_SERIAL
                                                    
    extern UCHAR *GSblkSetup(UCHAR *, ULONG, ULONG *);
    extern void SerialInit(void);

    /*-----------------------------------------------------------------*/
    /* Global variables set here used by dipi                          */
    /*-----------------------------------------------------------------*/
    int ProbeCon, ProbeHst;

#endif

#if !BSP_NEW_SERIAL && BSP_PARALLEL
        extern UCHAR *GSblkSetup(UCHAR *, ULONG, ULONG *);
#endif
 
NODE_CT *oldanchor;

/*---------------------------------------------------------------------*/
/* Node anchor and node configuration table.  The anchor address is    */
/* defined in the linker command file.  The anchor is a pointer to the */
/* node configuration table, which in turn points to the configuration */
/* tables for the various components.                                  */
/*---------------------------------------------------------------------*/
extern NODE_CT *anchor;
extern NODE_CT *rom_anchor;
NODE_CT NodeCfg;


/*******************************************************************/
/*    CheckSum: Calculate the checksum for a STORAGE structure     */
/*                                                                 */
/*      INPUTS: StructPtr - ptr to structure to checksum           */
/*              StructSize - size of structure in bytes            */
/*     RETURNS: Checksum for the structure                         */
/*        NOTE: We consider the "checksum" to be simply the sum of */
/*              the individual bytes in the structure              */
/*                                                                 */
/*******************************************************************/
ULONG CheckSum(void *StructPtr, int StructSize)
{
UCHAR *p = (UCHAR *)StructPtr;
USHORT tot = 0;

while(StructSize--)
    tot += *p++ & 0xFF;
return tot;
}


/***********************************************************************/
/* AdjustSysVars: Make any run-time adjustments necessary to the       */
/*                system variables                                     */
/*                                                                     */
/*        NOTE: This should be called after the system variables have  */
/*              been "finalized" by reading from parameter storage and */
/*              possibly being changed by the startup dialog           */
/*                                                                     */
/***********************************************************************/
static void AdjustSysVars(void)
{
#if (!SC_PSOS && !SC_PSOSM)
    if (SysVars.DebugMode == DBG_AP)
        {
        #if SC_STARTUP_DIALOG
            Print("Configured to run application, but pSOS+ not "
              "present, so setting to stand-alone pROBE+\n");
        #endif
        SysVars.DebugMode = DBG_SA;
        }
#endif

#if !SC_PNA
    if (SysVars.DebugMode == DBG_XN)
        {
        #if SC_STARTUP_DIALOG
            Print("Operating mode was remote debug/networked, "
              "but pNA not present\n");
            Print("Setting pROBE+ mode to standalone!\n");
        #endif
        SysVars.DebugMode = DBG_SA;
        }
#endif

#if !SC_RBUG_PORT
    if (SysVars.DebugMode == DBG_XS)
        {
        #if SC_STARTUP_DIALOG
            Print("Operating mode was remote debug/Serial, but "
              "SC_RBUG_PORT is not set.\n");
            Print("Setting pROBE+ mode to standalone!\n");
        #endif
        SysVars.DebugMode = DBG_SA;
        }
#endif

#if !BSP_LAN1
    if (SysVars.Lan1)
        {
        #if SC_STARTUP_DIALOG
            Print("LAN interface requested, but BSP does not "
              "support it\n");
        #endif
        SysVars.Lan1 = 0;
        }
#endif
}

/***********************************************************************/
/* BuildConfigTables: Build the component configuration tables, using  */
/*                    information from the system variables (SysVars). */
/*                                                                     */
/*       INPUT: FreeMemPtr - Pointer to first byte of available memory */
/*                                                                     */
/***********************************************************************/
static UCHAR *BuildConfigTables(UCHAR *FreeMemPtr)
{
    UINT16 j;
    
#if (SC_BOOT_ROM == YES)
    oldanchor = (void *)0;
#else /* SC_BOOT_ROM */
    oldanchor = rom_anchor;
#endif /* SC_BOOT_ROM */

/* This is where the component's configuration functions are called */
#if SC_PROBE
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = ProbeSetup(FreeMemPtr, &NodeCfg);
#endif
#if SC_PNA
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = PnaSetup(FreeMemPtr, &NodeCfg);
#endif
#if SC_PREPC
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = PrepcSetup(FreeMemPtr, &NodeCfg);
#endif
#if (SC_PHILE || SC_DEV_RAMDISK || SC_DEV_SCSI)
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = PhileSetup(FreeMemPtr, &NodeCfg);
#endif
#if SC_PRPC
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = PrpcSetup(FreeMemPtr, &NodeCfg);
#endif
#if SC_PX
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = PxSetup(FreeMemPtr, &NodeCfg);
#endif
#if SC_PSE
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = PseSetup(FreeMemPtr, &NodeCfg);
#endif
#if SC_PMONT
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = PmontSetup(FreeMemPtr, &NodeCfg);
#endif

/*---------------------------------------------------------------------*/
/* Perform any BSP specific configuration functions. Most of the node  */
/* configuration table can be used by BspSetup(). Only PsosSetup has   */
/* not been done when BspSetup is called. BspSetup may rely on this.   */
/*---------------------------------------------------------------------*/
//FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
//FreeMemPtr = BspSetup(FreeMemPtr, &NodeCfg);

 for(j=0; j< 256; j++){
	     SysSetVector(j, UserInt, NORMAL_WRAPPER);
   }
   SysSetVector(V_BUSERR, BusInt, NORMAL_WRAPPER);
   SysSetVector(V_ADDRERR, AddInt, NORMAL_WRAPPER);
   SysSetVector(V_ILLEGALINSTR, IllegalInstr, NORMAL_WRAPPER);
   SysSetVector(V_ZERODIVIDE, ZeroDivide, NORMAL_WRAPPER);
   SysSetVector(V_CHKCHK2, CHKCHK2, NORMAL_WRAPPER);
   SysSetVector(V_TRAPCCTRAPV, TRAPccTRAPv, NORMAL_WRAPPER);
   SysSetVector(V_PRIVILEGEVIO, PrivilegeVio, NORMAL_WRAPPER);
   SysSetVector(V_TRACE, PrivilegeVio, NORMAL_WRAPPER);
   SysSetVector(V_SPURIOUS, SpurInt, NORMAL_WRAPPER);




#if (SC_PSOS || SC_PSOSM)
    /*-----------------------------------------------------------------*/
    /* PsosSetup() must be called after all other Setup functions.     */
    /*                                                                 */
    /* If pSOS+ has been configured into the system, the FreeMemPtr is */
    /* now part of pSOS+ region zero!  So it can't be used to allocate */
    /* any more memory after this.                                     */
    /*-----------------------------------------------------------------*/
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = PsosSetup(FreeMemPtr, &NodeCfg);
#endif

/*---------------------------------------------------------------------*/
/* Finally, finish up node configuration table and set node anchor to  */
/* point to it.                                                        */
/*---------------------------------------------------------------------*/
#if (BSP_CPU == 68000)
    NodeCfg.cputype = 0;
#elif (BSP_CPU == 68010)
    NodeCfg.cputype = 1;
#elif (BSP_CPU == 68020)
    NodeCfg.cputype = 2;
#elif (BSP_CPU == 68030)
    NodeCfg.cputype = 3;
#elif (BSP_CPU == 68040)
    NodeCfg.cputype = 4;
#elif (BSP_CPU == 68060)
    NodeCfg.cputype = 6;
#elif (BSP_CPU == 68070)
    NodeCfg.cputype = 7;
#elif ((BSP_CPU == 68332) || (BSP_CPU == 68340))
    NodeCfg.cputype = 33;
#elif (BSP_CPU == 68360)
    NodeCfg.cputype = 36;
#else
    #error "UNKNOWN BSP_CPU TYPE"
#endif

#if (BSP_FPU == YES)
    NodeCfg.cputype |= 0x100;
#endif
 
#if (BSP_MMU == YES)
    NodeCfg.cputype |= 0x200;
#endif

anchor = &NodeCfg;

#if (SC_BOOT_ROM == YES)
rom_anchor = &NodeCfg;
#endif /* SC_BOOT_ROM */

return(FreeMemPtr);
}


/***********************************************************************/
/*     SysInit: Initialize system variables, conduct startup dialog    */
/*              if configured, and set up component configuration      */
/*              tables.                                                */
/*                                                                     */
/*        NOTE: Interrupts are assumed to be disabled upon entry to    */
/*              this routine.                                          */
/*                                                                     */
/***********************************************************************/
void SysInit(void)
{
ULONG csum, magic, StorageOffset, size, rc;
ULONG storage_update=FALSE, error_flag;
UCHAR *FreeMemPtr, *LastByte;
UCHAR *local, *dest;

#if BSP_NEW_SERIAL
    int i;
#endif

#if (SC_SD_PARAMETERS == SYS_CONF)
    UCHAR DebugModeSv;
#endif

/*---------------------------------------------------------------------*/
/* Copy initialized data from ROM to RAM.  This code is only needed    */
/* when you are placing your system in ROM.  For more information on   */
/* burning your system into ROM see link_sys.cmd.                      */
/*---------------------------------------------------------------------*/
#ifdef MRI

    local = (UCHAR *) ASM("\tmove.l\t#.startof.(??INITDATA),d0");
    if (ASM (UINT, "\tmove.l\t#.sizeof.(??INITDATA),d0") > 2)
        {
        local += 2;
    
        size = (ULONG)(((UCHAR)*local << 24) |
                       ((UCHAR)*(local+1) << 16) |
                       ((UCHAR)*(local+2) << 8) |
                        (UCHAR)*(local+3));
        local += 4;

        dest = (UCHAR *)(((UCHAR)*local << 24) |
                        ((UCHAR)*(local+1) << 16) |
                        ((UCHAR)*(local+2) << 8) |
                         (UCHAR)*(local+3));
        local += 4;

        while (size--) *dest++ = *local++;
        }

#elif (GHS || __DIAB)
/*---------------------------------------------------------------------*/
/* Initialized data needs to be copied from ROM to RAM when the code is*/
/* placed in ROM. It need not be done when the code is downloaded to   */
/* RAM as the data is in the RAM already. DataStart and TextEnd are    */
/* used to differentiate the ROM download and the RAM download. If ROM */
/* download, TextEnd points to end of .text section, which is a ROM    */
/* address. If RAM download, TextEnd point to DataStart. The           */
/* initialization code then copies the initialized data to RAM if      */
/* TextEnd != DataStart. The two symbols TextEnd and DataStart are set */
/* in the linker files of the BSP.                                     */
/*---------------------------------------------------------------------*/

    if (TextEnd != DataStart)
        {
        local = TextEnd;
        dest  = DataStart;
        size  = (ULONG) DataEnd - (ULONG) DataStart;
 
        while (size--) *dest++ = *local++;
        }
#elif _SDS
    /* For SDS this is handled in begin.s */
#endif

/*---------------------------------------------------------------------*/
/*                                                                     */
/*---------------------------------------------------------------------*/
/* Initialize the system variables.  If SC_SD_PARAMETERS is STORAGE,   */
/* we will attempt to read the variables from the parameter storage    */
/* area.  The parameter storage area is formatted as follows:          */
/*                                                                     */
/*     |                           |                                   */
/*     |===========================|  (lowest addr in parameter        */
/*     | "Magic #" (4 bytes)       |   storage area)                   */
/*     |===========================|                                   */
/*     | SysVars checksum (4 bytes)|                                   */
/*     |---------------------------|                                   */
/*     | SysVars                   |                                   */
/*     |===========================|                                   */
/*     | BspVars checksum (4 bytes)|                                   */
/*     |---------------------------|                                   */
/*     | BspVars                   |                                   */
/*     |===========================|                                   */
/*     | AppVars checksum (4 bytes)|                                   */
/*     |---------------------------|                                   */
/*     | AppVars                   |                                   */
/*     |===========================|                                   */
/*     |                           |                                   */
/*                                                                     */
/* BspVars is only present if BSP_PARMS is non-zero (bsp.h)            */
/* AppVars is only present if SC_APP_PARMS is non-zero (sys_conf.h)    */
/*                                                                     */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* Check that the parameters will fit.  "60" is the size of SysVars.   */
/*---------------------------------------------------------------------*/
#if ((60 + BSP_PARMS + SC_APP_PARMS + 16) > 256)
    #error "Too many parameters to fit in parameter storage area"
#endif

StorageRead(sizeof(NVVars), 0, &NVVars);

magic = NVVars.magic;
csum = NVVars.SysVars_CheckSum;
if ((csum != CheckSum(&SysVars, sizeof(SysVars))) || (magic != MAGIC))
    {
    storage_update = TRUE;
    SysVars = SysVarsDefaults;
    }

#if (SC_SD_PARAMETERS == SYS_CONF)
    DebugModeSv = SysVars.DebugMode;
    SysVars = SysVarsDefaults;
    SysVars.DebugMode = DebugModeSv;
#endif

#if (SC_SD_DEBUG_MODE != STORAGE)
    SysVars.DebugMode = SC_SD_DEBUG_MODE;
#endif

if ((SysVars.DebugMode > 4) || (SysVars.DebugMode < 1))
    SysVars.DebugMode = 1;

StorageOffset = (ULONG)(sizeof(SysVars) + 8);

#if BSP_PARMS
    csum = NVVars.BspVars_CheckSum;
    if ((csum != CheckSum(BspVars, BSP_PARMS)) || (magic != MAGIC))
        {
        storage_update = TRUE;
        BspGetdefaults(BspVars);
        }

    #if (SC_SD_PARAMETERS == SYS_CONF)
        BspGetdefaults(BspVars);
    #endif
    StorageOffset += (BSP_PARMS + 4);
#endif

#if SC_APP_PARMS
    csum = NVVars.AppVars_CheckSum;
    if ((csum != CheckSum(AppVars, SC_APP_PARMS)) || (magic != MAGIC))
        {
        storage_update = TRUE;
        AppGetdefaults(AppVars);
        }

    #if (SC_SD_PARAMETERS == SYS_CONF)
        AppGetdefaults(AppVars);
    #endif

#endif

/*---------------------------------------------------------------------*/
/* Initialize the polled serial driver so we can use Print() to print  */
/* messages out.  The polled serial driver will also be needed for the */
/* configuration dialog if it is configured.                           */
/*---------------------------------------------------------------------*/
//#if !BSP_NEW_SERIAL
//    Delay100ms();
//    SerialSetup(SysVars.DefBaud, PROBE_CON_SER_PORT, SC_RBUG_PORT);
//    SerialPollInit();
//    SerialPollOn();
//    Delay100ms();
//#else
//    SysBaud = SysVars.DefBaud;
//    SysConsole = SC_APP_CONSOLE;
//#endif

/*---------------------------------------------------------------------*/
/* The memory starting at "FreeMemStart" is available for allocation.  */
/* Call any high-level drivers that are configured so they can grab    */
/* some of this memory if they need it.  This technique allows us to   */
/* build systems in which the drivers use different numbers of buffers */
/* without having to re-compile the drivers.                           */
/*---------------------------------------------------------------------*/
FreeMemPtr = FreeMemStart;
FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);

#if SC_RAM_SIZE
    LastByte = (UCHAR *)(SC_RAM_SIZE + BSP_RAM_BASE - 1);
#else
    LastByte = (UCHAR *)(RamSize() + (ULONG)BSP_RAM_BASE - 1UL);
#endif

#if BSP_NEW_SERIAL

    /*-----------------------------------------------------------------*/
    /* Set the variables ProbeCon and ProbeHst to pe used by dipi      */
    /* driver.                                                         */
    /*-----------------------------------------------------------------*/
    ProbeCon = PROBE_CON_SER_PORT;
    ProbeHst = SC_RBUG_PORT;

    /*-----------------------------------------------------------------*/
    /* Initialize the General Serial Messaage block manager            */
    /*-----------------------------------------------------------------*/
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = GSblkSetup(FreeMemPtr, (ULONG)LastByte, &error_flag);

    
    /*-----------------------------------------------------------------*/
    /* Initialize the lower serial driver.                             */
    /*-----------------------------------------------------------------*/
//    SerialInit();

    /*-----------------------------------------------------------------*/
    /* Set up the "non pSOS serial ports" variables.                   */
    /*-----------------------------------------------------------------*/
    NumNon_pSOSChan = SC_NumNon_pSOSChan;
    i = 0;
    #if PROBE_CON_SER_PORT != 0
        Non_pSOSChan[i++] = PROBE_CON_SER_PORT;
    #endif
    #if SC_RBUG_PORT != 0
        Non_pSOSChan[i++] = SC_RBUG_PORT;
    #endif
    if (NumNon_pSOSChan < i)
	NumNon_pSOSChan = i;
#endif
     
#if !BSP_NEW_SERIAL && BSP_PARALLEL
    FreeMemPtr = (UCHAR *)ALIGN((ULONG)FreeMemPtr, 4);
    FreeMemPtr = GSblkSetup(FreeMemPtr, (ULONG)LastByte, &error_flag);
#endif
 
//#   if BSP_NEW_SERIAL
//        ProbeIOInit();
//#   endif

#   if (BSP_NEW_SERIAL || BSP_PARALLEL)
    if (error_flag)
      {
       while(1)
          {
    Print("\n\t#############################################################\n");
    Print("\t#                                                           #\n");
    Print("\t# GSblkSetup needs more memory to configure all the MBLK's  #\n");
    Print("\t# configured in gsblk_bufcfg structure.                     #\n");
    Print("\t#                                                           #\n");
    Print("\t# You need to re-configure your GS Blocks according to      #\n");
    Print("\t# Your memory requirements.                                 #\n");
    Print("\t#                                                           #\n");
    Print("\t# Modify GS_BUFS_xx in \"sys_conf.h\" file or configure       #\n");
    Print("\t# more memory for the Board and re-run the application.     #\n");
    Print("\t#                                                           #\n");
    Print("\t#############################################################\n");
        for (rc=0; rc<50; rc++)
          Delay100ms();
          }
        }
#endif

/*---------------------------------------------------------------------*/
/* If interactive dialog is configured, do it now.                     */
/*---------------------------------------------------------------------*/
#if SC_STARTUP_DIALOG
    #if (SC_SD_PARAMETERS == SYS_CONF)
       #error "SC_SD_PARAMETERS must be STORAGE if SC_STARTUP_DIALOG is YES"
    #endif

    if ((Dialog() == YES) || (storage_update == TRUE))
        {
        Print("Updating parameter storage. "
              "This may take a while...");

        /*-------------------------------------------------------------*/
        /* Save changed system variables in parameter storage area     */
        /*-------------------------------------------------------------*/
        NVVars.magic = MAGIC;
        NVVars.SysVars_CheckSum = CheckSum(&SysVars, sizeof(SysVars));

        #if BSP_PARMS
            NVVars.BspVars_CheckSum = CheckSum(&BspVars, sizeof(BspVars));
        #endif

        #if SC_APP_PARMS
            NVVars.AppVars_CheckSum = CheckSum(&AppVars, sizeof(AppVars));
        #endif

        StorageWrite(sizeof(NVVars), 0, &NVVars);
        Print("Done\n");
        }
#endif

/*---------------------------------------------------------------------*/
/* The parameters are now set - so do the following:                   */
/*    * Call BSP to advise it of VME base address (if appropriate)     */
/*    * Advise BSP and application of "final" values of their          */
/*      parameters (if appropriate)                                    */
/*---------------------------------------------------------------------*/
#if BSP_VME
    SetVmeAddress(SysVars.VmeBaseAddr);
#endif

#if BSP_PARMS
    BspUse(BspVars);
#endif

#if SC_APP_PARMS
    AppUse(AppVars);
#endif

/*---------------------------------------------------------------------*/
/* Check that the parameters make sense, then build the component      */
/* configuration tables                                                */
/*---------------------------------------------------------------------*/
AdjustSysVars();

FreeMemPtr = BuildConfigTables(FreeMemPtr);

/*---------------------------------------------------------------------*/
/* Check FreeMemPtr to make sure it has not over run memory!           */
/* NOTE: If pSOS+ has been configured into the system, the FreeMemPtr  */
/*       is now part of pSOS+ region zero!  So it can't be used to     */
/*       allocate any more memory after this.                          */
/*---------------------------------------------------------------------*/
if (FreeMemPtr > LastByte)
    SysInitFail(MemErrMsg);

#if ((BSP_CPU == 68040) && BSP_FPU)
    /*-----------------------------------------------------------------*/
    /* Set floating point execption vectors.                           */
    /*-----------------------------------------------------------------*/
    SysSetVector(V_FLINE, psos4_fline, NO_WRAPPER);
    SysSetVector(V_BSUN, psos4_bsun, NO_WRAPPER);
    SysSetVector(V_INEX, psos4_inex, NO_WRAPPER);
    SysSetVector(V_DZ, psos4_dz, NO_WRAPPER);
    SysSetVector(V_UNFL, psos4_unfl, NO_WRAPPER);
    SysSetVector(V_OPERR, psos4_operr, NO_WRAPPER);
    SysSetVector(V_OVFL, psos4_ovfl, NO_WRAPPER);
    SysSetVector(V_SNAN, psos4_snan, NO_WRAPPER);
    SysSetVector(V_UNSUPP, psos4_unsupp, NO_WRAPPER);
#endif
 
#if ((BSP_CPU == 68060) && BSP_FPU)
    /*-----------------------------------------------------------------*/
    /* Set floating point execption vectors.                           */
    /*-----------------------------------------------------------------*/
    SysSetVector(V_FLINE, psos6_fline, NO_WRAPPER);
    SysSetVector(V_INEX, psos6_inex, NO_WRAPPER);
    SysSetVector(V_DZ, psos6_dz, NO_WRAPPER);
    SysSetVector(V_UNFL, psos6_unfl, NO_WRAPPER);
    SysSetVector(V_OPERR, psos6_operr, NO_WRAPPER);
    SysSetVector(V_OVFL, psos6_ovfl, NO_WRAPPER);
    SysSetVector(V_SNAN, psos6_snan, NO_WRAPPER);
    SysSetVector(V_UNSUPP, psos6_unsupp, NO_WRAPPER);
    SysSetVector(V_EFFADD, psos6_effadd, NO_WRAPPER);
#endif


//#if BSP_NEW_SERIAL
    /*-----------------------------------------------------------------*/
    /* Initialize the lower serial driver.                             */
    /*-----------------------------------------------------------------*/
//    SysBaud = SysVars.DefBaud;
//    SerialInit();
//    ProbeIOInit();
//#else
    /*-----------------------------------------------------------------*/
    /* Set up serial driver again (in case baud rate changed).         */
    /*-----------------------------------------------------------------*/
//    SerialSetup(SysVars.DefBaud, PROBE_CON_SER_PORT, SC_RBUG_PORT);
//    SerialPollInit();
//    SerialPollOn();
//    Delay100ms();
//#endif


/*---------------------------------------------------------------------*/
/* Start pROBE+ running, if it is present.  Otherwise, transfer        */
/* control directly to pSOS+.                                          */
/*---------------------------------------------------------------------*/
#if SC_PROBE
    #if SC_BOOT_ROM
        if(SysVars.DebugMode == DBG_XS)

            Print("pROBE+ is now ready to talk to the host debugger"
                  " over this serial channel...\n");
	    else if (SysVars.DebugMode == DBG_XN)
            Print("pROBE+ is now ready to talk to the host debugger"
                  " over the network...\n");
     #endif

#if (SC_PROBE == USEROM)
    pROBE_tmp = (ULONG(*)(void))((ULONG)(NodeCfg.probect->td_code) +
    ENTRY_START_OFFSET + (ENTRY_LENGTH * PROBE_INIT_OFFSET));
    rc = (*pROBE_tmp)();

#else

    rc = pROBE_Init();
#endif

    while(1)
        {
        Print("pROBE+ Initialization Failed, Error Code 0x%08X\n", rc);
        Delay5sec();
        }

#elif (SC_PSOS || SC_PSOSM)

#if !BSP_NEW_SERIAL
    SerialPollOff();
#else
    ProbeExit();
#endif

#if ((SC_PSOS == USEROM) || (SC_PSOSM == USEROM))
    pSOS_tmp = (ULONG(*)(void))((ULONG)(NodeCfg.psosct->kc_psoscode) +
    ENTRY_START_OFFSET);
    rc = (*pSOS_tmp)();

#else

    PSOS_INIT();
#endif

#else
#if !BSP_NEW_SERIAL
    SerialPollOff();
#else
    ProbeExit();
#endif
    AppCode();   /* Not using pSOS or pROBE */
#endif

}

static void Delay5sec(void)
{
    ULONG i;
 
    for (i=0; i<50; i++)
        Delay100ms();
}
 
#if __cplusplus
}
#endif
