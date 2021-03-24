#include <systemc.h>
#ifndef SOURCE_H
#define SOURCE_H
#define L 23
SC_MODULE(SOURCE){
	
	
	//sc_out<float> in_real;
	sc_out< sc_int<L> > in_real, in_imag;
	sc_in<bool> data_req;					//data req from fft
	sc_out<bool> data_valid;				//data valid flag to give to the fft.
	sc_in_clk CLK;

	SC_CTOR(SOURCE)
		
		{
		SC_THREAD(COMPORTEMENT);
		sensitive<< CLK.pos();		
		}
	

	void COMPORTEMENT();
};
#endif

