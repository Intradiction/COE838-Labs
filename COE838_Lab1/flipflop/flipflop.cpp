// COE838 - Lab1 SystemC Intro
// FlipFlop Unit Tutorial. 
//////////////////////////////////
#include "flipflop.h"

 sc_int<3> data;
 
 void flipflop :: ff_method() {
	//after every rising edge, check if enabled
	cout << "Enable = " << enable.read() << ", input = " << din.read().to_string(SC_BIN) << ", output = ";
	if(enable.read() == 1){
	    data = din.read();
            dout.write(din.read());   
	}
	cout << data.to_string(SC_BIN) << endl; 
    }
 


