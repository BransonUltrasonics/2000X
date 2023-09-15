/* $Header:   D:/databases/VMdb/2000Series/App/COMMAND.C_V   2.192.1.22.2.22   08 Mar 2011 02:57:42   PDwivedi  $ */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/* Copyright (c) Branson Ultrasonics Corporation, 1995, 2009                */
/* This program is the property of Branson Ultrasonics Corporation          */
/* Copying of this software is expressly forbidden, without the prior       */
/* written consent of Branson Ultrasonics Corporation.                      */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
 *  ---------------------------- MODULE DESCRIPTION -------------------------------
 * 
 * Module name:  IPS_Command_Handler
 * 
 * Filename:     command.c
 * 
 * 
 * Written by:  Mark Lazarewicz
 *  Date:  03/11/96
 *  Language:  Microtec "C"
 * 
 * -------------------------------- REVISIONS ------------------------------------
 * 
 *  Revision #  Date     Author   Description
 *  ==========  ======== ======   ===========
 *  0           03/11/96 Mark L   Initial Version
 *  1           08/04/96 Mark L   Support Weld Serial Commands
 *  2           03/30/97 LAM      welddata test
 *  3           04/04/97 LAM      added welddata host
 *  4           04/21/97 LAM      1line data version
 *  5           04/28/97 LAM      cleanup
 *  6           05/08/97 LAM      cleanup warnings
 *  7           05/20/97 PhilJ    added special Branson Host commands
 *  8           05/20/97 LAM      fixed spc message out
 *  2.16        06/16/97 PhilJ    Changed UpdateCurrentSetup to
 *                                UpdateCurrentPreset.
 *  2.17        06/17/97 LAM      deleted parameter manager
 *  2.18        07/03/97 PhilJ    Modified special Branson Host
 *                                commands.
 *  2.19        07/08/97 LAM      deleted alarmsdb.h
 *  2.21        08/15/97 PhilJ    deleted all memcpys in host command
 *  2.24        08/18/97 PhilJ    Corrected bug in DisableFlag logic
 *  2.25        08/19/97 PhilJ    Deleted more memcpy in PS Config.
 *  2.26        08/20/97 PhilJ    Added CHECKSUM_ERROR opcode
 *  2.27        08/27/97 KevinD   Moved buffer release to bottom of loop
 *  2.28        09/11/97 PaulG    Cleanup code
 *  2.29        09.30.97 JBerman  Setup ControlLevel: added the following
 *                                Setup weld history, DoColdStart, ColdStartPlus
 *  2.31        10/6/97  Kevin D  Sorce code Beautification
 *  2.32        10/06/97 KevinD   ???
 *  2.30 2.33   10/06/97 LAM      had to readd my fix, Derby eliminated this
 *                                version error checked strings        
 *  2.34        10.07.97 JBerman  Added some more Manufacture
 *                                defaults into ColdStartPlus
 *  2.35        10.16.97 JBerman  DoColdStart was merged into ColdStartPlus.
 *                                SetRemote was removed -> caused problems.
 *  2.36        11-05-97 PaulG    Modified  WeldHistoryPtr.
 *  2.37        11-18-97 LAM      replaced finalresults with weldingresults
 *  2.38        12-29-97 BJB      Deleted call to DumbTermRxHandler().
 *  2.39        12-31-97 BJB      Got rid of now unnecessary calls to
 *                                 SerialPut().
 *  2.40        01-19-98 BJB      Doesn't allow host command to turn off
 *                                 MaxTimeout, only to set value.
 *                                Doesn't use MaxTimeoutFlag.
 *  2.42        01-28-98 BJB      Saves CurrentPreset before cold start
 *  2.43        01-29-98 PhilJ    Implemented Reset_Required and
 *                                Reset_Alarms opcodes.                                          
 *  2.44        02.02.98 JBerman  Setup a default 9600 baud 
 *                                when seting up a level:
 *                                CurrentSetup.BaudRate=BAUD_9600
 *  2.45        03-10-98 PhilJ    chged NACK(LAM put back)       
 *  2.46        03.10.98 JBerman  ChangedCurrentPreset.StrokeLen
 *                                to CurrentSetup.StrokeLen 
 *  2.47        04.24.98 JBerman  Added StrokeLength, CylSize, ActId
 *                                for NovRam purposes.
 *  2.48        04.24.98 JBerman  Changed Strk with Stroke
 *  2.49        05.06.98 JBerman  Added: ResetActLifeTime,SetDefSerNum 
 *                                SetDefPressure, SetDefLoadCell
 *  2.50        05.11.98 LAM      deleted unused code, code was not aligned
 *  2.51        05.11.98 JBerman  Added ActCopyDeftoNon();
 *  2.52        05.11.98 LAM      removed extra switch                      
 *  2.53        05.13.98 JBerman  Fixed Acknowladge function
 *  2.54        05.14.98 JBerman  Worked on SET_ACT_MODELNUMBER
 *  2.55        05.18.98 JBerman  Remover ResetActLifeTime(); Future Rel.
 *  2.58        08.05.98 BJB      Includes kpresmsg.h, getmsg.h
 *  2.59        05.19.98 PhilJ    Added release 2.5 Host commands
 *  2.60        09.03.98 BJB      Uses new AlarmOff() to turn off reset LED.
 *  2.61        10.14.98 LAM      fixed upcode for weld data out             
 *  2.62        10.16.98 LAM      fixed cylinder & stroke commands           
 *  2.63        10.22.98 LAM      added acknack commands to config
 *                                commands
 *  2.64        10.28.98 LAM      do not hardcopy ae to 3in dia. and
 *                                4in stroke
 *  2.65        10.30.98 LAM      added 15khz and 30khz, fixed weldmode
 *  2.66        11.13.98 BJB      Added 15 & 30 KHz ranges to freq
 *                                 offset command.
 *  2.67        11.18.98 LAM      fixed freq offset                    
 *  2.68        12.07.98 LAM      fixed cycle aborts and control limits
 *  2.69        05.17.99 OFI      Add //SetDefForce() in SET_ACT_SERIALNUMBER
 *  2.70        05-19-99 JZ       Added SetRTRamp, RTRamp, ReturnRamp,
 *                                SetPressure
 *  2.71        05-27-99 JZ       activated SetDefForce
 *  2.72        06-16-99 JZ       changed BIT2 to RATE_NORMAL
 *  2.73        08-11-99 JZ       added StartRamp
 *  2.74        08-23-99 JZ       added VelocityPC, ForcePC, GainFactor
 *  2.75        08-23-99 LAM      renamed function initializespringrate to 
                                  builddefaultspringrate
    2.76        09-03-99 LAM      Added call to BuildVelocityTable to docoldstartplus                                   
 *  2.77        09-03-99 JZ       added CurrentSetup.MinTrigForce
    2.78        09-08-99 LAM      added cal stroke length and sys pressure to docoldstart
    2.79        09-20-99 LAM      added all actuator defaults to docoldstart
 *  2.80        09-24-99 OFI      Merged 2.75.5.1 to trunk
    2.82        09-27-99 LAM      removed warnings finished Version7 commands
    2.83        10-01-99 OFI      Adde code to test max and min force value for force fixed 
                                  and force step
    2.84        10-11-99 OFI      Adde code to test max and min Amp value for Amp fixed 
                                  and Amp step
    2.85        10-15-99 LAM      removed setting system pressure when setting factory
                                  defaults.
    2.86        10-18-99 OFI      Fixed all graphs printing procedures for proper capturing the data
    2.87        10-25-99 JZ       Modified RtcWrite()
    2.88        10-26-99 JZ       added IdleSpeed and changed VelocityPC=1 in ColdStartPlus()
    2.89        10-27-99 JZ       updated ColdStartPlus() with new values
    2.90        10-28-99 JZ       added some new defines
    2.91        11-04-99 OFI      Converted tabs into spaces
    2.92        11-04-99 OFI      Changed 0xff79 to 0x7d and put it to defines in menu.h
    2.93        11-06-99 OFI      Fixed alignment
    2.94        11-06-99 OFI      Final alignment fix
    2.95        12-07-99 JZ       added switch on CylinDiameter for default settings
    2.96        12-16-99 LAM      removed unused error handling code                
    2.96.3.1    05-05-00 JLH      Rewrote and cleaned up most host commands.
    2.97        12-17-99 JZ       added switch on CylinDiameter for default settings
                                  fixed act AE defaults in ColdStartPlus()
                                  mergerd to trunk
    2.98        04-05-00 JZ       Removed features.h from include files and removed call to BootSF().
                                  Replaced IBM proprinter with HPLaserJet in set printer command.
                                  merged Lang to trunk
    2.100       05-26-00 JLH      Changed LaserJet to HPPCL and made other printer-related changes.
    2.101       06-09-00 JLH      Merged with 8Host revision 2.96.3.1.  Added OKI520 printer type,
                                   HPPCL printer type.
    2.102       06-14-00 SCM      Removed unused variable 'LangIndex'.
    2.104       07-10-00 JLH      RCS updates.
    2.103       06-16-00 DJL      Added LangIndex to all updateline calls
    2.102.1.1   07-12-00 BEKymer  Changed SETUPS to SETUPS_Ver800
                                  Added Flag to CurrentPreset flag members
                                  Changed TrigDistValue to TrigColValue
                                  Changed MaxForce to WeldForce
                                  Remove Software serial #, ForcePC, VelocityPC
    2.105       07-10-00 JLH      Added LangIndex to some UpdateLine function calls.
    2.106       07-13-00 LAM      merged preset build with host build
    2.102.1.2   07-13-00 BEKymer  In ColdStartPlus():
                                    - swapped SetMaxMinValues and SetDefaultValues
                                    - save max number of presets to ensure Version is correct in all
                                    - set CurrentSetup.ExtraCooling based on frequency
    2.102.1.3   07-14-00 BEKymer  Included alarms.h
    2.102.1.4   07-18-00 BEKymer  Fixed CurrentPreset.StartRamp cold start value to RATE_SLOW.
    2.107       07-26-00 LAM      merged Barry's changes
    2.108       07-28-00 JLH      Restored READ_PRESET and RECALL_PRESET commands.
    2.109       08-08-00 BEKymer  Added code to initialize 3 DUPS arrays at configuration time
    2.110       08-09-00 BEKymer  Added initialization for PSType in ColdStartPlus()
                                  Also initialize VelocityPV and ForcePC in BUCMenuBBR and RAM
    2.111       08/11/00 RBHerrin Added DUPS initialization at ColdStartPlus
    2.112       08/17/00 LAM      Corrected defaults for min trigger & trigger force
                                  (#3276)
    2.113       08/18/00 SRP      DUPS_Info.WeldStatusFlag = TRUE set in coldstartplus.
    2.114       08-25-00 JLH      Changed SERIALLENGTH from 9 to 12.  This is PS Serial Number length.
    2.115       08/29/00 AT       removed extern DUPS2COP, COP2DUPS..., added sizeof()
    2.116       08/30/00 JLH      Added Depot level updates to SET_CONTROLLEVEL command processor.
    2.117       08/31/00 JLH      Fixed SET_CONTROLLEVEL command processor to set CurrentSetup.ControlLevel
                                   to LEVEL_t when a command to set Depot level is received.          
    2.118       09/06/00 JLH      Restored ColdStartPlus function call.  Removed ASCII 0 padding for
                                   power supply serial number.  Returned LEVEL_DEPOT to host if in
                                   depot mode. 
    2.119       09/06/00 LAM      updated aed/aef defaults in ColdStartPlus function.
    2.120       09/12/00 JLH      Host commands code review updates.
    2.121       09/12/00 JLH      Removed Authorization code check from SET_PS_SERIALNUMBER.  Previous
                                   check was against previous serial number, and Jim Stow would not
                                   change Authorization code based on new serial number.
    2.122       09/13/00 JLH      Forgot to save change comment in history.
    2.123       09/13/00 JLH      Changed SW version number reporting to use contents of StrM6_8A.                                           
    2.124       09/21/00 JLH      Changed logic to extract authorization code from host messages.
    2.125       09/29/00 JLH      Fixed SET_ACT_MODELNUMBER so it can change to type e actuator.
    2.126       10/04/00 AT       Changed DUPS_DownloadCurrPS to DUPS_QueuedDownloadPS
    2.127       10/12/00 JLH      Omitted declaration of hard-coded software version number.
    2.128       10/16/00 AT       2195 - force weld ramp time to 80 at cold start (#3622)
    2.129       10-18-00 BEKymer  Added 2nd arg to SaveCompressedPreset call
                                   Fix for issue # 3387
    2.130       10/20/00 AT       ColdStartPlus - override DUPSMemFlag at cold start (#3622)
    2.131       10/16/00 AT       ColdStartPlus - set Mem store and Seek flags in SWDipSetting
    2.132       10/17/00 AT       ColdStartPlus - remove seek flag only once
    2.133       10/20/00 AT       ColdStartPlus - forgot to keep ~ in previous fix
    2.133.1.0   04/19/01 LAM      Converted PresetEnableFlag to an array.
                                  added cooling on when 4000 watt, defaulted External Presets &
                                  Handheld to OFF
    2.133.1.1   04/30/01 LAM      Changed 4400 Watts to 4000 Watts     
    2.133.1.2   08-03-01 BEKymer  Changed START_WELD_DATA for new format to provide ASCII output
                                   Fix bug which sent out ACK message along with Compuweld data
    2.133.1.3   09/25/01 LAM      Added SerialPort=Compuweld to ColdStartPlus     
    2.135       10/08/01 LAM      merged special changes with preset cleanup. 

                                  Also save CurrentSetup at end of ColdStartPlus 
    2.133.1.5   04-04-02 LAM      Added SetPSVersionNVR and UpdateNVRSpringRate to ColdStartPlus
    2.133.1.6   04-24-02 LAM      Moved initializing GAINFACTOR above updating the springrate default
    2.133.1.7   04-25-02 BEKymer  Default extra cooling on when wattage is greater than 3300
    2.133.1.8   10-02-02 BEKymer  Add case (special host command) for OnboardDiagnostics
    2.136       04-11-03 BEKymer  Move 2.133.1.8 to tip as 2.136 for 8.10 build
    2.137       04-15-03 BEKymer  Set OnboardDiag to FALSE for standard software so diagnostics
                                   are not enabled by default
                                  Default velocity reporting to off
    2.137.1.0   08-05-03 BEKymer  Merged 2.137 and 2.135 to create 2.137.1.0 for 9.00A build
                                  - Clean up code for preset recall
    2.139       08-18-03 JOY      Added cold start Process/Complete message display
                                  on QVGA in 'ColdStartPlus()'.
    2.140       09-01-03 JOY      Added Weld Param OPtion Deaults in 'CurrentSetup' struct.
    2.141       12-02-03 BEKymer  Merged 2.140 & 1.137.1.0 to create 2.141 for
                                   Ver9.00b build
    2.142       12-27-03  VSharma Added code for Ver9.00 commands(Download,Upload Preset,Reset-
                                   Alarms & Verify Preset) & inserted DisplayLock in Ack/Nak response.
    2.143       01-13-04  VSharma Changed the minimum FreqOffset check in
                                   CheckMinMaxLimit().
    2.145       01-19-04  VSharma Changed Verify Preset implementation.
    2.146       02-02-04  VSharma Added code to copy data from Preset0 if any Min/Max 
                                  error in Host preset.
    2.147       02-10-04  VSharma Count value is corrected in UPLOAD_REMOTE_CONFIG_PARMS.
    2.148       02-12-04  BEKymer Modified ColdSTartPlus()
    2.149       03-03-04  VSharma Modified 'DisplayLockFlag' as a member of struct INBITS.
    2.150       03-12-04  VSharma Typecast BOOLEAN variable 'Inp.DisplayLockFlag' as UINT8.
    2.151                         No change via India
    2.152       04-05-04  BEKymer Add host command for graphs
    2.153       06-10-04  BEKymer Merged 2.151.1.1
                                  Added Welder ID to Compuweld data packet
    2.154       06-25-04  BEKymer Add call to QVGAStoreScrnImage() in ColdStartPlus()
    2.155       07-12-04  LAM     Initialize Actuator A/D clock in ColdStartPlus()
    2.156       07-13-04  BEKymer Initialize to new system controller board in ColdStartPlus()
                                   Change 2500W to 200W for Ahmet special    
    2.157       07-14-04  LAM     moved A/D clock defines to root.h
    2.158       08-03-04  JOY     Corrected Touch screen display in ColdStartPlus().
    2.159       08-23-04  LAM     Configure Actuator AD clock to slow speed when not initialized.
    2.160       08-31-04  BEKymer Call function UpdateCylDefaults() in
                                   SetBucMenuToFactoryDefaults() to init ForcePC
                                  Add code for Velocity Graph host command
    2.161       01-27-05  BEKymer Fix bug in welder ID in Compuweld data
                                  Use MsPointer->count instead of ->TotalPoints
                                   when determining graph size
                                  Send a NAK when illegal graph is requested 
                                  Change all graphs to use SetupVals function
                                   same as printing
    2.162       02-23-05  BEKymer Call SetupVals() before CreateGraphHeader(),
                                   WeldDataCount wasn't setup yet.
                                  Correct problem with X step increment in
                                   CreateGraphHeader()
                                  Changes implemented in 9.03                                  
    2.163       05-04-05  Bwadia  Checked in file for VFD menus implementation for Ver 10                              
    2.164       05-12-05  Aare    Made host command handler functions global for RVTS task.                    
    2.165       05-23-05  Bwadia  Moved VGA menu related functions to qvgamenu.c
                                  Made two separate functions for VGA host command
                                  and general host commands. Restored changes for 
                                  2.162 revision                                       
    2.166       07-25-05  Bwadia  Added VGA commands for Ver10.0e
    2.167       07-28-05  Bwadia  Reset Alarm command modified. tm_wkafter addded
                                  instead of While Loop.
    2.168       08-12-05  Bwadia  Added support for Export Weld data option through SBC
                                  Added command 1024 for the same  
    2.169       08-19-05  Bwadia  Reset alarm processing wait time changed to 1 sec.
    2.170       09-10-05  Bwadia  VGA host commands added for Print related feature 
                                  in Ver10.0h
    2.171       09-11-05  Aare    Call InitSBL from ColdStartPlus.
    2.172       10-11-05  Bwadia  Implemented upload and download preset command for a 
                                  particular preset number
    2.173       10-24-05  Bwadia  Command added for PMC feature
    2.174       10-28-05  Bwadia  Command added for VGA sequencing feature 
    2.175       11-02-05  Aare    Corrected pretrigger variable names, added pretrigger
                                   delay variable to limits checking array
    2.176       11-22-05  Bwadia  Beep command implemented for error beep 
    2.177       12-07-05  Bwadia  Printer alarm sent from SBC. Modified for tracker issue 
                                  3987
    2.178       12-20-05  Bwadia  USB alarm sent from SBC handled. Also Sequence printing                                                               
                                  command added. Modified for tracker issue 4029, 3976
    2.179       01-12-06  Bwadia  Command added for USB and P/S view preset. Modified for 
                                  tracker issue 4017, 4018, 4049 
    2.180       02-07-06  Bwadia  Command added for entry to screen setup. Modified for
                                  tracker issue 4083
    2.181       02-22-06  Bwadia  DUPS memory reset flag cleared in cold start Plus.
                                  Modified for tracker issue 4077  
    2.182       04-13-06  Bwadia  CurrentSetup.USEncoder set to FALSE in cold start plus                                         
    2.183       04-24-06  Bwadia  Horn scan abort command added
    2.184       05-18-06  YGupta  Added VerifyLengthAndCode Function.
    2.185       12-26-06  NHAhmed Updated ProcessVGAHostCommand(), so that to get SBC S/W 
                                  Version with SEND_MENU_PTRS Command.
    2.186       01-03-07  NHAhmed Changes made for Password and Display Lock.
   
    2.187       03-12-07  NHAhmed Changes made in WELD_GRAPH_COMMAND for Cycling/viewing issue.
    2.188       03-27-07  NHAhmed Added VGASystemPresetReport5 to Print the VQSData limits,
                                  Added command SEND_QUALITYLIMITS_DATA.
    2.189       03-29-07  YGupta  Rename define WELD_HOSTORY_COUNT as WELD_HISTORY_COUNT and 
                                  removed tabs and lined up the case.
    2.190       04-19-07  NHAhmed Modified ConvertWeldData() for VQS.
    2.191       05-04-07  NHAhmed Modified ConvertWeldData() for Toatal Cycle Time (Tracker #4111).
    2.192       05-23-07  NHAhmed Modified Code so as to disable welding after Windows Setup 
                                  is pressed, and to pop up a "Welding On..." message if weldin
                                  is on while Windows Setup is pressed.
    2.192.1.0   10-22-07  NHAhmed Changes done for LangTest phase 0.
    2.192.1.1   12-03-07  BEKymer Initialize BUCMenuBBR->RecalCode300 to TRUE
    2.192.1.2   01-11-08  NHAhmed Implemented new commands 1051 and 1052.
                                  Updated Map Table for menus.
    2.192.1.3   04-14-08  NHAhmed Implemented new commands 1038,1053,1054 and 1055. Also added new 
                                  functions SendBargraphData(), ScanInfoStatus(), ProcessWindowSetup() 
                                  and SendBottomHalfData().Updated Map Table for Menus.
    2.192.1.4   06-06-08  NHAhmed Implemented new commands PROCESS_ALARM_ITEM, SEND_ALARMBIT_COMMAND, 
                                  PMC_COMMAND and modified WELD_DATA_COMMAND for graph implementaion.
                                  Updated Map Table for menus.
    2.192.1.5   08-01-08  NHAhmed Implemented new commands SEND_SETUPPRINT_DATA, USBPRESET_COMMAND.
                                  Updated Map Table for menus.
    2.192.1.6   08-08-08  NHAhmed Updated Map Table for menus.
    2.192.1.7   08-26-08  NHAhmed Added a function CheckforDisplayLock() and modified function SendBottomHalfData().
    2.192.1.8   08-26-08  NHAhmed Updated Map Table.
    2.192.1.9   09-02-08  NHAhmed CleanUp for multi-language support.
    2.192.1.10  09-04-08  YGupta  CleanUp for LangTest Project.
    2.192.1.11  09-09-08  NHAhmed CleanUp for multi-language support.
    2.192.1.12  09-09-08  NHAhmed Changed the SWVersionLabel string to H11.00 for LangTestH.
    2.192.1.13  09-12-08  NHAhmed Changes made in XMLDataProcess()and implemented new command START_RUNCYCLE.
    2.192.1.14  09-18-08  NHAhmed Updated function SendBottomHalfData().
    2.192.1.15  09-24-08  NHAhmed Updated function SendConditionVariable().
    2.192.1.16  10-01-08  NHAhmed Merged Ver10.40 Changes.
    2.192.1.17  10-06-08  NHAhmed Modified command START_RUNCYCLE.
    2.192.1.18  10-08-08  NHAhmed Updated function SendBottomHalfData().
    2.192.1.19  10-20-08  NHAhmed Replaced stroke length LENGTH_7 by LENGTH_2.
    2.192.1.20  11-07-08  NHAhmed Introduced SystemParameterChgdFlag for control level or actuator change check.
    2.192.1.21  11-18-08  NHAhmed Added changes for Test Menu Problem.
    2.192.1.22  12-16-08  BEKymer Change to version 11.00 for final release
2.192.1.22.2.0  09-22-09  YGupta  Added Support for MICRO and changes for AutoRefresh BUG.
2.192.1.22.2.1  10-02-09  BEKymer Change version to 11.10B for testing
2.192.1.22.2.2  10-05-09  BEKymer Change version to 11.10D for testing
2.192.1.22.2.3  10-05-09  BEKymer Change version to 11.10E for testing
2.192.1.22.2.4  10-05-09  BEKymer Change version to 11.10F for testing
2.192.1.22.2.5  10-05-09  BEKymer Change version to 11.10G for MH testing
2.192.1.22.2.6  11-02-09  YGupta  Modified SendQualityLimitsData to send AED in case of MICRO.
2.192.1.22.2.7  11-06-09  Pdwivedi Modified Changes for VQS Limit Update.
2.192.1.22.2.8  11-11-09  Pdwivedi Change version to 11.10I.
2.192.1.22.2.9  12-11-09  YGupta   Modfied SendQualityLimitsData function to look at CompressPreset.
2.192.1.22.2.10 11-20-09  BEKymer  Change version to 11.10J
2.192.1.22.2.11 12-07-09  BEKymer  Change version to 11.10 for final release
2.192.1.22.2.12 12-14-09  BEKymer  Change version to 11.11A for release to fix FT issue
2.192.1.22.2.13 12-18-09  BEKymer  Change version to 11.11 for hopefully the final release
2.192.1.22.2.14 06-08-10  PDwivedi Replace Stroke len 160mm with 50mm for Standard MICRO.
2.192.1.22.2.15 06-18-10  PDwivedi Change version to 11.20B for Standard MICRO.
2.192.1.22.2.16 07-28-10  PDwivedi Change version to 11.20C for Standard MICRO(Spring rate problem).    
2.192.1.22.2.17 07-28-10  BEKymer  Change version to 11.20D for Standard MICRO(Spring rate problem).    
2.192.1.22.2.18 07-28-10  BEKymer  Change version to 11.20E for Standard MICRO(Spring rate problem).    
2.192.1.22.2.19 09-01-10  BEKymer  Change version to 11.20G for Standard MICRO(Spring rate problem).    
2.192.1.22.2.20 11-8-10   BEKymer  Moved version string to Version.c.    
2.192.1.22.2.21 02/28/11  PDwivedi Added changes for USB Memory Full Alarm.
2.192.1.22.2.22 03/08/11  PDwivedi Added changes for USB Memory Full Alarm in polling command.
 * ------------------------------- DESCRIPTION -----------------------------------
 * This module handles host commands. See the IRS for more information.
 * ------------------------------- PSEUDO CODE -----------------------------------
 * 
 * ------------------------------ INCLUDE FILES ----------------------------------
 */

#include <psos.h>           /* general hardware defines, etc..   */
#include "string.h"
#include "names.h"          /* task objects                      */
#include "opcodes.h"
#include "serial.h"
#include "run_task.h"       /* Need the DIAG_Q_CNT for error log test */
#include "ck_qsend.h"

#include "command.h"        /* function prototype     */
#include "sysmangr.h"       /* function prototypes    */
#include "psnvram.h"        /* function prototypes    */
#include "menu6.h"          /* function prototypes    */
#include "root.h"          /* function prototypes    */

/* inbound messages */
#include "genrlmsg.h"
#include "resetmsg.h"
#include "ipscdmsg.h"
#include "selctkey.h"

/* outbound messages */
#include "nvm_msg.h"

/* called interfaces */
#include "battram.h"        /* battram_test() prototype  */
#include "ckptgbuf.h"
#include "ticks.h"
#include "kpresmsg.h"

/* typedef include */
#include "memap.h"
#include "fpdatmsg.h"
#include "weld_obj.h"
#include "preset.h"
#include "menu3.h"
#include "limits.h"
#include "menu7a.h"
#include "param.h"

#include "menu7.h"
#include "led.h"
#include "alsetup.h"
#include "ready.h"
#include "menu1.h"
#include "actnvram.h"
#include "snsrcalb.h"
#include "menu.h"
#include "menu4.h"
#include "menu2.h"
#include "rtclock.h"
#include "ipsatype.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "graphs.h"
#include "util.h"
#include "alarms.h"
#include "dups.h"
#include "dups_api.h"
#include "time.h"
#include "DrawScrn.h"
#include "statedrv.h"
#include "weldmngr.h"
#include "keypad.h"
#include "qvga_task.h"
#include "qvgamenu.h"
#include "digout.h"
#include "beep.h"
#include "portable.h"
#include "rdyweld1.h"
#include "mansensr.h"
#include "preset.h"


#define  WELD_HISTORY         1
#define  WELD_HISTORY_COUNT   25
#define  USCS                 0
#define  METRIC2              1
#define  METRIC3              2
#define  MAX_STRUCT           530

WELD_DATA7_02  SPCData;
UINT8          *SPCDataPtr;
UINT8           RcvChecksum;
UINT32          ErrorResponseMinLimit, ErrorResponseMaxLimit;
UINT32          ErrorID;
UINT32          NackError;
UINT16          HostPresetEmpty = TRUE; /*TRUE: if preset data is send from host terminal*/
BOOLEAN         ResetFailed = FALSE;    /*TRUE: in case of any Non-Resetable alarm.*/
BOOLEAN         ResetAlarmProcessed = FALSE; /* TRUE: After process the ResetKey in weldmngr*/
PRESET_COMPRESSED  HostPreset;/*Store the data sent from the Host terminal.*/
BOOLEAN         VGA_ScreenCalibFlag = FALSE;
BOOLEAN         WindowSetupFlag = FALSE;
BOOLEAN         VGA_ReadyFlag;
BOOLEAN         VGAPrinterOfflineFlag = FALSE;
BOOLEAN         VGAUSBOfflineFlag = FALSE;
BOOLEAN         VGAUSBFullFlag = FALSE;
UINT16          ViewDupsPresent = FALSE;
PRESET_COMPRESSED* CompressPreset;
BOOLEAN         CurrentPresetParameterChanged = FALSE;


/* ------------------------ EXTERNAL DATA --------------------------------- */

extern UINT32   SysmQueueId;
extern UINT32   WmgrQid;
extern UINT32 RadioPointer;
extern SETUPS_Ver800 CurrentPreset;
extern SETUPS_Ver800 RunningPreset;
extern SETUPS_Ver800 MinLimit;
extern SETUPS_Ver800 MaxLimit;
extern SETUPS_Ver800 CurrentViewPreset;
extern CONFIGSETUP CurrentSetup;
extern BUCMENU_800 BUCMenuRAM, *BUCMenuBBR;
extern INBITS Inp;
extern PSNOVRAMDATA PSNvRamData;
extern enum WELDSTATES WeldState;

/* Now defined in Version.c */
extern SINT8 SWVersionLabel[SW_VERSION_LENTGH+1];


extern BOOLEAN IsThereDataPrinting;
extern BOOLEAN IsGraphDrawing;
extern BOOLEAN ReadyFlag;
extern UINT8 ColdStartFlag;
extern UINT16 PresetHasBeenOKed;
extern UINT8 AlarmDetectedFlag;
extern UINT8 MainKeyFlag;
extern WELD_DATA WeldingResults;
extern WELD_DATA FinalResults;
extern UINT16 PresetEnableFlags[MAX_PRESETS+1];    /* TRUE: Preset is valid   FALSE: Preset is not valid */

extern UINT32   PresetAddress[];
extern SINT32   MinWeldsPerPage;
extern SINT32   MaxWeldsPerPage;
extern UINT16   LangIndex;
extern UINT16   RadioIndex;
extern DEPOT_FLAGS *DepotFlag;

extern BOOLEAN  QVGAHwAvail;

extern BOOLEAN UpdateFlag;
extern BOOLEAN VGAPrinterStatus;
extern UINT16  PresetNeedsToBeUpdated;
extern UINT16 PsosReadyFlag;
extern UINT32 KeyMask;
extern UINT16 RapidTraverseState;
extern UINT16 DisplayRefreshButton;
extern UINT16 VGAPresetNum;
extern UINT8  LimitChanged;


extern UINT8 VGAAckBuf[];
extern DUPS_CURRENTPARAMSET DUPS_HostParamSet; 
extern STR DUPS_HostParamSetName[DUPS_PARAMSETNAMELEN + 1]; 
extern SINT8 SBCVersionLabel[SBC_SW_VERSION_LENTGH+1];
/* Stuff for graph host command */

extern UINT16 WeldDataCount;
extern WELD_OBJECT *MsPointer;
extern WELD_DATA   *PrintFinalPtr;
extern SINT32      val2[MAX_WELD_SAMPLES];

extern SETUPS_Ver800 CurrentPreset;
extern SINT32 MaxNoOfCycles;
extern SINT32 MinNoOfCycles;

static UINT32       PsosReturnValue;

 /*
  *  ------------------------------- PROTOTYPES ------------------------------------
  */
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
UINT8 VerifyLengthAndCode(SINT16 length, UINT16 code);
void CalMaxWeldsPerPage(void);
void SaveActSerialNum(void);
UINT16 XmitNack (IPS_ACTION_ID_TYPE Function, EDIT_PARAM_TYPE Subfunction, UINT32 Error,
                 UINT32 Info1, UINT32 Info2, UINT8 *AckBuf);
UINT16 ProcessHostCommand (UINT32 Value32, UINT16 Function, UINT8  *DataPointer,
                           UINT16 CommandCount, UINT8 * AckBuf, SOURCE_TASK_ID_TYPE Source_Task);                 
UINT16 ProcessVGAHostCommand(UINT32 Value32, UINT16 Function, UINT8  *DataPointer,
                           UINT16 CommandCount);
UINT16 ComputeAuthorization(void);
void CreateColdStart(void);
UINT16 CreateGraphHeader(UINT16, UINT8 Buffer[]);
UINT16 CreateHornscanHeader(UINT8 AckBuf[]);
UINT16 SendMenuPtrs(UINT8 * to);

UINT16 CreateACK(UINT8 * AckBuf, UINT16 Function, UINT8 * response, UINT16 len);
void ProcessAlarmItems (UINT16 ID);

UINT16 SystemPresetReport1(UINT8 * AckBuf);
UINT16 SystemPresetReport2(UINT8 * AckBuf);
UINT16 SystemPresetReport3(UINT8 * AckBuf);
UINT16 SystemPresetReport4(UINT8 * AckBuf);
UINT16 SystemPresetReport5(UINT8 * AckBuf);
UINT16 DupsPresetReport1(UINT8 * AckBuf);
UINT16 DupsPresetReport2(UINT8 * AckBuf);
UINT16 PrintSeqPresetInfo(UINT8 * AckBuf);

UINT16 CreateSameBufferACK(UINT8 * AckBuf, UINT16 Function, UINT16 len);
UINT16 VGAPrintParameters(UINT8 * to);

UINT16 VGAPrintGraphInfo(UINT8 * to);
UINT16 VGAWeldDataInfo(UINT8 * to);

void InitSBL(void);
void ClearPMCData(void);
void AddToPMCData(void);
UINT16 SendPMCData(UINT8 * AckBuf);
BOOLEAN DUPS_HostUploadParamSet(UINT8 psNum);
BOOLEAN DUPS_HostDownloadParamSet(UINT8 psNum);
void RecallViewCompressedPreset(PRESET_COMPRESSED* CompressPreset);


UINT16 SendQualityLimitsData(UINT8 * to,UINT8 PresetNumber);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
UINT16 LangStrLen(SINT8 * str);
void QVGAResetWeldCounterOk(void);

#define AMP_MAX        100      /*    100 =     100 %  */
#define TEST_AMP        50      /*     50 =      50 %  */
BOOLEAN VGA_ScreenMicronCalFlag = FALSE;
SINT32 VGA_ScreenMicronCalAmp = AMP_MAX;
void VGARequestMicronCalEnabled(void);
void VGARequestMicronCalDisabled(void);
void QVGAExitTestSequence(void);
void VGARequestMicronUpdate(void);
void VGARequestMicronUpdateAll(void);
BOOLEAN VGADisableAmplitudePorcentages(void);

 /*
  *  --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
  */
/* inbound messages to the mich queue */
typedef union{
  GENERIC_MSG     generic;
  HOST_CMD_WELD_MSG host_cmd;
} RSCH_MSG_QUEUE_TYPE;

UINT32 RschQid;


/*------------------ LOCAL FUNCTION DECLARATIONS ---------------------------*/

UINT16 ConvertWeldData(WELD_DATA *Ver8WeldData, UINT8 *StrSPCData);
BOOLEAN CheckForParameterError(UINT16 Value);
void RefreshDUPSParam (PRESET_COMPRESSED* CompPreset);
UINT16 XMLDataProcess(UINT8 * to, UINT16 TempID, UINT16 ID);
void CheckforDisplayLock(void);


/*------------------- PRIVATE GLOBAL DATA ----------------------------------*/

BOOLEAN OnboardDiag = FALSE;   /* For standard software make sure diagnostics are disabled */
UINT8 DateArr[4];
UINT8 TimeArr[3];
UINT16 GlobalCommandID;
STR PresetListBoxBuffer[QVGA_LINESIZE];
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
STR LineBuffer[LINESIZE +1];
UINT8 PasswdEntryFlag;

/* SWVersionLabel moved to Version.c where it belongs */
//SINT8 SWVersionLabel[SW_VERSION_LENTGH+1] = "11.20F";
BOOLEAN SystemParameterChgdFlag = FALSE;

/*------------------------------- CODE -------------------------------------*/
UINT16 SendArrayData(UINT8 ** to, UINT16 TempID);
UINT16 SetArrayData(UINT8 ** to, UINT8    *Value, UINT8    *Arr);


void GetCylinderIndex(void);
void GetStrokeLenIndex(void);
void GetCalData(void);
void UpdateRunTopLine(void);
BOOLEAN DigitalPotEntry(void);
void InitWeldParamOption(void);

void GetRS232Index(void);
void SetRS232Terminal(void);
void SetCylinderDiameter(void);
void SetStrokeLen(void);

void SetBeeperCondition (void);
void CheckForPrintingOrWelding (void);
void QVGAGetSystemInfo(UINT32 MenuExtra);
void CheckForCustomAct (void);

void SaveWeldParamState(void);
void BuildWeldColumnStr(void);
void GetInput(void);
void GetOutput(void);
void SetInputSelection(void);
void SetOutputSelection(void);

void OkToDefault(void);
void ChangeDisplayColumn (void);

void GetWeldScaleIndex(void);
void SetWeldScaleIndex (void);
void SetTestScaleIndex (void);

void GetWeldMode(void);
void SetWeldMode(void);
void PrepareAmplitudeRadioMenu(void);        
void SetAmplitudeModes(void);
void PreparePretriggerRadioMenu(void);
void SetPretriggerModes(void);
void PrepareForceRadioMenu(void);
void SetForceModes(void);
void ChangeDUPSSubParamList(void);
void SetWeldFRateIndex(void);
void SetStepFRateIndex(void);
void SetHoldFRateIndex(void);
void ChangeFreqOffsetSign(void);
void VarDigPotStore(void);
void GetPresetNum (void);
void SaveNamedPreset(void);
void SetPresetClearFlags (void);
void ProcessPresetClear(void);
void PreparePrstSaveTitle (void);
void ProcessPresetRecall (void);
UINT16 ProcessPresetVerify(UINT8 **);
void LangStrCpy(SINT8 * to, SINT8 * from); 
void PreparePrstInfoString (void);                                     
void PresetSaveOk(void);
void PresetSaveCancel(void);
void EraseSeqList (void);
void EraseSeqList1 (void);
void GetSequenceNos (void);
void ChangeWeldCountToOne(void);
void SetPrinterChoice(void);
void SetPageSize(void);
void VQSLimitsChanged(void);
void InitSequenceValue(void);
void SetDisplayRefreshButton(void);
void SetAmpControlValue(void);
void SetFreqControlValue(void);
void SetupForceFixedOrStepFlag(void);
void SetupAmpModeStepFlag(void);
void VGAPasswordEntry(void);
void SetupOption(void);
UINT16 PasswordSave(UINT8 ** to);
void VGATestCheckSum(void);
void GetRTRamp(void);
void SetRTrRamp(void);
void GetReturnRamp(void);
void SetreturnRamp(void);
void GetStartRamp(void);
void SetstartRamp(void);
void UpdateCalibDefault(void);
void ResetHornScanValue(void);
void CopyToBBR(void);

void SetDupsPreset2Index(void);
void SetDupsPreset3Index(void);
void SetDupsPreset4Index(void);
void SetDupsPreset5Index(void);
void SetDupsPreset6Index(void);
void SetDupsPreset7Index(void);
void SetDupsPreset8Index(void);
void SetDupsPreset9Index(void);
void SetDupsPreset10Index(void);
void SetDupsPreset11Index(void);
void SetDupsPreset12Index(void);
void SetDupsPreset13Index(void);
void SetDupsPreset14Index(void);
void SetDupsPreset15Index(void);
void SetDupsPreset16Index(void);
void SetDupsPreset17Index(void);
void SetDupsPreset18Index(void);
void SetDupsPreset19Index(void);

void SetDupsPreset2(void);
void SetDupsPreset3(void);
void SetDupsPreset4(void);
void SetDupsPreset5(void);
void SetDupsPreset6(void);
void SetDupsPreset7(void);
void SetDupsPreset8(void);
void SetDupsPreset9(void);
void SetDupsPreset10(void);
void SetDupsPreset11(void);
void SetDupsPreset12(void);
void SetDupsPreset13(void);
void SetDupsPreset14(void);
void SetDupsPreset15(void);
void SetDupsPreset16(void);
void SetDupsPreset17(void);
void SetDupsPreset18(void);
void SetDupsPreset19(void);
void UpdateCurrentPresetAndSetup(void);

void SetDiagFlag(void);
void ProduceBeep(void);
void GetRunSelection(void);
void GetClearSelection(void);
void GetSeekSelection(void);
void GetStoreSelection(void);

void DisableDiagnostics(void);
void ColdStartEnable(void);
void EnableActColdStart(void);
void DebugReadMemory(void);
void QVGADigitalPotChoiceDone(void);
BOOLEAN DigitalFreqEntry(void);
void VGARecallMinimumPreset(void);
void VGARecallMaximumPreset(void);
void VGARecallColdStartPreset(void);
void VGASaveMinimumPreset(void);
void VGASaveMaximumPreset(void);
void VGASaveColdstartPreset(void);
void VGARestoreMinMaxPreset(void);
void RestoreFactoryColdstart(void);
void EnableHornScanStart(void);
void DUPS_StartHS(void);
void ProcessHSAbort1 (void);
void DoHornDownFunc(void);
void ProcessHDButtonPress2(void);
void ProcessHDButtonPress1(void);            //For retract button
void BottomMenuProcess (void);
void ProcessWindowSetup(void); //for Window Setup
//void  ExitMenuAndEnableWeld (void);
void EnableWelding(void);
void DoColdStart(void);
void VGAActColdStart(void);
void VGARestoreColdStart (void);
void VGACreateColdStartPreset(void);
void EnableCreateStart(void);
void OverwritePresetCheck (void);
void VGAOverwriteAllPreset (void);
void BankSwitchPresets(void);
void CreateGraphData(void);
void VGADebugColdStart(void);
void VGAConfigureFromBUCMenu(void);
void UpdateTestAmp(void);
void SetDigtalPot(void);
void ResetSensorCalb(void);
void VGARequestSensorCal(void);
void SBCReadA2D3(void);
void VGARequestActCal(void);
void SCInitialize(void);
void ManualSCInitialize(void);
void VGACloseCalibration(void);
void DisableCalActKey1(void);
void SBCReadA2D4(void);
void SaveCalibPressure(void);
void CalibFinalCleanup(void);
void SBCReadA2DLC2(void);
void SBCReadA2D1(void);
void VGABuildForceTable(void);
void BuildPressureTable(void);
void GetCurrentPresetNames(void);
UINT16 SendWeldState(UINT8 * to);
UINT16 WeldParams(UINT8  * *Response, UINT16 WeldCount, BOOLEAN ParamFlag);
void SetRunScreenParam(void);
UINT16 VGASendPollingData(UINT8 * to);
void ProcessHDButtonPress3 (void);
UINT16 ProcessWeldGraphValue (UINT8 WeldGraphDataReq, UINT8 WeldCount);
UINT16 SendPMCValue(UINT8 * AckBuf);
UINT16 SystemViewPresetReport(UINT8 * AckBuf);
UINT16 SendAlarmBits(UINT8 * to);
void VGAAlarmReset (UINT32 dummy);
void GetCalStatus(void);
void ChangeBaseAndWordLength(void);
void SetPSFrequency(void);
BOOLEAN SBCReadyFlag = FALSE;

extern BOOLEAN AllParamColumnFlag;
extern STR ps_ver[8];
extern UINT16 WorkingPasswordFlag;
extern UINT16 SystemPres60PSI;
extern UINT16 SystemPres80PSI;
extern STR PSFreqTxt[5];

extern SINT32 SecurityLevel;
extern UINT32 HWConfiguration;
extern UINT32 SWConfiguration;
extern RTC RTCMenu;

extern UINT16 DisplayNextMenu;
extern UINT16 HHInactive1  ;
extern UINT16 IsDisplay;
extern SINT32 WelderAddrMinValue;
extern SINT32 WelderAddrMaxValue;

extern SINT32 AmpMicronsMinValue;
extern SINT32 AmpMicronsMaxValue;

extern SINT32 MinPSWatt;
extern SINT32 MaxPSWatt;
extern SINT32 MinLimitVelocityPC;
extern SINT32 MaxLimitVelocityPC;
extern SINT32 MinSVDelay;
extern SINT32 MaxSVDelay;
extern SINT32 MinLimitForcePC;
extern SINT32 MinLimitMinTrigForce;
extern SINT32 MaxLimitMinTrigForce;
extern UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
extern UNION_BOOL_UINT16 AmplitudeStepMicronsEnableFlag;
extern UINT16 FlagPretriggerDist;
extern UINT16 FlagPretriggerTime;
extern UINT16 FlagPretriggerAmpl; // this flag is for pretrigger amplitude

extern UNION_BOOL_UINT16 ForceStepEnableFlag;
extern UNION_BOOL_UINT16 FreqControlInternal;
extern UINT16 FreqControlExternal,FreqControlInt,EnableStepForce;
extern UINT16 ForceFixedEnableFlag;              

extern UINT16 AmpCntrlExt, AmpCntrlInt;
extern UNION_BOOL_UINT16 AmpControlInternal;

extern const STR *PresetNameArray1[];

extern SINT8 AssignNamePresetBuffer[MESSAGESIZE];
extern STR InfoLine3[QVGA_LINESIZE];
extern STR InfoLine4[QVGA_LINESIZE];
extern STR InfoLine5[QVGA_LINESIZE];
extern STR InfoLine6[QVGA_LINESIZE];
extern UINT16  OldSameNameAvailable;
extern UINT16  NewSameNameAvailable;
extern STR NewSameName[];
extern STR OldSameName[];
extern UINT16 TempSequenceNos;
extern UINT16 ForceStepEnable,AmpStepEnable;
extern SINT32 MinWeldsPerPage, MaxWeldsPerPage;

extern enum LEVEL AccessLevel;
extern const SINT32 MinLimitMin;
extern const SINT32 MaxLimitMax;
extern const SINT32 BUCFactoryDefaults;

extern SINT32 MinBUCFactoryDefaults;
extern SINT32 MaxBUCFactoryDefaults;
extern SINT32 AmpDecayPercentMin;
extern SINT32 AmpDecayPercentMax;
extern const SINT32 MinLimitGainFactor;
extern const SINT32 MaxLimitGainFactor;
extern const SINT32 MinLimitIdleSpeed;
extern const SINT32 MaxLimitIdleSpeed;
extern const SINT32 EnergyBrakeTimeMin;
extern const SINT32 EnergyBrakeTimeMax;
extern const SINT32 EnergyBrakePercentMin;
extern const SINT32 EnergyBrakePercentMax;

extern ALARM_MASKS AlarmPtrRam;
extern const SINT32 AlarmPtrMin;
extern const SINT32 AlarmPtrMax;

extern SINT32 DigPotValue;
extern SINT32 MinDigPotValue, MaxDigPotValue;
extern SINT32 FMemoryBargraph;
extern SINT32 FActualBargraph;
extern BOOLEAN VGARunSelected, VGAClearSelected, VGASeekSelected, VGAStoreSelected;
extern SINT32 DebugPtr;
extern const SINT32 DebugLowValue, DebugHighValue; 
extern UINT16  BransonFunctionFlag;
extern UINT16  SpecialMenuFlag;
extern UINT16  TestingMenuFlag;
extern UINT16  DebugPasswordFlag;

extern BOOLEAN ForceDigitalTuneTest;
extern SINT32 SaveDigPotValue;
extern UINT16 DiagFlag;
extern UINT16 ResonanceFreqEnable[];
extern UNION_BOOL_UINT16 KeepHornDown;           /* TRUE to keep horn down after PB release */
extern SINT32 WorkingForceSet;        /* Temporary target pressure         */   
extern SINT32 RTTransitionDist;       /* Rapid Traverse Transition distance */
extern SINT32 CurrentPressure;
extern UINT16 HDShowPressure;            /* Controls display of sys pressure */
extern BOOLEAN QVGAHornDown;
extern SINT32 HornDownVelocity;
extern SINT32 HDPosition;             /* Same as EncoderPos but never < 0 */
extern SINT32 CurrentForce;            /* Actual horndown force */
extern UINT16 HDShowForce;               /* Controls display of force item */
extern UINT16 HDShowVelocity;            /* Controls display of velocity item */
extern BOOLEAN UserIOAlarmMenu;
extern BOOLEAN StateMachineDisabled;
extern UINT16 HDMenuID;
extern UINT8 FreqType[DUPS_NUMRESONANCES];
extern BOOLEAN HSStartFlag;
extern SINT32 CurrentFreqIn;
extern SINT32 PowerTest;
extern SINT32  UserPressure[3];
extern const SINT32  ForceGaugeReadingMin;  
extern const SINT32  ForceGaugeReadingMax; 
extern enum ERRORCODE_ARG ErrorCode; 
extern const SINT32  LoadCellReadingMin;       /* Lowest acceptable loadcell reading */
extern const SINT32  LoadCellReadingMax;   /* Highest acceptable reading         */
extern SINT32 ForceV[];
extern STR FailedByValue;
extern STR StrWeldStateLine[QVGA_LINESIZE];
extern STR CurrentPresetName;
extern BOOLEAN QVGASnsrCalibAllowed;
extern BOOLEAN QVGACalAllowed;
extern UINT16 TotalCycle;
extern BOOLEAN HSNotStarted;
extern UINT16 ShowHSAbort;
extern UINT8 PrevHornState;
extern BOOLEAN QVGAHornScanOLD;

extern BOOLEAN DebugBase;
extern BOOLEAN DebugBytes;
extern STR    DebugTitle[QVGA_LINESIZE];
extern STR    DebugText1[QVGA_LINESIZE];
extern STR    DebugText2[QVGA_LINESIZE];
extern STR    DebugText3[QVGA_LINESIZE];
extern STR    DebugText4[QVGA_LINESIZE];
extern SINT32 ActualHoldTime;
extern WELD_DATA WeldingResults;
extern SINT32 ActualPeakPower;
extern SINT32 TriggerLostTime;
extern SINT32 WeldForceEnd;
extern SINT32    TestTime;
extern SINT32 MaximumForce;
extern SINT32 FreqChg, TestTime, PowerTest;
extern SINT32    PTSTimer;
extern SINT32    ActualAfterburstTime;
extern SINT32    ABOverloadPower;
extern SINT32    OverloadPower, OverloadFreq;
extern SINT32    ActualSeekTime;
extern DUPS_WELDSTATUS ABOLStatus, WeldOLStatus;
extern SINT32    EBOverloadTimer,EBOverloadPower, EBOverloadFreq;
extern SINT32 ActualForceMax;
extern SINT32 ActualSBLMinFreq, ActualSBLMaxFreq;
extern SINT32 ActualValuePMC1, ActualValuePMC2;
extern UINT16 BinEnable,HexEnable;
extern UINT8 MenuNxtPointer;
extern BOOLEAN  VGAUSBFullStatus;
/***************** Map Table for Functions and Variables  ***********************/

enum DATA_TYPE{
   nothing,
   uint8,
   sint8,
   uint16,
   sint16,
   uint32,
   sint32,
   boolean,
   str,
   arr
};

typedef enum {
   WELDHISTORY,               /* Summary of last 50 welds   */
   WELDSUMMARY,               /* Information for each weld  */
   POWERGRAPH,                /* Graph of Power vs Time     */
   AMPGRAPH,                  /* Graph of Amplitude vs Time */
   FREQGRAPH,                 /* Graph of Frequency vs Time */
   COLDISTGRAPH,              /* Graph of Distance vs Time  */
   VELOCITYGRAPH,             /* Graph of Velocity vs Time  */
   FORCEGRAPH,                /* Graph of Force vs Time     */
   PRESETPRN,                 /* Prints out the Preset and System variables */
   FINALRESULTS,              /* Summary of last weld       */ 
   ONEMSDATA,
   ABSDISTGRAPH,
   HORNSCAN,
   DUPSPRESET,
   SEQUENCEPRESET
   }MSG_GRAPH_TYPE;

typedef struct Map{
   int       Struct_ID;
   void      *Vptr;
   enum DATA_TYPE DataType;
   UINT16    *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16    *DisableFlag;          /* Pointer to disable/enable flag        */
   void      (*Function1)(void);   // for those with two void func(void) type functions.(Fuction 1)
   void      (*Function2)(void);   // for all others (Function2)
}MAP;


typedef struct MinMaxMap{
   UINT16   Struct_ID;
   SINT32   *ptrmin;               /* Pointer to minimum value accepted     */
   SINT32   *ptrmax;               /* Pointer to maximum value accepted     */
}MINMAXMAP;


void GetTime(void)
{
   SetupOption();
   TimeArr[0] = (UINT8)RTCMenu.Hour;
   TimeArr[1] = (UINT8)RTCMenu.Minute;

}

void GetDate(void)
{
   SetupOption();
   if(CurrentSetup.Units == TRUE) /*Display Time in the DD/MM/YY format.*/
   {

      DateArr[0] = (UINT8)RTCMenu.Day;
      DateArr[1] = (UINT8)RTCMenu.Month;
      DateArr[2] = (UINT8)RTCMenu.Year;
   }
   else                       /*Display Time in MM/DD/YY format*/
   {
      DateArr[0] = (UINT8)RTCMenu.Month;
      DateArr[1] = (UINT8)RTCMenu.Day;
      DateArr[2] = (UINT8)RTCMenu.Year;
   }
}

void TimeSet(void)
{
   RTCMenu.Hour = (SINT32)TimeArr[0];
   RtcWrite(HOUR, RTCMenu.Hour);
   RTCMenu.Minute = (SINT32)TimeArr[1];
   RtcWrite(MINUTE, RTCMenu.Minute); 
   RtcWrite(SECONDS, 0);
}

void DateSet(void)
{
    RTCMenu.Month = (SINT32)DateArr[0];
    RtcWrite(MONTH, RTCMenu.Month);
    RTCMenu.Day = (SINT32)DateArr[1];
    RtcWrite(DAY, RTCMenu.Day);
    RTCMenu.Year = (SINT32)DateArr[2];
    RtcWrite(YEAR, RTCMenu.Year);
}

const MAP Map[]={
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ID    Variable Pointer                    Variable Pointer to flag   Pointer to                    Function 1              Function2                           comment                             */
/*                                             Type     to see if       disable/enable                                                                                                                */
/*                                                    Display Line      flag                                                                                                                          */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
   {0,   &CurrentSetup.Units,                boolean, NULL,             NULL,                         NULL,                   UpdateRunTopLine           },    //UnitsChoice
   {1,   &CurrentSetup.StartScreen,          boolean, NULL,             NULL,                         NULL,                   NULL                       },    //VGAStartScreenChoice
   {2,   &RadioIndex,                        uint16,  NULL,             NULL,                         GetRS232Index,          SetRS232Terminal           },    //RS232Selection
   {3,   &CurrentSetup.WelderAddrValue,      sint32,  NULL,             &CurrentSetup.WelderAddrFlag, NULL,                   NULL                       },    //WelderAddr
   {4,   &CurrentPreset.GeneralAlarmLFlag,   uint16,  NULL,             NULL,                         NULL,                   NULL                       },    //GeneralAlarmChoice
   {5,   &TimeArr,                           arr,     NULL,             NULL,                         GetTime,                TimeSet                    },    //TimeOfDay
   {6,   &DateArr,                           arr,     NULL,             NULL,                         GetDate,                DateSet                    },    //MonthDateYear
   {7,   &CurrentSetup.AmpControl,           boolean, NULL,             NULL,                         NULL,                   SetAmpControlValue         },    //AmpControl
   {8,   &CurrentSetup.ExtraCooling,         boolean, NULL,             NULL,                         NULL,                   NULL                       },    //ExtraCoolingOpt
   {9,   &CurrentSetup.HandHeld,             boolean, NULL,             NULL,                         NULL,                   DealWithHandHeldChange     },    //HandHeld
   {10,  &CurrentSetup.PLCControlFlag,       boolean, (UINT16*)&CurrentSetup.PLCControlMenuFlag,NULL, NULL,                   DealWithHandHeldChange     },    //PLCControl
   {11,  &CurrentSetup.ExtPresets,           boolean, NULL,             NULL,                         NULL,                   DealWithExtPresetChange    },    //ExtPresets
   {12,  &CurrentPreset.DigitalFilterFlag,   uint16,  NULL,             NULL,                         NULL,                   NULL                       },    //DigitalFilter
   {13,  &CurrentSetup.FreqControl,          boolean, NULL,             NULL,                         NULL,                   SetFreqControlValue        },    //FreqControl
   {14,  &CurrentSetup.PSLifetime,           sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //PSLifetime
   {15,  &CurrentSetup.Overload,             sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //Overloads
   {16,  &CurrentSetup.GenAlarmCount,        sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //GeneralAlarm
   {17,  &CurrentSetup.PSWatt,               sint32,  NULL,             NULL,                         GetPowerSupplyInfo,     NULL                       },    //FrequencyWatts
   {18,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetCalStatus,           NULL                       },    //CalibrationPass
   {19,  &DateArr,                           arr,     NULL,             NULL,                         GetCalData,             NULL                       },    //CalibrationDate
   {20,  &ps_ver,                            str,     NULL,             NULL,                         GetSerialNumbers,       NULL                       },    //PowerSupplyVersion
   {21,  &RadioIndex,                        uint16,  NULL,             NULL,                         LoadActuatorType,       NULL                       },    //ActuatorType 
   {22,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetControlLevel,        NULL                       },    //ControlLevelType
   {23,  &CurrentSetup.PSSerialNumber,       arr,     NULL,             NULL,                         NULL,                   StorePSSerialNumber        },    //PowerSupplySerialNumber / SetPSSerNum
   {24,  &CurrentSetup.ActSerialNumber,      arr,     NULL,             NULL,                         NULL,                   SaveActSerialNum           },    //ActuatorSerialNumber / SetActSerNum
   {25,  NULL,                               nothing, &SystemPres60PSI, NULL,                         NULL,                   NULL                       },    //SetPressure60PSI
   {26,  NULL,                               nothing, &SystemPres80PSI, NULL,                         NULL,                   NULL                       },    //SetPressure80PSI
   {27,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetCylinderIndex,       SetCylinderDiameter        },    //CylinderDiameter
   {28,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetStrokeLenIndex,      SetStrokeLen               },    //CylinderStroke
   {29,  &DUPS_Info.LibraryName,             str,     NULL,             NULL,                         NULL,                   NULL                       },    //QVGALibraryBlockName
   {30,  &WorkingPasswordFlag,               uint16,  NULL,             NULL,                         SetupOption,          VGAPasswordEntry             },    //QVGAPasswordChoice
   {31,  &CurrentSetup.USBGlobalFlag,        boolean, NULL,             NULL,                         NULL,                   NULL                       },    //USBGlobalToggle
   {32,  &CurrentSetup.USBWDSampleValue,     sint32,  NULL,             &CurrentSetup.USBWDSampleFlag,NULL,                   NULL                       },    //USBWeldDataSample
   {33,  &CurrentSetup.USBWDAlarmFlag,       boolean, NULL,             NULL,                         NULL,                   NULL                       },    //USBWeldDataAlarm
   {34,  &CurrentSetup.USBPGSampleValue,     sint32,  NULL,             &CurrentSetup.USBPGSampleFlag,NULL,                   NULL                       },    //USBPowerSample
   {35,  &CurrentSetup.USBPGAlarmFlag,       boolean, NULL,             NULL,                         NULL,                   NULL                       },    //USBPowerAlarm
   {36,  &CurrentSetup.USBCDGSampleValue,    sint32,  NULL,             &CurrentSetup.USBCDGSampleFlag,NULL,                  NULL                       },    //USBDistanceSample
   {37,  &CurrentSetup.USBCDGAlarmFlag,      boolean, NULL,             NULL,                         NULL,                   NULL                       },    //USBDistanceAlarm
   {38,  &CurrentSetup.USBVGSampleValue,     sint32,  NULL,             &CurrentSetup.USBVGSampleFlag,NULL,                   NULL                       },    //USBVelocitySample
   {39,  &CurrentSetup.USBVGAlarmFlag,       boolean, NULL,             NULL,                         NULL,                   NULL                       },    //USBVelocityAlarm
   {40,  &CurrentSetup.USBFGSampleValue,     sint32,  NULL,             &CurrentSetup.USBFGSampleFlag,NULL,                   NULL                       },    //USBForceSample
   {41,  &CurrentSetup.USBFGAlarmFlag,       boolean, NULL,             NULL,                         NULL,                   NULL                       },    //USBForceAlarm
   {42,  &CurrentSetup.USBAGSampleValue,     sint32,  NULL,             &CurrentSetup.USBAGSampleFlag,NULL,                   NULL                       },    //USBAmplitudeSample
   {43,  &CurrentSetup.USBAGAlarmFlag,       boolean, NULL,             NULL,                         NULL,                   NULL                       },    //USBAmplitudeAlarm
   {44,  &CurrentSetup.USBFreqGSampleValue,  sint32,  NULL,             &CurrentSetup.USBFreqGSampleFlag,NULL,                NULL                       },    //USBFreqSample
   {45,  &CurrentSetup.USBFreqGAlarmFlag,    boolean, NULL,             NULL,                         NULL,                   NULL                       },    //USBFreqAlarm
   {46,  NULL,                               nothing, NULL,             NULL,                         NULL,             QVGAResetWeldCounterOk           },    //VGAWeldCountResetOk
   {47,  &CurrentSetup.BeeperTrigger,        uint16,  &HHInactive1,     NULL,                      SetBeeperCondition,        NULL                       },    //BeeperTrigger
   {48,  &CurrentSetup.BeeperRelease,        uint16,  (UINT16*)&CurrentSetup.HandHeld,NULL,           NULL,                   NULL                       },    //BeeperRelease
   {49,  &CurrentSetup.BeeperError,          uint16,  NULL,             NULL,                         NULL,                   NULL                       },    //BeeperError
   {50,  &CurrentSetup.BeeperAlarm,          uint16,  NULL,             NULL,                         NULL,                   NULL                       },    //BeeperAlarm
   {51,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetPSFreq,         SetPSFrequency                  },    //SetPSFreq

   
   {52,  &CurrentSetup.PSWatt,               sint32,  NULL,             NULL,                         NULL,                StorePSWattage                },    //SetPSWatts
   {53,  &CurrentSetup.PSType,               boolean, NULL,             NULL,                         NULL,                   NULL                       },    //SetPsChoice
   {54,  &LineBuffer,                        arr,     NULL,             NULL,                         NULL,                   NULL                       },    //PasswordSaveCommand
   {55,  NULL,                               nothing, NULL,             NULL,                         NULL,                CheckForPrintingOrWelding     },    //QVGAActIOMenu

   {56,  &CurrentSetup.ULSLogicCustom,       boolean, NULL,             NULL,                         NULL,                CheckForCustomAct             },    //ULS
   {57,  &CurrentSetup.GndDetLogicCustom,    boolean, NULL,             NULL,                         NULL,                CheckForCustomAct             },    //GndDet

   {58,  &BUCMenuRAM.VelocityPC,             sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //SetVelocityPC
   {59,  &BUCMenuRAM.ForcePC,                sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //SetForcePC
   {60,  &CurrentSetup.MinTrigForce,         sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //SetMinTrigger
   {61,  &CurrentSetup.Metric3Flag,          boolean, NULL,             (UINT16 *)&CurrentSetup.Units,NULL,                   UpdateRunTopLine           },    //MetricChoice
   {62,  NULL,                               nothing, NULL,             NULL,                         NULL,                   CheckForPrintingOrWelding  },    //QVGAUserIOMenu
   {63,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetWeldScaleIndex,      SetWeldScaleIndex          },    //WeldScaleChoice
   {64,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetTestScaleIndex,      SetTestScaleIndex          },    //TestScaleChoice
   
   {65,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //TimeDisplay
   {66,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //PkPwrDisplay
   {67,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //EnergyDisplay
   {68,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //VelocityDisplayAed
   {69,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //VelocityDisplayAef
   {70,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //FreqMinDisplay
   {71,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //FreqMaxDisplay
   {72,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //FreqStartDisplay
   {73,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //FreqEndDisplay
   {74,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //FreqChgDisplay
   {75,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //SetAmpADisplay
   {76,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //SetAmpBDisplay`
   {77,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //WeldAbsDisplay
   {78,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //ActPressDisplay
   {79,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //TotalAbsDisplay
   {80,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //WeldColDisplay
   {81,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //TotalColDisplay
   {82,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //WeldForceDisplay
   {83,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //SetForceADisplay
   {84,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //SetForceBDisplay
   {85,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //PresetNumDisplay
   {86,  &RadioIndex,                        uint16,  NULL,             NULL,                         BuildWeldColumnStr,     SaveWeldParamState          },    //CycleTimeDisplay
   {87,  &RadioIndex,                        uint16,  NULL,             NULL,                         NULL,                   ChangeDisplayColumn         },    //VGARadioColumnOk

   {88,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetInput,               SetInputSelection          },    //J3_32_Input
   {89,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetInput,               SetInputSelection          },    //J3_33_Input
   {90,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetInput,               SetInputSelection          },    //J3_19_Input
   {91,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetInput,               SetInputSelection          },    //J3_17_Input
   {92,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetInput,               SetInputSelection          },    //J3_31_Input
   {93,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetInput,               SetInputSelection          },    //J3_1_Input

   {94,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetOutput,              SetOutputSelection         },    //J3_8_OutputSwap & J3_8_Output
   {95,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetOutput,              SetOutputSelection         },    //J3_36_OutputSwap & J3_36_Output
   {96,  &RadioIndex,                        uint16,  NULL,             NULL,                         GetOutput,              SetOutputSelection         },    //J3_22_Output
   
   {97,  &CurrentSetup.UserInLogic,          uint16,  NULL,             NULL,                         NULL,                   NULL                       },    //InputsActiveState
   {98,  &CurrentSetup.SVDelay,              sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //SVDelay

   {99,  NULL,                               nothing, NULL,             NULL,                         NULL,                   OkToDefault                },    //VGADefaultIOOk
 
   {100,  &CurrentPreset.WeldMode,           uint16,  NULL,             NULL,                         NULL,                   NULL                       },    //WeldSetupChoice /*not to be used*/
   {101,  &RadioIndex,                       uint16,  NULL,             NULL,                         GetWeldMode,            SetWeldMode                },    //WeldModeMenuTime
   {102,  &CurrentPreset.WeldTime,           sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //VGAWeldTimeTime
   {103,  &CurrentPreset.HoldTime,           sint32,  NULL,             &CurrentPreset.HoldTimeFlag,  NULL,                   NULL                       },    //VGAHoldTime1
   {104,  &CurrentPreset.TriggerForce,       sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //VGATriggerForce
   {105,  &CurrentPreset.ExtTrgDelay,        uint16,  NULL,             NULL,                         NULL,                   NULL                       },    //VGAExtTriggerDelayChoice

   {106,  &RadioIndex,                       uint16,  NULL,            NULL,                   PrepareAmplitudeRadioMenu,   SetAmplitudeModes            },    //radioAmplitudeMode
   {107,  &CurrentPreset.Amp1,               sint32,  &AmplitudeStepMicronsEnableFlag.uint16.Low,NULL,NULL,                   NULL                       },    //AmplitudeA
   {108,  &CurrentPreset.Amp2,               sint32,  &AmplitudeStepMicronsEnableFlag.uint16.Low,NULL,NULL,                   NULL                       },    //AmplitudeB
   {109,  &CurrentPreset.AmpTrigTimeValue,   sint32,  &AmplitudeStepEnableFlag.uint16.Hi,&CurrentPreset.Amp2Flag,NULL,        SelectAmpTriggerTime       },    //AmpStepAtTime
   {110,  &CurrentPreset.AmpTrigEnerValue,   sint32,  &AmplitudeStepEnableFlag.uint16.Hi,&CurrentPreset.Amp2Flag,NULL,        SelectAmpTriggerEnergy     },    //AmpStepAtEner
   {111,  &CurrentPreset.AmpTrigPowerValue,  sint32,  &AmplitudeStepEnableFlag.uint16.Hi,&CurrentPreset.Amp2Flag,NULL,        SelectAmpTriggerPower      },    //AmpStepAtPower
   {112,  &CurrentPreset.AmpTrigColValue,    sint32,  &AmplitudeStepEnableFlag.uint16.Hi,&CurrentPreset.Amp2Flag,NULL,        SelectAmpTriggerDist       },    //AmpStepAtDist
   {113,  &CurrentPreset.AmpTrigExtFlag,     uint16,  &AmpStepEnable,   NULL,                   SetupAmpModeStepFlag,         SelectAmpTriggerExt        },    //AmpStepExt(choice)
   {114,  &CurrentPreset.Amp1,               sint32,  &AmpCntrlInt,  &CurrentPreset.Amp2Flag,      SetAmpControlValue,        NULL                       },    //VGAAmplitude1
   {115,  &CurrentPreset.HoldForce,          sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //VGAHoldForce
   
   {116,  &CurrentPreset.WeldEnergy,         sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //VGAWeldEnergyEnergy
   {117,  &CurrentPreset.PeakPwr,            sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //VGAPeakPowerPP
   {118,  &CurrentPreset.ColDist,            sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //VGACollapseColl
   {119,  &CurrentPreset.AbsDist,            sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //VGAAbsoluteAbs
   {120,  &CurrentPreset.ScrubTime,          sint32,  NULL,      &CurrentPreset.ScrubTimeFlag,        NULL,                   NULL                       },    //VGAScrubTimeGndDet
   {121,  &CurrentPreset.AmpScrubTime,       sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //AmpGroundDetect
   {122,  &CurrentPreset.AbFlag,             uint16,  NULL,             NULL,                         NULL,                   NULL                       },     //VGAAfterburstChoice
   {123,  &CurrentPreset.AbDelay,            sint32,  NULL,             NULL,                         NULL,                   NULL                       },    //ABDelayTime
   {124,  &CurrentPreset.AbTime,             sint32,  NULL,             NULL,                         NULL,                   NULL                       },     //ABTimeTime
   {125,  &CurrentPreset.AbAmp,              sint32,  &AmpControlInternal.uint16.Hi,   NULL,      SetAmpControlValue,         NULL                       },      //ABAmplitude

   {126,  &RadioIndex,                       uint16,  NULL,             NULL,            PreparePretriggerRadioMenu,          SetPretriggerModes         },    //radioPretriggerMode
   {127,  &CurrentPreset.PreTrigDist,        sint32,  &FlagPretriggerDist,NULL,                       NULL,                   NULL                       },    //varPretrigDist
   {128,  &CurrentPreset.PreTrigDelay,       sint32,  &FlagPretriggerTime,NULL,                       NULL,                   NULL                       },    //varPretrigTime
   {129,  &CurrentPreset.PreTrigAmp,         sint32,  &FlagPretriggerAmpl,NULL,                       NULL,                   NULL                       },    //varPretrigAmplitude
   
   {130,  &CurrentPreset.PMCEnabled,         uint16,  NULL,             NULL,                         NULL,                   NULL                       },    //VGAPwrMatchCurve

/***************************************************************************************************** VGARejectLimitsChoice ************************************************************************************/
   {131,  &CurrentPreset.RejectLimitsFlag,   uint16,  NULL,                                           NULL,                      NULL,                   NULL                       },    //VGARejectLimitsChoice
   {132,  &CurrentPreset.RejResetRequiredFlag,uint16, NULL,                                           NULL,                      NULL,                   NULL                       },    //ResetRequiredRLimit
   {133,  &CurrentPreset.TimePLR,            sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //PTimeREnergy
   {134,  &CurrentPreset.TimeMLR,            sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //MTimeREnergy
   {135,  &CurrentPreset.EnergyPLR,          sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //PEnergyRTime
   {136,  &CurrentPreset.EnergyMLR,          sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //MEnergyRTime
   {137,  &CurrentPreset.PowerPLR,           sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //PPkPowerRLimit
   {138,  &CurrentPreset.PowerMLR,           sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //MPkPowerRLimit
   {139,  &CurrentPreset.ColPLR,             sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //PColDistRLimit
   {140,  &CurrentPreset.ColMLR,             sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //MColDistRLimit
   {141,  &CurrentPreset.AbsPLR,             sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //PAbsDistRLimit
   {142,  &CurrentPreset.AbsMLR,             sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //MAbsDistRLimit
   {143,  &CurrentPreset.TrsDistPLR,         sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //PTrigDistRLimit
   {144,  &CurrentPreset.TrsDistMLR,         sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //MTrigDistRLimit
   {145,  &CurrentPreset.WeldForcePLR,       sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //PMaxForceRLimit
   {146,  &CurrentPreset.WeldForceMLR,       sint32,  &CurrentPreset.RejectLimitsFlag,             &CurrentPreset.RejectLimits,  NULL,                   NULL                       },    //MMaxForceRLimit
   {147,  &CurrentPreset.SBLMaxFreq,         sint32,  &CurrentSetup.SBLEnable,                     &CurrentPreset.SBLFreqFlags,  NULL,                   NULL                       },    //PSBLFreqLimit
   {148,  &CurrentPreset.SBLMinFreq,         sint32,  &CurrentSetup.SBLEnable,                     &CurrentPreset.SBLFreqFlags,  NULL,                   NULL                       },    //MSBLFreqLimit

/***************************************************************************************************** VGASuspectLimitsChoice *************************************************************************************/
   {149,  &CurrentPreset.SuspectLimitsFlag,  uint16,  NULL,                                            NULL,                       NULL,                   NULL                      },    //VGASuspectLimitsChoice
   {150,  &CurrentPreset.SusResetRequired,   uint16,  NULL,                                            NULL,                       NULL,                   NULL                      },    //ResetRequiredSLimit
   {151,  &CurrentPreset.TimePLS,            sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //PTimeSEnergy
   {152,  &CurrentPreset.TimeMLS,            sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //MTimeSEnergy
   {153,  &CurrentPreset.EnergyPLS,          sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //PEnergySTime
   {154,  &CurrentPreset.EnergyMLS,          sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //MEnergySTime
   {155,  &CurrentPreset.PowerPLS,           sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //PPkPowerSLimit
   {156,  &CurrentPreset.PowerMLS,           sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //MPkPowerSLimit
   {157,  &CurrentPreset.ColPLS,             sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //PColDistSLimit
   {158,  &CurrentPreset.ColMLS,             sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //MColDistSLimit
   {159,  &CurrentPreset.AbsPLS,             sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //PAbsDistSLimit
   {160,  &CurrentPreset.AbsMLS,             sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //MAbsDistSLimit
   {161,  &CurrentPreset.TrsDistPLS,         sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //PTrigDistSLimit
   {162,  &CurrentPreset.TrsDistMLS,         sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //MTrigDistSLimit
   {163,  &CurrentPreset.WeldForcePLS,       sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //PMaxForceSLimit
   {164,  &CurrentPreset.WeldForceMLS,       sint32,  &CurrentPreset.SuspectLimitsFlag,             &CurrentPreset.SuspectLimits,  NULL,                   NULL                      },    //MMaxForceSLimit

/***************************************************************************************************** VGAForceChoiceStep / Fixed ************************************************************************************/
   {165,  &RadioIndex,                       uint16,  NULL,                             NULL,          PrepareForceRadioMenu, SetForceModes              },    //radioForceMenu
   {166,  &CurrentPreset.WeldForce,          sint32,  &ForceStepEnableFlag.uint16.Hi,   NULL,                    NULL,             NULL                  },    //WeldForceA 
   {167,  &CurrentPreset.Force2,             sint32,  &ForceStepEnableFlag.uint16.Hi,   NULL,                    NULL,             NULL                  },    //WeldForceB
   {168,  &CurrentPreset.ForceTrigTimeValue, sint32,  &ForceStepEnableFlag.uint16.Hi,&CurrentPreset.Force2Flag,  NULL,        SelectForceTriggerTime     },    //ForceStepAtTime
   {169,  &CurrentPreset.ForceTrigEnerValue, sint32,  &ForceStepEnableFlag.uint16.Hi,&CurrentPreset.Force2Flag,  NULL,        SelectForceTriggerEnergy   },    //ForceStepAtEner
   {170,  &CurrentPreset.ForceTrigPowerValue,sint32,  &ForceStepEnableFlag.uint16.Hi,&CurrentPreset.Force2Flag,  NULL,        SelectForceTriggerPower    },    //ForceStepAtPower
   {171,  &CurrentPreset.ForceTrigColValue,  sint32,  &ForceStepEnableFlag.uint16.Hi,&CurrentPreset.Force2Flag,  NULL,        SelectForceTriggerDist     },    //ForceStepAtCol
   {172,  &CurrentPreset.ForceTrigExtFlag,   uint16,  &ForceStepEnable,                 NULL,     SetupForceFixedOrStepFlag,  SelectForceTriggerExt      },    //ForceStepExt(choice)

/***************************************************************************************************** EnergyBrakingChoice  *******************************************************************************************/
   {173,  &CurrentPreset.EnergyBraking,      uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //EnergyBrakingChoice
   {174,  &CurrentPreset.EBTime,             sint32,  NULL,                             NULL,                    NULL,        NULL                       },    //EBTime

   {175,  &CurrentPreset.WeldForce,          sint32,  NULL,                   &CurrentPreset.Force2Flag,         NULL,        NULL                       },    //VGAWeldForceSetupMenu
   {176,  &CurrentPreset.PreSeek,            uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //VGAPreWeldSeekChoice
   {177,  &CurrentPreset.SeekFunFlag,        uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //VGAPostWeldSeekChoice

/***************************************************************************************************** VGAFreqOffsetChoice  *******************************************************************************************/
   {178,  &CurrentPreset.FreqOffsetFlag,     uint16,  &FreqControlInt,                  NULL,             SetFreqControlValue,NULL                       },    //VGAFreqOffsetChoice
   {179,  &CurrentPreset.FreqOffset,         sint32,  &FreqControlInternal.uint16.Hi,   NULL,                    NULL,        NULL                       },    //FreqOffset

/***************************************************************************************************** VGAActClearOutputChoice  ***************************************************************************************/
   {180,  &CurrentPreset.ActClrFlag,         uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //VGAActClearOutputChoice
   {181,  &CurrentPreset.ActClrDistance,     sint32,  NULL,                             NULL,                    NULL,        NULL                       },    //Distance

/***************************************************************************************************** VGAControlLimitsChoice1 /Choice2 *******************************************************************************/
   {182,  &CurrentPreset.ControlLimitsFlag,  uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //VGAControlLimitsChoice1 /Choice2
   {183,  &CurrentPreset.EnergyCompFlag,     uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //EnergyCompChoice
   {184,  &CurrentPreset.EnergyPL,           sint32,  NULL,                             NULL,                    NULL,        NULL                       },    //MaxEnergyComp
   {185,  &CurrentPreset.EnergyML,           sint32,  NULL,                             NULL,                    NULL,        NULL                       },    //MinEnergyComp
   {186,  &CurrentPreset.PeakPwrCutoff,      sint32,  NULL,        &CurrentPreset.PeakPwrCutoffFlag,             NULL,        NULL                       },    //PeakPowerCutoff
   {187,  &CurrentPreset.ABSCutoffDist,      sint32,  NULL,        &CurrentPreset.ABSCutoffFlag,                 NULL,        NULL                       },    //ABSCutoff
   {188,  &CurrentPreset.ColCutoffDist,      sint32,  NULL,        &CurrentPreset.ColCutoffFlag,                 NULL,        NULL                       },    //CollapseCutoff

/***************************************************************************************************** VGACycleAbortsChoice1 /Choice2 **********************************************************************************/
   {189,  &CurrentPreset.CycleAbortFlag,     uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //VGACycleAbortsChoice1 /Choice2
   {190,  &CurrentPreset.GndDetectFlag,      uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //GndDetChoice
   {191,  &CurrentPreset.MissingPartFlag,    uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //MissingPart
   {192,  &CurrentPreset.MissingPartMax,     sint32,  NULL,        &CurrentPreset.MissingMaxFlag,                NULL,        NULL                       },    //MissingPartMaximum
   {193,  &CurrentPreset.MissingPartMin,     sint32,  NULL,        &CurrentPreset.MissingMinFlag,                NULL,        NULL                       },    //MissingPartMinimum

   {194,  &CurrentPreset.RTFlag,             uint16,  NULL,                             NULL,                    NULL,        NULL                       },    //VGARapidTraverseChoice
   {195,  &CurrentPreset.RTDist,             sint32,  NULL,                             NULL,                    NULL,        NULL                       },    //StepAtRTDist
   {196,  &CurrentPreset.DownSpdStart,       sint32,  NULL,                             NULL,                    NULL,        NULL                       },    //VGADownSpeed

/********************************************************************************************************************** DigitalUPS **************************************************************************************/
   {197,  &DUPS_Info.DUPSMemFlag,            boolean, NULL,                             NULL,                    NULL, DUPS_ModifySWDipSetting           },    //MemorySetup
   {198,  &DUPS_CurrentParamSet.WeldRampTime,sint32,  NULL,                             NULL,                    NULL, ChangeDUPSSubParamList            },    //RTime
   {199,  &DUPS_CurrentParamSet.SeekTime,    sint32,  NULL,                             NULL,                    NULL, ChangeDUPSSubParamList            },    //STime
   {200,  &DUPS_Info.DUPSSeekFlag,           boolean, NULL,                             NULL,                    NULL, DUPS_ModifySWDipSetting           },    //DupsTimedSeek
   {201,  &DUPS_Info.DUPSMemRstFlag,         boolean, NULL,                             NULL,                    NULL, DUPS_ModifySWDipSetting           },    //MemoryResetSetup
   {202,  &CurrentPreset.WeldStatusFlag,     boolean, NULL,                             NULL,                    NULL, UpdateWS_Config                   },    //DupsWeldStatus
  
/********************************************************************************************************************** VGAForceRampsMenu *******************************************************************************/
   {203,  &RadioIndex,                       uint16,  NULL,                             NULL,                GetWeldFRateIndex,  SetWeldFRateIndex       },    //WeldFRate
   {204,  &RadioIndex,                       uint16,  NULL,                             NULL,                GetStepFRateIndex,  SetStepFRateIndex       },    //StepFRate
   {205,  &RadioIndex,                       uint16,  NULL,                             NULL,                GetHoldFRateIndex,  SetHoldFRateIndex       },    //HoldFRate
   {206,  &CurrentPreset.MaxTimeout,         sint32,  NULL,                             NULL,                    NULL,              NULL                 },    //VGAMaxTimeout

   {207,  NULL,                              nothing,  NULL,                            NULL,                    NULL,        ChangeFreqOffsetSign       },    //ChangeFreqSign
   {208,  &CurrentSetup.AmpControl,          boolean,  &AmpCntrlExt,                    NULL,                 SetAmpControlValue,   ProduceBeep          },    //AmplitudeExt
   {209,  &CurrentSetup.FreqControl,         boolean,  &FreqControlExternal,            NULL,                 SetFreqControlValue,  ProduceBeep          },    //QVGAFreqOffsetExt
   {210,  &CurrentPreset.WriteIn1,           arr,     NULL,                             NULL,                     NULL,             NULL                 },    //VGAWriteInSubmenu
   {211,  &CurrentPreset.WriteIn2,           arr,     NULL,                             NULL,                     NULL,             NULL                 },    //VGAWriteInSubmenu
   {212,  &DebugTitle,                       str,     NULL,                             NULL,                     NULL,             NULL                 },   //TitleDebug 
   {213,  &DebugBase,                        boolean, &BinEnable,                       NULL,                     NULL,     ChangeBaseAndWordLength      },   //toggleDebugBaseBinary

/********************************************************************************************************************** QVGAPresetsChoice ********************************************************************************/
   {214,  &VGAPresetNum,                     uint16,  NULL,                             NULL,           PreparePrstInfoString,PreparePrstSaveTitle       },    //VGAPresetSave
   {215,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                  GetPresetNum,        NULL                 },    //QVGAPresetsChoice
   {216,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                     NULL,       SaveNamedPreset            },    //VGAAutoName
   {217,  &OldSameName,                      str,  &OldSameNameAvailable,               NULL,                     NULL,       SaveNamedPreset            },    //VGASameNameAsOld
   {218,  &NewSameName,                      str,  &NewSameNameAvailable,               NULL,                     NULL,       SaveNamedPreset            },    //VGASameNameAsNew
   {219,  &AssignNamePresetBuffer,           arr,     NULL,                             NULL,                     NULL,       SaveNamedPreset            },    //VGAAssignName
  
   {220,  &PresetListBoxBuffer,               arr,    NULL,                             NULL,                     NULL,             NULL                 },    //SendVGAListBox
   {221,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                     NULL,        SetPresetClearFlags       },    //VGAPresetClear
   {222,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                     NULL,        ProcessPresetClear        },    //VGAClearOk
   {223,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                     NULL,        ProcessPresetRecall       },    //VGAPresetRecall
   {224,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                     NULL,             NULL                 },    //VGAPresetVerify
   {225,  &PresetListBoxBuffer,              arr,     NULL,                             NULL,                     NULL,             NULL                 },    //VGAPresetInfo
   {226,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                     NULL,       PreparePrstInfoString      },    //VGAPresetInfo
   {227,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                     NULL,       PresetSaveOk               },    //VGASaveOk   
   {228,  &VGAPresetNum,                     uint16,  NULL,                             NULL,                     NULL,       PresetSaveCancel           },    //VGASaveCancel   
   {229,  NULL,                              nothing, NULL,                             NULL,                     NULL,       EraseSeqList1              },    //Erase Sequencing list   

/********************************************************************************************************************** VGASequenceEnable *********************************************************************************/
   {232,  &TempSequenceNos,                  uint16,  NULL,                             NULL,                  GetSequenceNos,            NULL           },    //VGASequenceEnable
   {233,  &CurrentSetup.SequenceEnable,      boolean, NULL,                             NULL,                    NULL,                    NULL           },    //SeqEnableToggle
   {234,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 EraseSeqList      },    //Erase Sequencing list
   {235,  &PresetListBoxBuffer,              arr,     NULL,                             NULL,                    NULL,                    NULL           },    //SendSeqListBox
   {236,  &CurrentSetup.SequenceList,        arr,     NULL,                             NULL,                    NULL,                    NULL           },    //Store Seq. List
   {237,  &CurrentSetup.SequenceNos,         uint16,  NULL,                             NULL,                    NULL,                    NULL           },    //Change Seq.List
  

/********************************************************************************************************************** VGAVisualQualityScreen ****************************************************************************/
   {238,  &CurrentPreset.WeldTimeMaxVQS,     sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSWeldTimeMax
   {239,  &CurrentPreset.WeldTimeMinVQS,     sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSWeldTimeMin
   {240,  &CurrentPreset.EnergyMaxVQS,       sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSEnergyMax
   {241,  &CurrentPreset.EnergyMinVQS,       sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSEnergyMin
   {242,  &CurrentPreset.PeakPowerMaxVQS,    sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSPeakPowerMax
   {243,  &CurrentPreset.PeakPowerMinVQS,    sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSPeakPowerMin
   {244,  &CurrentPreset.WeldColMaxVQS,      sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSWeldColMax
   {245,  &CurrentPreset.WeldColMinVQS,      sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSWeldColMin
   {246,  &CurrentPreset.TotalColMaxVQS,     sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSTotalColMax
   {247,  &CurrentPreset.TotalColMinVQS,     sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSTotalColMin
   {248,  &CurrentPreset.TotalAbsMaxVQS,     sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSTotalAbsMax
   {249,  &CurrentPreset.TotalAbsMinVQS,     sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSTotalAbsMin
   {250,  &CurrentPreset.WeldForceMaxVQS,    sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSWeldForceMax
   {251,  &CurrentPreset.WeldForceMinVQS,    sint32,  NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSWeldForceMin
   {252,  &CurrentPreset.TotalCycleTimeMaxVQS,sint32, NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSTotalCycleTimeMax
   {253,  &CurrentPreset.TotalCycleTimeMinVQS,sint32, NULL,             &CurrentPreset.VQSLimit,                 NULL,             VQSLimitsChanged      },    //VQSTotalCycleTimeMin

/********************************************************************************************************************** QVGAPrintingChoice *********************************************************************************/
   {254,  NULL,                              nothing, NULL,                             NULL,                     NULL,                   NULL           },    //QVGAPrintingChoice
   {255,  &CurrentPreset.GlobalPrintingFlag, uint16,  NULL,                             NULL,                     NULL,                   NULL           },    //GlobalPrinting
   {256,  &CurrentSetup.ExtGlobalPrintFlag,  uint16,  NULL,                             NULL,                     NULL,                   NULL           },    //ExtGlobalPrinting
   {257,  &CurrentPreset.AutoScaleFlag,      uint16,  NULL,                             NULL,                     NULL,                   NULL           },    //XAutoScale
   {258,  &CurrentPreset.XScaleTime,         sint32,  NULL,                             NULL,                     NULL,                   NULL           },    //PrinterScaling
   {259,  &RadioIndex,                       uint16,  NULL,                             NULL,                     GetPrinterChoice,  SetPrinterChoice    },    //ChoosePrinter
   {260,  &RadioIndex,                       uint16,  NULL,                             NULL,                     GetPageSize,       SetPageSize         },    //ChoosePageSize
   {261,  &CurrentSetup.WeldsPerPage,        sint32,  NULL,                             NULL,                     NULL,              ChangeWeldCountToOne},    //WeldsPerPageVar

   {262,  &CurrentPreset.SetupPresetValue,   sint32,  NULL,        &CurrentPreset.SetupPresetSFlag,              NULL,            InitSetupPresetValue   },    //PrintOnSampleSetup
   {263,  &CurrentPreset.SetupPresetAFlag,   boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmSetup
   {264,  &CurrentSetup.SPExtSampleValue,    sint32,  NULL,        &CurrentSetup.SPExtSampleFlag,                NULL,                    NULL           },    //ExtPrintOnSampleSetup
   {265,  &CurrentSetup.SPExtAlarmFlag,      boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmSetup

   {266,  &CurrentPreset.WeldHistoryValue,   sint32,  NULL,        &CurrentPreset.WeldHistorySFlag,              NULL,            InitWeldHistoryValue   },    //PrintOnSampleHistory
   {267,  &CurrentPreset.WeldHistoryAFlag,   boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmHistory
   {268,  &CurrentSetup.WHExtSampleValue,    sint32,  NULL,        &CurrentSetup.WHExtSampleFlag,                NULL,                    NULL           },    //ExtPrintOnSampleHistory
   {269,  &CurrentSetup.WHExtAlarmFlag,      boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmHistory

   {270,  &CurrentPreset.WeldSummaryValue,   sint32,  NULL,        &CurrentPreset.WeldSummarySFlag,              NULL,            InitWeldSummaryValue   },    //PrintOnSampleSummary
   {271,  &CurrentPreset.WeldSummaryAFlag,   boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmSummary
   {272,  &CurrentSetup.WSExtSampleValue,    sint32,  NULL,        &CurrentSetup.WSExtSampleFlag,                NULL,                    NULL           },    //ExtPrintOnSampleSummary
   {273,  &CurrentSetup.WSExtAlarmFlag,      boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmSummary

   {274,  &CurrentPreset.PowerGraphValue,    sint32,  NULL,        &CurrentPreset.PowerGraphSFlag,               NULL,            InitPowerGraphValue    },    //PrintOnSamplePower
   {275,  &CurrentPreset.PowerGraphAFlag,    boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmPower
   {276,  &CurrentSetup.PGExtSampleValue,    sint32,  NULL,        &CurrentSetup.PGExtSampleFlag,                NULL,                    NULL           },    //ExtPrintOnSamplePower
   {277,  &CurrentSetup.PGExtAlarmFlag,      boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmPower

   {278,  &CurrentPreset.AmplitudeGraphValue,sint32,  NULL,        &CurrentPreset.AmplitudeGraphSFlag,           NULL,            InitAmpGraphValue      },    //PrintOnSampleAmplitude
   {279,  &CurrentPreset.AmplitudeGraphAFlag,boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmAmplitude
   {280,  &CurrentSetup.AGExtSampleValue,    sint32,  NULL,        &CurrentSetup.AGExtSampleFlag,                NULL,                    NULL           },    //ExtPrintOnSampleAmplitude
   {281,  &CurrentSetup.AGExtAlarmFlag,      boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmAmplitude

   {282,  &CurrentPreset.FrequencyGraphValue,sint32,  NULL,        &CurrentPreset.FrequencyGraphSFlag,           NULL,            InitFreqGraphValue     },    //PrintOnSampleFreq
   {283,  &CurrentPreset.FrequencyGraphAFlag,boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmFreq
   {284,  &CurrentSetup.FreqGExtSampleValue, sint32,  NULL,        &CurrentSetup.FreqGExtSampleFlag,             NULL,                    NULL           },    //ExtPrintOnSampleFreq
   {285,  &CurrentSetup.FreqGExtAlarmFlag,   boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmFreq

   {286,  &CurrentPreset.ColDistanceGraphValue,sint32,NULL,        &CurrentPreset.ColDistanceGraphSFlag,         NULL,            InitColDistGraphValue  },    //PrintOnSampleDistance
   {287,  &CurrentPreset.ColDistanceGraphAFlag,boolean, NULL,                             NULL,                  NULL,                    NULL           },    //PrintOnAlarmDistance
   {288,  &CurrentSetup.CDGExtSampleValue,   sint32,  NULL,        &CurrentSetup.CDGExtSampleFlag,               NULL,                    NULL           },    //ExtPrintOnSampleDistance
   {289,  &CurrentSetup.CDGExtAlarmFlag,     boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmDistance

   {290,  &CurrentPreset.VelocityGraphValue, sint32,  NULL,        &CurrentPreset.VelocityGraphSFlag,            NULL,            InitVelGraphValue      },    //PrintOnSampleVelocity
   {291,  &CurrentPreset.VelocityGraphAFlag, boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmVelocity
   {292,  &CurrentSetup.VGExtSampleValue,    sint32,  NULL,        &CurrentSetup.VGExtSampleFlag,                NULL,                    NULL           },    //ExtPrintOnSampleVelocity
   {293,  &CurrentSetup.VGExtAlarmFlag,      boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmVelocity

   {294,  &CurrentPreset.ForceGraphValue,    sint32,  NULL,        &CurrentPreset.ForceGraphSFlag,               NULL,            InitForceGraphValue    },    //PrintOnSampleForce
   {295,  &CurrentPreset.ForceGraphAFlag,    boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmForce
   {296,  &CurrentSetup.FGExtSampleValue,    sint32,  NULL,        &CurrentSetup.FGExtSampleFlag,                NULL,                    NULL           },    //ExtPrintOnSampleForce
   {297,  &CurrentSetup.FGExtAlarmFlag,      boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmForce

   {298,  &CurrentPreset.SeqPresetValue,     sint32,  NULL,        &CurrentPreset.SeqPresetSFlag,                NULL,            InitSequenceValue      },    //PrintOnSampleSeq
   {299,  &CurrentPreset.SeqPresetAFlag,     boolean, NULL,                             NULL,                    NULL,                    NULL           },    //PrintOnAlarmSeq
   {300,  &CurrentSetup.SeqExtSampleValue,   sint32,  NULL,        &CurrentSetup.SeqExtSampleFlag,               NULL,                    NULL           },    //ExtPrintOnSampleSeq
   {301,  &CurrentSetup.SeqExtAlarmFlag,     boolean, NULL,                             NULL,                    NULL,                    NULL           },    //ExtPrintOnAlarmSeq

   {302,  &CurrentSetup.AutoRefresh,         boolean, NULL,                             NULL,                    NULL,           SetDisplayRefreshButton },    //ExtPrintOnAlarmSeq

/********************************************************************************************************************** VGABUCMenu *******************************************************************************************/
   {303,  &CurrentSetup.PSLifetime,          sint32,  NULL,                             NULL,                    NULL,             StorePSLifeTimeCount  },    //SetPSLife
   {304,  &CurrentSetup.Overload,            sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SetOverloads
   {305,  &CurrentSetup.GenAlarmCount,       sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SetGenAlarms
   {306,  &BUCMenuRAM.AmpDecayPercent,       sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //AmpDecaySettings
   {307,  &BUCFactoryDefaults,               sint32,  NULL,                             NULL,                    NULL,             VGATestCheckSum       },    //VGAFactoryDefaults
   {308,  &CurrentPreset.PMCTimeout,         sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //VGAPwrCurveTimeout
   {309,  &CurrentPreset.SetRTComp,          sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SetRTComp
   {310,  &RadioIndex,                       uint16,  NULL,                             NULL,                  GetRTRamp,              SetRTrRamp        },    //SetRTRamp
   {311,  &RadioIndex,                       uint16,  NULL,                             NULL,                  GetReturnRamp,          SetreturnRamp     },    //SetReturnRamp
   {312,  &RadioIndex,                       uint16,  NULL,                             NULL,                  GetStartRamp,           SetstartRamp      },    //SetStartRamp
   {313,  &CurrentSetup.IdleSpeed,           sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SetIdleSpeed
   {314,  &CurrentSetup.GainFactor,          sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SetGainFactor
   {315,  NULL,                              nothing, NULL,                             NULL,                    NULL,              UpdateCalibDefault   },    //QVGAUpdateCalDef
   {316,  &BUCMenuRAM.EnergyBrakingTime,     sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SetEnergyBrakingTime
   {317,  &BUCMenuRAM.EnergyBrakingAmp,      sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SetEnergyBrakingPercent

   {318,  &DUPS_CurrentParamSet.SeekAmplitude,sint32, NULL,                             NULL,                    NULL,             DUPS_QueuedDownloadPS },    //AmplitudeFn
   {319,  &DUPS_CurrentParamSet.SeekRampTime, sint32, NULL,                             NULL,                    NULL,             DUPS_QueuedDownloadPS },    //SeekRampTimeVar
   {320,  &DUPS_CurrentParamSet.SeekFreqLimitHigh,sint32,  NULL,                        NULL,                    NULL,             DUPS_QueuedDownloadPS },    //FreqHighVar
   {321,  &DUPS_CurrentParamSet.SeekFreqLimitLow, sint32,  NULL,                        NULL,                    NULL,             DUPS_QueuedDownloadPS },    //FreqLowVar
   {322,  &DUPS_CurrentParamSet.SeekPhaseLoop,sint32,  NULL,                            NULL,                    NULL,             DUPS_QueuedDownloadPS },    //PhsLoop
   {323,  &DUPS_CurrentParamSet.SeekPhaseLoopCF,sint32,  NULL,                          NULL,                    NULL,             DUPS_QueuedDownloadPS },    //SeekPhsLoopCF
   {324,  &DUPS_CurrentParamSet.SeekAmplitudeLoopC1, sint32,  NULL,                     NULL,                    NULL,             DUPS_QueuedDownloadPS },    //AmplLoopC1
   {325,  &DUPS_CurrentParamSet.SeekAmplitudeLoopC2,sint32,  NULL,                      NULL,                    NULL,             DUPS_QueuedDownloadPS },    //AmplLoopC2

   {326,  &DUPS_CurrentParamSet.WeldAmplitude,sint32, NULL,                             NULL,                    NULL,             DUPS_QueuedDownloadPS },    //WeldAmplitude
   {327,  &DUPS_CurrentParamSet.WeldRampTime, sint32, NULL,                             NULL,                    NULL,             DUPS_QueuedDownloadPS },    //RampTime
   {328,  &DUPS_CurrentParamSet.WeldPhaseLoop,sint32, NULL,                             NULL,                    NULL,             DUPS_QueuedDownloadPS },    //WeldPhaseLoop
   {329,  &DUPS_CurrentParamSet.WeldPhaseLoopCF, sint32,  NULL,                         NULL,                    NULL,             DUPS_QueuedDownloadPS },    //PhsLoopCF
   {330,  &DUPS_CurrentParamSet.WeldAmplitudeLoopC1,sint32,  NULL,                      NULL,                    NULL,             DUPS_QueuedDownloadPS },    //WeldAmpLoopC1
   {331,  &DUPS_CurrentParamSet.WeldAmplitudeLoopC2,sint32,  NULL,                      NULL,                    NULL,             DUPS_QueuedDownloadPS },    //WeldAmpLoopC2
   {332,  &DUPS_CurrentParamSet.WeldFreqLimitHigh, sint32,  NULL,                       NULL,                    NULL,             DUPS_QueuedDownloadPS },    //WeldHighVar
   {333,  &DUPS_CurrentParamSet.WeldFreqLimitLow,sint32,  NULL,                         NULL,                    NULL,             DUPS_QueuedDownloadPS },    //WeldLowVar
   {334,  &DUPS_CurrentParamSet.WeldPhaseLimit, sint32,  NULL,                          NULL,                    NULL,             DUPS_QueuedDownloadPS },    //PhsLimit
   {335,  &DUPS_CurrentParamSet.WeldPhaseLimitTime,sint32,  NULL,                       NULL,                    NULL,             DUPS_QueuedDownloadPS },    //PhaseLimits

   {336,  &HornScanInfo.MaximumAmplitude,    sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SAmplitude
   {337,  &HornScanInfo.MaximumCurrent,      sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //SCurrent
   {338,  &HornScanInfo.StartFreq,           sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //FreqStartVar
   {339,  &HornScanInfo.StopFreq,            sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //FreqEndVar
   {340,  &HornScanInfo.FreqStep,            sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //FreqStepVar
   {341,  &HornScanInfo.TimeDelay,           sint32,  NULL,                             NULL,                    NULL,                    NULL           },    //TimeDelayVar
   {342,  NULL,                              nothing, NULL,                             NULL,                    NULL,              ResetHornScanValue },    //VGAResetScanValues

   {343,  &AlarmPtrRam.SetupGroup1,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg1
   {344,  &AlarmPtrRam.SetupGroup2,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg2
   {345,  &AlarmPtrRam.SetupGroup3,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg3
   {346,  &AlarmPtrRam.SetupGroup4,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg4
   {347,  &AlarmPtrRam.SetupGroup5,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg5
   {348,  &AlarmPtrRam.SetupGroup6,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg6
   {349,  &AlarmPtrRam.SetupGroup7,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg7
   {350,  &AlarmPtrRam.SetupGroup8,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg8
   {351,  &AlarmPtrRam.SetupGroup9,          sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg9
   {352,  &AlarmPtrRam.SetupGroup10,         sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //Seg10
   {353,  &AlarmPtrRam.Overload,             sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //olg1
   {354,  &AlarmPtrRam.NoCycle,              sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //ncg1
   {355,  &AlarmPtrRam.EquipmentFailure,     sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //eqg1
   {356,  &AlarmPtrRam.CycleModified,        sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //cmg1
   {357,  &AlarmPtrRam.Reject,               sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //prg1
   {358,  &AlarmPtrRam.Suspect,              sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //psg1
   {359,  &AlarmPtrRam.Warning,              sint32,  NULL,                             NULL,                    NULL,                 CopyToBBR         },    //wag1

   {360,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset2Index,        SetDupsPreset2     },    //DupsPreset2
   {361,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset3Index,        SetDupsPreset3     },    //DupsPreset3
   {362,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset4Index,        SetDupsPreset4     },    //DupsPreset4
   {363,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset5Index,        SetDupsPreset5     },    //DupsPreset5
   {364,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset6Index,        SetDupsPreset6     },    //DupsPreset6
   {365,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset7Index,        SetDupsPreset7     },    //DupsPreset7
   {366,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset8Index,        SetDupsPreset8     },    //DupsPreset8
   {367,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset9Index,        SetDupsPreset9     },    //DupsPreset9
   {368,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset10Index,       SetDupsPreset10    },    //DupsPreset10
   {369,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset11Index,       SetDupsPreset10    },    //DupsPreset11
   {370,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset12Index,       SetDupsPreset12    },    //DupsPreset12
   {371,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset13Index,       SetDupsPreset13    },    //DupsPreset13
   {372,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset14Index,       SetDupsPreset14    },    //DupsPreset14
   {373,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset15Index,       SetDupsPreset15    },    //DupsPreset15
   {374,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset16Index,       SetDupsPreset16    },    //DupsPreset16
   {375,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset17Index,       SetDupsPreset17    },    //DupsPreset17
   {376,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset18Index,       SetDupsPreset18    },    //DupsPreset18
   {377,  &RadioIndex,                       uint16,  NULL,                             NULL,             SetDupsPreset19Index,       SetDupsPreset19    },    //DupsPreset19
   
/************************************************************************************************************* VGABransonDefaultMenu **********************************************************************************************/
   {378,  NULL,                              nothing, NULL,                             NULL,                    NULL,                OkToDefault     },    //QVGADefaultsActuator
   {379,  NULL,                              nothing, NULL,                             NULL,                    NULL,                OkToDefault     },    //QVGADefaultsBBR
   {380,  NULL,                              nothing, NULL,                             NULL,                    NULL,                OkToDefault     },    //QVGADefaultsPrinting
   {381,  NULL,                              nothing, NULL,                             NULL,                    NULL,                OkToDefault     },    //QVGADefaultsGlobal

/************************************************************************************************************* QVGADiagnosticMenu1  ***********************************************************************************************/
   {382,  &CurrentSetup.DigPotFlag,          uint16,  NULL,                             NULL,                    SetDiagFlag,          NULL                             },    //QVGADigitalTuneChoice
   {383,  NULL,                              nothing, NULL,                             NULL,                    DisableDiagnostics,   ColdStartEnable                  },    //VGAColdStartOk
   {384,  &DigPotValue,                      sint32,  NULL,                             NULL,                    NULL,                 VarDigPotStore                   },    //DigitalFrequency
   {385,  NULL,                              nothing, NULL,                             NULL,               DisableDiagnostics,        EnableActColdStart               }, //VGAActStartOk
   {386,  NULL,                              nothing, &BransonFunctionFlag,             NULL,                    NULL,                 DisableDiagnostics               },   //QVGABransonFuncSubmenu
   {387,  &DebugPtr,                         sint32,  &DebugPasswordFlag,               NULL,                    NULL,                 DebugReadMemory                  },   //Debug
   {388,  NULL,                              nothing, &SpecialMenuFlag,                 NULL,                    NULL,                 NULL                             },   //QVGASpecialsSubmenu
   {389,  NULL,                              nothing, &TestingMenuFlag,                 NULL,                    NULL,                 NULL                             },   //QVGATestingSubmenu
   {390,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 VGARecallMinimumPreset           },   //VGARecallMinMsg
   {391,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 VGARecallMaximumPreset           },   //VGARecallMaxMsg
   {392,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 VGARecallColdStartPreset         },   //VGARecallColdStartMsg
   {393,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 VGASaveMinimumPreset             },   //VGASaveMinMsg
   {394,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 VGASaveMaximumPreset             },   //VGASaveMaxMsg
   {395,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 VGASaveColdstartPreset           },   //VGASaveColdstartMsg
   {396,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 VGARestoreMinMaxPreset           },   //VGARestoreMinMaxMsg
   {397,  NULL,                              nothing, NULL,                             NULL,                    VGARestoreColdStart,  RestoreFactoryColdstart          },   //QVGARestoreColdstartText
   {398,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 EnableHornScanStart              },   //QVGAsubmenuHornscan
   {399,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 DUPS_StartHS                     },   //VGAHSStart
   {400,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 ProcessHSAbort1                  },   //VGAHSAbort

/******************************************************************************************************** Horn Down  *********************************************************************************************************/
   {401,  NULL,                              nothing, NULL,                             NULL,                DoHornDownFunc,           DoHornDownFunc                   },   //HornDown
   /* ** VGAHDStartMenuAEF ** */
   {402,  &KeepHornDown.bool,                boolean, NULL,                             NULL,                    NULL,                 ProcessHDButtonPress2            },   //HDTriggerToggle
   {403,  &CurrentSetup.HornDownSpd,         sint32,  NULL,                             NULL,                    NULL,                 NULL                             },   //HDDownSpeedSet
   {404,  &WorkingForceSet,                  sint32,  NULL,                             NULL,                    NULL,                 NULL                             },   //HDWorkingForce
   {405,  &RapidTraverseState,               uint16,  NULL,                             NULL,                    NULL,                 NULL                             },   //QVGAHDRapidTraverse
   {406,  &RTTransitionDist,                 sint32,  NULL,                             NULL,                    NULL,                 NULL                             },   //RTTransition
   /* ** VGAHDStartMenuAED ** */
   {407,  &CurrentPressure,                  sint32,  &HDShowPressure,                  NULL,                    NULL,                 NULL                             },   //HDSysPres
   {408,  NULL,                              nothing, &KeepHornDown.uint16.Hi,          NULL,                    NULL,                 ProcessHDButtonPress1            },   //VGARetractButton

/***************************************************************************************************** Bottom Menu Commands ***************************************************************************************************/
   {409,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 BottomMenuProcess           },   //QVGATheMainMenu
   {410,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 BottomMenuProcess           },   //WeldModeSelectMenu
   {411,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 BottomMenuProcess           },   //GraphMenu
   {412,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 BottomMenuProcess           },   //VGARunMenu

/***************************************************************************************************** cold start & testing submenu *******************************************************************************************/
   {413,  NULL,                              nothing, NULL,                             NULL,                    DoColdStart,          NULL                       },   //DoColdStart
   {414,  NULL,                              nothing, NULL,                             NULL,                    VGAActColdStart,      NULL                       },   //ActColdStart
   {415,  NULL,                              nothing, NULL,                             NULL,                    VGACreateColdStartPreset,EnableCreateStart       },   //QVGACreateColdstartText
   {416,  NULL,                              nothing, NULL,                             NULL,                    VGAOverwriteAllPreset,OverwritePresetCheck       },   //QVGAUniquePresetsText
   {417,  NULL,                              nothing, NULL,                             NULL,                    VGAOverwriteAllPreset,OverwritePresetCheck       },   //QVGASetupAlarmsText
   {418,  NULL,                              nothing, NULL,                             NULL,                    VGAOverwriteAllPreset,OverwritePresetCheck       },   //QVGAColdStartAllText
   {419,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 BankSwitchPresets          },   //QVGABankSwitchText
   {420,  NULL,                              nothing, NULL,                             NULL,                    NULL,                 CreateGraphData            },   //QVGACreateGraphDataText

   {421,  &CurrentPreset.TestAmp,            sint32,  NULL,                             NULL,                    NULL,                 UpdateTestAmp              },   //TestAmplitude
   {422,  NULL,                              nothing, NULL,                             NULL,                    VGAConfigureFromBUCMenu,  NULL					      },   //VGACheckSum
   {423,  NULL,                              nothing, NULL,                             NULL,                    VGADebugColdStart,		NULL                       },   //VGACheckSum(VGAFactoryDefaults)
   {424,  NULL,                              nothing, NULL,                             NULL,                    SetDigtalPot,         NULL                       },   //VGADigitalChoiceTestMenu

/******************************************************************************************************** Calibration Menu  *************************************************************************************************/
   {425,  NULL,                              nothing, NULL,                             NULL,                    NULL,   ResetSensorCalb           },   //VGAResetSensorOk
   {426,  NULL,                              nothing, NULL,                             NULL,                    NULL,   VGARequestSensorCal       },   //QVGAsubCalibSensor
   {427,  &UserPressure[0],                  sint32,  NULL,                             NULL,                    NULL,   NULL                      },   //GaugeReading
   {428,  NULL,                              nothing, NULL,                             NULL,                    NULL,   SBCReadA2D3               },   //QVGAsubContinue2
   {429,  NULL,                              nothing, NULL,                             NULL,                    NULL,   VGARequestActCal          },   //QVGAsubmenuCalActuator
   {430,  NULL,                              nothing, NULL,                             NULL,                    NULL,   SCInitialize              },   //QVGAsubmenuStartSw1
   {431,  NULL,                              nothing, NULL,                             NULL,                    NULL,   ManualSCInitialize        },   //QVGAsubmenuManual1
   {432,  NULL,                              nothing, NULL,                             NULL,                    NULL,   DisableCalActKey1         },   //QVGAsubContinueForce1 / QVGAsubContinue5A
   {433,  NULL,                              nothing, NULL,                             NULL,           VGARequestActCal,VGACloseCalibration       },   //QVGAsubCFM3
   {434,  &(SINT32)ErrorCode,                sint32,  &ErrorCodeFlag,                   NULL,                    NULL,   NULL                      },   //ErrorCodeInfo
   {435,  &UserPressure[1],                  sint32,  NULL,                             NULL,                    NULL,   NULL                      },   //GaugeReading1
   {436,  NULL,                              nothing, NULL,                             NULL,                    NULL,   SBCReadA2D4               },   //QVGAsubContinue4
   {437,  &UserPressure[2],                  sint32,  NULL,                             NULL,                    NULL,   BuildPressureTable        },   //GaugeReading3
   {438,  NULL,                              nothing, NULL,                             NULL,                    NULL,   SaveCalibPressure         },   //QVGAsubContinue5B
   {439,  NULL,                              nothing, NULL,                             NULL,                    NULL,   CalibFinalCleanup         },   //QVGAsubContinueFail13
   {440,  &ForceV[0],                        sint32,  NULL,                             NULL,                    NULL,   NULL                      },   //varLoadCellReading1 
   {441,  NULL,                              nothing, NULL,                             NULL,                    NULL,   SBCReadA2D1               },   //QVGAsubContinue8
   {442,  &ForceV[1],                        sint32,  NULL,                             NULL,                    NULL,   NULL                      },   //varLoadCellReading3 
   {443,  &ForceV[2],                        sint32,  NULL,                             NULL,                    NULL,   NULL                      },   //varLoadCellReading3AEF 
   {444,  NULL,                              nothing, NULL,                             NULL,                    NULL,   SBCReadA2DLC2             },   //QVGAsubBlank12
   {445,  NULL,                              nothing, NULL,                             NULL,                    NULL,   VGABuildForceTable        },   //QVGAsubContinue12
   {446,  &FailedByValue,                    str,     NULL,                             NULL,                    NULL,   NULL                      },   //GaugeReading3 
/******************************************************************************************************** Weld Result Screen ***********************************************************************************************/
   {447,  &CurrentSetup.ActivePreset,        uint16,  NULL,                             NULL,                    NULL,           NULL              },   //PresetNameText(Preset Number) 
   {448,  &CurrentPresetName,                arr,     NULL,                             NULL,            GetCurrentPresetNames,  NULL              },   //PresetNameText(Preset Name)
   {449,  &StrWeldStateLine,                 arr,     NULL,                             NULL,                    NULL,           NULL              },   //WeldStateText 
   {450,  &CurrentSetup.WeldParamOption[0],  uint16,  NULL,                             NULL,                    NULL,           NULL              },   //WeldParamName1 
   {451,  &CurrentSetup.WeldParamOption[1],  uint16,  NULL,                             NULL,                    NULL,           NULL              },   //WeldParamName2 
   {452,  &CurrentSetup.WeldParamOption[2],  uint16,  NULL,                             NULL,                    NULL,           NULL              },   //WeldParamName3 
   {453,  &CurrentSetup.WeldParamOption[3],  uint16,  NULL,                             NULL,                    NULL,           NULL              },   //WeldParamName4 
   {454,  &CurrentSetup.WeldParamOption[4],  uint16,  NULL,                             NULL,                    NULL,           NULL              },   //WeldParamName5 
   {455,  NULL,                              nothing, NULL,                             NULL,                    NULL,           NULL              },   //Param No. 
   {456,  NULL,                              nothing, NULL,                             NULL,                    NULL,       ProcessWindowSetup    },   //Window Setup 
   {457,  &DebugText1,                       str,     NULL,                             NULL,                    NULL,           NULL              },   //textDebugData1
   {458,  &DebugText2,                       str,     NULL,                             NULL,                    NULL,           NULL              },   //textDebugData2 
   {459,  &DebugText3,                       str,     NULL,                             NULL,                    NULL,           NULL              },   //textDebugData3 
   {460,  &DebugText4,                       str,     NULL,                             NULL,                    NULL,           NULL              },   //textDebugData4 
   {461,  &DebugBase,                        boolean, &HexEnable,                       NULL,                    NULL,  ChangeBaseAndWordLength    },   //toggleDebugBase
   {462,  &DebugBytes,                       boolean, NULL,                             NULL,                    NULL,  ChangeBaseAndWordLength    },   //toggleDebugBytes 

   {463,  &CurrentPreset.PMCHighLimit,       sint32,  NULL,                     &CurrentPreset.PMCPlusBandFlag,  NULL,           NULL              },   //VGAPwrUpperBand 
   {464,  &CurrentPreset.PMCLowLimit,        sint32,  NULL,                     &CurrentPreset.PMCMinusBandFlag, NULL,           NULL              },   //VGAPwrLowerBand 

   {465,  NULL,                              nothing, NULL,                             NULL,                    NULL,        ClearPMCData         },   //PMCDATACLEAR 
   {466,  NULL,                              nothing, NULL,                             NULL,                    NULL,        AddToPMCData         },   //ADDTOPMCDATA 
/************************************************************************************** Alarm menu system *******************************************************************************************/
   {467,  &ActualHoldTime,                   sint32,  NULL,                             NULL,                    NULL,           NULL              },   //TrigLostTimeHold 
   {468,  &WeldingResults.ActualWeldTime,    sint32,  NULL,                             NULL,                    NULL,           NULL              },   //CM4Actual 
   {469,  &WeldingResults.TotalEnergy,       sint32,  NULL,                             NULL,                    NULL,           NULL              },   //CM6Actual 
   {470,  &WeldingResults.ActualWeldCollapse,sint32,  NULL,                             NULL,                    NULL,           NULL              },   //CM8Actual 
   {471,  &ActualPeakPower,                  sint32,  NULL,                             NULL,                    NULL,           NULL              },   //CM10Actual / PeakPwrActual
   {472,  &TriggerLostTime,                  sint32,  NULL,                             NULL,                    NULL,           NULL              },   //TrigLostTime 
   {473,  &WeldingResults.ActualAmplitudeEnd,sint32,  NULL,                             NULL,                    NULL,           NULL              },   //CM16ActualAmpB 
   {474,  &WeldingResults.ActualAmplitudeStart,sint32,NULL,                             NULL,                    NULL,           NULL              },   //CM18ActualAmpA 
   {475,  &WeldForceEnd,                     sint32,  NULL,                             NULL,                    NULL,           NULL              },   //CM22ActualWeldForce 
   {476,  &WeldingResults.ActualWeldCollapse,sint32,  NULL,                             NULL,                    NULL,           NULL              },   //CM23Actual 
   {477,  &CurrentPreset.AmpTrigForceValue,  sint32,  &AmplitudeStepEnableFlag.uint16.Hi,&CurrentPreset.Amp2Flag,NULL,      SelectAmpTriggerForce  },   //AmpStepAtForce 
   {478,  &Inp.PresetCode,                   sint32,  NULL,                             NULL,                    NULL,           NULL              },   //ExtPresetRecalled 
   {479,  &CurrentPreset.WeldForce,          sint32,  &ForceFixedEnableFlag,            &CurrentPreset.Force2Flag,NULL,          NULL              },   //WeldForceSetupMenuInfo
   {480,  &CurrentPreset.ForceTrigAmpValue,  sint32,  &ForceStepEnableFlag.uint16.Hi,   &CurrentPreset.Force2Flag,NULL,     SelectForceTriggerAmp  },   //ForceStepAtAmp 
   {481,  &MaximumForce,                     sint32,  NULL,                             NULL,                    NULL,           NULL              },   //MaximumForceInfo 

   {482,  &FinalResults.ActualTotalAbs,      sint32,  NULL,                             NULL,                    NULL,           NULL              },   //AbsDistActual 
   {483,  &FinalResults.ActualWeldCollapse,  sint32,  NULL,                             NULL,                    NULL,           NULL              },   //WeldColDistActual 
   {484,  &TestTime,                         sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTestTime 
   {485,  &PowerTest,                        sint32,  NULL,                             NULL,                    NULL,           NULL              },   //TestPower 
   {486,  &FreqChg,                          sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTestFreqChg 
   {487,  &WeldOLStatus.ErrorCurrent,        sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTestDUPSCurrent 
   {488,  &WeldOLStatus.ErrorFrequency,      sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTestDUPSFreqAct 
   {489,  &WeldOLStatus.ErrorPSV,            sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTestDUPSPhaseAct 
   {490,  &PTSTimer,                         sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTimePTrg 
   {491,  &OverloadPower,                    sint32,  NULL,                             NULL,                    NULL,           NULL              },   //PTOverloadPeakPwr 
   {492,  &OverloadFreq,                     sint32,  NULL,                             NULL,                    NULL,           NULL              },   //PTOverloadFreq 
   {493,  &ActualSeekTime,                   sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTimeSeek 
   {494,  &FinalResults.FrequencyChange,     sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadFreqChg 
   {495,  &FinalResults.ActualWeldTime,      sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTime 
   {496,  &ActualAfterburstTime,             sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadTimeAB 
   {497,  &ABOverloadPower,                  sint32,  NULL,                             NULL,                    NULL,           NULL              },   //ABOverloadPeakPwr 
   {498,  &ABOLStatus.ErrorCurrent,          sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadABDUPSCurrent 
   {499,  &ABOLStatus.ErrorFrequency,        sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadABDUPSFreqAct 
   {500,  &ABOLStatus.ErrorPSV,              sint32,  NULL,                             NULL,                    NULL,           NULL              },   //OverloadABDUPSPhaseAct 
   {501,  &EBOverloadTimer,                  sint32,  NULL,                             NULL,                    NULL,           NULL              },   //EBOverloadTime 
   {502,  &EBOverloadPower,                  sint32,  NULL,                             NULL,                    NULL,           NULL              },   //EBOverloadPeakPwr 
   {503,  &EBOverloadFreq,                   sint32,  NULL,                             NULL,                    NULL,           NULL              },   //EBOverloadFreqChg 

   {504,  &FinalResults.TotalEnergy,         sint32,  NULL,                             NULL,                    NULL,           NULL              },   //PeakEnergyActual 
   {505,  &FinalResults.ActualTotalCollapse, sint32,  NULL,                             NULL,                    NULL,           NULL              },   //ColDistActual 
   {506,  &FinalResults.ActualTriggerDistance,sint32, NULL,                             NULL,                    NULL,           NULL              },   //ActualTrigDist 
   {507,  &ActualForceMax,                   sint32,  NULL,                             NULL,                    NULL,           NULL              },   //ActualWeldForce 
   {508,  &FinalResults.ActualWeldTime,      sint32,  NULL,                             NULL,                    NULL,           NULL              },   //ActualTime 
   {509,  &ActualSBLMinFreq,                 sint32,  NULL,                             NULL,                    NULL,           NULL              },   //MActualFreq 
   {510,  &ActualSBLMaxFreq,                 sint32,  NULL,                             NULL,                    NULL,           NULL              },   //PActualFreq 
   {511,  &ActualValuePMC1,                  sint32,  NULL,                             NULL,                    NULL,           NULL              },   //PPmcActual 
   {512,  &ActualValuePMC2,                  sint32,  NULL,                             NULL,                    NULL,           NULL              },   //MPmcActual 
   {513,  &CurrentPreset.PreTrigFlag,        uint16,  NULL,                             NULL,                    NULL,           NULL              },   //AlarmPretriggerChoice
   {514,  &CurrentSetup.NoOfCycles,          sint32,  NULL,                             NULL,                    NULL,           NULL              },   //Print Weld History
   {515,  NULL,                              nothing, NULL,                             NULL,          CheckforDisplayLock,      NULL              },   //DisplayLock Chk on Exit 
   {516,  NULL,                              uint16,  &DUPS_Info.DUPSFlag,              NULL,                    NULL,           NULL              },   //Digital UPS
   {517,  &SBCVersionLabel,                  arr,     NULL,                             NULL,                    NULL,           NULL              },    //SBC Version
   {518,  &SWVersionLabel,                   arr,     NULL,                             NULL,                    NULL,           NULL              },    //332 SW Version
   {519,  &MenuNxtPointer,                   uint8,   NULL,                             NULL,                    NULL,           NULL              },   //Next menu in calibration
   {520,  &CurrentSetup.AmpMicronsValue,     sint32,  NULL,     &CurrentSetup.AmpMicronsFlag,                    NULL,           NULL              },
   {521,  &CurrentSetup.AmpMicronsFlag,      uint16,  NULL,     						NULL,                    NULL, VGARequestMicronUpdateAll   },
   {522,  &CurrentSetup.AmpMicronsValue,     sint32,  NULL,     						NULL,                    NULL, VGARequestMicronUpdateAll   },
   {523,  &CurrentSetup.PeakPowerWattsFlag,  uint16,  NULL,     						NULL,                    NULL,           NULL              },
   {524,  NULL,                              nothing, NULL,                             NULL, 					 NULL, VGARequestMicronCalEnabled  },
   {525,  NULL,                              nothing, NULL,                             NULL, 					 NULL, VGARequestMicronCalDisabled },
   {526,  &VGA_ScreenMicronCalAmp,           sint32,  NULL,                             NULL,                    NULL,           NULL              },
   {527,  &CurrentPreset.AmpAMicron,         sint32,  &CurrentSetup.AmpMicronsFlag,     &CurrentPreset.Amp2Flag, NULL, VGARequestMicronUpdate      },
   {528,  &CurrentPreset.AmpAMicron,         sint32,  &AmplitudeStepMicronsEnableFlag.uint16.Hi,NULL,            NULL, VGARequestMicronUpdate      },
   {529,  &CurrentPreset.AmpBMicron,         sint32,  &AmplitudeStepMicronsEnableFlag.uint16.Hi,NULL,            NULL, VGARequestMicronUpdate      },
};


const MINMAXMAP MinMap[] = {
/*-----------------------------------------------------------------------------------------------------------*/
/*  ID   Minimum Limit Pointer               Maximum Limit Pointer                          comment          */
/*-----------------------------------------------------------------------------------------------------------*/
   {3,   &WelderAddrMinValue,                &WelderAddrMaxValue                    },    //WelderAddr
   {32,  &MinLimit.WeldSummaryValue,         &MaxLimit.WeldSummaryValue             },    //USBWeldDataSample
   {34,  &MinLimit.PowerGraphValue,          &MaxLimit.PowerGraphValue              },    //USBPowerSample
   {36,  &MinLimit.ColDistanceGraphValue,    &MaxLimit.ColDistanceGraphValue        },    //USBDistanceSample
   {38,  &MinLimit.VelocityGraphValue,       &MaxLimit.VelocityGraphValue           },    //USBVelocitySample
   {40,  &MinLimit.ForceGraphValue,          &MaxLimit.ForceGraphValue              },    //USBForceSample
   {42,  &MinLimit.AmplitudeGraphValue,      &MaxLimit.AmplitudeGraphValue          },    //USBAmplitudeSample
   {44,  &MinLimit.FrequencyGraphValue,      &MaxLimit.FrequencyGraphValue          },    //USBFreqSample
   {52,  &MinPSWatt,                         &MaxPSWatt                             },    //SetPSWatts
   {58,  &MinLimitVelocityPC,                &MaxLimitVelocityPC                    },    //SetVelocityPC
   {59,  &MinLimitForcePC,                   &CurrentSetup.MinTrigForce             },    //SetForcePC
   {60,  &MinLimitMinTrigForce,              &MaxLimitMinTrigForce                  },    //SetMinTrigger
   {98,  &MinSVDelay,                        &MaxSVDelay                            },    //SVDelay
   {102, &MinLimit.WeldTime,                 &MaxLimit.WeldTime                     },    //VGAWeldTimeTime
   {103, &MinLimit.HoldTime,                 &MaxLimit.HoldTime                     },    //VGAHoldTime1
   {104, &CurrentSetup.MinTrigForce,         &MaxLimit.TriggerForce                 },    //VGATriggerForce

   {107, &MinLimit.Amp1,                     &MaxLimit.Amp1                         },    //AmplitudeA
   {108, &MinLimit.Amp2,                     &MaxLimit.Amp2                         },    //AmplitudeB
   {109, &MinLimit.AmpTrigTimeValue,         &MaxLimit.AmpTrigTimeValue             },    //AmpStepAtTime
   {110, &MinLimit.AmpTrigEnerValue,         &MaxLimit.AmpTrigEnerValue             },    //AmpStepAtEner
   {111, &MinLimit.AmpTrigPowerValue,        &MaxLimit.AmpTrigPowerValue            },    //AmpStepAtPower
   {112, &MinLimit.AmpTrigColValue,          &MaxLimit.AmpTrigColValue              },    //AmpStepAtDist
   {114, &MinLimit.Amp1,                     &MaxLimit.Amp1                         },    //VGAAmplitude1
   {115, &MinLimit.HoldForce,                &MaxLimit.HoldForce                    },    //VGAHoldForce
   
   {116, &MinLimit.WeldEnergy,               &MaxLimit.WeldEnergy                   },    //VGAWeldEnergyEnergy
   {117, &MinLimit.PeakPwr,                  &MaxLimit.PeakPwr                      },    //VGAPeakPowerPP
   {118, &MinLimit.ColDist,                  &MaxLimit.ColDist                      },    //VGACollapseColl
   {119, &MinLimit.AbsDist,                  &MaxLimit.AbsDist                      },    //VGAAbsoluteAbs
   {120, &MinLimit.ScrubTime,                &MaxLimit.ScrubTime                    },    //VGAScrubTimeGndDet
   {121, &MinLimit.AmpScrubTime,             &MaxLimit.AmpScrubTime                 },    //AmpGroundDetect
   {123, &MinLimit.AbDelay,                  &MaxLimit.AbDelay                      },    //ABDelayTime
   {124, &MinLimit.AbTime,                   &MaxLimit.AbTime                       },    //ABTimeTime
   {125, &MinLimit.AbAmp,                    &MaxLimit.AbAmp                        },    //ABAmplitude

   {127, &MinLimit.PreTrigDist,              &MaxLimit.PreTrigDist                  },    //varPretrigDist
   {128, &MinLimit.PreTrigDelay,             &MaxLimit.PreTrigDelay                 },    //varPretrigTime
   {129, &MinLimit.PreTrigAmp,               &MaxLimit.PreTrigAmp                   },    //varPretrigAmplitude
/******************************** VGARejectLimitsChoice *******************************************************/
   {133, &MinLimit.TimePLR,                  &MaxLimit.TimePLR                      },    //PTimeREnergy
   {134, &MinLimit.TimeMLR,                  &MaxLimit.TimeMLR                      },    //MTimeREnergy
   {135, &MinLimit.EnergyPLR,                &MaxLimit.EnergyPLR                    },    //PEnergyRTime
   {136, &MinLimit.EnergyMLR,                &MaxLimit.EnergyMLR                    },    //MEnergyRTime
   {137, &MinLimit.PowerPLR,                 &MaxLimit.PowerPLR                     },    //PPkPowerRLimit
   {138, &MinLimit.PowerMLR,                 &MaxLimit.PowerMLR                     },    //MPkPowerRLimit
   {139, &MinLimit.ColPLR,                   &MaxLimit.ColPLR                       },    //PColDistRLimit
   {140, &MinLimit.ColMLR,                   &MaxLimit.ColMLR                       },    //MColDistRLimit
   {141, &MinLimit.AbsPLR,                   &MaxLimit.AbsPLR                       },    //PAbsDistRLimit
   {142, &MinLimit.AbsMLR,                   &MaxLimit.AbsMLR                       },    //MAbsDistRLimit
   {143, &MinLimit.TrsDistPLR,               &MaxLimit.TrsDistPLR                   },    //PTrigDistRLimit
   {144, &MinLimit.TrsDistMLR,               &MaxLimit.TrsDistMLR                   },    //MTrigDistRLimit
   {145, &MinLimit.WeldForcePLR,             &MaxLimit.WeldForcePLR                 },    //PMaxForceRLimit
   {146, &MinLimit.WeldForceMLR,             &MaxLimit.WeldForceMLR                 },    //MMaxForceRLimit
   {147, &CurrentPreset.SBLMinFreqLim,       &CurrentPreset.SBLMaxFreqLim           },    //PSBLFreqLimit
   {148, &CurrentPreset.SBLMinFreqLim,       &CurrentPreset.SBLMaxFreqLim           },    //MSBLFreqLimit

/************************************* VGASuspectLimitsChoice *************************************************/
   {151, &MinLimit.TimePLS,                  &MaxLimit.TimePLS                      },    //PTimeSEnergy
   {152, &MinLimit.TimeMLS,                  &MaxLimit.TimeMLS                      },    //MTimeSEnergy
   {153, &MinLimit.EnergyPLS,                &MaxLimit.EnergyPLS                    },    //PEnergySTime
   {154, &MinLimit.EnergyMLS,                &MaxLimit.EnergyMLS                    },    //MEnergySTime
   {155, &MinLimit.PowerPLS,                 &MaxLimit.PowerPLS                     },    //PPkPowerSLimit
   {156, &MinLimit.PowerMLS,                 &MaxLimit.PowerMLS                     },    //MPkPowerSLimit
   {157, &MinLimit.ColPLS,                   &MaxLimit.ColPLS                       },    //PColDistSLimit
   {158, &MinLimit.ColMLS,                   &MaxLimit.ColMLS                       },    //MColDistSLimit
   {159, &MinLimit.AbsPLS,                   &MaxLimit.AbsPLS                       },    //PAbsDistSLimit
   {160, &MinLimit.AbsMLS,                   &MaxLimit.AbsMLS                       },    //MAbsDistSLimit
   {161, &MinLimit.TrsDistPLS,               &MaxLimit.TrsDistPLS                   },    //PTrigDistSLimit
   {162, &MinLimit.TrsDistMLS,               &MaxLimit.TrsDistMLS                   },    //MTrigDistSLimit
   {163, &MinLimit.WeldForcePLS,             &MaxLimit.WeldForcePLS                 },    //PMaxForceSLimit
   {164, &MinLimit.WeldForceMLS,             &MaxLimit.WeldForceMLS                 },    //MMaxForceSLimit

/************************************* VGAForceChoiceStep / Fixed *********************************************/
   {166, &MinLimit.WeldForce,                &MaxLimit.WeldForce                    },    //WeldForceA 
   {167, &MinLimit.Force2,                   &MaxLimit.Force2                       },    //WeldForceB
   {168, &MinLimit.ForceTrigTimeValue,       &MaxLimit.ForceTrigTimeValue           },    //ForceStepAtTime
   {169, &MinLimit.ForceTrigEnerValue,       &MaxLimit.ForceTrigEnerValue           },    //ForceStepAtEner
   {170, &MinLimit.ForceTrigPowerValue,      &MaxLimit.ForceTrigPowerValue          },    //ForceStepAtPower
   {171, &MinLimit.ForceTrigColValue,        &MaxLimit.ForceTrigColValue            },    //ForceStepAtCol

/************************************* EnergyBrakingChoice  ***************************************************/
   {174, &MinLimit.EBTime,                   &MaxLimit.EBTime                       },    //EBTime
   {175, &MinLimit.WeldForce,                &MaxLimit.WeldForce                    },    //VGAWeldForceSetupMenu
/************************************ VGAFreqOffsetChoice  *****************************************************/
   {179, &MinLimit.FreqOffset,               &MaxLimit.FreqOffset                   },    //FreqOffset

/************************************ VGAActClearOutputChoice  *************************************************/
   {181, &MinLimit.ActClrDistance,           &MaxLimit.ActClrDistance               },    //Distance

/****************************** VGAControlLimitsChoice1 /Choice2 ***********************************************/
   {184, &MinLimit.EnergyPL,                 &MaxLimit.EnergyPL                     },    //MaxEnergyComp
   {185, &MinLimit.EnergyML,                 &MaxLimit.EnergyML                     },    //MinEnergyComp
   {186, &MinLimit.PeakPwrCutoff,            &MaxLimit.PeakPwrCutoff                },    //PeakPowerCutoff
   {187, &MinLimit.ABSCutoffDist,            &MaxLimit.ABSCutoffDist                },    //ABSCutoff
   {188, &MinLimit.ColCutoffDist,            &MaxLimit.ColCutoffDist                },    //CollapseCutoff

/********************************** VGACycleAbortsChoice1 /Choice2 **********************************************/
   {192, &MinLimit.MissingPartMax,           &MaxLimit.MissingPartMax               },    //MissingPartMaximum
   {193, &MinLimit.MissingPartMin,           &MaxLimit.MissingPartMin               },    //MissingPartMinimum
   {195, &MinLimit.RTDist,                   &MaxLimit.RTDist                       },    //StepAtRTDist
   {196, &MinLimit.DownSpdStart,             &MaxLimit.DownSpdStart                 },    //VGADownSpeed

/********************************************* DigitalUPS ********************************************************/
   {198, &DUPS_MinParamSet.WeldRampTime,     &DUPS_MaxParamSet.WeldRampTime         },    //RTime
   {199, &DUPS_MinParamSet.SeekTime,         &DUPS_MaxParamSet.SeekTime             },    //STime
  
/***************************************** VGAForceRampsMenu *****************************************************/
   {206, &MinLimit.MaxTimeout,               &MaxLimit.MaxTimeout                   },    //VGAMaxTimeout

/*************************************** VGAVisualQualityScreen **************************************************/
   {238, &MinLimit.WeldTimeMaxVQS,           &MaxLimit.WeldTimeMaxVQS               },    //VQSWeldTimeMax
   {239, &MinLimit.WeldTimeMinVQS,           &MaxLimit.WeldTimeMinVQS               },    //VQSWeldTimeMin
   {240, &MinLimit.EnergyMaxVQS,             &MaxLimit.EnergyMaxVQS                 },    //VQSEnergyMax
   {241, &MinLimit.EnergyMinVQS,             &MaxLimit.EnergyMinVQS                 },    //VQSEnergyMin
   {242, &MinLimit.PeakPowerMaxVQS,          &MaxLimit.PeakPowerMaxVQS              },    //VQSPeakPowerMax
   {243, &MinLimit.PeakPowerMinVQS,          &MaxLimit.PeakPowerMinVQS              },    //VQSPeakPowerMin
   {244, &MinLimit.WeldColMaxVQS,            &MaxLimit.WeldColMaxVQS                },    //VQSWeldColMax
   {245, &MinLimit.WeldColMinVQS,            &MaxLimit.WeldColMinVQS                },    //VQSWeldColMin
   {246, &MinLimit.TotalColMaxVQS,           &MaxLimit.TotalColMaxVQS               },    //VQSTotalColMax
   {247, &MinLimit.TotalColMinVQS,           &MaxLimit.TotalColMinVQS               },    //VQSTotalColMin
   {248, &MinLimit.TotalAbsMaxVQS,           &MaxLimit.TotalAbsMaxVQS               },    //VQSTotalAbsMax
   {249, &MinLimit.TotalAbsMinVQS,           &MaxLimit.TotalAbsMinVQS               },    //VQSTotalAbsMin
   {250, &MinLimit.WeldForceMaxVQS,          &MaxLimit.WeldForceMaxVQS              },    //VQSWeldForceMax
   {251, &MinLimit.WeldForceMinVQS,          &MaxLimit.WeldForceMinVQS              },    //VQSWeldForceMin
   {252, &MinLimit.TotalCycleTimeMaxVQS,     &MaxLimit.TotalCycleTimeMaxVQS         },    //VQSTotalCycleTimeMax
   {253, &MinLimit.TotalCycleTimeMinVQS,     &MaxLimit.TotalCycleTimeMinVQS         },    //VQSTotalCycleTimeMin
   
/************************************** QVGAPrintingChoice ********************************************************/
   {258, &MinLimit.XScaleTime,               &MaxLimit.XScaleTime                   },    //PrinterScaling
   {261, &MinWeldsPerPage,                   &MaxWeldsPerPage                       },    //WeldsPerPageVar
   {262, &MinLimit.SetupPresetValue,         &MaxLimit.SetupPresetValue             },    //PrintOnSampleSetup
   {264, &MinLimit.SetupPresetValue,         &MaxLimit.SetupPresetValue             },    //ExtPrintOnSampleSetup
   {266, &MinLimit.WeldHistoryValue,         &MaxLimit.WeldHistoryValue             },    //PrintOnSampleHistory
   {268, &MinLimit.WeldHistoryValue,         &MaxLimit.WeldHistoryValue             },    //ExtPrintOnSampleHistory
   {270, &MinLimit.WeldSummaryValue,         &MaxLimit.WeldSummaryValue             },    //PrintOnSampleSummary
   {272, &MinLimit.WeldSummaryValue,         &MaxLimit.WeldSummaryValue             },    //ExtPrintOnSampleSummary
   {274, &MinLimit.PowerGraphValue,          &MaxLimit.PowerGraphValue              },    //PrintOnSamplePower
   {276, &MinLimit.PowerGraphValue,          &MaxLimit.PowerGraphValue              },    //ExtPrintOnSamplePower
   {278, &MinLimit.AmplitudeGraphValue,      &MaxLimit.AmplitudeGraphValue          },    //PrintOnSampleAmplitude
   {280, &MinLimit.AmplitudeGraphValue,      &MaxLimit.AmplitudeGraphValue          },    //ExtPrintOnSampleAmplitude
   {282, &MinLimit.FrequencyGraphValue,      &MaxLimit.FrequencyGraphValue          },    //PrintOnSampleFreq
   {284, &MinLimit.FrequencyGraphValue,      &MaxLimit.FrequencyGraphValue          },    //ExtPrintOnSampleFreq
   {286, &MinLimit.ColDistanceGraphValue,    &MaxLimit.ColDistanceGraphValue        },    //PrintOnSampleDistance
   {288, &MinLimit.ColDistanceGraphValue,    &MaxLimit.ColDistanceGraphValue        },    //ExtPrintOnSampleDistance
   {290, &MinLimit.VelocityGraphValue,       &MaxLimit.VelocityGraphValue           },    //PrintOnSampleVelocity
   {292, &MinLimit.VelocityGraphValue,       &MaxLimit.VelocityGraphValue           },    //ExtPrintOnSampleVelocity
   {294, &MinLimit.ForceGraphValue,          &MaxLimit.ForceGraphValue              },    //PrintOnSampleForce
   {296, &MinLimit.ForceGraphValue,          &MaxLimit.ForceGraphValue              },    //ExtPrintOnSampleForce
   {298, &MinLimit.SeqPresetValue,           &MaxLimit.SeqPresetValue               },    //PrintOnSampleSeq
   {300, &MinLimit.SeqPresetValue,           &MaxLimit.SeqPresetValue               },    //ExtPrintOnSampleSeq
   {303, &MinLimitMin,                       &MaxLimitMax                           },    //SetPSLife
   {304, &MinLimitMin,                       &MaxLimitMax                           },    //SetOverloads
   {305, &MinLimitMin,                       &MaxLimitMax                           },    //SetGenAlarms
   {306, &AmpDecayPercentMin,                &AmpDecayPercentMax                    },    //AmpDecaySettings
   {307, &MinBUCFactoryDefaults,             &MaxBUCFactoryDefaults                 },    //VGAFactoryDefaults
   {308, &MinLimit.PMCTimeout,               &MaxLimit.PMCTimeout                   },    //VGAPwrCurveTimeout
   {309, &MinLimit.SetRTComp,                &MaxLimit.SetRTComp                    },    //SetRTComp 
   {313, &MinLimitIdleSpeed,                 &MaxLimitIdleSpeed                     },    //SetIdleSpeed
   {314, &MinLimitGainFactor,                &MaxLimitGainFactor                    },    //SetGainFactor
   {316, &EnergyBrakeTimeMin,                &EnergyBrakeTimeMax                    },    //SetEnergyBrakingTime
   {317, &EnergyBrakePercentMin,             &EnergyBrakePercentMax                 },    //SetEnergyBrakingPercent

   {318, &DUPS_MinParamSet.SeekAmplitude,    &DUPS_MaxParamSet.SeekAmplitude        },    //AmplitudeFn
   {319, &DUPS_MinParamSet.SeekRampTime,     &DUPS_MaxParamSet.SeekRampTime         },    //SeekRampTimeVar 
   {320, &DUPS_MinParamSet.SeekFreqLimitHigh,&DUPS_MaxParamSet.SeekFreqLimitHigh    },    //FreqHighVar
   {321, &DUPS_MinParamSet.SeekFreqLimitLow, &DUPS_MaxParamSet.SeekFreqLimitLow     },    //FreqLowVar
   {322, &DUPS_MinParamSet.SeekPhaseLoop,    &DUPS_MaxParamSet.SeekPhaseLoop        },    //PhsLoop
   {323, &DUPS_MinParamSet.SeekPhaseLoopCF,  &DUPS_MaxParamSet.SeekPhaseLoopCF      },    //SeekPhsLoopCF
   {324, &DUPS_MinParamSet.SeekAmplitudeLoopC1,&DUPS_MaxParamSet.SeekAmplitudeLoopC1},    //AmplLoopC1
   {325, &DUPS_MinParamSet.SeekAmplitudeLoopC2,&DUPS_MaxParamSet.SeekAmplitudeLoopC2},    //AmplLoopC2

   {326, &DUPS_MinParamSet.WeldAmplitude,    &DUPS_MaxParamSet.WeldAmplitude        },    //WeldAmplitude
   {327, &DUPS_MinParamSet.WeldRampTime,     &DUPS_MaxParamSet.WeldRampTime         },    //RampTime
   {328, &DUPS_MinParamSet.WeldPhaseLoop,    &DUPS_MaxParamSet.WeldPhaseLoop        },    //WeldPhaseLoop
   {329, &DUPS_MinParamSet.WeldPhaseLoopCF,  &DUPS_MaxParamSet.WeldPhaseLoopCF      },    //PhsLoopCF 
   {330, &DUPS_MinParamSet.WeldAmplitudeLoopC1,&DUPS_MaxParamSet.WeldAmplitudeLoopC1},    //WeldAmpLoopC1
   {331, &DUPS_MinParamSet.WeldAmplitudeLoopC2,&DUPS_MaxParamSet.WeldAmplitudeLoopC2},    //WeldAmpLoopC2
   {332, &DUPS_MinParamSet.WeldFreqLimitHigh, &DUPS_MaxParamSet.WeldFreqLimitHigh   },    //WeldHighVar
   {333, &DUPS_MinParamSet.WeldFreqLimitLow,  &DUPS_MaxParamSet.WeldFreqLimitLow    },    //WeldLowVar
   {334, &DUPS_MinParamSet.WeldPhaseLimit,    &DUPS_MaxParamSet.WeldPhaseLimit      },    //PhsLimit
   {335, &DUPS_MinParamSet.WeldPhaseLimitTime,&DUPS_MaxParamSet.WeldPhaseLimitTime  },    //PhaseLimits

   {336, &HS_MinScanInfo.MaximumAmplitude,   &HS_MaxScanInfo.MaximumAmplitude       },    //SAmplitude
   {337, &HS_MinScanInfo.MaximumCurrent,     &HS_MaxScanInfo.MaximumCurrent         },    //SCurrent
   {338, &HS_MinScanInfo.StartFreq,          &HS_MaxScanInfo.StartFreq              },    //FreqStartVar
   {339, &HS_MinScanInfo.StopFreq,           &HS_MaxScanInfo.StopFreq               },    //FreqEndVar 
   {340, &HS_MinScanInfo.FreqStep,           &HS_MaxScanInfo.FreqStep               },    //FreqStepVar
   {341, &HS_MinScanInfo.TimeDelay,          &HS_MaxScanInfo.TimeDelay              },    //TimeDelayVar

   {343, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg1
   {344, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg2
   {345, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg3
   {346, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg4
   {347, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg5
   {348, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg6
   {349, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg7
   {350, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg8
   {351, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg9
   {352, &AlarmPtrMin,                       &AlarmPtrMax                           },    //Seg10
   {353, &AlarmPtrMin,                       &AlarmPtrMax                           },    //olg1
   {354, &AlarmPtrMin,                       &AlarmPtrMax                           },    //ncg1 
   {355, &AlarmPtrMin,                       &AlarmPtrMax                           },    //eqg1
   {356, &AlarmPtrMin,                       &AlarmPtrMax                           },    //cmg1
   {357, &AlarmPtrMin,                       &AlarmPtrMax                           },    //prg1
   {358, &AlarmPtrMin,                       &AlarmPtrMax                           },    //psg1
   {359, &AlarmPtrMin,                       &AlarmPtrMax                           },    //wag1

/************************************** QVGADiagnosticMenu1  ************************************************/
   {384, &MinDigPotValue,                    &MaxDigPotValue                        },    //DigitalFrequency
   {387, &DebugLowValue,                     &DebugHighValue                        },    //Debug
/********************************************* Horn Down  ***************************************************/
   {403, &MinLimit.DownSpdStart,             &MaxLimit.DownSpdStart                 },    //HDDownSpeedSet
   {404, &MinLimit.WeldForce,                &MaxLimit.WeldForce                    },    //HDWorkingForce
   {406, &MinLimit.RTDist,                   &MaxLimit.RTDist                       },    //RTTransition
   {421, &MinLimit.TestAmp,                  &MaxLimit.TestAmp                      },    //TestAmplitude
   {427, &ForceGaugeReadingMin,              &ForceGaugeReadingMax                  },    //GaugeReading
   {434, &(SINT32)ErrorCode,				      &(SINT32)ErrorCode						   },    //ErrorCodeInfo
   {435, &ForceGaugeReadingMin,				   &ForceGaugeReadingMax					   },    //GaugeReading1
   {437, &ForceGaugeReadingMin,				   &ForceGaugeReadingMax					   },    //GaugeReading3
   {440, &LoadCellReadingMin,				      &LoadCellReadingMax					      },    //varLoadCellReading1
   {442, &LoadCellReadingMin,				      &LoadCellReadingMax					      },    //varLoadCellReading3
   {443, &LoadCellReadingMin,				      &LoadCellReadingMax					      },    //varLoadCellReading3AEF
   {463, &MinLimit.PMCHighLimit,				   &MaxLimit.PMCHighLimit					   },    //VGAPwrUpperBand
   {464, &MinLimit.PMCLowLimit,				   &MaxLimit.PMCLowLimit					   },    //VGAPwrLowerBand
   {467, &ActualHoldTime,				         &ActualHoldTime					         },    //TrigLostTimeHold
   {468, &WeldingResults.ActualWeldTime,		&WeldingResults.ActualWeldTime			},    //CM4Actual
   {469, &WeldingResults.TotalEnergy,			&WeldingResults.TotalEnergy				},    //CM6Actual
   {470, &WeldingResults.ActualWeldCollapse,	&WeldingResults.ActualWeldCollapse		},    //CM8Actual
   {471, &ActualPeakPower,				         &ActualPeakPower					         },    //CM10Actual
   {472, &TriggerLostTime,				         &TriggerLostTime					         },    //TrigLostTime
   {473, &WeldingResults.ActualAmplitudeEnd,	&WeldingResults.ActualAmplitudeEnd		},    //CM16ActualAmpB
   {474, &WeldingResults.ActualAmplitudeStart,&WeldingResults.ActualAmplitudeStart	},    //CM18ActualAmpA
   {475, &WeldForceEnd,				            &WeldForceEnd					            },    //CM22ActualWeldForce
   {476, &WeldingResults.ActualWeldCollapse,	&WeldingResults.ActualWeldCollapse		},    //CM23Actual
   {477, &MinLimit.AmpTrigForceValue,		   &MaxLimit.AmpTrigForceValue			   },    //AmpStepAtForce
   {478, &Inp.PresetCode,			            &Inp.PresetCode				            },    //ExtPresetRecalled
   {479, &MinLimit.WeldForce,	               &MaxLimit.WeldForce		               },    //WeldForceSetupMenuInfo
   {480, &MinLimit.ForceTrigAmpValue,			&MaxLimit.ForceTrigAmpValue				},    //ForceStepAtAmp
   {481, &MaximumForce,				            &MaximumForce					            },    //MaximumForceInfo

   {482, &FinalResults.ActualTotalAbs,	      &FinalResults.ActualTotalAbs		      },    //AbsDistActual
   {483, &FinalResults.ActualWeldCollapse,	&FinalResults.ActualWeldCollapse			},    //WeldColDistActual
   {484, &TestTime,	                        &TestTime		                        },    //OverloadTestTime
   {485, &PowerTest,	                        &PowerTest			                     },    //TestPower
   {486, &FreqChg,	                        &FreqChg			                        },    //OverloadTestFreqChg
   {487, &WeldOLStatus.ErrorCurrent,	      &WeldOLStatus.ErrorCurrent			      },    //OverloadTestDUPSCurrent
   {488, &WeldOLStatus.ErrorFrequency,	      &WeldOLStatus.ErrorFrequency			   },    //OverloadTestDUPSFreqAct
   {489, &WeldOLStatus.ErrorPSV,	            &WeldOLStatus.ErrorPSV			         },    //OverloadTestDUPSPhaseAct
   {490, &PTSTimer,			                  &PTSTimer				                  },    //OverloadTimePTrg
   {491, &OverloadPower,				         &OverloadPower					            },    //PTOverloadPeakPwr
   {492, &OverloadFreq,				            &OverloadFreq					            },    //PTOverloadFreq
   {493, &ActualSeekTime,			            &ActualSeekTime					         },    //OverloadTimeSeek
   {494, &FinalResults.FrequencyChange,		&FinalResults.FrequencyChange				},    //OverloadFreqChg
   {495, &FinalResults.ActualWeldTime,			&FinalResults.ActualWeldTime				},    //OverloadTime
   {496, &ActualAfterburstTime,		         &ActualAfterburstTime				      },    //OverloadTimeAB
   {497, &ABOverloadPower,		               &ABOverloadPower				            },    //ABOverloadPeakPwr
   {498, &ABOLStatus.ErrorCurrent,		      &ABOLStatus.ErrorCurrent				   },    //OverloadABDUPSCurrent
   {499, &ABOLStatus.ErrorFrequency,		   &ABOLStatus.ErrorFrequency				   },    //OverloadABDUPSFreqAct
   {500, &ABOLStatus.ErrorPSV,		         &ABOLStatus.ErrorPSV				         },    //OverloadABDUPSPhaseAct
   {501, &EBOverloadTimer,		               &EBOverloadTimer				            },    //EBOverloadTime
   {502, &EBOverloadPower,		               &EBOverloadPower				            },    //EBOverloadPeakPwr
   {503, &EBOverloadFreq,		               &EBOverloadFreq				            },    //EBOverloadFreqChg
   
   {504, &FinalResults.TotalEnergy,		      &FinalResults.TotalEnergy				   },    //PeakEnergyActual
   {505, &FinalResults.ActualTotalCollapse,	&FinalResults.ActualTotalCollapse		},    //ColDistActual
   {506, &FinalResults.ActualTriggerDistance,&FinalResults.ActualTriggerDistance		},    //ActualTrigDist
   {507, &ActualForceMax,		               &ActualForceMax				            },    //ActualWeldForce
   {508, &FinalResults.ActualWeldTime,		   &FinalResults.ActualWeldTime				},    //ActualTime
   {509, &ActualSBLMinFreq,		            &ActualSBLMinFreq				            },    //MActualFreq
   {510, &ActualSBLMaxFreq,		            &ActualSBLMaxFreq				            },    //PActualFreq
   {511, &ActualValuePMC1,		               &ActualValuePMC1				            },    //PPmcActual
   {512, &ActualValuePMC2,		               &ActualValuePMC2				            },    //MPmcActual
   {514, &MinNoOfCycles,		               &MaxNoOfCycles				            },    //Print Weld History
   {522, &AmpMicronsMinValue,		           &AmpMicronsMaxValue      	            },    //Print Weld History
   {527, &AmpMicronsMinValue,		           &CurrentSetup.AmpMicronsValue      	    },
   {528, &AmpMicronsMinValue,		           &CurrentSetup.AmpMicronsValue      	    },
   {529, &AmpMicronsMinValue,		           &CurrentSetup.AmpMicronsValue      	    },
};

 UINT16 SendConditionVariable(UINT8 * to)
{
	UINT8 UnitsAndAutoRefresh = 0;
   UINT16 length=0;              // length of data in output buffer
   length += AddToBuffer(&to, (UINT8)CurrentSetup.ControlLevel);
   length += AddToBuffer(&to, (UINT8)CurrentSetup.Actuator);
   length += AddToBuffer(&to, (UINT8)CurrentPreset.WeldMode);
   length += AddToBuffer(&to, (UINT8)CurrentSetup.SecurityLevel);
   length += AddToBuffer(&to, (UINT8)AccessLevel);

   length += AddToBuffer(&to, (UINT8)((SWConfiguration)>>24));
   length += AddToBuffer(&to, (UINT8)((SWConfiguration)>>16));    
   length += AddToBuffer(&to, (UINT8)((SWConfiguration)>>8));      
   length += AddToBuffer(&to, (UINT8)(SWConfiguration));
    
   length += AddToBuffer(&to, (UINT8)((HWConfiguration)>>24));
   length += AddToBuffer(&to, (UINT8)((HWConfiguration)>>16));   
   length += AddToBuffer(&to, (UINT8)((HWConfiguration)>>8));     
   length += AddToBuffer(&to, (UINT8)(HWConfiguration));
   if(CurrentSetup.Units)    
		UnitsAndAutoRefresh = 0x01;
   else
		UnitsAndAutoRefresh = 0x00;

	if(CurrentSetup.AutoRefresh)
		UnitsAndAutoRefresh = UnitsAndAutoRefresh | 0x10;
	else
		UnitsAndAutoRefresh = UnitsAndAutoRefresh | 0x00;

	length += AddToBuffer(&to, (UINT8)UnitsAndAutoRefresh);//Units and AutoRefresh;

   if(CurrentSetup.PassWordFlag)
      length += AddToBuffer(&to, (UINT8)1);
   else
      length += AddToBuffer(&to, (UINT8)0);
   length += AddToBuffer(&to, (UINT8)(CurrentSetup.SequenceEnable));

   length += AddToBuffer(&to, (UINT8)(CurrentSetup.AmpMicronsFlag));

   length += AddToBuffer(&to, (UINT8)(CurrentSetup.PeakPowerWattsFlag));

   length += AddToBuffer(&to, (UINT8)((CurrentSetup.PSWatt)>>24));
   length += AddToBuffer(&to, (UINT8)((CurrentSetup.PSWatt)>>16));   
   length += AddToBuffer(&to, (UINT8)((CurrentSetup.PSWatt)>>8));     
   length += AddToBuffer(&to, (UINT8)(CurrentSetup.PSWatt));

   length += AddToBuffer(&to, (UINT8)(CurrentSetup.AmpMicronsValue));
   InitWeldParamOption();
   
   return length;
}



UINT16 XMLDataProcess(UINT8 * to, UINT16 PositionInMap, UINT16 ID)
/**************************************************************************/
/* This function provides data of different types required to display menu*/
/* according to ID sent by SBC side.                                      */
/**************************************************************************/
{
   UINT16   length = 0;    // length of data in output buffer
   UINT8    Uint8Var;
   UINT16   Uint16Var;
   UINT32   Uint32Var;
   BOOLEAN  booleanVar;
   UINT16   DisableFlag;
   UINT16   EnableFlag;
   UINT32   Uint32PowerTest;
   length += AddToBuffer(&to, (UINT8)(ID>>8));
   length += AddToBuffer(&to, (UINT8)ID);

   Uint8Var =  Map[PositionInMap].DataType;
   length += AddToBuffer(&to, (UINT8)Uint8Var);

   if(Map[PositionInMap].Function1!=NULL)
      Map[PositionInMap].Function1();

   EnableFlag =(*(Map[PositionInMap].Eptr));

   if(((Map[PositionInMap].Eptr == NULL)||EnableFlag == TRUE)){

      if(Map[PositionInMap].Eptr != NULL)
         length += AddToBuffer(&to, (UINT8)EnableFlag);
      else
         length += AddToBuffer(&to, (UINT8)1);
            
      switch(Map[PositionInMap].DataType){
         case uint8:
         case sint8:
            Uint8Var = *((UINT8*)(Map[PositionInMap].Vptr));
            length += AddToBuffer(&to, (UINT8)Uint8Var );
            break;
         case boolean:
            Uint8Var = *((BOOLEAN*)(Map[PositionInMap].Vptr));
            length += AddToBuffer(&to, (UINT8)Uint8Var );
            break;
         case uint16:
         case sint16:
            Uint16Var = *((UINT16*)(Map[PositionInMap].Vptr));
            length += AddToBuffer(&to, (UINT8)(Uint16Var>>8));
            length += AddToBuffer(&to, (UINT8)Uint16Var);
            break;
         case uint32:
         case sint32:
            Uint32Var = *((UINT32*)(Map[PositionInMap].Vptr));
            DisableFlag = *((UINT16*)(Map[PositionInMap].DisableFlag));
            if((ID == AMPLITUDMICRON_SET && (CurrentPreset.Amp2Flag & BIT0) && (CurrentPreset.WeldMode != CONTINUOUSMODE)) ||
               (ID == AMPLITUDEMODE_SET  && (CurrentPreset.Amp2Flag & BIT0) && (CurrentPreset.WeldMode != CONTINUOUSMODE)) ||
               (ID == WELDFORCEMODE_SET  && (CurrentPreset.Force2Flag & BIT0)) ||
               (ID == XSCALE_SET && (CurrentPreset.WeldMode == TIMEMODE) && (CurrentPreset.AutoScaleFlag & BIT0)))
            {
               length += AddToBuffer(&to, 0);
            }
            else
            {
               length += AddToBuffer(&to, 1);
               if(Map[PositionInMap].DisableFlag==NULL){
                  length += AddToBuffer(&to, 0);
                  length += AddToBuffer(&to, 0);
               }
               else{
                  length += AddToBuffer(&to, (UINT8)(DisableFlag>>8));
                  length += AddToBuffer(&to, (UINT8)(DisableFlag));
               }
               if(ID==POWER_TEST)
               {
                  Uint32PowerTest = Uint32Var;
                  Uint32PowerTest=(Uint32PowerTest * CurrentSetup.PSWatt/1000);
                  length += AddToBuffer(&to, (UINT8)(Uint32PowerTest>>24));
                  length += AddToBuffer(&to, (UINT8)(Uint32PowerTest>>16));
                  length += AddToBuffer(&to, (UINT8)(Uint32PowerTest>>8));
                  length += AddToBuffer(&to, (UINT8)(Uint32PowerTest));
               }
               else
               {
                  length += AddToBuffer(&to, (UINT8)(Uint32Var>>24));
                  length += AddToBuffer(&to, (UINT8)(Uint32Var>>16));
                  length += AddToBuffer(&to, (UINT8)(Uint32Var>>8));
                  length += AddToBuffer(&to, (UINT8)(Uint32Var));
               }
               if(ID == PSFREQ_WATTINFO){
                  length += AddToBuffer(&to, (UINT8)LangStrLen(PSFreqTxt));
                  length += AddToBufferString(&to, ((SINT8*)(PSFreqTxt)), LangStrLen(PSFreqTxt));
               }
            }
           break;
         case str:
            length += AddToBuffer(&to, (UINT8)LangStrLen(((SINT8*)(Map[PositionInMap].Vptr))));
            length += AddToBufferString(&to, ((SINT8*)(Map[PositionInMap].Vptr)), LangStrLen(((SINT8*)(Map[PositionInMap].Vptr))));
            break;
         case arr:
            length += SendArrayData(&to,PositionInMap);
            break;
         case nothing:  // no data have been added to buffer. 
         default:
            break;
      }
   }
   else
      length += AddToBuffer(&to, (UINT8)0);

   return length;
}

UINT16 XMLDataResponse(UINT16 PositionInMap, UINT8 *ReceiveValuePtr,UINT8 * to, UINT16 ID )
/****************************************************************************/
/* This function receives data from SBC side and stores it into the desired */
/* place according to Map ID sent by SBC side. As Map ID corresponds to a   */
/* set of structure information and according to corresponding data types   */
/* of Map IDs,1-byte, 2-byte, 4-byte, array or boolean data type are being  */
/* stored and for this a no. of different type pointers are taken here that */
/* point to same location where data have to be stored.                     */
/****************************************************************************/
{
   UINT8    *Uint8Ptr=(UINT8 *)(Map[PositionInMap].Vptr);
   BOOLEAN  *BoolPtr=(BOOLEAN  *)(Map[PositionInMap].Vptr);
   UINT16   *Uint16Ptr=(UINT16 *)(Map[PositionInMap].Vptr);
   UINT32   *Uint32Ptr=(UINT32 *)(Map[PositionInMap].Vptr);
   UINT16   *DisablePtr = (UINT16*)(Map[PositionInMap].DisableFlag);
   UINT8    *Arr=(UINT8 *)(Map[PositionInMap].Vptr);
   UINT8    ArrayLength; 
   UINT8    *Value =(UINT8 *) ReceiveValuePtr;
   UINT16   i,length = 0;        // length of data in output buffer

      switch(Map[PositionInMap].DataType){
      case boolean:
         if(*Value)
            *BoolPtr =TRUE;
         else
            *BoolPtr =FALSE;

         if (*Value != 0) //Send back Toggle value
            length += AddToBuffer(&to,(UINT8 )1);
         else
            length += AddToBuffer(&to,(UINT8)0);

         if(ID == UNIT_SET)  //send a byte as either 1 in case of Unit change
                      //or  0 in other case 
            length += AddToBuffer(&to, (UINT8)1);
         else
            length += AddToBuffer(&to, (UINT8)0);

         break;

      case uint8:
      case sint8:
         *Uint8Ptr =(UINT8)(*Value);
         break;

      case uint16:
      case sint16:
         if(ID != DIGITAL_TUNE_CHOICE || DigitalPotEntry())
         {
            *Uint16Ptr = ((UINT16)(*Value)<<8)+ (UINT16)(*(Value+1));
            if(ID == DIGITAL_TUNE_CHOICE)
               QVGADigitalPotChoiceDone();

            if((ID == WELDMODE_SET)||(ID == PRST_RECALL) || (ID == PASSWD_ENTRY))
               length += AddToBuffer(&to,(UINT8 )1);
            else
               length += AddToBuffer(&to,(UINT8 )0);

            length += AddToBuffer(&to,(UINT8 )(*Uint16Ptr)>>8);
            length += AddToBuffer(&to,(UINT8 )(*Uint16Ptr));
            if( ID == PRST_VERIFY)
               length += ProcessPresetVerify(&to);
         }
         else
         {
            NackError = WELDER_PROCESS_ERROR;
            ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
            ErrorResponseMaxLimit = 0;
         }
         break;

      case uint32:
      case sint32:
         *DisablePtr=((UINT16)(*Value)<<8)+ (UINT16)(*(Value+1));
         Value=Value+2;
         *Uint32Ptr =((UINT32)(*Value)<<24) + ((UINT32)(*(Value+1))<<16) + ((UINT32)(*(Value+2))<<8) + ((UINT32)(*(Value+3)));
         break;
      case arr:
         length += SetArrayData(&to,Value,Arr);
         break;
        
      case nothing:
         if(ID == PARAMETER_NUM)
         {
            SetRunScreenParam();
            length += WeldParams(&to,TotalCycle,AllParamColumnFlag);
         }
         break;
      default: // no data manipulation
            break;
      }
   
   length += AddToBuffer(&to, (UINT8)(ID>>8));
   length += AddToBuffer(&to, (UINT8)ID);

   if((Map[PositionInMap].DataType != nothing)&&(ID != PRST_VERIFY))
      UpdateCurrentPresetAndSetup();
   
   if(Map[PositionInMap].Function2!=NULL)
   {
      Map[PositionInMap].Function2();
      if(Uint16Ptr == &RadioIndex)
         UpdateCurrentPresetAndSetup();
   }

   if(!DisplayNextMenu)
   {
      DisplayNextMenu = TRUE;
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;                                                 
   }
   return length;
}

UINT16 SendMinMaxData(UINT8 * to, UINT16 PositionInMap)
/**************************************************************************/
/* This function provides minimum and maximum values for a variable entry */
/* according to Map ID sent by SBC side.                                  */
/**************************************************************************/

{
   UINT16 length = 0;
   SINT32 Max,Min;

   Max=*((SINT32 *)(MinMap[PositionInMap].ptrmax));
   Min=*((SINT32 *)(MinMap[PositionInMap].ptrmin));

   if((GlobalCommandID == AMPLITUDMICRON_SET && (CurrentPreset.Amp2Flag & BIT0) && (CurrentPreset.WeldMode != CONTINUOUSMODE)) ||
      (GlobalCommandID == AMPLITUDEMODE_SET  && (CurrentPreset.Amp2Flag & BIT0) && (CurrentPreset.WeldMode != CONTINUOUSMODE)) ||
      (GlobalCommandID == WELDFORCEMODE_SET  && (CurrentPreset.Force2Flag & BIT0)) ||
      (GlobalCommandID == XSCALE_SET && (CurrentPreset.WeldMode == TIMEMODE) && (CurrentPreset.AutoScaleFlag & BIT0)) ||
      (GlobalCommandID == RT_DIST && !(RapidTraverseState & BIT0)) || (MinMap[PositionInMap].ptrmax == MinMap[PositionInMap].ptrmin))
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
   else if (GlobalCommandID == DIGITAL_FREQ)
   {
      DiagFlag = FALSE;    //Disable diagnostics
      ForceDigitalTuneTest = FALSE;
      if(CurrentSetup.DigPotFlag && DigitalPotEntry())
      {
         ResetStateMachine();  /* Position is at original value, */
         StartStateMachine();  /* don't need to force Test.      */
         if (DigitalFreqEntry())/*Make sure in READY first */
            SaveDigPotValue = DigPotValue;
         else
         {
            NackError = WELDER_PROCESS_ERROR;
            ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
            ErrorResponseMaxLimit = 0;
         }   
      }
      else
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
         ErrorResponseMaxLimit = 0;
      }
   }
   if (!NackError)/*Editable VARIABLE */
   {
      if (QVGAHornDown){
         ProcessHDButtonPress3();
         ResetStateMachine(); /* Stop the State machine*/
         ClearReady();
      }
      length += AddToBuffer(&to, (UINT8)(Min>>24));
      length += AddToBuffer(&to, (UINT8)(Min>>16));
      length += AddToBuffer(&to, (UINT8)(Min>>8));
      length += AddToBuffer(&to, (UINT8)(Min));

      length += AddToBuffer(&to, (UINT8)(Max>>24));
      length += AddToBuffer(&to, (UINT8)(Max>>16));
      length += AddToBuffer(&to, (UINT8)(Max>>8));
      length += AddToBuffer(&to, (UINT8)(Max));
   }
   return(length);
}

UINT16 SendArrayData(UINT8 ** to, UINT16 PositionInMap)
/**************************************************************************/
/* This function provides array type values for different menus           */
/* according to GlobalCommandID sent by SBC side.                         */
/**************************************************************************/
{
   UINT16   Index;
   UINT8    Index1;
   SINT8    TempStr1[10];
   UINT16   length = 0;

   if( GlobalCommandID == PRST_LISTING)
   {
      for (Index = 0; Index < MAX_PRESETS; Index++)
      {
         strcpy(PresetListBoxBuffer, PresetNameArray1[Index]);  
         length += AddToBuffer(to, strlen(PresetListBoxBuffer));			           
         length += AddToBufferString(to, PresetListBoxBuffer, strlen(PresetListBoxBuffer));
      }
   }
   else if (GlobalCommandID == PRST_INFO)
   {
      if((PresetEnableFlags[VGAPresetNum] == TRUE) && (VGAPresetNum > 0)) 
      {
         /* Display the Date when preset was saved. */
         length += AddToBuffer(to, strlen(InfoLine4));			           
         length += AddToBufferString(to, InfoLine4, strlen(InfoLine4));
         /* Display the Time when preset was saved. */
         length += AddToBuffer(to, strlen(InfoLine5));			           
         length += AddToBufferString(to, InfoLine5, strlen(InfoLine5));
         /* Display the weld count of the preset. */
         length += AddToBuffer(to, strlen(InfoLine6));			           
         length += AddToBufferString(to, InfoLine6, strlen(InfoLine6));
         /* Display the verify status. */
         if(InfoLine3[0]=='1')
            length += AddToBuffer(to,(UINT8)1);
         else
            length += AddToBuffer(to,(UINT8)0);
      }
      else
         length += AddToBuffer(to, 0);
   }
   else if(GlobalCommandID == SEQUENCE_LISTING)
   {
      for (Index = 0; Index < MAX_SEQUENCE_NOS; Index++)
      {
         SPrintf(TempStr1, "%2d", Index+1);
         strcat(TempStr1, ". ");
         strcpy(PresetListBoxBuffer, TempStr1);
         if (Index < CurrentSetup.SequenceCount)
         {
            Index1 = CurrentSetup.SequenceList[Index];
            strcat(PresetListBoxBuffer, PresetNameArray1[Index1-1]);  
            length += AddToBuffer(to, strlen(PresetListBoxBuffer));			           
            length += AddToBufferString(to, PresetListBoxBuffer, strlen(PresetListBoxBuffer));
         }   
        else
        {
           length += AddToBuffer(to, strlen(PresetListBoxBuffer));			           
           length += AddToBufferString(to, PresetListBoxBuffer, strlen(PresetListBoxBuffer));
        }
      } 
   }
   else if(GlobalCommandID == TIME_INFO || GlobalCommandID == DATE_INFO || GlobalCommandID == CALIBRATE_INFO) 
   {
      if(GlobalCommandID == DATE_INFO || GlobalCommandID == CALIBRATE_INFO)       //For Date Array
         Index = 3;
      else                                                    //for Time Array
         Index = 2;
      length += AddToBuffer(to,(UINT8)Index);
      length += AddToBufferString(to, ((SINT8*)(Map[PositionInMap].Vptr)), (UINT8)Index);
   }
   else
   {
      length += AddToBuffer(to, (UINT8)strlen(((SINT8*)(Map[PositionInMap].Vptr))));
      length += AddToBufferString(to, ((SINT8*)(Map[PositionInMap].Vptr)), strlen(((SINT8*)(Map[PositionInMap].Vptr))));
   }
   return (length);
}

UINT16 SetArrayData(UINT8 ** to, UINT8    *Value, UINT8    *Arr)
/**************************************************************************/
/* This function sets array type values for different menus               */
/* according to GlobalCommandID.                                          */
/**************************************************************************/
{
   UINT16   length = 0,i;
   UINT8    ArrayLength;

   ArrayLength = (UINT8)(*Value);
   if(GlobalCommandID == SEQUENCE_LIST_UPDATE)
   {
      CurrentSetup.SequenceCount = ArrayLength; 
      if (CurrentSetup.SequenceNos >= CurrentSetup.SequenceCount)   
         CurrentSetup.SequenceNos = 0;
   }
   if(GlobalCommandID == PASSWD_SAVE)
   {
     Value++;
     PasswdEntryFlag =(UINT8)(*Value);
     ArrayLength--;
   }
   if(GlobalCommandID == PSSERIAL_NUMID)
      if(ArrayLength > SERIALLENGTH )
         NackError = PARAMETER_ERROR;
      else
         for (i=1; i<SERIALLENGTH; i++)   /* Test serial number for printable ascii */
         {
            if((*(Value +i)) < ' ') 
            {
               NackError = PARAMETER_ERROR;
               break;
            }
         }

   if(GlobalCommandID == ACTSERIAL_NUMID)
      if(ArrayLength > MAXSERIALNUM )
         NackError = PARAMETER_ERROR;

   if(!NackError)
   {
     for(i = 0 ; i < ArrayLength ; i++)
     {
         Value++;
         *(Arr + i)=(UINT8)(*Value);
     }
     *(Arr + i)='\0';
   }
   if(GlobalCommandID == PASSWD_SAVE)
      length += PasswordSave(to);
   return (length);
}

UINT16 SendBargraphData(UINT8 **to, SINT32 *VPtr)
/**************************************************************************/
/* This function provides Bargraph position information.                  */
/**************************************************************************/
{
   UINT16 length=0;
   UINT32 Index;
   UINT8 Value = (UINT8)(*VPtr);
   
   switch (Value)
   {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
         Index = Value;
         break;
      default:
         Index = 13;
         break;
   }
   length += AddToBuffer(to,(UINT8)(Index>>24));
   length += AddToBuffer(to,(UINT8)(Index>>16));

   length += AddToBuffer(to,(UINT8)(Index>>8));
   length += AddToBuffer(to,(UINT8)Index);

   return (length);
}

UINT16 ScanInfoStatus(UINT8 **to)
/**************************************************************************/
/* This function provides HornScan status information.                    */
/**************************************************************************/
{
   UINT8 Index;
   UINT16 length=0;

   switch(HornScanInfo. ScanStatus)
   {
   case DUPS_SCANINPROG:
      if(PrevHornState != DUPS_SCANINPROG)
         PrevHornState = DUPS_SCANINPROG;   
      length += AddToBuffer(to,(UINT8)1);
      length += AddToBuffer(to,(UINT8)1);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0); 
      length += AddToBuffer(to,(UINT8)0);
      break; 
      
   case DUPS_SCANDATAAVAIL:
      if(PrevHornState != DUPS_SCANDATAAVAIL)
      {
         EnableWelding();
         PrevHornState = DUPS_SCANDATAAVAIL;                   
      }
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)1);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      break;
      
   case DUPS_NOSCAN:
      if(PrevHornState != DUPS_NOSCAN)
      {
         EnableWelding(); 
         PrevHornState = DUPS_NOSCAN;            
      }
      if(QVGAHornScanOLD)
      {
         length += AddToBuffer(to,(UINT8)0);
         length += AddToBuffer(to,(UINT8)0);
         length += AddToBuffer(to,(UINT8)0);
         length += AddToBuffer(to,(UINT8)0);
         length += AddToBuffer(to,(UINT8)1);
         length += AddToBuffer(to,(UINT8)0);
      }
      else
      {
         length += AddToBuffer(to,(UINT8)0);
         length += AddToBuffer(to,(UINT8)0);
         length += AddToBuffer(to,(UINT8)0);
         length += AddToBuffer(to,(UINT8)1);
         length += AddToBuffer(to,(UINT8)0);
         length += AddToBuffer(to,(UINT8)0);
      }
      break;
            
   case DUPS_SCANSCOMPLETE:
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)1);
   break;
      
   default:
      length += AddToBuffer(to,(UINT8)1);
      length += AddToBuffer(to,(UINT8)1);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
      length += AddToBuffer(to,(UINT8)0);
   break;      
   } 
   return (length);   
}

UINT16 SendBottomHalfData(UINT8 *to, UINT16 BottomHalfID)
/**************************************************************************/
/* This function provides data for formation of Bottom Half screen        */
/**************************************************************************/
{
   UINT16   length = 0,i;
   char TempBuf[15];
   UINT32 Uint32PowerTest;
   switch(BottomHalfID)
   {
   case DIGITAL_TUNE_CHOICE:
      length += AddToBuffer(&to, (UINT8)0);
      length += AddToBuffer(&to,(UINT8)2);
      length += SendBargraphData(&to, &FMemoryBargraph);
      length += SendBargraphData(&to, &FActualBargraph);
      length += AddToBuffer(&to,(UINT8)6);
      length += AddToBuffer(&to, (UINT8)(1));
      length += AddToBuffer(&to, (UINT8)(1));
      GetRunSelection();
      length += AddToBuffer(&to,(UINT8)(VGARunSelected));
      GetClearSelection();
      length += AddToBuffer(&to,(UINT8)(VGAClearSelected));
      GetSeekSelection();
      length += AddToBuffer(&to,(UINT8)(VGASeekSelected));
      GetStoreSelection();
      length += AddToBuffer(&to,(UINT8)(VGAStoreSelected));
      break;

   case HS_START:
      length += AddToBuffer(&to,(UINT8)6);
      for (i=0;i<DUPS_NUMRESONANCES;i++) // Resonance frequency value
      {
         length += AddToBuffer(&to, (UINT8)((HornScanInfo.ResonanceFreqs[i])>>24));
         length += AddToBuffer(&to, (UINT8)((HornScanInfo.ResonanceFreqs[i])>>16));
         length += AddToBuffer(&to, (UINT8)((HornScanInfo.ResonanceFreqs[i])>>8));
         length += AddToBuffer(&to, (UINT8)(HornScanInfo.ResonanceFreqs[i]));
      }
      
      length += AddToBuffer(&to,(UINT8)6);
      for (i=0;i<DUPS_NUMRESONANCES;i++) // Resonance frequency type either series or parallel
      {
         length += AddToBuffer(&to, (UINT8)(FreqType[i]));
      }
      length += AddToBuffer(&to,(UINT8)13);

      for (i=0;i<DUPS_NUMRESONANCES;i++)
         length += AddToBuffer(&to, (UINT8)(ResonanceFreqEnable[i]));   //Enable Flag
      if(HSStartFlag)
         length += ScanInfoStatus(&to);
      else
         for (i=0;i<6;i++)
            length += AddToBuffer(&to, (UINT8)(0));   
      length += AddToBuffer(&to, (UINT8)(1)); // to show exit button  
      break;
   
   case HORN_DOWN_MENU:
         length += AddToBuffer(&to, (UINT8)HDMenuID);
         switch(HDMenuID)
         {
         case RESULT_MENU:
            length += AddToBuffer(&to, (UINT8)(4)); //Enable Flag
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>24));
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>16));
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>8));
            length += AddToBuffer(&to, (UINT8)(CurrentPressure));
         
            length += AddToBuffer(&to, (UINT8)((HDPosition)>>24));
            length += AddToBuffer(&to, (UINT8)((HDPosition)>>16));
            length += AddToBuffer(&to, (UINT8)((HDPosition)>>8));
            length += AddToBuffer(&to, (UINT8)(HDPosition));

            length += AddToBuffer(&to, (UINT8)((CurrentForce)>>24));
            length += AddToBuffer(&to, (UINT8)((CurrentForce)>>16));
            length += AddToBuffer(&to, (UINT8)((CurrentForce)>>8));
            length += AddToBuffer(&to, (UINT8)(CurrentForce));

            length += AddToBuffer(&to, (UINT8)((HornDownVelocity)>>24));
            length += AddToBuffer(&to, (UINT8)((HornDownVelocity)>>16));
            length += AddToBuffer(&to, (UINT8)((HornDownVelocity)>>8));
            length += AddToBuffer(&to, (UINT8)(HornDownVelocity));

            length += AddToBuffer(&to, (UINT8)(5));   
            length += AddToBuffer(&to, (UINT8)(HDShowPressure));
            length += AddToBuffer(&to, (UINT8)(1));
            length += AddToBuffer(&to, (UINT8)(HDShowForce));
            length += AddToBuffer(&to, (UINT8)(HDShowVelocity));
            length += AddToBuffer(&to, (UINT8)(KeepHornDown.uint16.Hi));

            break;

         case RESULT_MENU_AE:
            length += AddToBuffer(&to, (UINT8)(0));
            length += AddToBuffer(&to, (UINT8)(1));
            length += AddToBuffer(&to, (UINT8)(KeepHornDown.uint16.Hi));
            break;

         case REFRESH_MENU_AEF2:
            length += AddToBuffer(&to, (UINT8)(3)); //Enable Flag
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>24));
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>16));
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>8));
            length += AddToBuffer(&to, (UINT8)(CurrentPressure));

            length += AddToBuffer(&to, (UINT8)((HDPosition)>>24));
            length += AddToBuffer(&to, (UINT8)((HDPosition)>>16));
            length += AddToBuffer(&to, (UINT8)((HDPosition)>>8));
            length += AddToBuffer(&to, (UINT8)(HDPosition));

            length += AddToBuffer(&to, (UINT8)((CurrentForce)>>24));
            length += AddToBuffer(&to, (UINT8)((CurrentForce)>>16));
            length += AddToBuffer(&to, (UINT8)((CurrentForce)>>8));
            length += AddToBuffer(&to, (UINT8)(CurrentForce));
            
            length += AddToBuffer(&to, (UINT8)(3));
            
            length += AddToBuffer(&to, (UINT8)(HDShowPressure));
            length += AddToBuffer(&to, (UINT8)(1));
            length += AddToBuffer(&to, (UINT8)(HDShowForce));

            break;

         case REFRESH_MENU_AEF1:
         case REFRESH_MENU_AED:
            length += AddToBuffer(&to, (UINT8)(1)); //Enable Flag
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>24));
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>16));
            length += AddToBuffer(&to, (UINT8)((CurrentPressure)>>8));
            length += AddToBuffer(&to, (UINT8)(CurrentPressure));
            length += AddToBuffer(&to, (UINT8)(1));
            length += AddToBuffer(&to, (UINT8)(HDShowPressure));
            break;

         case REFRESH_MENU_AE:
            length += AddToBuffer(&to, (UINT8)(0));
            length += AddToBuffer(&to, (UINT8)(0));
            break;
         default:
            break;
         }
      break;
   case TEST_AMPLITUDE:
      length += AddToBuffer(&to, (UINT8)0);
      length += AddToBuffer(&to,(UINT8)4);

      Uint32PowerTest=PowerTest;
      Uint32PowerTest=(Uint32PowerTest * CurrentSetup.PSWatt/1000);
      length += AddToBuffer(&to, (UINT8)((Uint32PowerTest)>>24));
      length += AddToBuffer(&to, (UINT8)((Uint32PowerTest)>>16));
      length += AddToBuffer(&to, (UINT8)((Uint32PowerTest)>>8));
      length += AddToBuffer(&to, (UINT8)(Uint32PowerTest));

      length += AddToBuffer(&to, (UINT8)((CurrentFreqIn)>>24));
      length += AddToBuffer(&to, (UINT8)((CurrentFreqIn)>>16));
      length += AddToBuffer(&to, (UINT8)((CurrentFreqIn)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentFreqIn));

      length += SendBargraphData(&to, &FMemoryBargraph);
      length += SendBargraphData(&to, &FActualBargraph);
      length += AddToBuffer(&to,(UINT8)8);
      length += AddToBuffer(&to, (UINT8)(1));
      length += AddToBuffer(&to, (UINT8)(1));
      length += AddToBuffer(&to, (UINT8)(1));
      length += AddToBuffer(&to, (UINT8)(1));
      GetRunSelection();
      length += AddToBuffer(&to,(UINT8)(VGARunSelected));
      GetClearSelection();
      length += AddToBuffer(&to,(UINT8)(VGAClearSelected));
      GetSeekSelection();
      length += AddToBuffer(&to,(UINT8)(VGASeekSelected));
      GetStoreSelection();
      length += AddToBuffer(&to,(UINT8)(VGAStoreSelected));
      break;
   default: // no data have been provided to buffer
      break;
   }
   return (length);
}

void ProcessWindowSetup(void)
{
  if((WeldState != PREREADYSTATE) && (WeldState != READYSTATE))
  {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
      ErrorResponseMaxLimit = 0;
   }
   else 
   {
      WindowSetupFlag = TRUE;
      VGA_ReadyFlag = ReadyFlag;
      ReadyFlag = FALSE;
      ResetStateMachine();
      ClearReady();
   }
}
void CheckforDisplayLock(void)
{
   if(Inp.DisplayLockFlag)
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = SHOW_MAIN_MENU;
      ErrorResponseMaxLimit = 0;
   }
}
void RemoteSerialCommandHandler(void){

   RSCH_MSG_QUEUE_TYPE RschMsg;

   UINT16          i;
   UINT8           AckBuf[SERIAL_MAXACKLENGTH];
   UINT16          CommandCount;
   UINT16          Function;
 
   /* ActionFlags are used for commands that change more than 1 variable to
      defer the actions until all parameter limit tests have been performed.
      This is to prevent partial implementation of a command with a parameter
      error.   */
   UINT32          Value32;
   UINT32         *Host32;
   UINT32          PsosStatus;

   PsosStatus = q_ident(RSCH_Q, Q_NODE_0, &RschQid);

   while (FOREVER)
   {
      /* wait forever for a psos message */
      PsosStatus = q_receive(RschQid, Q_WAIT, Q_WAIT_FOREVER, &RschMsg);

      /* initialize queue send indicator and byte check each pass */
      NackError = 0;    /* Assume valid command */
      CommandCount = (RschMsg.host_cmd.byte_count+9);
      /* The majority of commands have 1 32-bit parameter. */
      /* Computing Value32 here saves space by not doing it repeatedly later. */
      Host32 = (UINT32 *) RschMsg.host_cmd.data_pointer;
      Value32 = *Host32;

      Function = RschMsg.generic.common.opcode;
      
      if (Function < VGA_HOST_COMMAND)
      {
         i = ProcessHostCommand(Value32, Function, 
                              (UINT8 *) RschMsg.host_cmd.data_pointer,
                              CommandCount, AckBuf, RschMsg.generic.common.source_task );
         SerialMessageQueue(AckBuf, i);
      }
      else
      {
         i = ProcessVGAHostCommand(Value32, Function, 
                                (UINT8 *) RschMsg.host_cmd.data_pointer,
                                CommandCount);
         SerialMessageQueue(VGAAckBuf, i);
      }   
                              
      if (RschMsg.host_cmd.common.pointer_flag == DATA_PTR_DEALLOC)
      {
         /* return the buffer allocated by the NvmManager task */
         PsosStatus = pt_retbuf(RschMsg.host_cmd.partition_id,
                      RschMsg.host_cmd.data_pointer);
      }
   }/* end while forever */
}

UINT16 ProcessHostCommand(UINT32 Value32, UINT16 Function, UINT8  *DataPointer,
                           UINT16 CommandCount, UINT8 * AckBuf, 
                           SOURCE_TASK_ID_TYPE Source_Task  )
/****************************************************************************/
/*Description:-                                                             */
/* This function builds reply for General Host commands and writes data in  */
/* in buffer                                                                */
/*Input Parameters:-                                                        */
/* Value32: First four data bytes are mostly pointer value                  */
/* Function: Host command Function number                                   */
/* Datapointer: Pointer to the host command data                            */
/* CommandCount: Nos of data bytes in a command                             */
/* AckBuf: Buffer where reply is written                                    */
/* Source_Task: Identifies source task from where the command came          */
/*Returns length of the bytes written to the buffer                         */  
/****************************************************************************/
                           
{
   FP_KEY_PRESSED_MSG FpkpQueue;

   UINT16          i, Count,j;
   UINT16          NoAckOrNak = FALSE;
   UINT16          SubFunction;

   /* ActionFlags are used for commands that change more than 1 variable to
     defer the actions until all parameter limit tests have been performed.
     This is to prevent partial implementation of a command with a parameter
     error.   */
   UINT16          ActionFlags[MAXACTIONFLAGS];
   UINT32          Params[MAXACTIONFLAGS];
   UINT8           Value8;
   UINT16          Value16;
   UINT8          *Host8;
   UINT8          *TempPtr;
   UINT16         *Host16;
   PRESET_COMPRESSED  *TempPreset;
   static UINT8    SendMenuResponse[256];
   UINT16          len;

   UINT32          PsosStatus;
   UINT32          FpkpQid;

   PsosStatus = q_ident(FPKP_Q, Q_NODE_0, &FpkpQid);

   for(Count=0; Count<MAXACTIONFLAGS; Count++)
      ActionFlags[Count] = FALSE;     /* zero all action flags */

   i = 0;
   switch (Function)
   {

      case DOWNLOAD_CURRENT_PRESET: /* Copy the data to HostPreset structure.*/
         if(CommandCount == DOWNLOADCOMMAND_SIZE )
         {
            memcpy( (UINT8 *) &HostPreset, (UINT8 *)DataPointer,
                      sizeof(PRESET_COMPRESSED));
            HostPresetEmpty = FALSE;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;


      case UPLOAD_CURRENT_PRESET:
         if(CommandCount == UPLOADCOMMAND_SIZE)
         {
            /* Added Temporarily to update the 3 Dups param*/
            TempPreset = (PRESET_COMPRESSED *)PresetAddress[0];
            TempPreset->SwDip = DUPS_CurrentParamSet.SWDipSetting;
            TempPreset->SeekTime = DUPS_CurrentParamSet.SeekTime;
            TempPreset->WeldRampTime = DUPS_CurrentParamSet.WeldRampTime;

            TempPtr = (UINT8 *) PresetAddress[0];
            /*Data in the Preset 0 is same as Current Preset Except some
            nonmatching members.Send the data in compressed form from 
            compressed preset only.*/
            i = 0;
            AckBuf[i++] = ACK;
            AckBuf[i++] = DLE;
            AckBuf[i++] = STX;
            /* Increment index over byte count */
            i += 2;
            /* fill in function */
            AckBuf[i++] = (UINT8)(Function >> 8);
            AckBuf[i++] = (UINT8)Function;
            /* fill in Error */
            AckBuf[i++] =  (UINT8)Inp.DisplayLockFlag;
            /*Fill the Preset Data*/
            for(j = 0; j < sizeof(PRESET_COMPRESSED); j++)
               AckBuf[i++] = *TempPtr++;   
            /* fill in byte count */
            AckBuf[3] = (UINT8)((i-3)>>8);
            AckBuf[4] = (UINT8) (i-3);   
            /* compute checksum */
            AckBuf[i] = 0;
            for (j=3; j<i; j++)
               AckBuf[i] ^= AckBuf[j];
            i++;
            /* add DLE, ETX to message */
            AckBuf[i++] = DLE;
            AckBuf[i++] = ETX;
            NoAckOrNak = TRUE;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case REQUEST_GRAPH_DATA:
         if (CommandCount == GRAPHCOMMAND_SIZE) {
            Host16 = (UINT16 *)DataPointer;
            Value16 = *Host16;
            i = 0;
            AckBuf[i++] = ACK;
            AckBuf[i++] = DLE;
            AckBuf[i++] = STX;
            i += 2;       /* Increment index over byte count */
            AckBuf[i++] = (UINT8)(Function >> BYTE3SHIFT);  /* fill in function */
            AckBuf[i++] = (UINT8)Function;
            AckBuf[i++] = (UINT8)Inp.DisplayLockFlag; /* fill in display lock info */

            switch (Value16) {      /*Fill the graph Data*/
               case POWERGRAPH:
                  SetupVals(POWGRAPH, val2);
                  i += CreateGraphHeader(Value16, &AckBuf[i]);
                  for (j = 0; j < MsPointer->count; j++) {
                     AckBuf[i++] = (UINT8)(val2[j]>>BYTE3SHIFT);
                     AckBuf[i++] = (UINT8)(val2[j]);
                  }
               break;

               case AMPGRAPH:
                  SetupVals(AMPLIGRAPH, val2);
                  i += CreateGraphHeader(Value16, &AckBuf[i]);
                  for (j = 0; j < MsPointer->count; j++) {
                     AckBuf[i++] = (UINT8)(val2[j]>>BYTE3SHIFT);
                     AckBuf[i++] = (UINT8)(val2[j]);
                  }
               break;

               case FREQGRAPH:
                  SetupVals(FREQUGRAPH, val2);
                  i += CreateGraphHeader(Value16, &AckBuf[i]);
                  for (j = 0; j < MsPointer->count; j++) {
                     AckBuf[i++] = (UINT8)(val2[j]>>BYTE3SHIFT);
                     AckBuf[i++] = (UINT8)(val2[j]);
                  }
               break;

               case COLDISTGRAPH:
                  SetupVals(DISTINGRAPH, val2);
                  i += CreateGraphHeader(Value16, &AckBuf[i]); 
                  for (j = 0; j < MsPointer->count; j++) {
                     AckBuf[i++] = (UINT8)(val2[j]>>BYTE3SHIFT);
                     AckBuf[i++] = (UINT8)(val2[j]);
                  }
               break;

               case VELOCITYGRAPH:
                  SetupVals(VELINGRAPH, val2);
                  i += CreateGraphHeader(Value16, &AckBuf[i]);
                  for (j = 0; j < MsPointer->count; j++) {
                     AckBuf[i++] = (UINT8)(val2[j]>>BYTE3SHIFT);
                     AckBuf[i++] = (UINT8)(val2[j]);
                  }
               break;

               case FORCEGRAPH:
                  SetupVals(FORCELBGRAPH, val2);
                  i += CreateGraphHeader(Value16, &AckBuf[i]);
                  for (j = 0; j < MsPointer->count; j++) {
                     AckBuf[i++] = (UINT8)(val2[j]>>BYTE3SHIFT);
                     AckBuf[i++] = (UINT8)(val2[j]);
                  }
               break;

               case HORNSCAN:
                  NackError = ILLEGAL_COMMAND; /* Until Hornscan done */
               //                     i += CreateHornscanHeader(&AckBuf[i]);
               break;

               default:
                  NackError = ILLEGAL_COMMAND;
            }

               if (!NackError) {
               AckBuf[3] = (UINT8)((i-3) >> BYTE3SHIFT);/* fill in byte count */
               AckBuf[4] = (UINT8) (i-3);   

               AckBuf[i] = 0;                           /* compute checksum   */
               for (j = 3; j < i; j++)
               AckBuf[i] ^= AckBuf[j];
               i++;

               AckBuf[i++] = DLE;                       /* add DLE, ETX to message */
               AckBuf[i++] = ETX;
               NoAckOrNak = TRUE;
               }
         }
         else NackError = ILLEGAL_COMMAND;
      break;

      case RESET_ALARMS:

         if(CommandCount == RESETALARMS_SIZE)
         {
            if((KeyMask & RESETKEYMASK) == RESETKEYMASK)
            /*Check if Reset key is enabled */
            {
               ResetFailed = FALSE;
               ResetAlarmProcessed = FALSE;
               FpkpQueue.key = ResetKey; 
               /*Send the key to FPK_TASK */  
               FpkpQueue.common.opcode = OP_FRONT_PANEL_KEYPRESS;
               PsosReturnValue = q_send(FpkpQid, &FpkpQueue);
               while(!ResetAlarmProcessed)/*Wait to Key processing in weldmngr*/
                  tm_wkafter( SECONDS_TO_TICKS( 1 ));
               if(ResetFailed)/*Check for any non-resetable alarm*/
                  NackError = HARDWARE_FAILURE;
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case RECALL_PRESET:
         Host8 = (UINT8 *)DataPointer;
         if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
         &&(IsThereDataPrinting == FALSE) && (IsGraphDrawing == FALSE))
         {  // Ok to recall preset since no weld in progress
            if (PresetEnableFlags[*Host8])
            {
               RecallPreset(*Host8);
               SystemParameterChgdFlag = TRUE;
            }
            else
               NackError = PARAMETER_ERROR;
         }
         else
         {
            /* PARAMETER_ERROR is temporary pending Ver9 and verbose error messages. */
            NackError = PARAMETER_ERROR;   
         }
      break;


      case SET_CURRENT_PRESET_PARAMETERS:

         /* Extract number of parms from message */
         Host16 = (UINT16 *)DataPointer;
         Value16 = *Host16;
         Host16++;                  /* Point to 1st PARMID */

         /* Process each parameter */
         for (Count=0; Count<Value16; Count++)
         {
            /* Break out of for loop if error encountered */
            if (NackError) break;

            /* Switch on Parm Id */
            SubFunction = *Host16;
            switch (SubFunction)
            {
               case WELDTIME:

                  Host16++;         /* Point to number of bytes for this parameter */
                  Host16++;         /* Point to 1st parameter byte */  
                  Value32 = *(SINT32 *)Host16;

                  /* Store upper and lower bounds in case of error */
                  ErrorResponseMinLimit = MinLimit.WeldTime;
                  ErrorResponseMaxLimit = MaxLimit.WeldTime;
                  SubFunction = WELDTIME;

                  if(Value32 >= MinLimit.WeldTime)
                  {
                     if(Value32 <= MaxLimit.WeldTime)
                     { 
                        ActionFlags[0] = TRUE;
                        Params[0] = Value32;
                     }
                     else
                        NackError = MAX_ERROR;
                  }
                  else
                     NackError = MIN_ERROR;

                  Host16 += 2;      /* Point to next PARMID */
               break;

               case HOLDTIME:

                  Host16++;         /* Point to number of bytes for this parameter */
                  Host16++;         /* Point to 1st parameter byte */ 
                  Value32 = *(SINT32 *)Host16;

                  /* Store upper and lower bounds in case of error */
                  ErrorResponseMinLimit = MinLimit.HoldTime;
                  ErrorResponseMaxLimit = MaxLimit.HoldTime;
                  SubFunction = HOLDTIME;

                  if (!Value32)
                     ActionFlags[1] = TRUE;

                  else if(Value32 >= MinLimit.HoldTime)
                  {
                     if(Value32 <= MaxLimit.HoldTime)
                     {  
                        ActionFlags[2] = TRUE;
                        Params[2] = Value32;
                     }
                     else
                        NackError = MAX_ERROR;
                  }
                  else
                     NackError = MIN_ERROR;

                  Host16 += 2;      /* Point to next PARMID */
               break;

               case PEAKPOWER:

                  Host16++;         /* Point to number of bytes for this parameter */
                  Host16++;         /* Point to 1st parameter byte */ 
                  Value32 = *(SINT32 *)Host16;

                  /* Store upper and lower bounds in case of error */
                  ErrorResponseMinLimit = MinLimit.PeakPwr;
                  ErrorResponseMaxLimit = MaxLimit.PeakPwr;
                  SubFunction = PEAKPOWER;

                  if(Value32 >= MinLimit.PeakPwr)
                  {
                     if(Value32 <= MaxLimit.PeakPwr)
                     { 
                        ActionFlags[3] = TRUE;
                        Params[3] = Value32;
                     }  
                     else
                        NackError = MAX_ERROR;
                  }
                  else
                     NackError = MIN_ERROR;

                  Host16 += 2;      /* Point to next PARMID */               
               break;
               case ABSOLUTE:
                  Host16++;         /* Point to number of bytes for this parameter */
                  Host16++;         /* Point to 1st parameter byte */ 
                  Value32 = *(SINT32 *)Host16;

                  /* Store upper and lower bounds in case of error */
                  ErrorResponseMinLimit = MinLimit.AbsDist;
                  ErrorResponseMaxLimit = MaxLimit.AbsDist;
                  SubFunction = ABSOLUTE;
                  if((CurrentSetup.ExtPresets == TRUE)||(CurrentSetup.SequenceEnable == TRUE))
                     NackError = PARAMETER_ERROR;
                  else
                  {
                     if(Value32 >= MinLimit.AbsDist)
                     {
                        if(Value32 <= MaxLimit.AbsDist)
                        { 
                           ActionFlags[4] = TRUE;
                           Params[4] = Value32;
                        }  
                        else
                           NackError = MAX_ERROR;
                     }
                     else
                        NackError = MIN_ERROR;

                  }
                  Host16 += 2;      /* Point to next PARMID */               
               break;

               default:
                  NackError = PARAMETER_ERROR;
               break;
            }   
      }
      if (!NackError)
      {
         /* SET_WELD_TIME was 1st parameter */
         if (ActionFlags[0])
         {
            CurrentPreset.WeldTime = Params[0];                        
            UpdateCurrentPreset(WELDTIME, 0, 0);    /* Save to BattRam */
            CurrentPresetParameterChanged = TRUE;
         }

         /* SET_HOLD_TIME is 2nd parameter */
         if(ActionFlags[1])
            /* value of 0 turns off hold time */
            CurrentPreset.HoldTimeFlag = TRUE;      /* Disable Flag */

         if(ActionFlags[2])
         {
            CurrentPreset.HoldTime = Params[2];
            CurrentPreset.HoldTimeFlag = FALSE;
         }
         UpdateCurrentPreset(HOLDTIME, 0, 0);  /* Save to BattRam */
         CurrentPresetParameterChanged = TRUE;
         /* Peak power is 3rd parameter */
         if(ActionFlags[3])
         {
            CurrentPreset.PeakPwr = Params[3];
            UpdateCurrentPreset(PEAKPOWER, 0, 0);   /* Save to BattRam */
            CurrentPresetParameterChanged = TRUE;
         }
         if(ActionFlags[4])
         {
            CurrentPreset.AbsDist = Params[4];
            UpdateCurrentPreset(ABSOLUTE, 0, 0);   /* Save to BattRam */
            CurrentPresetParameterChanged = TRUE;
         }
      }
      break;

      /* Set -Energy suspect limit */
      case SET_ENERGYMLS:

         ErrorResponseMinLimit = MinLimit.EnergyMLS;
         ErrorResponseMaxLimit = MaxLimit.EnergyMLS;

         if (!Value32)
            /* a value of 0 disables the limit */  
            CurrentPreset.SuspectLimits |= MENERGYBIT;  /* Turn Flag Off   */

         else if(Value32 >= MinLimit.EnergyMLS)
         {
            if(Value32 <= MaxLimit.EnergyMLS)
            {
            CurrentPreset.EnergyMLS = Value32;
            CurrentPreset.SuspectLimits &= (~MENERGYBIT);   /* Turn Flag On    */
            }
            else
            NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ENERGYMLS, 0, 0);  /* Save to BattRam */
      break;


      /* Set +Energy suspect limit */
      case SET_ENERGYPLS:

         ErrorResponseMinLimit = MinLimit.EnergyPLS;
         ErrorResponseMaxLimit = MaxLimit.EnergyPLS;

         if (!Value32)
           /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= PENERGYBIT;  /* Turn Flag Off   */

         else if(Value32 >= MinLimit.EnergyPLS)
         {
            if(Value32 <= MaxLimit.EnergyPLS)
            {
               CurrentPreset.EnergyPLS = Value32;
               CurrentPreset.SuspectLimits &= (~PENERGYBIT);   /* Turn Flag On    */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ENERGYPLS, 0, 0);  /* Save to BattRam */
      break;


      /* Set -Energy reject limit */
      case SET_ENERGYMLR:

         ErrorResponseMinLimit = MinLimit.EnergyMLR;
         ErrorResponseMaxLimit = MaxLimit.EnergyMLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= MENERGYBIT;   /* Turn Flag Off   */

         else if(Value32 >= MinLimit.EnergyMLR)
         {
            if(Value32 <= MaxLimit.EnergyMLR)
            {
               CurrentPreset.EnergyMLR = Value32;
               CurrentPreset.RejectLimits &= (~MENERGYBIT);    /* Turn Flag On    */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ENERGYMLR, 0, 0);   /* Save to BattRam */
      break;


      /* Set +Energy reject limit */
      case SET_ENERGYPLR:

         ErrorResponseMinLimit = MinLimit.EnergyPLR;
         ErrorResponseMaxLimit = MaxLimit.EnergyPLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= PENERGYBIT;   /* Turn Flag Off   */

         else if(Value32 >= MinLimit.EnergyPLR)
         {
            if(Value32 <= MaxLimit.EnergyPLR)
            {
               CurrentPreset.EnergyPLR = Value32;
               CurrentPreset.RejectLimits &= (~PENERGYBIT);    /* Turn Flag On    */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ENERGYPLR, 0, 0);   /* Save to BattRam */
      break;


      /* Set -Time suspect limit */
      case SET_TIMEMLS:

         ErrorResponseMinLimit = MinLimit.TimeMLS;
         ErrorResponseMaxLimit = MaxLimit.TimeMLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= MTIMEBIT;    /* Turn Flag Off   */

         else if(Value32 >= MinLimit.TimeMLS)
         {
            if(Value32 <= MaxLimit.TimeMLS)
            {
               CurrentPreset.TimeMLS = Value32;
               CurrentPreset.SuspectLimits &= (~MTIMEBIT); /* Turn Flag On    */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(SUSPECTLIMITS, 0, 0);   /* Save to BattRam */
      break;


      /* Set +Time suspect limit */
      case SET_TIMEPLS:

         ErrorResponseMinLimit = MinLimit.TimePLS;
         ErrorResponseMaxLimit = MaxLimit.TimePLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= PTIMEBIT;    /* Turn Flag Off   */

         else if(Value32 >= MinLimit.TimePLS)
         {
            if(Value32 <= MaxLimit.TimePLS)
            {
               CurrentPreset.TimePLS = Value32;
               CurrentPreset.SuspectLimits &= (~PTIMEBIT); /* Turn Flag On    */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(SUSPECTLIMITS, 0, 0);   /* Save to BattRam */
      break;


      /* Set -Time reject limit */
      case SET_TIMEMLR:

         ErrorResponseMinLimit = MinLimit.TimeMLR;
         ErrorResponseMaxLimit = MaxLimit.TimeMLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= MTIMEBIT; /* Turn Flag Off   */

         else if(Value32 >= MinLimit.TimeMLR)
         {
            if(Value32 <= MaxLimit.TimeMLR)
            {
               CurrentPreset.TimeMLR = Value32;
               CurrentPreset.RejectLimits &= (~MTIMEBIT);  /* Turn Flag On    */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(REJECTLIMITS, 0, 0);   /* Save to BattRam */
      break;


      /* Set +Time reject limit */
      case SET_TIMEPLR:

         ErrorResponseMinLimit = MinLimit.TimePLR;
         ErrorResponseMaxLimit = MaxLimit.TimePLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= PTIMEBIT; /* Turn Flag Off   */

         else if(Value32 >= MinLimit.TimePLR)
         {
            if(Value32 <= MaxLimit.TimePLR)
            {
               CurrentPreset.TimePLR = Value32;
               CurrentPreset.RejectLimits &= (~PTIMEBIT);  /* Turn Flag On    */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(REJECTLIMITS, 0, 0);   /* Save to BattRam */
      break;


      case START_WELD_DATA:
         if(Source_Task == SERIAL_INTERRUPT)
         {
            /* Request to start or stop sending weld data asynchronously over the link. */
            Host8 = (UINT8 *)DataPointer;
            Value8 = *Host8;
            if(Value8 == STOPASYNCWELDDATA || Value8 == STARTASYNCWELDDATA)
            {
               Host8++;          /* point to send now flag */
               if(!(*Host8 == SENDNOWOFF || *Host8 == SENDNOWON))  /* test for over limit */
                  NackError = PARAMETER_ERROR;
               else {
                  CurrentSetup.SerialPort = COMPUWELD;
                  UpdateCurrentPreset(SENDWELDDATA, 0, 0);

                  if (Value8 == STOPASYNCWELDDATA) {
                     if (*Host8 == SENDNOWON) {
                        i = ConvertWeldData(&FinalResults, AckBuf);
                        LimitChanged = FALSE;
                        NoAckOrNak = TRUE;
                     }
                  }
               }
            }
            else
            NackError = PARAMETER_ERROR;   
         }   
         else if(Source_Task == WELD_MGR)
         {
            /* Request to send weld data over the link. */
            i = ConvertWeldData((WELD_DATA*)DataPointer, AckBuf);
            NoAckOrNak = TRUE;
         }
         else
            NackError = INVALID_SOURCE;
      break;

      case SET_PEAKPOWER_CUTOFF:

         ErrorResponseMinLimit = MinLimit.PeakPwrCutoff;
         ErrorResponseMaxLimit = MaxLimit.PeakPwrCutoff;

         if (!Value32)
            /* a value of 0 disables the cutoff */
            CurrentPreset.PeakPwrCutoffFlag = BIT0;       /* Turn Flag Off */

         else if(Value32 >= MinLimit.PeakPwrCutoff)
         {
            if(Value32 <= MaxLimit.PeakPwrCutoff)
            {
               CurrentPreset.PeakPwrCutoff = Value32;
               CurrentPreset.PeakPwrCutoffFlag = FALSE;      /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(PEAKPOWERCUTOFF, 0, 0);    /* Save to BattRam */
      break;

      case SET_COLLDIST_CUTOFF:

         ErrorResponseMinLimit = MinLimit.ColCutoffDist;
         ErrorResponseMaxLimit = MaxLimit.ColCutoffDist;

         if (!Value32)
            /* a value of 0 disables the cutoff */
            CurrentPreset.ColCutoffFlag = BIT0;     /* Turn Flag Off */

         else if(Value32 >= MinLimit.ColCutoffDist)
         {
            if(Value32 <= MaxLimit.ColCutoffDist)
            {
               CurrentPreset.ColCutoffDist = Value32;
               CurrentPreset.ColCutoffFlag = FALSE;         /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(COLLCUTOFFDIST, 0, 0);    /* Save to BattRam */
      break;


      /* Set -Power Suspect Limit */
      case SET_MPOWER_SLIMIT:

         ErrorResponseMinLimit = MinLimit.PowerMLS;
         ErrorResponseMaxLimit = MaxLimit.PowerMLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= MPKPOWERBIT;/* Turn Flag Off */

         else if (Value32 >= MinLimit.PowerMLS)
         {
            if(Value32 <= MaxLimit.PowerMLS)
            {
               CurrentPreset.PowerMLS = Value32;
               CurrentPreset.SuspectLimits &= (~MPKPOWERBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(POWERMLS, 0, 0);    /* Save to BattRam */
      break;


      /* Set +Power Suspect Limit */
      case SET_PPOWER_SLIMIT:

         ErrorResponseMinLimit = MinLimit.PowerPLS;
         ErrorResponseMaxLimit = MaxLimit.PowerPLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= PPKPOWERBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.PowerPLS)
         {
            if(Value32 <= MaxLimit.PowerPLS)
            {
               CurrentPreset.PowerPLS = Value32;
               CurrentPreset.SuspectLimits &= (~PPKPOWERBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(POWERPLS, 0, 0);    /* Save to BattRam */
      break;


      /* Set -Power Reject Limit */
      case SET_MPOWER_RLIMIT:

         ErrorResponseMinLimit = MinLimit.PowerMLR;
         ErrorResponseMaxLimit = MaxLimit.PowerMLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= MPKPOWERBIT;/* Turn Flag Off */

         else if (Value32 >= MinLimit.PowerMLR)
         {
            if(Value32 <= MaxLimit.PowerMLR)
            {
               CurrentPreset.PowerMLR = Value32;
               CurrentPreset.RejectLimits &= (~MPKPOWERBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(POWERMLR, 0, 0);    /* Save to BattRam */
      break;


      /* Set +Power Reject Limit */
      case SET_PPOWER_RLIMIT:

         ErrorResponseMinLimit = MinLimit.PowerPLR;
         ErrorResponseMaxLimit = MaxLimit.PowerPLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= PPKPOWERBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.PowerPLR)
         {
            if(Value32 <= MaxLimit.PowerPLR)
            {
               CurrentPreset.PowerPLR = Value32;
               CurrentPreset.RejectLimits &= (~PPKPOWERBIT);/* Turn Flag On */
            }
            else
            NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(POWERPLR, 0, 0);    /* Save to BattRam */
      break;


      /* Set -Collapse Suspect Limit */
      case SET_MCOLLAPSE_SLIMIT:

         ErrorResponseMinLimit = MinLimit.ColMLS;
         ErrorResponseMaxLimit = MaxLimit.ColMLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= MCOLDISTBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.ColMLS)
         {
            if(Value32 <= MaxLimit.ColMLS)
            {
               CurrentPreset.ColMLS = Value32;
               CurrentPreset.SuspectLimits &= (~MCOLDISTBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(COLMLS, 0, 0);    /* Save to BattRam */
      break;


      /* Set +Collapse Suspect Limit */
      case SET_PCOLLAPSE_SLIMIT:

         ErrorResponseMinLimit = MinLimit.ColPLS;
         ErrorResponseMaxLimit = MaxLimit.ColPLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= PCOLDISTBIT;    /* Turn Flag Off */

         else if(Value32 >= MinLimit.ColPLS)
         {
            if(Value32 <= MaxLimit.ColPLS)
            {
            CurrentPreset.ColPLS = Value32;
            CurrentPreset.SuspectLimits &= (~PCOLDISTBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(COLPLS, 0, 0);     /* Save to BattRam */
      break;


      /* Set -Collapse Reject Limit */
      case SET_MCOLLAPSE_RLIMIT:

         ErrorResponseMinLimit = MinLimit.ColMLR;
         ErrorResponseMaxLimit = MaxLimit.ColMLR;

         if (!Value32)
            /* a value of 0 disaables the limit */
            CurrentPreset.RejectLimits |= MCOLDISTBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.ColMLR)
         {
            if(Value32 <= MaxLimit.ColMLR)
            {
               CurrentPreset.ColMLR = Value32;
               CurrentPreset.RejectLimits &= (~MCOLDISTBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(COLMLR, 0, 0);    /* Save to BattRam */
      break;


      /* Set +Collapse Reject Limit */
      case SET_PCOLLAPSE_RLIMIT:

         ErrorResponseMinLimit = MinLimit.ColPLR;
         ErrorResponseMaxLimit = MaxLimit.ColPLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= PCOLDISTBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.ColPLR)
         {
            if(Value32 <= MaxLimit.ColPLR)
            {
               CurrentPreset.ColPLR = Value32;
               CurrentPreset.RejectLimits &= (~PCOLDISTBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(COLPLR, 0, 0);    /* Save to BattRam */
      break;


      /* Set -Absolute Suspect Limit */
      case SET_MABSOLUTE_SLIMIT:

         ErrorResponseMinLimit = MinLimit.AbsMLS;
         ErrorResponseMaxLimit = MaxLimit.AbsMLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= MABSDISTBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.AbsMLS)
         {
            if(Value32 <= MaxLimit.AbsMLS)
            {
               CurrentPreset.AbsMLS = Value32;
               CurrentPreset.SuspectLimits &= (~MABSDISTBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ABSMLS, 0, 0);    /* Save to BattRam */
      break;

      /* Set +Absolute Suspect Limit */
      case SET_PABSOLUTE_SLIMIT:

         ErrorResponseMinLimit = MinLimit.AbsPLS;
         ErrorResponseMaxLimit = MaxLimit.AbsPLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= PABSDISTBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.AbsPLS)
         {
            if(Value32 <= MaxLimit.AbsPLS)
            {
               CurrentPreset.AbsPLS = Value32;
               CurrentPreset.SuspectLimits &= (~PABSDISTBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else 
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ABSPLS, 0, 0);   /* Save to BattRam */
      break;

      /* Set -Absolute Reject Limit */
      case SET_MABSOLUTE_RLIMIT:

         ErrorResponseMinLimit = MinLimit.AbsMLR;
         ErrorResponseMaxLimit = MaxLimit.AbsMLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= MABSDISTBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.AbsMLR)
         {
            if(Value32 <= MaxLimit.AbsMLR)
            {
               CurrentPreset.AbsMLR = Value32;
               CurrentPreset.RejectLimits &= (~MABSDISTBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ABSMLR, 0, 0);    /* Save to BattRam */

      break;

      /* Set +Absolute Reject Limit */
      case SET_PABSOLUTE_RLIMIT:

         ErrorResponseMinLimit = MinLimit.AbsPLR;
         ErrorResponseMaxLimit = MaxLimit.AbsPLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= PABSDISTBIT;/* Turn Flag Off */

         else if(Value32 >= MinLimit.AbsPLR)
         {
            if(Value32 <= MaxLimit.AbsPLR)
            {
               CurrentPreset.AbsPLR = Value32;
               CurrentPreset.RejectLimits &= (~PABSDISTBIT);/* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ABSPLR, 0, 0);    /* Save to BattRam */
      break;

      /* Set -Trigger Distance Suspect Limit */
      case SET_MTRIGDIST_SLIMIT:

         ErrorResponseMinLimit = MinLimit.TrsDistMLS;
         ErrorResponseMaxLimit = MaxLimit.TrsDistMLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= MTRIGDISTBIT; /* Turn Flag Off */

         else if(Value32 >= MinLimit.TrsDistMLS)
         {
            if(Value32 <= MaxLimit.TrsDistMLS)
            {
               CurrentPreset.TrsDistMLS = Value32;
               CurrentPreset.SuspectLimits &= (~MTRIGDISTBIT);  /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(TRSDISTMLS, 0, 0);    /* Save to BattRam */
      break;

      /* Set +Trigger Distance Suspect Limit */
      case SET_PTRIGDIST_SLIMIT:

         ErrorResponseMinLimit = MinLimit.TrsDistPLS;
         ErrorResponseMaxLimit = MaxLimit.TrsDistPLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= PTRIGDISTBIT; /* Turn Flag Off */

         else if(Value32 >= MinLimit.TrsDistPLS)
         {
            if(Value32 <= MaxLimit.TrsDistPLS)
            {
               CurrentPreset.TrsDistPLS = Value32;
               CurrentPreset.SuspectLimits &= (~PTRIGDISTBIT); /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
         UpdateCurrentPreset(TRSDISTPLS, 0, 0);    /* Save to BattRam */
      break;

      /* Set -Trigger Distance Reject Limit */
      case SET_MTRIGDIST_RLIMIT:

         ErrorResponseMinLimit = MinLimit.TrsDistMLR;
         ErrorResponseMaxLimit = MaxLimit.TrsDistMLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= MTRIGDISTBIT;  /* Turn Flag Off */

         else if(Value32 >= MinLimit.TrsDistMLR)
         {
            if(Value32 <= MaxLimit.TrsDistMLR)
            {
               CurrentPreset.TrsDistMLR = Value32;
               CurrentPreset.RejectLimits &= (~MTRIGDISTBIT); /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(TRSDISTMLR, 0, 0);    /* Save to BattRam */
      break;

      /* Set +Trigger Distance Reject Limit */
      case SET_PTRIGDIST_RLIMIT:

         ErrorResponseMinLimit = MinLimit.TrsDistPLR;
         ErrorResponseMaxLimit = MaxLimit.TrsDistPLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= PTRIGDISTBIT;  /* Turn Flag Off */

         else if(Value32 >= MinLimit.TrsDistPLR)
         {
            if(Value32 <= MaxLimit.TrsDistPLR)
            {
               CurrentPreset.TrsDistPLR = Value32;
               CurrentPreset.RejectLimits &= (~PTRIGDISTBIT); /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(TRSDISTPLR, 0, 0);    /* Save to BattRam */
      break;

      /* Set -Weld Force Suspect Limit */
      case SET_MMAXFORCE_SLIMIT:

         ErrorResponseMinLimit = MinLimit.WeldForceMLS;
         ErrorResponseMaxLimit = MaxLimit.WeldForceMLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= MFORCEBIT;  /* Turn Flag Off */

         else if(Value32 >= MinLimit.WeldForceMLS)
         {
            if(Value32 <= MaxLimit.WeldForceMLS)
            {
               CurrentPreset.WeldForceMLS = Value32;
               CurrentPreset.SuspectLimits &= (~MFORCEBIT);  /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(MAXFORCEMLS, 0, 0);    /* Save to BattRam */
      break;

      /* Set +Weld Force Suspect Limit */
      case SET_PMAXFORCE_SLIMIT:

         ErrorResponseMinLimit = MinLimit.WeldForcePLS;
         ErrorResponseMaxLimit = MaxLimit.WeldForcePLS;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.SuspectLimits |= PFORCEBIT;  /* Turn Flag Off */

         else if(Value32 >= MinLimit.WeldForcePLS)
         {
            if(Value32 <= MaxLimit.WeldForcePLS)
            {
               CurrentPreset.WeldForcePLS = Value32;
               CurrentPreset.SuspectLimits &= (~PFORCEBIT); /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(MAXFORCEPLS, 0, 0);    /* Save to BattRam */
      break;

      /* Set -Weld Force Reject Limit */
      case SET_MMAXFORCE_RLIMIT:

         ErrorResponseMinLimit = MinLimit.WeldForceMLR;
         ErrorResponseMaxLimit = MaxLimit.WeldForceMLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= MFORCEBIT;  /* Turn Flag Off */

         else if(Value32 >= MinLimit.WeldForceMLR)
         {
            if(Value32 <= MaxLimit.WeldForceMLR)
            {
               CurrentPreset.WeldForceMLR = Value32;
               CurrentPreset.RejectLimits &= (~MFORCEBIT); /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(MAXFORCEMLR, 0, 0);    /* Save to BattRam */
      break;

      /* Set +Weld Force Reject Limit */
      case SET_PMAXFORCE_RLIMIT:

         ErrorResponseMinLimit = MinLimit.WeldForcePLR;
         ErrorResponseMaxLimit = MaxLimit.WeldForcePLR;

         if (!Value32)
            /* a value of 0 disables the limit */
            CurrentPreset.RejectLimits |= PFORCEBIT;  /* Turn Flag Off */

         else if(Value32 >= MinLimit.WeldForcePLR)
         {
            if(Value32 <= MaxLimit.WeldForcePLR)
            {
               CurrentPreset.WeldForcePLR = Value32;
               CurrentPreset.RejectLimits &= (~PFORCEBIT); /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(MAXFORCEPLR, 0, 0);    /* Save to BattRam */
      break;

    /* Set Actuator Clear */
      case SET_ACTUATOR_CLEAR:

         ErrorResponseMinLimit = MinLimit.ActClrDistance;
         ErrorResponseMaxLimit = MaxLimit.ActClrDistance;

         if (!Value32)
            /* a value of 0 disables the function */
            CurrentPreset.ActClrFlag = FALSE;

         else if(Value32 >= MinLimit.ActClrDistance)
         {
            if(Value32 <= MaxLimit.ActClrDistance)
            {
            CurrentPreset.ActClrDistance = Value32;
            CurrentPreset.ActClrFlag = TRUE;   /* Turn Flag On */
            }
            else
               NackError = MAX_ERROR;
         }
         else
            NackError = MIN_ERROR;

         if(!NackError)
            UpdateCurrentPreset(ACTCLEARDIST, 0, 0);    /* Save to BattRam */
      break;

      case CHECKSUM_ERROR:    /* Bad data received */
         NackError = BAD_CHECKSUM;
      break;

      /* SPECIAL BRANSON COMMANDS */

      case ONBOARD_DIAGNOSTICS:          /* Special host command to start */
         OnboardDiag = TRUE;             /* diagnostics through the serial port */
      break;                                   

      case SET_PS_SERIALNUMBER:
         /* Point to serial number */
         Host8 = (UINT8 *) DataPointer;
         /* Test serial number for printable ascii */
         for (i=0; i<SERIALLENGTH; i++)
         {
            if(Host8[i] < ' ') 
            {
               NackError = PARAMETER_ERROR;
               break;
            }
         }

         if(!NackError)
         {
            /* Copy serial number */
            for(i=0; i<SERIALLENGTH; i++)
            CurrentSetup.PSSerialNumber[i] = Host8[i];  
            StorePSSerialNumber();
            GetSerialNumbers();
            SystemParameterChgdFlag = TRUE;
           
         }
      break;

      case SET_PS_MODELNUMBER:
         /* Load authorization code */
         Host8 = (UINT8 *)DataPointer;
         Value16 = (Host8[3] << 8) + Host8[4];
         if (Value16 != ComputeAuthorization())
            NackError = INVALID_AUTH_CODE;
         else
         {
            if(DUPS_Info.DUPSFlag != TRUE)
            {
               Host16 = (UINT16 *) DataPointer;
               Value16 = *Host16;
               Value8 = Host8[2];
               /* use switch to check for legal power supply wattage values */
               switch(Value16)
               {
                  case 200:            /*  200W */
                  case 400:            /*  400W */
                  case 800:            /*  800W */
                  case 1100:           /* 1100W */
                  case 1500:           /* 1500W */
                  case 2200:           /* 2200W */
                  case 3300:           /* 3300W */
                  case 4000:           /* 4000W */
                  case 6000:           /* 6000W */
                  break;
                  default:
                     NackError = PARAMETER_ERROR;
                  break;       
               }

               /* test for legal frequency designator */
               switch(Value8)
               {
                  case FREQ15KHZ:
                  case FREQ20KHZ:
                  case FREQ30KHZ:
                  case FREQ40KHZ:
                  case FREQ50KHZ:
                  case FREQ60KHZ:
                  break;
                  default:
                     NackError = PARAMETER_ERROR;
                  break;
               }

               if(!NackError)
               {
                  CurrentSetup.PSWatt = Value16;
                  CurrentSetup.PSFreq = Value8;
                  StorePSWattage();
                  StorePSFrequency();
                  GetPowerSupplyInfo();
               }
            }
            else
               NackError = PARAMETER_ERROR;
         }
      break;

      case SET_CONTROLLEVEL:
         Host16 = (UINT16 *) DataPointer;
         Host16++;           /* point to authorization code */
         Value16 = *Host16;
         if (Value16 == ComputeAuthorization())
         {
            /* Test for valid control level value */
            Host16--;        /* point to control level */ 
            Value16 = *Host16;
            switch (Value16)
            {
               case LEVEL_t:
               case LEVEL_e:
               case LEVEL_a:
               case LEVEL_ea:
               case LEVEL_d:  
               case LEVEL_f:
               case LEVEL_TEST:
                  DepotFlag->IsADepot = FALSE;
                  CurrentSetup.ControlLevel = Value16;
               break;
               case LEVEL_DEPOT:
                  DepotFlag->WasADepot = TRUE;
                  DepotFlag->IsADepot  = TRUE;
                  CurrentSetup.ControlLevel = LEVEL_t;
               break;

               default:
                  NackError = PARAMETER_ERROR;
               break;
            } 
         }
         else
            NackError = INVALID_AUTH_CODE;

         if(!NackError)
         {
            StorePSControlLevel();
            ColdStartPlus();
            GetControlLevel();
            SystemParameterChgdFlag = TRUE;
         }
      break;   

      case SET_ACT_SERIALNUMBER:
         Host8 = (UINT8 *) DataPointer;
         Count = strlen((SINT8 *) Host8);
         if(Count < MAXSERIALNUM)
         {
            strcpy(CurrentSetup.ActSerialNumber, (SINT8 *) Host8);
            SaveActSerialNum();
         }
         else
            NackError = PARAMETER_ERROR;
      break;

      case SET_ACT_MODELNUMBER:
         /* Load authorization code */
         Host8 = (UINT8 *)DataPointer;
         Value16 = (Host8[1] << 8) + Host8[2];
         if (Value16 != ComputeAuthorization())
            NackError = INVALID_AUTH_CODE;
         else
         {
            Value8 = *Host8;

            switch(Value8)
            {
               case 1:
                  CurrentSetup.Actuator=AE; // ae
               break;
               case 2: 
                  CurrentSetup.Actuator=AO; // ao
               break;
               case 3: 
                  CurrentSetup.Actuator=AED; // aed
               break;
               case 4:
                  CurrentSetup.Actuator=AOD; // aod
               break;
               case 5:   
                  CurrentSetup.Actuator=AEF; // aef
               break;
               case 6: 
                  CurrentSetup.Actuator=AOF; // aof
               break;
			   case 7:
				  CurrentSetup.Actuator=MICRO; // MICRO
               break;
               default:
                  NackError = PARAMETER_ERROR;
               break;
            }
            if(!NackError)
            {
               SetActId((UINT16) Value8);  // Should be a num between 1 to 6 
               SystemParameterChgdFlag = TRUE;
            }
         }
      break;

      case RESET_PSLIFETIMECOUNTER:
         CurrentSetup.PSLifetime = 0;
         StorePSLifeTimeCount();
      break;

      case RESET_OVERLOADCOUNTER:
         CurrentSetup.Overload = 0;
      break;

      case RESET_GENALARMCOUNTER:
         CurrentSetup.GenAlarmCount = 0;
      break;

      case SET_ACTUATOR_CYLINDERDIAMETER:
         /* Load authorization code */
         Host8 = (UINT8 *)DataPointer;            
         Value16 = (Host8[2] << 8) + Host8[3]; 
         if (Value16 != ComputeAuthorization())
            NackError = INVALID_AUTH_CODE;
         else
         {
            Host16 = (UINT16 *) DataPointer;
            Value16 = *Host16;
            /* use switch to check for legal values */
            switch(Value16)
            {
               case CUSTOMSIZE:
               case SIZE1_5:
               case SIZE2_0:
               case SIZE2_5:
               case SIZE3_0:
               case SIZE3_25:
               case SIZE_40:
               case SIZE_50:
               case SIZE_63:
               case SIZE_80:
                  CurrentSetup.CylinDiameter = Value16;
                  SetCylinderIndex();
               break;

               default:
                  NackError = PARAMETER_ERROR;
               break;
            }
         }
      break;

      case SET_ACTUATOR_STROKELENGTH:
         /* Load authorization code */
         Host8 = (UINT8 *)DataPointer;
         Value16 = (Host8[2] << 8) + Host8[3];             
         if (Value16 != ComputeAuthorization())
            NackError = INVALID_AUTH_CODE;
         else
         {
            Host16 = (UINT16 *) DataPointer;
            Value16 = *Host16;
            /* use switch to check for legal values */
            switch(Value16)
            {
               case CUSTOMLEN:
               case LENGTH_4:
               case LENGTH_5:
               case LENGTH_6:
               case LENGTH_2:
               case LENGTH_8:
               case LENGTH_80:
               case LENGTH_100:
               case LENGTH_125:
               //case LENGTH_160:
               case LENGTH_50:
                  CurrentSetup.StrokeLen = Value16;
                  SetStrokeLenIndex();
               break;

               default:
                  NackError = PARAMETER_ERROR;
               break;
            }
         }
      break;

      case UPLOAD_REMOTE_CONFIG_PARMS:

         for (i=0; i<15; i++) AckBuf[i] = 0;
         AckBuf[0] = ACK;
         AckBuf[1] = DLE;
         AckBuf[2] = STX;
         /* fill in count */
         AckBuf[3] = 0;
         AckBuf[4] = 25;
         /* fill in function */
         AckBuf[5] = (UINT8)(Function>>8);
         AckBuf[6] = (UINT8)Function;
         /* fill in PS serial number */
         for (i=7; i<SERIALLENGTH+7; i++)
            AckBuf[i] = CurrentSetup.PSSerialNumber[i-7];
         /* fill in SWVersion Number */
         for (i=19; i<24; i++) 
            AckBuf[i] = 0;
         /* fill in control level */
         AckBuf[24] = 0;
         if(DepotFlag->IsADepot)
            AckBuf[25] = (UINT8)LEVEL_DEPOT;
         else
            AckBuf[25] = (UINT8)CurrentSetup.ControlLevel; 
         /* fill in Weld Data Flag */
         AckBuf[26] = 0;
         AckBuf[27] = (UINT8)CurrentSetup.SerialPort;
         /* fill in checksum */
         AckBuf[28] = 0;
         for (i=3; i<28; i++) AckBuf[28] ^= AckBuf[i];
         AckBuf[29] = DLE;
         AckBuf[30] = ETX;
         i = UPLOAD_REMOTE_CONFIG_PARMS_SIZE; 
         NoAckOrNak = TRUE;

      break;      /* continue while forever */

      case SEND_QUALITYLIMITS_DATA :   // Send QualityLimits Info
         if (CommandCount == QUALITYLIMITS_DATA_COMMAND_SIZE) {
            Host8 = (UINT8 *)DataPointer;
            Value8 = *Host8;
            len = SendQualityLimitsData(SendMenuResponse,Value8);
            if (!NackError)
            {
               i = CreateACK(AckBuf, Function, SendMenuResponse, len);
               NoAckOrNak = TRUE;			  
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      default:
         /* unknown opcode */
         NackError = INVALID_OPCODE;
      break;
   }       /* opcode switch */

   if (NoAckOrNak == FALSE) {
      if (NackError)      
      {
         /* Generate NACK error response */
         i = XmitNack ( Function, SubFunction, NackError,
         ErrorResponseMinLimit, ErrorResponseMaxLimit, AckBuf );
      }
      else 
      {
         SendFakeKeyPress(UPDATEDISPLAY);
         AckBuf[0] = ACK;
         AckBuf[1] = DLE;
         AckBuf[2] = STX;
         /* fill in count */
         AckBuf[3] = 0;
         AckBuf[4] = 5;
         /* fill in function */
         AckBuf[5] = (UINT8)(Function>>8);
         AckBuf[6] = (UINT8)Function;
         /* fill in DisplayLock */
         AckBuf[7] = (UINT8)Inp.DisplayLockFlag;
         /* fill in checksum */
         AckBuf[8] = 0;
         for (i=3; i<8; i++) AckBuf[8] ^= AckBuf[i];
         AckBuf[9] = DLE;
         AckBuf[10] = ETX;
         i = ACK_REPLY_SIZE;
      }
   }

   return i;
}

UINT16 ProcessVGAHostCommand(UINT32 Value32, UINT16 Function, UINT8  *DataPointer,
                           UINT16 CommandCount)
/****************************************************************************/
/*Description:-                                                             */
/* This function builds reply for VGA hostcommand and writes data in buffer */
/*Input Parameters:-                                                        */
/* Value32: First four data bytes are mostly pointer value                  */
/* Function: Host command Function number                                   */
/* Datapointer: Pointer to the host command data                            */
/* CommandCount: Nos of data bytes in a command                             */
/*Returns length of the bytes written to the buffer                         */  
/****************************************************************************/

{
   FP_KEY_PRESSED_MSG FpkpQueue;
   UINT32          FpkpQid;
   UINT32          PsosStatus;

   UINT16         Position;
   UINT16          i, j;
   UINT16          NoAckOrNak = FALSE;
   UINT8           Value8;
   UINT16          Value16;
   UINT16          RadioValue;
   SINT32          VarValue;
   UINT16          VarFormat;
   UINT16          VarDsblFlag;
   UINT8           *Host8;
   UINT16          *Host16;
   
   static UINT8    SendMenuResponse[256];
   PRESET_COMPRESSED  *TempPreset;
   UINT8          *TempPtr;
   UINT16          len; 
   SINT8           LineBuffer[QVGA_LINESIZE];
   UINT16          SubFunction;
   UINT16          StructID;
   UINT8 TempMenuNxtPointer;

   PRESET_COMPRESSED TempPresetMicrons;
   UINT32 BattramStatus;

   i = 0;
   SubFunction = 0;
   PsosStatus = q_ident(FPKP_Q, Q_NODE_0, &FpkpQid);

   switch (Function)
   {

      case SEND_MENU_PTRS :    // Send Bottom button pointers and Initial Info
         if (CommandCount == MENU_PTRS_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            for(i = 0; i<SBC_SW_VERSION_LENTGH; i++){
               SBCVersionLabel[i]= Host8[i];
            }
            SBCVersionLabel[i] =  '\0';
            len = SendMenuPtrs(SendMenuResponse);
            i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
            NoAckOrNak = TRUE;
         }
          else
             NackError = ILLEGAL_COMMAND;
      break;

      case START_RUNCYCLE :    // Start state machine
         if (CommandCount == START_RUNCYCLE_COMMAND_SIZE)
         {
            SBCReadyFlag = TRUE;
            if(WindowSetupFlag)
            {
               WindowSetupFlag = FALSE;
               ReadyFlag = VGA_ReadyFlag;
               ResetStateMachine();
               StartStateMachine();
               SetReady();
            }
            else
            {
               StartStateMachine();
            }
         }
         else
             NackError = ILLEGAL_COMMAND;
      break;

      case SEND_CONDN_VAR : //Send condition Variable
         if(CommandCount == SEND_CONDN_VAR_SIZE){
            len = SendConditionVariable(SendMenuResponse);
            i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
            NoAckOrNak = TRUE;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;


      case SEND_STRUCTURE_DATA:
         if(CommandCount == SEND_STRUCTURE_DATA_SIZE){
            Host8 = (UINT8 *)DataPointer;
            StructID = ((UINT16)(*Host8)<<8)+ (UINT16)(*(Host8+1));
            TempMenuNxtPointer = (UINT8 )(*(Host8+2));
            if(StructID > MAX_STRUCT)
            {
               len=0;
            }
            else
            {
               for(Position = 0; Position< MAX_STRUCT; Position++){
                  if(Map[Position].Struct_ID == StructID)
                     break;
                  }
               if(Position >= MAX_STRUCT )
                  NackError = ILLEGAL_COMMAND;
               else{
               if(StructID == MENU_SYNC) /*Menu Sync in Calibration*/
                  MenuNxtPointer = TempMenuNxtPointer;
               GlobalCommandID=StructID;
               len = XMLDataProcess(SendMenuResponse,Position,StructID);
               }
            }
            if(!NackError)
            {
               i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
               NoAckOrNak = TRUE;
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
         break;

      case RECEIVE_STRUCTURE_DATA:
         if(CommandCount <= RECEIVE_STRUCTURE_DATA_SIZE)
         {
           Host8 = (UINT8 *)DataPointer;
           StructID = ((UINT16)(*Host8)<<8)+ (UINT16)(*(Host8+1));
            
           len=0;
            if(StructID <= MAX_STRUCT)
            {
               for(Position = 0; Position< MAX_STRUCT; Position++)
               {
                  if(Map[Position].Struct_ID == StructID)
                     break;
               }
               if(Position >= MAX_STRUCT )
                  NackError = ILLEGAL_COMMAND;
               else{
               GlobalCommandID=StructID;
               len += XMLDataResponse(Position,&Host8[2],SendMenuResponse,StructID);
               }
               if(!NackError)
               {
                i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
                NoAckOrNak = TRUE;
               }
               
            }
            else
               NackError = ILLEGAL_COMMAND;
       }
       else
          NackError = ILLEGAL_COMMAND;
       break;

      case SEND_MIN_MAX_COMMAND:
         if(CommandCount == SEND_MIN_MAX_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            StructID = ((UINT16)(*Host8)<<8)+ (UINT16)(*(Host8+1));
            if(StructID <= MAX_STRUCT)
            {
               for(Position = 0; Position< MAX_STRUCT; Position++)
               {
                  if(MinMap[Position].Struct_ID == StructID)
                     break;
               }
               if(Position >= MAX_STRUCT )
                  NackError = ILLEGAL_COMMAND;
               else{
               GlobalCommandID=StructID;
               len = SendMinMaxData(SendMenuResponse,Position);
               }
               if (!NackError)
               {
                  i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
                  NoAckOrNak = TRUE;
               }
            }
            else 
               NackError = ILLEGAL_COMMAND;
         }
         else
            NackError = ILLEGAL_COMMAND;
        break;

      case BOTTOMHALF_COMMAND :
         if(CommandCount == BOTTOMHALF_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            StructID = ((UINT16)(*Host8)<<8)+ (UINT16)(*(Host8+1));
            if(StructID <= MAX_STRUCT)
            {
            len = SendBottomHalfData(SendMenuResponse,StructID);
            if (!NackError)
            {
               i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
               NoAckOrNak = TRUE;
            }
            }
            else
               NackError = ILLEGAL_COMMAND;                  
         }
         else
            NackError = ILLEGAL_COMMAND;
        break;


      case WELD_DATA_COMMAND:   // Send Weld data and graph data command
         if(CommandCount == WELD_DATA_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            if((Host8[0]==WELD_HISTORY)&&(Host8[1]==WELD_HISTORY_COUNT)&&
            (WeldState != PREREADYSTATE) && (WeldState != READYSTATE))
            {
               NackError = WELDER_PROCESS_ERROR;
               ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
               ErrorResponseMaxLimit = 0;
            }
            else
            {
               len = ProcessWeldGraphValue(Host8[0], Host8[1]);
               if (!NackError)
               {
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               }
               else
                  NackError = ILLEGAL_COMMAND;
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;
  
      case VGA_POLLING_COMMAND:
         if(CommandCount == POLLING_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            if (Host8[0] & VGA_PRINTERON)
               VGAPrinterStatus = TRUE;  // Printer ON           
            else
               VGAPrinterStatus = FALSE; // Printer offline

            if ((Host8[0] & VGA_SCREENCALIB) && !(VGA_ScreenCalibFlag))   
            {
               VGA_ScreenCalibFlag = TRUE;
               VGA_ReadyFlag = ReadyFlag;
               ReadyFlag = FALSE;
               ResetStateMachine();
               ClearReady();
            }
            else if (!(Host8[0] & VGA_SCREENCALIB) && (VGA_ScreenCalibFlag))
            {
               VGA_ScreenCalibFlag = FALSE;
               ReadyFlag = VGA_ReadyFlag;
               ResetStateMachine();
               StartStateMachine();
               SetReady();
            }
            if(Host8[0] & VGA_USBFULLALARM)
               VGAUSBFullStatus = TRUE;
            else
               VGAUSBFullStatus = FALSE;
            

            len = VGASendPollingData(SendMenuResponse);
            i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
            NoAckOrNak = TRUE;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case PROCESS_ALARM_ITEM :    // Process Alarm Item
         if(CommandCount == PROCESS_ALARM_ITEM_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            StructID = ((UINT16)(*Host8)<<8)+ (UINT16)(*(Host8+1)); 
            ProcessAlarmItems (StructID);
            len = 0;
            if (!NackError)
            {
               i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
               NoAckOrNak = TRUE;
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case SEND_ALARMBIT_COMMAND :  // Send alarm bit  status
         if(CommandCount == SEND_ALARMBIT_COMMAND_SIZE)
         {
            VGAAlarmReset(1);
            len = SendAlarmBits(SendMenuResponse);
            i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
            NoAckOrNak = TRUE;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case SEND_WELDER_STATE_CMD :  // Send Weld State
         if(CommandCount == SEND_WELDER_STATE_COMMAND_SIZE)
         {
            len = SendWeldState(SendMenuResponse);
            i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
            NoAckOrNak = TRUE;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case SEND_START_WELD_DATA :  // Send Weld Start Data
         if(CommandCount == SEND_START_WELD_DATA_COMMAND_SIZE)
         {
            i = ConvertWeldData(&FinalResults, VGAAckBuf);
            LimitChanged = FALSE;
            NoAckOrNak = TRUE;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case SEND_SETUPPRINT_DATA :  // Send Weld Start Data
         if(CommandCount == SEND_SETUPPRINT_DATA_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            switch (Host8[0])
            {
               case 1 : 
                  len = SystemPresetReport1(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

               case 2 : 
                  len = SystemPresetReport2(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

               case 3 : 
                  len = SystemPresetReport3(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

               case 4 : 
                  len = SystemPresetReport4(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

               case 5 : 
                  len = DupsPresetReport1(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

               case 6 : 
                  len = DupsPresetReport2(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

              case 7 : 
                  len = VGAWeldDataInfo(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

               case 8 : 
                  len = VGAPrintGraphInfo(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

               /*case 9 : 
                  len = PrintHSInfo(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;*/

               case 10 : 
                  len = PrintSeqPresetInfo(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;

               case 11 : 
                  len = SystemPresetReport5(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  NoAckOrNak = TRUE;
               break;
            }   
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case SEND_PRINT_PARAM :  // Send Print Parameters
         if(CommandCount == SEND_PRINT_PARAM_COMMAND_SIZE)
         {
            len = VGAPrintParameters(SendMenuResponse);
            i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
            NoAckOrNak = TRUE;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case VGADOWNLOAD_PRESET: /* Copy the data to HostPreset structure.*/
         if((CommandCount == DOWNLOADCOMMAND_SIZE+1) ||
         (CommandCount == DOWNLOADDUPS_SIZE+1))
         {
            if (((CommandCount == DOWNLOADCOMMAND_SIZE+1) && CheckForDups()) ||
            ((CommandCount == DOWNLOADDUPS_SIZE+1) && (!CheckForDups())))
            {
               NackError = WELDER_PROCESS_ERROR;   
               ErrorResponseMinLimit = PS_MISMATCH;
               ErrorResponseMaxLimit = 0;                                                 
            }
            Host8 = (UINT8 *)DataPointer;
            Value8 = *Host8;
            Host8++;
            if (CheckForDups())
            { 
               Value16 = DUPS_FindDUPS4COP((UINT16)Value8);
               if(Value16 == DUPS_PARAMSETUNDEF)
                  Value16 = DUPS_SetDUPSParamSet((UINT16)Value8);
               if(Value16 != DUPS_PARAMSETUNDEF)
               {
                  for(j = 0; j < DUPS_PARAMSETNAMELEN; j++)
                     DUPS_HostParamSetName[j] = *Host8++;   

                  TempPtr =  (UINT8 *) &DUPS_HostParamSet;
                  memcpy(TempPtr, Host8, sizeof(DUPS_CURRENTPARAMSET));   

                  Host8 += sizeof(DUPS_CURRENTPARAMSET);
                  if (!(DUPS_HostDownloadParamSet((UINT8) Value16)))
                  {
                     NackError = WELDER_PROCESS_ERROR;   
                     ErrorResponseMinLimit = DUPS_NOT_DOWNLOADED;
                     ErrorResponseMaxLimit = 0;                                                 
                  }
               }
               else
               {
                  NackError = WELDER_PROCESS_ERROR;   
                  ErrorResponseMinLimit = DUPS_NOT_AVAILABLE;
                  ErrorResponseMaxLimit = 0;                                                 
               }
            }      
            if (NackError != WELDER_PROCESS_ERROR)
            {
               TempPtr =  (UINT8 *) PresetAddress[Value8];
               memcpy(TempPtr, Host8, sizeof(PRESET_COMPRESSED));
               TempPreset = (PRESET_COMPRESSED *)PresetAddress[Value8];
               TempPreset->DUPSPreset = Value16;
               GetPresetNames(); 
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case VGAUPLOAD_PRESET:
         if(CommandCount == UPLOADCOMMAND_SIZE+1)
         {
            Host8 = (UINT8 *)DataPointer;
            Value8 = *Host8;
            /*Check if DUPS parameter uploaded*/
            if (CheckForDups())
            {
               if (!DUPS_HostUploadParamSet(Value8))
               {
                  NackError = WELDER_PROCESS_ERROR;   
                  ErrorResponseMinLimit = DUPS_NOT_UPLOADED;
                  ErrorResponseMaxLimit = 0;                                                 
               }
            }
            if (NackError != WELDER_PROCESS_ERROR)
            {
               i = 0;
               VGAAckBuf[i++] = ACK;
               VGAAckBuf[i++] = DLE;
               VGAAckBuf[i++] = STX;
               /* Increment index over byte count */
               i += 2;
               /* fill in function */
               VGAAckBuf[i++] = (UINT8)(Function >> 8);
               VGAAckBuf[i++] = (UINT8)Function;
               /* fill in display lock */
               VGAAckBuf[i++] = (UINT8)Inp.DisplayLockFlag;

               if (CheckForDups())
               {
                  /*Fill the DUPS Preset Name*/
                  for(j = 0; j < DUPS_PARAMSETNAMELEN; j++)
                  VGAAckBuf[i++] = DUPS_HostParamSetName[j];   

                  TempPtr = (UINT8 *) &DUPS_HostParamSet;
                  /*Fill the DUPS Preset Data*/
                  for(j = 0; j < sizeof(DUPS_CURRENTPARAMSET); j++)
                     VGAAckBuf[i++] = *TempPtr++;   
               }
               TempPtr = (UINT8 *) PresetAddress[Value8];
               /*Fill the Preset Data*/
               for(j = 0; j < sizeof(PRESET_COMPRESSED); j++)
                  VGAAckBuf[i++] = *TempPtr++;   
               /* fill in byte count */
               VGAAckBuf[3] = (UINT8)((i-3)>>8);
               VGAAckBuf[4] = (UINT8) (i-3);   
               /* compute checksum */
               VGAAckBuf[i] = 0;
               for (j=3; j<i; j++)
                  VGAAckBuf[i] ^= VGAAckBuf[j];
               i++;
               /* add DLE, ETX to message */
               VGAAckBuf[i++] = DLE;
               VGAAckBuf[i++] = ETX;
               NoAckOrNak = TRUE;
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;


      case PMC_COMMAND :  // Process PMC feature related commands
         if(CommandCount == PMC_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            if(Host8[0] == SENDPMCDATA)
            {
               len = SendPMCValue(&VGAAckBuf[8]);   //Send PMC graph data
               i = CreateSameBufferACK(VGAAckBuf, Function, len);
               NoAckOrNak = TRUE;
            } 
            else
               NackError = ILLEGAL_COMMAND;
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case VGA_ERRORBEEP_COMMAND :  // Produce Error beep
         if(CommandCount == VGA_ERRORBEEP_COMMAND_SIZE)
            Beep(ERRORBEEP);
         else
          NackError = ILLEGAL_COMMAND;
      break;

      case VGA_PRINTERROR_COMMAND :  // Log Printer offline error
         if(CommandCount == VGA_PRINTERROR_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            if  (Host8[0] & BIT0)
            {
               VGAPrinterOfflineFlag = TRUE;
               RecordSetupAlarm(SE270);	   			  
            }

            if  (Host8[0] & BIT1)
            {
               VGAUSBOfflineFlag = TRUE;
               RecordAlarm(EQ27);
            }
            if  (Host8[0] & BIT2)
            {
               VGAUSBFullFlag = TRUE;
               RecordAlarm(EQ13);
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;
      
      case PSPRESET_COMMAND: /* Copy the data to VIEWPreset structure.*/
         if(CommandCount == PSPRESET_COMMAND_SIZE)
         {
            Host8 = (UINT8 *)DataPointer;
            Host8++;
            Value8 = *Host8++;
            if (CheckForDups())
            { 
               if (!DUPS_HostUploadParamSet(Value8))
               {
               NackError = WELDER_PROCESS_ERROR;   
               ErrorResponseMinLimit = DUPS_NOT_UPLOADED;
               ErrorResponseMaxLimit = 0; 
               }
               else
               ViewDupsPresent = TRUE; 
            }      
            if (NackError != WELDER_PROCESS_ERROR)
            {
               TempPtr =  (UINT8 *) PresetAddress[Value8];
               memcpy((UINT8 *)  &HostPreset, TempPtr , sizeof(PRESET_COMPRESSED));
               RecallViewCompressedPreset(&HostPreset);
               len = SystemViewPresetReport(&VGAAckBuf[8]);
               i = CreateSameBufferACK(VGAAckBuf, Function, len);
               ViewDupsPresent = FALSE;
               NoAckOrNak = TRUE;
            }
         }
         else
         NackError = ILLEGAL_COMMAND;
      break;

      case USBPRESET_COMMAND: /* Copy the data to VIEWPreset structure.*/
         Host8 = (UINT8 *)DataPointer;
         switch (*Host8++)
         {
            case VIEWPRESETPARTONE:
               if((CommandCount == DOWNLOADCOMMAND_SIZE+1) ||
               (CommandCount == DOWNLOADDUPS_SIZE+1) ||
               (CommandCount == SEND_SETUPPRINT_DATA_COMMAND_SIZE)
               )
               {
                  if (CommandCount == DOWNLOADDUPS_SIZE+1)
                  { 
                     for(j = 0; j < DUPS_PARAMSETNAMELEN; j++)
                        DUPS_HostParamSetName[j] = *Host8++;   
                     TempPtr =  (UINT8 *) &DUPS_HostParamSet;
                     memcpy(TempPtr, Host8, sizeof(DUPS_CURRENTPARAMSET));   
                     Host8 += sizeof(DUPS_CURRENTPARAMSET);
                     ViewDupsPresent = TRUE;
                  }      
                  memcpy((UINT8 *)  &HostPreset, Host8, sizeof(PRESET_COMPRESSED));
                  RecallViewCompressedPreset(&HostPreset);

                  len = SystemViewPresetReport(&VGAAckBuf[8]);
                  i = CreateSameBufferACK(VGAAckBuf, Function, len);
                  ViewDupsPresent = FALSE;
                  NoAckOrNak = TRUE;

               }
               else
                  NackError = ILLEGAL_COMMAND;
            break;

            default:
               NackError = ILLEGAL_COMMAND;
            break;
         }      
      break;

      case VGA_SCREENSETUP_COMMAND :  // Check if entry allowed in screen setup
         if(CommandCount == VGA_SCREENSETUP_COMMAND_SIZE)
         {
            /* Check for the Ready or Pre-Ready state. */
            if ((WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
            {
               ResetStateMachine();
               ClearReady();		      
            }
            else
            {Beep(ERRORBEEP);
               NackError = ILLEGAL_COMMAND;
               
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      case VGA_RESET_ALARMS:          //for reset alarms
         if(CommandCount == VGA_RESET_ALARMS_SIZE)
         {
            if((KeyMask & RESETKEYMASK) == RESETKEYMASK)
            /*Check if Reset key is enabled */
            {
               FpkpQueue.key = ResetKey; 
               /*Send the key to FPK_TASK */  
               FpkpQueue.common.opcode = OP_FRONT_PANEL_KEYPRESS;
               PsosReturnValue = q_send(FpkpQid, &FpkpQueue);               
            }
         }
         else
            NackError = ILLEGAL_COMMAND;
      break;

      default:
         /* unknown opcode */
         NackError = INVALID_OPCODE;
      break;
   }       /* opcode switch */

   if (NoAckOrNak == FALSE) {
      if (NackError)      
      {
         /* Generate NACK error response */
         i = XmitNack ( Function, SubFunction, NackError,
         ErrorResponseMinLimit, ErrorResponseMaxLimit, VGAAckBuf );
      }
      else 
      {
         SendFakeKeyPress(UPDATEDISPLAY);
         VGAAckBuf[0] = ACK;
         VGAAckBuf[1] = DLE;
         VGAAckBuf[2] = STX;
         /* fill in count */
         VGAAckBuf[3] = 0;
         VGAAckBuf[4] = 5;
         /* fill in function */
         VGAAckBuf[5] = (UINT8)(Function>>8);
         VGAAckBuf[6] = (UINT8)Function;
         /* fill in DisplayLock */
         VGAAckBuf[7] = (UINT8)Inp.DisplayLockFlag;
         /* fill in checksum */
         VGAAckBuf[8] = 0;
         for (i=3; i<8; i++) VGAAckBuf[8] ^= VGAAckBuf[i];
         VGAAckBuf[9] = DLE;
         VGAAckBuf[10] = ETX;
         i = ACK_REPLY_SIZE;
      }
   }

   return i;
}


UINT16 SendQualityLimitsData(UINT8 * to,UINT8 Presetnumber)
{
   UINT16 length = 0;
	UINT16 TempAct = 0;
      
      length += AddToBuffer(&to, (UINT8)((LangIndex)>>8));
      length += AddToBuffer(&to, (UINT8)(LangIndex));
   
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.Units)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.Units));

      length += AddToBuffer(&to, (UINT8)((CurrentSetup.ControlLevel)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.ControlLevel));
		
		if(CurrentSetup.Actuator == MICRO)
		{
			TempAct = AED; // Send AED Actuator to VQS in case of MICRO as VQS doesn't know about MICRO.
			length += AddToBuffer(&to, (UINT8)((TempAct)>>8));
			length += AddToBuffer(&to, (UINT8)(TempAct));
		}
		else
		{
			length += AddToBuffer(&to, (UINT8)((CurrentSetup.Actuator)>>8));
			length += AddToBuffer(&to, (UINT8)(CurrentSetup.Actuator));
		}
   
   CompressPreset = (PRESET_COMPRESSED*)(BBR800_PRESET_START + (Presetnumber * SIZE_OF_COMPRESSED_PRESET));

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & MTIMEBIT) != MTIMEBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->WeldTimeMinVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->WeldTimeMinVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

   if((CompressPreset->VQSLimit & MENERGYBIT) != MENERGYBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->EnergyMinVQS)>>24));
      length += AddToBuffer(&to, (UINT8)((CompressPreset->EnergyMinVQS)>>16));
      length += AddToBuffer(&to, (UINT8)((CompressPreset->EnergyMinVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->EnergyMinVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}
      
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & MPKPOWERBIT) != MPKPOWERBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->PeakPowerMinVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->PeakPowerMinVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & MWELDCOLLAPSEBIT) != MWELDCOLLAPSEBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->WeldColMinVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->WeldColMinVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & MCOLDISTBIT) != MCOLDISTBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalColMinVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->TotalColMinVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

   if((CompressPreset->VQSLimit & MABSDISTBIT) != MABSDISTBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalAbsMinVQS)>>24));
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalAbsMinVQS)>>16));
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalAbsMinVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->TotalAbsMinVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & MFORCEBIT) != MFORCEBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->WeldForceMinVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->WeldForceMinVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & MTOTCYCLETIMEBIT) != MTOTCYCLETIMEBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalCycleTimeMinVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->TotalCycleTimeMinVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & PTIMEBIT) != PTIMEBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->WeldTimeMaxVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->WeldTimeMaxVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

   if((CompressPreset->VQSLimit & PENERGYBIT) != PENERGYBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->EnergyMaxVQS)>>24));
      length += AddToBuffer(&to, (UINT8)((CompressPreset->EnergyMaxVQS)>>16));
      length += AddToBuffer(&to, (UINT8)((CompressPreset->EnergyMaxVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->EnergyMaxVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & PPKPOWERBIT) != PPKPOWERBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->PeakPowerMaxVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->PeakPowerMaxVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & PWELDCOLLAPSEBIT) != PWELDCOLLAPSEBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->WeldColMaxVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->WeldColMaxVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & PCOLDISTBIT) != PCOLDISTBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalColMaxVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->TotalColMaxVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

   if((CompressPreset->VQSLimit & PABSDISTBIT) != PABSDISTBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalAbsMaxVQS)>>24));
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalAbsMaxVQS)>>16));
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalAbsMaxVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->TotalAbsMaxVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & PFORCEBIT) != PFORCEBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->WeldForceMaxVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->WeldForceMaxVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}

      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   if((CompressPreset->VQSLimit & PTOTCYCLETIMEBIT) != PTOTCYCLETIMEBIT) {
      length += AddToBuffer(&to, (UINT8)((CompressPreset->TotalCycleTimeMaxVQS)>>8));
      length += AddToBuffer(&to, (UINT8)(CompressPreset->TotalCycleTimeMaxVQS));}
   else{
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);}
   return length;
}


UINT16 CreateACK(UINT8 * AckBuf, UINT16 Function, UINT8 * response, UINT16 len)
/****************************************************************************/
/*Description:-                                                             */
/* This function builds ACK command and writes the same to the buffer       */
/****************************************************************************/
{
   UINT16 i, j;

   i = 0;
   AckBuf[i++] = ACK;
   AckBuf[i++] = DLE;
   AckBuf[i++] = STX;
   /* Increment index over byte count */
   i += 2;
   /* fill in function */
   AckBuf[i++] = (UINT8)(Function >> 8);
   AckBuf[i++] = (UINT8)Function;
   AckBuf[i++] = (UINT8)Inp.DisplayLockFlag;
   /* fill in the data */
   if  (len > 0)
   {
      memcpy(&AckBuf[i], response, len);
      i += len;
   }
   /* fill in byte count */
   AckBuf[3] = (UINT8)((i-3)>>8);
   AckBuf[4] = (UINT8) (i-3);   
   /* compute checksum */
   AckBuf[i] = 0;
   for (j=3; j<i; j++)
      AckBuf[i] ^= AckBuf[j];
   i++;
   /* add DLE, ETX to message */
   AckBuf[i++] = DLE;
   AckBuf[i++] = ETX;

   return i;
}

UINT16 CreateSameBufferACK(UINT8 * AckBuf, UINT16 Function, UINT16 len)
/****************************************************************************/
/*Description:-                                                             */
/* This function builds ACK command and writes the same to the buffer       */
/****************************************************************************/
{
   UINT16 i, j;

   i = 0;
   AckBuf[i++] = ACK;
   AckBuf[i++] = DLE;
   AckBuf[i++] = STX;
   i = i + 2;
   AckBuf[i++] = (UINT8)(Function>>8);
   AckBuf[i++] = (UINT8)(Function);
   AckBuf[i++] = (UINT8)Inp.DisplayLockFlag;
   i = i + len;
   /* fill in byte count */
   AckBuf[3] = (UINT8)((i-3)>>8);
   AckBuf[4] = (UINT8) (i-3);
   /* compute checksum */
   AckBuf[i] = 0;
   for (j=3; j<i; j++)
      AckBuf[i] ^= AckBuf[j];
   i++;
   /* add DLE, ETX to message */
   AckBuf[i++] = DLE;
   AckBuf[i++] = ETX;

   return i;
}


UINT16 XmitNack (IPS_ACTION_ID_TYPE Function, EDIT_PARAM_TYPE Subfunction, UINT32 Error,
                 UINT32 Info1, UINT32 Info2, UINT8 *NackBuf)
{
   UINT16 i = 0, j;

   NackBuf[i++] = NAK;
   NackBuf[i++] = DLE;
   NackBuf[i++] = STX;

   /* Increment index over byte count */
   i += 2;

   /* fill in function */
   NackBuf[i++] = (UINT8)(Function>>8);
   NackBuf[i++] = (UINT8)Function;
   /* fill in DisplayLock */
   NackBuf[i++] = (UINT8)Inp.DisplayLockFlag;

   /* fill in Error */
   NackBuf[i++] =  (UINT8)(Error>>24);
   NackBuf[i++] =  (UINT8)(Error>>16);
   NackBuf[i++] =  (UINT8)(Error>>8);
   NackBuf[i++] = (UINT8)Error;

   /* test for Set Current Preset Parameters function */
   if ( Function == SET_CURRENT_PRESET_PARAMETERS )
   {
      /* fill in subfunction */
      NackBuf[i++] = (UINT8)(Subfunction>>8);
      NackBuf[i++] = (UINT8)Subfunction;
   }
   /* test for Data Follows = 1 */
   if ( (Error & 1) )
   {
      /* fill in informative parameter no. 1 */
      NackBuf[i++] = (UINT8)(Info1>>24);
      NackBuf[i++] = (UINT8)(Info1>>16);
      NackBuf[i++] = (UINT8)(Info1>>8);
      NackBuf[i++] = (UINT8)Info1;

      /* fill in informative parameter no. 2 */
      NackBuf[i++] = (UINT8)(Info2>>24);
      NackBuf[i++] = (UINT8)(Info2>>16);
      NackBuf[i++] = (UINT8)(Info2>>8);
      NackBuf[i++] = (UINT8)Info2;
      
      if ( Function == VERIFY_PRESET )
      {
         /* fill in param id */
         NackBuf[i++] = (UINT8)(ErrorID>>24);
         NackBuf[i++] = (UINT8)(ErrorID>>16);
         NackBuf[i++] = (UINT8)(ErrorID>>8);
         NackBuf[i++] = (UINT8)(ErrorID);
         
      }
   }

   /* fill in byte count */
   NackBuf[3] = 0;
   NackBuf[4] = i-3;   

   /* compute checksum */
   NackBuf[i] = 0;
   for (j=3; j<i; j++)
      NackBuf[i] ^= NackBuf[j];
   i++;

   /* add DLE, ETX to message */
   NackBuf[i++] = DLE;
   NackBuf[i++] = ETX;

   return i;
}

UINT16 ComputeAuthorization(void)
/* Use PS serial number to compute authorization code for RCS commands. */
{
   UINT16 i, Sum = 0;
   for (i=0; i<SERIALLENGTH; i++)
      Sum += CurrentSetup.PSSerialNumber[i];
   return Sum;
}   



void ColdStartPlus(void)
/****************************************************************************/ 
/*                                                                          */
/* This function sets up the factory defaults. After this function is called*/
/* a long calibration must be run.                                          */
/*                                                                          */
/****************************************************************************/ 
{
   FixBattRam();
   SetBucMenuToFactoryDefault();

   if ( (CurrentSetup.Actuator==AED) ||
	       (CurrentSetup.Actuator==AEF) ||
	       (CurrentSetup.Actuator == MICRO) )
   {
      SetDefCalSysPressure((SINT16)LOW_PRESSURE);
      SetDefCalStrokeLength(DEF_CAL_LENGTH);
      SetDefPressure(); 
      SetDefLoadCell();
      SetDefForce();
      NvrCopyDeftoNon();   /* copy actuator def novram settings to working novram settings */
      UpdateNVRSpringRate(); 
      SetPSVersionNVR();
      BuildDefaultSpringRate();
   }
   SelectNewBoard();                         /* Assume from now on its a new */
}



UINT16 ConvertWeldData(WELD_DATA *Ver8WeldData, UINT8 *StrSPCData){

   UINT8           ByteToCopy;
   UINT16          Index = 0, Retval;

   /* Convert WeldData to 7.02 format for Compuweld */  
   SPCData.CycleCount = Ver8WeldData->CycleCount;
   memcpy(&SPCData.CycleTime, &Ver8WeldData->CycleTime, sizeof(struct t_time));
   memcpy(&SPCData.CycleDate, &Ver8WeldData->CycleDate, sizeof(struct t_date)); 
   SPCData.ActualWeldTime = Ver8WeldData->ActualWeldTime;
   SPCData.TotalEnergy = Ver8WeldData->TotalEnergy;
   SPCData.ActualDistance = Ver8WeldData->ActualTotalAbs;
   SPCData.ActualWeldCollapse = Ver8WeldData->ActualWeldCollapse;
   SPCData.ActualTotalCollapse = Ver8WeldData->ActualTotalCollapse;
   SPCData.ActualFreqStart = Ver8WeldData->ActualFreqStart;
   SPCData.ActualFreqEnd = Ver8WeldData->ActualFreqEnd;
   SPCData.FrequencyChange = Ver8WeldData->FrequencyChange;
   SPCData.FrequencyMin = Ver8WeldData->FrequencyMin;
   SPCData.FrequencyMax = Ver8WeldData->FrequencyMax;
   SPCData.ActualVelocity = Ver8WeldData->ActualVelocity;
   SPCData.ActualTriggerDistance = Ver8WeldData->ActualTriggerDistance;
   SPCData.RejectBitResult = Ver8WeldData->RejectBitResult;
   SPCData.SuspectBitResult = Ver8WeldData->SuspectBitResult;
   SPCData.NoCycleAlarms = Ver8WeldData->NoCycleAlarms;
   SPCData.OverloadAlarms = Ver8WeldData->OverloadAlarms;
   SPCData.EquipmentFailureAlarms = Ver8WeldData->EquipmentFailureAlarms;
   SPCData.CycleModifiedAlarms = Ver8WeldData->CycleModifiedAlarms;
   SPCData.PresetNum = (UINT8)(Ver8WeldData->PresetNum);
   if(CurrentSetup.Units)
   {
      if(CurrentSetup.Metric3Flag)
         SPCData.Unit = METRIC3;
      else
         SPCData.Unit = METRIC2;
   }
   else
      SPCData.Unit = USCS;
   SPCData.Language = (UINT8)(LangIndex);
   SPCData.LimitChangedFlag = LimitChanged;
   SPCData.Warnings = Ver8WeldData->Warnings;
   SPCData.ActualAmplitudeStart = Ver8WeldData->ActualAmplitudeStart;
   SPCData.ActualAmplitudeEnd = Ver8WeldData->ActualAmplitudeEnd;
   SPCData.Weldmode = Ver8WeldData->Weldmode;
   SPCData.PSActControlFlags = Ver8WeldData->PSActControlFlags;
   SPCData.PeakPower = Ver8WeldData->PeakPower;
   SPCData.WeldPressure = Ver8WeldData->WeldPressure;
   SPCData.WeldForceEnd = Ver8WeldData->WeldForceEnd;
   SPCData.HoldForceMax = Ver8WeldData->HoldForceMax;
   SPCData.TotalCycleTime = Ver8WeldData->CycleTimeResult;
   SPCData.TrigForce = Ver8WeldData->TrigForce;

   SPCDataPtr = (UINT8 *) & SPCData;
   StrSPCData[Index++] = DLE;
   StrSPCData[Index++] = STX;
   StrSPCData[Index++] = 0;  // count is 16bits 

   if (CurrentSetup.WelderAddrFlag == 0) {  /* 0:Welder ID on */
      StrSPCData[Index++] = (UINT8) (sizeof(WELD_DATA7_02) + 4);
//      StrSPCData[Index++] = (UINT8) (0x076);
      StrSPCData[Index++] = (CurrentSetup.WelderAddrValue & 0x0ff00) >> 8;
      StrSPCData[Index++] = (CurrentSetup.WelderAddrValue & 0x0ff);
      StrSPCData[Index++] = 0;  // function number is 16bits 
      StrSPCData[Index++] = 26;
      for (ByteToCopy = 0; ByteToCopy < (sizeof(WELD_DATA7_02) ); ByteToCopy++)
      {
         StrSPCData[Index++] = *(SPCDataPtr + ByteToCopy);
      }
      Retval = SPCSIZE+2;  /* Add in for welder ID */
   }
   else {  /* This is compatable with original Compuweld - DON'T CHANGE IT */
      StrSPCData[Index++] = (UINT8) (sizeof(WELD_DATA7_02) + 2);
      StrSPCData[Index++] = 0;  // function number is 16bits 
      StrSPCData[Index++] = 26;
      for (ByteToCopy = 0; ByteToCopy < (sizeof(WELD_DATA7_02) - 1); ByteToCopy++)
      {
         StrSPCData[Index++] = *(SPCDataPtr + ByteToCopy);
      }
      Retval = SPCSIZE;
   }

   StrSPCData[Index++] = 0;  // chksum 
   StrSPCData[Index++] = DLE;
   StrSPCData[Index] = ETX;
   return(Retval);
}


/* Store the MIN_ERROR or MAX_ERROR in ErrorType to send in NAK response */
#define STORE_MIN_ERROR     (*ErrorType = MIN_ERROR) 
#define STORE_MAX_ERROR     (*ErrorType = MAX_ERROR) 




BOOLEAN CheckForParameterError(UINT16 Value)
/*****************************************************************************/
/*                                                                           */
/* This function checks, whether the passing parameter contain a valid value.*/
/* If not, the function returns TRUE.                                        */
/*                                                                           */
/*****************************************************************************/
{
   BOOLEAN RetVal = FALSE;
   if(CurrentSetup.ControlLevel == LEVEL_f)
   {
      switch(Value)
      {
         case RATE_SLOWEST:
         case RATE_SLOW:
         case RATE_NORMAL:
         case RATE_FAST:
         case RATE_FASTEST:
            break;
         default:
            RetVal = TRUE;
            break;
      }
   }
   return (RetVal);
}


UINT16 CreateGraphHeader(UINT16 Type, UINT8 Buffer[])
/*****************************************************************************/
/*                                                                           */
/*  This function will fill in the graph header in the passed buffer.  It    */
/*  will return the number of bytes added to the passed buffer.  The header  */
/*  format is:                                                               */
/*                                                                           */
/*  bytes  description                                                       */
/*  -----  ---------------------------------------------------               */
/*    2    graph type (first passed argument)                                */
/*    4    trigger delay tick mark referenced from trigger point (ms)        */
/*    4    amplitude step tick mark referenced from trigger point (ms)       */
/*    4    force step tick mark referenced from trigger point (ms)           */
/*    4    end of sonics tick mark referenced from trigger point (ms)        */
/*    4    end of hold time tick mark referenced from trigger point (ms)     */
/*    2    number of y values (should be less than or equal to 400)          */
/*    2    x start value (always -0.100 ms before trigger point)             */
/*    2    x step value (ms * 100).  For example 188 = 1.88 ms               */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 Count = 0;
   UINT32 TriggerDelay = 0;     /* TEMP for now */
   UINT16 Increment;
   DFLOAT XStep;
   WELD_DATA LastResults;
   
/* Graph type */
   Buffer[Count++] = (UINT8) (Type >> BYTE3SHIFT);
   Buffer[Count++] = (UINT8) Type;
   
/* Trigger delay tick mark */   
   Buffer[Count++] = (UINT8) (TriggerDelay >> BYTE1SHIFT);
   Buffer[Count++] = (UINT8) (TriggerDelay >> BYTE2SHIFT);
   Buffer[Count++] = (UINT8) (TriggerDelay >> BYTE3SHIFT);
   Buffer[Count++] = (UINT8) TriggerDelay;
   
/* Amplitude step tick mark */   
   Buffer[Count++] = (UINT8) (MsPointer->AmpStepAtTime >> BYTE1SHIFT);
   Buffer[Count++] = (UINT8) (MsPointer->AmpStepAtTime >> BYTE2SHIFT);
   Buffer[Count++] = (UINT8) (MsPointer->AmpStepAtTime >> BYTE3SHIFT);
   Buffer[Count++] = (UINT8) MsPointer->AmpStepAtTime;
   
/* Force step tick mark */   
   Buffer[Count++] = (UINT8) (MsPointer->ForceStepAtTime >> BYTE1SHIFT);
   Buffer[Count++] = (UINT8) (MsPointer->ForceStepAtTime >> BYTE2SHIFT);
   Buffer[Count++] = (UINT8) (MsPointer->ForceStepAtTime >> BYTE3SHIFT);
   Buffer[Count++] = (UINT8) MsPointer->ForceStepAtTime;
   
/* End of sonics tick mark */   
   GetLastWeldData(&LastResults);
   Buffer[Count++] = (UINT8) (LastResults.ActualWeldTime >> BYTE1SHIFT);
   Buffer[Count++] = (UINT8) (LastResults.ActualWeldTime >> BYTE2SHIFT);
   Buffer[Count++] = (UINT8) (LastResults.ActualWeldTime >> BYTE3SHIFT);
   Buffer[Count++] = (UINT8) LastResults.ActualWeldTime;
   
/* End of hold time tick mark */   
   Buffer[Count++] = (UINT8) (MsPointer->HoldEndAtTime >> BYTE1SHIFT);
   Buffer[Count++] = (UINT8) (MsPointer->HoldEndAtTime >> BYTE2SHIFT);
   Buffer[Count++] = (UINT8) (MsPointer->HoldEndAtTime >> BYTE3SHIFT);
   Buffer[Count++] = (UINT8) MsPointer->HoldEndAtTime;
   
/* Number of Y values */   
   Buffer[Count++] = (UINT8) (WeldDataCount >> BYTE3SHIFT);
   Buffer[Count++] = (UINT8) WeldDataCount;

/* X start value */   
   Buffer[Count++] = (SINT8) (-100 >> BYTE3SHIFT);
   Buffer[Count++] = (SINT8) -100;

/* X step value */
   XStep = (MsPointer->IncrementPts + 0.005) * 100;  /* Round off, then X 100 */
   Increment = (UINT16) XStep;
   Buffer[Count++] = (UINT8) (Increment >> BYTE3SHIFT);
   Buffer[Count++] = (UINT8) Increment;

   return(Count);
}



UINT16 CreateHornscanHeader(UINT8 Buffer[])
/*****************************************************************************/
/*                                                                           */
/*  This function will fill in the horn scan header in the passed buffer. It */
/*  will return the number of bytes added to the passed buffer.  The header  */
/*  format is:                                                               */
/*                                                                           */
/*  bytes  description                                                       */
/*  -----  ---------------------------------------------------               */
/*    2    graph type (first passed argument)                                */
/*    4                                                                      */
/*    4                                                                      */
/*    4                                                                      */
/*    4    x start value                                                     */
/*    4    x step value                                                      */
/*                                                                           */
/*****************************************************************************/
{
}



void SetBucMenuToFactoryDefault(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will initialize the variables stored in BBR that are       */
/*  accessed via the BUC menu.                                               */
/*                                                                           */
/*****************************************************************************/
{
   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;

   BUCMenuRAM.VelocityPC = VELOCITY_PC_DEFAULT;
   BUCMenuBBR->VelocityPC = VELOCITY_PC_DEFAULT;
   BUCMenuRAM.VelocityReporting = FALSE; /* Default velocity reporting to off */
   BUCMenuBBR->VelocityReporting = FALSE;
   BUCMenuBBR->RecalCode300 = TRUE;
   BUCMenuRAM.RecalCode300 = TRUE;

   /* Default values for EnergyBraking and AmpDecay.*/
   BUCMenuRAM.AmpDecayPercent = AMP_DECAY_PERCENT_DEFAULT;  
   BUCMenuRAM.EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
   BUCMenuRAM.EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
   BUCMenuBBR->EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
   BUCMenuBBR->EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
   BUCMenuBBR->AmpDecayPercent = AMP_DECAY_PERCENT_DEFAULT;
   BUCMenuBBR->MicroHomeForce = LEAVINGHOMEFORCEMICROLO;

   CurrentSetup.IdleSpeed = IDLE_SPEED_DEFAULT;
   UpdateCylDefaults();  /* This will update ForcePC in BBR based on cylinder */
   
   GetAlarmMask();                 /* Fix all alarm masks */
}



UINT8 VerifyLengthAndCode(SINT16 length, UINT16 code)
/*******************************************************************/
/*                                                                 */
/*  This function will Check the Length and Code of command.       */
/*  and return true if correct else return false.                  */
/*******************************************************************/
{   
   UINT8 ValidLengthAndCode = FALSE;
   length+=DEFAULT_COMMAND_SIZE;
   switch(code)
   {
      case DOWNLOAD_CURRENT_PRESET: /* Copy the data to HostPreset structure.*/
         if(length == DOWNLOADCOMMAND_SIZE )
            ValidLengthAndCode = TRUE;
      break;
      case VERIFY_PRESET: 
         if(length == VERIFYCOMMAND_SIZE )
            ValidLengthAndCode = TRUE;
      break;
      case UPLOAD_CURRENT_PRESET:
         if(length == UPLOADCOMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;
      case REQUEST_GRAPH_DATA:
         if (length == GRAPHCOMMAND_SIZE) 
            ValidLengthAndCode = TRUE;
      break;

      case RESET_ALARMS:	    
         if(length == RESETALARMS_SIZE)
            ValidLengthAndCode = TRUE;
      break;
      case RECALL_PRESET:	    
         if(length == RECALL_PRESET_COMMAND_SIZE )
            ValidLengthAndCode = TRUE;
      break;

      case SET_CURRENT_PRESET_PARAMETERS:	    
         if(length <= SET_CURRENT_PRESET_PARAMETERS_COMMAND_SIZE )
            ValidLengthAndCode = TRUE;
      break;

      case START_WELD_DATA:	    
         if(length == START_WELD_DATA_COMMAND_SIZE )
            ValidLengthAndCode = TRUE;
      break;

      case SET_ENERGYMLS:	    
      case SET_ENERGYPLS:	    
      case SET_ENERGYMLR:
      case SET_ENERGYPLR:	    
      case SET_TIMEMLS:	    
      case SET_TIMEPLS:	    
      case SET_TIMEMLR:	    
      case SET_TIMEPLR:	    
      case SET_PEAKPOWER_CUTOFF:	    
      case SET_COLLDIST_CUTOFF:	    
      case SET_MPOWER_SLIMIT:	    
      case SET_PPOWER_SLIMIT:	    
      case SET_MPOWER_RLIMIT:	    
      case SET_PPOWER_RLIMIT:	    
      case SET_MCOLLAPSE_SLIMIT:	    
      case SET_PCOLLAPSE_SLIMIT:	    
      case SET_MCOLLAPSE_RLIMIT:	    
      case SET_PCOLLAPSE_RLIMIT:	    
      case SET_MABSOLUTE_SLIMIT:	    
      case SET_PABSOLUTE_SLIMIT:	    
      case SET_MABSOLUTE_RLIMIT:	    
      case SET_PABSOLUTE_RLIMIT:	    
      case SET_MTRIGDIST_SLIMIT:	    
      case SET_PTRIGDIST_SLIMIT:	    
      case SET_MTRIGDIST_RLIMIT:	    
      case SET_PTRIGDIST_RLIMIT:	    
      case SET_MMAXFORCE_SLIMIT:	    
      case SET_PMAXFORCE_SLIMIT:	    
      case SET_MMAXFORCE_RLIMIT:	    
      case SET_PMAXFORCE_RLIMIT:	    
      case SET_ACTUATOR_CLEAR:	    
         if(length == SET_PARAMETER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case CHECKSUM_ERROR:    /* Bad data received */	    
         if(length == CHECKSUM_ERROR_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;
      case ONBOARD_DIAGNOSTICS:          /* Special host command to start */	    
         if(length == ONBOARD_DIAGNOSTICS_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;
      case SET_PS_SERIALNUMBER:	    
         if(length <= SET_PS_SERIALNUMBER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SET_PS_MODELNUMBER:	    
         if(length == SET_PS_MODELNUMBER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SET_CONTROLLEVEL:
         if(length == SET_CONTROLLEVEL_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SET_ACT_SERIALNUMBER:	    
         if(length <= SET_ACT_SERIALNUMBER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SET_ACT_MODELNUMBER:	    
         if(length == SET_ACT_MODELNUMBER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case RESET_PSLIFETIMECOUNTER:	    
         if(length == RESET_PSLIFETIMECOUNTER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case RESET_OVERLOADCOUNTER:	    
         if(length == RESET_OVERLOADCOUNTER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case RESET_GENALARMCOUNTER:	    
         if(length == RESET_GENALARMCOUNTER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SET_ACTUATOR_CYLINDERDIAMETER:	    
         if(length == SET_ACTUATOR_CYLINDERDIAMETER_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SET_ACTUATOR_STROKELENGTH:	    
         if(length == SET_ACTUATOR_STROKELENGTH_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case UPLOAD_REMOTE_CONFIG_PARMS:	    
         if(length == UPLOAD_REMOTE_CONFIG_PARMS_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_QUALITYLIMITS_DATA:     
         if(length == QUALITYLIMITS_DATA_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_MENU_PTRS:
         if(length == MENU_PTRS_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case START_RUNCYCLE:
         if(length == START_RUNCYCLE_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_CONDN_VAR:
         if (length == SEND_CONDN_VAR_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_STRUCTURE_DATA:
         if(length == SEND_STRUCTURE_DATA_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case RECEIVE_STRUCTURE_DATA  :
         //if(length == RECEIVE_STRUCTURE_DATA_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_MIN_MAX_COMMAND :
         if(length == SEND_MIN_MAX_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case BOTTOMHALF_COMMAND :
         if(length == BOTTOMHALF_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case VGA_POLLING_COMMAND         :
         if(length == POLLING_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case WELD_DATA_COMMAND      :
         if(length == WELD_DATA_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case PROCESS_ALARM_ITEM           :
         if(length == PROCESS_ALARM_ITEM_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_ALARMBIT_COMMAND         :
         if(length == SEND_ALARMBIT_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_WELDER_STATE_CMD       :
         if(length == SEND_WELDER_STATE_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;
      case SEND_START_WELD_DATA    :
         if(length == SEND_START_WELD_DATA_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_SETUPPRINT_DATA         :
         if(length == SEND_SETUPPRINT_DATA_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case SEND_PRINT_PARAM        :
         if(length == SEND_PRINT_PARAM_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case PMC_COMMAND          :
         if(length == PMC_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;
      case VGA_ERRORBEEP_COMMAND   :
         if(length == VGA_ERRORBEEP_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case VGA_PRINTERROR_COMMAND  :
         if(length == VGA_PRINTERROR_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case VGA_SCREENSETUP_COMMAND :
         if(length == VGA_SCREENSETUP_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case VGA_RESET_ALARMS :
         if(length == VGA_RESET_ALARMS_SIZE)
            ValidLengthAndCode = TRUE;
      break;

      case VGADOWNLOAD_PRESET: /* Copy the data to HostPreset structure.*/
         if((length == DOWNLOADCOMMAND_SIZE+1)||(length== DOWNLOADDUPS_SIZE+1))
            ValidLengthAndCode = TRUE;
      break;		 

      case VGAUPLOAD_PRESET:
         if(length == UPLOADCOMMAND_SIZE+1)
            ValidLengthAndCode = TRUE;
      break;

      case USBPRESET_COMMAND: /* Copy the data to VIEWPreset structure.*/
         if((length == DOWNLOADCOMMAND_SIZE+1)||( length== DOWNLOADDUPS_SIZE+1)
            ||(length==SEND_SETUPPRINT_DATA_COMMAND_SIZE))
            ValidLengthAndCode = TRUE;
      break;

      case PSPRESET_COMMAND: /* Copy the data to VIEWPreset structure.*/
         if(length == PSPRESET_COMMAND_SIZE)
            ValidLengthAndCode = TRUE;
      break;
      default:
         ValidLengthAndCode = FALSE;
   }
   return ValidLengthAndCode;
}

/*************************************************************************/
/*Description:                                                           */
/* Enabled micron calibration                                            */
/*                                                                       */
/*************************************************************************/
void VGARequestMicronCalEnabled(void)
{
	SetCurrentAmp(VGA_ScreenMicronCalAmp);
	VGA_ScreenMicronCalFlag = TRUE;
	Beep(CONFIRMBEEP);
}

/*************************************************************************/
/*Description:                                                           */
/* Disabled micron calibration                                            */
/*                                                                       */
/*************************************************************************/
void VGARequestMicronCalDisabled(void)
{
	if(VGA_ScreenMicronCalFlag == TRUE){
		QVGAExitTestSequence();
		VGA_ScreenMicronCalFlag = FALSE;
	}
}

void VGARequestMicronUpdate(void)
{
    CurrentPreset.Amp1 = ThreeRuleMicronsToPorcentage(CurrentPreset.AmpAMicron,CurrentSetup.AmpMicronsValue);
    if ((CurrentPreset.Amp2Flag & BIT0) == BIT0)
    {
        CurrentPreset.Amp2 = ThreeRuleMicronsToPorcentage(CurrentPreset.AmpBMicron,CurrentSetup.AmpMicronsValue);
    }
  	SaveCompressedPreset((PRESET_COMPRESSED *) PRESET_0_START, &CurrentPreset);
   	Beep(CONFIRMBEEP);
}

void VGARequestMicronUpdateAll(void)
{
	PRESET_COMPRESSED TempPreset;
	UINT16 CounterCrt;
	UINT32 BattramStatus;

    CurrentPreset.Amp1 = ThreeRuleMicronsToPorcentage(CurrentPreset.AmpAMicron,CurrentSetup.AmpMicronsValue);
    CurrentPreset.Amp2 = ThreeRuleMicronsToPorcentage(CurrentPreset.AmpBMicron,CurrentSetup.AmpMicronsValue);
    SaveCompressedPreset((PRESET_COMPRESSED *) PRESET_0_START, &CurrentPreset);

	for (CounterCrt=1; CounterCrt< ALL_PRESETS; CounterCrt++) {
		 BattramStatus = BattramAccess(BBR_READ, PRESET_SECTION, (UINT8 *)&TempPreset,  PresetAddress[CounterCrt], sizeof(TempPreset));
		 TempPreset.Amp1 = ThreeRuleMicronsToPorcentage(TempPreset.AmpAMicron,CurrentSetup.AmpMicronsValue);
		 TempPreset.Amp2 = ThreeRuleMicronsToPorcentage(TempPreset.AmpBMicron,CurrentSetup.AmpMicronsValue);
		 BattramStatus = BattramAccess(BBR_WRITE, PRESET_SECTION, (UINT8 *)&TempPreset, PresetAddress[CounterCrt], sizeof(TempPreset));
	}

	Beep(CONFIRMBEEP);
}

BOOLEAN VGADisableAmplitudePorcentages(void)
{
	if(CurrentSetup.AmpMicronsFlag==FALSE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "command.ut"
#endif
/* FOR UNIT TEST ONLY */

/* FOR INTEGRATION TEST ONLY */
#ifdef INCLUDE_INTEGRATION_TEST
#include "command.it"
#endif
/* FOR INTEGRATION TEST ONLY */
