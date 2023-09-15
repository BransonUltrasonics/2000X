/* $Header:   D:/SWLab/VMdb/2000Series/INC/PARAM.H_V   2.80   May 23 2007 16:56:18   nhahmed  $ */
#ifndef PARAM_H
#define PARAM_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*************************                         **************************/

/*
 ------------------------ MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      param.h


 ----------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            4/25/96       LAM         Initial Release
      1.00         5/2/96        PJ          Updated enum to more closely
                                             match presets.
      2.00         5/3/96        PJ          Added parameters to enum list.
      3.00         6/20/96       PJ          Divided and added parameters for
                                             CurrentPreset and CurrentSetup.
      3.01         7/02/96       PJ          Added UPPERLIMITFLAG & TRIGGERSWFLAG
                                             to CurrentSetup ID's.
      4.00         7/26/96       LAM         Added LOADCELLTABLE,SPRINGRATETABLE,
                                             PRESSURETABLE,FORCETABLE,& VELOCITYTABLE
      5.00         8/01/96       PJ          Added FREQOFFSETFLAG,CONTROLLIMITSFLAG
                                             ENERGYCOMPFLAG, MINENERGYCOMP,
                                             MAXENERGYCOMP, ABSCUTOFFDIST,
                                             all ACTCLEARPSW types. 
      5.10         8/07/96       PJ          Added ID's for Sequence menus.
      5.20         9/06/96       PJ          Added SAVEPRESETZERO Id.
      5.30         9/24/96       PJ          Added SAVECURRENTSETUP Id.
      5.40        11-14-96       BEKymer     Added TESTAMPLITUDE
      5.50        11/27/96       PhilJ       Added PREWELDSEEK, AUTOTRIGGER Id.
      5.60        01/29/97       PhilJ       Added CYCLEABORT Id.
      5.60        01/31/97       PhilJ       Added MISSINGPART Ids.
      6.00        03/03/97       LAM         Added actclear to preset
      7.00        03-17-97       BEKymer     Added REMOTETERMINAL to Setup
      7.10        04/11/97       PhilJ       Added XSCALEFACTOR and
                                             XTIMESCALEFACTOR.
      8.00        04/21/97       LAM         Added seconds             
      8.10        05/13/97       PhilJ       Added PAGELENGTH
      8.20        06/13/97       PhilJ       Added ACTIVEPRESET
      8.2.17      06/17/97       PhilJ       added missing Id's to CurrentSetup
      8.2.18      06/20/97       PhilJ       Added unique Id's for all
                                             CurrentSetup variables.
      8.2.19      07/03/97       PhilJ       Deleted unused CurrentSetup Ids
                                             Added STARTSCREEN
      8.2.20      07/09/97       PhilJ       Added HOSTCOMPUTER Id
      8.2.21      07/11/97       PhilJ       Added HMENUINDEX Id
      8.2.22      07/17/97       PhilJ       Added STROKELENGTH
      8.2.23      08/04/97       PhilJ       Added DIGITALFREQ & DIGITALTUNE
      2.24        02/23/98       LAM         moved FEATURES to preset
      2.25        04/30/98       BJB         Moved ACTLIFETIMECOUNTER to setup.
      2.26        07-21-98       BEKymer     Moved CYLINDIAMETER to preset.
      2.27        03-12-99       BEKymer     Added RAPIDTRAVERSEINITVEL,
                                             RAPDITRAVERSERAMP, RAMPTRS,
                                             RAMPFORCEATOFORCEB, RAMPHOLDTOVEL
                                             
      2.28        04-20-99       OFI         Changed for DIAB
      2.29        05-12-99       JZ          Added SETPRESSURE, WELDRATES, STEPRATES,
                                             HOLDRATES, RTRAMPRATE, RETURNRAMPRATE,
                                             SETRTCOMP
      2.30        06-04-99       JHenry      Add parameter types used by menuhorn.c
      2.31        08-11-99       JZ          added STARTRAMPRATE
      2.32        08-23-99       JZ          added parameters types for Part contact
      2.33        10-26-99       JZ          added SETIDLESPEED
      2.34        06-09-00       JLH         Added SENDWELDDATA and STROKELEN parameters to CurrentSetup.
      2.35        06-21-00       AS          Added Param types for DUPS and Horn Scan
      2.36        07-14-00       BEKymer     Add EXTRACOOLING to setup group of enums
                                             Moved SETFORCEPC from preset to setup group enum
                                             Moved SETVELOCITYPC from preset to setup group enum
                                             Added WELDSTATUS to preset group enum
      2.37        07-17-00       SRP         Spell mistake corrected at HORN_SCANMAXIMUMAMPLITUDE
      2.38        07-27-00       SRP         SETPSTYPE added . 
      2.39        04-06-01       DJL         Added extpresets and handheld under enum.
      2.39.2.0    10-01-03       JOY         Added 'FREQOFFSETSIGNFLAG'.
      2.39.3.0    11-13-03       LAM         moved 'FREQOFFSETSIGNFLAG'to the end of the list.
      2.40        09-24-01       BEKymer     Add BUCMENU in the enum list
      2.41        09-08-03       BEKymer     Add ENERGYBRAKINGFLAG
      2.42        12-08-03       BEKymer     Merged 2.41 & 2.39.2.1 to create 2.42
                                              for Ver9.00b build
      2.43        12-09-03       BEKymer     Added RAPIDTRAVERSEDIST, somehow missed
                                              during the merge.
      2.44        12-11-03       BEKymer     Add DEBUGGER to list of parameters
      2.45        01-19-04       VSharma     Added 'DUPSPRESETNUM'&'WELDCOUNT' in EDIT_PARAM_TYPE enum.
      2.47        01-21-04       BEKymer     Added SCRUBTIME to list and re-alphatized list
      2.48        02-18-04       VSharma     Added 'INPUTS', 'OUTPUTS', 'INPUTLOGIC', 'GNDDETLOGIC' & 'BEEPERRELEASE'.
                                             Added 'WRITEIN1' & 'WRITEIN2' to the list of parameters.
      2.50        04-06-04       VSharma     Arrange list in alphabatical order. 
      2.51        04-26-04       VSharma     Added ALARMMASKID to the list. 
      2.52        05-17-04       VSharma     Moved ALARMMASKID to end of the list.
      2.53        06-02-04       VSharma     Added EXTPRESETALARM & EXTPRESETSAMPLE to the list.                                      
      2.52.1.0    06-18-04       BEKymer     Added WELDERADDR
      2.54        06-25-04       BEKymer     Merged 2.52.1.0 & 2.53 to create
                                              2.54 for Ver9.00l build
      2.55        08-18-04       JOY         Added SV_TIMEOUT.
      2.56        08-27-04       BEKymer     Add ENERGYBRAKETIME to PARAM enum       
      2.57        07-25-05       Bwadia      Parameter list added for VGA
      2.58        08-23-05       Aare        Added enum for pretrigger delay.
      2.59        08-25-05       Aare        Added enum for metric distance flag.
      2.60        09-10-05       Aare        Merged 10f and 10h.
      2.61        09-10-05       Aare        Checked in so that 'get' wouldn't overwrite it.
      2.62        10-11-05       Bwadia      USB related VGA defines added
      2.63        10-24-05       Bwadia      Added PMC related param defines
      2.64        10-26-05       Bwadia      Added Sequencing related param defines
      2.65        11-22-05       Bwadia      Param Added for SBL variable menus
      2.66        12-07-05       Bwadia      View Graphs made VGABUTTON. Param defined
                                             for the same. Modified for tracker issue
                                             4034
      2.67        12-20-05       Bwadia      defines added for DUPS preset download from USB
                                             Modified for tracker issue 4013 
      2.68        01-03-06       Bwadia      Modified for tracker issue 3972. Param IDs added
                                             for VGABOTTOMHALF object
      2.69        01-05-06       LAM         Reorder Param IDs so production test will not be affected.
      2.70        01-09-06       Bwadia      VGA_PMC param ID added and VGA_PMCON and VGA_PMCOFF
                                             removed. Modified for tracker issue 4042
      2.71        01-12-06       Bwadia      VGA_WINDOWSSETUP param defined
      2.72        02-08-06       Bwadia      Param defined for USB global On/Off toggle
      2.73        03-20-06       Bwadia      Added Param ID for VGA reset scan value button  
                                             and VGA view Current Setup button
      2.74        12-22-06       NHAhmed     Added IDs for Sensor Cal Popup menu.
      2.75        03-12-07       NHAhmed     Added ID for Amplitude for scrub time (SCRUBAMPLITUDE).
      2.76        03-27-07       NHAhmed     Added IDs for VQS variables.
      2.77        03-29-07       YGupta      Modified PARAM enum to move SCRUBAMPLITUDE after WELDTIME, HOLDTIME AND PEAKPOWER.
      2.78        04-16-07       NHAhmed     Added IDs VGA_IPADDRESS and VGA_COPYSCANDATA.
      2.79        05-04-07       NHAhmed     Added ID VGA_VGAPREVBUTTON (Tracker #4115).
      2.80        05-23-07       NHAhmed     Added ID PRINT_WELDRESULT.
  --------------------------- DESCRIPTION -----------------------------------



 ------------------------- INCLUDE FILES ----------------------------------
*/  

