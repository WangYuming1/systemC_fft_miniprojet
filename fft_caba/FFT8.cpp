#include "FFT8.h"
#include<stdio.h>
#include"fft.h"

using std::cout;
using std::endl;
#define L 23

sc_int<27> W[4][4]={ 67108863, 0, 
	47453133, -47453133, 
	0, -67108864, 
	-47453133, -47453133};


// #define W {\
// 	{67108863, 0}, \
// 	{47453133, -47453133}, \
// 	{0, -67108864}, \
// 	{-47453133, -47453133}\
// }

void FFT8::COMPORTEMENT(){
    sc_int < 23 > data_in[16];                         //to store the data received from the source
    sc_int < 27 >  data_out[16];                        //to send out the data calculated 
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

//complex_t weights[4] = W;

// void but(complex_t *weight,
// 					complex_t *in0,
// 					complex_t *in1,
// 					complex_t *out0,
// 					complex_t *out1)
// {
//       out0->real = (in0->real + ((in1->real * weight->real) - (in1->imag * weight->imag)));
//       out0->imag = (in0->imag + ((in1->real * weight->imag) + (in1->imag * weight->real)));
//       out1->real = (in0->real - ((in1->real * weight->real) - (in1->imag * weight->imag)));
//       out1->imag = (in0->imag - ((in1->real * weight->imag) + (in1->imag * weight->real)));
// }


template <unsigned int N> void papillon(  sc_int<N> Wr, sc_int<N> Wi, 
                sc_int<N> ar, sc_int<N> ai,
                sc_int<N> br, sc_int<N> bi,
                sc_int<N+2> &new_ar, sc_int<N+2> &new_ai,
                sc_int<N+2> &new_br, sc_int<N+2> &new_bi)
// le papillon sur 2 echantillons complexes peut ramener l'energie
// des 2 echantillons sur une seule composante (reelle ou imaginaire)
// d'un seul echantillon en sortie,
// donc si entree sur N bits, sortie sur N+2
// Mais si l'on cascade S etages, si entree sur N bits,
// sortie sur N+S+1 bits (2^S entrees combinent au pire toute leur
// energie sur une unique composante d'un echantillon de sortie, 
// donc il faudra recadrer!
    {
      sc_int<2*N> mult_brr;
      sc_int<2*N> mult_bri;
      sc_int<2*N> mult_bir;
      sc_int<2*N> mult_bii;
      
      sc_int<N> mult_brr_trunc;
      sc_int<N> mult_bri_trunc;
      sc_int<N> mult_bir_trunc;
      sc_int<N> mult_bii_trunc;
      
      mult_brr = (br * Wr);
      mult_bri = (br * Wi);
      mult_bir  = (bi * Wr);
      mult_bii  = (bi * Wi);

      mult_brr_trunc =  mult_brr.range(2*N-2,N-1)+mult_brr[N-2];

      // car les W sont codes sur 1 bit de signe et N-1 bits pour la partie fractionnaire
      // et ont rajoute le bit de precision pour l'arrondi
      mult_bri_trunc =  mult_bri.range(2*N-2,N-1)+mult_bri[N-2];
      mult_bir_trunc =  mult_bir.range(2*N-2,N-1)+mult_bir[N-2];
      mult_bii_trunc =  mult_bii.range(2*N-2,N-1)+mult_bii[N-2];
            
      new_ar = (ar + ((mult_brr_trunc) - (mult_bii_trunc)));
      new_ai = (ai + ((mult_bri_trunc) + (mult_bir_trunc)));
      new_br = (ar - ((mult_brr_trunc) - (mult_bii_trunc)));
      new_bi = (ai - ((mult_bri_trunc) + (mult_bir_trunc)));               
    }


void fft(complex_t in[8], complex_t out[8]) 
{
	complex_t stage1[8], stage2[8];

	// First stage
	// but(&weights[0], &in[0], &in[4], &stage1[0], &stage1[1]);
	// but(&weights[0], &in[2], &in[6], &stage1[2], &stage1[3]);
	// but(&weights[0], &in[1], &in[5], &stage1[4], &stage1[5]);
	// but(&weights[0], &in[3], &in[7], &stage1[6], &stage1[7]);
    papillon<23> ( W[0][0].range(26,4), W[0][1].range(26,4), 
        in[0].real, in[0].imag, in[4].real, in[4].imag,
        stage1[0].real, stage1[0].imag, stage1[1].real, stage1[1].imag);

    papillon<23> (W[0][0].range(26,4), W[0][1].range(26,4), 
        in[2].real, in[2].imag, in[6].real, in[6].imag,
        stage1[2].real, stage1[2].imag, stage1[3].real, stage1[3].imag);

    papillon<23> (W[0][0].range(26,4), W[0][1].range(26,4), 
        in[1].real, in[1].imag, in[5].real, in[5].imag,
        stage1[4].real, stage1[4].imag, stage1[5].real, stage1[5].imag);

    papillon<23> (W[0][0].range(26,4), W[0][1].range(26,4), 
        in[3].real, in[3].imag, in[7].real, in[7].imag,
        stage1[6].real, stage1[6].imag, stage1[7].real, stage1[7].imag);

	// Second stage
	// but(&weights[0], &stage1[0], &stage1[2], &stage2[0], &stage2[2]);
	// but(&weights[2], &stage1[1], &stage1[3], &stage2[1], &stage2[3]);
	// but(&weights[0], &stage1[4], &stage1[6], &stage2[4], &stage2[6]);
	// but(&weights[2], &stage1[5], &stage1[7], &stage2[5], &stage2[7]);

    papillon<25> (W[0][0].range(26,2), W[0][1].range(26,2), 
        stage1[0].real, stage1[0].imag, stage1[2].real, stage1[2].imag,
        stage2[0].real, stage2[0].imag, stage2[2].real, stage2[2].imag);

    papillon<25> (W[2][0].range(26,2), W[2][1].range(26,2), 
        stage1[1].real, stage1[1].imag, stage1[3].real, stage1[3].imag,
        stage2[1].real, stage2[1].imag, stage2[3].real, stage2[3].imag);

    papillon<25> (W[0][0].range(26,2), W[0][1].range(26,2), 
        stage1[4].real, stage1[4].imag, stage1[6].real, stage1[6].imag,
        stage2[4].real, stage2[4].imag, stage2[6].real, stage2[6].imag);

    papillon<25> (W[2][0].range(26,2), W[2][1].range(26,2), 
        stage1[5].real, stage1[5].imag, stage1[7].real, stage1[7].imag,
        stage2[5].real, stage2[5].imag, stage2[7].real, stage2[7].imag);
                
	// Etape 3
	// but(&weights[0], &stage2[0], &stage2[4], &out[0], &out[4]);
	// but(&weights[1], &stage2[1], &stage2[5], &out[1], &out[5]);
	// but(&weights[2], &stage2[2], &stage2[6], &out[2], &out[6]);
	// but(&weights[3], &stage2[3], &stage2[7], &out[3], &out[7]);

    papillon<27> (W[0][0].range(26,0), W[0][1].range(26,0), 
        stage2[0].real, stage2[0].imag, stage2[4].real, stage2[4].imag,
        out[0].real, out[0].imag, out[4].real, out[4].imag);

    papillon<27> (W[1][0].range(26,2), W[1][1].range(26,0), 
        stage2[1].real, stage2[1].imag, stage2[5].real, stage2[5].imag,
        out[1].real, out[1].imag, out[5].real, out[5].imag);

    papillon<27> (W[2][0].range(26,2), W[2][1].range(26,0), 
        stage2[2].real, stage2[2].imag, stage2[6].real, stage2[6].imag,
        out[2].real, out[2].imag, out[6].real, out[6].imag);

    papillon<27> (W[3][0].range(26,2), W[3][1].range(26,0), 
        stage2[3].real, stage2[3].imag, stage2[7].real, stage2[7].imag,
        out[3].real, out[3].imag, out[7].real, out[7].imag);
}