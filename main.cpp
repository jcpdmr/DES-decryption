#include <iostream>
#include "utility.h"
//#include <omp.h>
//#include "testing.h"

int main(){

    // Hex key                0x5465737431323334
    uint64_t bin_key =        0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =           "0101010001100101011100110111010000110001001100100011001100110100";

    // Hex plain text         0x4369616F6369616F
    string str_plain_text =    "0100001101101001011000010110111101100011011010010110000101101111";
    uint64_t bin_plain_text = 0b0100001101101001011000010110111101100011011010010110000101101111;

    uint64_t bin_ciphe_text = 0b0011111011110001111111101100011100110001010011101111111101000001;
    string str_ciph_text = "0011111011110001111111101100011100110001010011101111111101000001";

    auto start_bin = chrono::high_resolution_clock::now();
#pragma omp parallel for private(bin_key) default(none)
    for(uint64_t i = 0; i < 100000000; i++){
        uint64_t inv_round_keys[16];
        generate_keys(bin_key, inv_round_keys);

        uint64_t ciptxt;
        encrypt(i, inv_round_keys);
    }
    auto stop_bin = chrono::high_resolution_clock::now();


//    auto start_str = chrono::high_resolution_clock::now();
//    for(uint64_t i = 0; i < 1000; i++){
//        string str_round_keys[16];
//        generate_keys(str_key, str_round_keys);
//
//        ostringstream text;
//        text << setw(64) << setfill("0") << i;
//        encrypt(text, str_round_keys);
//    }
//    auto stop_str = chrono::high_resolution_clock::now();
//    auto duration_str = chrono::duration_cast<chrono::microseconds>(stop_str - start_str);
//    cout << "Bin : " << duration_str.count() << endl;
    auto duration_bin = chrono::duration_cast<chrono::microseconds>(stop_bin - start_bin);
    cout << "Bin : " << duration_bin.count() << endl;


//    uint64_t bin_round_keys[16];
//    string str_round_keys[16];
//    generate_keys(bin_key, bin_round_keys);
//    generate_keys(str_key, str_round_keys);
//
//    string ciphertxt;
//    uint64_t ciptxt;
//
//    ciphertxt = encrypt(str_plain_text, str_round_keys);
//    ciptxt = encrypt(bin_plain_text, bin_round_keys);
//    std::cout << "Ciphertext str: " << ciphertxt << std::endl;
//    std::cout << "Ciphertext bin: " << std::bitset<64>(ciptxt) << std::endl;

    return 0;
}