/*
 --------------------------- DEFINES ---------------------------------------
*/

#define CURRENT_SETUP_OFFSET 1024
#define HORN_DOWN_OFFSET     2048
#define DUPS_PARAM_OFFSET    3072
#define VGA_PARAM_OFFSET     4096


/***************************************************************************/
/*                                                                         */
/*   NOTE!  THE ORDER OF THE PARAM ENUM'S BELOW AFFECTS THE HOST COMMAND   */
/*          "SET_CURRENT_PRESET_PARAMETERS" WHICH IS USED BY CHRIS IN      */
/*          MANUFACTURING TEST.  IF ANY CHANGES ARE MADE, HE MUST BE       */
/*          NOTIFIED.  IN PARTICULAR, WELDTIME, HOLDTIME AND PEAKPOWER.    */
/*                                                                         */
/*                                                BARRY  08-27-04          */
/***************************************************************************/


/* PARAM_ID's 0 thru 1023 define parameters types used in Presets */

typedef enum PARAM {              /* All parameters which can be changed   */
   ALLEMPTY = 0,                  /* Must be first entry in list           */
   ABSCUTOFFDIST,                 /* Added 07-30-96                        */
   ABSOLUTE,                      /* Added 04-25-96                        */
   ABSMLR,                        /* Added 05-03-96                        */
   ABSMLS,                        /* Added 05-03-96                        */
   ABSPLR,                        /* Added 05-03-96                        */
   ABSPLS,                        /* Added 05-03-96                        */
   ACTCLEARDIST,                  /* Added 07-31-96  Moved 01-21-04 BEK    */
   ACTCLEARPOSSW,                 /* Added 07-31-96  Moved 01-21-04 BEK    */
   ACTCLEARPSW1,                  /* Added 07-31-96  Moved 01-21-04 BEK    */
   ACTCLEARPSW2,                  /* Added 07-31-96  Moved 01-21-04 BEK    */
   ACTCLEARPSW3,                  /* Added 07-31-96  Moved 01-21-04 BEK    */
   AFTERBURST,                    /*                                       */
   AFTERBURSTAMP,                 /* Added 05-02-96                        */
   AFTERBURSTDELAY,               /* Added 05-02-96                        */
   AFTERBURSTFLAG,                /* Added 05-02-96                        */
   AFTERBURSTTIME,                /* Added 05-02-96                        */
   AMP1,                          /*                                       */
   AMP2,                          /*                                       */
   AMPLITUDEGRAPHALARM,           /*                                       */
   AMPLITUDEGRAPHSAMPLE,          /*                                       */
   AMPLITUDESTEP1,                /* Added 07-01-96                        */
   AMPLITUDESTEP2,                /* Added 07-01-96                        */
   AMPLITUDESTEPFLAG,             /* Added 04-22-96                        */
   AMPTRIGDISTVALUE,              /* Added 05-02-96                        */
   AMPTRIGENERVALUE,              /* Added 05-02-96                        */
   AMPTRIGEXTFLAG,                /* Added 05-02-96                        */
   AMPTRIGFLAG,                   /* Added 05-02-96                        */
   AMPTRIGFORCEVALUE,             /* Added 05-02-96                        */
   AMPTRIGPOWERVALUE,             /* Added 05-02-96                        */
   AMPTRIGTIMEVALUE,              /* Added 05-02-96                        */
   AUTOTRIGGER,                   /*                                       */
   BUCMENU,                       /* 8.3S                                  */
   COLLAPSE,                      /* added 4-25-96                         */
   COLLCUTOFFDIST,                /* Added 01-29-97                        */
   COLMLR,                        /* Added 05-03-96                        */
   COLMLS,                        /* Added 05-03-96                        */
   COLPLR,                        /* Added 05-03-96                        */
   COLPLS,                        /* Added 05-03-96                        */
   CONTROLLIMITSFLAG,             /* Added 06-18-96                        */
   CYCLEABORT,                    /* Added 01-29-97                        */
   CYLINDIAMETER,                 /* Moved from setup group on 07-21-98    */
   DAY,                           /* Added 06-18-96                        */
   DEBUGGER,                      /* Added 12-11-03                        */
   DIGITALFILTER,                 /*                                       */
   DISTANCEGRAPHALARM,            /*                                       */
   DISTANCEGRAPHSAMPLE,           /*                                       */
   DISTANCEGRAPHVALUE,            /* added 05-02-96                        */
   DOWNSPDSTART,                  /*                                       */
   DOWNSPDSTEP,                   /*                                       */
   DOWNSPDTYPE,                   /*                                       */
   DOWNSPEED,                     /*                                       */
   DOWNTRIGVALUE,                 /*                                       */
   DUPSPRESETNUM,                 /* Added 01-19-04                        */
   ENERGYBRAKETIME,               /* Added 08-27-04                        */
   ENERGYBRAKINGFLAG,             /*                                       */
   ENERGYCOMPFLAG,                /*                                       */
   ENERGYMLR,                     /* Added 05-03-96                        */
   ENERGYMLS,                     /* Added 05-03-96                        */
   ENERGYPLR,                     /* Added 05-03-96                        */
   ENERGYPLS,                     /* Added 05-03-96                        */
   FORCE2,                        /*                                       */
   FORCE2FLAG,                    /*                                       */
   FORCEGRAPHALARM,               /*                                       */
   FORCEGRAPHSAMPLE,              /*                                       */
   FORCEGRAPHVALUE,               /* Added 05-02-96                        */
   FORCESTEP,                     /*                                       */
   FORCESTEPFLAG,                 /* Added 04-22-96                        */
   FORCETABLE,                    /* Added 07-26-96                        */
   FORCETRIGAMPVALUE,             /* Added 05-02-96                        */
   FORCETRIGDISTVALUE,            /* Added 05-02-96                        */
   FORCETRIGEXTFLAG,              /* Added 05-02-96                        */
   FORCETRIGENERVALUE,            /* Added 05-02-96                        */
   FORCETRIGFLAG,                 /* Added 05-02-96                        */
   FORCETRIGPOWERVALUE,           /* Added 05-02-96                        */
   FORCETRIGTIMEVALUE,            /* Added 05-02-96                        */
   FORCETRIGVALUE,                /*                                       */
   FREQOFFSETFLAG,                /* Added 07-29-96                        */
   FREQOFFSETSIGNFLAG,            /* Added 10-01-03                        */
   FREQUENCYOFFSET,               /*                                       */
   FREQUENCYGRAPHALARM,           /*                                       */
   FREQUENCYGRAPHSAMPLE,          /*                                       */
   FREQUENCYGRAPHVALUE,           /* Added 05-02-96                        */
   GLOBALPRINTING,                /*                                       */
   GROUNDDETECT,                  /*                                       */
   HOLDFORCE,                     /*                                       */
   HOLDRATES,                     /* Added 05-10-99  JZ                    */
   HOLDTIME,                      /*                                       */
   HOUR,                          /* Added 06-18-96                        */
   LOADCELLTABLE,                 /* Added 07-26-96                        */
   LABGRAPHSALARM,                /*                                       */
   LABGRAPHSSAMPLE,               /*                                       */
   LABGRAPHVALUE,                 /* Added 05-02-96                        */
   MAXENERGYCOMP,                 /* Added 07-30-96                        */
   MAXFORCEMLR,                   /* Added 05-03-96                        */
   MAXFORCEMLS,                   /* Added 05-03-96                        */
   MAXFORCEPLR,                   /* Added 05-03-96                        */
   MAXFORCEPLS,                   /* Added 05-03-96                        */
   MINENERGYCOMP,                 /* Added 07-30-96                        */
   MINUTE,                        /* Added 06-18-96                        */
   MISSINGMAXFLAG,                /* Changed 01-29-97                      */
   MISSINGMINFLAG,                /* Changed 01-29-97                      */
   MISSINGPARTFLAG,               /* Changed 01-29-97                      */
   MISSINGPARTMAX,                /* Changed 01-29-97                      */
   MISSINGPARTMIN,                /* Changed 01-29-97                      */
   MONTH,                         /* Added 06-18-96                        */
   MONTHDATEYEAR,                 /*                                       */
   PEAKPOWER,                     /*                                       */
   PEAKPOWERCUTOFF,               /* Added 04-22-96                        */
   POSTWELDSEEK,                  /*                                       */
   POWERGRAPHALARM,               /*                                       */
   POWERGRAPHSAMPLE,              /*                                       */
   POWERGRAPHVALUE,               /* Added 05-02-96                        */
   POWERMLR,                      /* Added 05-03-96                        */
   POWERMLS,                      /* Added 05-03-96                        */
   POWERPLR,                      /* Added 05-03-96                        */
   POWERPLS,                      /* Added 05-03-96                        */
   PRETRIGAMP,                    /* Added 04-22-96 Changed name 05-02-96  */
   PRETRIGDIST,                   /* Changed from PRETRIGGER 05-02-96      */
   PRETRIGFLAG,                   /* Added 04-22-96 Changed name 05-22-96  */
   PRETRIGSWITCH,                 /*                                       */
   PREWELDSEEK,                   /*                                       */
   RAPIDTRAVERSEDIST,             /* Added 12-09-03                        */
   RAPIDTRAVERSEFLAG,             /* Added 04-22-96                        */
   RAPIDTRAVERSESWITCH,           /* Added 05-02-96                        */
   RAPIDTRAVERSESPEED,            /* Added 04-22-96                        */
   REJECTLIMITS,                  /*                                       */
   REJECTLIMITSFLAG,              /* Added 04-22-96                        */
   RESETREQUIRED,                 /*                                       */
   RESETWELDCOUNTER,              /* Added 06-20-96                        */
   RETURNRAMPRATE,                /* Added 05-12-99 JZ                     */
   RTRAMPRATE,                    /* Added 05-12-99 JZ                     */
   SAVEPRESETZERO,                /* Added 09-06-96                        */
   SCRUBTIME,                     /* Added 01-21-04                        */
   SECONDS,                       /* Added 04-21-97                        */
   SECURITYLEVEL,                 /*                                       */
   SETGAINFACTOR,                 /* added 08-23-99 JZ                     */
   SETIDLESPEED,                  /* added 10-26-99 JZ                     */
   SETMINTRIGGER,                 /* added 08-23-99 JZ                     */
   SETPRESSURE,                   /* Added 05-06-99 JZ                     */
   SETRTCOMP,                     /* BUC menu item                         */
   SETUPPRESETALARM,              /*                                       */
   SETUPPRESETSAMPLE,             /*                                       */
   SETUPPRESETVALUE,              /* Added 05-02-96                        */
   SPRINGRATETABLE,               /* Added 07-26-96                        */
   STARTRAMPRATE,                 /* ADDED 08-11-99                        */
   STEPRATES,                     /* Added 05-10-99  JZ                    */
   STROKELENGTH,                  /*                                       */
   SUSPECTLIMITS,                 /*                                       */
   SUSPECTLIMITSFLAG,             /* Added 04-22-96                        */
   TESTAMPLITUDE,                 /* Added 11-14-96   by BEK               */
   TIMEOFDAY,                     /*                                       */
   TRIGGERDELAY,                  /*                                       */
   TRIGGERDELAYFLAG,              /* Added 05-02-96                        */
   TRIGGERFORCE,                  /*                                       */
   TRSDISTMLR,                    /* Added 05-03-96                        */
   TRSDISTMLS,                    /* Added 05-03-96                        */
   TRSDISTPLR,                    /* Added 05-03-96                        */
   TRSDISTPLS,                    /* Added 05-03-96                        */
   VELOCITYGRAPHALARM,            /*                                       */
   VELOCITYGRAPHSAMPLE,           /*                                       */
   VELOCITYGRAPHVALUE,            /* Added 05-02-96                        */
   VELOCITYTABLE,                 /* Added 07-26-96                        */
   WELDCOUNT,                     /* Added 01-19-04                        */
   WELDENERGY,                    /* Added 04-25-95                        */
   WELDFORCE,                     /*                                       */
   WELDFORCE1,                    /* Added 07-01-96                        */
   WELDFORCE2,                    /* Added 07-01-96                        */
   WELDHISTORYALARM,              /*                                       */
   WELDHISTORYSAMPLE,             /*                                       */
   WELDHISTORYVALUE,              /* Added 05-02-96                        */
   WELDMODE,                      /*                                       */
   WELDMODEFLAGS,                 /* Added 04-22-96                        */
   WELDSTATUS,                    /*                                       */
   WELDSUMMARYALARM,              /*                                       */
   WELDSUMMARYSAMPLE,             /*                                       */
   WELDSUMMARYVALUE,              /* Added 05-02-96                        */
   WELDTIME,                      /*                                       */
   WELDRATES,                     /* Added 05-10-99  JZ                    */
   WRITEIN1,                      /* Added 02-18-04                        */
   WRITEIN2,                      /* Added 02-18-04                        */
   XSCALEFACTOR,                  /* Added 04-11-97                        */
   XTIMESCALEFACTOR,              /* Added 04-11-97                        */
   PRETRIGDELAY,                  /* Added 08-15-05,need to keep at end    */
   SBLFREQMLR,                    /* Added 11-10-2005                      */
   SBLFREQPLR,                    /* Added 11-10-2005                      */
   SEQPRESETALARM,
   SEQPRESETSAMPLE,
   SCRUBAMPLITUDE,                /* Added 02-13-07                        */
   VQSWELDTIMEP, 
   VQSWELDTIMEM,
   VQSENERGYM,
   VQSENERGYP,
   VQSPEAKPOWM,
   VQSPEAKPOWP,
   VQSTOTDISTM,
   VQSTOTDISTP,
   VQSWELDCOLP,
   VQSWELDCOLM,
   VQSTOTABSP,
   VQSTOTABSM,
   VQSFORCEP,
   VQSFORCEM,
   VQSCYCLETIMEP,
   VQSCYCLETIMEM, 
   XXCANTCHANGEXX,                /* For run screen if things cant change  */
   YEAR,                          /* Added 06-18-96                        */


/* PARAM_ID's from 1024 thru 2047 define parameter types used in CurrentSetup*/

   ACTIVEPRESET = CURRENT_SETUP_OFFSET,/*                                  */
   ACTLIFETIMECOUNTER,                 /*                                  */
   ACTMODELNUMBER,                     /*                                  */
   ACTSERIALNUMBER,                    /*                                  */
   ADJUSTWHILERUN,                     /*                                  */
   ADVANCEDCOUNTERS,                   /*                                  */
   ADVANCEDCYCLES,                     /*  Added 06-20-96                  */
   AMPCONTROL,                         /*                                  */
   AMPDECAYPERCENT,                    /* Really in BUC menu               */
   BAUDRATE,                           /*                                  */
   BEEPERALARM,                        /*                                  */
   BEEPERERROR,                        /*                                  */
   BEEPERRELEASE,                      /*  Added 02-18-04                  */
   BEEPERTRIGGER,                      /* added 05-02-96                   */
   CONTROLLEVEL,                       /*                                  */
   CUSTOMACTLOGIC,                     /*                                  */
   DIGITALFREQ,                        /*                                  */
   DIGITALTUNE,                        /*                                  */
   DISTSWITCHFLAG,                     /*                                  */
   ECHO,                               /*                                  */
   ENERGYBRAKINGPERCENT,               /* Really in BUC menu               */
   ENERGYBRAKINGTIME,                  /* Really in BUC menu               */
   EXTPRESETALARM,                     /*  Added 06-02-04                  */
   EXTPRESETSAMPLE,                    /*  Added 06-02-04                  */
   EXTPRESETS,                         /*added 04-06-01                    */
   EXTSWITCHLOGIC,                     /*                                  */
   EXTRACOOLING,                       /*                                  */
   FORMFEED,                           /*                                  */
   FREQCONTROL,                        /*                                  */
   GENERALALARMCOUNTER,                /*                                  */
   GNDDETLOGIC,                        /*  Added 02-18-04                  */
   HANDHELD,                           /*added 04-06-01                    */
   HMENUINDEX,                         /*                                  */
   HOSTCOMPUTER,                       /*                                  */
   INPUTLOGIC,                         /*  Added 02-18-04                  */
   INPUTS,                             /*  Added 02-18-04                  */
   LANGUAGE,                           /* Addwd 06-10-96                   */
   LINESPERPAGE,                       /*                                  */
   LOWERLIMITFLAG,                     /* Added 07-31-96                   */
   OUTPUTS,                            /*  Added 02-18-04                  */
   OVERLOADCOUNTER,                    /*                                  */
   PAGESIZE,                           /*                                  */
   PASSWORD,                           /*                                  */
   PRINTERTYPE,                        /*                                  */
   PRINT_WELDRESULT,                   /*                                  */
   PRESSURETABLE,                      /* Added 7-26-96                    */
   PSLIFETIMECOUNTER,                  /*                                  */
   PSSERIALNUMBER,                     /*                                  */
   PSMODELNUMBER,                      /*                                  */
   REMOTETERMINAL,                     /* Added 03-17-97 BEK               */
   SAVECURRENTSETUP,                   /*                                  */
   SCROLLDISPLAY,                      /*                                  */
   SENDWELDDATA,
   SERIALPORT,                         /*                                  */
   SETFORCEPC,                         /* added 08-23-99 JZ                     */
   SETVELOCITYPC,                      /* added 08-23-99 JZ                     */
   SEQUENCEFLAG,                       /* Added 08-01-96                   */
   SEQUENCE1FLAG,                      /* Added 08-01-96                   */
   SEQUENCE2FLAG,                      /* Added 08-01-96                   */
   SEQUENCE3FLAG,                      /* Added 08-01-96                   */
   SETUPSTUFF,                         /*                                  */
   SETPSTYPE,                          /* PSType in system configuration */
   STARTSCREEN,                        /*                                  */
   STROKELEN,
   SWHANDSHAKE,                        /*                                  */
   SWSERIALNUMBER,                     /*                                  */
   TESTTIMES,                          /* Added 08-01-96                   */
   TRIGGERSWITCHFLAG,                  /* Added 07-02-96                   */
   UNITS,                              /*                                  */
   UPPERLIMITFLAG,                     /* Added 07-02-96                   */
   WELDERADDR,                         /* Added 06-10-04                   */
   WELDTIMES,                          /* Added 08-01-96                   */
   SV_TIMEOUT,                         /* Added 08-18-04                   */
   DISTANCE3FLAG,                      /* Metric, 3 decimals               */
   SBLMINFREQ,                         /* SBL minimum frequency            */
   SBLMAXFREQ,                         /* SBL maximum frequency            */

/* PARAM_ID's from 2048 thru 3071 define parameters types used in Horn Down*/

   SETUP_HORNDOWNFORCE=HORN_DOWN_OFFSET,/*                                 */
   HD_TRIGGER_STATE,                   /*                                  */
   HD_RAPID_TRAVERSE,                  /*                                  */
   HD_SPEED,                           /*                                  */
   WORKING_HORNDOWNFORCE,              /*                                  */
   RT_TRANSITION,               
   PRESET_TRIGGER_FORCE,
   ALARMMASKID,                        /* Added 04-26-04                   */

/* PARAM_IDs from 3072 thru 4091 define DUPS and Horn Scan parameters      */
   DUPS_PARAMIDS    = DUPS_PARAM_OFFSET, /* Added 06-19-00                 */
   DUPS_PARAMSETNAME,
   DUPS_DIPFLAG,
   DUPS_SWDIPSETTING,
   DUPS_SEEKAMPLITUDE,
   DUPS_SEEKRAMPTIME,
   DUPS_SEEKTIME,
   DUPS_SEEKFLIMH,
   DUPS_SEEKFLIML,
   DUPS_SEEKPHLOOPI,
   DUPS_SEEKPHLOOPCF,
   DUPS_SEEKAMPLOOPC1,
   DUPS_SEEKAMPLOOPC2,
   DUPS_WELDAMPLITUDE,
   DUPS_WELDRAMPTIME,
   DUPS_WELDPHLOOPI,
   DUPS_WELDPHLOOPCF,
   DUPS_WELDAMPLOOPC1,
   DUPS_WELDAMPLOOPC2,
   DUPS_WELDFLIMH,
   DUPS_WELDFLIML,
   DUPS_WELDPHLIM,
   DUPS_WELDPHLIMTIME,

   /* Flags in SWDipSetting variable */
   DUPS_SWBIT0FLAG,
   DUPS_SWBIT1FLAG,
   DUPS_SWAMPSOURCEFLAG,
   DUPS_SWMEMFLAG,
   DUPS_SWMEMSTOREFLAG,
   DUPS_SWBIT5FLAG,
   DUPS_SWSEEKFLAG,
   DUPS_SWSEEKPWRFLAG,

  /*These parameters define Horn Scan parameters                           */
   HORN_SCANSTARTFREQ,
   HORN_SCANSTOPFREQ,
   HORN_SCANFREQSTEP,
   HORN_SCANTIMEDELAY,
   HORN_SCANMAXIMUMAMPLITUDE,
   HORN_SCANMAXIMUMCURRENT,

/* PARAM_IDs from 4096 thru 5120 define VGA parameters      */
   VGA_ACTSTARTCANCEL = VGA_PARAM_OFFSET,
   VGA_ACTSTARTOK,
   VGA_ALARMBUTTON,
   VGA_AMPLITUDEGRAPH, 
   VGA_AMPLITUDEPRINTNOW,
   VGA_AUTOREFRESH,
   VGA_BHHORNSCAN,
   VGA_BHHORNDOWN,
   VGA_BHTEST,
   VGA_BHDIAGNOSTICS,
   VGA_CALSNSRCANCEL,
   VGA_CALSNSROK,
   VGA_COLDISTGRAPH,
   VGA_COLDSTARTCANCEL,
   VGA_COLDSTARTOK,
   VGA_COLUMNSETUP,
   VGA_COMPAREHSCDATA,
   VGA_COMPAREHSCGRAPH,
   VGA_COMPAREHSCTABLE,
   VGA_COPYSCANDATA,
   VGA_DISTANCEPRINTNOW,
   VGA_FACTORYDEFAULTCANCEL,
   VGA_FACTORYDEFAULTOK,
   VGA_FORCEGRAPH,
   VGA_FORCEPRINTNOW,
   VGA_FREQPRINTNOW,
   VGA_FREQUENCYGRAPH,
   VGA_HISTORYPRINTNOW,
   VGA_HORNSCAN,
   VGA_HORNSCANABORT,
   VGA_HORNSCANGRAPH,
   VGA_HORNSCANPRINT,
   VGA_IPADDRESS,
   VGA_NOGRAPH,
   VGA_NOHSGRAPH,
   VGA_OVERWRITEPRESETCANCEL,
   VGA_OVERWRITEPRESETOK,
   VGA_POWERGRAPH,
   VGA_POWERPRINTNOW,
   VGA_PRESETCLEAR,
   VGA_PRESETCLEARCANCEL,
   VGA_PRESETCLEAROK,
   VGA_PRESETDOWN,
   VGA_PRESETINFO,
   VGA_PRESETNAME,
   VGA_PRESETRECALL,
   VGA_PRESETSAVE,
   VGA_PRESETSAVEASSIGN,
   VGA_PRESETSAVEAUTO,
   VGA_PRESETSAVECANCEL,
   VGA_PRESETSAVENEW,
   VGA_PRESETSAVEOK,
   VGA_PRESETSAVEOLD,
   VGA_PRESETUP,
   VGA_PRESETVERIFY,
   VGA_PRINTABORT,
   VGA_PRINTDUPSSETUP,
   VGA_PRINTGRAPH,
   VGA_PRINTHSCDATA,
   VGA_PMCADDAVGGRAPH,
   VGA_PMCCLEARAVGGRAPH,
   VGA_PMC,
   VGA_PMCENTERLIMITS,
   VGA_PMCGRAPH,
   VGA_PMCLOWERBAND,
   VGA_PMCTIMEOUT,
   VGA_PMCUPPERBAND,
   VGA_RADIOCOLUMNCANCEL,
   VGA_RADIOCOLUMNOK,
   VGA_REFRESHGRAPH,
   VGA_RESETSCANVALUES,
   VGA_RESETSENSORCANCEL,
   VGA_RESETSENSOROK,
   VGA_SAVESCANA,
   VGA_SAVESCANB,
   VGA_SAVESCANC,
   VGA_SEQPRINTNOW,
   VGA_SEQUENCECONTINUE,
   VGA_SEQUENCEDEFINE,
   VGA_SEQUENCEDELETE,
   VGA_SEQUENCEDOWNBUTTON,
   VGA_SEQUENCEENABLE,
   VGA_SEQUENCEERASE,
   VGA_SEQUENCEERASECANCEL,
   VGA_SEQUENCEERASEOK,
   VGA_SEQUENCEINSERT,
   VGA_SEQUENCELIST,
   VGA_SEQUENCEREPLACE,
   VGA_SEQUENCEUPBUTTON,
   VGA_SETUPPRINTNOW,
   VGA_SUMMARYPRINTNOW,
   VGA_SCREENSETUP,
   VGA_USBAMPLITUDEGRAPHSAMPLE,
   VGA_USBAMPLITUDEGRAPHALARM,
   VGA_USBDISTANCEGRAPHSAMPLE,
   VGA_USBDISTANCEGRAPHALARM,
   VGA_USBFORCEGRAPHSAMPLE,
   VGA_USBFORCEGRAPHALARM,
   VGA_USBFREQUENCYGRAPHSAMPLE,
   VGA_USBFREQUENCYGRAPHALARM,
   VGA_USBGLOBALFLAG,
   VGA_USBPOWERGRAPHSAMPLE,
   VGA_USBPOWERGRAPHALARM,
   VGA_USBVELOCITYGRAPHSAMPLE,
   VGA_USBVELOCITYGRAPHALARM,
   VGA_USBWELDDATASAMPLE,
   VGA_USBWELDDATAALARM,
   VGA_USBSETUP,
   VGA_VELOCITYGRAPH,
   VGA_VELOCITYPRINTNOW,
   VGA_VGAEXITBUTTON,
   VGA_VGANEXTBUTTON,
   VGA_VGAPREVBUTTON,
   VGA_VGASAVEBUTTON,
   VGA_VIEWGRAPHS,
   VGA_VIEWSETUPCHOICE,
   VGA_WELDRESETCOUNTCANCEL,
   VGA_WELDRESETCOUNTOK,
   VGA_WELDRETRACT,
   VGA_WELDHISTORY,
   VGA_WELDPSHISTORY,
   VGA_WELDSTATE,
   VGA_WINDOWSSETUP,
   VQSQUALITYSCREEN

   } EDIT_PARAM_TYPE;
  #endif
