/* $Header:   K:\APPS\PVCS Pro\PSS68K.222\CONFIGS\STD\math.h_v   1.0   Mar 29 1999 13:51:00   ofingere  $ */
/* @(#) pSOSystem/68K V2.2.2: include/math.diab.h (&U&) 2.4 97/05/08 11:33:01 */
/*---------------------------------------------------------------------*/
/* Diab math.h file with errno changed to be compatible with pSOSystem.*/
/*---------------------------------------------------------------------*/
/* --------------------------------- REVISIONS -------------------------

 Rev # Date     Author  Description
 ===== ======== ======  =============================================
 1.0   03/26/99 OFI     Original Version

*/

#ifndef __Imath
#define __Imath

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef HUGE_VAL
typedef union _h_val {
	unsigned long	i[2];
	double		d;
} _h_val;

extern _h_val		__huge_val;

#define HUGE_VAL	__huge_val.d
#endif

extern double
	acos(double),
	asin(double),
	atan(double),
	atan2(double, double),
	cos(double),
	sin(double),
	tan(double),
	cosh(double),
	sinh(double),
	tanh(double),
	exp(double),
	frexp(double, int *),
	ldexp(double, int),
	log(double),
	log10(double),
	modf(double, double *),
	pow(double, double),
	sqrt(double),
	ceil(double),
	fabs(double),
	floor(double),
	fmod(double, double);

#if !defined(__STRICT_ANSI__) && !defined(_POSIX_SOURCE)
extern double
 	erf(double),
	erfc(double),
	gamma(double),
	hypot(double, double),
	j0(double), j1(double), jn(int, double),
	y0(double), y1(double), yn(int, double);

#ifndef errno
unsigned long *errno_addr(void);
#define errno (*(int *)(errno_addr()))
#endif

extern int signgam;

extern int matherr(struct exception *);

struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

#define HUGE	HUGE_VAL

#define DOMAIN		1
#define SING		2
#define OVERFLOW	3
#define UNDERFLOW	4
#define TLOSS		5
#define PLOSS		6

#define M_E		2.7182818284590452353603
#define M_LOG2E		1.4426950408889634073599
#define M_LOG10E	0.4342944819032518276511
#define M_LN2		0.6931471805599453094172
#define M_LN10		2.3025850929940456840180
#define M_PI		3.1415926535897932384626
#define M_PI_2		1.5707963267948966192313
#define M_PI_4		0.7853981633974483096157
#define M_1_PI		0.3183098861837906715377
#define M_2_PI		0.6366197723675813430755
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.4142135623730950488016
#define M_SQRT1_2	0.7071067811865475244008

#endif /* __STRICT_ANSI__ */
#ifdef	__cplusplus
}
#endif
#endif
