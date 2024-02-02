#include <systemc.h>

// Define Carry Save Adder (CSA) Module
SC_MODULE(CarrySaveAdder) {
    sc_in<bool> clk{"clk"};
    sc_in<sc_uint<8>> a{"a"}, b{"b"}, cin{"cin"};
    sc_out<sc_uint<8>> sum{"sum"}, cout{"cout"};

    void adder_logic() {
        sum.write(a.read() + b.read() + cin.read());
        cout.write((a.read() + b.read() + cin.read()) >> 8);
    }

    SC_CTOR(CarrySaveAdder) {
        SC_METHOD(adder_logic);
        sensitive << clk.pos();
    }
};

// Define 8x8 Array Multiplier Module
SC_MODULE(ArrayMultiplier) {
    sc_in<bool> clk;
    sc_in<sc_uint<8>> a[8], b[8];
    sc_out<sc_uint<64>> result;

    CarrySaveAdder *CSA[64];
    CarrySaveAdder *CPA[8];

    void multiplier_logic() {
        // Connect the carry save adders
        for (int i = 0; i < 64; ++i) {
            CSA[i]->a(a[i / 8]);
            CSA[i]->b(b[i % 8]);
            //CSA[i]->cin(i == 0 ? 0 : CSA[i - 1]->cout);
            if (i != 0 ){
                CSA[i]->cin(CSA[i - 1]->cout);
            }
        }

        // Connect the carry propagate adders
        for (int i = 0; i < 8; ++i) {
            //CPA[i]->a(i == 0 ?  : CSA[i * 8 - 1]->cout);
            CPA[i]->b(CSA[i * 8]->sum);
            //CPA[i]->cin(i == 0 ? 0 : CPA[i - 1]->cout);

            if (i != 0 ){
                CPA[i]->a(CSA[i * 8 - 1]->cout);
                CPA[i]->cin(CPA[i - 1]->cout);
            }
        }

        // Output result
        result.write((sc_uint<64>)CPA[7]->sum);
    }

    SC_CTOR(ArrayMultiplier) {
        for (int i = 0; i < 64; ++i) {
            CSA[i] = new CarrySaveAdder(("CSA_" + std::to_string(i)).c_str());
            CSA[i]->clk(clk);
        }

        for (int i = 0; i < 8; ++i) {
            CPA[i] = new CarrySaveAdder(("CPA_" + std::to_string(i)).c_str());
            CPA[i]->clk(clk);
            CPA[7]->cout(CPA[6]->cout);
        }

        SC_METHOD(multiplier_logic);
        sensitive << clk.pos();
    }

    ~ArrayMultiplier() {
        for (int i = 0; i < 64; ++i)
            delete CSA[i];
        
        for (int i = 0; i < 8; ++i)
            delete CPA[i];
    }
};

// Define Testbench Module
SC_MODULE(Testbench) {
    sc_clock clk;
    sc_signal<sc_uint<8>> a[8], b[8];
    sc_signal<sc_uint<64>> result;

    ArrayMultiplier *multiplier;

    void generate_input() {
        for (int i = 0; i < 8; ++i) {
            a[i].write(i + 1);
            b[i].write(8 - i);
        }
    }

    void print_output() {
        cout << "Result: " << result.read() << endl;
    }

    SC_CTOR(Testbench) : clk("clk", 10, SC_NS) {
        multiplier = new ArrayMultiplier("multiplier");
        multiplier->clk(clk);
        for (int i = 0; i < 8; ++i) {
            multiplier->a[i](a[i]);
            multiplier->b[i](b[i]);
        }
        multiplier->result(result);

        SC_THREAD(generate_input);
        sensitive << clk.posedge_event();

        SC_METHOD(print_output);
        sensitive << result;
    }

    ~Testbench() {
        delete multiplier;
    }
};

int sc_main(int argc, char* argv[]) {
    Testbench tb("tb");
    sc_start(100, SC_NS);

    return 0;
}
