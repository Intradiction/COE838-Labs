#ifndef ALU_H
#define ALU_H

#include <systemc.h>

void make_alu();

SC_MODULE(alu) {
    sc_in<bool> clk;                // The clock signal
    sc_in<sc_int<8>> a_in, b_in;   // The two 8-bit ALU inputs
    sc_in<sc_uint<1>> op;           // The 1-bit ALU opcode (0 = Sub, 1 = Add)
    sc_out<sc_int<8>> out;         // The 8-bit output

    // The method that handles ALU functionality
    void alu_method() {
        cout << "ALU: ";
        sc_int<8> data;
        cout << "op = " << op.read() << " | a_in = " << a_in.read() << ", b_in = " << b_in.read() << ", output = ";

        // Subtract operation
        if(op.read() == 0){
            data = a_in.read() - b_in.read();
            out.write(a_in.read() - b_in.read());
        } 
        // Add operation
        else if (op.read() == 1) {
            data = a_in.read() + b_in.read();
            out.write(a_in.read() + b_in.read());
        }

        cout << data.to_string() << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
    }

    SC_CTOR(alu){
        SC_METHOD(alu_method);
        dont_initialize();
        sensitive << clk.neg();
    }
};
#endif