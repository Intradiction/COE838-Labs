// COE838 - Lab1 SystemC Intro
// BarrelFlop Unit Tutorial.
//////////////////////////////////

#ifndef BARRELSHIFT_H
#define BARRELSHIFT_H

#include <systemc.h>

void make_barrel();

SC_MODULE(barrel_shift)
{
	sc_in<bool> clk;
	sc_in<bool> enable;
	sc_in<bool> left_right;
	sc_in<sc_uint<4>> shift_amt;
	sc_in<sc_int<8>> input;
	sc_inout<sc_int<8>> output;

	void barrel_method()
	{
		cout << "BS:  ";
		sc_int<8> result;

		if (enable.read() == 1)
		{
			//result = output.read();
			int shift_int = shift_amt.read().to_int();
			// shift left
			if (left_right.read() == 0)
			{ 
				cout << "[shift left by " << shift_int << "]  ";
				for(int i = 7; i > 0; i--)
				{
					int j = i - shift_int;
					if(j >= 0 && j <= 7)
						result[i] = input.read()[j];
				}
				
			}
			// shift right
			else if (left_right.read() == 1)
			{
				cout << "[shift right by " << shift_int << "] ";
				if((7-shift_int) >= 0)
					for(int i = 7-shift_int; i > 0; i--)
					{
						int j = i + shift_int;
						if(j >= 0 && j <= 7)
							result[i] = input.read()[j];
					}

			}
			
		}
		else
		{
			cout << "[not enabled]      ";
			result = input.read();
		}

		output.write(result);
		cout << "input = " << input.read() << /*", output = " << output.read() <<*/", result = "<< result.to_int64() << endl;
			
	};

	SC_CTOR(barrel_shift)
	{
		SC_METHOD(barrel_method);
		dont_initialize();
		sensitive << clk.pos(); // edge sensitive
	}
};
#endif
