#ifndef TOP_H
#define TOP_H
#include <systemc.h>
#include "fft.h"
#include "FFT8.h"
#include "sink.h"
#include "source.h"
SC_MODULE(TOP){
	sc_clock clk;
    sc_signal<float> SOURCE_FFT;
    sc_signal<float> FFT_SINK;
    FFT8 fft8;
    SINK sink;
    SOURCE source;

	
	SC_CTOR(TOP):
       
        fft8("fft8"),
        source("source"),
        sink("sink")
		{
            source.FIFO_OUT(SOURCE_FFT);
            sink.FIFO_IN(FFT_SINK);
            fft8.FFT8_IN(SOURCE_FFT);
            fft8.FFT8_OUT(FFT_SINK);
            fft8.CLK(clk);
            source.CLK(clk);
            sink.CLK(clk);
		}
		
	
};
#endif