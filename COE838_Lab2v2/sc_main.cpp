// Main cpp
#include <systemc.h>
#include "CSA.h"
#include "CPA.h"
#define size 8
int sc_main(int argc, char *argv[])
{
    sc_trace_file *tf; // Create VCD file for tracing

    sc_signal<sc_uint<size>> sum_cpa;
    sc_signal<sc_uint<size>> carryout_cpa;
    sc_signal<sc_uint<size>> ain_cpa;
    sc_signal<sc_uint<size>> bin_cpa;
    sc_signal<sc_uint<size>> carryin_cpa;

    sc_signal<sc_uint<size>> lsb_out_cpa;
    sc_signal<sc_uint<size>> sum_out_csa;
    sc_signal<sc_uint<size>> carry_out_csa;

    sc_signal<sc_uint<size>> msb_out_cpa;
    sc_signal<sc_uint<size>> lsb_in_cpa;
    sc_signal<sc_uint<size * 2>> product;

    sc_signal<sc_uint<size>> sum_csa;
    sc_signal<sc_uint<size>> carryout_csa;
    sc_signal<sc_uint<size>> ain_csa;
    sc_signal<sc_uint<size>> bin_csa;
    sc_signal<sc_uint<size>> sin_csa;
    sc_signal<sc_uint<size>> carryin_csa;
    sc_signal<sc_uint<size>> lsb_out_csa;

    sc_clock clk("clk", 10, SC_NS, 0.5); // Create a clock signal

    CPA arraymult_DUT("CPA"); // Create Device Under Test (DUT)

    arraymult_DUT.B_input(bin_cpa);
    arraymult_DUT.A_input(ain_cpa);
    arraymult_DUT.carry_in(carryin_cpa);
    arraymult_DUT.carry_out(carryout_cpa);
    arraymult_DUT.sum_out(sum_cpa);
    
    arraymult_DUT.lsb_out(lsb_out_cpa);
    arraymult_DUT.sum_out_csa(sum_out_csa);
    arraymult_DUT.carry_out_csa(carry_out_csa);
    
    arraymult_DUT.msb_out(msb_out_cpa);
    arraymult_DUT.complete(product);
    arraymult_DUT.least_sig(lsb_in_cpa);

    // Create wave file and trace the signals executing
    tf = sc_create_vcd_trace_file("trace_file");

    tf->set_time_unit(1, SC_NS);

    sc_trace(tf, msb_out_cpa, "MSB_output_cpa");
    sc_trace(tf, product, "Product");

    
    sc_trace(tf, sum_out_csa, "Sum_CSA_output");
    sc_trace(tf, carry_out_csa, "Carry_CSA_output");
    sc_trace(tf, bin_cpa, "B_input_whole_module");
    sc_trace(tf, ain_cpa, "A_input_whole_module");
    

    
    sc_trace(tf, lsb_out_cpa, "LSB_output_cpa");
    

    cout << "\nExecuting Array Multiplier DUT... check .vcd produced" << endl;

    // Test normal product: 3 * 2 = 6
    ain_cpa.write(3); 
    bin_cpa.write(2);
    sc_start(20, SC_NS);

    // Test multiplying with 0
    ain_cpa.write(0); 
    bin_cpa.write(44); 
    sc_start(20, SC_NS);

    // Test multiplying with same number and double digit result
    ain_cpa.write(9); 
    bin_cpa.write(9); 
    sc_start(20, SC_NS);

    // Test large number (max) multiplication 
    ain_cpa.write(255); 
    bin_cpa.write(255); 
    sc_start(20, SC_NS);

    sc_close_vcd_trace_file(tf);

    return 0;
}