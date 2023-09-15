/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\pollio.c_v   1.1   Apr 06 1999 14:01:52   lmarkure  $ */
/* @(#) pSOSystem/68K V2.2.2: configs/pollio.c (std) 3.22 98/02/11 19:19:23 */
/***********************************************************************/
/*                                                                     */
/*   MODULE:  pollio.c                                                 */
/*   DATE:    98/02/11                                                 */
/*   PURPOSE: Routines for serial I/O before pREPC can be run          */
/*                                                                     */
/*---------------------------------------------------------------------*/
/*                                                                     */
/*           Copyright 1991 - 1996, Integrated Systems, Inc.           */
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

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version
 1.1   04/06/99 LAM     added TRUE/FALSE define, deleted multiple defined
                        prototypes
 
*/

#include <types.h>
#include <stdarg.h>
#include "bsp.h"
#include <bspfuncs.h>
#include <apdialog.h>

#define Disable_Ints() splx(MAX_ILEV)

/*---------------------------------------------------------------------*/
/* Symbol Definitions                                                  */
/*---------------------------------------------------------------------*/
#define NL           0x0A
#define CR           0x0D
#define BSP          0x08
#define CTRLZ        0x1A
#define RUBOUT       0x7F
#define DEFAULT     -1
#define DEFAULT_P    6      /* default precision */

/*---------------------------------------------------------------------*/
/* Input buffer                                                        */
/*---------------------------------------------------------------------*/
#define INP_LEN 100
#define TRUE 1
#define FALSE 0
static char  inp_buff[INP_LEN];   /* Input buffer */
static UCHAR inp_cnt;             /* # of chars currently in buffer */

/*---------------------------------------------------------------------*/
/* This structure is used to store information obtained from parsing a */
/* format specifier.                                                   */
/*---------------------------------------------------------------------*/
typedef struct
    {
    long width;            /* field width */
    long precision;        /* precision specifier */
    ULONG count;           /* character count */
                           /* BOOLEAN flags with default values */
    UCHAR space;           /* FALSE */
    UCHAR right;           /* TRUE */
    UCHAR alter;           /* FALSE */
    UCHAR plus;            /* FALSE */
    UCHAR zero;            /* FALSE */
    UCHAR mod;             /* process modifier */
    UCHAR type;            /* conversion type */
    } FORMAT;

/*---------------------------------------------------------------------*/
/* Buffer structure - used to set up the formatted output.             */
/*---------------------------------------------------------------------*/
#define BUFFSIZE 60
typedef struct
    {
    UCHAR buff[BUFFSIZE];     /* data buffer */
    UCHAR *ptr;               /* ptr to current position in buffer */
    UCHAR *end;               /* last position in buffer */
    } BUFFER;

/*---------------------------------------------------------------------*/
/* Function Prototypes                                                 */
/*---------------------------------------------------------------------*/

extern ULONG SerialPollConsts(ULONG);
extern UCHAR SerialPollConin(void);
extern void  SerialPollConout(UCHAR);

static void  strout(FORMAT *f_flags, UCHAR *str, long len);
static char *percent(char *format, FORMAT *f_flags, va_list *arg_pt);
static void  copy(void *pt, void *str, long str_len);
ULONG Print(char *format, ...);

/***********************************************************************/
/*        copy: Copy memory                                            */
/*                                                                     */
/*      INPUTS: dstp = pointer to destination                          */
/*              srcp = pointer to source                               */
/*              count = number of bytes to copy                        */
/*                                                                     */
/***********************************************************************/
static void copy(void *dstp, void *srcp, long count)
{
char *dst, *src;

dst = (char *)dstp;
src = (char *)srcp;
while (count--)
   *dst++ = *src++;
}

