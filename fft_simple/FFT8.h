#include <systemc.h>
#ifndef FFT8_H
#define FFT8_H

SC_MODULE(FFT8){
	

	sc_fifo_in<float> FFT8_FIFO_IN;
    sc_fifo_out<float> FFT8_FIFO_OUT;
	sc_in_clk CLK;

	SC_CTOR(FFT8)
		
		{
		SC_THREAD(COMPORTEMENT);
		sensitive<< CLK.pos();		
	
		}
	

	void COMPORTEMENT();
};
#endif
