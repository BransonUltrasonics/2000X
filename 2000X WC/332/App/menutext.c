/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUTEXT.C_V   2.498.2.3.1.4   May 27 2005 07:18:04   bwadia  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96,97           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menutext.c      
                                    
   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0                                      Initial Version
      1.00        04/29/96       PJ          Modified for PSOS version
      3.00        05/29/96       PJ          Added error message strings
      4.00        06/11/96       PJ          Added strings for Menu7 & menu7a
      5.00        06-11-96       BEKymer     Added \042 (inch) for MX_42 & 44
      5.01        06-13-96       BEKymer     Uppercase calibration titles
      5.04        06-20-96       PJ          Renamed Title lines of Main Menu
      5.07        07-01-96       PJ          Added StrStep and StrFixed.
      5.08        07-02-96       PJ          Added strings for Custom Act
                                             Logic Submenus.
      5.11        07-19-96       PJ          Updated version to 2.09. Deleted
                                             MESSAGESIZE from strings. Added
                                             strings for new menu's.
      5.12        07-26-96       PJ          Updated version to 2.10. Deleted
                                             and changed strings for menu2a.
      5.20        08/01/96       PhilJ       Added/Changed strings per Spec
                                             Rev 1.C
      5.30        08/02/96       PhilJ       Updated version to 2.11. Added
                                             strings for password screen
      5.40        08/02/96       PhilJ       Updated version to 2.12. Added
                                             strings for Preset screen
      5.50        08/07/96       LAM         fixed calibration screens
      5.60        08/14/96       PhilJ       Updated version to 2.13. Added/
                                             changed strings for Preset Menus
      5.70        08/15/96       PMG         Added new strings for the Print   
                                             Menu, starting at StrM8_0   
      5.80        08/21/96       PhilJ       Updated version to 2.14. Added/
                                             Changed strings for Password
                                             menu.
      5.90        08/22/96       PMG         Modified StrM8_31A to "Abort Printing.
                                             Modified StrM8_42B to WeldsPerPage.
                                             Added StrM8_41E thru StrM8_41J.
      6.10        08/26/96       PhilJ       Updated version to 2.16.
                                             Changed Run Screen strings per
                                             1000 Spec Rev: 1.D
      6.20        08/26/96       PhilJ       Updated version to 2.17.
                                             Added/Changed text to Menu1 (Run
                                             Screen Menu).
      6.30        09/10/96       PhilJ       Updated version to 2.18.
                                             Deleted Menu1 strings StrM1_4 thru
                                             StrM1_20.  Moved to Menu1.c.
      6.40        09/14/96       PhilJ       Added space character to the end
                                             StrAlpha2.
      6.51        10/02/96       PAULG       Modified string StrM8_42A.
      6.52        10/03/96       LAM         Modified calibration strings
      6.53        10/04/96       PAULG       Added string StrM8_2DD Thru StrM8_2JJ
      8.10        10/17/96       PhilJ       Changed StrM2_4 & StrM2_7 and
                                             added enter password string.
      8.20        10-18-96       BEKymer     Add power up checking messages
      8.30        10/22/96       PhilJ       Updated text per DCS issues.
     10.00        10/27/96       LAM         Updated version to 3.02,fixed downspeed
     10.10        10/27/96       PhilJ       Added StrMH_9 for HornDown menu.
     10.20        10/27/96       PhilJ       Added to StrM7_10 & StrM7_11 the
                                             Submenu indicator '>'.
     10.30        11/01/96       PhilJ       Updated vers: to 3.03. Changed
                                             text strings for System Info menu.
     11.00        11/02/96       LAM         added metric to calibration
     12.00        11/06/96       PaulG       Modify StrM8_2 and StrM8_3
     13.00        11/10/96       LAM         updated version to 3.04     
     14.00        11/13/96       PhilJ       Added Cold Start messages
     17.00        11/22/96       LAM         Updated version to 3.07,fixed preset
                                             counter
     18.00        11/26/96       PhilJ       Updated version to 3.08. Removed
                                             = sign from StrM6_1 thru StrM6_4.
                                             Added StrM2_42A. Capitalized OK.
                                             Deleted Page Info from Calibration
                                             Menus.
     19.10        12/10/96       PhilJ       Increased StrM1_1 to 20 characters.
     22.10        12/30/96       LAM         chged to MPS switch, update ver to 3.13
     23.00        01/12/97       LAM         update ver to 3.14,chged control level
     26.00        01/30/97       PhilJ       Added strings in menu2 for
                                             Cycle Abort menu.
     28.00        02/06/97       LAM         Updated version to 3.18,chged testmenu
     29.00        02/12/97       PhilJ       Updated version to 3.19. Shorten
                                             strings in menu2.
     29.10        02/13/97       PhilJ       Added string StrM2_83.
     30.10        02/27/97       PhilJ       Modified Strings M2_32, 77, and 81.
     30.20        03/03/97       PhilJ       updated ver 3.23. Added StrResetMsgs.       
     30.30        03/07/97       PhilJ       Abbreviated string M6_13. Cyl Strk.
     30.40        03/11/97       PhilJ       updated ver 3.24.       
     30.50        03/13/97       PhilJ       updated ver 3.25. Added Str M7_31A.      
     30.60        03/17/97       BEKymer     Added string for Remote Terminal
     32.00        04/11/97       PhilJ       updated ver 3.28. Added StrM8_43
                                             and StrM8_44.
     32.10        04/11/97       PhilJ       Deleted StrM8_44.
                                             Updated vers: 3.29.
     32.20        04/17/97       PhilJ       Added StrM8_44. Updated vers:3.30
     32.30        04/17/97       PhilJ       Chngd StrM8_42B to Lines Per Page
     32.40        04/21/97       PhilJ       Updated vers:3.31.
     32.50        04/24/97       LAM         deleted unused strs
     34.00        05/08/97       LAM         Updated vers:3.33, added center freq
     36.00        05/12/97       LAM         Updated vers:3.35, chged pkpwrcutoff &
                                             chged missing part
     36.10        05/13/97       PhilJ       Added StrM8_22B for global printing.
     36.20        05/14/97       PhilJ       Updated vers:3.36
     38.01        05/23/97       PaulG       Added StrM8_41L and StrM8_41K for OkiData.
     39.00        05/24/97       LAM         Updated vers:3.39,added show strings
     39.01        05/24/97       LAM         Updated vers:3.40,added show strings
     42.2.122     06/17/97       PaulG       Added string StrM8_45 thru StrM8_45C.
     42.2.122     06/18/97       LAM         Updated vers: 4.00
     42.2.123     06/23/97       PaulG       Updated StrM8_45B and StrM8_41A thru StrM8_41K.
     42.2.124     07/03/97       PhilJ       Changed StrPO_5 & 6.
     43.2.125     07.07.97       J.B.        Adding Main/Run start screen
     42.2.126     07/08/97       PhilJ       Added StrM7A_10 thru 11A.
     42.2.128     07/09/97       PhilJ       Updated vers:4.01
     43.2.129     07.10.97       J.B.        Added StrM0A_4 "Adv Feat on".
     42.2.130     07/17/97       PhilJ       Added StrM2_84 to StrM2_97.
                                             Updated vers:4.02
     42.2.131     07/18/97       PhilJ       Added StrM7A_41 to 53.
     42.2.132     07/18/97       PhilJ       Deleted extra character in M6_8
     42.2.133     07/18/97       PhilJ       Added StrM6_8A
     42.2.134     07/22/97       PhilJ       Chngd StrM0_2 to Weld Setup.
                                             Updated vers:4.03
     42.2.135     07/23/97       PhilJ       Added StrMH_10
     42.2.136     07/23/97       JBerman     Added Str17Spc
     43.2.137     07/24/97       LAM         Updated vers:4.04, added power calib strs
                                             chged freq control to offset
     43.2.138     07/30/97       LAM         redid power calib strs
     43.2.139     07/30/97       PaulG       Changed StrM8_2H.
     43.2.140     07/30/97       LAM         deleted str5a_7,modified str5a_8
     43.2.141     08/01/97       PhilJ       Chngd StrM2_0 thru StrM2_8 per
                                             ORS 1.08. Update vers: 4.05
     43.2.142     08/04/97       PhilJ       Added strings per DigitalTune
                                             menus.
     43.2.143     08/06/97       PhilJ       Added strings StrMPW_9 & 10
     44.2.144     08/08/97       LAM         Added string  StrM3_9a
     44.2.145     08/13/97       PhilJ       Added string StrM7A_41N
                                             Updated vers:4.06 
     44.2.146     08/15/97       LAM         chged value string
     44.2.147     08/20/97       PhilJ       Chgd StrM7A_41M Custom to lowercase
                                             Updated vers:4.07 
     44.2.148     08.26.97       JBerman     Changed Proprinter with IBM Pro.
     2.149        08.26.97       LAM         updated to ver 4.08             
     2.150        08.30.97       LAM         updated to ver 4.09
     2.151        09.02.97       LAM         updated to ver 4.10
     2.152        09.05.97       LAM         updated to ver 4.11
     2.153        09.10.97       LAM         updated to ver 4.12,moved text from weldmngr
     2.154        09-12-97       PaulG       Modify StrM8_22C.
     2.155        09-15-97       PaulG       Modify LinesPerPage to WeldsPerPage.
     2.156        09-22-97       PaulG       Modified PageSize text for display.
     2.157        09-23-97       LAM         updated to ver 4.13
     2.157        09-30-97       LAM         updated to ver 4.14
     2.158        10-01-97       LAM         updated to ver 4.15
     2.159        10.03.97       JBerman     Added some more strings for Cylinder
                                             Dia. & stroke Length in mm.
     2.160        10-03-97       BJB         Put variable units (&&&&) in string
                                             for Horn Down velocity
     2.161        10-06-97       LAM         chged digpot screens
     2.162        10-07-97       LAM         updated to ver 4.17,deleted strm6_12 & 13
     2.163        10.07.97       JBerman     Removed Cyl Dia & Stroke strings
                                             from menu7a.c into this file.
                                             Associate with Cyl Dia & Stroke
     2.164        10-13-97       LAM         updated to ver 4.18
     2.165        10-14-97       LAM         updated to ver 4.19, added powercal timeout
     2.166        10-17-97       BJB         Added cursor to initial preset
                                              name entry screen.
                                             Extended StrMPW_3 "Password" to
                                              full line length.
     2.167        10-21-97       BJB         Added uppercase PASSWORD string
                                              for use as title when new password
                                              is accepted.
     2.168        10-23-97       LAM         updated to ver 4.20
     2.169        10-24-97       LAM         updated to ver 4.21
     2.170        10-28-97       BJB         Extended Horn Down strings to full line.
     2.171        10-29-97       LAM         updated to ver 4.22
     2.172        11-05-97       LAM         chged please wait string
     2.173        11-05-97       PaulG       Spelling mistake correction
     2.174        11-06-97       BJB         Added text for Freq Offset>Ext
                                             Took space off end of StrPO_5[] so
                                              control level shows next to 2000.
     2.175        11-07-97       LAM         updated to ver 4.23
     2.176        11-08-97       BJB         Moved 'space' in Alpha string so it
                                              isn't at end of line.
                                             Deleted unused strings StrM3_5[],
                                              StrM3_6[].
     2.177        11-11-97       BJB         Moved "Start Over" in StrMPW_6[] to
                                              end of line.
     2.178        11-12-97       LAM         updated to ver 4.24
     2.179        11-17-97       LAM         updated to ver 4.25
     2.180        11-24-97       LAM         updated to ver 4.26
     2.181        12-01-97       LAM         updated to ver 4.27
     2.182        12.02.97       JBerman     Modified the Actuator decimal #
     2.183        12-03-97       LAM         updated to ver 4.28
     2.184        12-04-97       BJB         Added message "No Value Entered".
                                             Extended lengths of "Value Below Min"
                                              and "Value Above Max" because code
                                              that uses them expects them to be
                                              full-line length.
     2.185        12-08-97       LAM         updated to ver 4.29
     2.186        12-11-97       LAM         updated to ver 4.30
     2.187        12-12-97       LAM         updated to ver 4.31
     2.188        12-15-97       LAM         updated to ver 4.32
     2.189        12-19-97       LAM         updated to ver 4.33,deleted space in watt meter
     2.190        01-19-98       LAM         updated to ver 4.34, changed copyreight to 1998
     2.191        01-20-98       PaulG       Update string from reset to realign.
     2.192        01-22-98       BJB         Deleted StrYes[] and StrNo[]
     2.193        01-22-98       BJB         Changed "host computer" to "remote computer"
     2.194        01-23-98       BJB         Changed "READY" to "RUN" on run screen.
     2.195        01-26-98       LAM         updated to ver 4.35, changed copyright to 1996-98
     2.196        02-02-98       LAM         updated to ver 4.36, chged frc to f
     2.197        02-09-98       LAM         updated to ver 4.37
     2.198        02-17-98       LAM         updated to ver 4.38
     2.199        02-23-98       LAM         updated to ver 4.39
     2.200        03-02-98       LAM         updated to ver 4.40, added calibration text
     2.201        03-09-98       BJB         Removed word "Diagnostics" from Calibration
                                              choice, title.
     2.202        03-11-98       LAM         updated to ver 4.41
     2.203        03-16-98       LAM         updated to ver 4.42
     2.204        03-18-98       LAM         updated to ver 4.43
     2.205        03-18-98       BJB         Changed text of "Amplitude" line to say
                                              "Set Amp".
     2.206        03-20-98       BJB         Removed '>' from "Date>" and "Time>".
     2.207        03-24-98       LAM         updated to ver 4.44
     2.208        03-27-98       LAM         updated to ver 4.45
     2.209        04-06-98       LAM         updated to ver 4.46
     2.210        04-08-98       LAM         updated to ver 4.47
     2.211        04-08-98       LAM         updated to ver 4.48
     2.212        04-15-98       LAM         updated to ver 4.49
     2.213        04-16-98       LAM         updated to ver 5.00(Release 2)
     2.214        04-16-98       LAM         added calibration strings, ground detect
                                             cutoff to abort
     2.215        04-20-98       LAM         updated to ver 5.0a
     2.216        04-27-98       LAM         updated to ver 5.0b
     2.217        04-29-98       BJB         Added text strings for Branson menu.
     2.218        04-29-98       BEKymer     Changed StrM7A_24A text
     2.219        04-30-98       LAM         added act calibration strings
     2.220        05-04-98       LAM         updated to ver 5.0c
     2.221        05-08-98       LAM         updated to ver 5.0d
     2.222        05-15-98       LAM         deleted equal sign from calibration
                                             strings, entry routine puts it in
     2.223        05-18-98       LAM         updated to ver 5.0e
     2.224        05-18-98       PaulG       Added StrM8_47: "Abs Distance Graph".
     2.225        05-21-98       LAM         revised calibration text per ORS 2.01
     2.226        05-26-98       LAM         updated to ver 5.0f
     2.227        05-29-98       BJB         Deleted Increase/Decrease Freq Offset
                                              strings, added Change Sign.
     2.228        06-01-98       LAM         updated to ver 5.0g
     2.229        06-01-98       BJB         Put > after "Adjust Weld" in string
                                              used on Run Screen.
     2.230        06-01-98       BJB         Changed "ADJUST SETUP" to "ADJUST WELD"
     2.231        06-03-98       BJB         Changed text of Digital Pot screens.
     2.232        06-05-98       LAM         Changed calibration text in sys info
     2.233        06-10-98       LAM         updated to ver 5.0h, added pass/fail string
     2.234        06-11-98       LAM         updated to ver 5.0i, added screen text to
                                             show calibrate actuator after cal sensor
     2.235        06-18-98       BJB         Added text that comes up if user attempts
                                              cold start during welding.
     2.236        06-22-98       LAM         updated to ver 5.0j
     2.237        06-22-98       BJB         Changed text Max F to Weld F.
     2.238        06-24-98       BJB         Changed text "Normal" to "Basic",
                                              "Advanced" to "All".
     2.239        06-25-98       LAM         updated to ver 5.0k, chged calibration
                                             screens to match ORS2.5
     2.240        06-29-98       BJB         Changed spelling of "Pretrg Amp" to match
                                              spec.
                                             Added string for 800W Branson Menu entry.
     2.241        07-01-98       LAM         added calibration aborted menu
     2.242        07-02-98       LAM         updated to ver 5.0l
     2.243        07-06-98       LAM         updated to ver 5.0m
     2.244        07-08-98       LAM         updated to ver 5.0n
     2.245        07-14-98       LAM         updated to ver 5.0o
     2.246        07-20-98       LAM         updated to ver 5.0p,added manual overide
                                             complete message
     2.247        07-24-98       PaulG       Updated to ver 5.0q.
     2.248        07-29-98       LAM         Updated to ver 5.0r, changed last
                                             message during calibration
     2.249        07-31-98       LAM         Updated to ver 5.0s, changed verify
                                             screen.
     2.251        08-05-98       LAM         Updated to ver 5.0t.
     2.252        08-07-98       PaulG       Updated to ver 5.0u.
     2.253        08-11-98       LAM         Updated to ver 5.0v.
     2.254        08-11-98       BEKymer     Changed StrM2_21 (Power -> Pwr)
     2.255        08-18-98       LAM         Updated to ver 5.0w.
     2.256        08-25-98       LAM         Updated to ver 5.0x.
     2.257        08-26-98       LAM         added 20psi str for small cylinders
     2.258        08-27-98       LAM         Updated to ver 5.0y,added update cal
                                             string,added default string
     2.259        09-01-98       BJB         Deleted strings no longer needed by
                                              digital tune screens.
     2.260        09-02-98       LAM         chged 20psi to 25psi,chged complete string
     2.261        09-03-98       BJB         On sys info screen, AE shows as ae/ao,
                                              AED as aed/aod, AEF as aef/aof.
     2.262        09-08-98       LAM         Updated to ver 5.0z.
     2.263        09-10-98       LAM         Updated to ver 5.aa.
     2.264        09-15-98       LAM         Updated to ver 5.ab.
     2.265        09-23-98       LAM         Updated to ver 5.ac.
     2.266        09-30-98       LAM         Updated to ver 5.ad., chged default to
                                             factory.
     2.267        10-01-98       PaulG       Added StrColdStartMsg6[] string.
     2.268        10-02-98       LAM         Updated to ver 5.ae.
     2.269        10-06-98       LAM         Updated to ver 5.af.
     2.270        10-06-98       PaulG       Modify StrColdStartMsg6[] string.
     2.271        10-09-98       BEKymer     Change StrME_11 to Bad Mode so its
                                             less than 10 characters
     2.272        10-14-98       LAM         changed default to factory default
     2.273        10-16-98       LAM         Updated to ver 5.ag.
     2.274        10-20-98       LAM         Updated to ver 5.ah.
     2.275        10-21-98       LAM         Updated to ver 5.ai.
     2.276        10-28-98       LAM         Updated to ver 5.aj.
     2.277        10-30-98       LAM         Updated to ver 5.ak, changed cal standards
                                             to Cal Full System.
     2.278        11-02-98       PaulG       Modify text strings StrM8_2[], StrM8_2A[]. 
     2.279        11-04-98       LAM         Updated to ver 5.al, changed sys pressure to
                                             actual pressure
     2.280        11-10-98       LAM         Updated to ver 5.am, added 15/30khz text strings,
                                             added 5PSI string
     2.281        11-18-98       LAM         Updated to ver 5.an.
     2.282        11-25-98       LAM         Updated to ver 5.ao.
     2.283        11-25-98       LAM         Updated to ver 5.ap.
     2.284        12-01-98       LAM         Updated to ver 5.aq.
     2.285        12-01-98       BJB         Added strings for 15/30khz Branson menu.
     2.286        12-08-98       LAM         Updated to ver 5.ar.
     2.287        12-09-98       LAM         Updated to ver 5.as.
     2.287        12-09-98       LAM         Updated to ver 5.at.
     2.288        12-15-98       LAM         Updated to ver 5.au.
     2.290        12-17-98       LAM         Updated to ver 6.00(Release 2.5).
     2.291        03-12-99       BEKymer     Added 5 StrBranf0_ strings
     2.291        03-15-99       LAM         Updated to ver 6.f0
     2.292        05-12-99       JZ          Added menu strings for Rapid Traverse and Force 
     2.293        05-14-99       JZ          Added string for SetForce
     2.294        05-19-99       JZ          Changed R/T Ramp to R/T Rate, Return Ramp to
                                             Return Rate
     2.295        05-26-99       LAM         Updated copyright string to 99, chged ver to
                                             6.f2
     2.296        05-27-99       JZ          added StrAE, StrAED, StrAEF     
     2.297        06-04-99       JHenry      added more strings for menuhorn.c updates                                     
     2.298        06-10-99       JHenry      Deleted duplicate "Rapid Traverse" string.
     2.299        06-10-99       LAM         updated ver to 7.f0
     2.300        06-10-99       CMC         added changes for new CalForceMenu(s)
     2.301        06-16-99       LAM         updated ver to 7.f1, fixed lowercase done,
                                             added changes per Jack's code review
     2.302        06-17-99       JZ          changed Set Force in running buffer                                        
     2.303        06-17-99       CMC         delete temporary strings StrMX_12 thru StrMX_21C
     2.304        06-17-99       CMC         chg all StrMH_18 to StrM2_41
     2.305.3.0    07-09-99       CMC         change StrMH_15 from "Trigger" to "Horn Down Clamp"
     2.305.3.1    07-12-99       LAM         updated ver to 7f12
     2.305.3.3    07-23-99       JLH        Added strings needed for 3 load cell readings. 
     2.307        07-30-99       OFI        Changed "/" to "-" and updated ver to 7.f2
     2.308        08-02-99       OFI        updated ver to 7f2a
     2.309        08-03-99       JZ         fixed spelling
     2.310        08-11-99       JZ         added strings for StartRamp 
     2.311        08-11-99       LAM        updated ver to 7f3a
     2.312        08-16-99       LAM        updated ver to 7f3b
     2.313        08-23-99       JZ         added strings for part contact, gain factor, min trigger
     2.314        08-25-99       OFI        updated ver to 7f3c
     2.315        08-23-99       JZ         changed StrVelocityPC, chngd rev to 7f3d
     2.316        08-25-99       OFI        fixed 0 in part contact string
     2.317        08-25-99       OFI        updated ver to 7f3e
     2.318        08-25-99       OFI        updated ver to 7f3f
     2.319        09-01-99       JZ         added StrFactoryD string, removed StrMH_14
     2.320        09-03-99       JZ         changed StrFactoryD to "Checksum"
     2.321        09-09-99       JLH        Changed text of Calibration Saved menu
     2.322        09-13-99       OFI        updated ver to 7f3g
     2.323        09-20-99       OFI        updated ver to 7f3h
     2.324        09-21-99       OFI        updated ver to 7f3i
     2.325        09-23-99       BEKymer    Added string StrSetSwNum
     2.326        09-23-99       OFI        updated ver to 7f3j
     2.327        10-01-99       OFI        updated ver to 7f4
     2.328        10-14-99       OFI        updated ver to 7f4A
     2.329        10-18-99       OFI        updated ver to 7f4B
     2.330        10-25-99       JZ         fixed spelling in "Override" strings
     2.331        10-26-99       JZ         added StrIdleSpeed
     2.332        11-05-99       OFI        updated ver to 7f4C
     2.333        11-05-99       OFI        updated ver to 7f4D
     2.334        11-15-99       OFI        updated ver to 7f4E
     2.335        11-16-99       OFI        updated ver to 7f4F
     2.336        11-18-99       OFI        updated ver to 7f4G
     2.337        11-19-99       OFI        updated ver to 7f4H
     2.338        12-03-99       OFI        updated ver to 7f4I
     2.339        12-07-99       OFI        updated ver to 7f4H
     2.340        12-10-99       OFI        updated ver to 7.00
     2.341        12-17-99       JZ         deleted strings for AED compatibility
     2.342        12-20-99       OFI        updated ver to 8C00
     2.342.6.1    02-29-00       JLH        Added strings for Spanish and Italian language choices.
     2.342.6.2    04-06-00       SCM        Added string definitions for Diagnostic menu items.
     2.343        02-14-00       OFI        updated ver to 8C01
     2.344        02-28-00       OFI        updated ver to 8C02
     2.345        03-21-00       JLH        Removed IBM proprinter menu text and added HP(PCL) menu text.
     2.346        03-27-00       JZ         updated copyrights info in string InitializingMsg3
     2.347        03-31-00       JZ         deleted  StrMX_51 and updated to 8C03
     2.348        04-07-00       JZ         merged Lang to trunk
     2.349        04-14-00       SCM        Added string definitions for the Run Screen Menu.
     2.350        04-14-00       SCM        Added string definition for Verify Preset.
     2.351        04-18-00       SCM        Added string definitions for System Information menu
                                            (Ver 8 ORS definition)
     2.352        04-19-00       SCM        No additions done.Checked in to do a build.
     2.353        04-20-00       SCM        This version not tested or built.
     2.353        05-20-00       SCM        Changed string definition to accomodate foreign
                                            language definition.
     2.354        05-26-00       JLH        Added strings for printer type name updates; deleted InkJet and
                                            LaserJet, and added OKI520 and HPPCL.
     2.355        06-02-00       SCM        Added strings for Printer Status and moved  
                                            WeldDataStrPtr from menu1.c.
     2.356        06-07-00       LAM        fixed Estop str to 20chars, fixed strings
                                            used with UpdateLine function, eliminate blanks
                                            strings and used StrBlankLine  
     2.357        06-14-00       SCM        Added strings for the two DEPOT menu structures.
     2.358        06-15-00       SCM        Updated version label to 8L00 for official Ver8 build.
     2.359        06-16-00       LAM        Center "Please Wait"
     2.359.1.0    07-12-00       BEKymer    Added foreign languages              
     2.360        07-13-00       LAM        merger to trunk              
     2.361        07-14-00       BEKymer    Added string StrM6_7F for level ea
     2.362        07-18-00       JLH        Added DUPS text strings
     2.363        07-20-00       SCM        Added the string Str_psdigital[] related to the DUPS P/S.
     2.364        07-22-00       SCM        Changed the string Str_psversion.
     2.365        07-26-00       LAM        merger BEKymer Changed Act Ser# string to Act S/N
     2.366        07-27-00       SCM        Moved the string StrM6_23 to menu6.c
     2.367        07-27-00       BEKymer    Fix many string lengths and alignment problems
     2.368        07-27-00       SCM        Fixed a few string problems.
     2.368        08-07-00       DJL        Made changes to software version for 8L01A build
     2.370        08-08-00       LAM        fixed french string
     2.371        08-08-00       JLH        Fixed truncation of Done for preset name and password entry.
     2.372        08-09-00       DJL        Made changes to display string for software version 8L01B build
     2.373        08-11-00       SCM        Added strings for Save Preset(Error display) .
     2.374        08-14-00       LAM        deleted unused calibration strings
     2.375        08-15-00       DJL        Made changes to the file from the new 8-03 Omnilangua file
     2.376        08-16-00       LAM        fixed warning & gauge strings
     2.377        08-17-00       LAM        fixed "done" string
     2.378        08-18-00       LAM        fixed "continue" string & deleted multiple copies
     2.379        08-23-00       AT         StrM8_45C - moved 'Page Size' 1 char left, StrOff must be same length as StrOn
     2.381        08-23-00       DJL        Renamed software version for the 8L02a build
     2.382        08-29-00       BEKymer    Corrected spacing on many strings
     2.382        08-29-00       DJL         Made changes from the final omnilingua version of the file 
                                             changed Down Speed to Downspeed.
     2.383        08-29-00       DJL        Made changes to the strings continue, OK, cancel,done to make sure
                                             that they were right justified in the display                                      
     2.384        08-30-00       LAM        deleted unused custom strings
     2.385        08-30-00       LAM        found more unused strings
     2.386        08-31-00       BEKymer    Made StrM6_8A 5 characters for compatability with RCS program 
     2.387        08-31-00       SRP        StrM3_9A made 17 characters.
     2.388        09-02-00       LAM        updated ver to 8l07       
     2.389        09-06-00       LAM        updated ver to 8l08 & fixed #3353       
     2.390        09-06-00       BEKymer    Fixed some strings to agree with printout
                                             (may be wrong now, but they agree)
                                             DCS issue # 3549, 3550, 3551
     2.391        09-06-00       BEKymer    Manual translation of string StrMH_19
     2.392        09-08-00       BEKymer    Fix string StrM2_60 so its consistant with similiar strings  DCS # 3547
                                            Fix string StrM2_46 so its consistant with similiar strings  DCS # 3548
    2.393         09-15-00      DJL         Changed version 8L08 to 8RCS for the unofficial RCS Build.
    2.393         09-18-00      LAM         Changed other str from 8L08 to 8RCS for the unofficial RCS Build.
    2.395         09-20-00      JLH         Eliminated unneeded trailing spaces for Werk and Usine in StrDefault.
    2.396         09-21-00      AT          Added TxtHSScanning and TxtHSComplete strings
    2.397         09-22-00      BEKymer     Added string StrM3_0F for use by ALPHA menu structure
    2.398         09-22-00      BEKymer     Converted Save portion of string StrM3_0F to uppercase
    2.399         09-29-00      DJL         Made changes to the display for the 8L09 build
    2.400         10-04-00      LAM         Added TxtHSOverload string ISSUE(3597)
    2.401         10-04-00      SCM         Modified string WeldDataStrPtr[6].
    2.402         10-06-00      SCM         Modified string for the '8L10' official build.
    2.403         10-06-00      SCM         Modified string(again!) for the '8L10' official build.
    2.404         10-11-00      SCM         Modified string for the '8L11' official build.
    2.405         10-19-00      SCM         Modified the strings StrM8_41A and StrM8_41D.
    2.406         10-22-00      LAM         Modified string for the '8L12' official build.
    2.407         10-31-00      AT          Changed Saut to Pas in french
    2.408         10-31-00      AT          Removed spaces at end of StrSlowest
    2.409         11-01-00      AT          Language issues (too many to list)
    2.410         11-01-00      AT          Fixed Slowest/Fastest strings for languages.
    2.411         11-01-00      AT          More fixes for fast (italian).
    2.412         11-01-00      AT          'Force Step rate' for french.
    2.413         11-02-00      AT          More language fixes.
    2.414         11-02-00      AT          More language fixes.
    2.415         11-03-00      AT          Spanish fixes.
    2.416         11-03-00      BEKymer     Change manual reference from 7.3 to 7.2
                                            Modified string for the '8L13' official build.
    2.417         11-09-00      SCM         Modified string for the '8L14' official build.
    2.418         11-10-00      AT          Horn scan strings
    2.419         11-14-00      AT          More translations
    2.420         11-14-00      LAM         More translations.Modified string for the 
                                            '8L15' official build
    2.421         11-15-00      LAM         Modified string for the '8L16' official build.
    2.422         11-17-00      BEKymer     Modified string for the '8L17' official build.
    2.423         11-17-00      LAM         Modified string for the '8L18' official build.
    2.424         11-20-00      LAM         Modified string for the '8L19' official build.
    2.425         11-27-00      LAM         Modified string for the '8.00' official build.
    2.426         12-13-00      LAM         Modified string for the '8M00' official build.
    2.427         01-02-00      DJL         MOdified string for the '8.01' official build.
    2.425.1.3     03-08-01      LAM/AT      updated french
    2.425.1.4     03-14-01      LAM/AT      updated german & french
    2.425.1.5     03-20-01      LAM/AT      all foreign language updates
    2.425.1.6     03-26-01      LAM         Modified string for the '8.02' official build.
    2.427         01-18-01      BEKymer     Upgrade version, remove unused '01, 02'... strings                                            
                                             Changed copyright to 2001
                                            Remove duplicate strings StrM7_53, StrM7_56
                                             StrM7_59, StrM7_62, StrM7_68, StrM7_71, StrM7A_53N
                                            Remove unused strings: StrM3_1                                                
                                            Added strings: StrPreset, StrName, StrCycleCount                   
    2.428         03-29-01      LAM         Merged 8.02 and Ver9                                  
    2.425.1.7     04-06-01      DJL         Added new string array for the External Presets
    2.425.1.8     04-09-01      LAM         removed duplicated text strings,m7_58,m7_61,m7_64
    2.425.1.9     04-10-01      BEKymer     Set version to 8.1S for 900 M elimination special
    2.425.1.10    04-16-01      BEKymer     Change StrAE from "ae act" to ae/HH"
                                            Change StrM6_6A from "ae/ao" to "ae/ao/HH"
    2.425.1.11    04-23-01      LAM         Added translations to External Presets & handheld
    2.425.1.12    04-30-01      LAM         changed strM6_5F & strBranWatts from 4400 Watts to 
                                            4000 Watts
    
    2.425.1.13   05-18-01       DJL         Made changes from 8.1s to 8.1sa for 8.1sa build.  
    2.425.1.14   05-18-01       DJL         Moved the version label 1 space to the left, because
                                            the maximum allowed letters is 5. 
    2.425.1.15   05-18-01       DJL         Made changes from 8.1sa to 8.1sb for 8.1sb build 
    2.425.1.16   06-05-01       DJL         Made changes from 8.sb to 8.1s for 8.1s official build                                                                               
    2.425.1.17   06-27-01       BEKymer     Change to 8.1SC, add M7A_41P, M7A_46E, M7A_52Y, M7A_52Z
    2.425.1.18   06-28-01       DJL         Made changes to label from 8.1sc to 8.1sd for new build
    2.425.1.19   07-02-01       DJL         Changed the software version from 8.1sd to 8.1se
    2.425.1.20   07-03-01       DJL         Changed the version label from 8.1se to 8.1s for official build.
    2.425.1.21   08-20-01       BEKymer     Added text to support RS232 ASCII, updated software version
    2.425.1.22   08-21-01       BEKymer     Detab    
    2.425.1.22.1.1 09-11-01       LAM         Official 8.2S build    
    2.425.1.22.1.2 10-11-01     LAM         Official AA8.05 build added 8.2S foreign languages strings
                                            except for disabled being translated.    
    2.425.1.22.1.3 10-29-01     BEKymer     Change string for B8.05 build, add Disabled translation
    2.425.1.22.1.4 11-02-01     LAM         Official 8.05 build
    2.425.1.22.1.5 04-03-02     BEKymer     Add strings for "Actuator Coldstart" and "Debug"
    2.425.1.22.1.4.2.1 04-04-02 BEKymer     Add translations for "Actuator Coldstart"
    2.425.1.22.1.4.2.2 04-17-02 BEKymer     Add StrM5_49 for debugger
    2.425.1.22.1.4.2.3 04-25-02 BEKymer     Add a string for 6000 Watts (actually use 2500 W)
    2.425.1.22.1.4.2.3 05-06-02 LAM         Change string for B8.06 build
    2.425.1.22.1.4.2.4 05-07-02 LAM         Change string for C8.06 build
    2.425.1.22.1.4.2.5 05-08-02 LAM         Change string for D8.06 build
    2.425.1.22.1.4.2.6 05-17-02 LAM         Change string for E8.06 build
    2.425.1.22.1.4.2.8 05-23-02 BEKymer     Add strings for P/S Clear, Auto and P/S Coldstart
    2.425.1.22.1.4.2.9 06-05-02 DJL         Changed string E8.06 to 8.06 for official build