/***********************************************************************/
/*       getch: Get a character from console, waiting if necessary     */
/*                                                                     */
/*     RETURNS: Value of character                                     */
/*       NOTES: 1. Handles backspaces                                  */
/*              2. Doesn't echo characters or update the input buffer  */
/*                 (unless character is backspace)                     */
/*                                                                     */
/***********************************************************************/
static UCHAR getch(void)
{
UCHAR c;
ULONG ivec, old_mode;

for (;;)
    {
    /*-----------------------------------------------------------------*/
    /* Get a character when it is typed in.  Translate linefeed to CR. */
    /*-----------------------------------------------------------------*/
    ivec = Disable_Ints();
    SerialPollOn();
    while (SerialPollConsts(0) == 0);
    c = SerialPollConin() & 0x7F;
    SerialPollOff();
    (void)splx(ivec);
    if (c == NL) c = CR;

    /*-----------------------------------------------------------------*/
    /* Handle backspace                                                */
    /*-----------------------------------------------------------------*/
    if ((c == BSP) || (c == RUBOUT))
        {
        if (inp_cnt > 0)
            {
            Print("\b \b");
            inp_cnt--;
            }
        }

    /*-----------------------------------------------------------------*/
    /* Don't allow the input buffer to overflow.                       */
    /*-----------------------------------------------------------------*/
    else if (inp_cnt >= INP_LEN)
        {
        ivec = Disable_Ints();
        SerialPollOn();
        SerialPollConout(7);
        SerialPollOff();
        (void)splx(ivec);
        }

    /*-----------------------------------------------------------------*/
    /* Skip control characters (other than backspace and CR)           */
    /*-----------------------------------------------------------------*/
    else if ((c <= CTRLZ) && (c != CR))
        continue;

    /*-----------------------------------------------------------------*/
    /* Otherwise just return the character                             */
    /*-----------------------------------------------------------------*/
    else
        return c;
    }
}

/***********************************************************************/
/*    get_line: Get a line of input                                    */
/*                                                                     */
/*     OUTPUTS: inp_buff[] and inp_cnt are updated                     */
/*                                                                     */
/***********************************************************************/
static void get_line(void)
{
UCHAR c;
ULONG ivec, old_mode;

inp_cnt = 0;
while ((c = getch()) != CR)
    {
    inp_buff[inp_cnt++] = c;
    ivec = Disable_Ints();
    SerialPollOn();
    SerialPollConout(c);
    SerialPollOff();
    (void)splx(ivec);
    }
inp_buff[inp_cnt] = 0;
ivec = Disable_Ints();
SerialPollOn();
SerialPollConout('\n');
SerialPollConout('\r');
SerialPollOff();
(void)splx(ivec);
}

/***********************************************************************/
/* read_string: Read a string from the input                           */
/*                                                                     */
/*     RETURNS: number of characters in the string                     */
/*     OUTPUTS: *dest_ptr contains the null-terminated string.         */
/*                                                                     */
/***********************************************************************/
static UCHAR read_string(char *dest_ptr)
{
char *src_ptr, count;

get_line();
count = 0;
src_ptr = inp_buff;
while (*dest_ptr++ = *src_ptr++)
    count++;

return count;
}

/***********************************************************************/
/*    read_num: Interpret a string as a number                         */
/*                                                                     */
/*      INPUTS: base = 10 or 16                                        */
/*     OUTPUTS: *val_ptr = New value (if function returns TRUE)        */
/*                                                                     */
/*     RETURNS: TRUE if a new number was entered.                      */
/*       NOTES: Allows leading $ or 0x if base is 16.  Number string   */
/*              is delimited by a null or a space.                     */
/*                                                                     */
/***********************************************************************/
static UCHAR read_num(char *ptr, UCHAR base, ULONG *val_ptr)
{
ULONG value;
UCHAR c, hex;

value = 0;
while (*ptr == ' ') ptr++;  /* Skip leading spaces */
hex = (base == 16);

if (*ptr == 0) return 0;

/*---------------------------------------------------------------------*/
/* If hex, allow leading $ or 0x.                                      */
/*---------------------------------------------------------------------*/
if (hex)
    {
    if (*ptr == '$')
        ptr++;
    else if ((*ptr == '0') && ((ptr[1] == 'x') || (ptr[1] == 'X')))
        ptr = ptr + 2;
    }

/*---------------------------------------------------------------------*/
/* Run through the string, adding the value represented by each        */
/* character to the total.                                             */
/*---------------------------------------------------------------------*/
while (*ptr)
    {
    c = *ptr++;
    if ((c >= '0') && (c <= '9'))
        c -= '0';
    else if (hex && (c >= 'A') && (c <= 'F'))
        c = c - 'A' + 10;
    else if (hex && (c >= 'a') && (c <= 'f'))
        c = c - 'a' + 10;
    else
        {
        Print("Invalid number\a\n");
        return 0;
        }
    if (hex)
        value = (value << 4) + c;
    else
        value = value * 10 + c;
    }

*val_ptr = value;
return 1;
}

