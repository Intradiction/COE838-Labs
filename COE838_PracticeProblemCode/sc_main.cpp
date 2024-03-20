#include <systemc.h>

int sc_main(int argc, char* argv[]) {
    // Create a 32-bit sc_bv initialized with all bits set to 1
    sc_bv<32> my_bv1(0xFFFFFBFF);

    // Or you can use hexadecimal notation
    sc_bv<32> my_bv2("1111111111111111111111111111011");

    sc_bv<32> my_bv3(0);

    // Print the sc_bv
    cout << "my_bv1: " << my_bv1 << endl;
    cout << "my_bv2: " << my_bv2 << endl;
    cout << "my_bv3: " << my_bv3 << endl;

    cout << "range: " << my_bv2.range(3,1) << endl;

    return 0;
}
