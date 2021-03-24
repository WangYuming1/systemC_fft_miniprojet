#include <systemc.h>
#ifndef __FFT_H__
#define __FFT_H__
#define L 23

/* #define W {\
	{1, 0}, \
	{0.7071067812, -0.7071067812}, \
	{0, -1}, \
	{-0.7071067812, -0.7071067812}\
} */
/* #define W {\
	{67108863, 0}, \
	{47453133, -47453133}, \
	{0, -67108864}, \
	{-47453133, -47453133}\
}

typedef struct complex_s complex_t;

struct complex_s {
	sc_int<L> real;
	sc_int<L> imag;
};
 */


typedef struct  {
	sc_int<L> real;
	sc_int<L> imag;
} complex_in;

typedef struct  {
	sc_int<L+4> real;
	sc_int<L+4> imag;
} complex_out;
void fft(complex_in in[8], complex_out out[8]);

#endif