/***********************************************************************/
/*      Prompt: Display the current value of a parameter, and allow    */
/*              user to change it.                                     */
/*                                                                     */
/*      INPUTS: string = ptr to descriptive string                     */
/*              ptype =  type of parameter (DECIMAL,   ULONG           */
/*                                          HEX,       ULONG           */
/*                                          FLAG,      UCHAR           */
/*                                          CHAR,      UCHAR           */
/*                                          STRING,    UCHAR[]         */
/*                                          IP)        ULONG           */
/*              parm_ptr = ptr to parameter value                      */
/*                                                                     */
/*     OUTPUTS: *parm_ptr contains updated value of parameter          */
/*                                                                     */
/***********************************************************************/
void Prompt(char *string, PARM_TYPE ptype, void *parm_ptr)
{
UCHAR rc;
char line[80], *line_ptr, *seg_ptr;
ULONG temp, ip_byte[4];
int i;
UCHAR *ptr;

Print(string);
switch (ptype)
    {
    case DECIMAL:
        Print(" [%d] ", *((ULONG *)parm_ptr));
        get_line();
        if (read_num(inp_buff, 10, &temp))
           *((ULONG *)parm_ptr) = temp;
        break;

    case HEX:
        Print(" [%X] ", *((ULONG *)parm_ptr));
        get_line();
        if (read_num(inp_buff, 16, &temp))
           *((ULONG *)parm_ptr) = temp;
        break;

    case FLAG:
        Print(" [%c] ", (*((UCHAR *)parm_ptr) ? 'Y' : 'N'));
        if (rc = read_string(line))
            {
            if (rc != 1)
                Print("Invalid response\007\n");
            else if ((line[0] == 'Y') || (line[0] == 'y'))
               *((UCHAR *)parm_ptr) = 1;
            else if ((line[0] == 'N') || (line[0] == 'n'))
               *((UCHAR *)parm_ptr) = 0;
            else
                Print("Invalid response\007\n");
            }
        break;

    case CHAR:
        Print(" [%c] ", *((UCHAR *)parm_ptr));
        if (rc = read_string(line))
            {
            if (rc != 1)
                Print("Invalid response\007\n");
            else
               *((UCHAR *)parm_ptr) = line[0];
            }
        break;

    case STRING:
        Print(" [%s] ", (UCHAR *)parm_ptr);
        if (read_string(line))
            {
            line_ptr = line;
            ptr = (UCHAR *)parm_ptr;
            while (*ptr++ = *line_ptr++);
            }
        break;

    case IP:
        Print(" [%I] ", *((ULONG *)parm_ptr));

        if (read_string(line))
            {
            line_ptr = line;
            for (i = 3; i >= 0; i--)
                {
                seg_ptr = line_ptr;
                while ((*line_ptr) && (*line_ptr != '.'))
                    line_ptr++;
                if ((*line_ptr == '.') && (line_ptr[1]))
                   *line_ptr++ = 0;
                if (!read_num(seg_ptr, 10, &ip_byte[i]) || (ip_byte[i] > 255))
                    {
                    Print("Invalid IP address\n");
                    return;
                    }
                }
           *((ULONG *)parm_ptr) = (ip_byte[3] << 24)
                                  + (ip_byte[2] << 16)
                                  + (ip_byte[1] << 8)
                                  + ip_byte[0];
            }
        break;
    }
}

/***********************************************************************/
/*                                                                     */
/*   This subset of printf() supports the following conversion types:  */
/*                                                                     */
/*      %d, %i - output number as a signed decimal (this implementa-   */
/*               tion only uses the low 16 bits of the argument)       */
/*      %o - output number as an unsigned octal number                 */
/*      %x, %X - output number as unsigned hexadecimal                 */
/*      %c - output a single character                                 */
/*      %s - ouput a string                                            */
/*                                                                     */
/*   In addition, the normal width and precision specifiers may be     */
/*   used.                                                             */
/*                                                                     */
/***********************************************************************/

/***********************************************************************/
/*        putb: Output a character                                     */
/*                                                                     */
/*      INPUTS: ch = character to output                               */
/*                                                                     */
/***********************************************************************/
static void putb(UCHAR ch)
{
ULONG ivec, old_mode;
ivec = Disable_Ints();
SerialPollOn();
SerialPollConout(ch);
if (ch == '\n')
    SerialPollConout('\r');
SerialPollOff();
(void)splx(ivec);
}