2.425.1.22.1.4.2.8.1.0.1.0  11-21-02  SCM   Made changes to various strings for German Language 
                                            as part of version 8.07.
    2.425.1.22.1.4.2.8.1.0.1.1 11-22-02 LAM  Changed string 8.06 to A807 for official build
    2.425.1.22.1.4.2.8.1.0.1.2 01-15-03 SCM  Made further changes to various strings for German  
                                             Language as part of version A808
    2.425.1.22.1.4.2.8.1.0.1.2.1.0 03-21-03  SCM  Made further changes to various strings for German  
                                                  Language as part of version c808
    2.431        04-10-03       BEKymer     Move back to tip as 2.431
    2.432        04-11-03       BEKymer     Change ver to A8.10
    2.433        04-17-03       BEKymer     Change ver to B8.10 (Cyber has a copy
                                             of A8.10 so it had to change)    
    2.434        05-27-03       BEKymer     Change ver to C8.10
    2.435        06-23-03       BEKymer     Change ver to D8.10
    2.436        07-08-03       BEKymer     Change ver to E8.10
    2.437        07-09-03       BEKymer     Change ver to 8.10 for official build
    2.425.1.22.1.4.2.8.1.0.1.2.1.0 05-19-03 SCM  Change string for TS01 complete build.
    2.425.1.11.1.4.2.8.1.0.1.2.3.1 06-16-03 JOY  Added Language Strings for QVGA.
    2.425.1.11.1.4.2.8.1.0.1.2.3.0.1.1 06-16-03 JOY  Added Language Strings for QVGA.
    2.438        07-25-03       LAM         merged 8.10 with TS01     
    2.439        08-03-03       JOY         Added Language strings.
    2.440        08-19-03       LAM         change ver to G820.
    2.441        08-22-03       LAM         change ver to H820.
    2.442        08-29-03       LAM         change ver to I820.
    2.443        09-12-03       JOY         Added Language strings.
    2.444        09-15-03       LAM         change ver to J820.
    2.445        09-22-03       JOY         Added Language Strings.
    2.446        09-23-03       LAM         change ver to K820.
    2.447        09-24-03       LAM         removed ID from assign ID
    2.448        09-27-03       LAM         change ver to L820.
    2.449        09-30-03       JOY         Modified Language string.
    2.450        09-30-03       LAM         change ver to M820.
    2.451        10-03-03       JOY         Added Language strings.
    2.452        10-03-03       LAM         change ver to N820.
    2.453        10-14-03       JOY         Added Language strings.
    2.454        10-15-03       LAM         modified Language strings change ver O820
    2.455        10-20-03       LAM         modified Language strings change ver P820
    2.456        10-24-03       JOY         Added New strings.
    2.457        11-02-03       LAM         change ver to q820.
    2.458        11-03-03       LAM         modified translation strings
    2.459        11-05-03       LAM         change ver to r820.
    2.460        11-13-03       LAM         change ver to s820.
    2.461        11-13-03       LAM         modified translation strings
    2.462        11-21-03       LAM         change ver to 820, added final translations.
    2.463        11-24-03       LAM         corrected compiler error
    2.465        12-04-03       BEKymer     Merged 2.464 & 2.437.1.1 to create 2.465
                                             Ver9.00b build
    2.466        12-10-03       BEKymer     Added back in the strings for preset numbers,
                                             need to be removed when qvgapreset.c is
                                             rewritten to handle arguments.
                                            Remove StrM7_70 (Pres Correction)
    2.467        02-11-04       BEKymer     Change version to D9.00 for external preset build
    2.468        02-12-04       BEKymer     Add StrTesting & StrSpecials
                                            Change version to E9.00 for testing menus
    2.469        02-20-04       VSharma     Added StrReleaseBeep, Str_WriteIn1, Str_WriteIn2,
                                            Str_ExecuteMsg2 & Str_BransonFunc.
                                            Shifted VerifyPresetName,InfoPresetName,InfoVerifiedYes &
                                            InfoVerifiedNo from menu3.c.
                                            Change Ver to F9.00.
    2.470        03-09-04       VSharma     Added StrExecuteMsg1 & Str_OverwriteAll.
    2.471        03-28-04       LAM         Change Ver to G9.00.
    2.472        04-06-04       VSharma     Added Str_SeriesF & Str_ParallelF.
                                            Modified WeldDataStrPtr.
                                            Change Ver to H9.00.                
    2.473        04-19-04       VSharma     Added StrDUPSTemp & StrInterlockDelay.
    2.474        05-03-04       VSharma     Modified StrM7_89 & StrM7_93.Added StrM7_70I.
    2.475        05-07-04       LAM         Built 9.00i
    2.476        05-17-04       VSharma     Removed unused strings.
    2.477        06-10-04       BEKymer     Added string StrM7_41 for Welder Addr
    2.478        06-17-04       VSharma     Made language updates for Ver9.00 strings.
    2.479        06-18-04       BEKymer     Changed MAXSCROLLMENUS to RMAXPARAMETERS and added
                                             second copy of Velocity strings to handle aed
                                             and aef as separate entities.
    2.480        06-23-04       JOY         Foreign language strings changed back to Ver 8.21 strings.   
    2.481        06-24-04       BEKymer     Merged 2.479 & 2.480 to create 2.481
                                             for Ver9.00l build
    2.482        07-07-04       BEKymer     Added string StrM0_17[] for Touch Screen init
    2.483        07-12-04       BEKymer     Changed wattage strings from 2500W
                                             to 200W for Ahmet special
    2.484        07-14-04       BEKymer     Change version to M9.00 for mongrel horde build
    2.485        07-27-04       JOY         Added String Str_60KHZ.
    2.486        08-02-04       BEKymer     Change Ext Trigger to Ext Signal
                                            Change version to N9.00 for 2nd round
                                              of testing
    2.487        08-18-04       JOY         Added Str_SVDelay[].
    2.488        08-24-04       JOY         String 'SV Interlock' is replaced to 'External Start'.
                                            String 'Ext trg Delay' is replaced to 'Ext U/S Delay'.
    2.489        08-26-04       JOY         Modified string Str_SVDelay[];
    2.490        08-02-04       JOY         Modified string StrTriggerDelay[].
    2.491        09-02-04       BEKymer     Uppercase StrTriggerDelay strings
                                            Change StrInterlockDelay text to 
                                             EXT START DELAY
    2.492        09-07-04       BEKymer     Change build to O9.00
    2.493        09-16-04       BEKymer     Change build to p9.00
    2.494        09-23-04       BEKymer     Change build to 9.00 for official release
    2.495        10-04-04       BEKymer     Change build to a9.01
    2.496        10-27-04       BEKymer     Change build to b9.01
    2.497        10-27-04       BEKymer     Change build to 9.01 for official build
    2.498        11-15-04       BEKymer     Change build to 9.02 for official build
    2.498.2.0    02-03-05       BEKymer     Change build to 9.03a for official build    
    2.498.2.1    02-10-05       BEKymer     Change build to 9.03b
    2.498.2.2    02-23-05       BEKymer     Change build to 9.03c
    2.498.2.3    03-03-05       BEKymer     Change build to 9.03
    2.498.2.4    04-01-05       Aare        Fix for 4 flash build
    2.498.2.3.1.1  04-06-05     LAM         SBeam build    
    2.498.2.3.1.2  04-26-05     LAM         deleted power calb strings 
    2.498.2.3.1.3  05-04-05     LAM         deleted contrast strings 
    2.498.2.3.1.4  05-27-05     Bwadia      Added strings for Auto Refresh
                                            and view graphs
                                                           
                                                 
*/
/* ------------------------------- DESCRIPTION -----------------------------*/
 
/* This file will contain all the text (except for alarms and printing)     */
/* for all languages.                                                      */

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/


#include "portable.h"
#include "menu.h"

/* This section will go into flash that starts at 2MB. */
#pragma section CONST  ".lang"
#pragma section STRING ".lang"
#pragma section CODE   ".lang"

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/



/******************************************************************************/
/*   The languages will be defined in the following order:                    */
/*       English                                                              */
/*       German                                                               */
/*       Spanish                                                              */
/*       Italian                                                              */
/*       French                                                               */
/*                                                                            */
/******************************************************************************/
/*-------------  These need to be changed with every version or revision  ------------*/

const UINT16  CurrentVersion =1000;    /* Current version/revision in binary, no decimal */

const STR *const StrM6_8[]   =  { "S/W Version   =10.0c",
                                  "S/W Version   =10.0c",
                                  "Version SOFT  =10.0c",
                                  "Versione Int. =10.0c",
                                  "Version Log   =10.0c"  };

const STR *const StrM6_8A[]  =  { "10.0c",       /* A total of 5 characters VV.RR */
                                  "10.0c",       /* where VV = Version            */   
                                  "10.0c",       /*       RR = Revision           */
                                  "10.0c",       /* is needed for the RCS program */
                                  "10.0c"  };

/*--------------  End of revision/version change --------------*/



const STR *const StrOff[]   =    { "Off",
                                   "0",
                                   "0",
                                   "0",
                                   "0"  };

const STR *const StrOn[]    =    { "On ",
                                   "1",
                                   "1",
                                   "1",
                                   "1"  };

const STR *const StrDefault[] =  { "Factory",
                                   "Werk",
                                   "Fabrica",
                                   "Fabbric",
                                   "Usine"  };

const STR *const StrBlank[] =    { " ",
                                   " ",
                                   " ",
                                   " ",
                                   " "  };

const STR *const StrStep[]  =    { "STEP",
                                   "PROFIL",
                                   "PASO",
                                   "STEP",
                                   "SAUT"  };

const STR *const StrFixed[] =    { "FIXED",
                                   "FEST",
                                   "FIJA",
                                   "FISSA",
                                   "FIXE"  };

const STR *const StrPage[]  =    { "Pg",
                                   "S.",
                                   "Pg",
                                   "Pg",
                                   "Pg"  };

const STR *const StrAsterisk[] = { "*",
                                   "*",
                                   "*",
                                   "*",
                                   "*"  };

const STR *const StrAuto[]  =    { "Auto",
                                   "Auto",
                                   "Auto",
                                   "Auto",
                                   "Auto"  };

const STR *const StrSetForce[] = { "Set Force(&&) =     ",
                                   "Soll Kraft(&&)=     ",
                                   "Ajs Fuerz(&&) =     ",
                                   "Impost forza(&&)=   ",
                                   "Reg Force(&&) =     "  };

const STR *const Str60psi[] =    { "SetPres=60PSI/415kPa",
                                   "Drkstel=60PSI/415kPa",
                                   "AjsPres=60PSI/415kPa",
                                   "ImpPres=60PSI/415kPa",
                                   "SetPres=60PSI/415kPa"  };

const STR *const Str80psi[] =    { "SetPres=80PSI/553kPa",
                                   "Drkstel=80PSI/553kPa",
                                   "AjsPres=80PSI/553kPa",
                                   "ImpPres=80PSI/553kPa",
                                   "SetPres=80PSI/553kPa"  };

const STR *const StrForceRamps[]={ "Force Ramps>",
                                   "Kraft Rampe> ",
                                   "Rampas Frza>",
                                   "Rampe forza>",
                                   "Rpes Force> "  };

const STR *const StrForceRampst[]={"Force Ramps",
                                   "Kraft Rampe",
                                   "Rampas Frza",
                                   "Rampe forza",
                                   "Rpes Force"  };

const STR *const StrWeldFRate[]= { "Weld F Rate",
                                   "Schw.K.Rampe",
                                   "Tasa F Sold",
                                   "Vel. F sald",
                                   "Taux F Soud"  };

const STR *const StrStepFRate[]= { "Step F Rate",
                                   "Prof. K. Rampe",
                                   "Tasa F Paso",
                                   "Vel. step F",
                                   "Saut Tx F"  };

const STR *const StrHoldFRate[]= { "Hold F Rate",
                                   "Haltekr.rmp",
                                   "Idce F Mant",
                                   "Vel F  Raff",
                                   "Tx F Maint"  };

const STR *const StrSlowest[]  = { "Slowest",
                                   "sehr langsam",
                                   "Mas len",
                                   "Molt len",
                                   "Minimum"  };

const STR *const StrSlowestW[] = { "Weld F Rate> Slowest",
                                   "SKR>    sehr langsam",
                                   "Tasa F Sold> Mas len",
                                   "Vel. F sald>Molt len",
                                   "Taux F Soud> Minimum"  };

const STR *const StrSlowestS[] = { "Step F Rate> Slowest",
                                  "PKR>    sehr langsam",
                                   "Tasa F Paso> Mas len",
                                   "Vel. step F>Molt len",
                                   "Saut Tx F>   Minimum"  };

const STR *const StrSlowestH[] = { "Hold F Rate> Slowest",
                                   "Haltekr.rmp>sehr lng",
                                   "Idce F Mant> Mas len",
                                   "Vel F Raff> Molt len",
                                   "Tx F Maint>  Minimum"  };

const STR *const StrSlow[]    =  { "Slow",
                                   "langsam",
                                   "Lento",
                                   "Lento",
                                   "Lent"  };

const STR *const StrSlowW[]   =  { "Weld F Rate>    Slow",
                                   "SKR>         langsam",
                                   "Tasa F Sold>   Lento",
                                   "Vel. F sald>   Lento",
                                   "Taux F Soud>    Lent"  };

const STR *const StrSlowS[]   =  { "Step F Rate>    Slow",
                                   "PKR>         langsam",
                                   "Tasa F Paso>   Lento",
                                   "Vel. step F>   Lento",
                                   "Saut Tx F>      Lent"  };

const STR *const StrSlowH[]   =  { "Hold F Rate>    Slow",
                                   "Haltekr.rmp> langsam",
                                   "Idce F Mant>   Lento",
                                   "Vel F Raff>    Lento",
                                   "Tx F Maint>     Lent"  };

const STR *const StrNormal[]  =  { "Normal",
                                   "normal",
                                   "Normal",
                                   "Normale",
                                   "Normal"  };

const STR *const StrNormalW[]  = { "Weld F Rate>  Normal",
                                   "SKR>          normal",
                                   "Tasa F Sold>  Normal",
                                   "Vel. F sald> Normale",
                                   "Taux F Soud>  Normal"  };

const STR *const StrNormalS[]  = { "Step F Rate>  Normal",
                                   "PKR>          normal",
                                   "Tasa F Paso>  Normal",
                                   "Vel. step F> Normale",
                                   "Saut Tx F>    Normal"  };

const STR *const StrNormalH[]  = { "Hold F Rate>  Normal",
                                   "Haltekr.rmp>  normal",
                                   "Idce F Mant>  Normal",
                                   "Vel F Raff>  Normale",
                                   "Tx F Maint>   Normal"  };

const STR *const StrFast[]    =  { "Fast",
                                   "schnell",
                                   "Rapido",
                                   "Rapida",
                                   "Rapd"  };

const STR *const StrFastW[]    = { "Weld F Rate>    Fast",
                                   "SKR>         schnell",
                                   "Tasa F Sold>  Rapido",
                                   "Vel. F sald>  Rapide",
                                   "Taux F Soud>    Rapd"  };

const STR *const StrFastS[]    = { "Step F Rate>    Fast",
                                   "PKR>         schnell",
                                   "Tasa F Paso>  Rapido",
                                   "Vel. step F>  Rapida",
                                   "Saut Tx F>      Rapd"  };

const STR *const StrFastH[]    = { "Hold F Rate>    Fast",
                                   "Haltekr.rmp> schnell",
                                   "Idce F Mant>  Rapido",
                                   "Vel F Raff>   Rapida",
                                   "Tx F Maint>     Rapd"  };

const STR *const StrFastest[] =  { "Fastest",
                                   "sehr schnell",
                                   "Mas rap",
                                   "Molt rap",
                                   "Maximum"  };

const STR *const StrFastestW[] = { "Weld F Rate> Fastest",
                                   "SKR>    sehr schnell",
                                   "Tasa F Sold> Mas rap",
                                   "Vel. F sald>Molt rap",
                                   "Taux F Soud> Maximum"  };

const STR *const StrFastestS[] = { "Step F Rate> Fastest",
                                   "PKR>    sehr schnell",
                                   "Tasa F Paso> Mas rap",
                                   "Vel. step F>Molt rap",
                                   "Saut Tx F>   Maximum"  };

const STR *const StrFastestH[] = { "Hold F Rate> Fastest",
                                   "Haltek.rmp>sehr schn",
                                   "Idce F Mant> Mas rap",
                                   "Vel F Raff> Molt rap",
                                   "Tx F Maint>  Maximum"  };

const STR *const StrBlankLine[] = {"                    ",
                                   "                    ",
                                   "                    ",
                                   "                    ",
                                   "                    "  };

const STR  StrAlpha1[] =   "ABCDEFGHIJKLM./01234";

const STR  StrAlpha2[] =   "NOPQRSTUVWXYZ# 56789";

const STR *const StrColdStartMsg1[] = {"     Cold Start     ",
                                       "     Kaltstart      ",
                                       "     Arque Frio     ",
                                       "     Cold Start     ",
                                       "     Param Usine    "  };

const STR *const StrColdStartMsg2[] = {"     In Process     ",
                                       "     In Arbeit      ",
                                       "     En Proceso     ",
                                       "     In Corso       ",
                                       "     En Cours       "  };

const STR *const StrColdStartMsg3[] = {" Cold Start Complete",
                                       " Kaltstart abgeschl.",
                                       " Arque Frio Completo",
                                       " Cold Start Completo",
                                       " Param Usine Charges"  };

const STR *const StrColdStartMsg4[] = {" Please Wait for    ",
                                       " Bitte warten auf   ",
                                       " Por favor espre que",
                                       " Attendere prego    ",
                                       " Attdre SVP         "  };

const STR *const StrColdStartMsg5[] = {" Cycle to Complete  ",
                                       " Zyklus beenden     ",
                                       " Ciclo se complete  ",
                                       " Ciclo da completare",
                                       " Cycle a effectuer  "  };

const STR *const StrColdStartMsg6[] ={ "or Printing to Stop.",
                                       "oder Druckende.",
                                       "o termine la impres.",
                                       "o stampa da intrmpr.",
                                       "ou imprsn jusq.arrt."  };

const STR *const StrColdStartMsg7[] ={ "Custom Digital UPS  ",
                                       "Einst. DUPS         ", //detrans 8/21
                                       "F/A. Digital Person ", //   8/21
                                       "Person UPS digital  ", //  8/21
                                       "GUD Special  "  }; //frtrans 8/21

const STR *const StrColdStartMsg8[] ={ "is out of memory.   ",
                                       "ungenuegend Speicher", //detrans 8/21
                                       "memoria llena.   ", //  8/21
                                       "is out of memory.   ", //  8/21
                                       "memoire insuff.   "  }; //frtrans 8/21

const STR *const StrColdStartMsg9[] ={ "Clear a preset      ", 
                                       "Loesche Voreinst.   ", //detrans 8/21
                                       "Borrar una presl    ", //  8/21
                                       "Eff. un prereg      ", //  8/21
                                       "Cncl un preset      "  }; //frtrans 8/21

const STR *const StrAE[] = {           "ae/HH",
                                       "ae/HH",
                                       "ae/HH",
                                       "ae/HH",
                                       "ae/HH"  };

const STR *const StrAED[] ={           "aed act",
                                       "aed VE",
                                       "aed act",
                                       "aed act",
                                       "aed act"  };

const STR *const StrAEF[] = {          "aef act",
                                       "aef VE",
                                       "aef act",
                                       "aef act",
                                       "aef act"  };

const STR *const StrResetMsg[]  = {    "       RESET        ",
                                       "       RESET        ",
                                       "       RESET        ",
                                       "       RESET        ",
                                       "        RAZ         "  };

const STR *const StrResetCompleteMsg[] = { "      COMPLETE      ",
                                           "      KOMPLETT      ",
                                           "      COMPLETO      ",
                                           "      COMPLETO      ",
                                           "      TERMINE       "  };

const STR *const StrM0_0[] =   {       "Main Menu           ",
                                       "Hauptmenu           ",
                                       "Menu Princ.         ",
                                       "Menu prcn           ",
                                       "Menu prnc           "  };

const STR *const StrM0_1[] =   {       "Run Screen",
                                       "Schweissen",
                                       "Eje Pantla",
                                       "Eseg Scren",
                                       "Ecran Exe"  };

const STR *const StrM0_2[] =   {       "Weld Setup",
                                       "Parameter",
                                       "Config Sold",
                                       "Setup Sald",
                                       "Confg Soud"  };

const STR *const StrM0_3[] =   {       "Save/Recall Presets",
                                       "Vorein. speich/abruf",
                                       "Guar/Extr. Preselec.",
                                       "Salva/Richma Preset",
                                       "Enrg/Rappel Presets"  };

const STR *const StrM0_4[] =   {       "Print Menu",
                                       "Druckmenu ",
                                       "Impr. Menu",
                                       "Menu Stamp",
                                       "Impr Menu"  };

const STR *const StrM0_6[] =   {       "System Information",
                                       "Systeminformation",
                                       "Informacion Sist.",
                                       "Informazion Sistem",
                                       "Information Syst."  };

const STR *const StrM0_7[] =   {       "System Configuration",
                                       "Systemkonfiguration",
                                       "Configuracion Sist.",
                                       "Configuraz. Sist.",
                                       "Configuration Syst."  };

const STR *const StrM0_9[] =   {       "Depot Configuration",
                                       "Depot Konfiguration",
                                       "Configuracion Depo",
                                       "Configuraz iniziale",
                                       "Configuration Depot"  };
                                   
const STR *const StrM0_10[] =   {      "Configure Unit",
                                       "Einheit konfig.",
                                       "Configurar Ud",
                                       "Configura Unit",
                                       "Config. Unite"  };

const STR *const StrM0_11[] =   {      "View Setup",
                                       "Ansicht Einrichten",
                                       "Ver config.",
                                       "Impostazione vista",
                                       "Voir Setup"  };

const STR *const StrM0A_0[] =  {       "Set Defaults", 
                                       "Voreinstell.",
                                       "Ajustes def.",
                                       "Set Defaults",
                                       "Param Usine"  };

const STR *const StrM0_12[] =  {       "User I/O >",
                                       "Benutzer I/O >",
                                       "Usuario I/O >",
                                       "Utente O/I >",
                                       "E/S Client >"  };

const STR *const StrM0_13[] =  {       "Actuator >", 
                                       "VE >",
                                       "Actuador >",
                                       "Actuator >",
                                       "Actuator >"  };

const STR *const StrM0_14[] =  {       "System Constants >",    /**** MUST BE TRANSLATED ****/
                                       "System Constants >",
                                       "System Constants >",
                                       "System Constants >",
                                       "System Constants >"  };

const STR *const StrM0_15[] =  {       "Printing >",  
                                       "Drucken >",
                                       "Imprmndo >",
                                       "Stampa >",
                                       "Impressn >"  };

const STR *const StrM0_16[] =  {       "Reset All >",
                                       "Alles Reset >",
                                       "Resetar todo >",
                                       "Reset tutto >",
                                       "Reset complet >"  };

const STR *const StrM0_17[] =  {       "Touch Screen >",
                                       "Touch Screen >",
                                       "Touch Screen >",
                                       "Touch Screen >",
                                       "Touch Screen >"  };

const STR *const WeldDataStrPtr[RMAXPARAMETERS][LANGSIZE] = { 
                                     { "Weld Results>       ",
                                       "Schw Ergebni>       ",
                                       "Resulta Sold>       ",
                                       "Risulti sald>       ",
                                       "Result. Soud>       "  },

                                     { "Cycle# =            ",
                                       "Zykls# =            ",
                                       "Ciclo# =            ",
                                       "Ciclo# =            ",
                                       "Cycle# =            "  },

                                     { "Time(&) =           ",
                                       "Zeit(&) =           ",
                                       "Tiem(&) =           ",
                                       "Tempo(&)=           ",
                                       "Temps(&)=           "  },

                                    {  "Pk Pwr(&) =         ",
                                       "Sp.Lst.(&)=         ",
                                       "Pic.Pot(&)=         ",
                                       "Pc Pot(&) =         ",
                                       "PS CRT(&) =         "  },

                                    {  "Energy(&) =         ",
                                       "Energie(&) =        ",
                                       "Energi(&) =         ",
                                       "Energia(&) =        ",
                                       "Energie(&) =        "  },

                                    {  "Velocity(&&&&) =    ",
                                       "Geschw.(&&&&) =     ",
                                       "Velocida(&&&&) =    ",
                                       "Velocit.(&&&&) =    ",
                                       "Vitesse(&&&&) =     "  },

                                    {  "Velocity(&&&&) =    ",
                                       "Geschw.(&&&&) =     ",
                                       "Velocida(&&&&) =    ",
                                       "Velocit.(&&&&) =    ",
                                       "Vitesse(&&&&) =     "  },

                                    {  "Weld Abs(&&) =      ",
                                       "Weg abs (&&) =      ",
                                       "Sold Abs(&&) =      ",
                                       "Sald Ass(&&) =      ",
                                       "Soud Abs(&&) =      "  },

                                    {  "Total Abs(&&)=      ",
                                       "Abs. Ges.(&&)=      ",
                                       "Total Abs(&&)=      ",
                                       "Total Ass(&&)=      ",
                                       "Total Abs(&&)=      "  },

                                    {  "Weld Col(&&)=       ",
                                       "Weg rel (&&)=       ",
                                       "Sold Col(&&)=       ",
                                       "Sald Col(&&)=       ",
                                       "Soud Col(&&)=       "  },

                                    {  "Total Col(&&)=      ",
                                       "Rel. Ges.(&&)=      ",
                                       "Total Col(&&)=      ",
                                       "Total Col(&&)=      ",
                                       "Total Col(&&)=      "  },

                                    {  "Set Amp A(&) =      ",
                                       "Soll Amp. A(&)=     ",
                                       "Ajs Amp A(&) =      ",
                                       "Set Amp A(&) =      ",
                                       "Reg Amp A(&) =      "  },

                                    {  "Set Amp B(&) =      ",
                                       "Soll Amp. B(&)=     ",
                                       "Ajs Amp B(&) =      ",
                                       "Set Amp B(&) =      ",
                                       "Reg Amp B(&) =      "  },

                                    {  "Set Force A(&&)=    ",
                                       "Soll Amp.A(&)=      ",
                                       "Ajs Fuerz A(&&)=    ",
                                       "Set Forza A(&&)=    ",
                                       "Reg Force A(&&)=    "  },

                                    {  "Set Force B(&&)=    ",
                                       "Soll Amp.B(&)=      ",
                                       "Ajs Fuerz B(&&)=    ",
                                       "Set Forza B(&&)=    ",
                                       "Reg Force B(&&)=    "  },

                                    {  "Weld Force(&&) =    ",
                                       "Schw.Kraft(&&) =    ",
                                       "Fuerza Sold(&&)=    ",
                                       "Forza Sald(&&) =    ",
                                       "Soud Force(&&) =    "  },

                                    {  "Act Press(&&&)=     ",
                                       "VE Druck(&&&)=      ",
                                       "Press act(&&&)=     ",
                                       "Press att(&&&)=     ",
                                       "Act Press(&&&)=     "  },

                                    {  "Freq Min(&&) =      ",
                                       "Freq.Min(&&) =      ",
                                       "Frec Min(&&) =      ",
                                       "Freq Min(&&) =      ",
                                       "Freq Min(&&) =      "  },

                                    {  "Freq Max(&&) =      ",
                                       "Freq.Max(&&) =      ",
                                       "Frec Max(&&) =      ",
                                       "Freq Max(&&) =      ",
                                       "Freq Max(&&) =      "  },

                                    {  "Freq Start(&&)=     ",
                                       "Freq.Start(&&)=     ",
                                       "Inic Frec(&&) =     ",
                                       "Freq Iniz(&&)=      ",
                                       "Freq Debut(&&)=     "  },

                                    {  "Freq End(&&) =      ",
                                       "Freq.Ende(&&)=      ",
                                       "Fin Frec(&&) =      ",
                                       "Freq Fin(&&) =      ",
                                       "Freq Fin(&&) =      "  },

                                    {  "Freq Chg(&&) =      ",
                                       "Freq.Aend(&&)=      ",
                                       "Cam Frec(&&) =      ",
                                       "Camb Freq(&&)=      ",
                                       "Chg Freq(&&) =      "  },
                                       
                                    {  "Preset # =          ", 
                                       "Vorein # =          ",
                                       "Presel # =          ",
                                       "Preset # =          ",
                                       "Preset # =          "  }

                                                                  };

const STR *const StrM1_1[]  =  {       "Adjust Weld>        ",
                                       "Schw einst>         ",
                                       "Ajte Soldad>        ",
                                       "Regola Sald>        ",
                                       "Regler Soud>        "  };

const STR *const StrM1_2[]  =  {       "ADJUST WELD         ",
                                       "SCHW EINST          ",
                                       "AJTE SOLDAD         ",
                                       "REGOLA SALD         ",
                                       "REGLER SOUD         "  };

const STR *const StrM1_3[]  =  {       "Set Other Parameters",
                                       "Weitere Param einst",
                                       "Fij otros parametros",
                                       "Impost altr parametr",
                                       "Reg Autres Parametre"  };

const STR *const StrM1_4[]  =  {       "Amplitude =      Ext",
                                       "Amplitude =      Ext",
                                       "Amplitud =       Ext",
                                       "Ampiezza =       Ext",
                                       "Amplitude =      Ext"  };

const STR *const StrM1_5[]  =  {       "Set Amp(&) =        ",
                                       "Soll Amp.(&) =      ",
                                       "Ajs Amp(&) =        ",
                                       "Imp Amp(&) =        ",
                                       "Reg. Amp(&) =       "  };

const STR *const StrM2_1[]  =  {       "WELD SETUP          ",
                                       "SCHW EINR.          ",
                                       "CONFIG SOLD         ",
                                       "SETUP SALD          ",
                                       "CONFG SOUD          "  };

const STR *const StrM2_2[]  =  {       "Weld Mode>      Time",
                                       "Modus>          Zeit",
                                       "Modo Sold>    Tiempo",
                                       "Mod. di sald>  Tempo",
                                       "Mode Soud>       Tps"  };

const STR *const StrM2_3[]  =  {       "Weld Mode>    Energy",
                                       "Modus>       Energie",
                                       "Modo Sold>    Energi",
                                       "Mod. di sald>Energia",
                                       "Mode Soud>   Energie"  };

const STR *const StrM2_4[]  =  {       "Weld Mode>Peak Power",
                                       "Modus>  Sp. Leistung",
                                       "Modo Sold>Pico Poten",
                                       "Mod sald.> Picco Pot",
                                       "Mode Soud>Pui.-Crete"  };

