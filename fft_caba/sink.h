#include <systemc.h>
#ifndef SINK_H
#define SINK_H
#define L 27
SC_MODULE(SINK){
	

	sc_in< sc_int<L> > out_real;
	sc_in< sc_int<L> > out_imag;
	sc_out<bool> data_req;
	sc_in<bool> data_valid;
	sc_in_clk CLK;

	SC_CTOR(SINK)
		
		{
		SC_THREAD(COMPORTEMENT);
		sensitive<< CLK.pos();		
	
		}

	void COMPORTEMENT();
};
#endif

