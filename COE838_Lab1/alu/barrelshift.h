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
	sc_in<sc_int<8>> input;
	sc_inout<sc_int<8>> output;

	void barrel_method()
	{
		sc_int<8> result;

		if (enable.read() == 1)
		{
			result = output.read();
			// shift left
			if (left_right.read() == 0)
			{ 
				cout << "[shift left]  ";
				for(int i = 7; i > 0; i--)
				{
					result[i] = input.read()[i-1];
				}
				
			}
			else if (left_right.read() == 1)
			{
				cout << "[shift right] ";
				for(int i = 6; i > 0; i--)
				{
					result[i] = input.read()[i+1];
				}
			}
			output.write(result);
		}
		else
		{
			cout << "[not enabled] ";
			//output.write(input.read());
		}

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
