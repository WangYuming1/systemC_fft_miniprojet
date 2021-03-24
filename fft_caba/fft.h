#ifndef __FFT_H__ 
#define __FFT_H__ 
#define L 23

struct complex_s {							// complex_s for the valor put in the fft function, the input is 23bits.
	sc_int< L > real;
	sc_int< L > imag;
};		

struct complex_t {							// complex_t for the valor out the fft function, the output is 27bits.
	sc_int< L+4 > real;
	sc_int< L+4 > imag;

};
void fft(complex_s in[8], complex_t out[8]);

#endif
