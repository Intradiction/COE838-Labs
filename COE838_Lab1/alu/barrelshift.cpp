// COE838 - Lab1 SystemC Intro
// BarrelFlop Unit Tutorial.
// Anita Tino
//////////////////////////////////
#include "barrelshift.h"

void make_barrel()
{
	sc_trace_file *tf;				   // Create VCD file for tracing
	sc_signal<bool> en, left_right;
	sc_signal<sc_int<8>> data_in;
	sc_signal<sc_int<8>> data_out;

	sc_clock clk("clk", 10, SC_NS, 0.5); // Create a clock signal

	barrel_shift barrel("barrelshift"); // Create testbench Device Under Test (DUT)


	barrel.clk(clk);
	barrel.enable(en);
	barrel.left_right(left_right);
	barrel.input(data_in);
	barrel.output(data_out);

	// Create wave file and trace the signals executing
	tf = sc_create_vcd_trace_file("trace_file");
	tf->set_time_unit(1, SC_NS);
	sc_trace(tf, clk, "clk");
	sc_trace(tf, en, "enable");
	sc_trace(tf, left_right, "left_right_signal");
	sc_trace(tf, data_out, "data_out");
	sc_trace(tf, data_in, "data_in");

	cout << "\nExecuting 1bit barrel shift example... check .vcd produced" << endl;

	// start the testbench
	en.write(0); // initialize
	data_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);

	en.write(1); // enable and shift left
	data_in.write(5);
	left_right.write(0);
	sc_start(10, SC_NS);

	en.write(0); // not enabled and input scenario
	data_in.write(0);
	left_right.write(1);
	sc_start(10, SC_NS);

	en.write(1); // enable and shift right
	data_in.write(3);
	left_right.write(1);
	sc_start(10, SC_NS);

	sc_close_vcd_trace_file(tf);
}
