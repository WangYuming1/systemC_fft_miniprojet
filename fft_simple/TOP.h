#ifndef TOP_H
#define TOP_H
#include <systemc.h>
#include "fft.h"
#include "FFT8.h"
#include "sink.h"
#include "source.h"
SC_MODULE(TOP){
	sc_clock clk;
    sc_signal SRC_2_FFT;
    sc_signal FFT_2_SINK;
    FFT8 fft8;
    SINK sink;
    SOURCE source;

	
	SC_CTOR(TOP):
        fft8("fft8"),
        source("source"),
        sink("sink")
        clk("clk", 2, SC_NS, 0.5),
		{
            source.SRC_FIFO_OUT(SRC_2_FFT);
            sink.SINK_FIFO_IN(FFT_2_SINK);
            fft8.FFT8_FIFO_IN(SRC_2_FFT);
            fft8.FFT8_FIFO_OUT(FFT_2_SINK);
            source.CLK(clk);
            sink.CLK(clk);
            fft8.CLK(clk);

		}
		
	
};
#endif