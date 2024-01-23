// COE838 - Lab1 SystemC Intro
// BarrelFlop Unit Tutorial. 
//////////////////////////////////

#ifndef BARRELSHIFT_H   
#define BARRELSHIFT_H

#include <systemc.h>       


void make_barrel();
                                
SC_MODULE(barrel_shift) {
	sc_in<bool > clk;
	sc_in<bool> enable;
	sc_in<bool> left_right;
    	sc_in<bool> l_in, r_in;
    	sc_inout<sc_int<8> > output;
 
	void barrel_method();   
 
        SC_CTOR(barrel_shift) {

        SC_METHOD(barrel_method);
	dont_initialize();
        sensitive << clk.pos(); //edge sensitive
    }

};
#endif 
