#include <systemc.h>

SC_MODULE(jkff) {
    sc_in<bool> J, K, clk;
    sc_out<bool> Q, QP;

    void jkff_method();

    SC_CTOR(jkff){
        SC_METHOD(jkff_method);
        dont_initialize();
        sensitive << clk.pos();
    }
};