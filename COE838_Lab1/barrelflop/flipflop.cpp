// COE838 - Lab1 SystemC Intro
// BarrelFlop Unit Tutorial. 
//////////////////////////////////
#include "flipflop.h"

void make_flipflop(){
	 sc_trace_file *tf;                  // Create VCD file for tracing
	 sc_signal<sc_uint<3> > data_in, data_out;      //Declare signals
	 sc_signal<bool> en;

	 sc_clock clk("clk",10,SC_NS,0.5);   //Create a clock signal
	
   	 flipflop DUT("flipflop");            //Create Device Under Test (DUT)

   	 DUT.din(data_in);                       // Connect/map the ports to testbench signals
   	 DUT.dout(data_out);
   	 DUT.clk(clk);
	 DUT.enable(en);

       // Create wave file and trace the signals executing
	tf = sc_create_vcd_trace_file("trace_file");
        tf->set_time_unit(1, SC_NS);
	sc_trace(tf, clk, "clk");
	sc_trace(tf, en, "enable");
	sc_trace(tf, data_in, "data_in");
	sc_trace(tf, data_out, "data_out");
	
	cout << "\nExecuting flip flop example... check .vcd produced"<<endl;

	//start the testbench
        en.write(0); //initialize
	data_in.write(0);
	sc_start(9, SC_NS);

	en.write(1); //enable and input
	data_in.write(7);
	sc_start(10, SC_NS);
	
	data_in.write(6);
	sc_start(10, SC_NS);
	
	data_in.write(5);
	sc_start(10, SC_NS);
	
	en.write(0); //not enabled and input scenario
	data_in.write(6);
	sc_start(10, SC_NS);
	
	en.write(1); //enabled
	data_in.write(1);
	sc_start(10, SC_NS);
	data_in.write(0);
	sc_start(10, SC_NS);

   	sc_close_vcd_trace_file(tf);
}
