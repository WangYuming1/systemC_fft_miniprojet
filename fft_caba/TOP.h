#ifndef TOP_H
#define TOP_H
#include <systemc.h>
#include "fft.h"
#include "FFT8.h"
#include "sink.h"
#include "source.h"
SC_MODULE(TOP){
	sc_in_clk clk;
    FFT8 fft8;
    SINK sink;
    SOURCE source;

    sc_signal< sc_int< L > > src_2_fft_real, src_2_fft_imag;
    sc_signal<bool> src_2_fft_valid, fft_2_src_req;

    sc_signal< sc_int<L+4> > fft_2_sink_real, fft_2_sink_imag;
    sc_signal<bool> fft_2_sink_valid, sink_2_fft_req;


	SC_CTOR(TOP):
        fft8("fft8"),
        source("source"),
        sink("sink")
       
		{
            source.in_real(src_2_fft_real);
            source.in_imag(src_2_fft_imag);
            source.data_valid(src_2_fft_valid);
            source.data_req(fft_2_src_req);
            source.CLK(clk);

            sink.out_real(fft_2_sink_real);
            sink.out_imag(fft_2_sink_imag);
            sink.data_valid(fft_2_sink_valid);
            sink.data_req(sink_2_fft_req);
            sink.CLK(clk);
           
            fft8.in_real(src_2_fft_real);
            fft8.in_imag(src_2_fft_imag);
            fft8.out_real(fft_2_sink_real);
            fft8.out_imag(fft_2_sink_imag);
            fft8.data_valid_in(src_2_fft_valid);
            fft8.data_valid_out(fft_2_sink_valid);
            fft8.data_req_in(sink_2_fft_req);
            fft8.data_req_out(fft_2_src_req);
            fft8.CLK(clk);
		}  
};
#endif