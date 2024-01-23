// COE838 - Lab1 SystemC Intro
// BarrelFlop Unit Tutorial. 
//////////////////////////////////
//Testbench driver 

#include <systemc.h>
#include "flipflop.h"
#include "barrelshift.h"

int sc_main(int argc, char* argv[]){

	if(argc == 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0){ //make sure user has selected an option for tutorial example
		cout << "Usage: ./flipflop.x [option#] "<<endl;
		cout << "where [option#] 1 - flip flop example " <<endl;
		cout << "                2 - barrel shift example" << endl;
		return 1;
	}

	if(argv[1][0] == '1'){
		make_flipflop();
	}else if(argv[1][0] == '2'){
		make_barrel();
	}
		

    return 0;                         
}