/***********************************************************************/
/*    isdigit: Determine whether a character is an ASCII decimal digit */
/*                                                                     */
/*      INPUTS: c = character to check                                 */
/*                                                                     */
/*     RETURNS: TRUE if "c" is a decimal digit                         */
/*                                                                     */
/***********************************************************************/
static UCHAR isdigit(char c)
{
return (c >= '0') && (c <= '9');
}

/***********************************************************************/
/*     charout: Output a character                                     */
/*                                                                     */
/*      INPUTS: f_flags = ptr to format data structure                 */
/*              arg_pt = ptr to next argument in list                  */
/*                                                                     */
/***********************************************************************/
static void charout(FORMAT *f_flags, va_list *arg_pt)
{
UCHAR cbuf[4];

*((UCHAR *) &cbuf[0]) = (UCHAR) va_arg((*arg_pt), ULONG);
strout(f_flags, cbuf, 1);
}

/***********************************************************************/
/*      strlen: returns length of a string                             */
/*                                                                     */
/*      INPUTS: str = ptr to string being measured                     */
/*                                                                     */
/***********************************************************************/
static ULONG strlen(UCHAR *str)
{
long i;

for(i = 0; *str++; i++);

return i;
}

/***********************************************************************/
/*   stringout: Output a string                                        */
/*                                                                     */
/*      INPUTS: f_flags = ptr to format data structure                 */
/*              arg_pt = ptr to next argument in list                  */
/*                                                                     */
/*        NOTE: Strings longer than 100 bytes are truncated!           */
/*                                                                     */
/***********************************************************************/
static void stringout(FORMAT *f_flags, va_list *arg_pt)
{
UCHAR *str, str_buff[102];
UCHAR *pt;
ULONG str_len;

pt = &str_buff[101];
str = (UCHAR *)va_arg((*arg_pt), int);
str_len = strlen(str);
if (str_len > f_flags->precision && f_flags->precision != 0)
    str_len = f_flags->precision;
if (str_len > 100) str_len = 100;

*(pt) = '\0';
pt = pt - str_len;
copy(pt, str, (long)str_len);

strout(f_flags, pt, (long)strlen(pt));
}

/***********************************************************************/
/*      decout: Output a value as a decimal number                     */
/*                                                                     */
/*      INPUTS: f_flags = ptr to format data structure                 */
/*              arg_pt = ptr to next argument in list                  */
/*                                                                     */
/***********************************************************************/
static void decout(FORMAT *f_flags, va_list *arg_pt)
{
UCHAR dec_buff[20], *pt, neg;
long val, s_length;
ULONG t_count;

t_count = 0;
pt = &dec_buff[19];
neg = FALSE;

/*---------------------------------------------------------------------*/
/* Get the value to output from the argument list.                     */
/*---------------------------------------------------------------------*/
if (f_flags->mod == 'h')
    val = (short) va_arg((*arg_pt), long);
else
    val = (long) va_arg((*arg_pt), long);

/*---------------------------------------------------------------------*/
/* Null terminate the output string.  Not included in output count.    */
/*---------------------------------------------------------------------*/
*(pt--) = '\0';

/*---------------------------------------------------------------------*/
/* If val is negative, set the true flag and multiply by -1.           */
/*---------------------------------------------------------------------*/
if (val < 0)
    {
    neg = TRUE;
    val = -val;
    }

/*---------------------------------------------------------------------*/
/* While val is greater than zero, output characters to the string     */
/* from right to left.                                                 */
/*---------------------------------------------------------------------*/
do
    {
    long i, tmp;

    /*-----------------------------------------------------------------*/
    /* The next two statements cause problems on the 68000, since that */
    /* processor does not have a 32-bit divide instruction.  They are  */
    /* replaced by functionally equivalent routines.                   */
    /*-----------------------------------------------------------------*/

    /*  *(pt--) = val % 10 + '0';  */
    tmp = val;


    while (tmp >= 10000) tmp -= 10000;
    while (tmp >= 1000) tmp -= 1000;
    while (tmp >= 100) tmp -= 100;

    while ((tmp -= 10) >= 10);
    if (tmp < 0) tmp += 10;
    *(pt--) = (UCHAR) (tmp + '0');

    /*   val /= (short)10;        */
    if (val >= 10)
        {
        for (i = 0; val >= 100000; i += 10000) val -= 100000;
        for (     ; val >=  10000; i +=  1000) val -= 10000;
        for (     ; val >=   1000; i +=   100) val -= 1000;
        for (     ; val >=    100; i +=    10) val -= 100;
        for (     ; val >=     10; i++) val -= 10;
        val = i;
        }
    else
        val = 0;

    t_count++;
    } while (val != 0);

while (t_count < f_flags->precision)
    {
    *(pt--) = '0';
    t_count++;
    }

/*---------------------------------------------------------------------*/
/* Next check to see if the 0 flag was used in the format and if the   */
/* current count is less than the specified field width.  If TRUE then */
/* fill in the leading zeros.  Temporarily leave room in the field for */
/* an optional plus or minus sign.                                     */
/*---------------------------------------------------------------------*/
pt++;
if (f_flags->zero)
    {
    s_length = strlen(pt);
    while (f_flags->width > s_length + 1)
        {
       *(--pt) = '0';
        s_length += 1;
        }
    }

/*---------------------------------------------------------------------*/
/* Add leading plus or minus sign, and/or leading zero if needed.      */
/*---------------------------------------------------------------------*/
if (neg)
   *(--pt) = '-';
else if (f_flags->plus)
   *(--pt) = '+';
else if (f_flags->space)
   *(--pt) = ' ';
else if ((f_flags->zero) && (f_flags->width > s_length))
   *(--pt) = '0';
f_flags->precision = DEFAULT;
strout(f_flags, pt, (long)strlen(pt));
}

