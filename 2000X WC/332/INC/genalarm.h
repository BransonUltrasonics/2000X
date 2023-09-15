/* $Header:   D:/SWLab/VMdb/2000Series/INC/GENALARM.H_V   1.40   May 23 2007 16:57:26   nhahmed  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
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

   Filename: genalarm.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      1.0         10/11/96        PhilJ      Initial Version
      1.1         10/16/96        PhilJ      Deleted function FormatAlarmBuffers
      1.2         10-24-96        BEKymer    Added alarms to GENERALALARM3MASK
      1.3         10-30-96        PhilJ      Added alarms to SYSTEMFAULT1MASK
      1.4         11-14-96        PhilJ      Added GeneralAlarm #81&82 to mask.
      1.5         01-23-97        PhilJ      Added SYSFAULTABORTMASK1 and
                                             GENALARMABORTMASK2.
      1.6         02-28-97        PhilJ      Added TESTOVERLOADMASK,SEEKOVERLOADMASK,
                                             and PSOVERLOADMASK.
      1.7         04-08-97        PhilJ      Changed GENERALARM2MASK and WARNINGMASK.
      1.8         04-23-97        PhilJ      Added BIT4 to SYSFAULTABORTMASK1.
      1.9         04-29-97        BEKymer    Added W7 to warning mask
      2.0         05-05-97        PhilJ      Deleted BIT7 in GENERALALARMABORTMASK2.
      2.1         05-09-97        PhilJ      Added OVERLOADMASK define.
      2.2         05-13-97        PhilJ      Chngd OVERLOADMASK define. Added
                                             Prototypes.
      3.0         05-29-97        LAM        chged warning mask.       
      4.1.16      07-21-97        BEKymer    Added define for new groups
      1.17        10-03-97        BEKymer    New mask-REJECTALARMMASK
      1.18        01-20-98        PaulG      Modified mask EQUIPMENTFAILUREMASK
                                             and SETUPGROUP9MASK.
      1.19        02-03-98        BEKymer    Changed CYCLEMODIFIEDMASK to 0x0000fffe
                                             NOCYCLEMASK to 0x00001fda
      1.20        02-11-98        BEKymer    Changed SETUPGROUP9MASK to 0x0ff0e
      1.21        02-17-98        BEKymer    Changed CYCLEMODIFIEDMASK to
                                             add CM16-CM20 alarms
      1.22        04-28-98        BEKymer    Change mask for SETUPGROUP9MASK
                                             Remove SYSFAULTABORTMASK1 and
                                             GENALARMABORTMASK2
                                             Change WARNINGMASK
      1.23        05-20-98        BEKymer    Updated masks to reflect moving
                                             PR15 to CM21    DCS # 2494
                                             EQUIPMENTFAILUREMASK->0x01effffe
                                             to add EQ24
      1.24        05-27-98        BEKymer    Change mask for SETUPGROUP4
      1.25        06-18-98        BEKymer    Change mask for CALIBRATEMASK and
                                             EQUIPMENTFAILUREMASK
      1.26        11-23-98        BEKymer    Change mask for CYCLEMODIFIEDMASK
      1.27        05-25-99        OFI        Changed MASKs for F product allarms
      1.28        04-23-01        LAM        Change mask SETUPGROUP2MASK to accommodate 
                                             new alarm - SE46
      1.29        04-06-04        VSharma    Modified NOCYCLEMASK,OVERLOADMASK,WARNINGMASK &
                                              SETUPGROUP10MASK to accommodate Ver9.00 alarms. 
      1.30        05-03-04        VSharma    Modified SETUPGROUP10MASK.
      1.31        07-29-04        JOY        Modified SETUPGROUP10MASK.//SE296.
      1.32        08-06-04        BEKymer    Removed SE169 from SEG6 (Missing part Setup)
      1.33        10-24-05        Bwadia     Enabled +R and -R PMC alarms in REJECTBITRESULTMASK
      1.34        10-28-05        Bwadia     Enabled sequencing in setup mask 10
      1.35        11-22-05        Bwadia     Enabled SBL alarms in REJECTBITRESULTMASK
      1.36        12-20-05        Bwadia     USB alarm mask enabled. Modified for
                                             tracker issue 4029
      1.37        02-14-06        Bwadia     Enabled +-PMC Reject alarms not in reject groups
                                             to be counted
      1.38        01-18-07        NHAhmed    Changed the SETUPGROUP10MASK.             
      1.39        03-27-07        NHAhmed    Changed the SETUPGROUP4MASK,SETUPGROUP8MASK,
                                             SETUPGROUP9MASK Setup Alarms.
      1.40        05-23-07        NHAhmed    Changed the SETUPGROUP10MASK.
*/

