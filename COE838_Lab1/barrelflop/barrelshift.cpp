// COE838 - Lab1 SystemC Intro
// BarrelFlop Unit Tutorial. 
// Anita Tino
//////////////////////////////////
#include "barrelshift.h"

void barrel_shift :: barrel_method(){
	sc_int<8> data;
	int i;

	if(enable.read() == 1){
		data = output.read();
		if(left_right.read() == 0){ //shift left
			cout << "[left]  Data = " << data.to_string(SC_BIN) << endl; 
			for(i = 7; i > 0; i--)
				data[i] = output.read()[i-1];
			data[0] = l_in.read();
			output.write(data);
 
		}else if(left_right.read() == 1){
		cout << "[right] Data = " << data.to_string(SC_BIN) << endl; 
			for(i = 0; i < 7; i++)//shift right
				data[i] = output.read()[i+1];
			
			data[7] = r_in.read();
			output.write(data);
		}
	}
	else cout << "Not enabled "<<endl;
}


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
	sc_start(10, SC_NS);

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