/***********************************************************************/
/*      hexout: Output a value as a hexadecimal number                 */
/*                                                                     */
/*      INPUTS: f_flags = ptr to format data structure                 */
/*              arg_pt = ptr to next argument in list                  */
/*                                                                     */
/***********************************************************************/
static void hexout(FORMAT *f_flags, va_list *arg_pt)
{
UCHAR c, *pt, d[16], hexbuff[16];
ULONG val, t_count;
long s_length;
USHORT i;

t_count = 0;

/*---------------------------------------------------------------------*/
/* Set up the array of hex digits used in conversion.                  */
/*---------------------------------------------------------------------*/
for (i = 0; i <= 9; i++)
    d[i] = '0' + i;
c = (f_flags->type == 'X') ? 'A' : 'a';
for (i = 10; i <= 15; i++)
    d[i] = c++;

/*---------------------------------------------------------------------*/
/* Obtain the value to be output.                                      */
/*---------------------------------------------------------------------*/
if (f_flags->mod == 'h')
    val = (USHORT) va_arg((*arg_pt), ULONG);
else
    val = (ULONG) va_arg((*arg_pt), ULONG);

/*---------------------------------------------------------------------*/
/* Null terminate string then process the value.                       */
/*---------------------------------------------------------------------*/
pt = &hexbuff[15];
*(pt--) = '\0';

/*---------------------------------------------------------------------*/
/* Process the value                                                   */
/*---------------------------------------------------------------------*/
do
    {
    *(pt--) = d[val & 0xf];
    t_count++;
    } while (val >>= 4);

while (t_count < f_flags->precision)
    {
    *(pt--) = '0';
    t_count++;
    }

/*---------------------------------------------------------------------*/
/* Next check to see if the 0 flag was used in the format and if the   */
/* current count is less than the specified field width.  If TRUE then */
/* fill in the leading zeros.  Temporarily leave room in the field for */
/* an optional plus or minus sign.                                     */
/*---------------------------------------------------------------------*/
pt++;

if (f_flags->zero)
    {
    s_length = strlen(pt);
    if (f_flags->alter)
        while (f_flags->width > s_length+2)
            {
            *(--pt) = '0';
            s_length += 1;
            }
    else
        while (f_flags->width > s_length)
            {
            *(--pt) = '0';
            s_length += 1;
            }
    }

/*---------------------------------------------------------------------*/
/* If the "alternate form" flag is set, add 0x or 0X to the front of   */
/* the string.                                                         */
/*---------------------------------------------------------------------*/
if (f_flags->alter)
    {
    if (f_flags->type == 'x')
        *(--pt) = 'x';
    else
        *(--pt) = 'X';
    *(--pt) = '0';
    }
f_flags->precision = DEFAULT;
strout(f_flags, pt, (long)strlen(pt));
}

