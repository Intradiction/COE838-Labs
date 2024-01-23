#include "alu.h"

void make_alu() {
    sc_trace_file *tf;  // Create VCD trace file, can use GTKWave to view waveforms
    sc_signal<sc_int<8>> a_in, b_in, out;
    sc_signal<sc_uint<1>> op;
    sc_signal<bool> en;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    // Create Device Under Test (DUT)

    alu alu_DUT("alu"); 
    alu_DUT.clk(clk);
    alu_DUT.op(op);
    alu_DUT.a_in(a_in);
    alu_DUT.b_in(b_in);
    alu_DUT.out(out);

    tf = sc_create_vcd_trace_file("trace_file");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clk, "clk");
    sc_trace(tf, op, "op");
    sc_trace(tf, a_in, "a_in");
    sc_trace(tf, b_in, "b_in");
    sc_trace(tf, out, "out");

    cout << "\nExecuting ALU, check .vcd file in GTKWave\n" << endl;

    // Start testbench, initialize first
    op.write(0);
    a_in.write(0);
    b_in.write(0);
    sc_start(10, SC_NS);

    // Test addition | 2 + 3 = 5
    op.write(1);
    a_in.write(2);
    b_in.write(3);
    sc_start(10, SC_NS);
    
    // Test subtraction | 4 - 1 = 3
    op.write(0);
    a_in.write(4);
    b_in.write(1);
    sc_start(10, SC_NS);

    // Test subtraction with negative difference | 5 - 7 = -2
    op.write(0);
    a_in.write(5);
    b_in.write(7);
    sc_start(10, SC_NS);
    
    sc_close_vcd_trace_file(tf);
}