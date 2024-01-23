// COE838 - Lab1 SystemC Intro
// BarrelFlop Unit Tutorial. 
//////////////////////////////////
//simple flip flop example using systemC

#ifndef FLIPFLOP_H    
#define FLIPFLOP_H

#include <systemc.h>       


void make_flipflop();
                                
SC_MODULE(flipflop) {
    sc_in<bool > clk;
    sc_in<bool> enable;
    sc_in<sc_uint<3> > din;
    sc_out<sc_uint<3> > dout;
    sc_int<3> data;
 
    void ff_method() {
	//after every rising edge, check if enabled
	cout << "Enable = " << enable.read() <<", output = ";
	if(enable.read() == 1){
	    data = din.read();
            dout.write(din.read());   
	}
	cout << data.to_string(SC_BIN) << endl; 
    }
 
        SC_CTOR(flipflop) {
        SC_METHOD(ff_method);
	dont_initialize();
        sensitive << clk.pos(); //edge sensitive
    }

};
#endif 
