#include "testing.h"

void grid_compare_testing(){
    uint64_t key =                 0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =                "0101010001100101011100110111010000110001001100100011001100110100";
    string str_short_key =                          "011100110111010000110001111100100011001100110100";
    grid_compare(key, str_key);
    grid_compare(key, str_short_key);
}

void generate_keys_testing(){
    uint64_t key =          0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =         "0101010001100101011100110111010000110001001100100011001100110100";
    uint64_t bin_round_keys[16];
    grid();
    generate_keys(key, bin_round_keys);
    string str_round_keys[16];
    generate_keys(str_key, str_round_keys);
    for(int i = 0; i < 16; i++){
        grid_compare(bin_round_keys[i], str_round_keys[i]);
    }
}

void xor_testing(){
    uint64_t a = 0b0000000000101;
    uint64_t b = 0b0000001110110;
    uint64_t xored;
    xored = Xor(a, b);
    grid_bin(xored);
}

void timing(){
    uint64_t bin_key =          0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =         "0101010001100101011100110111010000110001001100100011001100110100";
    uint64_t bin_round_keys[16];
    string str_round_keys[16];

    auto start_bin = chrono::high_resolution_clock::now();
    generate_keys(bin_key, bin_round_keys);
    auto stop_bin = chrono::high_resolution_clock::now();

    auto start_str = chrono::high_resolution_clock::now();
    generate_keys(str_key, str_round_keys);
    auto stop_str = chrono::high_resolution_clock::now();

    auto duration_bin = chrono::duration_cast<chrono::microseconds>(stop_bin - start_bin);
    auto duration_str = chrono::duration_cast<chrono::microseconds>(stop_str - start_str);

    cout << "Bin : " << duration_bin.count() << endl;
    cout << "Str : " << duration_str.count() << endl;
}