/*------------------------------ INCLUDES ----------------------------------*/

#include "alarms.h"

/*-------------------------------- DEFINES ---------------------------------*/                           

#define SUSPECTBITRESULTMASK  0x00007ffe
#define REJECTBITRESULTMASK   0x00787ffe    /* Reject limits only         */
#define REJECTALARMMASK       0x00780000    /* Alarms grouped with reject */
#define OVERLOADMASK          0x000005fe
#define NOCYCLEMASK           0x0000ffda
#define EQUIPMENTFAILUREMASK  0x0bf7ffde
#define CYCLEMODIFIEDMASK     0x00fffffe
#define WARNINGMASK           0x00000ffe
#define CALIBRATEMASK         0x00000000

#define SETUPGROUP1MASK       0x0ffffffe
#define SETUPGROUP2MASK       0x0ffffffe
#define SETUPGROUP3MASK       0x0fffff3e
#define SETUPGROUP4MASK       0x0ffffffe
#define SETUPGROUP5MASK       0x0ffffffe
#define SETUPGROUP6MASK       0x0ffffdfe
#define SETUPGROUP7MASK       0x0e7ffffe
#define SETUPGROUP8MASK       0x0ffffffe
#define SETUPGROUP9MASK       0x003fff5e
#define SETUPGROUP10MASK      0x00000ffe


/*--  These masks need to be figured out again (07-21-97)  --*/

//#define SYSFAULTABORTMASK1    0x003FA13C
//#define GENALARMABORTMASK2    0x00000040


#define BIT33  BIT1
#define BIT34  BIT2
#define BIT35  BIT3  
#define BIT36  BIT4 
#define BIT37  BIT5  
#define BIT38  BIT6  
#define BIT39  BIT7  
#define BIT40  BIT8  
#define BIT41  BIT9  
#define BIT42  BIT10 
#define BIT43  BIT11 
#define BIT44  BIT12 
#define BIT45  BIT13 
#define BIT46  BIT14 
#define BIT47  BIT15 
#define BIT48  BIT16 	
#define BIT49  BIT17 
#define BIT50  BIT18 
#define BIT51  BIT19 
#define BIT52  BIT20 
#define BIT53  BIT21 
#define BIT54  BIT22 
#define BIT55  BIT23 
#define BIT56  BIT24
#define BIT57  BIT25
#define BIT58  BIT26
#define BIT59  BIT27
               
#define BIT65  BIT1
#define BIT66  BIT2
#define BIT67  BIT3  
#define BIT68  BIT4 
#define BIT69  BIT5  
#define BIT70  BIT6  
#define BIT71  BIT7  
#define BIT72  BIT8  
#define BIT73  BIT9  
#define BIT74  BIT10 
#define BIT75  BIT11 
#define BIT76  BIT12 
#define BIT77  BIT13 
#define BIT78  BIT14 
#define BIT79  BIT15 
#define BIT80  BIT16 	
#define BIT81  BIT17 
#define BIT82  BIT18 
#define BIT83  BIT19 
#define BIT84  BIT20 
#define BIT85  BIT21 
#define BIT86  BIT22 
#define BIT87  BIT23 
#define BIT88  BIT24
#define BIT89  BIT25
#define BIT90  BIT26
#define BIT91  BIT27

#define BIT97  BIT1
#define BIT98  BIT2
#define BIT99  BIT3  
#define BIT100 BIT4 
#define BIT101 BIT5  
#define BIT102 BIT6  
#define BIT103 BIT7  
#define BIT104 BIT8  
#define BIT105 BIT9  
#define BIT106 BIT10 
#define BIT107 BIT11 
#define BIT108 BIT12 
#define BIT109 BIT13 
#define BIT110 BIT14 
#define BIT111 BIT15 
#define BIT112 BIT16 	
#define BIT113 BIT17 
#define BIT114 BIT18 
#define BIT115 BIT19 
#define BIT116 BIT20 
#define BIT117 BIT21 
#define BIT118 BIT22 
#define BIT119 BIT23 
#define BIT120 BIT24
#define BIT121 BIT25
#define BIT122 BIT26
#define BIT123 BIT27

#define BIT129 BIT1
#define BIT130 BIT2
#define BIT131 BIT3  
#define BIT132 BIT4 
#define BIT133 BIT5  
#define BIT134 BIT6  
#define BIT135 BIT7  
#define BIT136 BIT8  
#define BIT137 BIT9  
#define BIT138 BIT10 
#define BIT139 BIT11 
#define BIT140 BIT12 
#define BIT141 BIT13 
#define BIT142 BIT14 
#define BIT143 BIT15 
#define BIT144 BIT16 	
#define BIT145 BIT17 
#define BIT146 BIT18 
#define BIT147 BIT19 
#define BIT148 BIT20 
#define BIT149 BIT21 
#define BIT150 BIT22 
#define BIT151 BIT23 
#define BIT152 BIT24
#define BIT153 BIT25
#define BIT154 BIT26
#define BIT155 BIT27

