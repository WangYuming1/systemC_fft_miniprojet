#include <systemc.h>
#include "TOP.h"

int sc_main ( int argc, char *argv[])
{
	//Instanciation du TOP
	TOP mainTop("top");
  sc_clock clk ("ID", 10, SC_NS, 0.5, 10, SC_NS, true);
	//Creation des traces
	mainTop.clk(clk);
	//mainTop.s_valid(s_data_valid_input2);
	//mainTop.s_data_valid_input(s_data_valid_input2);
	sc_trace_file *tf = sc_create_vcd_trace_file("trace");

	tf->set_time_unit(1, SC_NS);



	sc_trace(tf,clk,"clk");
	sc_trace(tf,mainTop.src_2_fft_valid,"src_2_fft_valid");
	sc_trace(tf,mainTop.fft_2_src_req,"fft_2_src_req");
	sc_trace(tf,mainTop.fft_2_sink_valid,"fft_2_sink_valid");
	sc_trace(tf,mainTop.sink_2_fft_req,"sink_2_fft_req");
	sc_start(2000, SC_NS);
	//fin
	cout<< "Finished at" << sc_time_stamp() << "\n";
	//Fermeture du fichier de traces
	sc_close_vcd_trace_file(tf);

	return 0;
}