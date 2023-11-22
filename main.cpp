#include <iostream>
#include "utility.h"
//#include <omp.h>
//#include "testing.h"

namespace fs = std::filesystem;

int main(){

    // Hex key                0x5465737431323334
    uint64_t bin_key =        0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =           "0101010001100101011100110111010000110001001100100011001100110100";

    // Hex plain text         0x4369616F6369616F
    string str_plain_text =    "0100001101101001011000010110111101100011011010010110000101101111";
    uint64_t bin_plain_text = 0b0100001101101001011000010110111101100011011010010110000101101111;

    uint64_t bin_ciphe_text = 0b0011111011110001111111101100011100110001010011101111111101000001;
    string str_ciph_text = "0011111011110001111111101100011100110001010011101111111101000001";

    const int n_datapoint = 4;

    const int test_per_datapoint = 5;

    int n_test = n_datapoint * test_per_datapoint;

    int64_t time_results[n_test];
    long iterations [n_test];
     long keys_per_datapoint[n_datapoint] = {100000, 500000, 1000000, 5000000};
//    long keys_per_datapoint[n_datapoint] = {1000000, 1000000, 1000000, 1000000, 1000000, 1000000};

//    if((sizeof(keys_per_datapoint) / sizeof(keys_per_datapoint[0])) != n_datapoint){
//        cerr << "Wrong dimension of keys attempt " << endl;
//        exit(-1);
//    }

    for(int i = 0; i < n_test; i++){
        iterations[i] = keys_per_datapoint[i / n_datapoint];
        cout << "iterations[i] = " << iterations[i] << endl;
    }


    auto start_bin = chrono::high_resolution_clock::now();
#pragma omp parallel for shared(time_results, bin_key, n_test, iterations, start_bin) default(none)
    for (int test = 0; test < n_test; test++) {
        for (uint64_t i = 0; i < iterations[test]; i++) {
            uint64_t inv_round_keys[16];
            generate_keys(bin_key, inv_round_keys);

            uint64_t ciptxt;
            encrypt(i, inv_round_keys);
        }
        auto stop_bin = chrono::high_resolution_clock::now();
        auto duration_bin = chrono::duration_cast<chrono::microseconds>(stop_bin - start_bin);
        time_results[test] = duration_bin.count();
    }
    cout << "Computation finished" <<endl;


    // Create directory to save data, if it doesn't exist
    if (!fs::exists("./../output")) {
        if (fs::create_directory("./../output")) {
            std::cout << "Directory created successfully" << std::endl;
        } else {
            std::cerr << "Unable to create the directory." << std::endl;
        }
    }


    // Write the result to a file
    std::ofstream f("./../output/output_data.txt", std::ios::trunc);
    if(f.is_open()) {
        for(int i = 0; i < n_test; i++){
            f << "Bitwise " << iterations[i] << " " << time_results[i] << endl;
        }
        f.close();
        std::cout << "Data saved successfully" << std::endl;
    }
    else {
        std::cerr << "Unable to open the file" << std::endl;
        exit(-1);
    }

    return 0;
}