const STR *const StrM2_5[]  =  {       "Weld Mode>  Collapse",
                                       "Modus>       Weg rel",
                                       "Modo Sold>   Colapso",
                                       "Mod di sald>Collasso",
                                       "Mode Soud>  D. Relat"  };

const STR *const StrM2_6[]  =  {       "Weld Mode>  Absolute",
                                       "Modus>       Weg abs",
                                       "Modo Sold>  Absoluto",
                                       "Mod di sald> Assolut",
                                       "Mode Soud>    D. Abs"  };

const STR *const StrM2_7[]  =  {       "Weld Mode>Gnd Detect",
                                       "Modus> Metallkontakt",
                                       "Modo Sold>Det Tierra",
                                       "Mod sald> Gnd Detect",
                                       "Mode Soud> Det.Masse"  };

const STR *const StrM2_8[]  =  {       "Weld Mode>Continuous",
                                       "Modus>  Kontinuierl.",
                                       "Modo Sold>  Continuo",
                                       "Mod sald>   Continua",
                                       "Mode Soud>   Continu"  };

const STR *const StrM2_10[]  = {       "Weld Time(&)",
                                       "Schw. Zeit(&)",
                                       "Tiem Sold(&)",
                                       "Temp sald(&)",
                                       "Tps Soud(&)"  };

const STR *const StrM2_11[]  = {       "Hold Time(&)",
                                       "Haltezeit(&)",
                                       "Mant Tiem(&)",
                                       "Temp Raff(&)",
                                       "Tps Maint(&)"  };

const STR *const StrM2_12[]  = {       "Trig Force(&&)",
                                       "Trig.Kraft(&&)",
                                       "Fuerza Disp(&&)",
                                       "Forza trig(&&)",
                                       "Force Trig(&&)"  };

const STR *const StrM2_14[]  = {       "Trig Delay(&)",
                                       "Trig Verz(&) ",
                                       "Retard Dsp(&)",
                                       "Ritard Trg(&)",
                                       "Delai Trig(&)"  };

const STR *const StrM2_15[]  = {       "Weld Force(&&)",
                                       "Schw.Kraft(&&)",
                                       "Fuerza Sold(&&)",
                                       "Frza sald(&&)",
                                       "Force Soud(&&)"  };

const STR *const StrM2_15A[] = {       "Weld Force(&&) = ***",
                                       "Schw.Kraft(&&) = ***",
                                       "Fuerza Sold(&&)= ***",
                                       "Forza sald(&&) = ***",
                                       "Force Soud(&&) = ***"  };

const STR *const StrM2_16[]  = {       "Force A(&&)",
                                       "Kraft A(&&)",
                                       "Fuerza A(&&)",
                                       "Forza A(&&)",
                                       "Force A(&&)"  };

const STR *const StrM2_16A[] = {       "Force B(&&)",
                                       "Kraft B(&&)",
                                       "Fuerza B(&&)",
                                       "Forza B(&&)",
                                       "Force B(&&)"  };

const STR *const StrM2_17[]  = {       "Force",
                                       "Kraft",
                                       "Fuerza",
                                       "Forza",
                                       "Force"  };

const STR *const StrM2_17A[] = {       "Force step",
                                       "Kraft Profil",
                                       "Paso Frza",
                                       "Step Forza",
                                       "Saut Force"  };

const STR *const StrM2_19[]  = {       "Step @ T(&)",
                                       "Prof. @ Z(&)",
                                       "Paso @ T(&)",
                                       "Step a T(&)",
                                       "Saut @ T(&) "  };

const STR *const StrM2_20[]  = {       "Step @ E(&)",
                                       "Prof. @ E(&)",
                                       "Paso @ E(&)",
                                       "Step a E(&)",
                                       "Saut @ E(&) "  };

const STR *const StrM2_21[]  = {       "Step @ Pwr(&)",
                                       "Prof. @ Lst.(&)",
                                       "Paso @ Ptn(&)",
                                       "Step a Ptn(&)",
                                       "Saut @ Pss(&) "  };

const STR *const StrM2_22[]  = {       "Step@Col(&&)",
                                       "Prof. @ rel (&&)",
                                       "Paso@Col(&&)",
                                       "Step Col(&&)",
                                       "Saut@DRl(&&) "  };

const STR *const StrM2_23[]  = {       "Step @ Amp(&)",
                                       "Prof. @ Amp(&)",
                                       "Paso @ Amp(&)",
                                       "Step Amp(&)",
                                       "Saut @ Amp(&)"  };

const STR *const StrM2_24[]  = {       "Step @ Ext Sig",
                                       "Prof. @ Ext. Sig.",
                                       "Paso @ Sol Ext",
                                       "Step a Seg Est",
                                       "Saut @ Sig Ext "  };

const STR *const StrM2_25[]  = {       "Hold Force(&&)",
                                       "Haltekraft(&&)",
                                       "Furz Mantn(&&)",
                                       "Forza Raff(&&)",
                                       "Force Mtn(&&)"  };

const STR *const StrM2_26[]  = {       "Downspeed(&)",
                                       "Abf.Gesch.(&)",
                                       "Vel. Lenta(&)",
                                       "Veloc dis(&)",
                                       "Vit. Desc(&)"  };

const STR *const StrM2_27[]  = {       "Amplitude(&)",
                                       "Amplitude(&)",
                                       "Amplitud(&)",
                                       "Ampiezza(&)",
                                       "Amplitude(&)"  };

const STR *const StrM2_27A[] = {       "Amplitude(&)   = ***",
                                       "Amplitude(&)   = ***",
                                       "Amplitud(&)    = ***",
                                       "Ampiezza(&)    = ***",
                                       "Amplitude(&)   = ***"  };

const STR *const StrM2_28[]  = {       "Amplitude A(&)",
                                       "Amplitude A(&)",
                                       "Amplitud A(&)",
                                       "Ampiezza A(&)",
                                       "Amplitude A(&)"  };

const STR *const StrM2_29[]  = {       "Amplitude",
                                       "Amplitude",
                                       "Amplitud",
                                       "Ampiezza",
                                       "Amplitude"  };

const STR *const StrM2_29A[] = {       "AMP STEP            ",
                                       "AMP.PROF.           ",
                                       "PASO AMP            ",
                                       "STEP AMP            ",
                                       "SAUT AMP            "  };

const STR *const StrM2_30[]  = {       "Amplitude B(&)",
                                       "Amplitude B(&)",
                                       "Amplitud B(&)",
                                       "Ampiezza B(&)",
                                       "Amplitude B(&)"  };

const STR *const StrM2_31[]  = {       "Pretrigger",
                                       "Pretrigger",
                                       "Predisparo",
                                       "Pretrigger",
                                       "Pretrigger"  };

const STR *const StrM2_32[]  = {       "Pretrg@D(&&)",
                                       "Pretrig.@W(&&)",
                                       "Predis@D(&&)",
                                       "Pretrg@D(&&)",
                                       "Pretrg@D(&&)"  };

const STR *const StrM2_33[]  = {       "External Pretrig",
                                       "Ext. Vortrig.",
                                       "Predisp externo ",
                                       "Pretrig esterno",
                                       "Predec Ext"  };

const STR *const StrM2_34[]  = {       "Pretrg Amp(&)",
                                       "Pretrig. Amp.(&)",
                                       "Predis Amp(&)",
                                       "Amp pretrg(&)",
                                       "Amp Pretrg(&)"  };

const STR *const StrM2_35[]  = {       "Afterburst",
                                       "Nachimpuls",
                                       "DisPostUS",
                                       "Afterburst",
                                       "Postimplsn"  };

const STR *const StrM2_36[]  = {       "AB Delay(&)",
                                       "NI Verz(&)",
                                       "Rtd DPUS(&)",
                                       "Ritrd AB(&)",
                                       "Del. PI(&)"  };

const STR *const StrM2_37[]  = {       "AB Time(&)",
                                       "NI Zeit(&)",
                                       "Tm DPUS(&)",
                                       "Temp AB(&)",
                                       "Dur PI(&)"  };

const STR *const StrM2_38[]  = {       "AB Amplitude(&)",
                                       "NI Amplitude(&)",
                                       "Amplit. DPUS(&)",
                                       "Ampiezza AB(&)",
                                       "Amplit. PI(&)"  };

const STR *const StrM2_39[]  = {       "Rapid Traverse",
                                       "Eilgang",
                                       "Vel. Rapida",
                                       "Spost. Rapido",
                                       "Mouvemt Rapide"  };

const STR *const StrM2_39A[] = {       "rapid trav",
                                       "Eilgang",
                                       "vel. rapida",
                                       "spost rapd",
                                       "mvmt rapid"  };

const STR *const StrM2_40[]  = {       "Energy Brake",
                                       "Energy Brake", 
                                       "Freno energía",
                                       "Energy Brake",
                                       "Reduct energie"  };

const STR *const StrM2_40A[] = {       "Step Time(&)",
                                       "Step Time(&)",
                                       "Paso t. (&)",
                                       "Step Time(&)",
                                       "Step Time(&)"  };

const STR *const StrM2_40B[] = {       "Step Amp(&)",
                                       "Profil Ampl(&)",
                                       "Paso Amp. (&)",
                                       "Step Amp(&)",
                                       "Amplitude C (&)"  };

const STR *const StrM2_40C[] = {       "Energy Brake  >", 
                                       "Energy Brake  >",
                                       "Freno energía >",
                                       "Energy Brake  >",
                                       "Energy Brake  >"  };

const STR *const StrM2_41[]  = {       "R/T @ D(&&)",
                                       "EG @ W(&&)",
                                       "C/R @ D(&&)",
                                       "R/T @ D(&&)",
                                       "R/T @ D(&&)"  };

const STR *const StrM2_42[]  = {       "Post Weld Seek",
                                       "Suche nach Schw.",
                                       "Busca Pos Sold",
                                       "Seek Post-sald",
                                       "Rech Post Soud"  };

const STR *const StrM2_42A[] = {       "Pre Weld Seek",
                                       "Suchen vor Schw.",
                                       "Busca Pre Sol",
                                       "Seek Pre-sald",
                                       "Rech Pre-Soud"  };

const STR *const StrM2_43[]  = {       "Frequency Offset",
                                       "Frequenz Offset",
                                       "Desvio Frecuenc",
                                       "Offset Frequenza",
                                       "Decal Frequence"  };

const STR *const StrM2_43X[] = {       "Frequency Offset>Ext",
                                       "Frequenz Offset> Ext",
                                       "Desvio Frecuenc> Ext",
                                       "Offset Frequenza>Est",
                                       "Decal. Frequence>Ext"  };

const STR *const StrM2_43A[] = {       "FREQ OFFSET         ",
                                       "FREQ. OFFSET        ",
                                       "DESVIO FREC         ",
                                       "FREQ OFFSET         ",
                                       "DECAL FREQ          "  };

const STR *const StrM2_43B[] = {       "Freq Offset(&&)",
                                       "Freq. Offset(&&)",
                                       "Fesvio Frec(&&)",
                                       "Freq Offset(&&)",
                                       "Decal Freq(&&)"  };

const STR *const StrM2_43C[] = {       "Change Sign[-,+]",
                                       "Vorz. aend.[-,+]",
                                       "Cambio sign[-,+]",
                                       "Modif segno[-,+]",
                                       "Chang Sign [-,+]"  };

const STR *const StrM2_44[]  = {       "Pk Pwr Cut(&)",
                                       "Sp.Lst. Absch(&)",
                                       "Cte Pc Pot(&)",
                                       "Arr P Pot(&)",
                                       "Arr P -Cre(&)"  };

const STR *const StrM2_45[]  = {       "Gnd Det Abort",
                                       "Abbr. Metallkont.",
                                       "Cortar det GD",
                                       "Inter ril ter",
                                       "Det Sol Inter"  };

const STR *const StrM2_46[]  = {       "Suspect Limits",
                                       "Pruefgrenzwert",
                                       "Ltes. Sospech.",
                                       "Limit sospetti",
                                       "Limtes Suspect"  };

const STR *const StrM2_46A[] = {       "SUSP LIMITS         ",
                                       "PRUEFGRZWERT        ",
                                       "LTES. SOSPECH.      ",
                                       "LIMITI SOSPETTI     ",
                                       "LIMTES SUSP         "  };

const STR *const StrM2_47[]  = {       "Reset Required",
                                       "Reset erforderlich",
                                       "Reset Requerdo",
                                       "Reset Val Scan",
                                       "RAZ Requise"  };

const STR *const StrM2_48[]  =  {      "-S Energy (&)",
                                       "-P Energ (&)",
                                       "-S Energ. (&)",
                                       "-S Energi (&)",
                                       "-S Energie(&)"  };

const STR *const StrM2_49[]  =  {      "+S Energy (&)",
                                       "+P Energ (&)",
                                       "+S Energ. (&)",
                                       "+S Energi (&)",
                                       "+S Energie(&)"  };

const STR *const StrM2_50[]  =  {      "-S Pk Power(&)",
                                       "-P Sp Leist(&)",
                                       "-S Pico Pot(&)",
                                       "-S LmPicPot(&)",
                                       "-S LmPuiCrt(&)"  };       

const STR *const StrM2_51[]  =  {      "+S Pk Power(&)",
                                       "+P Sp Leist(&)",
                                       "+S Pico Pot(&)",
                                       "+S LmPicPot(&)",
                                       "+S LmPuiCrt(&)"  };       

const STR *const StrM2_52[]  =  {      "-S Col D(&&)",
                                       "-P W rel(&&)",
                                       "-S D Col(&&)",
                                       "-S D Col(&&)",
                                       "-D Rel S(&&)"  };

const STR *const StrM2_53[]  =  {      "+S Col D(&&)",
                                       "+P W rel(&&)",
                                       "+S D Col(&&)",
                                       "+S D Col(&&)",
                                       "+D Rel S(&&)"  };

const STR *const StrM2_54[]  =  {      "-S Abs D(&&)",
                                       "-P W abs(&&)",
                                       "-S D Abs(&&)",
                                       "-S D Ass(&&)",
                                       "-D Abs S(&&)"  };

const STR *const StrM2_55[]  =  {      "+S Abs D(&&)",
                                       "+P W abs(&&)",
                                       "+S D Abs(&&)",
                                       "+S D Ass(&&)",
                                       "+D Abs S(&&)"  };

const STR *const StrM2_56[]  =  {      "-S Trg D(&&)",
                                       "-P Trg W(&&)",
                                       "-S D Dsp(&&)",
                                       "-S D Trg(&&)",
                                       "-D Trg S(&&)"  };

const STR *const StrM2_57[]  =  {      "+S Trg D(&&)",
                                       "+P Trg W(&&)",
                                       "+S D Dsp(&&)",
                                       "+S D Trg(&&)",
                                       "+D Trg S(&&)"  };

const STR *const StrM2_58[]  =  {      "-S Weld F(&&)",
                                       "-P Schw K(&&)",
                                       "-S Sold F(&&)",
                                       "-S Sald F(&&)",
                                       "-S Soud F(&&)"  };

const STR *const StrM2_59[]  =  {      "+S Weld F(&&)",
                                       "+P Schw K(&&)",
                                       "+S Sold F(&&)",
                                       "+S Sald F(&&)",
                                       "+S Soud F(&&)"  };

const STR *const StrM2_60[]  = {       "Reject Limits",
                                       "Grenze Aussch",
                                       "Ltes. Rechazo.",
                                       "Limiti Scarto",
                                       "Limites Rej"  };

const STR *const StrM2_60A[] = {       "REJ LIMITS          ",
                                       "GRENZW. AUSSCH      ",
                                       "LTES. RECHAZO       ",
                                       "LIMITI SCARTO       ",
                                       "LIMTES REJ          "  };

const STR *const StrM2_61[]  = {       "Step @ F(&&)",
                                       "Prof. @ K(&&)",
                                       "Paso @ F(&&)",
                                       "Step a F(&&)",
                                       "Saut @ F(&&) "  };

const STR *const StrM2_62[]  = {       "Auto Pretrigger",
                                       "Auto Pretrigger",
                                       "Predisparo Auto",
                                       "Auto Pretrigger",
                                       "Pretrig. Auto"  };

const STR *const StrM2_63[]  = {       "Step @ MPS Sw",
                                       "Prof. @ MPS",
                                       "Paso @ MPS Sw",
                                       "Step @ MPS Sw",
                                       "Saut @ MPS Sw"  };

const STR *const StrM2_64[]  = {       "Weld Energy(&)",
                                       "Schw Energ(&)",
                                       "Sold Energ.(&)",
                                       "Energi sald(&)",
                                       "Energ. Soud(&)"  };

const STR *const StrM2_65[]  = {       "Timeout(&)",
                                       "Zeituebers (&)",
                                       "Agotado(&)",
                                       "Timeout(&)",
                                       "Del Att(&)"  };

const STR *const StrM2_66[]  =  {      "-S Time (&)",
                                       "-P Zeit (&)",
                                       "-S Tiem (&)",
                                       "-S Tmpo (&)",
                                       "-Tps S (&)"  };

const STR *const StrM2_67[]  =  {      "+S Time (&)",
                                       "+P Zeit (&)",
                                       "+S Tiem (&)",
                                       "+S Tmpo (&)",
                                       "+Tps S (&)"  };

const STR *const StrM2_68[]  = {       "Peak Power(&)",
                                       "Sp.Lst.(&)",
                                       "Pico Poten(&)",
                                       "Picco Pot.(&)",
                                       "Pui. Crete(&)"  };

const STR *const StrM2_69[]  = {       "Collapse(&&)",
                                       "Weg rel (&&)",
                                       "Colapso(&&)",
                                       "Collasso(&&)",
                                       "D. Relat(&&)"  };

const STR *const StrM2_70[]  = {       "Absolute(&&)",
                                       "Weg abs(&&)",
                                       "Absoluto(&&)",
                                       "Assoluto(&&)",
                                       "Absolue(&&)"  };

const STR *const StrM2_71[]  = {       "Scrub Time(&)",
                                       "Verz.Zeit(&)",
                                       "Tiem Rsrva(&)",
                                       "Tmpo lvggi(&)",
                                       "Tps Retrd.(&)"  };

const STR *const StrM2_74[]  = {       "Control Limits",
                                       "Grenzwerte",
                                       "Ltes Control",
                                       "Limit controlo",
                                       "Limites Comde"  };

const STR *const StrM2_75[]  = {       "CNTL LIMITS         ",
                                       "GRENZWERTE          ",
                                       "LIMITES CTRL        ",
                                       "LIMITI              ",
                                       "LIMITES CMDE        "  };

const STR *const StrM2_76[]  = {       "Energy Comp",
                                       "Energiekomp.",
                                       "Comp Energ.",
                                       "Energi Comp",
                                       "Energie Comp"  };

const STR *const StrM2_76A[] = {       "ENERGY COMP         ",
                                       "ENERGIEKOMP.        ",
                                       "COMP ENERG.         ",
                                       "ENERGIA COMP        ",
                                       "ENERGIE COMP         "  };

const STR *const StrM2_76B[] = {       "Min Energy(&)",
                                       "Min Energie(&)",
                                       "Energi Min(&)",
                                       "Energi Min(&)",
                                       "Energ. Min(&)"  };

const STR *const StrM2_76C[] = {       "Max Energy(&)",
                                       "Max Energie(&)",
                                       "Energi Max(&)",
                                       "Energi Max(&)",
                                       "Energ. Max(&)"  };

const STR *const StrM2_77[]  = {       "AbsCut(&&)",
                                       "Weg abs(&&)",
                                       "CteAbs(&&)",
                                       "IntrAs(&&)",
                                       "CprAbs(&&)"  };

const STR *const StrM2_78[]  = {       "Cycle Aborts",
                                       "Zykl. Abbruch",
                                       "Ciclo Cancel",
                                       "Interr Ciclo",
                                       "Arret Cycle"  };

const STR *const StrM2_79[]  = {       "Missing Part",
                                       "Teilerkennung",
                                       "Falta Pieza",
                                       "Parte Mncnte",
                                       "Pce Manqte"  };

const STR *const StrM2_80[]  = {       "MISSING PART",
                                       "TEILERKENNUNG",
                                       "FALTA PIEZA",
                                       "PARTE MNCNTE",
                                       "PCE MANQTE"  };

const STR *const StrM2_81[]  = {       "ColCut(&&)",
                                       "Weg rel (&&)",
                                       "ColCut(&&)",
                                       "IntrFs(&&)",
                                       "CpDRel(&&)"  };

const STR *const StrM2_82[]  = {       "Minimum(&&)",
                                       "Minimum(&&)",
                                       "Minimo(&&)",
                                       "Minimo(&&)",
                                       "Minimum(&&)"  };

const STR *const StrM2_83[]  = {       "Maximum(&&)",
                                       "Maximum(&&)",
                                       "Maximo(&&)",
                                       "Massimo(&&)",
                                       "Maximum(&&)"  };

const STR *const StrM2_84[]  = {       "+R Time (&)",
                                       "+A Zeit (&)",
                                       "+R Tiem (&)",
                                       "+R Tmpo (&)",
                                       "+R Tps  (&)"  };

const STR *const StrM2_85[]  = {       "-R Time (&)",
                                       "-A Zeit (&)",
                                       "-R Tiem (&)",
                                       "-R Tmpo (&)",
                                       "-R Tps  (&)"  };

const STR *const StrM2_86[]  = {       "+R Energy (&)",
                                       "+A Energ (&) ",
                                       "+R Energ. (&)",
                                       "+R Energi (&)",
                                       "+R Energie(&)"  };

const STR *const StrM2_87[]  = {       "-R Energy (&)",
                                       "-A Energ (&)",
                                       "-R Energ. (&)",
                                       "-R Energi (&)",
                                       "-R Energie(&)"  };

const STR *const StrM2_88[]  = {       "+R Pk Power(&)",
                                       "+A Sp Leist(&)",
                                       "+R Pico Pot(&)",
                                       "+R Pic Pot(&)",
                                       "+P.-Crete R(&)"  };

const STR *const StrM2_89[]  = {       "-R Pk Power(&)",
                                       "-A Sp Leist(&)",
                                       "-R Pico Pot(&)",
                                       "-R Pic Pot(&)",
                                       "-P.-Crete R(&)"  };

const STR *const StrM2_90[]  = {       "+R Col D(&&)",
                                       "+A W rel(&&)",
                                       "+R D Col(&&)",
                                       "+R D Col(&&)",
                                       "+D Rel R(&&)"  };

const STR *const StrM2_91[]  = {       "-R Col D(&&)",
                                       "-A W rel(&&)",
                                       "-R D Col(&&)",
                                       "-R D Col(&&)",
                                       "-D Rel R(&&)"  };

const STR *const StrM2_92[]  =  {      "+R Abs D(&&)",
                                       "+A W abs(&&)",
                                       "+R D Abs(&&)",
                                       "+R D Ass(&&)",
                                       "+D Abs R(&&)"  };

const STR *const StrM2_93[]  =  {      "-R Abs D(&&)",
                                       "-A W abs(&&)",
                                       "-R D Abs(&&)",
                                       "-R D Ass(&&)",
                                       "-D Abs R(&&)"  };

const STR *const StrM2_94[]  =  {      "+R Trg D(&&)",
                                       "+A Trg W(&&)",
                                       "+R D Dsp(&&)",
                                       "+R D Trg(&&)",
                                       "+D Trg R(&&)"  };

const STR *const StrM2_95[]  =  {      "-R Trg D(&&)",
                                       "-A Trg W(&&)",
                                       "-R D Dps(&&)",
                                       "-R D Trg(&&)",
                                       "-D Trg R(&&)"  };

const STR *const StrM2_96[]  =  {      "+R Weld F(&&)",
                                       "+A Schw K(&&)",
                                       "+R Sold F(&&)",
                                       "+R Sald F(&&)",
                                       "+R Soud F(&&)"  };

const STR *const StrM2_97[]  =  {      "-R Weld F(&&)",
                                       "-A Schw K(&&)",
                                       "-R Sold F(&&)",
                                       "-R Sald F(&&)",
                                       "-R Soud F(&&)"  };

const STR *const StrM2_98[]  = {       "Step @ Abs(&&)",
                                       "Prof. @ Abs(&&)",
                                       "Paso @ Abs(&&)",
                                       "Step a Ass(&&)",
                                       "Saut @ Abs(&&) "  };


const STR *const StrM2_100[]  = {      "  Write In 1  Pg1of1",
                                       "SCHREIBE IN 1 S.1v.1",
                                       " ESCRIBIR EN 1 Pg1/1",
                                       "SCRIVERE 1 IN Pg1DI1",
                                       "SAISIE DANS 1 Pg1DE1"  };

const STR *const StrM2_101[]  = {      "  Write In 2  Pg1of1",
                                       "SCHREIBE IN 2 S.1v.1",
                                       " ESCRIBIR EN 2 Pg1/1",
                                       "SCRIVERE 2 IN Pg1DI1",
                                       "SAISIE DANS 2 Pg1DE1"  };

const STR *const StrM2_102[]  = {      "Text:           Done",
                                       "Text:           Done",
                                       "Text:           Done",
                                       "Text:           Done",
                                       "Text:           Done"  };

const STR *const StrM2_103[]  = {      "Write In Field",
                                       "Schre in Feld",
                                       "Escr. campo",
                                       "Write In Field",
                                       "Saisie ds Chp"  };

const STR *const StrM2_108[]  = {      "Write In Fields>",
                                       "Schreibe in Felder>",
                                       "Escr. campos>",
                                       "Write In Fields>",
                                       "Saisie ds Chp>" };

const STR *const StrM2_109[]  = {      "Text1>",
                                       "Text1>",
                                       "Texto1>",
                                       "Text1>",
                                       "Texte1>"  };

const STR *const StrM2_110[]  = {      "Text2>",
                                       "Text2>",
                                       "Texto2>",
                                       "Text2>",
                                       "Texte2>"  };


const STR *const StrM2A_0[]  = {       "WELD MODE",
                                       "MODUS",
                                       "MOD SLDRA",
                                       "Mod sald",
                                       "Mode Soud"  };

const STR *const StrM2A_1[]  = {       "Time",
                                       "Zeit",
                                       "Tiem",
                                       "Tempo",
                                       "Temps"  };

const STR *const StrM2A_2[]  = {       "Energy",
                                       "Energie",
                                       "Energi",
                                       "Energi",
                                       "Energie"  };

const STR *const StrM2A_3[]  = {       "Peak Power",
                                       "Sp.Leistung",
                                       "Pico Poten",
                                       "Picco Pot.",
                                       "Pui.-Crete"  };

const STR *const StrM2A_4[]  = {       "Collapse",
                                       "Weg rel",
                                       "Colapso",
                                       "Collasso",
                                       "D. Relat"  };

const STR *const StrM2A_5[]  = {       "Absolute",
                                       "Weg abs",
                                       "Absoluto",
                                       "Assoluta",
                                       "D.Abs"  };

const STR *const StrM2A_6[]  = {       "Ground Detect",
                                       "Metallkont.",
                                       "Detecc Tierra",
                                       "Ground Detect",
                                       "Detec.Masse"  };

const STR *const StrM2A_7[]  = {       "Continuous",
                                       "Kontinuier",
                                       "Continuo",
                                       "Continua",
                                       "Continu"  };

const STR *const StrM2A_8[]  = {       "Digital UPS>",
                                       "Digital UPS>",
                                       "F/A. Digital>",
                                       "UPS Digital>",
                                       "GUD>"  };

const STR *const StrDigUpsTitle[] =  { "DIGITAL UPS",
                                       "DIGITAL UPS",
                                       "F/A. DIGITAL",
                                       "UPS DIGITAL",
                                       "GUD"  };

const STR *const StrSetupTitle[] = {   "Setup>",
                                       "Einr.>",
                                       "Config>",
                                       "Setup>",
                                       "Confg>"  };

const STR *const StrWStatusTitle[] = { "Weld Status",
                                       "Schw. Status",
                                       "Estado Sold",
                                       "Stato Sald.",
                                       "Etat Soud"  };

const STR *const StrSetTitle[] = {     "SETUP",
                                       "EINR.",
                                       "CONFIG",
                                       "SETUP",
                                       "CONFG"  };

const STR *const StrMemorySetup[] = {  "Memory",
                                       "Speichern",
                                       "Memori",
                                       "Memori",
                                       "Memoi."  };

const STR *const StrRTime[] = {        "Ramp Time(s)",
                                       "Ramp.Zeit(s)",
                                       "Tiem Rmpa(s)",
                                       "Tmpo Rmpa(s)",
                                       "Tps Monte(s)"  };

const STR *const StrSTime[] = {        "Seek Time(s)",
                                       "Suchzeit(s)",
                                       "Tiem Busq(s)",
                                       "Tmpo Seek(s)",
                                       "Tps Rech.(s)"  };

const STR *const StrTimedSeek[] = {    "Timed Seek",
                                       "Suchperiode",
                                       "Busc Tiem",
                                       "Rcrca Prog",
                                       "Rech. Temp"  };


const STR *const StrSPresettitle[] = { "PRESET NAMES",
                                       "PARAM. NAMEN", 
                                       "NOMBRES PRESL", 
                                       "NOME PRESETS", 
                                       "NOMS PRESET"  }; 

const STR *const StrM3_0[]   =  {      "PRESETS",
                                       "PARAM.",
                                       "PRESELEC.",
                                       "PRESETS",
                                       "PRESETS"  };

const STR *const StrM3_0A[]  =  {      "Recall",
                                       "Abruf",
                                       "Volver",
                                       "Richia",
                                       "Rappel"  };

const STR *const StrM3_0B[]  =  {      "Save",
                                       "Speichern",
                                       "Guardar",
                                       "Salva",
                                       "Enrg"  };

const STR *const StrM3_0C[]  =  {      "CLEAR",
                                       "LOESCHEN",
                                       "BORRAR",
                                       "CANCELA",
                                       "EFFAC"  };

const STR *const StrM3_0D[]  =  {      "Clear",
                                       "Loeschen",
                                       "Borrar",
                                       "Cancela",
                                       "Effac"  };


const STR *const StrM3_0E[]  =  {      "Verify Preset",
                                       "Voreinst. pruefen",
                                       "Verif Presel",
                                       "Verif Preset",
                                       "Verif. Preset"  };

const STR *const StrM3_0F[]  =  {      "SAVE          Pg1of1",     /* This string used only for ALPHA menu display */
                                       "SPEICHERN     S.1of1",
                                       "GUARDAR       Pg1of1",
                                       "SALVA         Pg1of1",
                                       "ENRG          Pg1of1"  };

const STR *const StrM3_2[]   =  {      "Automatically Name",
                                       "Name automatisch",
                                       "Nombre automatico",
                                       "Nom Automaticament",
                                       "Nom. Automatiquemt"  };

const STR *const StrM3_3[]   =  {      "Assign Name",
                                       "Name zuweis.",
                                       "Asig Nombre",
                                       "Assegn Nome",
                                       "Assign Identif"  };

const STR *const StrM3_7[]   =  {      "OVERWRITE PRESET ",
                                       "ERSETZE VOREINST.",
                                       "SOBRSCRIBIR PRES ",
                                       "SOVRASCR. PRESET ",
                                       "ECRASER PRESET "  };

const STR *const StrM3_9[]   =    {    "               Done",
                                       "              Getan",
                                       "               Tmdo",
                                       "               Esgt",
                                       "               Term"  };

const STR *const StrM3_9A[]  =  {      "_            Done",
                                       "_           Getan",
                                       "_            Tmdo",
                                       "_            Esgt",
                                       "_            Term" };


const STR *const StrM3_21[]  =      {  "                  OK",
                                       "                  OK",
                                       "                  OK",
                                       "                  OK",
                                       "                  OK"  };

const STR *const StrM3_22[]  =      {  "              Cancel",
                                       "             Abbrch.",
                                       "              Cancel",
                                       "              Cancel",
                                       "              Annul."  };

const STR *const StrM3_23[]  =  {      "Tm=",
                                       "Zt=", 
                                       "Tm=",
                                       "Tp=",
                                       "TP="  };

const STR *const StrM3_24[]  =  {      "En=",
                                       "En=",
                                       "En=",
                                       "En=",
                                       "En="  };

const STR *const StrM3_25[]  =  {      "PP=",
                                       "PP=",
                                       "PP=",
                                       "PP=",
                                       "PP="  };

const STR *const StrM3_26[]  =  {      "Cl=",
                                       "Cl=",
                                       "Cl=",
                                       "Cl=",
                                       "Cl="  };

const STR *const StrM3_27[]  =  {      "Ab=",
                                       "Ni=",
                                       "Ab=",
                                       "Ab=",
                                       "Pi="  };

const STR *const StrM3_28[]  =  {      "GD=",
                                       "MK=",
                                       "GD=",
                                       "GD=",
                                       "DM="  };

const STR *const StrM3_30[]  =  {      "Continuous",
                                       "Kontinuier",
                                       "Continua",
                                       "Continua",
                                       "Continu"  };


const STR *const StrPreset[]  =  {    "Preset",
                                      "Vorein",
                                      "Presel",
                                      "Preset",
                                      "Preset"  };

