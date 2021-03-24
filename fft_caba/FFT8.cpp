#include "FFT8.h"
#include<stdio.h>
#include"fft.h"

using std::cout;
using std::endl;
#define L 23

sc_int<27> W[4][2]={ 67108863, 0, 
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
    sc_int < L > data_in[16];                         //to store the data received from the source
    sc_int < L+4 >  data_out[16];                        //to send out the data calculated 
    complex_s in[8];                            //store the data received with the format complex_s
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



template <unsigned int N> void papillon(  sc_int<N> Wr, sc_int<N> Wi,           //ar+brWr-biWi, if the ar is 23 bits, brWr is 23 bits, ar+brWr can reach 24 bits, if the 
                sc_int<N> ar, sc_int<N> ai,                                     // biWi is regarded as a plus, the result can reach 25 bits.
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


void fft(complex_s in[8], complex_t out[8]) 
{
    sc_int<L+2> stage1_real[8];
    sc_int<L+2> stage1_imag[8];
    sc_int<L+4> stage2_real[8];
    sc_int<L+4> stage2_imag[8];
    sc_int<L+6> stage3_real[8];
    sc_int<L+6> stage3_imag[8];

	// First stage

    papillon<23> ( W[0][0].range(26,4), W[0][1].range(26,4), 
        in[0].real, in[0].imag, in[4].real, in[4].imag,
        stage1_real[0], stage1_imag[0], stage1_real[1], stage1_imag[1]);

    papillon<23> (W[0][0].range(26,4), W[0][1].range(26,4), 
        in[2].real, in[2].imag, in[6].real, in[6].imag,
        stage1_real[2], stage1_imag[2], stage1_real[3], stage1_imag[3]);

    papillon<23> (W[0][0].range(26,4), W[0][1].range(26,4), 
        in[1].real, in[1].imag, in[5].real, in[5].imag,
        stage1_real[4], stage1_imag[4], stage1_real[5], stage1_imag[5]);

    papillon<23> (W[0][0].range(26,4), W[0][1].range(26,4), 
        in[3].real, in[3].imag, in[7].real, in[7].imag,
        stage1_real[6], stage1_imag[6], stage1_real[7], stage1_imag[7]);

	// Second stage


    papillon<25> (W[0][0].range(26,2), W[0][1].range(26,2), 
        stage1_real[0], stage1_imag[0], stage1_real[2], stage1_imag[2],
        stage2_real[0], stage2_imag[0], stage2_real[2], stage2_imag[2]);

    papillon<25> (W[2][0].range(26,2), W[2][1].range(26,2), 
        stage1_real[1], stage1_imag[1], stage1_real[3], stage1_imag[3],
        stage2_real[1], stage2_imag[1], stage2_real[3], stage2_imag[3]);

    papillon<25> (W[0][0].range(26,2), W[0][1].range(26,2), 
        stage1_real[4], stage1_imag[4], stage1_real[6], stage1_imag[6],
        stage2_real[4], stage2_imag[4], stage2_real[6], stage2_imag[6]);

    papillon<25> (W[2][0].range(26,2), W[2][1].range(26,2), 
        stage1_real[5], stage1_imag[5], stage1_real[7], stage1_imag[7],
        stage2_real[5], stage2_imag[5], stage2_real[7], stage2_imag[7]);
                
	// Etape 3


    papillon<27> (W[0][0], W[0][1], 
        stage2_real[0], stage2_imag[0], stage2_real[4], stage2_imag[4],
        stage3_real[0], stage3_imag[0], stage3_real[4], stage3_imag[4]);

    papillon<27> (W[1][0], W[1][1], 
        stage2_real[1], stage2_imag[1], stage2_real[5], stage2_imag[5],
        stage3_real[1], stage3_imag[1], stage3_real[5], stage3_imag[5]);

    papillon<27> (W[2][0], W[2][1], 
        stage2_real[2], stage2_imag[2], stage2_real[6], stage2_imag[6],
        stage3_real[2], stage3_imag[2], stage3_real[6], stage3_imag[6]);

    papillon<27> (W[3][0], W[3][1], 
        stage2_real[3], stage2_imag[3], stage2_real[7], stage2_imag[7],
        stage3_real[3], stage3_imag[3], stage3_real[7], stage3_imag[7]);

    for (int i=0; i<8; i++){
        out[i].real=stage3_real[i].range(26,0);
        out[i].imag=stage3_imag[i].range(26,0);
    }
}