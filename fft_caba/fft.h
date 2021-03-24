#ifndef __FFT_H__ 
#define __FFT_H__ 
#define L 23
// #define W {\
// 	{1, 0}, \
// 	{0.7071067812, -0.7071067812}, \
// 	{0, -1}, \
// 	{-0.7071067812, -0.7071067812}\
// }
// W[0][0] = 67108863; //2^26-1
//         W[0][1] = 0;
//         W[1][0] = 47453133;
//         W[1][1] = -47453133;
//         W[2][0] = 0;
//         W[2][1] = -67108864;//-2^26
//         W[3][0] = -47453133; 
//         W[3][1] = -47453133;

// #define W {\
// 	{67108863, 0}, \
// 	{47453133, -47453133}, \
// 	{0, -67108864}, \
// 	{-47453133, -47453133}\
// }

//typedef struct complex_s complex_t;

struct complex_s {
	sc_int< L > real;
	sc_int< L > imag;
};

struct complex_t {
	sc_int< L+4 > real;
	sc_int< L+4 > imag;

};
void fft(complex_s in[8], complex_t out[8]);

#endif