#define BIT161 BIT1
#define BIT162 BIT2
#define BIT163 BIT3  
#define BIT164 BIT4 
#define BIT165 BIT5  
#define BIT166 BIT6  
#define BIT167 BIT7  
#define BIT168 BIT8  
#define BIT169 BIT9  
#define BIT170 BIT10 
#define BIT171 BIT11 
#define BIT172 BIT12 
#define BIT173 BIT13 
#define BIT174 BIT14 
#define BIT175 BIT15 
#define BIT176 BIT16 	
#define BIT177 BIT17 
#define BIT178 BIT18 
#define BIT179 BIT19 
#define BIT180 BIT20 
#define BIT181 BIT21 
#define BIT182 BIT22 
#define BIT183 BIT23 
#define BIT184 BIT24
#define BIT185 BIT25
#define BIT186 BIT26
#define BIT187 BIT27

#define BIT193 BIT1
#define BIT194 BIT2
#define BIT195 BIT3  
#define BIT196 BIT4 
#define BIT197 BIT5  
#define BIT198 BIT6  
#define BIT199 BIT7  
#define BIT200 BIT8  
#define BIT201 BIT9  
#define BIT202 BIT10 
#define BIT203 BIT11 
#define BIT204 BIT12 
#define BIT205 BIT13 
#define BIT206 BIT14 
#define BIT207 BIT15 
#define BIT208 BIT16 	
#define BIT209 BIT17 
#define BIT210 BIT18 
#define BIT211 BIT19 
#define BIT212 BIT20 
#define BIT213 BIT21 
#define BIT214 BIT22 
#define BIT215 BIT23 
#define BIT216 BIT24
#define BIT217 BIT25
#define BIT218 BIT26
#define BIT219 BIT27

#define BIT225 BIT1
#define BIT226 BIT2
#define BIT227 BIT3  
#define BIT228 BIT4 
#define BIT229 BIT5  
#define BIT230 BIT6  
#define BIT231 BIT7  
#define BIT232 BIT8  
#define BIT233 BIT9  
#define BIT234 BIT10 
#define BIT235 BIT11 
#define BIT236 BIT12 
#define BIT237 BIT13 
#define BIT238 BIT14 
#define BIT239 BIT15 
#define BIT240 BIT16 	
#define BIT241 BIT17 
#define BIT242 BIT18 
#define BIT243 BIT19 
#define BIT244 BIT20 
#define BIT245 BIT21 
#define BIT246 BIT22 
#define BIT247 BIT23 
#define BIT248 BIT24
#define BIT249 BIT25
#define BIT250 BIT26
#define BIT251 BIT27

#define BIT257 BIT1
#define BIT258 BIT2
#define BIT259 BIT3  
#define BIT260 BIT4 
#define BIT261 BIT5  
#define BIT262 BIT6  
#define BIT263 BIT7  
#define BIT264 BIT8  
#define BIT265 BIT9  
#define BIT266 BIT10 
#define BIT267 BIT11 
#define BIT268 BIT12 
#define BIT269 BIT13 
#define BIT270 BIT14 
#define BIT271 BIT15 
#define BIT272 BIT16 	
#define BIT273 BIT17 
#define BIT274 BIT18 
#define BIT275 BIT19 
#define BIT276 BIT20 
#define BIT277 BIT21 
#define BIT278 BIT22 
#define BIT279 BIT23 
#define BIT280 BIT24
#define BIT281 BIT25
#define BIT282 BIT26
#define BIT283 BIT27

#define BIT289 BIT1
#define BIT290 BIT2
#define BIT291 BIT3  
#define BIT292 BIT4 
#define BIT293 BIT5  
#define BIT294 BIT6  
#define BIT295 BIT7  
#define BIT296 BIT8  
#define BIT297 BIT9  
#define BIT298 BIT10 
#define BIT299 BIT11 
#define BIT300 BIT12 
#define BIT301 BIT13 
#define BIT302 BIT14 
#define BIT303 BIT15 
#define BIT304 BIT16 	
#define BIT305 BIT17 
#define BIT306 BIT18 
#define BIT307 BIT19 
#define BIT308 BIT20 
#define BIT309 BIT21 
#define BIT310 BIT22 
#define BIT311 BIT23 
#define BIT312 BIT24
#define BIT313 BIT25
#define BIT314 BIT26
#define BIT315 BIT27



/*--------------------------- FUNCTION PROTOTYPES --------------------------*/




