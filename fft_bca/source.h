#include <systemc.h>
#ifndef SOURCE_H
#define SOURCE_H

SC_MODULE(SOURCE){
	

	sc_out<float> in_real;
	sc_out<float> in_imag;
	sc_in<bool> data_req;
	sc_out<bool> data_valid;
	sc_in_clk CLK;

	SC_CTOR(SOURCE)
		
		{
		SC_THREAD(COMPORTEMENT);
		sensitive<< CLK.pos();		
		}
	

	void COMPORTEMENT();
};
#endif

