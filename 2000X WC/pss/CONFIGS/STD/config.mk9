#* @(#) pSOSystem/68K V2.2.2: configs/config.diab.mk (normal) 2.47 97/09/12 16:19:22 *
#* $Header:   K:\APPS\PVCS Pro\PSS68k.222\Configs\std\config.mkv   1.2   Apr 05 1999 13:38:52   lmarkure  $ *
#***********************************************************************
#*                                                                     *
#*   MODULE:  config.mk                                                *
#*   DATE:    97/09/12                                                 *
#*   PURPOSE: Standard make options for all applications               *
#*            Allows builds based on PVCS archives                     *
#*                                                                     *
#*---------------------------------------------------------------------*
#*                                                                     *
#*        Copyright 1991 - 1997, Integrated Systems, Inc.              *
#*                      ALL RIGHTS RESERVED                            *
#*                                                                     *
#*   Permission is hereby granted to licensees of Integrated Systems,  *
#*   Inc. products to use or abstract this computer program for the    *
#*   sole purpose of implementing a product based on Integrated        *
#*   Systems, Inc. products.   No other rights to reproduce, use,      *
#*   or disseminate this computer program, whether in part or in       *
#*   whole, are granted.                                               *
#*                                                                     *
#*   Integrated Systems, Inc. makes no representation or warranties    *
#*   with respect to the performance of this computer program, and     *
#*   specifically disclaims any responsibility for any damages,        *
#*   special or consequential, connected with the use of this program. *
#*                                                                     *
#*-------------------------- REVISIONS --------------------------------*
#*                                                                     *
#* Rev # Date     Author Description                                   *
#* ===== ======== ====== ==============================================*
#* 1.1   04/06/99 LAM    based on config.mk ver 1.7. , has not been    *
#*                       updated for PVCS yet.                         *
#* 1.2   05/13/99 LAM    updated for diab                              *
#* 1.3   05/18/99 ?      ?                                             *
#* 1.4   05/19/99 JRJ    Changed being.s so copied to L:\332\app       *
#* 1.5   05/20/99 OFI    Changed L:\pss68k.222 to $(PSS_ROOT)          *
#* 1.6   07/19/99 JRJ    added -D$(DOTEST) to COPTS                    *
#* 1.7   06/22/00 AS     added $(PSS_APPOBJS46)                        *
#* 1.8   06/30/00 LAM    removed $(PSS_APPOBJS46)                      *
#***********************************************************************
#***********************************************************************
#*   NOTE: bsp.mk must be included before this file                    *
#*                                                                     *
#***********************************************************************
#
# Diab "Make" options
#
#
#------------------------------------------------------------------------
# Define the command-line options to the compiler.  The options we use
# have the following meanings:
#
# COPTS specifies the c compile options.  These are specified
# as command-line options:
#     -D  <name>             Specifies  a preprocessor #define
# The DOTEST macro specifies the define which is to be considered set to 1
#-----------------------------------------------------------------------
#*---------------------------------------------------------------------*

CC         = dcc
COPTS = -D$(DOTEST) -I$(PSS_APPINCS) -I$(PSS_ROOT)\include
COPTS_FILE2= -D__DIAB -Xsmall-const=0 -Xsmall-data=0 -Xforce-prototypes -Xansi
COPTS_FILE3= -Xstruct-min-align=1 -tMC$(CPU)F$(DFP):psos -c -g

#COPTS = -@c.opt

#------------------------------------------------------------------------
# Assembler command-line options:
#------------------------------------------------------------------------
AS=     das
AOPTS = -tMC$(CPU)F$(DFP):psos -Xmnem-emb
#AOPTS=  -@a.opt

#------------------------------------------------------------------------
# Librarian command name and options
#------------------------------------------------------------------------
LIB= dar
LIBOPTS= -qf
LIBOPTS_SORT= -sR

#------------------------------------------------------------------------
# Linker command name
#------------------------------------------------------------------------
LD=     dcc
LOPTS= -Ws -tMC$(CPU)F$(DFP):psos -Wl,-Xprefix-underscore-coff -a -m2

#========================================================================
# Link everything together
#========================================================================
CFG1_OBJS= sysinit.o prepccfg.o pollio.o
CFG2_OBJS= psoscfg.o gsblkcfg.o probecfg.o