/***********************************************************************/
/*      strout: Output a formatted string, adding fill characters and  */
/*              field justification.                                   */
/*                                                                     */
/*      INPUTS: f_flags = ptr to format data structure                 */
/*              str = ptr to string                                    */
/*              len = length of string                                 */
/*                                                                     */
/***********************************************************************/
static void strout(FORMAT *f_flags, UCHAR *str, long len)
{
long size;
ULONG i, count = 0;
UCHAR pad = ' ';

/*---------------------------------------------------------------------*/
/* Check for a NULL string.                                            */
/*---------------------------------------------------------------------*/
if (len == 0)
    str = (UCHAR *)"(null)";

/*---------------------------------------------------------------------*/
/* Calculate the field width.                                          */
/*---------------------------------------------------------------------*/
f_flags->count += len;
size = (f_flags->width < len ) ? len : f_flags->width;

/*---------------------------------------------------------------------*/
/* If the right justified field is set, fill the leading characters    */
/* with blanks.                                                        */
/*---------------------------------------------------------------------*/
if (f_flags->right)
    {
    for (i = size - len; i > 0; i--)
        {
        putb(pad);
        count++;
        }
    size = len;
    }

/*---------------------------------------------------------------------*/
/* Output the string.                                                  */
/*---------------------------------------------------------------------*/
while (*str != '\0' && len > 0)
    {
    putb(*str++);
    len--;
    size--;
    }

/*---------------------------------------------------------------------*/
/* If left justified, it may be necessary to pad end of the string.    */
/*---------------------------------------------------------------------*/
for (i = size - len; i > 0; i--)
    {
    putb(pad);
    count++;
    }

f_flags->count += count;
}

/***********************************************************************/
/*      Print: Format output and send it to the console                */
/*                                                                     */
/*      INPUTS: format = ptr to format string                          */
/*              additional inputs as specified by *format.             */
/*                                                                     */
/*     RETURNS: # of characters output                                 */
/*        NOTE: Format strings are explained in the header at the      */
/*              top of this module.                                    */
/*                                                                     */
/***********************************************************************/
ULONG Print(char *format, ...)
{
ULONG ip_addr;
FORMAT f_flags;
BUFFER buf;
va_list arg_pt;

buf.ptr = buf.buff;
buf.end = &buf.buff[BUFFSIZE-1];

va_start(arg_pt, format);

f_flags.count = 0;
if (format == NULL)
    format = (char *)"(null)";

/*---------------------------------------------------------------------*/
/* Process characters in 'format ' string until null terminator is     */
/* reached.  If the character is not a '%' then simply print it.       */
/* Otherwise it will require further processing.                       */
/*---------------------------------------------------------------------*/
while (*format != '\0')
    {
    if (*format != '%')
        {
        putb(*format++);
        f_flags.count++;
        }
    else
        {
        /*-------------------------------------------------------------*/
        /* Set up the fields in the format structure.                  */
        /*-------------------------------------------------------------*/
        format++;
        format = percent(format, &f_flags, &arg_pt);

        /*-------------------------------------------------------------*/
        /* Continue to process based on the format type:               */
        /*  d,i   -   signed decimal                                   */
        /*  x,X   -   unsigned hexadecimal                             */
        /*  c     -   print least significant character of int         */
        /*  s     -   argument taken to be (char *) pointer to string  */
        /*  %     -   A % is printed. No argument is converted.        */
        /*  I     -   IP address (dd.dd.dd.dd)                         */
        /*-------------------------------------------------------------*/
        switch (f_flags.type)
            {
            case 'd':
            case 'i':
                decout(&f_flags, &arg_pt);
                break;
            case 'x':
            case 'X':
                hexout(&f_flags, &arg_pt);
                break;
            case 'c':
                charout(&f_flags, &arg_pt);
                break;
            case 's':
                stringout(&f_flags, &arg_pt);
                break;
            case '%':
                putb('%');
                f_flags.count++;
                break;
            case 'I':
                ip_addr = va_arg((arg_pt), long);
                Print("%d.%d.%d.%d", (ip_addr >> 24) & 0xFF,
                 (ip_addr >> 16) & 0xFF,
                 (ip_addr >> 8)  & 0xFF,
                 ip_addr & 0xFF);
                break;
            default:
                break;
            }
        }
    }

return f_flags.count;
}

