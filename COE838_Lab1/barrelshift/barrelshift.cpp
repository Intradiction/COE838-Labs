// COE838 - Lab1 SystemC Intro
// BarrelShift Unit Tutorial. 
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
		cout << "[right] Data = " << output.read().to_string(SC_BIN) << endl; 
			for(i = 0; i < 7; i++)//shift right
				data[i] = output.read()[i+1];
			
			data[7] = r_in.read();
			output.write(data);
		}
	}
	else 
		cout << "Not enabled "<<endl;
}


