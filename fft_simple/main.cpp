#include <systemc.h>
#include "TOP.h"
#include "main.h"

int sc_main ( int argc, char *argv[]){

    TOP mainTop("mainTop");
    sc_trace_file *tf = sc_create_vcd_trace_file("trace");
    tf->set_time_unit(1, SC_NS);
    mainTop.SRC_2_FFT.trace(tf);
    mainTop.FFT_2_SINK.trace(tf);
    sc_start(2000,SC_NS);
    cout<<"Finished at "<<sc_time_stamp()<< "\n";
    sc_close_vcd_trace_file(tf);
    return 0;
    


}