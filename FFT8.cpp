#include "FFT8.h"
#include<stdio.h>
#include"fft.h"

using std::cout;
using std::endl;

void FFT8::COMPORTEMENT(){
    float data_in[16];
    float data_out[16];
    complex_t in[8];
    complex_t out[8];

    while(1){
        i=0;
        while(i<16){
            if(FFT8_IN.num.available>0){
                data_in[i]=FFT8_IN.read();
                i++;
            }
            else
                cout<<"pas assez data";
            wait();
        }
        for(i=0;i<8;i++){
            in[i].real=data_in[i*2];
            in[i].imag=data_in[i*2+1];
        }
        fft(in,out);
        for(i=0;i<8;i++){
            data_out[i*2]=out[i].real;
            data_out[i*2+1]=out[i].imag;
        }
         while(i<16){
            if(FFT8_OUT.num_free>0){
                data_out[i]=FFT8_OUT.read();
                i++;
            }
            else
                cout<<"pas assez place";
            wait();
        } 

    }
}


complex_t weights[4] = W;

void but(complex_t *weight,
					complex_t *in0,
					complex_t *in1,
					complex_t *out0,
					complex_t *out1)
{
      out0->real = (in0->real + ((in1->real * weight->real) - (in1->imag * weight->imag)));
      out0->imag = (in0->imag + ((in1->real * weight->imag) + (in1->imag * weight->real)));
      out1->real = (in0->real - ((in1->real * weight->real) - (in1->imag * weight->imag)));
      out1->imag = (in0->imag - ((in1->real * weight->imag) + (in1->imag * weight->real)));
}


void fft(complex_t in[8], complex_t out[8]) 
{
	complex_t stage1[8], stage2[8];

	// First stage
	but(&weights[0], &in[0], &in[4], &stage1[0], &stage1[1]);
	but(&weights[0], &in[2], &in[6], &stage1[2], &stage1[3]);
	but(&weights[0], &in[1], &in[5], &stage1[4], &stage1[5]);
	but(&weights[0], &in[3], &in[7], &stage1[6], &stage1[7]);

	// Second stage
	but(&weights[0], &stage1[0], &stage1[2], &stage2[0], &stage2[2]);
	but(&weights[2], &stage1[1], &stage1[3], &stage2[1], &stage2[3]);
	but(&weights[0], &stage1[4], &stage1[6], &stage2[4], &stage2[6]);
	but(&weights[2], &stage1[5], &stage1[7], &stage2[5], &stage2[7]);
                
	// Etape 3
	but(&weights[0], &stage2[0], &stage2[4], &out[0], &out[4]);
	but(&weights[1], &stage2[1], &stage2[5], &out[1], &out[5]);
	but(&weights[2], &stage2[2], &stage2[6], &out[2], &out[6]);
	but(&weights[3], &stage2[3], &stage2[7], &out[3], &out[7]);
}