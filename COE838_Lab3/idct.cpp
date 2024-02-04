#include "idct.h"

void idct::calculate_idct() {
    unsigned char u, v, x, y;
    double temp;

    // Do inverse discrete cosine transform
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            temp = 0.0;
            for (u = 0; u < 8; u++) {
                for (v = 0; v < 8; v++) {
                    double cu = (u == 0) ? (1 / sqrt(2)) : 1;
                    double cv = (v == 0) ? (1 / sqrt(2)) : 1;
                    temp += cu * cv * in64[u][v].read() * fcosine[x][u].read() * fcosine[y][v].read();
                }
            }
            output_data[x][y] = (char)round(temp / 4.0);
        }
    }

    // Write output_data to out64
    // for (x = 0; x < 8; x++) {
    //     for (y = 0; y < 8; y++) {
    //         out64[x][y].write(output_data[x][y]);
    //     }
    // }

    printf(".");
}

void idct::write_data() {
    FILE* output_file = sc_output.read();

    // Write the output data to the output file
    fwrite(output_data, 1, 64, output_file);
}