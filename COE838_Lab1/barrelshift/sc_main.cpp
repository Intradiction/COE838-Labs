// COE838 - Lab1 SystemC Intro
// BarrelShift Unit Tutorial. 
//////////////////////////////////
//Testbench driver for barrelshift

#include <systemc.h>
#include "barrelshift.h"


void make_barrel(){
 	sc_trace_file *tf;                  // Create VCD file for tracing
	sc_signal<bool> left_in, right_in;      //Declare signals
	sc_signal<bool> en, left_right;
	sc_signal<sc_int<8> >data_out;

	 sc_clock clk("clk",10,SC_NS,0.5);   //Create a clock signal
	
   	 barrel_shift barrel("barrelshift");            //Create testbench Device Under Test (DUT)

   	 barrel.l_in(left_in);                       // Connect/map the ports to testbench signals
   	 barrel.r_in(right_in);
   	 barrel.clk(clk);
	 barrel.enable(en);
         barrel.left_right(left_right);
	 barrel.output(data_out);

       // Create wave file and trace the signals executing
	tf = sc_create_vcd_trace_file("trace_file");
        tf->set_time_unit(1, SC_NS);
	sc_trace(tf, clk, "clk");
	sc_trace(tf, en, "enable");
	sc_trace(tf, left_in, "left_data");
	sc_trace(tf, right_in, "right_data");
	sc_trace(tf, left_right, "left_right_signal");
	sc_trace(tf, data_out, "data_out");
	
	cout << "\nExecuting 1bit barrel shift example... check .vcd produced"<<endl;

	//start the testbench
        en.write(0); //initialize
	left_in.write(0); right_in.write(0);
	left_right.write(0); 
	sc_start(9, SC_NS);

	en.write(1); //enable and input
	left_in.write(1); right_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);

	left_in.write(1); right_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);

	left_in.write(1); right_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);

	left_in.write(1); right_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);

	left_in.write(1); right_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);

	left_in.write(1); right_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);
	
	left_in.write(1); right_in.write(0);
	left_right.write(1);
	sc_start(10, SC_NS);
		
	en.write(0); //not enabled and input scenario
	left_in.write(1); right_in.write(0);
	left_right.write(1);
	sc_start(10, SC_NS);
	
	en.write(1); //enabled
	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

   	sc_close_vcd_trace_file(tf);
}

int sc_main(int argc, char* argv[]){

	make_barrel(); //example of function call in main cpu


	return 0;                         
}
