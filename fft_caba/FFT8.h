#include <systemc.h>
#ifndef FFT8_H
#define FFT8_H
#define L 23
SC_MODULE(FFT8){
	

	sc_in< sc_int<L> > in_real, in_imag;
	sc_out< sc_int<27> > out_real, out_imag; 
	sc_in<bool> data_valid_in;
	sc_out<bool> data_valid_out;
	sc_in<bool> data_req_in;
	sc_out<bool> data_req_out; 
	sc_in_clk CLK;
	SC_CTOR(FFT8)	
		{
		SC_THREAD(COMPORTEMENT);
		sensitive<< CLK.pos();		
		}
	void COMPORTEMENT();
};
#endif
