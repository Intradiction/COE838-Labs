// COE838 - Lab1 SystemC Intro
// FlipFlop Unit Tutorial. 
//////////////////////////////////

#ifndef FLIPFLOP_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define FLIPFLOP_H

#include <systemc.h>     

                          
SC_MODULE(flipflop) {
    sc_in<bool > clk;
    sc_in<bool> enable;
    sc_in<sc_uint<3> > din;
    sc_out<sc_uint<3> > dout;
 
    void ff_method(); 
 
    SC_CTOR(flipflop) {
        SC_METHOD(ff_method);
	dont_initialize();
        sensitive << clk.pos(); //edge sensitive
    }

};
#endif 
