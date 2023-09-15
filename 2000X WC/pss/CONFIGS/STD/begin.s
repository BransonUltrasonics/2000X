* $Header:   K:\APPS\PVCS Pro\PSS68k.222\configs\std\begin.s_v   1.2   Apr 05 1999 13:38:52   lmarkure  $ *
* @(#) pSOSystem/68K V2.2.2: configs/68k/begin.s (diab) 3.18 97/05/05 11:16:04
*************************************************************************
*                                                                       *
*   MODULE:  begin.s                                                    *
*   DATE:    97/05/05                                                   *
*   PURPOSE: RESET VECTOR, ENTRY POINT FOR pSOSystem                    *
*                                                                       *
*-----------------------------------------------------------------------*
*                                                                       *
*            COPYRIGHT 1991 - 1997, INTEGRATED SYSTEMS, INC.            *
*                          ALL RIGHTS RESERVED                          *
*                                                                       *
*    PERMISSION IS HEREBY GRANTED TO LICENSEES OF INTEGRATED SYSTEMS,   *
*    INC. PRODUCTS TO USE OR ABSTRACT THIS COMPUTER PROGRAM FOR THE     *
*    SOLE PURPOSE OF IMPLEMENTING A PRODUCT BASED ON INTEGRATED         *
*    SYSTEMS, INC. PRODUCTS.   NO OTHER RIGHTS TO REPRODUCE, USE,       *
*    OR DISSEMINATE THIS COMPUTER PROGRAM, WHETHER IN PART OR IN        *
*    WHOLE, ARE GRANTED.                                                *
*                                                                       *
*    INTEGRATED SYSTEMS, INC. MAKES NO REPRESENTATION OR WARRANTIES     *
*    WITH RESPECT TO THE PERFORMANCE OF THIS COMPUTER PROGRAM, AND      *
*    SPECIFICALLY DISCLAIMS ANY RESPONSIBILITY FOR ANY DAMAGES,         *
*    SPECIAL OR CONSEQUENTIAL, CONNECTED WITH THE USE OF THIS PROGRAM.  *
*                                                                       *
*-----------------------------------------------------------------------*
*                                                                       *
*    THIS MODULE CONTAINS THE CODE WHICH GOES AT THE BEGINNING OF       *
*    pSOSystem (THE RESET VECTOR AND SYSTEM ENTRY POINT).  IT ALSO      *
*    CONTAINS ROUTINE SysInitVars(), WHICH ZEROES OUT THE ".bss"        *
*    LINKER SECTION.                                                    *
*
*************************************************************************
*                                                                       *
*      Copyright (c) Branson Ultrasonics Corporation, 1995 - 99         *
*     This program is the property of Branson Ultrasonics Corporation   *
*   Copying of this software is expressly forbidden, without the prior  *
*   written consent of Branson Ultrasonics Corporation.                 *
*                                                                       *
* --------------------------------- REVISIONS -------------------------

* Rev #       Date     Author  Description
* =====       ======== ======  =============================================
* 1.0         03/26/99 OFI     Original Version
* 1.1         04/06/99 LAM     added branson copyright
* 1.2         04/29/99 LAM     fixed line1 added vector table   
* 1.2.1.0     05/02/03 SCM     Added vector definition for QVGA (#29)
* 1.2.1.0.1.0 11/29/07 BEKymer Removed vector for VFReady(#136)
*                               and vector for QvgaInt (#29)
*                                                                      
* 1.2.1.0.1.1 09/04/08 ygupta Removed vector for printer (#25).                                                                     
*************************************************************************
        XREF    _HdwInit,_InitialStackPointer
*
*------------------------------------------------------------------------
*
*                     R E S E T   V E C T O R
*
* THE VERY FIRST THING IN THE SYSTEM IS THE 68K RESET VECTOR.  IF THIS
* CODE IS PLACED IN ROM, THE CPU WILL FETCH THE INITIAL STACK POINTER
* AND PROGRAM COUNTER FROM HERE.  IF THIS CODE IS DOWNLOADED TO A
* SYSTEM VIA THE TFTP BOOTLOADER IN THE pSOSystem ROMS, THE BOOTLOADER
* ALSO USES THIS RESET VECTOR TO START THE SYSTEM RUNNING.
*------------------------------------------------------------------------
        SECTION BEGIN,,C
INITIAL_SP:
        DC.L    _InitialStackPointer       ;INITIAL STACK POINTER
        DC.L    _START                     ;INITIAL PROGRAM COUNTER
        DC.L      _BusInt                ;Vector   #2 
        DC.L      _AddInt                ;Vector   #3 
        DC.L      _IllegalInstr          ;Vector   #4 
        DC.L      _ZeroDivide            ;Vector   #5 
        DC.L      _CHKCHK2               ;Vector   #6 
        DC.L      _TRAPccTRAPv           ;Vector   #7 
        DC.L      _PrivilegeVio          ;Vector   #8 
        DC.L      _PrivilegeVio          ;Vector   #9 
        DC.L      _Vector10Int           ;Vector  #10 
        DC.L      _Vector10Int           ;Vector  #11 
        DC.L      _Vector10Int           ;Vector  #12 
        DC.L      _Vector10Int           ;Vector  #13 
        DC.L      _Vector10Int           ;Vector  #14 
        DC.L      _Vector10Int           ;Vector  #15 
        DC.L      _ReservedInt           ;Vector  #16 
        DC.L      _ReservedInt           ;Vector  #17 
        DC.L      _ReservedInt           ;Vector  #18 
        DC.L      _ReservedInt           ;Vector  #19 
        DC.L      _ReservedInt           ;Vector  #20 
        DC.L      _ReservedInt           ;Vector  #21 
        DC.L      _ReservedInt           ;Vector  #22 
        DC.L      _ReservedInt           ;Vector  #23 
        DC.L      _SpurInt               ;Vector  #24 
        DC.L      _UserInt               ;Vector  #25 
        DC.L      _KeyInt                ;Vector  #26
        DC.L      _Vector10Int           ;Vector  #27
        DC.L      _Vector10Int           ;Vector  #28
        DC.L      _Vector10Int           ;Vector  #29
        DC.L      _Vector10Int           ;Vector  #30
        DC.L      _Vector10Int           ;Vector  #31
        DC.L      _Vector10Int           ;Vector  #32
        DC.L      _Vector10Int           ;Vector  #33
        DC.L      _Vector10Int           ;Vector  #34
        DC.L      _Vector10Int           ;Vector  #35
        DC.L      _Vector10Int           ;Vector  #36
        DC.L      _Vector10Int           ;Vector  #37
        DC.L      _Vector10Int           ;Vector  #38
        DC.L      _Vector10Int           ;Vector  #39
        DC.L      _Vector10Int           ;Vector  #40
        DC.L      _Vector10Int           ;Vector  #41
        DC.L      _Vector10Int           ;Vector  #42
        DC.L      _Vector10Int           ;psos serice call
        DC.L      _Vector10Int           ;psos i/o call
        DC.L      _Vector10Int           ;psos return from interrupt
        DC.L      _Vector10Int           ;Vector  #46
        DC.L      _Vector10Int           ;Vector  #47
        DC.L      _ReservedInt           ;Vector  #48
        DC.L      _ReservedInt           ;Vector  #49
        DC.L      _ReservedInt           ;Vector  #50
        DC.L      _ReservedInt           ;Vector  #51
        DC.L      _ReservedInt           ;Vector  #52
        DC.L      _ReservedInt           ;Vector  #53
        DC.L      _ReservedInt           ;Vector  #54
        DC.L      _ReservedInt           ;Vector  #55
        DC.L      _ReservedInt           ;Vector  #56
        DC.L      _ReservedInt           ;Vector  #57
        DC.L      _ReservedInt           ;Vector  #58
        DC.L      _ReservedInt           ;Vector  #59
        DC.L      _ReservedInt           ;Vector  #60
        DC.L      _ReservedInt           ;Vector  #61
        DC.L      _ReservedInt           ;Vector  #62
        DC.L      _ReservedInt           ;Vector  #63
        DC.L      _isr_uart              ;Vector  #64
        DC.L      _UserInt               ;Vector  #65
        DC.L      _UserInt               ;Vector  #66
        DC.L      _UserInt               ;Vector  #67
        DC.L      _UserInt               ;Vector  #68
        DC.L      _UserInt               ;Vector  #69
        DC.L      _UserInt               ;Vector  #70
        DC.L      _UserInt               ;Vector  #71
        DC.L      _UserInt               ;Vector  #72
        DC.L      _UserInt               ;Vector  #73
        DC.L      _UserInt               ;Vector  #74
        DC.L      _UserInt               ;Vector  #75
        DC.L      _UserInt               ;Vector  #76
        DC.L      _UserInt               ;Vector  #77
        DC.L      _UserInt               ;Vector  #78
        DC.L      _UserInt               ;Vector  #79
        DC.L      _UserInt               ;Vector  #80
        DC.L      _UserInt               ;Vector  #81
        DC.L      _UserInt               ;Vector  #82
        DC.L      _UserInt               ;Vector  #83
        DC.L      _UserInt               ;Vector  #84
        DC.L      _UserInt               ;Vector  #85
        DC.L      _UserInt               ;Vector  #86
        DC.L      _UserInt               ;Vector  #87
        DC.L      _UserInt               ;Vector  #88
        DC.L      _UserInt               ;Vector  #89
        DC.L      _UserInt               ;Vector  #90
        DC.L      _UserInt               ;Vector  #91
        DC.L      _UserInt               ;Vector  #92
        DC.L      _UserInt               ;Vector  #93
        DC.L      _UserInt               ;Vector  #94
        DC.L      _UserInt               ;Vector  #95
        DC.L      _UserInt               ;Vector  #96
        DC.L      _UserInt               ;Vector  #97
        DC.L      _UserInt               ;Vector  #98
        DC.L      _UserInt               ;Vector  #99
        DC.L      _UserInt               ;Vector  #100
        DC.L      _UserInt               ;Vector  #101
        DC.L      _UserInt               ;Vector  #102
        DC.L      _UserInt               ;Vector  #103
        DC.L      _UserInt               ;Vector  #104
        DC.L      _UserInt               ;Vector  #105
        DC.L      _UserInt               ;Vector  #106
        DC.L      _UserInt               ;Vector  #107
        DC.L      _UserInt               ;Vector  #108
        DC.L      _UserInt               ;Vector  #109
        DC.L      _UserInt               ;Vector  #110
        DC.L      _UserInt               ;Vector  #111
        DC.L      _UserInt               ;Vector  #112
        DC.L      _UserInt               ;Vector  #113
        DC.L      _UserInt               ;Vector  #114
        DC.L      _UserInt               ;Vector  #115
        DC.L      _UserInt               ;Vector  #116
        DC.L      _UserInt               ;Vector  #117
        DC.L      _UserInt               ;Vector  #118
        DC.L      _UserInt               ;Vector  #119
        DC.L      _UserInt               ;Vector  #120
        DC.L      _UserInt               ;Vector  #121
        DC.L      _UserInt               ;Vector  #122
        DC.L      _UserInt               ;Vector  #123
        DC.L      _UserInt               ;Vector  #124
        DC.L      _UserInt               ;Vector  #125
        DC.L      _UserInt               ;Vector  #126
        DC.L      _UserInt               ;Vector  #127
        DC.L      _MsInt                 ;Vector  #128
        DC.L      _UserInt               ;Vector  #129
        DC.L      _UserInt               ;Vector  #130
        DC.L      _UserInt               ;Vector  #131
        DC.L      _UserInt               ;Vector  #132
        DC.L      _UserInt               ;Vector  #133
        DC.L      _UserInt               ;Vector  #134
        DC.L      _UserInt               ;Vector  #135
        DC.L      _UserInt               ;Vector  #136
        DC.L      _UserInt               ;Vector  #137
        DC.L      _UserInt               ;Vector  #138
        DC.L      _UserInt               ;Vector  #139
        DC.L      _UserInt               ;Vector  #140
        DC.L      _UserInt               ;Vector  #141
        DC.L      _UserInt               ;Vector  #142
        DC.L      _StoreInt              ;Vector  #143
        DC.L      _UserInt               ;Vector  #144
        DC.L      _UserInt               ;Vector  #145
        DC.L      _UserInt               ;Vector  #146
        DC.L      _UserInt               ;Vector  #147
        DC.L      _UserInt               ;Vector  #148
        DC.L      _UserInt               ;Vector  #149
        DC.L      _UserInt               ;Vector  #150
        DC.L      _UserInt               ;Vector  #151
        DC.L      _UserInt               ;Vector  #152
        DC.L      _UserInt               ;Vector  #153
        DC.L      _UserInt               ;Vector  #154
        DC.L      _UserInt               ;Vector  #155
        DC.L      _UserInt               ;Vector  #156
        DC.L      _UserInt               ;Vector  #157
        DC.L      _UserInt               ;Vector  #158
        DC.L      _UserInt               ;Vector  #159
        DC.L      _UserInt               ;Vector  #160
        DC.L      _UserInt               ;Vector  #161
        DC.L      _UserInt               ;Vector  #162
        DC.L      _UserInt               ;Vector  #163
        DC.L      _UserInt               ;Vector  #164
        DC.L      _UserInt               ;Vector  #165
        DC.L      _UserInt               ;Vector  #166
        DC.L      _UserInt               ;Vector  #167
        DC.L      _UserInt               ;Vector  #168
        DC.L      _UserInt               ;Vector  #169
        DC.L      _UserInt               ;Vector  #170
        DC.L      _UserInt               ;Vector  #171
        DC.L      _UserInt               ;Vector  #172
        DC.L      _UserInt               ;Vector  #173
        DC.L      _UserInt               ;Vector  #174
        DC.L      _UserInt               ;Vector  #175
        DC.L      _UserInt               ;Vector  #176
        DC.L      _UserInt               ;Vector  #177
        DC.L      _UserInt               ;Vector  #178
        DC.L      _UserInt               ;Vector  #179
        DC.L      _UserInt               ;Vector  #180
        DC.L      _UserInt               ;Vector  #181
        DC.L      _UserInt               ;Vector  #182
        DC.L      _UserInt               ;Vector  #183
        DC.L      _UserInt               ;Vector  #184
        DC.L      _UserInt               ;Vector  #185
        DC.L      _UserInt               ;Vector  #186
        DC.L      _UserInt               ;Vector  #187
        DC.L      _UserInt               ;Vector  #188
        DC.L      _UserInt               ;Vector  #189
        DC.L      _UserInt               ;Vector  #190
        DC.L      _UserInt               ;Vector  #191
        DC.L      _UserInt               ;Vector  #192
        DC.L      _UserInt               ;Vector  #193
        DC.L      _UserInt               ;Vector  #194
        DC.L      _UserInt               ;Vector  #195
        DC.L      _UserInt               ;Vector  #196
        DC.L      _UserInt               ;Vector  #197
        DC.L      _UserInt               ;Vector  #198
        DC.L      _UserInt               ;Vector  #199
        DC.L      _UserInt               ;Vector  #200
        DC.L      _UserInt               ;Vector  #201
        DC.L      _UserInt               ;Vector  #202
        DC.L      _UserInt               ;Vector  #203
        DC.L      _UserInt               ;Vector  #204
        DC.L      _UserInt               ;Vector  #205
        DC.L      _UserInt               ;Vector  #206
        DC.L      _UserInt               ;Vector  #207
        DC.L      _UserInt               ;Vector  #208
        DC.L      _UserInt               ;Vector  #209
        DC.L      _UserInt               ;Vector  #210
        DC.L      _UserInt               ;Vector  #211
        DC.L      _UserInt               ;Vector  #212
        DC.L      _UserInt               ;Vector  #213
        DC.L      _UserInt               ;Vector  #214
        DC.L      _UserInt               ;Vector  #215
        DC.L      _UserInt               ;Vector  #216
        DC.L      _UserInt               ;Vector  #217
        DC.L      _UserInt               ;Vector  #218
        DC.L      _UserInt               ;Vector  #219
        DC.L      _UserInt               ;Vector  #220
        DC.L      _UserInt               ;Vector  #221
        DC.L      _UserInt               ;Vector  #222
        DC.L      _UserInt               ;Vector  #223
        DC.L      _UserInt               ;Vector  #224
        DC.L      _UserInt               ;Vector  #225
        DC.L      _UserInt               ;Vector  #226
        DC.L      _UserInt               ;Vector  #227
        DC.L      _UserInt               ;Vector  #228
        DC.L      _UserInt               ;Vector  #229
        DC.L      _UserInt               ;Vector  #230
        DC.L      _UserInt               ;Vector  #231
        DC.L      _UserInt               ;Vector  #232
        DC.L      _UserInt               ;Vector  #233
        DC.L      _UserInt               ;Vector  #234
        DC.L      _UserInt               ;Vector  #235
        DC.L      _UserInt               ;Vector  #236
        DC.L      _UserInt               ;Vector  #237
        DC.L      _UserInt               ;Vector  #238
        DC.L      _UserInt               ;Vector  #239
        DC.L      _UserInt               ;Vector  #240
        DC.L      _UserInt               ;Vector  #241
        DC.L      _UserInt               ;Vector  #242
        DC.L      _UserInt               ;Vector  #243
        DC.L      _UserInt               ;Vector  #244
        DC.L      _UserInt               ;Vector  #245
        DC.L      _UserInt               ;Vector  #246
        DC.L      _UserInt               ;Vector  #247
        DC.L      _UserInt               ;Vector  #248
        DC.L      _UserInt               ;Vector  #249
        DC.L      _UserInt               ;Vector  #250
        DC.L      _UserInt               ;Vector  #251
        DC.L      _UserInt               ;Vector  #252
        DC.L      _UserInt               ;Vector  #253
        DC.L      _UserInt               ;Vector  #254
        DC.L      _UserInt               ;Vector  #255
*
        XDEF _START
_START:
        MOVE    #$2700,SR                  ;IN CASE OF 
        MOVE.L  #_InitialStackPointer,SP   ;WARM START
        JMP     _HdwInit

        .text
*
*************************************************************************
*  SysInitVars: ZERO OUT STATIC VARIABLES                               *
*                                                                       *
*       SYNTAX: void SysInitVars(void)                                  *
*        NOTES: 1. THIS SHOULD BE CALLED AS EARLY AS POSSIBLE, BECAUSE  *
*                  IF THE STACK IS LOCATED IN ".bss", IT WILL BE        *
*                  CLEARED!                                             *
*                                                                       *
*************************************************************************
        XDEF    _SysInitVars
_SysInitVars:
        XREF    _bss_start
        XREF    _bss_end
        MOVE.L  (SP),A1                    ;A1: RETURN ADDRESS
        MOVE.L  #_bss_start,A0
        MOVE.L  #_bss_end,D0
        SUB.L   #_bss_start,D0
ZEROLOOP:
        SUBQ.L  #1,D0
        BCS.S   ZEROLOOPEND
        MOVE.B  #0,(A0)+
        BRA.S   ZEROLOOP
ZEROLOOPEND:
        MOVE.L  A1,(SP)
        RTS

        END