#rom.elf: a.opt c.opt begin.o    \
rom.elf: c.opt L:\332\app\begin.o    \
    $(CFG1_OBJS) \
    $(CFG2_OBJS) \
    $(PSS_BSP)/libbsp.a \
    $(PSS_APPOBJS1) \
    $(PSS_APPOBJS2) \
    $(PSS_APPOBJS3) \
    $(PSS_APPOBJS4) \
    $(PSS_APPOBJS5) \
    $(PSS_APPOBJS6) \
    $(PSS_APPOBJS7) \
    $(PSS_APPOBJS8) \
    $(PSS_APPOBJS9) \
    $(PSS_APPOBJS10) \
    $(PSS_APPOBJS11) \
    $(PSS_APPOBJS12) \
    $(PSS_APPOBJS13) \
    $(PSS_APPOBJS14) \
    $(PSS_APPOBJS15) \
    $(PSS_APPOBJS16) \
    $(PSS_APPOBJS17) \
    $(PSS_APPOBJS18) \
    $(PSS_APPOBJS19) \
$(PSS_APPOBJS20) \
$(PSS_APPOBJS21) \
    $(PSS_APPOBJS22) \
    $(PSS_APPOBJS23) \
    $(PSS_APPOBJS24) \
    $(PSS_APPOBJS25) \
    $(PSS_APPOBJS26) \
    $(PSS_APPOBJS27) \
    $(PSS_APPOBJS28) \
    $(PSS_APPOBJS29) \
$(PSS_APPOBJS30) \
$(PSS_APPOBJS31) \
    $(PSS_APPOBJS32) \
    $(PSS_APPOBJS33) \
    $(PSS_APPOBJS34) \
    $(PSS_APPOBJS35) \
    $(PSS_APPOBJS36) \
    $(PSS_APPOBJS37) \
    $(PSS_APPOBJS38) \
    $(PSS_APPOBJS39) \
    $(PSS_APPOBJS40) \
    $(PSS_APPOBJS41) \
    $(PSS_APPOBJS42) \
    $(PSS_APPOBJS43) \
    $(PSS_APPOBJS44) \
    $(PSS_APPOBJS45) \
$(PSS_ROOT)/sys/libc/libprepc.a \
    $(PSS_ROOT)/sys/os/libsys.a \
    $(PSS_BSP)/rom.lnk
    @cat $(PSS_BSP)/rom.lnk >cmd.lnk
    @echo $(LOPTS) -o rom.elf -Wmcmd.lnk begin.o > l.opt
    @echo -I. $(CFG1_OBJS) >> l.opt
    @echo -I. $(CFG2_OBJS) >> l.opt
    @echo -I. $(PSS_APPOBJS1) >> l.opt
    @echo -I. $(PSS_APPOBJS2) >> l.opt
    @echo -I. $(PSS_APPOBJS3) >> l.opt
    @echo -I. $(PSS_APPOBJS4) >> l.opt
    @echo -I. $(PSS_APPOBJS5) >> l.opt
    @echo -I. $(PSS_APPOBJS6) >> l.opt
    @echo -I. $(PSS_APPOBJS7) >> l.opt
    @echo -I. $(PSS_APPOBJS8) >> l.opt
    @echo -I. $(PSS_APPOBJS9) >> l.opt
    @echo -I. $(PSS_APPOBJS10) >> l.opt
    @echo -I. $(PSS_APPOBJS11) >> l.opt
    @echo -I. $(PSS_APPOBJS12) >> l.opt
    @echo -I. $(PSS_APPOBJS13) >> l.opt
    @echo -I. $(PSS_APPOBJS14) >> l.opt
    @echo -I. $(PSS_APPOBJS15) >> l.opt
    @echo -I. $(PSS_APPOBJS16) >> l.opt
    @echo -I. $(PSS_APPOBJS17) >> l.opt
    @echo -I. $(PSS_APPOBJS18) >> l.opt
    @echo -I. $(PSS_APPOBJS19) >> l.opt
    @echo -I. $(PSS_APPOBJS20) >> l.opt
    @echo -I. $(PSS_APPOBJS21) >> l.opt
    @echo -I. $(PSS_APPOBJS22) >> l.opt
    @echo -I. $(PSS_APPOBJS23) >> l.opt
    @echo -I. $(PSS_APPOBJS24) >> l.opt
    @echo -I. $(PSS_APPOBJS25) >> l.opt
    @echo -I. $(PSS_APPOBJS26) >> l.opt
    @echo -I. $(PSS_APPOBJS27) >> l.opt
    @echo -I. $(PSS_APPOBJS28) >> l.opt
    @echo -I. $(PSS_APPOBJS29) >> l.opt
    @echo -I. $(PSS_APPOBJS30) >> l.opt
    @echo -I. $(PSS_APPOBJS31) >> l.opt
    @echo -I. $(PSS_APPOBJS32) >> l.opt
    @echo -I. $(PSS_APPOBJS33) >> l.opt
    @echo -I. $(PSS_APPOBJS34) >> l.opt
    @echo -I. $(PSS_APPOBJS35) >> l.opt
    @echo -I. $(PSS_APPOBJS36) >> l.opt
    @echo -I. $(PSS_APPOBJS37) >> l.opt
    @echo -I. $(PSS_APPOBJS38) >> l.opt
    @echo -I. $(PSS_APPOBJS39) >> l.opt
    @echo -I. $(PSS_APPOBJS40) >> l.opt
    @echo -I. $(PSS_APPOBJS41) >> l.opt
    @echo -I. $(PSS_APPOBJS42) >> l.opt
    @echo -I. $(PSS_APPOBJS43) >> l.opt
    @echo -I. $(PSS_APPOBJS44) >> l.opt
    @echo -I. $(PSS_APPOBJS45) >> l.opt
    @echo -L $(PSS_ROOT)/sys/libc >> l.opt
    @echo -L $(PSS_BSP) -lbsp >> l.opt
    @echo -lprepc >> l.opt
    @echo -L $(PSS_ROOT)/sys/os -lsys >> l.opt
    @echo -I. $(PSS_COMPLIB) >> l.opt
        $(LD) -@l.opt > rom.map
        ddump -tv rom.elf >> rom.map
    @rm -f cmd.lnk l.opt

