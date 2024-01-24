/**
 * COE 838 - Lab 1 SystemC ALU 
 * Author: Greylyn Gao
 **/ 

#include <systemc.h>
#include "alu.h"
#include "barrelshift.h"

int sc_main(int argc, char* argv[]) {
    //make_alu();
    //make_barrel();

    sc_trace_file *tf;  // Create VCD trace file, can use GTKWave to view waveforms

    // Initialize signals
    sc_signal<sc_int<8>> a_in, b_in, bs_out, alu_out;
    sc_signal<sc_uint<1>> op;
    sc_signal<bool> enable, left_right;
    sc_signal<sc_uint<4>> shift_amt;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    // Create Device Under Test (DUT)
    barrel_shift bs_DUT("bs");
    bs_DUT.clk(clk);
    bs_DUT.enable(enable);
    bs_DUT.left_right(left_right);
    bs_DUT.input(b_in);
    bs_DUT.output(bs_out);
    bs_DUT.shift_amt(shift_amt);

    // 	sc_in<bool> clk;
	// sc_in<bool> enable;
	// sc_in<bool> left_right;
	// sc_inout<sc_int<8>> input, output;

    alu alu_DUT("alu"); 
    alu_DUT.clk(clk);
    alu_DUT.op(op);
    alu_DUT.a_in(a_in);
    alu_DUT.b_in(bs_out);
    alu_DUT.out(alu_out);

    tf = sc_create_vcd_trace_file("trace_file");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clk, "clk");
    sc_trace(tf, op, "op");
    sc_trace(tf, a_in, "a_in");
    sc_trace(tf, b_in, "b_in");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, left_right, "left0_right1");
    sc_trace(tf, shift_amt, "shift_amt");
    sc_trace(tf, alu_out, "alu_out");

    cout << "\nExecuting ALU, check .vcd file in GTKWave\n" << endl;

    // Start testbench, initialize first
    // op         | 0 = sub, 1 = add
    // a_in       | 8-bit integer
    // b_in       | 8-bit integer
    // enable     | 0 = barrelshifter off, 1 = barrelshifter on
    // left_right | 0 = shift left, 1 = shift right
       
    op.write(0);
    a_in.write(0);
    b_in.write(2);
    enable.write(1);
    left_right.write(0);
    shift_amt.write(1);
    sc_start(10, SC_NS);

    // // Test addition | 2 + 3 = 5
    // op.write(1);
    // a_in.write(2);
    // b_in.write(3);
    // sc_start(10, SC_NS);
    
    // // Test subtraction | 4 - 1 = 3
    // op.write(0);
    // a_in.write(4);
    // b_in.write(1);
    // sc_start(10, SC_NS);

    // // Test subtraction with negative difference | 5 - 7 = -2
    // op.write(0);
    // a_in.write(5);
    // b_in.write(7);
    // sc_start(10, SC_NS);

    // Test addition with left shift | 2 + (3<<1) = 8
    op.write(1);
    a_in.write(2);
    b_in.write(3);
    enable.write(1);
    left_right.write(0);
    shift_amt.write(1);
    sc_start(10, SC_NS);

    // Test subtraction with right shift | 9 - (8>>2) = 7
    op.write(0);
    a_in.write(9);
    b_in.write(8);
    enable.write(1);
    left_right.write(1);
    shift_amt.write(2);
    sc_start(10, SC_NS);

    // Test above case with enable = 0
    op.write(0);
    a_in.write(9);
    b_in.write(8);
    enable.write(0);
    left_right.write(1);
    shift_amt.write(2);
    sc_start(10, SC_NS);

    // Test above case with shift_amt = 0
    op.write(0);
    a_in.write(9);
    b_in.write(8);
    enable.write(1);
    left_right.write(1);
    shift_amt.write(0);
    sc_start(10, SC_NS);
    
    sc_close_vcd_trace_file(tf);

    return 0;
}