/***********************************************************************/
/*     percent: Interpret a conversion specification                   */
/*                                                                     */
/*      INPUTS: format = ptr to current position in format string      */
/*              arg_pt = ptr to next argument                          */
/*                                                                     */
/*     RETURNS: Ptr to next char in format string past this specifier. */
/*     OUTPUTS: *f_flags = filled in with format specification         */
/*                                                                     */
/***********************************************************************/
static char *percent(char *format, FORMAT *f_flags, va_list *arg_pt)
{
UCHAR p_flag = FALSE;

/*---------------------------------------------------------------------*/
/*  Initialize the f_flag structure with the default values.           */
/*---------------------------------------------------------------------*/
f_flags->width = DEFAULT;
f_flags->precision = DEFAULT_P;
f_flags->right = TRUE;
f_flags->plus = FALSE;
f_flags->alter = FALSE;
f_flags->zero = FALSE;
f_flags->space = FALSE;
f_flags->type = '\0';
f_flags->mod = '\0';

/*---------------------------------------------------------------------*/
/* Process the flags that may exists between the '%' and the start of  */
/* the width specification.  The following flags may exist:            */
/*                                                                     */
/*      '-'    to set left justified                                   */
/*      '+'    result will always have sign (+ or -)                   */
/*      space  for leading space                                       */
/*      '#'    for alternate form                                      */
/*      '0'    use leading zeros instead of spaces.                    */
/*                                                                     */
/* The sequence of these flags is important.                           */
/*---------------------------------------------------------------------*/
if (*format == '-')
    {
    f_flags->right = FALSE;
    format++;
    }

if (*format == '+')
    {
    f_flags->plus = TRUE;
    format++;
    }

if (*format == ' ')
    {
    if (f_flags->plus == FALSE)
        f_flags->space = TRUE;
    format++;
    }

if (*format == '#')
    {
    f_flags->alter = TRUE;
    format++;
    }

if (*format == '0')
    {
    if (f_flags->right)
        f_flags->zero = TRUE;
    format++;
    }

/*---------------------------------------------------------------------*/
/* Process the width specification of the format.  The width can be    */
/* specified by the next value in the arg_pt list.  If the next        */
/* character is '*' then get the width from arg_pt with a call to the  */
/* va_arg() macro.                                                     */
/*                                                                     */
/* The width can also be specified as a value in the format.   In this */
/* case the width is specified by a decimal number.                    */
/*---------------------------------------------------------------------*/
if (*format == '*')
    {
    f_flags->width = va_arg((*arg_pt), int);
    if (f_flags->width < 0)
        {
        f_flags->right = FALSE;
        f_flags->width = -f_flags->width;
        }
    format++;
    }
else
    {
    if (isdigit(*format))
        for (f_flags->width = 0; isdigit(*format); )
            f_flags->width = f_flags->width * 10 + *format++ - '0';
    }

/*---------------------------------------------------------------------*/
/* Process the precision field.  The same options that are allowed for */
/* the width field are permitted here.                                 */
/*---------------------------------------------------------------------*/
if (*format == '.')
    {
    p_flag = TRUE;
    format++;
    if (*format == '*')
        {
        f_flags->precision = va_arg((*arg_pt), int);
        format++;
        }
    else
        {
        f_flags->precision = 0;
        while (isdigit (*format))
            f_flags->precision = f_flags->precision * 10 + *format++ - '0';
        }
    }

/*---------------------------------------------------------------------*/
/*  Check for process modifier characters. {h, l, L}                   */
/*---------------------------------------------------------------------*/
if ((*format == 'h') || (*format == 'l') || (*format == 'L'))
    f_flags->mod = *format++;

/*---------------------------------------------------------------------*/
/* Based on the type of conversion it may be necessary to readjust the */
/* precision flag to a default value of 0.                             */
/*---------------------------------------------------------------------*/
if ((p_flag == FALSE) && (*format != 'c') && (*format != '%'))
    f_flags->precision = 0;

/*---------------------------------------------------------------------*/
/* The final step is to read in the conversion type.                   */
/*---------------------------------------------------------------------*/
f_flags->type = *format++;
return format;
}