const STR *const StrName[]  =    {    "Name:",
                                      "Namen:",
                                      "Nombres:",
                                      "Nome:",
                                      "Noms:"  };

STR *const StrCycleCount[] = {        "Cycles Run",
                                      "Cycles Run",
                                      "Cycles Run",
                                      "Cycles Run",
                                      "Cycles Run"  };



/***   ***   This section used to update RunBuffer2   ***   ***/

const STR *const StrPreset0[] =  {    "Preset0 ",
                                      "Param.0 ",
                                      "Presel0 ",
                                      "Preset0 ",
                                      "Preset0 "  };

const STR *const StrPreset1[] =  {    "Preset1 ",
                                      "Param.1 ",
                                      "Presel1 ",
                                      "Preset1 ",
                                      "Preset1 "  };

const STR *const StrPreset2[] =  {    "Preset2 ",
                                      "Param.2 ",
                                      "Presel2 ",
                                      "Preset2 ",
                                      "Preset2 "  };

const STR *const StrPreset3[] =  {    "Preset3 ",
                                      "Param.3 ",
                                      "Presel3 ",
                                      "Preset3 ",
                                      "Preset3 "  };

const STR *const StrPreset4[] =  {    "Preset4 ",
                                      "Param.4 ",
                                      "Presel4 ",
                                      "Preset4 ",
                                      "Preset4 "  };

const STR *const StrPreset5[] =  {    "Preset5 ",
                                      "Param.5 ",
                                      "Presel5 ",
                                      "Preset5 ",
                                      "Preset5 "  };

const STR *const StrPreset6[] =  {    "Preset6 ",
                                      "Param.6 ",
                                      "Presel6 ",
                                      "Preset6 ",
                                      "Preset6 "  };

const STR *const StrPreset7[] =  {    "Preset7 ",
                                      "Param.7 ",
                                      "Presel7 ",
                                      "Preset7 ",
                                      "Preset7 "  };

const STR *const StrPreset8[] =  {    "Preset8 ",
                                      "Param.8 ",
                                      "Presel8 ",
                                      "Preset8 ",
                                      "Preset8 "  };

const STR *const StrPreset9[] =  {    "Preset9 ",
                                      "Param.9 ",
                                      "Presel9 ",
                                      "Preset9 ",
                                      "Preset9 "  };

const STR *const StrPreset10[] = {    "Preset10 ",
                                      "Param.10 ",
                                      "Presel10 ",
                                      "Preset10 ",
                                      "Preset10 "  };

const STR *const StrPreset11[] = {    "Preset11 ",
                                      "Param.11 ",
                                      "Presel11 ",
                                      "Preset11 ",
                                      "Preset11 "  };

const STR *const StrPreset12[] = {    "Preset12 ",
                                      "Param.12 ",
                                      "Presel12 ",
                                      "Preset12 ",
                                      "Preset12 "  };

const STR *const StrPreset13[] = {    "Preset13 ",
                                      "Param.13 ",
                                      "Presel13 ",
                                      "Preset13 ",
                                      "Preset13 "  };

const STR *const StrPreset14[] = {    "Preset14 ",
                                      "Param.14 ",
                                      "Presel14 ",
                                      "Preset14 ",
                                      "Preset14 "  };

const STR *const StrPreset15[] = {    "Preset15 ",
                                      "Param.15 ",
                                      "Presel15 ",
                                      "Preset15 ",
                                      "Preset15 "  };

const STR *const StrPreset16[] = {    "Preset16 ",
                                      "Param.16 ",
                                      "Presel16 ",
                                      "Preset16 ",
                                      "Preset16 "  };




const STR *const StrM5_0[]    =    {  "Cal Actuator",
                                      "Kal. VE",
                                      "Cal Actuator",
                                      "Cal Attuatore",
                                      "Cal Actuator"  };

const STR *const StrM5_0A[]   =    {  "W/Start Switches",
                                      "M/Startschalter",
                                      "c/puls. inico",
                                      "W/Inter di avvio",
                                      "S/Contacts Demar"  };

const STR *const StrM5_0B[]   =    {  "W/Manual Override",
                                      "Manu. Ueberbr.",
                                      "c/manual op.",
                                      "W/Override manual",
                                      "Mode Manuel"  };

const STR *const StrM5_0C[]   =    {  "Use Manual",
                                      "Handbuch",
                                      "Use Manual",//
                                      "Usa Manual",
                                      "Cf. Manuel"  };

const STR *const StrM5_0D[]   =    {  "Override on valve",
                                      "Ueberbr. am Ventil",
                                      "Anulacion valvula",
                                      "Override su vlvl",
                                      "Encl man. Evanne"  };

const STR *const StrM5_0EA[]  =    {  "Calibration Saved   ",
                                      "Kalib. gespeich.    ",
                                      "Calibrdo guardado   ",
                                      "Calibraz salvata    ",
                                      "Calibrat. Enreg.    "  };

const STR *const StrM5_0F[]   =    {  "Release Start       ",
                                      "Start freigeben     ",
                                      "Liberar inic        ",
                                      "Rilasc Start        ",
                                      "Relach Start        "  };

const STR *const StrM5_0GA[]  =    {  "Switches        Done",
                                      "Schalter       Getan",
                                      "Conmuts         Tmdo",
                                      "Interruttori    Esgt", 
                                      "Contacts.       Term"  };

const STR *const StrM5_0H[]   =    {  "Release Manual      ",
                                      "Manuell freigeben   ",
                                      "Liberar manual      ",
                                      "Rilasc Manuale      ",
                                      "Relach Manuel.      "  };

const STR *const StrM5_0IA[]  =    {  "Override        Done",
                                      "Ueberbr.       Getan",
                                      "Anular          Tmdo",
                                      "Esclusione      Esgt",
                                      "Encl.manu       Term"  };

const STR *const StrM5_1[]    =    {  "Reset Sensor Cal",
                                      "Reset Kal.Sensor",
                                      "Reset cal sensor",
                                      "Reset cal sensor",
                                      "RAZ Cal. Captrs"  };

const STR *const StrM5_2[]    =    {  "Reset? ",
                                      "Reset? ",
                                      "Reset? ",
                                      "Reset? ",
                                      "RAZ? "  };

const STR *const StrM5_2A[]   =    {  "This will revert to",
                                      "Rueckkehr zu",
                                      "Se regresara a los ",
                                      "Il sistema torna a",
                                      "Retour a"  };

const STR *const StrM5_2B[]   =    {  "factory defaults  OK",
                                      "Werkseinstell.    OK",
                                      "valores fabrica   OK",
                                      "valori pred prod  OK",
                                      "Param usine       OK"  };

const STR *const StrM5_3[]    =    {  "Successful",
                                      "erfolgreich",
                                      "Con exito",
                                      "Riuscito",
                                      "Reussi"  };

const STR *const StrM5_4[]    =    {  "Cal Full System",
                                      "Ganz. Syst. Kal.",
                                      "Cal sist compl.",
                                      "Cal sist intero",
                                      "Cal Compl Sys"  };

const STR *const StrM5_4A[]   =    {  "Cal System",
                                      "Syst. Kalibr.",
                                      "Cal sistem",
                                      "Cal sistem",
                                      "Cal System"  };


const STR *const StrM5A_6[]   =    {  "Calibration         ",
                                      "Kalibrierung        ",
                                      "Calibracion         ",
                                      "Calibrazion         ",
                                      "Calibration         "  };

const STR *const StrM5_7[]    =    {  "Diagnostics",
                                      "Diagnose",
                                      "Diagnosis",
                                      "Diagnostica",
                                      "Diagnost."  };

const STR *const StrM5_20[]   =    {  "Cold start",
                                      "Kaltstart",
                                      "Arque Frio",
                                      "Cold start",
                                      "Param Usin"  };

const STR *const StrM5_21[]   =    {  "This will Clear your",
                                      "Loschen Ihrer",
                                      "Esto eliminara su   ",
                                      "Questo Cancel Il Tuo",
                                      "Cela effacera la"  };

const STR *const StrM5_22[]   =    {  "Present Setup.    OK",
                                      "Akt. Einricht.    OK",
                                      "Config Actual.    OK",
                                      "Install Attuale   OK",
                                      "Config Actuel.    OK"  };

const STR *const StrM5_23[]   =     { "              Cancel",
                                      "             Abbrch.",
                                      "              Cancel",
                                      "              Cancel",
                                      "              Annul."  };

const STR *const StrM5_25[]   =    {  "Cold start",
                                      "Kaltstart",
                                      "Rest.Config.Defecto",
                                      "Cold start",
                                      "Param Usin"  };

const STR *const StrM5_26[]   =    {  "Cal Distance Now",
                                      "Kalib. Weg jetzt",
                                      "Cal distan ahora",
                                      "Cal distanza ora",
                                      "Cal Distan Matnt"  };

const STR *const StrM5_27[]   =    {  "Yes",
                                      "Ja",
                                      "Si",
                                      "Si",
                                      "Oui"  };

const STR *const StrM5_28[]   =    {  "No",
                                      "Nn",
                                      "No",
                                      "No",
                                      "No"  };

const STR *const StrM5_29[]   =    {  "Digital Tune",
                                      "Digit. Abstim",
                                      "Sint Digital",
                                      "Sint Digital",
                                      "Accord Digit"  };

const STR *const StrM5_30[]   =    {  "Start Freq(&&)",
                                      "Start Freq.(&&)",
                                      "Inicio Frc(&&)",
                                      "Aviar Freq(&&)",
                                      "Debut Freq(&&)"  };


const STR *const StrM5_31[]   =    {  "Actuator Cold start",
                                      "Kaltstart VE",
                                      "Cold start Act",
                                      "Cold Start Act",
                                      "Param Usine Act"  };

const STR *const StrM5_32[]   =    {  "Debug",
                                      "Testen",
                                      "Ajuste",
                                      "Debug",
                                      "Debug"  };


const STR *const StrM5_33[]   =    {  "   Press Test To    ",
                                      "   Test druecken um ",
                                      "   Pulse Test p/    ",
                                      "   Premere Test per ",
                                      "   Press. Test p/   "  };

const STR *const StrM5_34[]   =     { " Confirm Operation  ",
                                      "Vorgang bestaetigen ",
                                      " Confirm operacion  ",
                                      " conferm operazion  ",
                                      " Confirm. Operation "  };

const STR *const StrM5_35[]   =    {  "    Please Wait     ",
                                      "    Bitte warten    ",
                                      "        Espere      ",
                                      "    Attendere Prego ",
                                      "    Attdre SVP     "  };

const STR *const StrM5_36[]   =    {  "Center Frequency",
                                      "Mitten-Frequenz",
                                      "Centro Frequenci",
                                      "Centrar frequenz",
                                      "Frequence centr."  };

const STR *const StrM5_37[]   =    {  "Horn Scan",
                                      "Horn Scan",
                                      "Diagnosis Sono.",
                                      "Anal Sono",
                                      "Scan Sono"  };

const STR *const StrM5_38[]   =    {  "HORN SCAN",
                                      "HORN SCAN",
                                      "DIAGNOSIS SONO.",
                                      "ANAL SONO",
                                      "SCAN SONO"  };

const STR *const StrM5_39[]   =    {  "Start Scan",
                                      "Starte Scan",
                                      "Inicio Diagnosis",
                                      "Avvre scan",
                                      "Start Scan"  };

const STR *const StrM5_40[]   =    {  "Print Scan Graph",
                                      "Drucke Scan Grafik",
                                      "Impr. Diagnosis",
                                      "Stamp scan graf",
                                      "Imp. Grph. Scan"  };

const STR *const StrM5_41[]   =    {  "Freq1(&&)",
                                      "Freq1(&&)",
                                      "Frec1(&&)",
                                      "Freq1(&&)",
                                      "Freq1(&&)"  };

const STR *const StrM5_42[]   =    {  "Freq2(&&)",
                                      "Freq2(&&)",
                                      "Frec2(&&)",
                                      "Freq2(&&)",
                                      "Freq2(&&)"  };

const STR *const StrM5_43[]   =    {  "Freq3(&&)",
                                      "Freq3(&&)",
                                      "Frec3(&&)",
                                      "Freq3(&&)",
                                      "Freq3(&&)"  };

const STR *const StrM5_44[]   =    {  "Freq4(&&)",
                                      "Freq4(&&)",
                                      "Frec4(&&)",
                                      "Freq4(&&)",
                                      "Freq4(&&)"  };

const STR *const StrM5_45[]   =    {  "Freq5(&&)",
                                      "Freq5(&&)",
                                      "Frec5(&&)",
                                      "Freq5(&&)",
                                      "Freq5(&&)"  };

const STR *const StrM5_46[]   =    {  "Freq6(&&)",
                                      "Freq6(&&)",
                                      "Frec6(&&)",
                                      "Freq6(&&)",
                                      "Freq6(&&)"  };

const STR *const StrM5_47[]   =    {  "actuator cal.     OK",
                                      "actuator cal.     OK",
                                      "actuator cal.     OK",
                                      "actuator cal.     OK",
                                      "actuator cal.     OK"  };

const STR *const StrM5_48[]   =    {  "Number Base",
                                      "Startpunkt",
                                      "Núm. Base",
                                      "Numero base",
                                      "Base numér."  };

const STR *const StrM5_49[]   =    {  "Display Size",
                                      "Bildsch.groesse",
                                      "Tamaño pantalla",
                                      "Display Size",
                                      "Frmt affichage"  };


const STR *const StrM5_55[]   =    {  "CAL ACTUATOR        ",
                                      "KAL. VE             ",
                                      "CAL ACTUADOR        ",
                                      "CAL ATTUATORE       ",
                                      "CAL ACTUATOR        "  };

const STR *const StrM5_63[]   =    {  "  Calibrating   ",
                                      "  Kalibrierung  ",
                                      "  Calibrando    ",
                                      "  Calibrzn corso",
                                      "  Calibrage     "  };



const STR *const StrM6_0[]   =  {     "System Info",
                                      "Systeminfo",
                                      "Info. Sistema",
                                      "Info Sistem",
                                      "Info System"  };

const STR *const StrM6_1[]   =  {     "PS Life",
                                      "Gen Lebens",
                                      "Cont. F/A",
                                      "Vita PS",
                                      "Vie PS "  };

const STR *const StrM6_2[]   =  {     "Overloads",
                                      "Ueberlast",
                                      "Sobrecarg",
                                      "Sovracrch",
                                      "Surchrges"  };

const STR *const StrM6_3[]   =  {     "Gen Alarm",
                                      "Ges. Alarm",
                                      "Alarm Gen",
                                      "Alarm Gen",
                                      "Alarm Gen"  };

const STR *const StrM6_4[]   =  {     "Act Life",
                                      "VE Leb.",
                                      "Cont. Act.",
                                      "Vita att",
                                      "Vie Act"  };

const STR *const StrM6_5A[]  =  {     "20kHz ",
                                      "20kHz ",
                                      "20kHz ",
                                      "20kHz ",
                                      "20kHz "  };

const STR *const StrM6_5B[]  =  {     "40kHz ",
                                      "40kHz ",
                                      "40kHz ",
                                      "40kHz ",
                                      "40kHz "  };

const STR *const StrM6_5K[]  =  {     "15kHz ",
                                      "15kHz ",
                                      "15kHz ",
                                      "15kHz ",
                                      "15kHz "  };

const STR *const StrM6_5L[]  =  {     "30kHz ",
                                      "30kHz ",
                                      "30kHz ",
                                      "30kHz ",
                                      "30kHz "  };
                                      
const STR *const Str_60KHZ[]  =  {    "60kHz ",
                                      "60kHz ",
                                      "60kHz ",
                                      "60kHz ",
                                      "60kHz "  };

const STR *const StrM6_5C[]  =  {     "1100w         ",
                                      "1100w         ",
                                      "1100w         ",
                                      "1100w         ",
                                      "1100w         "  };

const STR *const StrM6_5D[]  =  {     "2200w         ",
                                      "2200w         ",
                                      "2200w         ",
                                      "2200w         ",
                                      "2200w         "  };

const STR *const StrM6_5M[]  =  {     "6000w         ",
                                      "6000w         ",
                                      "6000w         ",
                                      "6000w         ",
                                      "6000w         "  };

const STR *const StrM6_5N[]  =  {     "1500w         ",
                                      "1500w         ",
                                      "1500w         ",
                                      "1500w         ",
                                      "1500w         "  };

const STR *const StrM6_5O[]  =  {     "200w          ",
                                      "200w          ",
                                      "200w          ",
                                      "200w          ",
                                      "200w          "  };

const STR *const StrM6_5E[]  =  {     "3300w         ",
                                      "3300w         ",
                                      "3300w         ",
                                      "3300w         ",
                                      "3300w         "  };

const STR *const StrM6_5F[]  =  {     "4000w         ",
                                      "4000w         ",
                                      "4000w         ",
                                      "4000w         ",
                                      "4000w         "  };

const STR *const StrM6_5H[]  =  {     "800w          ",
                                      "800w          ",
                                      "800w          ",
                                      "800w          ",
                                      "800w          "  };

const STR *const StrM6_5J[]  =  {     "400w          ",
                                      "400w          ",
                                      "400w          ",
                                      "400w          ",
                                      "400w          "  };


const STR *const PassStr[]   =  {     "Pass",
                                      "OK",
                                      "OK",
                                      "Pass",
                                      "Pass"  };

const STR *const FailStr[]   =  {     "Fail",
                                      "Fehler",
                                      "Falo",
                                      "Gsto",
                                      "Echc"  };

const STR *const StrM6_6[]   =  {     "Actuator = ",
                                      "VE = ",
                                      "Actuador = ",
                                      "Actuator = ",
                                      "Actuator = "  };

const STR *const StrM6_6A[]  =  {     "ae/ao/HH",
                                      "ae/ao/HH",
                                      "ae/ao/HH",
                                      "ae/ao/HH",
                                      "ae/ao/HH"  };

const STR *const StrM6_6B[]  =  {     "ao      ",
                                      "ao      ",
                                      "ao      ",
                                      "ao      ",
                                      "ao      "  };

const STR *const StrM6_6C[]  =  {     "aed/aod ",
                                      "aed/aod ",
                                      "aed/aod ",
                                      "aed/aod ",
                                      "aed/aod "  };

const STR *const StrM6_6D[]  =  {     "aod     ",
                                      "aod     ",
                                      "aod     ",
                                      "aod     ",
                                      "aod     "  };

const STR *const StrM6_6E[]  =  {     "aef     ",
                                      "aef     ",
                                      "aef     ",
                                      "aef     ",
                                      "aef     "  };

const STR *const StrM6_6F[]  =  {     "aof     ",
                                      "aof     ",
                                      "aof     ",
                                      "aof     ",
                                      "aof     "  };

const STR *const StrM6_6G[]  =  {     "CUSTOM  ",
                                      "EINST.  ",
                                      "PERSON  ",
                                      "PERSON  ",
                                      "SPEC    "  };


const STR *const StrM6_7[]   =  {     "Control Level = ",
                                      "Steuerlevel = ",
                                      "Nivel Control = ",
                                      "Livel Control = ",  
                                      "Niveau Comde = "  };

const STR *const StrM6_7A[]  =  {     "t   ",
                                      "t   ",
                                      "t   ",
                                      "t   ",
                                      "t   "  };

const STR *const StrM6_7B[]  =  {     "e   ",        
                                      "e   ",
                                      "e   ",
                                      "e   ",
                                      "e   "  };

const STR *const StrM6_7C[]  =  {     "d   ",
                                      "d   ",
                                      "d   ",
                                      "d   ",
                                      "d   "  };

const STR *const StrM6_7D[]  =  {     "a   ",
                                      "a   ",
                                      "a   ",
                                      "a   ",
                                      "a   "  };

const STR *const StrM6_7E[]  =  {     "f   ",
                                      "f   ",
                                      "f   ",
                                      "f   ",
                                      "f   "  };

const STR *const StrM6_7F[]  =  {     "TEST",
                                      "TEST",
                                      "TEST",
                                      "TEST",
                                      "TEST"  };

const STR *const StrM6_7G[]  =  {     "ea  ",
                                      "ea  ",
                                      "ea  ",
                                      "ea  ",
                                      "ea  "  };


const STR *const StrM6_10[]  =  {     "P/S S/N=",   /* All of these reduced in size for CP in doors */
                                      "Gen #  =",
                                      "F/A #  =",
                                      "P/S S/N= ",
                                      "P/S S/N="    /* This suggested by Bob Stevenson and Ralph Bermeman 07-19-00*/ };

const STR *const StrM6_11[]  =  {     "Act S/N=",
                                      "VE SerN=",
                                      "Ser Act=",
                                      "Seratt#=",
                                      "Act S/N="  };

const STR *const StrM6_12[]  =  {     "Calibration Data>",
                                      "Kalib. Daten>",
                                      "Datos calibrado >",
                                      "Dati calibrazion>",
                                      "Donnees calibrg>"  };

const STR *const StrM6_13[]  =  {     "CALIBRATION DATA ",
                                      "KALIB. DATEN ",
                                      "DATOS CALIBRADO ",
                                      "DATI CALIBRAZIONE",
                                      "DONNEES CALIBRAT."  };

const STR *const StrM6_14[]  =  {     "Calibration =",
                                      "Kalibrier. =",
                                      "Calibracion =",
                                      "Calibrazion =",
                                      "Calibrat. ="  };

const STR *const StrM6_15[]  =  {     "Date Run ",
                                      "Schw.Datum",
                                      "Fecha Ejec.",
                                      "Eseg dat ",
                                      "Date Exe"  };

const STR *const StrM6_18[]  =  {     "P/S Presets> ",
                                      "Gen Vorein> ",
                                      "F/A Presel> ",
                                      "Preset P/S> ",
                                      "Prereg Gen> "  };

const STR *const StrM6_19[]  =  {     "P/S PRESETS ",
                                      "GEN VOREINST.",
                                      "F/A PRESEL ",
                                      "PRESET P/S ",
                                      "PREREG GEN "  };

const STR *const StrM6_20[]  =  {     "P/S Library> ",
                                      "Gen Bibliot.> ",
                                      "Libreria FA> ",
                                      "Libreri P/S> ",
                                      "P/S biblio> "  };
  
const STR *const StrM6_21[]  =  {     "Preset Names> ",
                                      "Param. Namen> ",
                                      "Nombres Presl> ",
                                      "Nome Presets> ",
                                      "Noms Presets> "  };
                               
const STR *const StrM6_22[]  =  {     "P/S Library ",
                                      "Gen Bibliot. ",
                                      "Libreria FA ",
                                      "Libreri P/S ",
                                      "P/S biblio "  };

const STR *const StrM6_24[]  =  {     "PRESET NAMES ",
                                      "PARAM. NAMEN ",
                                      "NOMBRES PRESL",
                                      "NOME PRESETS ",
                                      "NOMS PRESETS "  };

const STR *const Str_analog[]  = {    "Analog",
                                      "Analog",//detrans
                                      "Analog",
                                      "Analog",
                                      "Analog"  }; //ftrans

const STR *const Str_digital[] = {    "Digital",
                                      "Digital",
                                      "Digital",
                                      "Digital",
                                      "Digital"  };//ftrans

const STR *const Str_psversion[] = {  "P/S Version =",
                                      "Gen. Version =",//detrans
                                      "Version F/A =",
                                      "P/S Version =",
                                      "GEN Version ="  };//frtrans

const STR *const Str_psanalog[]  = {  "P/S =         Analog",
                                      "Generator =   Analog",
                                      "F/A =         Analog",
                                      "P/S =         Analog",
                                      "GEN =         Analog"  };

const STR *const Str_psdigital[]  = { "P/S =        Digital",
                                      "Generator =  Digital",
                                      "F/A =        Digital",
                                      "P/S =        Digital",
                                      "GEN =        Digital"  };

const STR *const StrM7_0[]   =  {     "Sys Config",
                                      "Syst. Konfig.",
                                      "Config Sis",
                                      "Config Sis",
                                      "Config Sys"  };

const STR *const StrM7_1A[]  =  {     "Language>    English",
                                      "Sprache>    Englisch",
                                      "Idioma>       Ingles",
                                      "Lingua>      Inglese",
                                      "Langue>      Anglais"  };

const STR *const StrM7_1B[]  =  {     "Language>     German",
                                      "Sprache>     Deutsch",
                                      "Idioma>       Aleman",
                                      "Lingua>      Tedesco",
                                      "Langue>       Alemnd"  };

const STR *const StrM7_1C[]  =  {     "Language>    Spanish",
                                      "Sprache>    Spanisch",
                                      "Idioma>      Espanol",
                                      "Lingua>     Spagnolo",
                                      "Langue>      Espagn."  };

const STR *const StrM7_1D[]  =  {     "Language>    Italian",
                                      "Sprache> Italienisch",
                                      "Idioma>     Italiano",
                                      "Lingua>     Italiano",
                                      "Langue>      Italien"  };

const STR *const StrM7_1E[]  =  {     "Language>     French",
                                      "Sprache>   Franzoes.",
                                      "Idioma>      Frances",
                                      "Lingua>     Francese",
                                      "Langue>     Francais"  };   

const STR *const StrM7_2[]   =  {     "Units",
                                      "Einheit",
                                      "Unidad",
                                      "Unita",
                                      "Untes"  };

const STR *const StrM7_2A[]  =  {     "USCS",
                                      "USCS",
                                      "USCS",
                                      "USCS",
                                      "USCS"  };

const STR *const StrM7_2B[]  =  {     "Metric",
                                      "Metrisch",
                                      "Metric",
                                      "Metric",
                                      "Metr."  };

const STR *const StrM7_3[]   =  {     "Password",
                                      "Passwort",
                                      "CNTRSENA",
                                      "Password",
                                      "MOT PASS"  };

// Added by J.B.
const STR *const StrM7_5[] = {        "Start Screen",
                                      "Start Bild",
                                      "Inic Pantlla",
                                      "Avvia Screen",
                                      "Ecran Demarr"  };

const STR *const StrM7_5A[] = {       "Main",
                                      "Haupt",
                                      "Prnc",
                                      "Prnc",
                                      "Prnc"  };

const STR *const StrM7_5B[] = {       "Run",
                                      "Schw",
                                      "Eje",
                                      "Eseg",
                                      "Exe"  };

const STR *const StrM7_8[]   =  {     "RS232",
                                      "RS232",
                                      "RS232",
                                      "RS232",
                                      "RS232"  };


const STR *const StrM7_9[]   =  {     "Gen Alarm Reset",
                                      "Reset Ges.Alarm",
                                      "Reset Alarm Gen",
                                      "Reset Allar Gen",
                                      "RAZ Alarm Gen"  };

const STR *const StrM7_10[]  =  {     "Time",
                                      "Zeit",
                                      "Tiem",
                                      "Tempo",
                                      "Temps"  };

const STR *const StrM7_11[]  =  {     "Date",
                                      "Datum",
                                      "Fecha",
                                      "Data",
                                      "Date"  };

const STR *const StrM7_15[]  =  {     "Hand Held ",
                                      "Handgeraet",
                                      "Portatil",
                                      "Portatil",
                                      "Portativ"  };

const STR *const StrM7_20[]  =  {     "Digital Filter",
                                      "Digitalfilter",
                                      "Filtro Digital",
                                      "Filtro Digital",
                                      "Filtre Digital"  };

const STR *const StrM7_22[]  =  {     "Amp Control",
                                      "Amp.Steuer.",
                                      "Control Amp",
                                      "Control Amp",
                                      "Cmde Ampl."  };

const STR *const StrM7_22A[] =  {     "Ext",
                                      "Ext",
                                      "Ext",
                                      "Est",
                                      "Ext"  };

const STR *const StrM7_22B[] =  {     "Int",
                                      "Int",
                                      "Int",
                                      "Int",
                                      "Int"  };

const STR *const StrM7_23[]  =  {     "Freq Offset",
                                      "Freq. Offset",
                                      "Desvio Frec",
                                      "Freq Offset",
                                      "Decal Freq"  };

const STR *const StrM7_24[]  =  {     "Act Clr Output",
                                      "VE Ausgang frei",
                                      "Sal. Act. Libre",
                                      "Canc Outpt Att",
                                      "Sortie Deg Act"  };

const STR *const StrM7_26[]  =  {     "Adjust While Run",
                                      "Einst. bei Ablauf",
                                      "Ajuste en Func",
                                      "Regol Mentre Lav",
                                      "Regler pdt Exec."  };

const STR *const StrM7_30[]  =  {     "Preset Counter>",
                                      "Param. Zaehler>",
                                      "Contdor Presel>",
                                      "Contatore Prst>",
                                      "Compt. Preset>"  };

const STR *const StrM7_30A[] =  {     "PRESET COUNT",
                                      "PARAM. ZAEHLER",
                                      "CONTD PRESEL",
                                      "PRESET CONT.",
                                      "COMPT PRESET"  };

const STR *const StrM7_31[]  =     {  "Reset",
                                      "Reset",
                                      "Reset",
                                      "Reset",
                                      "RAZ"  };

const STR *const StrM7_32[]  =     {  "Cancel Reset",
                                      "Abbr. Reset",
                                      "Cancel Reset",
                                      "Can Reset",
                                      "Annuler RAZ"  };

const STR *const StrM7_33[]  =  {     "Sequencing",
                                      "Takten",
                                      "Secuencia",
                                      "Sequenza",
                                      "Sequence"  };

const STR *const StrM7_34[]  =  {     "Act Settings >",
                                      "VE Einstell. > ",
                                      "Ajustes Act > ",
                                      "Impostaz. Att>",
                                      "Reglages Act >"  };

const STR *const StrM7_35[]  =  {     "Beepers >",
                                      "Signal > ",
                                      "Busca >  ",
                                      "Segnltr >",
                                      "Beepers >"  };

const STR *const StrM7_36[]  =  {     "Bargraph Scales >",
                                      "Balken Anzeige > ",
                                      "Esc GraFabarras >",
                                      "Scale Istrogr. > ",
                                      "Ech. Bargraph >  "  };

const STR *const StrM7_37[]  =  {     "P/S Settings>",
                                      "Gen Einstell.>",
                                      "Ajustes F/A> ",
                                      "Impost. P/S> ",
                                      "Reglages Gen>"  };

const STR *const StrM7_38[]  =  {     "P/S SETTINGS",
                                      "GEN EINSTELL.",
                                      "AJUSTES F/A",
                                      "IMPOST. P/S",
                                      "Reglages Gen"  };

const STR *const StrM7_39[]  =  {     "P/S",
                                      "Gen",
                                      "F/A",
                                      "P/S",
                                      "Gen"  };

const STR *const StrM7_40[]  =  {     "Extra Cooling",
                                      "Zusatzkuehlung",
                                      "Refrig Extra",
                                      "Raffred. Extra",
                                      "Refroid Supp"  };

const STR *const StrM7_41[]  =  {     "Welder Addr",
                                      "Welder Addr",
                                      "Welder Addr",
                                      "Welder Addr",
                                      "Welder Addr"  };

const STR *const StrM7_42[]  =  {     "SYS EQUIPMENT",
                                      "SYSTAUSRUEST.",
                                      "EQUIPO SISTEM",
                                      "ATTRZZTRE SIS",
                                      "EQUIPEMNT SYS"  };

const STR *const StrM7_43[]  =  {     "User I/O >",
                                      "Benutzer I/O >",
                                      "Usuario I/O >",
                                      "Utente O/I >",
                                      "E/S Client >"  };

