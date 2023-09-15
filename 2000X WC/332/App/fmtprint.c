/* $Header:   L:/pvcs/1000/psos332/archives/app/FMTPRINT.C_v   1.6   17 Aug 1998 10:43:34   bbarrows  $ */
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
/****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: fmtprint.c

 ----------------------------- REVISIONS ------------------------------------

 Rev # Date     Author Description
 ----- -------- ------ ------------------------------------------------------
 0     09-14-96 GertR  Initial
 1.00  02-13-97 GertR  Corrected compiler-round error.
 1.05  07-21-97 PaulG  Removed memset, replace with for loop.
 1.6   08-17-98 BJB    Modified so SPrintf() is re-entrant.
*/
                                                    
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "graphs.h"

struct fmt_data {
    SINT8   format;
    SINT8   lead_0;
    SINT8   lead_0_finished;
    SINT8   sign;
    SINT8   vor_komma;
    SINT8   nach_komma;
    SINT8   komma_flag;
    };

SINT16 GetFormat(const SINT8*, struct fmt_data *STRFormat);
float GetMaxComp(float i_source);
SINT16 PrintInt(SINT32 i_source, SINT8* pc_buf, SINT16 si_prec, struct fmt_data *STRFormat);
SINT16 PrintFloat(float f_source, SINT8* pc_buf, struct fmt_data *STRFormat);

SINT16 SPrintf(SINT8* pc_buf, const SINT8* pc_format,...){
void *pv_parameter;
SINT16 FormatSize;
SINT8 *pc_source;
SINT16 SINumber = 0;
SINT32 i_source;
float f_source;
struct fmt_data STRFormat;

    pv_parameter = (SINT8*)&pc_format + sizeof(SINT8*);
    for(;*pc_format;){
        if(*pc_format != '%'){
            *pc_buf++ = *pc_format++;       /* no format just copy */
            STRFormat.format = 0;
            SINumber++;
        }
        else{
            FormatSize = GetFormat(pc_format, &STRFormat);      /* set format flags */
        }
        switch(STRFormat.format){
            case 0          :       break;                  /* no format just copy */
            case 's'        :   /* string conversion */
                            pc_source = *(SINT8 **)pv_parameter;
                            (SINT8*)pv_parameter += sizeof(SINT8*);
                            while(*pc_source){
                                *pc_buf++ = *pc_source++;
                                SINumber++;
                            }
                            pc_format += FormatSize;
                            break;
            case 'i'        :
            case 'u'        :
            case 'd'        :       i_source = *(int *)pv_parameter;
                            ((int*)pv_parameter)++;
                            pc_buf += PrintInt(i_source,
                                    pc_buf, STRFormat.vor_komma, &STRFormat);
                            pc_format += FormatSize;
                            break;
            case 'f'        :   /* f_source = *(float*)pv_parameter;*/
                            f_source = *(double*)pv_parameter;
                            /* ((float*)pv_parameter)++; */
                            ((double*)pv_parameter)++;
                            pc_buf += PrintFloat(f_source, pc_buf, &STRFormat);
                            pc_format += FormatSize;

                            break;
            default         :       pc_format += FormatSize;
                            break;

        }/* switch.. */
    }/* for(;*pc_format;pc_format++) */
    *pc_buf = 0;    /* Terminator */
    return(SINumber);       /* number of chars printed */
}/* SINT16 SPrintf(char* pc_buf, const char* pc_format,...) */


