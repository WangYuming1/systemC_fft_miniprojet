#include "FFT8.h"
#include<stdio.h>
#include"fft.h"

using std::cout;
using std::endl;

void FFT8::COMPORTEMENT(){
    double data_in[16];                         //to store the data received from the source
    double data_out[16];                        //to send out the data calculated 
    complex_t in[8];                            //store the data received with the format complex_t
    complex_t out[8];                           //store the result by fft to send out
    data_valid_out=false;                       //initialize the signal valid and req
    data_req_out=false;
    while(1){
        data_valid_out=false;                   //in each tranfer of 8 samples, initialize the signal valid to 0 and req to 1. 
        data_req_out=true;                      
        int i=0;
        while(i<15){
            if(data_valid_in && data_req_out){  //when the src has data valid and fft is available for the data, store the data in the data_in
                data_in[i]=in_real.read();
                i++;  
                data_in[i]=in_imag.read();
                i++;
            }
            wait();
        }

        data_req_out=false;                     //after reading a set of 8 samples, set req to 0
        
        for(i=0;i<8;i++){                       // store the data to complex format
            in[i].real=data_in[i*2];
            in[i].imag=data_in[i*2+1];
        }

        fft(in,out);

        for(i=0;i<8;i++){                       //store the complex result to send out
            data_out[i*2]=out[i].real;
            data_out[i*2+1]=out[i].imag;
        }

        i=0;
        while(i<15){
            if(!data_valid_out&&(data_req_in)){ //when data is valid and the sink can read data, write the data to the port
                out_real.write(data_out[i]);
                i++;
                out_imag.write(data_out[i]);
                data_valid_out=true;            //set valid to true after writing 2 data to the port
                i++;
            }  
            wait();
            data_valid_out=false;               //set the valid to 0 after the next pos_clk
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