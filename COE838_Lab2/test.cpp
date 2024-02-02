SC_CTOR(ArrayMultiplier) {
    for (int i = 0; i < 64; ++i) {
        CSA[i] = new CarrySaveAdder(("CSA_" + std::to_string(i)).c_str());
        CSA[i]->clk(clk);
    }

    for (int i = 0; i < 8; ++i) {
        CPA[i] = new CarrySaveAdder(("CPA_" + std::to_string(i)).c_str());
        CPA[i]->clk(clk);
    }

    // Initialize the instances of CPA modules
    for (int i = 0; i < 8; ++i) {
        CPA[i]->a(a[i]);
        CPA[i]->b(b[i]);
        CPA[i]->cin(i == 0 ? sc_uint<8>(0) : CSA[i * 8 - 1]->cout); // Provide initial value
        CPA[i]->sum(result_part[i]);
        if (i != 0) {
            CPA[i]->cin(CPA[i - 1]->cout);
        }
    }

    SC_METHOD(multiplier_logic);
    sensitive << clk.pos();
}