const STR *const StrM7_48[]  =  {     "USER I/O",
                                      "User_EIN",
                                      "USAR DR",
                                      "UTNT_IN",
                                      "EN_UTIL"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_49[]  =   {    "J3-22 Output  >", 
                                      "J3-22 Ausgang >",
                                      "Salida J3-22  >",
                                      "Uscita J3-22  >",
                                      "Sortie J3-22  >"  };

const STR *const StrM7_50[]  =   {    "Current Value", 
                                      "Aktueller Wert",
                                      "Valor corriente",
                                      "Valore corrente",
                                      "Valeur actuelle"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_53[]  =   {    "J3-32 Input   >",
                                      "J3-32 Eingang >",
                                      "Entrada J3-32 >",
                                      "Ingresso J3-32>",
                                      "Entrée J3-32  >"  };

const STR *const StrM7_54[]  =  {     "Select Preset1",
                                      "Select Preset1",
                                      "Selecc Presel1",
                                      "Selez. Preset1",
                                      "Select Preset1"  };

const STR *const StrM7_55[]  =  {     "Ext U/S Delay",
                                      "Ext U/S Delay",
                                      "Ext U/S Delay",
                                      "Ext U/S Delay",
                                      "Ext U/S Delay"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_56[]  =   {    "J3-33 Input   >", 
                                      "J3-33 Eingang >",
                                      "Entrada J3-33 >",
                                      "Ingresso J3-33>",
                                      "Entrée J3-33  >"  };

const STR *const StrM7_57[]  =  {     "Select Preset2",
                                      "Select Preset2",
                                      "Selecc Presel2",
                                      "Selez. Preset2",
                                      "Select Preset2"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_59[]  =   {    "J3-19 Input   >", 
                                      "J3-19 Eingang >",
                                      "Entrada J3-19 >",
                                      "Ingresso J3-19>",
                                      "Entrée J3-19  >"  };

const STR *const StrM7_60[]  =  {     "Select Preset4",
                                      "Select Preset4",
                                      "Selecc Presel4",
                                      "Selez. Preset4",
                                      "Select Preset4"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_62[]  =   {    "J3-17 Input   >", 
                                      "J3-17 Eingang >",
                                      "Entrada J3-17 >",
                                      "Ingresso J3-17>",
                                      "Entrée J3-17  >"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_62A[]  =  {    "J3-31 Input   >", 
                                      "J3-31 Eingang >",
                                      "Entrada J3-31 >",
                                      "Ingresso J3-31>",
                                      "Entrée J3-31  >"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_62B[]  =  {    "J3-1  Input   >", 
                                      "J3-1 Eingang  >",
                                      "Entrada J3-1  >",
                                      "Ingresso J3-1 >",
                                      "Entrée J3-1   >"  };

const STR *const StrM7_63[]  =  {     "Select Preset8",
                                      "Select Preset8",
                                      "Selecc Presel8",
                                      "Selez. Preset8",
                                      "Select Preset8"  };

const STR *const StrM7_64[]  =  {     "Select Preset16",
                                      "Select Preset16",
                                      "Selecc Presel16",
                                      "Selez. Preset16",
                                      "Select Preset16"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_66[]  =   {    "J3-36 Output  >", 
                                      "J3-36 Ausgang >",
                                      "Salida J3-36  >",
                                      "Uscita J3-36  >",
                                      "Sortie J3-36  >"  };

/* The '>' must be beyond character position 14 so the Pgxofy information covers it up */
const STR *const StrM7_67[]  =   {    "J3-8  Output  >", 
                                      "J3-8  Ausgang >",
                                      "Salida J3-8   >",
                                      "Uscita J3-8   >",
                                      "Sortie J3-8   >"  };

const STR *const StrM7_69[]  =  {     "Confirm Preset",
                                      "Param. bestaet.",
                                      "Confirm Presel",
                                      "Conferm Preset",
                                      "Confirm.Preset"  };


const STR *const StrM7_70A[] =  {     "Amplitude Decay",
                                      "Amplitude Decay",
                                      "Descenso Amp.",
                                      "Amplitude Decay",
                                      "amplit.retombee"  };

const STR *const StrM7_70B[] =  {     "Ext Beeper",      
                                      "Ext akust Signal",
                                      "Ext Beeper",
                                      "Segnale esterno",
                                      "Beeper externe"  };

const STR *const StrM7_70C[] =  {     "Cycle Okay",  
                                      "Zyklus ok",
                                      "Ciclo correcto",
                                      "Ciclo ok",
                                      "Cycle OK"  };

const STR *const StrM7_70D[] =  {     "No Cycle Alarm",
                                      "Kein Zyklusalarm",
                                      "No alar. Ciclo",
                                      "No Cycle Alarm",
                                      "Pas d'alarme"  };

const STR *const StrM7_70E[] =  {     "Overload Alarm", 
                                      "Ueberlast Alarm",
                                      "Alar. sobrecarga",
                                      "Overload Alarm",
                                      "Alarme surcharge"  };

const STR *const StrM7_70F[] =  {     "Modified Alarm", 
                                      "Zyklusaenderung",
                                      "Alar. Modificada",
                                      "Modified Alarm",
                                      "Alarme modifiee"  };

const STR *const StrM7_70G[] =  {     "Note",           
                                      "Hinweis",
                                      "Nota",
                                      "Note",
                                      "Note"  };

const STR *const StrM7_70H[] =  {     "Missing Part",   
                                      "Teil fehlt",
                                      "Parte perdida",
                                      "Parte mancante",
                                      "Piece manquante"  };

const STR *const StrM7_70I[] =  {     "Sync Out",          /**** MUST BE TRANSLATED ****/
                                      "Sync Out",
                                      "Sync Out",
                                      "Sync Out",
                                      "Sync Out"  };

const STR *const StrM7_72[] =   {     "Amp Decay(&)",   
                                      "Amp Reduzier(&)",
                                      "Descenso Amp(&)",
                                      "Amp Decay(&)",
                                      "Amp Decay(&)"  };

const STR *const StrM7_74[]  =  {     "CUSTOM @ Home",  
                                      "Indiv Einstel",
                                      "CUSTOM @ Home",
                                      "CUSTOM @ Home",
                                      "Config Lim Sw"  };

const STR *const StrM7_75[]  =  {     "Cycle Start",
                                      "Zyklusstart",
                                      "Inicio Cicl",
                                      "Inizio Cicl",
                                      "Lanct Cycle"  };

const STR *const StrM7_76[]  =  {     "User Inputs",
                                      "User Eingab.",
                                      "EntUsuario",
                                      "Inpututent",
                                      "Ent Util"  };

const STR *const StrM7_77[]  =  {     "Upper Limit Sw",
                                      "ULS",
                                      "LS",
                                      "ILS",
                                      "ULS"  };

const STR *const StrM7_79[]  =  {     "Gnd Det",
                                      "Mk",
                                      "Det TT",
                                      "Gnd Det",
                                      "Det Mse"  };

const STR *const StrM7_82[]  =  {     "Start Sig + SV",
                                      "Start Sig. + MV",
                                      "Inic. Sol + EV",
                                      "Seg avvio + EV",
                                      "Sig Start + EV"  };

const STR *const StrM7_83[]  =  {     "Start Sig no SV",
                                      "Start Sig. kein MV",
                                      "Inic Sol sin EV",
                                      "Seg avvio no EV",
                                      "Sig Start ss EV"  };

const STR *const StrM7_84[]  =  {     "Trg SW no SV",
                                      "Trig kein MV",
                                      "No Dp Cnm EV",
                                      "Int Tg no EV",
                                      "Trig ss EV"  };

const STR *const StrM7_85[]  =  {     "Ext Sig no SV",
                                      "Ext. Sig. kein MV",
                                      "Seo Ext no EV",
                                      "Seg est no EV",
                                      "Sig Ext ss EV"  };

const STR *const StrM7_86[]  =  {     "Ext Presets",
                                      "Ext. Vorein",
                                      "Persel Ext.",
                                      "Preset Est.",
                                      "Preset Ext."  };

const STR *const StrM7_88[]  =  {     "Display Lock",  
                                      "Eingabe Verriegl",
                                      "Bloquear pantalla",
                                      "Display spento",
                                      "Bloquage clavier"  };

const STR *const StrM7_89[]  =  {     "Ext Signal",     /**** MUST BE TRANSLATED ****/
                                      "Ext Signal",
                                      "Ext Signal",
                                      "Ext Signal",
                                      "Ext Signal"  };

const STR *const StrM7_90[]  =  {     "Sonics Disable",   
                                      "Schall deaktiv",
                                      "Desactivar ultr.",
                                      "Sonics Disable",
                                      "Interruption us"  };

const STR *const StrM7_91[]  =  {     "Memory Reset",     
                                      "Speicher loesch",
                                      "Reset memoria",
                                      "Reset memoria",
                                      "Reset memoire"  };

const STR *const StrM7_92[]  =  {     "External Start",     
                                      "External Start",
                                      "External Start",
                                      "External Start",
                                      "External Start"  };

const STR *const StrM7_93[]  =  {     "Sync In",    /**** MUST BE TRANSLATED ****/
                                      "Sync In",
                                      "Sync In",
                                      "Sync In",
                                      "Sync In"  };


const STR *const StrM7A_6[]   =  {    "LANGUAGE",
                                      "SPRACHE",
                                      "IDIOMA",
                                      "LINGUA",
                                      "LANGUE"  };

/* Language # 1 in menu */
const STR *const StrM7B_7[]   =  {    "English",
                                      "Englisch",
                                      "Ingles",
                                      "Inglese",
                                      "Anglais"  };

        
/* Language # 2 in menu */
const STR *const StrM7B_8[]   =  {    "German",
                                      "Deutsch",
                                      "Aleman",
                                      "Tedesco",
                                      "Alemnd"  };

/* Language # 3 in menu */
const STR *const StrM7B_9[]   =  {    "Spanish",
                                      "Spanisch",
                                      "Espanol",
                                      "Spagnpl",
                                      "Espgnol"  };

/* Language # 4 in menu */
const STR *const StrM7B_10[]  =  {    "Italian",
                                      "Italienisch",
                                      "Italiano",
                                      "Italiano",
                                      "Italien"  };

/* Language # 5 in menu */
const STR *const StrM7B_11[]  =  {    "French",
                                      "Franzoes.",
                                      "Francs",
                                      "Francs",
                                      "Francais"  };


const STR *const StrM7A_13A[] = {     "BAUD RATE",
                                      "BAUDRATE",
                                      "TASA BAUD",
                                      "BAUD RATE",
                                      "TAUX BAUD"  };

const STR *const StrM7A_14[]  = {     "Baud Rate>      4800",
                                      "Baudrate>       4800",
                                      "Tasa Baud>      4800",
                                      "Baud Rate>      4800",
                                      "Taux Baud>      4800"  };

const STR *const StrM7A_14A[] = {     "4800",
                                      "4800",
                                      "4800",
                                      "4800",
                                      "4800"  };

const STR *const StrM7A_15[]  = {     "Baud Rate>      9600",
                                      "Baudrate>       9600",
                                      "Tasa Baud>      9600",
                                      "Baud Rate>      9600",
                                      "Taux Baud>      9600"  };

const STR *const StrM7A_15A[] = {     "9600",
                                      "9600",
                                      "9600",
                                      "9600",
                                      "9600"  };

const STR *const StrM7A_16[]  = {     "Baud Rate>     19200",
                                      "Baudrate>      19200",
                                      "Tasa Baud>     19200",
                                      "Baud Rate>     19200",
                                      "Taux Baud>     19200"  };

const STR *const StrM7A_16A[] = {     "19200",
                                      "19200",
                                      "19200",
                                      "19200",
                                      "19200"  };

const STR *const StrM7A_20[]  = {     "1X",
                                      "1X",
                                      "1X",
                                      "1X",
                                      "1X"  };

const STR *const StrM7A_21[]  = {     "2X",
                                      "2X",
                                      "2X",
                                      "2X",
                                      "2X"  };

const STR *const StrM7A_22[]  = {     "3X",
                                      "3X",
                                      "3X",
                                      "3X",
                                      "3X"  };

const STR *const StrM7A_23[]  = {     "ACT CLR OUT",
                                      "VE frei",
                                      "SAL. ACT LIBRE",
                                      "CANC ATT",
                                      "SOR DEG ACT"  };

const STR *const StrM7A_24A[] = {     "Act Clr D(&&)",
                                      "VE W frei(&&)",
                                      "Sld Act D(&&)",
                                      "Canc D(&&)",
                                      "Deg Act D(&&)"  };

const STR *const StrM7A_24B[] = {     "Output @ MPS Sw",
                                      "Ausgng @ MPS Sch.", 
                                      "Salida @ MPS Sw",
                                      "Output @ MPS Sw", //
                                      "Output @ MPS Sw"  };//FRTRANS

const STR *const StrM7A_29[]  = {     "Hours",
                                      "Stunden", 
                                      "Horas", 
                                      "Ore", 
                                      "Heures"   };

const STR *const StrM7A_30[]  = {     "Minutes",
                                      "Minuten", 
                                      "Minutos", 
                                      "Minuti", 
                                      "Minutes"   }; 

const STR *const StrM7A_31[]  = {     "Month",
                                      "Monat", 
                                      "Mes", 
                                      "Mese", 
                                      "Mois"  };

const STR *const StrM7A_31A[] = {     "Day",
                                      "Tag", 
                                      "Dia", 
                                      "Giorno", 
                                      "Jour"  };

const STR *const StrM7A_32[]  = {     "Year",
                                      "Jahr", 
                                      "Ano ", 
                                      "Anno", 
                                      "Annee"  };
  
const STR *const StrM7A_35[]  = {     "24V",
                                      "24V", 
                                      "24V", 
                                      "24V", 
                                      "24V"   };

const STR *const StrM7A_36[]  = {     "0V",
                                      "0V", 
                                      "0V", 
                                      "0V", 
                                      "0V"   };

const STR *const StrM7A_40[]  = {     "SEQUENCING",
                                      "TAKTEN",
                                      "SECUENCIA", 
                                      "SEQUENZA", 
                                      "SEQUENCE"  };

const STR *const StrM7A_40A[] = {     "Sequence 1",
                                      "Takte 1",
                                      "Secuenci 1",
                                      "Sequenza 1",
                                      "Sequence 1"  };

const STR *const StrM7A_40B[] = {     "Sequence 2",
                                      "Takte 2",
                                      "Secuenci 2",
                                      "Sequenza 2",
                                      "Sequence 2"  };

const STR *const StrM7A_40C[] = {     "Sequence 3",
                                      "Takte 3",
                                      "Secuenci 3",
                                      "Sequenza 3",
                                      "Sequence 3"  };


const STR *const StrM7A_41[]  = {     "ACT SETTINGS",
                                      "VE EINSTELL.",
                                      "AJUSTES ACT",
                                      "IMPOSTAZ ATT",
                                      "REGLAGES ACT"  };


const STR *const StrM7A_41A[] = {     "Cyl Dia(in) >    1.5",
                                      "Zyl. Dur.(in) >  1.5",
                                      "Dia Cil(in) >    1.5",
                                      "Dia cil(in) >    1.5",
                                      "Dia Cyl(in) >    1.5"  };

const STR *const StrM7A_41B[] = {     "Cyl Dia(in) >    2.0",
                                      "Zyl. Dur.(in) >  2.0",
                                      "Dia Cil(in) >    2.0",
                                      "Dia cil(in) >    2.0",
                                      "Dia Cyl(in) >    2.0"  };

const STR *const StrM7A_41C[] = {     "Cyl Dia(in) >    2.5",
                                      "Zyl. Dur.(in) >  2.5",
                                      "Dia Cil(in) >    2.5",
                                      "Dia cil(in) >    2.5",
                                      "Dia Cyl(in) >    2.5"  };

const STR *const StrM7A_41D[] = {     "Cyl Dia(in) >    3.0",
                                      "Zyl. Dur.(in) >  3.0",
                                      "Dia Cil(in) >    3.0",
                                      "Dia cil(in) >    3.0",
                                      "Dia Cyl(in) >    3.0"  };

const STR *const StrM7A_41E[] = {     "Cyl Dia(in) >   3.25",
                                      "Zyl. Dur.(in) > 3.25",
                                      "Dia Cil(in) >   3.25",
                                      "Dia cil(in) >   3.25",
                                      "Dia Cyl(in) >   3.25"  };

const STR *const StrM7A_41P[] = {     "Cyl Dia(in) >    4.0",
                                      "Zyl Dur(in) >    4.0",
                                      "Dia Cil(in) >    4.0",
                                      "Dia cil(in) >    4.0",
                                      "Dia Cyl(in) >    4.0"  };

const STR *const StrM7A_41Z[] = {     "Cyl Dia(mm) >     40",
                                      "Zyl. Dur.(mm) >   40",
                                      "Dia Cil(mm) >     40",
                                      "Dia cil(mm) >     40",
                                      "Dia Cyl(mm) >     40"  };

const STR *const StrM7A_41Y[] = {     "Cyl Dia(mm) >     50",
                                      "Zyl. Dur.(mm) >   50",
                                      "Dia Cil(mm) >     50",
                                      "Dia cil(mm) >     50",
                                      "Dia Cyl(mm) >     50"  };

const STR *const StrM7A_41X[] = {     "Cyl Dia(mm) >     63",
                                      "Zyl. Dur.(mm) >   63",
                                      "Dia Cil(mm) >     63",
                                      "Dia cil(mm) >     63",
                                      "Dia Cyl(mm) >     63"  };

const STR *const StrM7A_41W[] = {     "Cyl Dia(mm) >     80",
                                      "Zyl. Dur.(mm) >   80",
                                      "Dia Cil(mm) >     80",
                                      "Dia cil(mm) >     80",
                                      "Dia Cyl(mm) >     80"  };


const STR *const StrM7A_41F[] = {     "Cyl Dia >     Custom",
                                      "Zyl. Dur. >    Spez.",
                                      "Dia Cil >     Person",
                                      "Dia cil >     Person",
                                      "Dia Cyl >       Spec"  };


const STR *const StrM7A_41G[] = {     "Cyl Stroke(in) > 4.0",
                                      "Zyl. Hub(in) >   4.0",
                                      "Carrera Ci(in) > 4.0",
                                      "Corsa cil(in) >  4.0",
                                      "Course Cyl(in) > 4.0"  };

const STR *const StrM7A_41H[] = {     "Cyl Stroke(in) > 5.0",
                                      "Zyl. Hub(in) >   5.0",
                                      "Carrera Ci(in) > 5.0",
                                      "Corsa cil(in) >  5.0",
                                      "Course Cyl(in) > 5.0"  };

const STR *const StrM7A_41J[] = {     "Cyl Stroke(in) > 6.0",
                                      "Zyl. Hub(in) >   6.0",
                                      "Carrera Ci(in) > 6.0",
                                      "Corsa cil(in) >  6.0",
                                      "Course Cyl(in) > 6.0"  };

const STR *const StrM7A_41K[] = {     "Cyl Stroke(in) > 7.0",
                                      "Zyl. Hub(in) >   7.0",
                                      "Carrera Ci(in) > 7.0",
                                      "Corsa cil(in) >  7.0",
                                      "Course Cyl(in) > 7.0"  };

const STR *const StrM7A_41L[] = {     "Cyl Stroke(in) > 8.0",
                                      "Zyl. Hub(in) >   8.0",
                                      "Carrera Ci(in) > 8.0",
                                      "Corsa cil(in) >  8.0",
                                      "Course Cyl(in) > 8.0"  };

const STR *const StrM7A_41M[] = {     "Cyl Stroke >  Custom",
                                      "Zyl. Hub >     Spez.",
                                      "Carrera Ci >  Person",
                                      "Corsa cil >   Person",
                                      "Course Cyl >    Spec"  };

const STR *const StrM7A_41V[] = {     "Cyl Stroke(mm) >  80",
                                      "Zyl. Hub(mm) >    80",
                                      "Carrera Ci(mm) >  80",
                                      "Corsa cil(mm) >   80",
                                      "Course Cyl(mm) >  80"  };

const STR *const StrM7A_41U[] = {     "Cyl Stroke(mm) > 100",
                                      "Zyl. Hub(mm) >   100",
                                      "Carrera Ci(mm) > 100",
                                      "Corsa cil(mm) >  100",
                                      "Course Cyl(mm) > 100"  };

const STR *const StrM7A_41T[] = {     "Cyl Stroke(mm) > 125",
                                      "Zyl. Hub(mm) >   125",
                                      "Carrera Ci(mm) > 125",
                                      "Corsa cil(mm) >  125",
                                      "Course Cyl(mm) > 125"  };

const STR *const StrM7A_41S[] = {     "Cyl Stroke(mm) > 160",
                                      "Zyl. Hub(mm) >   160",
                                      "Carrera Ci(mm) > 160",
                                      "Corsa cil(mm) >  160",
                                      "Course Cyl(mm) > 160"  };


const STR *const StrM7A_41N[] = {     "CYL DIA",
                                      "ZYL DUR",
                                      "DIA CIL",
                                      "DIA CIL",
                                      "DIA CYL"  };

const STR *const StrM7A_42[]  = {     "1.5(in)",
                                      "1.5(in)",
                                      "1.5(in)",
                                      "1.5(in)",
                                      "1.5(in)"  };

const STR *const StrM7A_43[]  = {     "2.0(in)",
                                      "2.0(in)",
                                      "2.0(in)",
                                      "2.0(in)",
                                      "2.0(in)"  };

const STR *const StrM7A_44[]  = {     "2.5(in)",
                                      "2.5(in)",
                                      "2.5(in)",
                                      "2.5(in)",
                                      "2.5(in)"  };

const STR *const StrM7A_45[]  = {     "3.0(in)",
                                      "3.0(in)",
                                      "3.0(in)",
                                      "3.0(in)",
                                      "3.0(in)"  };

const STR *const StrM7A_46[]  = {     "3.25(in)",
                                      "3.25(in)",
                                      "3.25(in)",
                                      "3.25(in)",
                                      "3.25(in)"  };

const STR *const StrM7A_46A[] = {     "40(mm)",
                                      "40(mm)",
                                      "40(mm)",
                                      "40(mm)",
                                      "40(mm)"  };

const STR *const StrM7A_46B[] = {     "50(mm)",
                                      "50(mm)",
                                      "50(mm)",
                                      "50(mm)",
                                      "50(mm)"  };

const STR *const StrM7A_46C[] = {     "63(mm)",
                                      "63(mm)",
                                      "63(mm)",
                                      "63(mm)",
                                      "63(mm)"  };

const STR *const StrM7A_46D[] = {     "80(mm)",
                                      "80(mm)",
                                      "80(mm)",
                                      "80(mm)",
                                      "80(mm)"  };

const STR *const StrM7A_46E[] = {     "4.0(in)",
                                      "4.0(in)",
                                      "4.0(in)",
                                      "4.0(in)",
                                      "4.0(in)"  };
                              
const STR *const StrM7A_47[]  = {     "Custom >",
                                      "Einst. >",
                                      "Person >",
                                      "Person >",
                                      "Spec >"  };

const STR *const StrM7A_48[]  = {     "4.0(in)",
                                      "4.0(in)",
                                      "4.0(in)",
                                      "4.0(in)",
                                      "4.0(in)"  };

const STR *const StrM7A_49[]  = {     "5.0(in)",
                                      "5.0(in)",
                                      "5.0(in)",
                                      "5.0(in)",
                                      "5.0(in)"  };

const STR *const StrM7A_50[]  = {     "6.0(in)",
                                      "6.0(in)",
                                      "6.0(in)",
                                      "6.0(in)",
                                      "6.0(in)"  };

const STR *const StrM7A_51[]  = {     "7.0(in)",
                                      "7.0(in)",
                                      "7.0(in)",
                                      "7.0(in)",
                                      "7.0(in)"  };

const STR *const StrM7A_52[]  = {     "8.0(in)",
                                      "8.0(in)",
                                      "8.0(in)",
                                      "8.0(in)",
                                      "8.0(in)"  };

const STR *const StrM7A_52A[] = {     "80(mm)",
                                      "80(mm)",
                                      "80(mm)",
                                      "80(mm)",
                                      "80(mm)"  };

const STR *const StrM7A_52B[] = {     "100(mm)",
                                      "100(mm)",
                                      "100(mm)",
                                      "100(mm)",
                                      "100(mm)"  };

const STR *const StrM7A_52C[] = {     "125(mm)",
                                      "125(mm)",
                                      "125(mm)",
                                      "125(mm)",
                                      "125(mm)"  };

const STR *const StrM7A_52D[] = {     "160(mm)",
                                      "160(mm)",
                                      "160(mm)",
                                      "160(mm)",
                                      "160(mm)"  };


const STR *const StrM7A_52E[]  = {    "Cyl Dia     = Custom",
                                      "Zyl. Dur.    = Spez.",
                                      "Dia Cil     = Person",
                                      "Dia cil     = Person",
                                      "Dia Cyl       = Spec"  };

const STR *const StrM7A_52F[]  =   {  "Custom",
                                      "Einst.",
                                      "Person",
                                      "Person",
                                      "Spec"  };

const STR *const StrM7A_52G[]  = {    "Cyl Dia(in)    = 1.5",
                                      "Zyl. Dur.(in)  = 1.5",
                                      "Dia Cil(in)    = 1.5",
                                      "Dia cil(in)    = 1.5",
                                      "Dia Cyl(in)    = 1.5"  };

const STR *const StrM7A_52H[]  = {    "1.50in",
                                      "1.50in",
                                      "1.50in",
                                      "1.50in",
                                      "1.50in"  };

const STR *const StrM7A_52I[]  = {    "Cyl Dia(in)    = 2.0",
                                      "Zyl. Dur.(in)  = 2.0",
                                      "Dia Cil(in)    = 2.0",
                                      "Dia cil(in)    = 2.0",
                                      "Dia Cyl(in)    = 2.0"  };

const STR *const StrM7A_52J[]  = {    "2.00in",
                                      "2.00in",
                                      "2.00in",
                                      "2.00in",
                                      "2.00in"  };

const STR *const StrM7A_52K[]  = {    "Cyl Dia(in)    = 2.5",
                                      "Zyl. Dur.(in)  = 2.5",
                                      "Dia Cil(in)    = 2.5",
                                      "Dia cil(in)    = 2.5",
                                      "Dia Cyl(in)    = 2.5"  };

const STR *const StrM7A_52L[]  =   {  "2.50in",
                                      "2.50in",
                                      "2.50in",
                                      "2.50in",
                                      "2.50in"  };

const STR *const StrM7A_52M[]  = {    "Cyl Dia(in)    = 3.0",
                                      "Zyl. Dur.(in)  = 3.0",
                                      "Dia Cil(in)    = 3.0",
                                      "Dia cil(in)    = 3.0",
                                      "Dia Cyl(in)    = 3.0"  };

const STR *const StrM7A_52N[]  =   {  "3.00in",
                                      "3.00in",
                                      "3.00in",
                                      "3.00in",
                                      "3.00in"  };

const STR *const StrM7A_52O[]  = {    "Cyl Dia(in)   = 3.25",
                                      "Zyl. Dur.(in) = 3.25",
                                      "Dia Cil(in)   = 3.25",
                                      "Dia cil(in)   = 3.25",
                                      "Dia Cyl(in)   = 3.25"  };

const STR *const StrM7A_52P[]  =   {  "3.25in",
                                      "3.25in",
                                      "3.25in",
                                      "3.25in",
                                      "3.25in"  };

const STR *const StrM7A_52Q[]  = {    "Cyl Dia(mm)     = 40",
                                      "Zyl. Dur.(mm)   = 40",
                                      "Dia Cil(mm)     = 40",
                                      "Dia cil(mm)     = 40",
                                      "Dia Cyl(mm)     = 40"  };

const STR *const StrM7A_52R[]  =   {  "40mm",
                                      "40mm",
                                      "40mm",
                                      "40mm",
                                      "40mm"  };

const STR *const StrM7A_52S[]  = {    "Cyl Dia(mm)     = 50",
                                      "Zyl. Dur.(mm)   = 50",
                                      "Dia Cil(mm)     = 50",
                                      "Dia cil(mm)     = 50",
                                      "Dia Cyl(mm)     = 50"  };

const STR *const StrM7A_52T[]  =   {  "50mm",
                                      "50mm",
                                      "50mm",
                                      "50mm",
                                      "50mm"  };

const STR *const StrM7A_52U[]  = {    "Cyl Dia(mm)     = 63",
                                      "Zyl. Dur.(mm)   = 63",
                                      "Dia Cil(mm)     = 63",
                                      "Dia cil(mm)     = 63",
                                      "Dia Cyl(mm)     = 63"  };

const STR *const StrM7A_52V[]  =   {  "63mm",
                                      "63mm",
                                      "63mm",
                                      "63mm",
                                      "63mm"  };

const STR *const StrM7A_52W[]  = {    "Cyl Dia(mm)     = 80",
                                      "Zyl. Dur.(mm)   = 80",
                                      "Dia Cil(mm)     = 80",
                                      "Dia cil(mm)     = 80",
                                      "Dia Cyl(mm)     = 80"  };

const STR *const StrM7A_52X[]  = {    "80mm",
                                      "80mm",
                                      "80mm",
                                      "80mm",
                                      "80mm"  };

const STR *const StrM7A_52Y[]  = {    "Cyl Dia(in)    = 4.0",
                                      "Zyl Dur(in)    = 4.0",
                                      "Dia Cil(in)    = 4.0",
                                      "Dia cil(in)    = 4.0",
                                      "Dia Cyl(in)    = 4.0"  };

const STR *const StrM7A_52Z[]  =   {  "4.00in",
                                      "4.00in",
                                      "4.00in",
                                      "4.00in",
                                      "4.00in"  };

const STR *const StrM7A_53[]   = {    "CYL STROKE",
                                      "ZYL HUB",
                                      "CARRERA CI",
                                      "CORSA CIL",
                                      "COURSE CYL"  };


const STR *const StrM7A_53A[]  = {    "Cyl Stroke  = Custom",
                                      "Zyl. Hub     = Spez.",
                                      "Carrera Ci  = Person",
                                      "Corsa cil   = Person",
                                      "Course Cyl    = Spec"  };

const STR *const StrM7A_53B[]  =   {  "Custom",
                                      "Einst.",
                                      "Person",
                                      "Person",
                                      "Spec"  };

const STR *const StrM7A_53C[]  = {    "Cyl Stroke(in) = 4.0",
                                      "Zyl. Hub(in)   = 4.0",
                                      "Carrera Ci(in) = 4.0",
                                      "Corsa cil(in)  = 4.0",
                                      "Course Cyl(in) = 4.0"  };

const STR *const StrM7A_53D[]  =  {   "4.00in",
                                      "4.00in",
                                      "4.00in",
                                      "4.00in",
                                      "4.00in"  };

const STR *const StrM7A_53E[]  = {    "Cyl Stroke(in) = 5.0",
                                      "Zyl. Hub(in)   = 5.0",
                                      "Carrera Ci(in) = 5.0",
                                      "Corsa cil(in)  = 5.0",
                                      "Course Cyl(in) = 5.0"  };

const STR *const StrM7A_53F[]  =   {  "5.00in",
                                      "5.00in",
                                      "5.00in",
                                      "5.00in",
                                      "5.00in"  };

const STR *const StrM7A_53G[]  = {    "Cyl Stroke(in) = 6.0",
                                      "Zyl. Hub(in)   = 6.0",
                                      "Carrera Ci(in) = 6.0",
                                      "Corsa cil(in)  = 6.0",
                                      "Course Cyl(in) = 6.0"  };

const STR *const StrM7A_53H[]  =   {  "6.00in",
                                      "6.00in",
                                      "6.00in",
                                      "6.00in",
                                      "6.00in"  };

const STR *const StrM7A_53I[]  = {    "Cyl Stroke(in) = 7.0",
                                      "Zyl. Hub(in)   = 7.0",
                                      "Carrera Ci(in) = 7.0",
                                      "Corsa cil(in)  = 7.0",
                                      "Course Cyl(in) = 7.0"  };

const STR *const StrM7A_53J[]  =   {  "7.00in",
                                      "7.00in",
                                      "7.00in",
                                      "7.00in",
                                      "7.00in"  };

const STR *const StrM7A_53K[]  = {    "Cyl Stroke(in) = 8.0",
                                      "Zyl. Hub(in)   = 8.0",
                                      "Carrera Ci(in) = 8.0",
                                      "Corsa cil(in)  = 8.0",
                                      "Course Cyl(in) = 8.0"  };

const STR *const StrM7A_53L[]  =   {  "8.00in",
                                      "8.00in",
                                      "8.00in",
                                      "8.00in",
                                      "8.00in"  };

const STR *const StrM7A_53M[]  = {    "Cyl Stroke(mm)  = 80",
                                      "Zyl. Hub(mm)    = 80",
                                      "Carrera Ci(mm)  = 80",
                                      "Corsa cil(mm)   = 80",
                                      "Course Cyl(mm)  = 80"  };

const STR *const StrM7A_53N[]  =   {  "80mm",
                                      "80mm",
                                      "80mm",
                                      "80mm",
                                      "80mm"  };

const STR *const StrM7A_53O[]  = {    "Cyl Stroke(mm) = 100",
                                      "Zyl. Hub(mm)   = 100",
                                      "Carrera Ci(mm) = 100",
                                      "Corsa cil(mm)  = 100",
                                      "Course Cyl(mm) = 100"  };

const STR *const StrM7A_53P[]  =   {  "100mm",
                                      "100mm",
                                      "100mm",
                                      "100mm",
                                      "100mm"  };

const STR *const StrM7A_53Q[]  = {    "Cyl Stroke(mm) = 125",
                                      "Zyl. Hub(mm)   = 125",
                                      "Carrera Ci(mm) = 125",
                                      "Corsa cil(mm)  = 125",
                                      "Course Cyl(mm) = 125"  };

const STR *const StrM7A_53R[]  =   {  "125mm",
                                      "125mm",
                                      "125mm",
                                      "125mm",
                                      "125mm"  };

const STR *const StrM7A_53S[]  = {    "Cyl Stroke(mm) = 160",
                                      "Zyl. Hub(mm)   = 160",
                                      "Carrera Ci(mm) = 160",
                                      "Corsa cil(mm)  = 160",
                                      "Course Cyl(mm) = 160"  };

const STR *const StrM7A_53T[]  =   {  "160mm",
                                      "160mm",
                                      "160mm",
                                      "160mm",
                                      "160mm"  };



const STR *const StrM7A_54[]  = {     "BEEPERS",
                                      "SIGNAL",
                                      "BUSCA",
                                      "SEGNAL",
                                      "BEEPERS"  };

const STR *const StrM7A_55[]  = {     "Alarm Beeper",
                                      "Alarmsignal",
                                      "Alarma Acust",
                                      "Segnal alarm",
                                      "Biper Alarme"  };

const STR *const StrM7A_56[]  = {     "Error Beeper",
                                      "Fehlersignal",
                                      "S Acus Error",
                                      "Segnal error",
                                      "Biper Erreur"  };

const STR *const StrM7A_57[]  = {     "Trigger Beeper",
                                      "Triggersignal",
                                      "S Acus Disparo",
                                      "Segnal Trigger",
                                      "Biper Declenc"  };

const STR *const StrM7A_58[]  = {     "SCALES",
                                      "SKALA",
                                      "ESCALA",
                                      "SCALE",
                                      "ECHEL."  };

const STR *const StrM7A_59[]  = {     "Weld Scale",
                                      "Skalierung",
                                      "Escala Sold",
                                      "Scala sald",
                                      "Ech. Soud"  };

const STR *const StrM7A_59A[] = {     "Weld Scale>       1X",
                                      "Skalierung>       1X",
                                      "Escala Sold>      1X",
                                      "Scala sald>       1X",
                                      "Ech. Soud>        1X"  };

const STR *const StrM7A_59B[] = {     "Weld Scale>       2X",
                                      "Skalierung>       2X",
                                      "Escala Sold>      2X",
                                      "Scala sald>       2X",
                                      "Ech. Soud>        2X"  };

const STR *const StrM7A_59C[] = {     "Weld Scale>       3X",
                                      "Skalierung>       3X",
                                      "Escala Sold>      3X",
                                      "Scala sald>       3X",
                                      "Ech. Soud>        3X"  };

const STR *const StrM7A_60[]  = {     "Test Scale",
                                      "Testskala",
                                      "Escala Test",
                                      "Scala test",
                                      "Ech. Test"  };

const STR *const StrM7A_60A[] = {     "Test Scale>       1X",
                                      "Testskala>        1X",
                                      "Escala Test>      1X",
                                      "Scala test>       1X",
                                      "Ech. Test>        1X"  };

const STR *const StrM7A_60B[] = {     "Test Scale>       2X",
                                      "Testskala>        2X",
                                      "Escala Test>      2X",
                                      "Scala test>       2X",
                                      "Ech. Test>        2X"  };

const STR *const StrM7A_60C[] = {     "Test Scale>       3X",
                                      "Testskala>        3X",
                                      "Escala Test>      3X",
                                      "Scala test>       3X",
                                      "Ech. Test>        3X"  };

const STR *const StrM7A_61[] = {     "RS232>     Compuweld",
                                     "RS232>     Compuweld",
                                     "RS232>     Compuweld",
                                     "RS232>     Compuweld",
                                     "RS232>     Compuweld"  };

const STR *const StrM7A_62[] = {     "RS232>      Terminal",
                                     "RS232>      Terminal",
                                     "RS232>      Terminal",
                                     "RS232>      Terminal",
                                     "RS232>      Terminal"  };

const STR *const StrM7A_63[] = {     "RS232> ASCII (comma)",
                                     "RS232> ASCII (Komma)",
                                     "RS232> ASCII (Virg) ",
                                     "RS232> ASCII (Virg) ",
                                     "RS232> ASCII (Virg) "  };

const STR *const StrM7A_64[] = {     "RS232>   ASCII (tab)",
                                     "RS232>   ASCII (tab)",
                                     "RS232>   ASCII (tab)",
                                     "RS232>   ASCII (tab)",
                                     "RS232>   ASCII (tab)"  };

const STR *const StrM7A_65[] = {     "RS232> ASCII (space)",
                                     "RS232> ASCII(Strich)",
                                     "RS232> ASCII (Esp)  ",
                                     "RS232> ASCII (Esp)  ",
                                     "RS232> ASCII(Espace)"  };

const STR *const StrM7A_66[] = {     "RS232>      Disabled",
                                     "RS232>   Unbrauchbar",
                                     "RS232>   Incapacitar",
                                     "RS232>    Incapacita",
                                     "RS232>    Incapacite"  };

const STR *const StrM7A_67[] = {     "Disabled",
                                     "Unbrauchbar",
                                     "Incapacitar",
                                     "Incapacita",
                                     "Incapacite"  }; 

const STR *const StrM7A_68[] = {     "ASCII (comma)",   /* Menu & Printout */
                                     "ASCII (Komma)",
                                     "ASCII (Virg) ",
                                     "ASCII (Virg) ",
                                     "ASCII (Virg) "  }; 

const STR *const StrM7A_69[] = {     "ASCII (tab)", /* Menu & Printout */
                                     "ASCII (tab)",
                                     "ASCII (tab)",
                                     "ASCII (tab)",
                                     "ASCII (tab)"  };

const STR *const StrM7A_70[] = {     "ASCII (space)",   /* Menu & Printout */
                                     "ASCII(Strich)",
                                     "ASCII (Esp)  ",
                                     "ASCII (Esp)  ",
                                     "ASCII(Espace)"  };

const STR *const StrM7A_71[] = {     "Compuweld(tm)",/* Menu & Printout */
                                     "Compuweld(tm)",
                                     "Compuweld(tm)",
                                     "Compuweld(tm)",
                                     "Compuweld(tm)"  };

const STR *const StrM7A_72[] = {     "Terminal",    /* Menu & Printout */
                                     "Terminal",
                                     "Terminal",
                                     "Terminal",
                                     "Terminal"  };


const STR *const StrM8_0[]  = {       "Print Menu",
                                      "Druckmenu", 
                                      "Impr. Menu",
                                      "Menu stamp",
                                      "Impr Menu"  };

const STR *const StrM8_1[]  = {       "Printer",
                                      "Drucker",
                                      "Impresora",
                                      "Stampnt",
                                      "Imprmte"  };

const STR *const StrM8_2[]  = {       "Choose Printout>",
                                      "Ausdruck waehl>", 
                                      "Selec impresion>", 
                                      "Selziona stampa>", 
                                      "Choisir Imprim.>"  };

const STR *const StrM8_2A[] = {       "PRINTOUT",
                                      "AUSDRUCK", 
                                      "IMPRESION", 
                                      "STAMPA", 
                                      "IMPRIMER"   };

const STR *const StrM8_2B[] = {       "Printing",
                                      "Drucken",
                                      "Imprmndo",
                                      "Stampa",
                                      "Impressn"  };

const STR *const StrM8_21C[]= {       "Print Now",
                                      "Jetzt Druck", 
                                      "Impr. Ahor",
                                      "Stamp ora",
                                      "Imp Matnt"  };

const STR *const StrM8_22C[]= {       "Print Sample",
                                      "Drucke Beispiel", 
                                      "Impr muestra", 
                                      "Stamp campio", 
                                      "Imprim Echnt"  };

const STR *const StrM8_23C[]= {       "Print On Alarm",
                                      "Drucke bei Alarm", 
                                      "Impr. Alarmas",
                                      "Stamp su allar",
                                      "Impr sur Alarm"  };

const STR *const StrM8_21A[]= {       "Setup>",
                                      "Einr.>",
                                      "Config>",
                                      "Setup>",
                                      "Confg>"  };

const STR *const StrM8_2C[] = {       "Weld History>",
                                      "Datenbank>",
                                      "Hist. Sold>",
                                      "Stor saldatr>",
                                      "Histor. Soud>"  };

const STR *const StrM8_2D[] = {       "Weld Data>",
                                      "Schw.Daten>",
                                      "Datos Sold>",
                                      "Dati sald>",
                                      "Donn Soud>"  };

const STR *const StrM8_2E[] = {       "Power Graph>",
                                      "Leist. Grafik>",
                                      "Graf. Poten>",
                                      "Graf. potenz>",
                                      "Graph Puiss>"  };

const STR *const StrM8_2F[] = {       "Amplitude Graph>",
                                      "Amp. Grafik>",
                                      "Graf. Amplitud>",
                                      "Graf. ampiezza>",
                                      "Graph Amplitude>"  };

const STR *const StrM8_2G[] = {       "Frequency Graph>",
                                      "Frequenzgrafik>",
                                      "Graf Frecuencia>",
                                      "Graf. frequenza>",
                                      "Graph Frequence>"  };

const STR *const StrM8_2H[] = {       "Col Distance Graph>",
                                      "Grafik Weg rel>",
                                      "Graf. Dist Col>",
                                      "Graf. Distanza Col>",
                                      "Graph Distance Rel>"  };

const STR *const StrM8_2I[] = {       "Velocity Graph>",
                                      "Geschw. Grafik>",
                                      "Graf Velocidad>",
                                      "Graf. velocita>",
                                      "Graph Vitesse>"  };

const STR *const StrM8_2J[] = {       "Force Graph>",
                                      "Kraft Grafik>",
                                      "Graf Fuerza>",
                                      "Graf. forza>",
                                      "Graph Force>"  };

const STR *const StrM8_21AA[]= {      "Setup       ",
                                      "Einr.       ",
                                      "Config      ",
                                      "Setup       ",
                                      "Confg       "  };

const STR *const StrM8_2CC[] = {      "Weld History",
                                      "Datenbank",
                                      "Hist. Sold",
                                      "Stori saldat",
                                      "Histor. Soud"  };

const STR *const StrM8_2DD[] = {      "Weld Data",
                                      "Schw.Daten",
                                      "Datos Sold",
                                      "Dati sald",
                                      "Donn Soud"  };

const STR *const StrM8_2EE[] = {      "Power Graph",
                                      "Leist. Grafik",
                                      "Graf. Poten",
                                      "Graf. potenz",
                                      "Graph Puiss"  };

const STR *const StrM8_2FF[] = {      "Amp Graph",
                                      "Amp.Grafik",
                                      "Graf. Amp.",
                                      "Graf. Amp.",
                                      "Graph Amp."  };

const STR *const StrM8_2GG[] = {      "Freq Graph",
                                      "Freq. Grafik",
                                      "Graf. Frec.",
                                      "Graf. Freq.",
                                      "Graph Freq"  };

const STR *const StrM8_2HH[] = {      "Col Graph",
                                      "Weg rel Grafik",
                                      "Graf. Col",
                                      "Graf. Col",
                                      "Graph Rel"  };

const STR *const StrM8_2II[] = {      "Vel Graph",
                                      "Geschw. Grafik",
                                      "Graf. Vel.",
                                      "Graf. vel",
                                      "Graph Vit"  };

const STR *const StrM8_2JJ[] = {      "Force Graph",
                                      "Kraft Grafik",
                                      "Graf. Fuerza",
                                      "Graf. forza",
                                      "Graph Force"  };

const STR *const StrM8_31A[]= {       "Abort Printing",
                                      "Drucken abbr.",
                                      "Cancela Impres",
                                      "Annulla stampa",
                                      "Annuler Impr."  };

const STR *const StrM8_4[]  = {       "Setup Printer>",
                                      "Drucker einr.>",
                                      "Config Impresora>",
                                      "Setup stampnt>",
                                      "Config Imprte>"  };

const STR *const StrM8_4A[] = {       "PRINTER",
                                      "DRUCKER",
                                      "IMPRESORA",
                                      "STAMPNT",
                                      "IMPRMTE"  };

const STR *const StrM8_41A[]= {       "Printer>  OKI520/320",
                                      "Drucker>  OKI520/320",
                                      "Impresr>  OKI520/320",
                                      "Stampnt>  OKI520/320",
                                      "Imprmte>  OKI520/320"  };

const STR *const StrM8_41B[]= {       "Printer>Epson(Esc/P)",
                                      "Drucker>Epson(Esc/P)",
                                      "Impresr>Epson(Esc/P)",
                                      "Stampnt>Epson(Esc/P)",
                                      "Imprmte>Epson(Esc/P)"  };

const STR *const StrM8_41C[]= {       "Printer>     HP(PCL)",
                                      "Drucker>     HP(PCL)",
                                      "Impresr>     HP(PCL)",
                                      "Stampnt>     HP(PCL)",
                                      "Imprmte>     HP(PCL)"  };


const STR *const StrM8_41D[]= {       "OKI520/320",
                                      "OKI520/320",
                                      "OKI520/320",
                                      "OKI520/320",
                                      "OKI520/320"  };
      
const STR *const StrM8_41E[]= {       "Epson(Esc/P)",
                                      "Epson(Esc/P)",
                                      "Epson(Esc/P)",
                                      "Epson(Esc/P)",
                                      "Epson(Esc/P)"  };

const STR *const StrM8_41F[]= {       "HP(PCL)",
                                      "HP(PCL)",
                                      "HP(PCL)",
                                      "HP(PCL)",
                                      "HP(PCL)"  };

const STR *const StrM8_41G[]= {       "Refer to Manual",
                                      "Siehe Handbuch", 
                                      "Vease el Manual", 
                                      "Vedere manuale", 
                                      "Cf. manuel"  };

const STR *const StrM8_42B[]= {       "Welds Per Page",
                                      "Schw. pro Seite",
                                      "Solds por pag",
                                      "Sald. per pag.",
                                      "Soud par Page"  };

const STR *const StrM8_42C[]= {       "Page Length",
                                      "Seitnlaenge", 
                                      "Long pagina", 
                                      "Lung pagina", 
                                      "Long. page"  };

const STR *const StrM8_43[] = {       "X Scale(&)",
                                      "X-Skala(&)",
                                      "Escal X(&)",
                                      "Scala X(&)",
                                      "Ech. X(&)"  };

const STR *const StrM8_44[] = {       "Auto Scale",
                                      "Auto Skala",
                                      "Autoescala",
                                      "Scala Auto",
                                      "Ech. Auto"  };

const STR *const StrM8_44A[]= {       "X Scale(s)     = ***",
                                      "X-Skala(s)     = ***",
                                      "Escala X(s)    = ***",
                                      "Scala X(s)     = ***",
                                      "Ech. X(s)      = ***"  };

const STR *const StrM8_45[] = {       "Page Size",
                                      "Format",
                                      "T. Pagina",
                                      "Dimns pag",
                                      "Format Pg"  };

const STR *const StrM8_45A[]= {       "11\" Page Size",
                                      "11\" Format",
                                      "11\" T. Pagina",
                                      "11\" Dimns pag",
                                      "11\" Format Pg"  };

const STR *const StrM8_45B[]= {       "14\" Page Size",
                                      "14\" Format",
                                      "14\" T. Pagina",
                                      "14\" Dimns pag",
                                      "14\" Format Pg"  };

const STR *const StrM8_45C[]= {       "A4 Page Size",
                                      "A4 Format",
                                      "A4 T. Pagina",
                                      "A4 Dimns pag",
                                      "A4 Format Pg"  };

const STR *const StrM8_45D[]= {       "Page Size>       11\"",
                                      "Format>          11\"",
                                      "T. Pagina>       11\"",
                                      "Dimns pag>       11\"",
                                      "Format Pg>       11\""  };

const STR *const StrM8_45E[]= {       "Page Size>       14\"",
                                      "Format>          14\"",
                                      "T. Pagina>       14\"",
                                      "Dimns pag>       14\"",
                                      "Format Pg>       14\""  };

const STR *const StrM8_45F[]= {       "Page Size>        A4",
                                      "Format>           A4",
                                      "T. Pagina>        A4",
                                      "Dimns pag>        A4",
                                      "Format Pg>        A4"  };

const STR *const StrM8_46A[]= {       "Realign top of page ",
                                      "Papier ausricht. ", 
                                      "Realinear cab pag.  ", 
                                      "Riallinear bord sup ", 
                                      "Realign. Haut page " };


const STR *const StrM8_47A[]= {       "Abs Distance Graph> ",
                                      "Weg abs Grafik> ",
                                      "Grafico Dist Abs> ",
                                      "Graf distanza ass.> ",
                                      "Graph Distance Abs> "  };

const STR *const StrM8_47B[]= {       "Abs Graph",
                                      "Abs. Grafik",
                                      "Graf. Abs",
                                      "Graf ass.",
                                      "Graph Abs"  };


const STR *const StrBranson[] =    {  "Branson             ",
                                      "Branson             ", 
                                      "Branson             ", 
                                      "Branson             ", 
                                      "Branson             "  };


const STR *const StrBranFreq1[] =  {  "Frequency>    15 KHz",
                                      "Frequenz>     15 KHz",
                                      "Frecuencia>   15 KHz",
                                      "Frequenza>    15 KHz",
                                      "Frequence>    15 KHz"  };

const STR *const StrBranFreq2[] =  {  "Frequency>    20 KHz",
                                      "Frequenz>     20 KHz",
                                      "Frecuencia>   20 KHz",
                                      "Frequenza>    20 KHz",
                                      "Frequence>    20 KHz"  };

const STR *const StrBranFreq3[] =  {  "Frequency>    30 KHz",
                                      "Frequenz>     30 KHz",
                                      "Frecuencia>   30 KHz",
                                      "Frequenza>    30 KHz",
                                      "Frequence>    30 KHz"  };

const STR *const StrBranFreq4[] =  {  "Frequency>    40 KHz",
                                      "Frequenz>     40 KHz",
                                      "Frecuencia>   40 KHz",
                                      "Frequenza>    40 KHz",
                                      "Frequence>    40 KHz"  };
                                      
const STR *const StrBranFreq5[] =  {  "Frequency>    60 KHz",
                                      "Frequenz>     60 KHz",
                                      "Frecuencia>   60 KHz",
                                      "Frequenza>    60 KHz",
                                      "Frequence>    60 KHz"  };

const STR *const StrBranWatts0[] = {  "Wattage>        200W",
                                      "Watt>           200W",
                                      "Vataje>         200W",
                                      "Watagio>        200W",
                                      "Puissce>        200W"  };

const STR *const StrBranWatts1[] = {  "Wattage>        400W",
                                      "Watt>           400W",
                                      "Vataje>         400W",
                                      "Watagio>        400W",
                                      "Puissce>        400W"  };

const STR *const StrBranWatts2[] = {  "Wattage>        800W",
                                      "Watt>           800W",
                                      "Vataje>         800W",
                                      "Watagio>        800W",
                                      "Puissce>        800W"  };

const STR *const StrBranWatts3[] = {  "Wattage>       1100W",
                                      "Watt>          1100W",
                                      "Vataje>        1100W",
                                      "Watagio>       1100W",
                                      "Puissce>       1100W"  };

const STR *const StrBranWatts4[] = {  "Wattage>       1500W",
                                      "Watt>          1500W",
                                      "Vataje>        1500W",
                                      "Watagio>       1500W",
                                      "Puissce>       1500W"  };

const STR *const StrBranWatts5[] = {  "Wattage>       2200W",
                                      "Watt>          2200W",
                                      "Vataje>        2200W",
                                      "Watagio>       2200W",
                                      "Puissce>       2200W"  };

const STR *const StrBranWatts6[] = {  "Wattage>       6000W",
                                      "Watt>          6000W",
                                      "Vataje>        6000W",
                                      "Watagio>       6000W",
                                      "Puissce>       6000W"  };

const STR *const StrBranWatts7[] = {  "Wattage>       3300W",
                                      "Watt>          3300W",
                                      "Vataje>        3300W",
                                      "Watagio>       3300W",
                                      "Puissce>       3300W"  };

const STR *const StrBranWatts8[] = {  "Wattage>       4000W",
                                      "Watt>          4000W",
                                      "Vataje>        4000W",
                                      "Watagio>       4000W",
                                      "Puissce>       4000W"  };

const STR *const StrBranCalib[]  = {  "Update Cal. Defaults",
                                      "Akt. Kal. Wrkseinst.",
                                      "Actual Cal por dfcto",
                                      "Aggiorna default cal",
                                      "Actual Val Def Calib"  };

const STR *const StrFreqChoice[] = {  "FREQUENCY           ",
                                      "FREQUENZ            ",
                                      "FRECUENCIA          ",
                                      "FREQUENZA           ",
                                      "FREQUENCE           "  };

const STR *const StrWattChoice[] = {  "WATTAGE             ",
                                      "WATT                ",
                                      "VATAJE              ",
                                      "WATTAGGIO           ",
                                      "PUISSCE             "  };

const STR *const StrSetPSNum[] =   {  "ENTER P/S SERIAL #  ",
                                      "GEN SERIENNR EING   ", 
                                      "INTRO No SERIE F/A  ",
                                      "INSERI P/S SERIALE N",
                                      "ENTRER # SERIE GEN  "  }; 

const STR *const StrSetActNum[] =  {  "ENTER ACT SERIAL #  ",
                                      "VE SERIENNR EINGEB  ",
                                      "INTRO No SERIE ACT  ",
                                      "INSERI ATT SERIALE N",
                                      "ENTRER # SERIE ACT  "  };

const STR *const StrBlankEntry[] = {  "_               Done",
                                      "_              Getan",
                                      "_               Tmdo",
                                      "_               Esgt",
                                      "_               Term"  };

const STR *const StrActSettings[] = { "Actuator Settings> ",
                                      "VE Einstellungen> ", 
                                      "Ajustes actuador> ", 
                                      "Impostazioni att> ", 
                                      "Reglages actuator> "  }; 

const STR *const StrTitleActset[] = { "ACT SETTINGS",
                                      "VE EINSTELL.",
                                      "AJUSTES ACT", 
                                      "IMPOSTAZ ATT",
                                      "REGLAGES ACT"  }; 

const STR *const StrDigitalPS[] = {   "Digital P/Supply>",
                                      "Digital Gen.>",
                                      "F/Alim Digital>",
                                      "P/S digitale>",
                                      "Generat. Digital>"  };

const STR *const StrDigiPStitle[] = { "DIGITAL P/S",
                                      "DIGITAL GEN.",
                                      "F/A Digital",
                                      "P/S digital",
                                      "Gn. Digital"  };

const STR *const StrCurDupsSetup[] ={ "Current DUPS Setup>",
                                      "Aktuelle DUPS Einr.>",
                                      "Config Crrnte FAUD>",
                                      "Setup DUPS corrent>",
                                      "Config.actu. GUD>"  };

const STR *const StrScanSettings[] ={ "Scan Settings>",
                                      "Scan Einstell.>",
                                      "Ajustes Scan>",
                                      "Impost scans>",
                                      "Scan Reglages>"  };

const STR *const StrDupsPreset[] = {  "DUPS Preset Status>",
                                      "DUPS Param. Status>", 
                                      "Estado presel FADU>", 
                                      "Stato Preset DUPS>", 
                                      "Etat Preset GUD>"  }; 

const STR *const StrPrtDupsSetup[] ={ "Print DUPS Setup",
                                      "Drucke DUPS Einr.",
                                      "Impr Config DUPS",
                                      "Stamp inst DUPS",
                                      "Impr Config GUD"  };

const STR *const StrDupsStptitle[] ={ "DUPS SETUP",
                                      "DUPS EINR.",
                                      "Conf FAUD",
                                      "Setup DUPS",
                                      "Conf. GUD"  };

const STR *const StrSeekFunctions[]={ "Seek Functions>",
                                      "Suchfunktion>",
                                      "Busc Funciones>",
                                      "Funzioni Seek>",
                                      "Fonct. de Rech>"  };

const STR *const StrWeldFunctions[]={ "Weld Functions>",
                                      "Schw.Funktionen>",
                                      "Funciones Sold>",
                                      "Funzioni sald.>",
                                      "Fonctions Soud>"  };

const STR *const StrDipSetting[] = {  "Dip Setting",
                                      "DIP Einstel.",
                                      "Ajustar Dip",
                                      "Impost. DIP",
                                      "Reglage Dip"  };

const STR *const StrSwDipSetting[] ={ "SW Dip Setting",
                                      "DIP Einstellung",
                                      "Ajust Conm Dip",
                                      "Impost int Dip",
                                      "Regl Cont. Dip"  };

const STR *const Str_hw[] = {         "H/W",
                                      "H/W", 
                                      "H/W", 
                                      "H/W", 
                                      "H/W"  }; 

const STR *const Str_sw[] = {         "S/W",
                                      "S/W",
                                      "SFT",
                                      "INT",
                                      "Log"  };

const STR *const StrSeekFntitle[] = { "SEEK FUNCTIONS",
                                      "Suchfunktion",
                                      "BUSC FUNCIONES",
                                      "FUNZIONI SEEK",
                                      "FONCT. DE RECH"  };
  
const STR *const StrAmplitude[] = {   "Amplitude(%)",
                                      "Amplitude(%)",
                                      "Amplitud(%)",
                                      "Ampiezza(%)",
                                      "Amplitude(%)"  };

const STR *const StrFreqHigh[] = {    "Freq High(Hz)",
                                      "Freq.High(Hz)",
                                      "Frec Alta(Hz)",
                                      "Alta freq(Hz)",
                                      "Freq Hte(Hz)"  };

const STR *const StrDUPSFreqAct[] = { "DUPS Freq(Hz)",
                                      "DUPS Freq(Hz)",
                                      "DUPS Frec(Hz)",
                                      "DUPS Alta(Hz)",
                                      "GUD Freq(Hz)"  };

const STR *const StrFreqLow[] = {     "Freq Low(Hz)",
                                      "Freq.Low(Hz)",
                                      "Frec Baj(Hz)",
                                      "Bass frq(Hz)",
                                      "Frq Bass(Hz)"  };

const STR *const StrPhaseLoop[] = {   "Phase Loop",
                                      "Phase Schl.",
                                      "Bucle Fase",
                                      "Loop fase",
                                      "Bcle Phase"  };

const STR *const StrAmpLoopC1[] = {   "Amp Loop C1",
                                      "Amp.Schl.C1",
                                      "Lazo Amp C1",
                                      "Amp Loop C1",
                                      "Bcle Amp C1"  };

const STR *const StrAmpLoopC2[] = {   "Amp Loop C2",
                                      "Amp.Schl.C2",
                                      "Lazo Amp C2",
                                      "Amp Loop C2",
                                      "Bcle Amp C2"  };

const STR *const StrWeldFntitle[] = { "WELD FUNCTIONS",
                                      "SCHW.FUNK.",
                                      "FUNCIONE SOLD>",
                                      "FUNZIONI SALD>",
                                      "FONCTION SOUD>"  };

const STR *const StrWeldAmplitude[]={ "Amplitude(%)",
                                      "Amplitude(%)",
                                      "Amplitud(%)",
                                      "Ampiezza(%)",
                                      "Amplitude(%)"  };

const STR *const StrRampTime[] = {    "Ramp Time(s)",
                                      "Ramp.Zeit(s)",
                                      "Tiem Rmpa(s)",
                                      "Tmpo Rmpa(s)",
                                      "Tps Monte(s)"  };

const STR *const StrWPhaseLoop[] = {  "Phase Loop",
                                      "Phase Schl.",
                                      "Bucle Fase",
                                      "Loop fase",
                                      "Bcle Phase"  };

const STR *const StrPhaseLoopCF[] = { "Phase Loop CF",
                                      "Phase Schl.CF",
                                      "Bucle Fase CF",
                                      "Loop fase CF",
                                      "Bcle Phase CF"  };

const STR *const StrWAmpLoopC1[] = {  "Amp Loop C1",
                                      "Amp.Schl.C1",
                                      "Lazo Amp C1",
                                      "Amp Loop C1",
                                      "Bcle Amp C1"  };

const STR *const StrWAmpLoopC2[] = {  "Amp Loop C2",
                                      "Amp.Schl.C2",
                                      "Lazo Amp C2",
                                      "Amp Loop C2",
                                      "Bcle Amp C2"  };

const STR *const StrWeldHigh[] = {    "Weld High",
                                      "Schw High",
                                      "Sold Alta",
                                      "Sald alto",
                                      "Soud Haut"  };

const STR *const StrWeldLow[] = {     "Weld Low",
                                      "Schw. Low",
                                      "Sold Bja",
                                      "Sald bas",
                                      "Soud Bas"  };

const STR *const StrPhaseLimit[] = {  "Phase Limit",
                                      "Phase Grnz.",
                                      "Limite Fase",
                                      "Limite fase",
                                      "Lim. Phase"  };

const STR *const StrDUPSPhaseAct[] = {"DUPS Phase",
                                      "DUPS Phase",
                                      "DUPS Fase",
                                      "DUPS Fase",
                                      "GUD Phase"  };

const STR *const StrDUPSTemp[]   =   {"Temp Act(F)",
                                      "Temp Act(F)",
                                      "Temp Act(F)",
                                      "Temp Act(F)",
                                      "Temp Act(F)" };

const STR *const StrPhaseLimits[] = { "Phase Lim(s)",
                                      "Phase Grnz.(s)",
                                      "Lim Fase(s)",
                                      "Lim fase(s)",
                                      "Lim. Phase(s)"  };

const STR *const StrScanSetgtitle[]={ "SCAN SETTINGS",
                                      "SCAN EINSTELL.",
                                      "AJUSTES SCAN>",
                                      "IMPOST SCANS>",
                                      "REGL. SCAN>"  };

const STR *const StrSAmplitude[] = {  "Amplitude(%)",
                                      "Amplitude(%)",
                                      "Amplitud(%)",
                                      "Ampiezza(%)",
                                      "Amplitude(%)"  };

const STR *const StrCurrent[] = {     "Current",
                                      "Aktuell",
                                      "Corrnte",
                                      "Corrent",
                                      "Actuel."  };

const STR *const StrDUPSCurrent[] = { "DUPS Current",
                                      "DUPS Aktuell",
                                      "DUPS Corrnte",
                                      "DUPS Corrent",
                                      "GUD Actuel."  };

const STR *const StrFreqStart[] = {   "Freq Start(Hz)",
                                      "Freq.Start(Hz)",
                                      "Inic Frec(Hz)",
                                      "Avvio freq(Hz)",
                                      "Freq Deb.(Hz)"  };

const STR *const StrFreqEnd[] = {     "Freq End(Hz)",
                                      "Freq.Ende(Hz)",
                                      "Fin Frec(Hz)",
                                      "Fine Frq(Hz)",
                                      "Freq Fin(Hz)"  };

const STR *const StrTimeDelay[] = {   "Time Delay(s)",
                                      "Zeitverzoe(s)",
                                      "Retrd Tiem(s)",
                                      "Ritrd tmpo(s)",
                                      "Dur Delai(s)"  };

const STR *const StrResetScanVals[]={ "Reset Scan Values",
                                      "Reset Scan Werte",
                                      "Reset Vlores Scan",
                                      "Reset valori scan",
                                      "RAZ Valeurs Scan"  };

const STR *const StrDupsPrsttitle[]={ "PRESET STATUS",
                                      "PARAM. STATUS",
                                      "ESTADO PRESEL",
                                      "STATO PRESET",
                                      "ETAT PRESETS"  };

const STR *const StrLocked2[] = {     "Preset2>      Locked",
                                      "Parameter2> Gesperrt",
                                      "Presel2>   Bloqueado",
                                      "Preset2>    Bloccato",
                                      "Preset2>      Verrou"  };

const STR *const StrAvail2[] = {      "Preset2>       Avail",
                                      "Parameter2> Verfuegb",
                                      "Presel2>       Dispo",
                                      "Preset2>     Dispon.",
                                      "Preset2>       Dispo"  };

const STR *const StrSaved2[] = {      "Preset2>       Saved",
                                      "Parameter2>  Gespei.",
                                      "Presel2>     Guardar",
                                      "Preset2>     Salvato",
                                      "Preset2>       Enrge"  };

const STR *const StrLocked3[] = {     "Preset3>      Locked",
                                      "Parameter3> Gesperrt",
                                      "Presel3>   Bloqueado",
                                      "Preset3>    Bloccato",
                                      "Preset3>      Verrou"  };

const STR *const StrAvail3[] = {      "Preset3>       Avail",
                                      "Parameter3> Verfuegb",
                                      "Presel3>       Dispo",
                                      "Preset3>     Dispon.",
                                      "Preset3>       Dispo"  };

const STR *const StrSaved3[] = {      "Preset3>       Saved",
                                      "Parameter3>  Gespei.",
                                      "Presel3>     Guardar",
                                      "Preset3>     Salvato",
                                      "Preset3>       Enrge"  };

const STR *const StrLocked4[] = {     "Preset4>      Locked",
                                      "Parameter4> Gesperrt",
                                      "Presel4>   Bloqueado",
                                      "Preset4>    Bloccato",
                                      "Preset4>      Verrou"  };

const STR *const StrAvail4[] = {      "Preset4>       Avail",
                                      "Parameter4> Verfuegb",
                                      "Presel4>       Dispo",
                                      "Preset4>     Dispon.",
                                      "Preset4>       Dispo"  };

const STR *const StrSaved4[] = {      "Preset4>       Saved",
                                      "Parameter4>  Gespei.",
                                      "Presel4>     Guardar",
                                      "Preset4>     Salvato",
                                      "Preset4>       Enrge"  };

const STR *const StrLocked5[] = {     "Preset5>      Locked",
                                      "Parameter5> Gesperrt",
                                      "Presel5>   Bloqueado",
                                      "Preset5>    Bloccato",
                                      "Preset5>      Verrou"  };

const STR *const StrAvail5[] = {      "Preset5>       Avail",
                                      "Parameter5> Verfuegb",
                                      "Presel5>       Dispo",
                                      "Preset5>     Dispon.",
                                      "Preset5>       Dispo"  };

const STR *const StrSaved5[] = {      "Preset5>       Saved",
                                      "Parameter5>  Gespei.",
                                      "Presel5>     Guardar",
                                      "Preset5>     Salvato",
                                      "Preset5>       Enrge"  };

const STR *const StrLocked6[] = {     "Preset6>      Locked",
                                      "Parameter6> Gesperrt",
                                      "Presel6>   Bloqueado",
                                      "Preset6>    Bloccato",
                                      "Preset6>      Verrou"  };

const STR *const StrAvail6[] = {      "Preset6>       Avail",
                                      "Parameter6> Verfuegb",
                                      "Presel6>       Dispo",
                                      "Preset6>     Dispon.",
                                      "Preset6>       Dispo"  };

const STR *const StrSaved6[] = {      "Preset6>       Saved",
                                      "Parameter6>  Gespei.",
                                      "Presel6>     Guardar",
                                      "Preset6>     Salvato",
                                      "Preset6>       Enrge"  };

const STR *const StrLocked7[] = {     "Preset7>      Locked",
                                      "Parameter7> Gesperrt",
                                      "Presel7>   Bloqueado",
                                      "Preset7>    Bloccato",
                                      "Preset7>      Verrou"  };

const STR *const StrAvail7[] = {      "Preset7>       Avail",
                                      "Parameter7> Verfuegb",
                                      "Presel7>       Dispo",
                                      "Preset7>     Dispon.",
                                      "Preset7>       Dispo"  };

const STR *const StrSaved7[] = {      "Preset7>       Saved",
                                      "Parameter7>  Gespei.",
                                      "Presel7>     Guardar",
                                      "Preset7>     Salvato",
                                      "Preset7>       Enrge"  };

const STR *const StrLocked8[] = {     "Preset8>      Locked",
                                      "Parameter8> Gesperrt",
                                      "Presel8>   Bloqueado",
                                      "Preset8>    Bloccato",
                                      "Preset8>      Verrou"  };

const STR *const StrAvail8[] = {      "Preset8>       Avail",
                                      "Parameter8> Verfuegb",
                                      "Presel8>       Dispo",
                                      "Preset8>     Dispon.",
                                      "Preset8>       Dispo"  };

const STR *const StrSaved8[] = {      "Preset8>       Saved",
                                      "Parameter8>  Gespei.",
                                      "Presel8>     Guardar",
                                      "Preset8>     Salvato",
                                      "Preset8>       Enrge"  };

const STR *const StrLocked9[] = {     "Preset9>      Locked",
                                      "Parameter9> Gesperrt",
                                      "Presel9>   Bloqueado",
                                      "Preset9>    Bloccato",
                                      "Preset9>      Verrou"  };

const STR *const StrAvail9[] = {      "Preset9>       Avail",
                                      "Parameter9> Verfuegb",
                                      "Presel9>       Dispo",
                                      "Preset9>     Dispon.",
                                      "Preset9>       Dispo"  };

const STR *const StrSaved9[] = {      "Preset9>       Saved",
                                      "Parameter9>  Gespei.",
                                      "Presel9>     Guardar",
                                      "Preset9>     Salvato",
                                      "Preset9>       Enrge"  };

const STR *const StrLocked10[]= {     "Preset10>     Locked",
                                      "Parameter10>Gesperrt",
                                      "Presel10>  Bloqueado",
                                      "Preset10>   Bloccato",
                                      "Preset10>     Verrou"  };

const STR *const StrAvail10[] = {     "Preset10>      Avail",
                                      "Parameter10>Verfuegb",
                                      "Presel10>      Dispo",
                                      "Preset10>    Dispon.",
                                      "Preset10>      Dispo"  };

const STR *const StrSaved10[] = {     "Preset10>      Saved",
                                      "Parameter10> Gespei.",
                                      "Presel10>    Guardar",
                                      "Preset10>    Salvato",
                                      "Preset10>      Enrge"  };

const STR *const StrLocked11[] ={     "Preset11>     Locked",
                                      "Parameter11>Gesperrt",
                                      "Presel11>  Bloqueado",
                                      "Preset11>   Bloccato",
                                      "Preset11>     Verrou"  };

const STR *const StrAvail11[] = {     "Preset11>      Avail",
                                      "Parameter11>Verfuegb",
                                      "Presel11>      Dispo",
                                      "Preset11>    Dispon.",
                                      "Preset11>      Dispo"  };

const STR *const StrSaved11[] = {     "Preset11>      Saved",
                                      "Parameter11> Gespei.",
                                      "Presel11>    Guardar",
                                      "Preset11>    Salvato",
                                      "Preset11>      Enrge"  };

const STR *const StrLocked12[] = {    "Preset12>     Locked",
                                      "Parameter12>Gesperrt",
                                      "Presel12>  Bloqueado",
                                      "Preset12>   Bloccato",
                                      "Preset12>     Verrou"  };

const STR *const StrAvail12[] = {     "Preset12>      Avail",
                                      "Parameter12>Verfuegb",
                                      "Presel12>      Dispo",
                                      "Preset12>    Dispon.",
                                      "Preset12>      Dispo"  };

const STR *const StrSaved12[] = {     "Preset12>      Saved",
                                      "Parameter12> Gespei.",
                                      "Presel12>    Guardar",
                                      "Preset12>    Salvato",
                                      "Preset12>      Enrge"  };

const STR *const StrLocked13[] ={     "Preset13>     Locked",
                                      "Parameter13>Gesperrt",
                                      "Presel13>  Bloqueado",
                                      "Preset13>   Bloccato",
                                      "Preset13>     Verrou"  };

const STR *const StrAvail13[] = {     "Preset13>      Avail",
                                      "Parameter13>Verfuegb",
                                      "Presel13>      Dispo",
                                      "Preset13>    Dispon.",
                                      "Preset13>      Dispo"  };

const STR *const StrSaved13[] = {     "Preset13>      Saved",
                                      "Parameter13> Gespei.",
                                      "Presel13>    Guardar",
                                      "Preset13>    Salvato",
                                      "Preset13>      Enrge"  };

const STR *const StrLocked14[] ={     "Preset14>     Locked",
                                      "Parameter14>Gesperrt",
                                      "Presel14>  Bloqueado",
                                      "Preset14>   Bloccato",
                                      "Preset14>     Verrou"  };

const STR *const StrAvail14[] = {     "Preset14>      Avail",
                                      "Parameter14>Verfuegb",
                                      "Presel14>      Dispo",
                                      "Preset14>    Dispon.",
                                      "Preset14>      Dispo"  };

const STR *const StrSaved14[] = {     "Preset14>      Saved",
                                      "Parameter14> Gespei.",
                                      "Presel14>    Guardar",
                                      "Preset14>    Salvato",
                                      "Preset14>      Enrge"  };

const STR *const StrLocked15[] ={     "Preset15>     Locked",
                                      "Parameter15>Gesperrt",
                                      "Presel15>  Bloqueado",
                                      "Preset15>   Bloccato",
                                      "Preset15>     Verrou"  };

const STR *const StrAvail15[] = {     "Preset15>      Avail",
                                      "Parameter15>Verfuegb",
                                      "Presel15>      Dispo",
                                      "Preset15>    Dispon.",
                                      "Preset15>      Dispo"  };

const STR *const StrSaved15[] = {     "Preset15>      Saved",
                                      "Parameter15> Gespei.",
                                      "Presel15>    Guardar",
                                      "Preset15>    Salvato",
                                      "Preset15>      Enrge"  };

const STR *const StrLocked16[] ={     "Preset16>     Locked",
                                      "Parameter16>Gesperrt",
                                      "Presel16>  Bloqueado",
                                      "Preset16>   Bloccato",
                                      "Preset16>     Verrou"  };

const STR *const StrAvail16[] = {     "Preset16>      Avail",
                                      "Parameter16>Verfuegb",
                                      "Presel16>      Dispo",
                                      "Preset16>    Dispon.",
                                      "Preset16>      Dispo"  };

const STR *const StrSaved16[] = {     "Preset16>      Saved",
                                      "Parameter16> Gespei.",
                                      "Presel16>    Guardar",
                                      "Preset16>    Salvato",
                                      "Preset16>      Enrge"  };

const STR *const StrLocked17[] ={     "Preset17>     Locked",
                                      "Parameter17>Gesperrt",
                                      "Presel17>  Bloqueado",
                                      "Preset17>   Bloccato",
                                      "Preset17>     Verrou"  };

const STR *const StrAvail17[] = {     "Preset17>      Avail",
                                      "Parameter17>Verfuegb",
                                      "Presel17>      Dispo",
                                      "Preset17>    Dispon.",
                                      "Preset17>      Dispo"  };

const STR *const StrSaved17[] = {     "Preset17>      Saved",
                                      "Parameter17> Gespei.",
                                      "Presel17>    Guardar",
                                      "Preset17>    Salvato",
                                      "Preset17>      Enrge"  };

const STR *const StrLocked18[] ={     "Preset18>     Locked",
                                      "Parameter18>Gesperrt",
                                      "Presel18>  Bloqueado",
                                      "Preset18>   Bloccato",
                                      "Preset18>     Verrou"  };

const STR *const StrAvail18[] = {     "Preset18>      Avail",
                                      "Parameter18>Verfuegb",
                                      "Presel18>      Dispo",
                                      "Preset18>    Dispon.",
                                      "Preset18>      Dispo"  };

const STR *const StrSaved18[] = {     "Preset18>      Saved",
                                      "Parameter18> Gespei.",
                                      "Presel18>    Guardar",
                                      "Preset18>    Salvato",
                                      "Preset18>      Enrge"  };

const STR *const StrLocked19[] = {    "Preset19>     Locked",
                                      "Parameter19>Gesperrt",
                                      "Presel19>  Bloqueado",
                                      "Preset19>   Bloccato",
                                      "Preset19>     Verrou"  };

const STR *const StrAvail19[] = {     "Preset19>      Avail",
                                      "Parameter19>Verfuegb",
                                      "Presel19>      Dispo",
                                      "Preset19>    Dispon.",
                                      "Preset19>      Dispo"  };

const STR *const StrSaved19[] = {     "Preset19>      Saved",
                                      "Parameter19> Gespei.",
                                      "Presel19>    Guardar",
                                      "Preset19>    Salvato",
                                      "Preset19>      Enrge"  };

const STR *const StrLocked20[] = {    "Preset20>     Locked",
                                      "Parameter20>Gesperrt",
                                      "Presel20>  Bloqueado",
                                      "Preset20>   Bloccato",
                                      "Preset20>     Verrou"  };

const STR *const StrAvail20[] = {     "Preset20>      Avail",
                                      "Parameter20>Verfuegb",
                                      "Presel20>      Dispo",
                                      "Preset20>    Dispon.",
                                      "Preset20>      Dispo"  };

const STR *const StrSaved20[] = {     "Preset20>      Saved",
                                      "Parameter20> Gespei.",
                                      "Presel20>    Guardar",
                                      "Preset20>    Salvato",
                                      "Preset20>      Enrge"  };

const STR *const StrPLocked[] = {     "Locked",
                                      "Gesperrt",
                                      "Bloqueado",
                                      "Bloccato",
                                      "Verrou"  };

const STR *const StrPAvail[] = {      "Avail",
                                      "Verfuegb.",
                                      "Dispo",
                                      "Dispon.",
                                      "Dispo"  };

const STR *const StrPSaved[] = {      "Saved",
                                      "Gespeichert",
                                      "Guardar",
                                      "Salvato",
                                      "Enrge"  };

const STR *const StrAlarm[] = {       "Alarms",
                                      "Alarme",      
                                      "Alrmas",      
                                      "Allarmi",  
                                      "Alarmes"  };   

const STR *const StrAlarmsTitle[] = { "ALARMS",
                                      "ALARME",     
                                      "ALRMAS",     
                                      "ALLARMI", 
                                      "ALARMES"  };  

const STR *const StrSeg1[] = {        "SEG1",
                                      "SEG1",        // detrans
                                      "SEG1",        // estrans
                                      "SEG1",        // ittrans
                                      "SEG1"  }; // frtrans

const STR *const StrSeg2[] = {        "SEG2",
                                      "SEG2",        // detrans
                                      "SEG2",        // estrans
                                      "SEG2",        // ittrans
                                      "SEG2"  }; // frtrans

const STR *const StrSeg3[] = {        "SEG3",
                                      "SEG3",        // detrans
                                      "SEG3",        // estrans
                                      "SEG3",        // ittrans
                                      "SEG3"  }; // frtrans

const STR *const StrSeg4[] = {        "SEG4",
                                      "SEG4",        // detrans
                                      "SEG4",        // estrans
                                      "SEG4",        // ittrans
                                      "SEG4"  }; // frtrans

const STR *const StrSeg5[] = {        "SEG5",
                                      "SEG5",        // detrans
                                      "SEG5",        // estrans
                                      "SEG5",        // ittrans
                                      "SEG5"  }; // frtrans

const STR *const StrSeg6[] = {        "SEG6",
                                      "SEG6",        // detrans
                                      "SEG6",        // estrans
                                      "SEG6",        // ittrans
                                      "SEG6"  }; // frtrans

const STR *const StrSeg7[] = {        "SEG7",
                                      "SEG7",        // detrans
                                      "SEG7",        // estrans
                                      "SEG7",        // ittrans
                                      "SEG7"  }; // frtrans

const STR *const StrSeg8[] = {        "SEG8",
                                      "SEG8",        // detrans
                                      "SEG8",        // estrans
                                      "SEG8",        // ittrans
                                      "SEG8"  }; // frtrans

const STR *const StrSeg9[] = {        "SEG9",
                                      "SEG9",        // detrans
                                      "SEG9",        // estrans
                                      "SEG9",        // ittrans
                                      "SEG9"  }; // frtrans

const STR *const StrSeg10[] = {       "SEG10",
                                      "SEG10",       // detrans
                                      "SEG10",       // estrans
                                      "SEG10",       // ittrans
                                      "SEG10"  };    // frtrans

const STR *const Strolg1[] = {        "OLG1",
                                      "OLG1",        // detrans
                                      "OLG1",        // estrans
                                      "OLG1",        // ittrans
                                      "OLG1"  }; // frtrans

const STR *const Strncg1[] = {        "NCG1",
                                      "NCG1",        // detrans   
                                      "NCG1",        // estrans
                                      "NCG1",        // ittrans
                                      "NCG1"  }; // frtrans

const STR *const Streqg1[] = {        "EQG1",
                                      "EQG1",        // detrans
                                      "EQG1",        // estrans
                                      "EQG1",        // ittrans
                                      "EQG1"  }; // frtrans

const STR *const Strcmg1[] = {        "CMG1",
                                      "CMG1",        // detrans
                                      "CMG1",        // estrans
                                      "CMG1",        // ittrans
                                      "CMG1"  }; // frtrans

const STR *const Strprg1[] = {        "PRG1",
                                      "PRG1",        // detrans
                                      "PRG1",        // estrans
                                      "PRG1",        // ittrans
                                      "PRG1"  }; // frtrans

const STR *const Strpsg1[] = {        "PSG1",
                                      "PSG1",        // detrans
                                      "PSG1",        // estrans
                                      "PSG1",        // ittrans
                                      "PSG1"  }; // frtrans

const STR *const Strwag1[] = {        "WAG1",
                                      "WAG1",        // detrans
                                      "WAG1",        // estrans
                                      "WAG1",        // ittrans
                                      "WAG1"  }; // frtrans


const STR *const StrFactoryD[] = {    "Checksum",
                                      "Zahl pruef.",
                                      "Suma com",
                                      "Checksum",
                                      "Checksum"  };

const STR *const StrRTComp[] = {      "R/T Comp(&)",
                                      "EG Komp.(&)",
                                      "Comp C/R(&)",
                                      "R/T comp(&)",
                                      "Comp M/R(&)"  };

const STR *const StrRTRamp[] = {      "R/T Rate",
                                      "EG Rampe",
                                      "Tasa C/R",
                                      "Vel. R/T",
                                      "Taux M/R"  };

const STR *const StrReturnRamp[] = {  "Return Rate",
                                      "Hochfahren",
                                      "Tasa Retorn",
                                      "Vel ritorno",
                                      "Taux Retour"  };

const STR *const StrGainFactor[] = {  "Gain Factor",
                                      "Verst.Faktor",
                                      "Fact Gananc",
                                      "Fat amplif.",
                                      "Fact. Gain"  };

const STR *const StrIdleSpeed[] =   { "Idle PV(&)",
                                      "PV Eins(&)",
                                      "VP prda(&)",
                                      "PV intv(&)",
                                      "VP Ral.(&)"  };

const STR *const StrMinTrigger[] = {  "Min Trigger(&&)",
                                      "Min Trigger(&&)",
                                      "Disparo Min(&&)",
                                      "Trigger min(&&)",
                                      "Trigger Min(&&)"  };

const STR *const StrPartContact[] = { "Part Contact>",    
                                      "Teilekontakt>",
                                      "Contact Piez>",
                                      "Contato part>",
                                      "Contact Pce>"  };

const STR *const StrPartContactT[] = {"Part Contact",
                                      "Teilekontakt",
                                      "Contact Piez",
                                      "Contato part",
                                      "Contact Pce"  };

const STR *const StrVelocityPC[] = {  "Velocity(.1in/s)",
                                      "Geschw.(.1in/s)",
                                      "Velocid(.1in/s)",
                                      "Velocit:(.1in/s)",
                                      "Vitesse(.1in/s)"  };

const STR *const StrForcePC[] = {     "Force(&&)",
                                      "Kraft(&&)",
                                      "Fuerza(&&)",
                                      "Forza(&&)",
                                      "Force(&&)"  };

const STR *const StrRTRampSlowest[] ={"R/T Rate>    Slowest",
                                      "EG Rampe>   lngs.min",
                                      "Tasa C/R>    Mas len",
                                      "Vel. R/T>   Molt len",
                                      "Taux M/R>    Minimum"  };

const STR *const StrRTRampSlow[] = {  "R/T Rate>       Slow",
                                      "EG Rampe>    langsam",
                                      "Tasa C/R>      Lento",
                                      "Vel. R/T>      Lento",
                                      "Taux M/R>       Lent"  };

const STR *const StrRTRampNormal[] = {"R/T Rate>     Normal",
                                      "EG Rampe>     normal",
                                      "Tasa C/R>     Normal",
                                      "Vel. R/T>    Normale",
                                      "Taux M/R>     Normal"  };

const STR *const StrRTRampFast[] = {  "R/T Rate>       Fast",
                                      "EG Rampe>    schnell",
                                      "Tasa C/R>     Rapido",
                                      "Vel. R/T>     Rapida",
                                      "Taux M/R>       Rapd"  };

const STR *const StrRTRampFastest[] ={"R/T Rate>    Fastest",
                                      "EG Rampe>   schn.max",
                                      "Tasa C/R>    Mas rap",
                                      "Vel. R/T>   Molt rpd",
                                      "Taux M/R>    Maximum"  };

const STR *const StrReturnRampSlowest[] = {
                                      "Return Rate> Slowest",
                                      "Hochfahren> lngs.min",
                                      "Tasa Retorno>Mas len",
                                      "Vel ritorno>Molt len",
                                      "Taux Retour> Minimum"  };

const STR *const StrReturnRampSlow[]={"Return Rate>    Slow",
                                      "Hochfahren>  langsam",
                                      "Tasa Retorno>  Lento",
                                      "Vel ritorno>   Lento",
                                      "Taux Retour>    Lent"  };

const STR *const StrReturnRampNormal[] = {
                                      "Return Rate>  Normal",
                                      "Hochfahren>   normal",
                                      "Tas Retorno>  Normal",
                                      "Vel ritorno> Normale",
                                      "Taux Retour>  Normal"  };

const STR *const StrReturnRampFast[]={"Return Rate>    Fast",
                                      "Hochfahren>  schnell",
                                      "Tas Retorno>  Rapido",
                                      "Vel ritorno>  Rapida",
                                      "Taux Retour>    Rapd"  };

const STR *const StrReturnRampFastest[] = {
                                      "Return Rate> Fastest",
                                      "Hochfahren> schn.max",
                                      "Tasa Retorno>Mas rap",
                                      "Vel ritorno>Molt rpd",
                                      "Taux Retour> Maximum"  };

const STR *const StrStartRamp[] = {   "Start Rate",
                                      "Startrampe",
                                      "Tasa Inic",
                                      "Vel. avvio",
                                      "Taux Start"  };

const STR *const StrStartRampSlowest[] = {
                                      "Start Rate>  Slowest",
                                      "Startr.>sehr langsam",
                                      "Tasa Inic>   Mas len",
                                      "Vel. avvio> Molt len",
                                      "Taux Start>  Minimum"  };

const STR *const StrStartRampSlow[] ={"Start Rate>     Slow",
                                      "Startrampe>     lang",
                                      "Tasa Inic>     Lento",
                                      "Vel. avvio>    Lento",
                                      "Taux Start>     Lent"  };

const STR *const StrStartRampNormal[] = {
                                      "Start Rate>   Normal",
                                      "Startrampe>   normal",
                                      "Tasa Inic>    Normal",
                                      "Vel. avvio>  Normale",
                                      "Taux Start>   Normal"  };

const STR *const StrStartRampFast[]={ "Start Rate>     Fast",
                                      "Startrampe>  schnell",
                                      "Tasa Inic>    Rapido",
                                      "Vel. avvio>   Rapida",
                                      "Taux Start>     Rapd"  };

const STR *const StrStartRampFastest[] = { 
                                      "Start Rate>  Fastest",
                                      "Startr.>sehr schnell",
                                      "Tasa Inic>   Mas rap",
                                      "Vel. avvio> Molt rpd",
                                      "Taux Start>  Maximum"  };          


const STR *const StrMH_0[] = {        "HORN DOWN           ",               
                                      "HORN AB             ",       
                                      "SONO. ABAJO         ",
                                      "RIDR SNTO           ",       
                                      "DESC SONO           "  };    

const STR *const StrMH_2[] = {        "Downspeed(&)",
                                      "Abf.Gesch.(&)",
                                      "Vel. Lenta(&)",
                                      "Veloc dis(&)",
                                      "Vit. Desc(&)" };

const STR *const StrMH_4[] =  {       "Press Start Switches",
                                      "Startschalter drueck",
                                      "Pulse Puls. Inicio",
                                      "Premi tasto avvio",
                                      "Enf. Boutons Start"  };

const STR *const StrMH_5[] =  {       "Until Beep is Heard ",
                                      "Signal hoerbar      ",
                                      "Hasta escuchar snal ",
                                      "Finche sente segnal ",
                                      "Jusqu'au bip sonore "  };

const STR *const StrMH_6[] =  {       "Abs Pos(&&)",
                                      "Abs. Pos.(&&)",        
                                      "Pos abs(&&)",        
                                      "Pos ass(&&)",        
                                      "Pos Abs(&&)"  };     

const STR *const StrMH_8[] =  {       "Force Act(&&)",
                                      "Kraft VE(&&)",
                                      "Fuerza Act(&&)",
                                      "Att forza(&&)",
                                      "Force Act(&&)"  };

const STR *const StrMH_10[] = {       "In Horn Down Mode   ",
                                      "Im Einrichtmodus    ",
                                      "En mod Sntrd Abj    ",
                                      "Mod disc sonotrd    ",
                                      "Mde Desc. Sonotr.   "  };

const STR *const StrMH_11[] = {       "Velocity(&&&&)",
                                      "Geschw.(&&&&)",
                                      "Velocida(&&&&)",
                                      "Velocita(&&&&)",
                                      "Vitesse(&&&&)"  };

const STR *const StrMH_12[] = {       "Sys Pres(&&&)",
                                      "Syst.Drck(&&&)",
                                      "Pres Sis(&&&)",
                                      "Press ss(&&&)",
                                      "Press Ss(&&&)"  };

const STR *const StrMH_15[] =    {    "Horn Down Clamp",           /* was "Trigger"; */
                                      "Horn Ab klem.  ",        
                                      "Blqueo Sono.Abajo",
                                      "Serrare sonotrd",        
                                      "Verrouill.Desc."  };     

 
const STR *const StrMH_17[] = {       "RAPID TRAV",
                                      "EILGANG",
                                      "VEL. RAPIDA",
                                      "SPOST RAPD",
                                      "DESC RAPID."  };

const STR *const StrMH_19[] = {       "HD Force(&&)",
                                      "HD Kraft(&&)",
                                      "Fuerza Baj.(&&)",
                                      "HD Forza(&&)",
                                      "HD Force(&&)"  };

                                                       
const STR *const StrMT_0[] =     {    "Test",           
                                      "Test",       
                                      "Test",       
                                      "Test",       
                                      "Test"  };    

const STR *const StrMT_2[] =     {    "F Memory",
                                      "K speich.",
                                      "F Memori",
                                      "F memori",
                                      "Mem. F"  };

const STR *const StrMT_3[] =     {    "F Actual",
                                      "K akt",
                                      "F Actual",
                                      "F reale",
                                      "F R'elle"  };

const STR *const StrMT_4[] =     {    "Power(&)",
                                      "Leistung(&)",
                                      "Poten(&)",
                                      "Potnz(&)",
                                      "Puiss(&)"  };

const STR *const StrMT_5[] =     {    "Frequency(&&)",
                                      "Frequenz(&&)",
                                      "Frecuenci(&&)",
                                      "Frequenza(&&)",
                                      "Frequence(&&)"  };

const STR *const StrMT_6[] =     {    "Amplitude(&)",
                                      "Amplitude(&)",
                                      "Amplitud(&)",
                                      "Ampiezza(&)",
                                      "Amplitude(&)"  };


const STR *const StrMX_2[]  = {       "Cal Sensors",
                                      "Kal. Sensor",
                                      "Cal Detecto",
                                      "Sensori cal",
                                      "Cal Captrs"  };

const STR *const StrMX_3[]  = {       "Verify Distance",
                                      "Weg pruefen",
                                      "Verif Distancia",
                                      "Verifica distnz",
                                      "Verif. Distance"  };

const STR *const StrMX_4[]  = {       "            Continue",
                                      "              Weiter",
                                      "              Seguir",
                                      "            Continua",
                                      "             Contin."  };

const STR *const StrMX_5[]  = {       "Press Start Switches",
                                      "Startschalter drueck",
                                      "Pulse Puls. Inicio",
                                      "Premi tasto avvio",
                                      "Enf. Boutons Start"  };

const STR *const StrMX_6[]  = {       "Until Beep is Heard",
                                      "Signal hoerbar     ",
                                      "Hasta escuchar snal",
                                      "Finche sente segnal",
                                      "Jusqu'au bip sonore"  };

const STR *const StrMX_8[]  = {       "Set Regulator To ",
                                      "Regler einst. auf ",
                                      "Fija Regulador a ",
                                      "Imp. regolator a ",
                                      "Reg Regulateur a "  };

const STR *const StrMX_9A[] = {       "10-30PSI( 69-207kPa)",
                                      "10-30PSI( 69-207kPa)",
                                      "10-30PSI( 69-207kPa)",
                                      "10-30PSI( 69-207kPa)",
                                      "10-30PSI( 69-207kPa)"  };

const STR *const StrMX_9B[] = {       "50-80PSI(345-552kPa)",
                                      "50-80PSI(345-552kPa)",
                                      "50-80PSI(345-552kPa)",
                                      "50-80PSI(345-552kPa)",
                                      "50-80PSI(345-552kPa)"  };

const STR *const StrMX_9C[] = {       "Operating PSI(kPa)",
                                      "Betriebs PSI(kPa)",     
                                      "Operacion PSI(kPa)",     
                                      "PSI d eserczi(kPa)",     
                                      "PSI (kPa) de Serv."  };  

const STR *const StrMX_9D[] = {       "Reading(&&&)   ",
                                      "Anzeige(&&&)   ",
                                      "Lectura(&&&)   ",
                                      "Lettura(&&&)   ",
                                      "Mesure(&&&)    "  };

const STR *const StrMX_9E[] = {       "20-30PSI(138-207kPa)",
                                      "20-30PSI(138-207kPa)",
                                      "20-30PSI(138-207kPa)",
                                      "20-30PSI(138-207kPa)",
                                      "20-30PSI(138-207kPa)"  };

const STR *const StrMX_9J[] = {       "30-50PSI(207-345kPa)",
                                      "30-50PSI(207-345kPa)",
                                      "30-50PSI(207-345kPa)",
                                      "30-50PSI(207-345kPa)",
                                      "30-50PSI(207-345kPa)"  };

const STR *const StrMX_9F[] = {       "50 PSI(345 kPa)",
                                      "50 PSI(345 kPa)",
                                      "50 PSI(345 kPa)",
                                      "50 PSI(345 kPa)",
                                      "50 PSI(345 kPa)"  };

const STR *const StrMX_9K[] = {       "60 PSI(415 kPa)",
                                      "60 PSI(415 kPa)",
                                      "60 PSI(415 kPa)",
                                      "60 PSI(415 kPa)",
                                      "60 PSI(415 kPa)"  };

const STR *const StrMX_9G[] = {       "Set to 15PSI(104kPa)",
                                      "Einst. 15PSI(104kPa)",       
                                      "Ajst a 15PSI(104kPa)",       
                                      "Impr a 15PSI(104kPa)",       
                                      "Reg. a 15PSI(104kPa)"  };    

const STR *const StrMX_9H[] = {       "Set to 25PSI(173kPa)",
                                      "Einst. 25PSI(173kPa)",       
                                      "Ajst a 25PSI(173kPa)",       
                                      "impr a 25PSI(173kPa)",       
                                      "Reg. a 25PSI(173kPa)"  };    

const STR *const StrMX_9I[] = {       "Set to 5PSI(35kPa)",
                                      "Einst. 5PSI(35kPa)",         
                                      "Ajst a 5PSI(35kPa)",         
                                      "Impr a 5PSI(35kPa)",         
                                      "Reg. a 5PSI(35kPa)"  };      

const STR *const StrMX_10[] = {       "CAL SENSORS         ",
                                      "KAL. SENSOR         ",
                                      "CAL DETECTO         ",
                                      "SENSORI CAL         ",
                                      "CAL CAPTRS          "  };

const STR *const StrMX_11[]      =  { "(50mm)      Continue",
                                      "(50mm)        Weiter",
                                      "(50mm)        Seguir",
                                      "(50mm)      Continua",
                                      "(50mm)       Contin."  };

const STR *const StrMX_22[] = {       "Enter Pressure Gauge",
                                      "Druck eingeben",       
                                      "Intro manometro",       
                                      "Inserire manometro",       
                                      "Entr. Pression"  };    

const STR *const StrMX_25[] = {       "Horn Down       Done",
                                      "Horn Ab        Getan",       
                                      "Sono. Abajo     Tmdo",       
                                      "Rid sonotrodo   Esgt",   
                                      "Desc. Sonotr.  Term."  };    


const STR *const StrMX_26[] = {       "Failed by ",
                                      "Fehler durch ",                 
                                      "Fallo por ",                 
                                      "Guas dvt a ",                 
                                      "Echec "  };              

const STR *const StrMX_27[] = {       "See Manual Section",
                                      "Siehe Handb. Abschn.",
                                      "Ver Seccian Manual",
                                      "Vedi sezion manual",
                                      "Cf. Section Manuel"  };

const STR *const StrMX_28[] = {       "7.2             Done",
                                      "7.2            Getan",
                                      "7.2             Tmdo",
                                      "7.2             Esgt",
                                      "7.2             Term"  };

const STR *const StrMX_29[] = {       "Position Load Cell",
                                      "Pos. Kraftaufnehmer",
                                      "Colocar Cel Carga",
                                      "Posizion cel caric",
                                      "Placer Jauge Contr"  };

const STR *const StrMX_29A[] = {      "Set Downspeed = 20%",
                                      "Abw.Gesch einst= 20%",       
                                      "Veloc colocacn = 20%",       
                                      "Impost decelera= 20%",       
                                      "Reg. Vit. Desc.= 20%"  };    

const STR *const StrMX_29B[] = {      "Set Stroke To 2\042",
                                      "Hub einst. auf 2\042",        
                                      "Ajs carrera a 2\042",        
                                      "Impost cors a 2\042",        
                                      "Reg Course a 2\042"  };     

const STR *const StrMX_32[] = {       "Reading(&&)      ",
                                      "Anzeige(&&)      ",
                                      "Lectura(&&)      ",
                                      "Lettura(&&)      ",
                                      "Mesure(&&)       "  };

const STR *const StrMX_33[] = {       "    Please Wait     ",
                                      "    Bitte warten    ",
                                      "        Espere      ",
                                      "  Attendere Prego   ",
                                      "     Attdre SVP     "  };

const STR *const StrMX_34[] = {       "Reenter Load Cell",
                                      "Krft.Wert neu eingeb",      
                                      "Reintro cel carga",      
                                      "Reinser cel caric",      
                                      "Entrer Jauge Contr"  };   

const STR *const StrMX_36[] = {       "Complete            ",
                                      "Komplett            ",
                                      "Completo            ",
                                      "Completo            ",
                                      "Fin                 "  };

const STR *const StrMX_55[]  = {      "Enter 1st Load Cell",
                                      "Eingabe Krft.Wert 1",
                                      "Intro 1 cel carga ",
                                      "Inseri 1 cel caric",
                                      "Entr. Val Jauge 1"  };

const STR *const StrMX_55A[] = {      "Enter 2nd Load Cell",
                                      "Eingabe Krft.Wert 2",
                                      "Intro 2 cel carga ",
                                      "Inseri 2 cel caric",
                                      "Entr. Val Jauge 2"  };

const STR *const StrMX_55B[] = {      "Enter 3rd Load Cell",
                                      "Eingabe Krft.Wert 3",
                                      "Intro 3 cel carga ",
                                      "Inseri 3 cel caric",
                                      "Entr. Val Jauge 3"  };

const STR *const StrMX_56[] =   {     "An Alarm Occurred ",
                                      "Alarm eingetret ",
                                      "Hubo una alarma   ",
                                      "Si e verif allarm ",
                                      "Alarme Emise"  };

const STR *const StrMX_57[] =    {    "Calibration is   ",
                                      "Kalib. ist       ",
                                      "Calibracion      ",
                                      "Calibraz e stata ",
                                      "Calibration      "  };

const STR *const StrMX_58[] =    {    "      Aborted       ",
                                      "      Abgebr.       ",
                                      "      Anulada       ",
                                      "      abortita      ",
                                      "      Annulee       "  };

const STR *const StrMX_59[] = {       "Calibration not",
                                      "Kalib. nicht",
                                      "Calibracion no ",
                                      "Calibrazion non",
                                      "Calibration non"  };

const STR *const StrMX_60[] = {       "changed         Done",
                                      "Geaendert      Getan",
                                      "varia           Tmdo",
                                      "Modif       Eseguito",
                                      "modif.         Term."  };

const STR *const StrMX_61[] = {       "Verify Using",
                                      "Ueberpr. mit",
                                      "Verif en uso",
                                      "Verifi tramt",
                                      "Verifier par"  };

const STR *const StrMPW_0[] =   {     "TYPE PASSWORD       ",
                                      "PASSWORT EING       ",
                                      "ESCRIBIR CONTRASENA ",
                                      "DIGITA PSSWRD       ",
                                      "ENTR M. PASS        "  };

const STR *const StrMPW_1[] =   {     "RETYPE PASSWORD     ",
                                      "PASSWORT BESTAE     ",
                                      "RESCRBR CNTRSN      ",
                                      "RIDIGITA PSSWRD     ",
                                      "RETYPER M. PASS     "  };

const STR *const StrMPW_2[] =   {     "Password=_      Done",
                                      "Passwort=_     Getan",
                                      "Cntrsena=_      Tmdo",
                                      "Password=_      Esgt",
                                      "M. Passe=_      Term"  };

const STR *const StrMPW_3[] =   {     "Password            ",
                                      "Passwort            ",
                                      "Cntrsena            ",
                                      "Password            ",
                                      "M. Passe            "  };

const STR *const StrMPW_4[] =   {     "Password Accepted   ",
                                      "Passwort akzept     ",
                                      "Cntrsena Aceptada   ",
                                      "Psswrd accettata    ",
                                      "Mot Passe Accepte   "  };

const STR *const StrMPW_5[] =   {     "Incorrect           ",
                                      "Inkorrekt           ",
                                      "Incorrect           ",
                                      "Errato              ",
                                      "Incorrect           "  };

const STR *const StrMPW_6[] =     {   "          Start Over",
                                      "         Start Ueber",
                                      "          Volv a Emp",
                                      "          Ricomincia",
                                      "          Redemarrer"  };

const STR *const StrMPW_8[] =   {     "ENTER PASSWORD      ",
                                      "PASSWORT EING       ",
                                      "ENTRE CONTRSNA      ",
                                      "INSRSCI PSSWRD      ",
                                      "ENT. MOT PASSE      "  };

const STR *const StrMPW_9[] =   {     "Password Incorrect  ",
                                      "Passwort falsch     ",
                                      "Contrasena Incorrec.",
                                      "Password errata     ",
                                      "Mot Passe Incorr.   "  };

const STR *const StrMPW_10[] =  {     "Retype Password     ",
                                      "PASSWORT BESTAE     ",
                                      "Reescrbr Cntrsn     ",
                                      "Ridigita Psswrd     ",
                                      "Retyper M. Pass     "  };

const STR *const StrMPW_11[] =  {     "PASSWORD            ",
                                      "PASSWORT            ",
                                      "CNTRSENA            ",
                                      "PASSWORD            ",
                                      "MOT PASSE           "  };


const STR *const StrME_0[]  =   {     "   Emergency Stop   ",
                                      "       Not-Aus      ",
                                      "    Paro emergenc   ",
                                      "    Arresto emrgnz  ",
                                      "    Arret urgence   "  };

const STR *const StrME_4[]  =   {     "Value Below Minimum ",
                                      "Wert unter Minimum  ",
                                      "Valor Por Debajo Mn ",
                                      "Valore Sotto Minimo ",
                                      "Val. Inf Au Minimum "  };

const STR *const StrME_5[]  =   {     "Value Above Maximum ",
                                      "Wert ueber Maximum  ",
                                      "Valor Por Encim Max ",
                                      "Valore Sopr Massimo ",
                                      "Val. Sup Au Maximum "  };

const STR *const StrME_6[]  =   {     "No Value Entered    ",
                                      "Kein Wert eingegeb. ",
                                      "Ningun val intro    ",
                                      "Nessun val inserito ",
                                      "Aucune Val. Entree  "  };

const STR *const StrME_8[]  =   {     "Min Value           ",
                                      "Min Wert            ",
                                      "Valor min           ",
                                      "Valore min          ",
                                      "Val. Min.           "  };

const STR *const StrME_9[]  =   {     "Max Value           ",
                                      "Max Wert            ",
                                      "Valor max           ",
                                      "Valore max          ",
                                      "Val. Max.           "  };

const STR *const StrME_10[] =   {     "Press Go Back       ",
                                      "Druecke Zurueck     ",
                                      "Pulse Atras         ",
                                      "Premi Go Back       ",
                                      "Press.Go Back       "  };

const STR *const StrME_11[] =   {     "Bad Mode",
                                      "Falsch. Modus",
                                      "Mal modo",
                                      "Mod erra",
                                      "Mauv Mod"  };


const STR *const StrPO_1[]  =   {     "Checking Actuator...",
                                      "VE pruefen..........",
                                      "Probando Actuador...",
                                      "Verifica attuator...",
                                      "Verific. Actuator..."  };

const STR *const StrPO_2[]  =   {     "Checking Power/S....",
                                      "Generat. pruefen....",
                                      "Probando FA.........",
                                      "Verifica Genrtr.....",
                                      "Verific. Generat...."  };

const STR *const StrPO_3[]  =   {     "Checking Controls...",
                                      "Steuerung pruefen...",
                                      "Probando Contrles...",
                                      "Verifica controli...",
                                      "Verific. Cmdes......"  };

const STR *const StrPO_4[]  =   {     "Checking Stack......",
                                      "Akku. pruefe........",
                                      "Probando Pila.......",
                                      "Verifica stack......",
                                      "Verific. Stack......"  };

const STR *const StrPO_5[]  =   {     "BRANSON 2000",
                                      "BRANSON 2000",               
                                      "BRANSON 2000",               
                                      "BRANSON 2000",               
                                      "BRANSON 2000"  };            

const STR *const StrPO_6[]  =   {     "Control Level = ",
                                      "Steuerlevel =   ",
                                      "Nivel Control = ",
                                      "Livel Control = ",
                                      "Niveau Comde =  "  };

const STR *const InitializingMsg3[]={ "(c)1996-2004 BRANSON",
                                      "(c)1996-2004 BRANSON",
                                      "(c)1996-2004 BRANSON",
                                      "(c)1996-2004 BRANSON",
                                      "(c)1996-2004 BRANSON"  };

const STR *const InitializingMsg4[]={ "ULTRASONICS CORP  ",
                                      "ULTRASONICS CORP  ",
                                      "ULTRASONICS CORP  ",
                                      "ULTRASONICS CORP  ",
                                      "ULTRASONICS CORP  "  };



const STR *const StrReadyUndefined[]={"RUN:Undefined Mode  ",
                                      "SCHW.:Undef. Mod.   ",       
                                      "EJEC:modo no defin  ",         
                                      "ESE:Non Defin Modo  ",         
                                      "EXE:Mode non def.   "  };    


 //READYSTATE
const STR *const StrReadyTime[]  = {  "RUN:TIME =          ",
                                      "SCHW.:ZEIT =        ",
                                      "RUN:TIEM =          ",
                                      "ESE:TEMP =          ",
                                      "EXE:TPS =           "  };

 //READYSTATE
const STR *const StrReadyEnergy[] = { "RUN:ENERGY =        ",
                                      "SCHW.:ENERGIE=      ",
                                      "RUN:ENRGIA =        ",
                                      "ESE:ENERGIA =       ",
                                      "EXE:ENERGIE =       "  };

//READYSTATE
const STR *const StrReadyPP[]   = {   "RUN:PK PWR =        ",
                                      "SCHW.:SP.LST. =     ",
                                      "RUN:PC POT =        ",
                                      "ESE:PK PWR =        ",
                                      "EXE:PUIS.CRT=       "  };

 //READYSTATE
const STR *const StrReadyCollapse[]={ "RUN:COL =           ",
                                      "SCHW.:REL =         ",
                                      "RUN:COL =           ",
                                      "ESE:COL =           ",
                                      "EXE:REL =           "  };

//READYSTATE
const STR *const StrReadyAbsolute[]={ "RUN:ABS =           ",
                                      "SCHW.:ABS =         ",
                                      "RUN:ABS =           ",
                                      "ESE:ABS =           ",
                                      "EXE:ABS =           "  };

//READYSTATE
const STR *const StrReadyGrdDet[]= {  "RUN:GROUND DETECT   ",
                                      "SCHW.:METALLKONT.   ",
                                      "RUN:DETECC TIERRA   ",
                                      "ESE:RILEVA TERA     ",
                                      "EXE:DETECT. MASSE   "  };

 //READYSTATE
const STR *const StrReadyCont[]  = {  "RUN:CONTINUOUS      ",
                                      "SCHW.:KONTIN.       ",       
                                      "RUN:CONTINUA        ",         
                                      "ESE:CONTINUA        ",         
                                      "EXE:CONTINU.        "  };    

//DOWNSTROKESTATE
const STR *const StrDownstroke1[] = { "EXTENDING           ",
                                      "VERLAENGERN         ",
                                      "AMPLIANDO           ",
                                      "ESTENSION           ",
                                      "EXTENSION           "  };

 //DOWNSTROKESTATE (Preset changed)
const STR *const StrVerifying[]  = {  "VERIFYING PRESET    ",
                                      "VOREINST. PRUEFEN   ",
                                      "VERIFICA PRESEL     ",
                                      "VERIFICA PRESET     ",
                                      "VERIFICAT PREREG    "  };

// SVINTERLOCK STATE
const STR *const StrInterlockDelay[]={"EXT START DELAY     ",
                                      "EXT START DELAY     ",
                                      "EXT START DELAY     ",
                                      "EXT START DELAY     ",
                                      "EXT START DELAY     "  };

 //TRIGGERDELAYSTATE
const STR *const StrTriggerDelay[] = {"ULTRASONIC DELAY    ",
                                      "ULTRASONIC DELAY    ",
                                      "ULTRASONIC DELAY    ",
                                      "ULTRASONIC DELAY    ",
                                      "ULTRASONIC DELAY    "  };

//WELDTIMESTATE
const STR *const StrWeld[]      = {   "WELDING             ",
                                      "SCHWEIS             ",
                                      "SOLDAND             ",
                                      "SALDATR             ",
                                      "SOUDAGE             "  };


//HOLDTIMESTATE
const STR *const StrHold[]       = {  "HOLDING             ",
                                      "HALTEN              ",
                                      "MANTNMT             ",
                                      "MNTINPRSS           ",
                                      "MAINTN              "  };

 //AFTERBURSTDELAYSTATE
const STR *const StrABdelay[]   = {   "AFTERBURST DELAY    ",
                                      "NACHIMP.VERZOEG.    ",
                                      "RET. DPUS           ",
                                      "RITRD AFTERBURST    ",
                                      "DELAI POST-IMP      "  };

 //AFTERBURSTTIMESTATE
const STR *const StrAB[]         = {  "AFTERBURST          ",
                                      "NACHIMPULS          ",
                                      "Dis.PostUS          ",
                                      "AFTERBURST          ",
                                      "PSTMPLSION          "  };

const STR *const StrUpstroke[]   = {  "RETRACTING          ",
                                      "ZURUECKZIE.         ",
                                      "REPLEGANDO          ",
                                      "RITORNO             ",
                                      "RETRACTION          "  };

const STR *const StrSeeking[]    = {  "POST SEEKING        ",
                                      "NACHSUCHEN          ",
                                      "BUSCNDO POS         ",
                                      "SEEK POST           ",
                                      "POST RECH.          "  };

 //Latching alarms
const STR *const StrNotReady[]  = {   "NOT READY           ",
                                      "NI BEREIT           ",
                                      "NO LISTO            ",
                                      "NO PRONTO           ",
                                      "PAS PRET            "  };

// TxtHSScanning[] must be 10 chars long
const STR * const TxtHSScanning[] = { "Scanning  ",
                                      "Scanning  ",
                                      "Scanning  ",
                                      "Scanning  ",
                                      "Scanning  " };

const STR * const TxtHSComplete[] = { "Scan complete       ",
                                      "Scan abbrech        ",
                                      "Cancela scan        ",
                                      "Annulla scan        ",
                                      "Fin scan            " };


const STR * const TxtHSOverload[] = { "Scan Overload       ",
                                      "Scan Ueberlast      ",
                                      "Scan Sobrecarga     ",
                                      "Scan Sovraccarico   ",
                                      "Scan Surcharge      " };

/*--------------------------------------------------------------------------
                            QVGA Language Strings
---------------------------------------------------------------------------*/
const STR *const Str_Graph[]      =  { "Graphs",
                                       "Graphs",
                                       "Grafs ",
                                       "Grafs ",
                                       "Graphs" };


const STR *const Str_PresentSetup[]= {  "Present Setup.",
                                      "Akt. Einricht.",
                                      "Config Actual.",
                                      "Install Attuale",
                                      "Config Actuel. "  };

const STR *const Str_ActSetup[]   =  {"actuator cal.",
                                      "VE kalibrieren",
                                      "Actuador cal.",
                                      "Cal. Attuatore",
                                      "Cal. Actuator"  };

const STR *const Str_Cycle[]      =  {  "Cycle#:",
                                        "Zykls#:",
                                        "Ciclo#:",
                                        "Ciclo#:",
                                        "Cycle#:"  };

const STR *const Str_Refresh[]     = { "Refresh",
                                       "aktuali.",
                                       "Refresc.",
                                       "Pulisci",
                                       "Rafraichir"   };
                                       
const STR *const Str_Print[]       = { "Print",
                                       "Druck",
                                       "Imprimir",
                                       "Stampa",
                                       "Imprimer"   };
                                       
const STR *const Str_RunResults[] =  { "Weld Results",
                                       "Schw Ergbni",
                                       "Resulta Sold",
                                       "Risulti sald",
                                       "Result. Soud" };


const STR *const Str_HornDown[]   =   {"Horn Down",
                                       "Horn Abw ",       
                                       "Horn Down",       
                                       "Rid sonotrodo",   
                                       "Desc. Sontro."  };   

                    
const STR *const Str_ScreenSetup[] =  {"Screen Setup",
                                       "Bild. einst.",       
                                       "Conf pantalla",       
                                       "Imposta Sreen",   
                                       "Reglage Ecran"  };
                                       
const STR *const QVGAInitializingMsg3[]={ "(c)1996-2004 BRANSON",
                                          "(c)1996-2004 BRANSON",
                                          "(c)1996-2004 BRANSON",
                                          "(c)1996-2004 BRANSON",
                                          "(c)1996-2004 BRANSON"  };                                                               
                                                               
const STR *const Str_Preset[]         = { "Preset",
                                          "Parameter",
                                          "Presel",
                                          "Preset",
                                          "Preset"  };
                                          
const STR *const Str_Velocity[]      = {  "Velocity",
                                          "Geschwin",
                                          "Velocid ",
                                          "Velocit ",
                                          "Vitesse "  };
                                      
const STR *const Str_Power[]         = {  "Power",
                                          "Leist",
                                          "Poten",
                                          "Potnz",
                                          "Puiss"  }; 
                                      
const STR *const Str_Freq[]          = { "Frequency",
                                         "Frequenz",
                                         "Frecuenci",
                                         "Frequenza",
                                         "Frequence"  };   
                                      
const STR *const Str_ColDist[]       = { "Col Distance",
                                         "Weg rel",
                                         "Dist Col",
                                         "Distanza Fus",
                                         "Distance Rel"  };

const STR *const Str_PCol[]          = { "P/Col",
                                         "Leist/Weg rel",
                                         "Pot/Colapso",
                                         "Pot./Dis Rel",
                                         "Puiss/Dist.Rel" };

const STR *const Str_PForce[]        = { "P/Force",
                                         "Leistung/Kraft",
                                         "Pot/Fuerza",
                                         "Pot./Forza",
                                         "Puiss/Force" };
                                
const STR *const Str_ForceCol[]     = { "Force/Col",
                                        "Kraft/Weg rel",
                                        "Fuerza/Colapso",
                                        "Forza Dist.Rel",
                                        "Force/Dist Rel" }; 
                                        
const STR *const Str_Exit[]     = { "Exit",
                                    "Ende",
                                    "Salir",
                                    "Esci",
                                    "Exit" };                                                                                                       

/* Language string for Current value */
const STR *const StrCurrentValue[]   = { "Current Value",  
                                         "Aktuell Wert",
                                         "Corrnte Valor",
                                         "Corrent Valore",
                                         "Actuel. Val." };
/* Language string for New value */                                  
const STR *const StrNewValue[]       = { "New Value",
                                         "New Wert",
                                         "New Valor",
                                         "New Valore",
                                         "New Val." };

const STR *const Str_NewPresetName[] = {  "New Preset Name",  
                                          "Neuer Para. Name",
                                          "Nuevo nombres presl",
                                          "Nome nuovo Preset",
                                          "Nom nouveau Preset" };    

const STR *const Str_CurrPresetName[] = { "Current Preset Name",  
                                          "Akt. Para. Name",
                                          "Actual nombres presl",
                                          "Nome Preset Attuale",
                                          "Nom Preset actuel" };                                                                    
           
const STR *const Str_DigitalTuneSett[] = { "Digital Tune Settings =",
                                           "Digital Tune Einstell =",
                                           "Ajustes Digital Tune =",
                                           "Impost. Digital Tune =",
                                           "Reglages Digital Tune =" };

const STR *const Str_DispGraph[]       = {"Display Graph",
                                          "Display Graph",
                                          "Display Graf ",
                                          "Display Graf ",
                                          "Display Graph" };

const STR *const Str_OvrWritePreset[]   = {"Overwrite Preset ",
                                           "Ersetze Voreinst.",
                                           "Sobrscribir Pres ",
                                           "Sovrascr. Preset ",
                                           "Ecraser Preset "  };
                                           
const STR *const Str_FreqMemory[]       = {"Freq Memory",
                                           "Freq speich.",
                                           "Frec Memori",
                                           "Freq memori",
                                           "Mem. Freq"  };

const STR *const Str_FreqActual[]       = {"Freq Actual",
                                           "Freq akt",
                                           "Frec Actual",
                                           "Freq reale",
                                           "Freq R'elle"  };
                                           
const STR *const Str_AbortScan[]        = {"Abort Scan",
                                           "Scan abbrechen",
                                           "Abortar Scan",
                                           "Scan. abortita",
                                           "Arret Scan"  };                                                                                      

const STR *const Str_Default[]            = {"Default",
                                             "Vorein.",
                                             "Defecto",
                                             "Default",
                                             "Usine"};
                                             
const STR *const Str_FactDefaults[]   =  {  "factory defaults",
                                            "Werkseinstell.",
                                            "valores fabrica",
                                            "valori pred prod",
                                            "Param usine"  };
                                            
const STR *const Str_CalibNotChnged[] = { "Calibration not Changed",
                                          "Kalib. nicht Geaendert",
                                          "Calibracion no varia",
                                          "Calibrazion non Modif",
                                          "Calibration non modif"  };

const STR *const Str_VerifyHornDown[] = {"Verify Using Horn Down",
                                      "Ueberpr. mit Horn Ab",
                                      "Verif en uso Sono. Abajo",
                                      "Verifi tramt Rid sonotrodo",
                                      "Verifier par Desc. Sonotr."  };
                                      
const STR *const Str_ReleaseStart[]   =    {"Release Start Switches",
                                            "Start freigeben Schalter",
                                            "Liberar inic Conmuts",
                                            "Rilasc Start Interruttori",
                                            "Relach Start Contacts"  };

const STR *const Str_ReleaseOvrd[]    =    {"Release Manual Override",
                                            "Manuell freigeben Ueberbr",
                                            "Liberar manual Anular",
                                            "Rilasc Manuale Esclusione",
                                            "Relach Manuel. Encl.manu"  };                                      
                                            
const STR *const Str_SetStroke[] = {      "Set Stroke To 2 Inch",
                                          "Hub einst. auf 2 Inch",        
                                          "Ajs carrera a 2 Inch",        
                                          "Impost cors a 2 Inch",        
                                          "Reg Course a 2 Inch"  };                                              

const STR *const Str_Next[]       = { "Next",
                                      ">>",
                                      ">>",
                                      ">>",
                                      ">>" }; 

const STR *const Str_Prev[]       = { "Prev",
                                      "<<",
                                      "<<",
                                      "<<",
                                      "<<" };
                                      
const STR *const Str_TouchButton1[]  = {"Touch 1 and Release",
                                        "Taster 1 betätigen",
                                        "Pulsar botón 1",
                                        "Tocca pulsante 1",
                                        "Presser 1 et relacher" };
                                      

const STR *const Str_TouchButton2[]  = {"Touch 2 and Release",
                                        "Taster 2 betätigen",
                                        "Pulsar botón 2",
                                        "Tocca pulsante 2",
                                        "Presser 2 et relacher" };
                                     
const STR *const StrTestBUCMenu[] =  {"BUCMenu",  
                                      "BUCMenu",
                                      "BUCMenu",
                                      "BUCMenu",
                                      "MenuBUC"  };
                                   
const STR *const StrCalDef[] =      {"Cal Defaults",
                                     "Kalib.Voreinst",
                                     "Calib. Defecto",
                                     "Cal. di Default",
                                     "Calibr. Usine"  };
                                   
const STR *const Str_DigitalPS[] =  {"Digital P/S>",
                                     "Digital GEN.",
                                     "F/A Digital",
                                     "P/S digital",
                                     "Gn. Digital"  };
                                   
const STR *const Str_ActSettings[] = {"Act Settings>",
                                      "VE Einstell. > ",
                                      "Ajustes Act > ",
                                      "Impostaz. Att>",
                                      "Reglages Act >"  };

                                      
const STR *const Str_CurrSerialNum[] =   { "Current Serial Num",
                                           "Aktuelle Serien-Nr",
                                           "Actual Núm. Serie",
                                           "N. Serie Attuale",
                                           "No de serie actuel"  };
                                           
const STR *const Str_NewSerialNum[] =   {  "New Serial Num",
                                           "Neue Serien-Nr.",
                                           "Nuevo Núm. Serie",
                                           "Nuovo N. Serie",
                                           "Nouv. No de serie"  };
 
const STR *const Str_ResetWeldCounter[]   = {"Reset Weld Counter? ",
                                           "Reset Zykluszähler?",
                                           "Reset cont. Ciclos",
                                           "Cancella Contacicli",
                                           "Reset Compteur Cycles? "  };
                                           
const STR *const Str_Secretfunc[]        = {  "Secret Function",
                                            "Geheime Funktion",
                                            "Función secreta",
                                            "Funzione Segreta",
                                            "Fonction cachee"  };
                                            
const STR *const Str_Exec[]            = { "       Executed    ", 
                                           "      Ausgeführt   ",                      
                                           "       Ejecutado   ",                      
                                           "       Eseguito    ",                      
                                           "       Executé     " };                                            

const STR *const Str_CurrDate[] =   {  "Current Date",
                                       "Aktuelles Datum",
                                       "Fecha actual",
                                       "Dati Attuali",
                                       "Date actuelle"  };
                                        
const STR *const Str_NewDate[] =   {  "New Date",
                                      "Neues Datum",
                                      "Fecha nueva",
                                      "Nuovi Dati",
                                      "Nouvelle date"  };
                                       
const STR *const Str_CurrTime[] =   {  "Current Time",
                                       "Aktuelle Zeit",
                                       "Tiempo actual",
                                       "Tempo Attuale",
                                       "Heure actuelle"  };
                                        
const STR *const Str_NewTime[] =   {  "New Time",
                                      "Neue Zeit",
                                      "Tiempo nuevo",
                                      "Nuovo Tempo",
                                      "Nouvelle heure"  };
                                       
const STR *const StrInvalidEntry[] =  { "Invalid Entry",
                                        "Eintrag ungültig",
                                        "Entrada Invalida",
                                        "Ingresso non valido",
                                        "Erreur d'entrée"  };
                                           
const STR *const StrEnterPass[] =  {    "Enter Password",
                                        "Passwort eingeben",
                                        "Entrar contraseña",
                                        "Inserisci Password",
                                        "Entrer mot de passe"  };
 
const STR *const StrConfirmPass[] =  {  "Confirm Password",
                                        "Passwort bestätigen",
                                        "Confirm. Contraseña",
                                        "Conferma Password",
                                        "Confirmer mot de p."  };
                                        
const STR *const Str_PressStartBeep[]  = {"                     "
                                          "Press Start Switches Until Beep",
                                          "                     "
                                      "Startschalter drueck Signal hoerbar",
                                      "                     "
                                      "Pulse Puls. Inicio Hasta escuchar snal",
                                      "                     "
                                      "Premi tasto avvio Finche sente segnal",
                                      "                     "
                                      "Enf. Boutons Start Jusqu'au bip sonore"};
                                      
/****************---WARNING!!!!!---*************/
/* Don't Change spacing between following texts*/

const STR *const  QVGATestBuffer1[] = {
                                      "Run   =              Seek =           Clear  =          Store  =",
                                      "Betrieb =        Suchen =          Clear  =        Speichern=",
                                      "Ejecutar=       Buscar =         Borrar =          Guardar =",
                                      "Esegui =         Cerca =         Cancella =        Salva =",                       
                                      "Executer=      Chercher=       Effacer =       Enregistrer="};

const STR *const Str_XScale[]       = {"X SCALE",
                                       "X-SKALA",
                                       "ESCAL X",
                                       "SCALA X",
                                       "ECH. X"};


const STR *const Str_Column[]   =     { "Column",
                                        "Spalte",
                                        "Columna",
                                        "Colonna",
                                        "Colonne"  };                                   
                                       

const STR *const StrColumn1[]   =    { "Column1",
                                       "Spalte1",
                                       "Columna1",
                                       "Colonna1",
                                       "Colonne1"  };

const STR *const StrColumn2[]   =    { "Column2",
                                       "Spalte2",
                                       "Columna2",
                                       "Colonna2",
                                       "Colonne2"  };

const STR *const StrColumn3[]   =    { "Column3",
                                       "Spalte3",
                                       "Columna3",
                                       "Colonna3",
                                       "Colonne3"  };

const STR *const StrColumn4[]   =    { "Column4",
                                       "Spalte4",
                                       "Columna4",
                                       "Colonna4",
                                       "Colonne4"  };

const STR *const Str_WldRsltSetup[]= { "Weld Results Setup",
                                       "Setup Schweißungen",
                                       "Config. Resultado",
                                       "Config. risult. Sald.",
                                       "Config rapports"  };
   
const STR *const Str_ScrnAlign[]   = { "Screen Alignment",
                                       "Bild. Einstellung",
                                       "Alinear pantalla",
                                       "Allineamento Screen",
                                       "Alignement ecran"  };
                                       
const STR *const Str_Retract[]     = { "Retract",
                                       "rückgängig",
                                       "Replegar",
                                       "Ritorna",
                                       "Retraction"  };
                                       
const STR *const Str_Reenter[]      = { "Reenter Value",
                                        "Neu Wert eing",
                                        "Reintr. Valor",
                                        "Valore del rientro",
                                        "Resaisir val."  };

const STR *const StrReplace_Col[]   = { "   Replace it ?",
                                        "   Ersetzen?   ",
                                        "   Reemplazar? ",
                                        "   Sostituire? ",
                                        "   Remplacer?  "  };

const STR *const Str_Selected[]     = { "Already Selected.",
                                        "Schon ausgewaehlt",
                                        "Todo seleccionado",
                                        "Già selezionato.",
                                        "Deja Selectionné"  };

const STR *const Str_Resonance[]     = { "Resonance",
                                         "Resonanz",
                                         "Resonanc.",
                                         "Risonanza",
                                         "Resonn."  };

const STR *const StrTesting[] = {     "Testing",
                                      "Testing",
                                      "Testing",
                                      "Testing",
                                      "Testing"  };

const STR *const StrSpecials[] = {    "Specials",
                                      "Specials",
                                      "Specials",
                                      "Specials",
                                      "Specials"  };

const STR *const StrReleaseBeep[]  = { "Release Beeper",
                                       "Release Beeper",
                                       "Release Beeper",
                                       "Release Beeper",
                                       "Release Beeper"  };

const STR *const Str_WriteIn1[]  = {   "WriteIn Field1 =",
                                       "Schre in Feld1 =",
                                       "Escr. Campo1   =",
                                       "WriteIn Field1 =",
                                       "Saisie ds Chp1 ="  };

const STR *const Str_WriteIn2[]  = {   "WriteIn Field2 =",
                                       "Schre in Feld2 =",
                                       "Escr. Campo2   =",
                                       "WriteIn Field2 =",
                                       "Saisie ds Chp2 ="  };

const STR *VerifyPresetName[] =  { "Verify",
                                   "Verify",
                                   "Verify",
                                   "Verify",
                                   "Verify" };

const STR *InfoPresetName[] =  {   "Information",
                                   "Information",
                                   "Information",
                                   "Information",
                                   "Information",  };

const STR *InfoVerifiedYes[] =  {  "Preset Verified",
                                   "Preset Verified",
                                   "Preset Verified",
                                   "Preset Verified",
                                   "Preset Verified",  };

const STR *InfoVerifiedNo[] =  {   "Preset not Verified",
                                   "Preset not Verified",
                                   "Preset not Verified",
                                   "Preset not Verified",
                                   "Preset not Verified",  };

const STR *const Str_ExecuteMsg1[] =  { "Function Executing...",
                                        "Function Executing...",
                                        "Function Executing...",
                                        "Function Executing...",
                                        "Function Executing..."  };

const STR *const Str_ExecuteMsg2[] =  { "Function Executed",
                                       "Function Executed",
                                       "Function Executed",
                                       "Function Executed",
                                       "Function Executed"  };

const STR *const Str_BransonFunc[] = { "Branson Function",
                                       "Branson Function",
                                       "Branson Function",
                                       "Branson Function",
                                       "Branson Function"  };

const STR *const Str_OverwriteAll[] = { "Overwrite Presets?",
                                        "Overwrite Presets?",
                                        "Overwrite Presets?",
                                        "Overwrite Presets?",
                                        "Overwrite Presets?",  };

const STR *const Str_SeriesF[] = { "Series F(&&)",
                                   "Series F(&&)",
                                   "Series F(&&)",
                                   "Series F(&&)",
                                   "Series F(&&)"  };

const STR *const Str_ParallelF[] = { "Parallel F(&&)",
                                     "Parallel F(&&)",
                                     "Parallel F(&&)",
                                     "Parallel F(&&)",
                                     "Parallel F(&&)"  };
                                        
const STR *const Str_SVDelay[] =   { "Ext Start Dly",
                                     "Ext Start Dly",
                                     "Ext Start Dly",
                                     "Ext Start Dly",
                                     "Ext Start Dly"  };
                                     
const STR *const Str_FactDefault[]= {"Factory Defaults",
                                     "Factory Defaults",
                                     "Factory Defaults",
                                     "Factory Defaults",
                                     "Factory Defaults" };

const STR *const Str_Autorefresh[]= {"Auto Refresh",
                                     "Auto Refresh",
                                     "Auto Refreshs",
                                     "Auto Refresh",
                                     "Auto Refresh" };


const STR *const Str_ViewGraphs[]= {"View Graphs>",
                                    "View Graphs>",
                                    "View Graphs>",
                                    "View Graphs>",
                                    "View Graphs>" };
