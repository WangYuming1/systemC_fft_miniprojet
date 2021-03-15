#ifndef TOP_H
#define TOP_H
#include <systemc.h>
#include "fft.h"
#include "FFT8.h"
#include "sink.h"
#include "source.h"
SC_MODULE(TOP){
	sc_clock CLK;
    sc_signal FFT_FIFO_IN;
    sc_signal FFT_FIFO_OUT;
    FFT8 fft8;
    SINK sink;
    SOURCE source;

	
	SC_CTOR(TOP):
       
        FFT8("FFT8"),
        source("source"),
        sink("sink")
		{
            source.FIFO_OUT(FFT_FIFO_IN);
            sink.FIFO_IN(FFT_FIFO_OUT);
            FFT8.FFT8_IN(FFT_FIFO_IN);
            

			


		}
		
	
};
#endif