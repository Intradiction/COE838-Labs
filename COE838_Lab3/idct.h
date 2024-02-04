#include "systemc.h"
#include <math.h>

#ifndef IDCT_H
#define IDCT_H

struct idct : sc_module {
    sc_in<double> in64[8][8]; // the input 8x8 block
    sc_out<FILE*> sc_output; // output file pointer port
    sc_in<double> fcosine[8][8]; // cosine table input
    sc_in<bool> clk; // clock signal

    char output_data[8][8]; // the data to be written to the output file

    void calculate_idct(); // perform inverse discrete cosine transform
    void write_data(); // write the output 8x8 block to the output file

    // Define idct as a constructor
    SC_CTOR(idct) {
        // Make calculate_idct method sensitive to the positive clock edge
        SC_METHOD(calculate_idct);
        dont_initialize();
        sensitive << clk.pos();

        // Make write_data method sensitive to the positive clock edge
        SC_METHOD(write_data);
        dont_initialize();
        sensitive << clk.neg();
    }
};

#endif