rom.hex: rom.elf
    ddump -Rv -o rom.hex rom.elf

#------------------------------------------------------------------------
# Compile or assemble modules which are always used.
#------------------------------------------------------------------------
#$(PSS_CONFIG)/begin.s
L:\332\app\begin.o:  begin.s
        $(AS) $(AOPTS) $(PSS_CONFIG)\begin.s
        copy $(PSS_CONFIG)\begin.o  L:\332\app\begin.o
        del $(PSS_CONFIG)\begin.o

#gsblkcfg.o: gsblkcfg.c
#        (ExtraLine)$(CC) $(COPTS) $(COPTS_FILE2) $(COPTS_FILE3) $(PSS_CONFIG)/gsblkcfg.c

#sysinit.o:
#        (ExtraLine)$(CC) $(COPTS) $(COPTS_FILE2) $(COPTS_FILE3) $(PSS_CONFIG)/sysinit.c

##prepccfg.o:
##        (ExtraLine)$(CC) $(COPTS) $(COPTS_FILE2) $(COPTS_FILE3) $(PSS_CONFIG)/prepccfg.c

##probecfg.o:
##        (ExtraLine)$(CC) $(COPTS) $(COPTS_FILE2) $(COPTS_FILE3) $(PSS_CONFIG)/probecfg.c

##psoscfg.o:
##        (ExtraLine)$(CC) $(COPTS) $(COPTS_FILE2) $(COPTS_FILE3) $(PSS_CONFIG)/psoscfg.c

##pollio.o:
##        (ExtraLine)$(CC) $(COPTS) $(COPTS_FILE2) $(COPTS_FILE3) $(PSS_CONFIG)/pollio.c

#a.opt:
#        @echo $(AOPTS_FILE1) >  a.opt

c.opt:
    @echo $(COPTS_FILE2) >> c.opt
    @echo $(COPTS_FILE3) >> c.opt

#UPDATE#

gsblkcfg.o:     bsp.h sys_conf.h
pollio.o:   bsp.h
prepccfg.o: sys_conf.h
probecfg.o: sys_conf.h bsp.h
psoscfg.o:  sys_conf.h
sysinit.o:      sys_conf.h bsp.h xception.h apdialog.h version.h machine.h

#ENDUPDATE#


