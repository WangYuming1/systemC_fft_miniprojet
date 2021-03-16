#include <systemc.h>
#ifndef SOURCE_H
#define SOURCE_H

SC_MODULE(SOURCE){
	

	sc_fifo_out<float> SRC_FIFO_OUT;
	sc_in_clk CLK;

	SC_CTOR(SOURCE)
		
		{
		SC_THREAD(COMPORTEMENT);
		sensitive<< CLK.pos();		
	
		}
	

	void COMPORTEMENT();
};
#endif