SINT16 GetFormat(const SINT8* pc_format, struct fmt_data *STRFormat){
SINT8 number;
    number = 1;
    pc_format++;
    STRFormat->lead_0 = 0;                   /* reset flags */
    STRFormat->lead_0_finished = 0;
    STRFormat->sign = 0;
    STRFormat->vor_komma = 0;
    STRFormat->nach_komma = 0;
    STRFormat->komma_flag = 0;       /* 0 vor, 1 nach */
    while(!isalpha(*pc_format)){    /* while no format letter */
        switch(*pc_format){                     /* decode flags, precision... */
            case '0':   /* leading 0s */
                        if(!STRFormat->lead_0_finished){
                            STRFormat->lead_0 = 1;
                            break;
                        }
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                        STRFormat->lead_0_finished = 1;
                        if(STRFormat->komma_flag == 0){
                            STRFormat->vor_komma *= 10;
                            STRFormat->vor_komma += *pc_format - '0';
                        }
                        else{
                            STRFormat->nach_komma *= 10;
                            STRFormat->nach_komma += *pc_format - '0';
                        }
                        break;
            case '.':       STRFormat->komma_flag = 1;
                        STRFormat->lead_0_finished = 1;
                        break;
            case '+':       /* print sign */
                        STRFormat->sign = 1;
                        break;
            default :   break;
        }/* switch(*pc_format) */
        pc_format++;    /* next flag */
        number++;
    }
    STRFormat->format = *pc_format;
    return(number+1);
}

float GetMaxComp(float i_source){
double df_compare = 10.;
    while( df_compare < i_source) df_compare *= 10.;
    return(df_compare / 10.);
}

SINT16 PrintInt(SINT32 i_source, SINT8* pc_buf, SINT16 si_prec, struct fmt_data *STRFormat){
SINT16 i_counter, ii, SIActPrec;
SINT8 c_mem[16], *pc_mem;
UINT16 i;

    for(i = 0; i < 16; i++){
      c_mem[i] = 0;
    }
    pc_mem = (SINT8*)&c_mem[14];    /* init pointer to end of string */
    if(STRFormat->lead_0)
        for(ii=0; ii < si_prec; ii++) *(pc_buf + ii) = '0';
    else
        for(ii=0; ii < si_prec; ii++) *(pc_buf + ii) = ' ';
                                /* init */
    if(i_source < 0){
        *pc_buf++ = '-';
        i_counter = 1;
        i_source *= -1;
    }
    else if(STRFormat->sign){
        *pc_buf++ = '+';
        i_counter = 1;
    }
    else i_counter = 0;
    if(i_source == 0) *pc_mem-- = '0';
    while(i_source > 0){
        *pc_mem-- = (i_source % 10) + '0';
//              *(pc_buf+ si_prec - i_counter - 1) =
//                                                                                      (i_source % 10) + '0';
        i_source /= 10;
//              i_counter ++;
    }/* while.. */
    SIActPrec = (SINT16)((char*)&c_mem[14] - pc_mem);
    if(SIActPrec > si_prec){
        pc_mem++;
        while(*pc_mem){
            *pc_buf++ = *pc_mem++;
        }
        i_counter += SIActPrec;
    }
    else{
        pc_mem = (SINT8*)&c_mem[14];            /* init pointer to end of string */
        pc_buf += si_prec - 1;
        while (*pc_mem){
            *pc_buf-- = *pc_mem--;
        }
        i_counter += si_prec;
    }
    return(i_counter);
}/* SINT16 PrintInt(SINT32 i_source, SINT8* pc_buf, SINT16 si_prec) */


SINT16 PrintFloat(float f_source, SINT8* pc_buf, struct fmt_data *STRFormat){
SINT32 i_source;
SINT16 si_prec, ii, si_output;
SINT32  i_frac = 10;
static float f_buffer;
    i_source = (SINT32)f_source;
    f_buffer = f_source;
    si_prec = STRFormat->vor_komma - STRFormat->nach_komma - 1;
    si_output = PrintInt(i_source, pc_buf, si_prec, STRFormat);
    pc_buf += si_output;
    *pc_buf++ = '.';
    si_output++;
    f_source -= i_source; /* get fraction */
    f_buffer = f_source;
    si_prec = STRFormat->nach_komma;
    if(si_prec > 0){
        STRFormat->sign = 0;
        STRFormat->lead_0 = 1;
        for(ii=0;ii < si_prec;ii++){ 
            f_source *= 10.;
            f_buffer = f_source;
        }

        f_source += (float)0.01;
                // rounding problem while casting from float to int
        f_buffer = f_source;
        i_frac = (SINT32)(f_source);    
        
        if(i_frac < 0) i_frac *= -1;
        si_output += PrintInt(i_frac, pc_buf, si_prec, STRFormat);
    }
    return(si_output);
}
