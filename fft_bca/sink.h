#include <systemc.h>
#ifndef SINK_H
#define SINK_H

SC_MODULE(SINK){
	

	sc_in<float> out_real;
	sc_in<float> out_imag;
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

