#include <system.h>
#ifndef "SINK_H"
#define "SINK_H"

SC_MODULE(SINK){
	

	sc_fifo_in<float> FIFO_IN;
	sc_in_clk CLK;

	SC_CTOR(SINK):
		
		{
		SC_THREAD(COMPORTEMENT);
		sensitive<< CLK.pos();		
	
		}
	

	void COMPORTEMENT();
};
#endif

