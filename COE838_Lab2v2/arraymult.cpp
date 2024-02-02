
#include "CPA.h"
#include "CSA.h"

#define size 8

//CSA
sc_uint<size> sum;
sc_uint<size> carryout;
sc_uint<size> ain;
sc_uint<size> bin;
sc_uint<size> A_combined;
sc_uint<size> sin_input;
sc_uint<size> ainandbin;
sc_uint<size> lsb_val;
sc_uint<size> carryin;
sc_uint<size> sum_actual;
sc_uint<size> carr_actual;
sc_uint<size> sum_simplier;
sc_uint<size> carr_simplier;
int i = 0;
int j = 0;
int y = 0;
int sum_holder[size][size];
int carryout_holder[size][size];

// CPA
sc_uint<size> sum_cpa;
sc_uint<size> carryout_cpa;

sc_uint<size> sum_holder_cpa;
sc_uint<size> carryout_holder_cpa;

sc_uint<size> sum_csa;

sc_uint<size> carryout_csa;
sc_uint<size> ain_cpa;
sc_uint<size> bin_cpa;
sc_uint<size> carryin_cpa;

sc_uint<size> least_significant;
sc_uint<size * 2> complete_output;

sc_uint<size> msb_val;
int x, w = 0;
int z = 0;


// a xor b
// b and c
// (a xor b)  xor cin  => sum  -> main eq
// (a and c) OR (a and b) => cout -> main eq

void CPA ::CPA_method()
{
    cout << "\n======= Array Multiplier Operation =======\n";

    //**************************************** CSA Method
    ain = A_input.read();
    bin = B_input.read();
    A_combined = ain & bin;
    for (i = 0; i < size; i++)
    { // row number

        for (j = 0; j < size; j++)
        { // column number
            if (i == 0)
            { // if first row , C = 0 and S = 0
                sin_input = 0;
                carryin = 0;

                A_combined = ain[j] & bin[i];
                sum = (((A_combined) ^ (sin_input)) ^ (carryin)); //((axorb)) xor cin
                carryout = ((A_combined)&sin_input) | (sin_input & carryin) | (A_combined & carryin);
                if (j == 0)
                {
                    lsb_val[i] = sum[j]; // every row that last column sum will be stored in the lsb register
                }
                sum_holder[i][j] = sum;         // holder current column number (i.e first column A3)
                carryout_holder[i][j] = carryout; // holder current column number (i.e first column A3)
            }

            else if (j == (size - 1) && (i != 0))
            { // S = 0

                A_combined = ain[j] & bin[i];
                carryin = carryout_holder[i - 1][j]; // will have to make equal carryout value in same column but previous row
                sin_input = 0;
                sum = (((A_combined) ^ (sin_input)) ^ (carryin)); //((axorb)) xor cin
                carryout = ((A_combined)&sin_input) | (sin_input & carryin) | (A_combined & carryin);

                sum_holder[i][j] = sum;         // holder current column number (i.e first column A3)
                carryout_holder[i][j] = carryout; // holder current column number (i.e first column A3)
            }

            else
            {

                A_combined = ain[j] & bin[i];
                carryin = carryout_holder[i - 1][j];               // will have to make equal carryout value in same column but previous row
                sin_input = sum_holder[i - 1][j + 1];            // will have to make sin input the previous row & future columb
                sum = (((A_combined) ^ (sin_input)) ^ (carryin)); //((axorb)) xor cin
                carryout = ((A_combined)&sin_input) | (sin_input & carryin) | (A_combined & carryin);

                sum_holder[i][j] = sum;         // holder current column number (i.e first column A3)
                carryout_holder[i][j] = carryout; // holder current column number (i.e first column A3)

                if (j == 0)
                {
                    lsb_val[i] = sum[j]; // every row that last column sum will be stored in the lsb register
                }
            }

            cout << "Sumout at ["<<i<<","<<j<<"] = "<<sum_holder[i][j] << " | ";
            cout << "Carryout at ["<<i<<","<<j<<"] = "<<carryout_holder[i][j];
            cout << endl;
        }
    }

    for (y = 0; y < size; y++)
    { // column
        sum_simplier[y] = sum_holder[size - 1][y];
        carr_simplier[y] = carryout_holder[size - 1][y];
    }

    lsb_out.write(lsb_val);
    carry_out_csa.write(carr_simplier);
    sum_out_csa.write(sum_simplier);

    //**************************************** CSA Method

    sum_csa = sum_simplier;
    carryout_csa = carr_simplier;
    least_significant = lsb_val;
    // sum_csa = A_input.read();  //in sc_main sum_csa will be inputted into CPA A_input
    // carryout_csa = B_input.read();  //in sc_main sum_csa will be inputted into CPA B_input
    // least_significant = least_sig.read();

    for (x = 0; x < size; x++)
    { // x is column #
        if (x == 0)
        { // if A0
            carryin_cpa = 0;
            ain_cpa = sum_csa[x + 1];
            bin_cpa = carryout_csa[x];

            sum_cpa = ((ain_cpa ^ bin_cpa) ^ (carryin_cpa));
            carryout_cpa = ((ain_cpa & bin_cpa) | (carryin_cpa & bin_cpa) | (ain_cpa & carryin_cpa));

            sum_holder_cpa[x] = sum_cpa;
            msb_val[x] = sum_cpa;
            carryout_holder_cpa[x] = carryout_cpa;
        }

        else if (x == (size - 1))
        { // if x = A3
            carryin_cpa = 0;
            bin_cpa = carryout_holder_cpa[x - 1];
            ain_cpa = carryout_csa[x];

            sum_cpa = ((ain_cpa ^ bin_cpa) ^ (carryin_cpa));
            carryout_cpa = ((ain_cpa & bin_cpa) | (carryin_cpa & bin_cpa) | (ain_cpa & carryin_cpa));

            sum_holder_cpa[x] = sum_cpa;
            msb_val[x] = sum_cpa;
            carryout_holder_cpa[x] = carryout_cpa;
        }
        else
        {
            carryin_cpa = carryout_holder_cpa[x - 1]; // making C in equal to prev value C out
            bin_cpa = carryout_csa[x];
            ain_cpa = sum_csa[x + 1];

            sum_cpa = ((ain_cpa ^ bin_cpa) ^ (carryin_cpa));
            carryout_cpa = ((ain_cpa & bin_cpa) | (carryin_cpa & bin_cpa) | (ain_cpa & carryin_cpa));

            sum_holder_cpa[x] = sum_cpa;
            msb_val[x] = sum_cpa;
            carryout_holder_cpa[x] = carryout_cpa;
        }
        //cout << sum_holder_cpa[x];
    }

    msb_out.write(msb_val);

    for (z = 0; z < (size * 2); z++)
    {
        if (z < (size))
        {
            complete_output[z] = least_significant[z];
        }
        else
        {
            complete_output[z] = msb_val[z - size];
        }
    }

    complete.write(complete_output);
    cout << "Final output: "<< complete_output.to_int() << endl;
}
