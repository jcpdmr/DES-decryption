#include <iostream>
#include "utility.h"
//#include <omp.h>
//#include "testing.h"

namespace fs = std::filesystem;

int main(){

    // Hex key                0x5465737431323334     base10: 6081393814712496948
    uint64_t bin_key =        0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =           "0101010001100101011100110111010000110001001100100011001100110100";

    // Hex plain text         0x4369616F6369616F
    uint64_t bin_plain_text = 0b0100001101101001011000010110111101100011011010010110000101101111;
    string str_plain_text =    "0100001101101001011000010110111101100011011010010110000101101111";

    uint64_t bin_ciphe_text = 0b0011111011110001111111101100011100110001010011101111111101000001;
    string str_ciph_text = "0011111011110001111111101100011100110001010011101111111101000001";

    const int n_datapoints = 7;
    const int tests_per_datapoint = 3;
    int n_tot_tests = n_datapoints * tests_per_datapoint;
    uint64_t attempts_per_datapoint[n_datapoints] = {100000, 500000, 1000000, 5000000, 10000000, 50000000, 100000000};

    uint64_t test[n_tot_tests];
    string results[n_tot_tests];

    // Populate the test array assigning the number of attempts to do for each test
    for(int i = 0; i < n_tot_tests; i++){
        test[i] = attempts_per_datapoint[i / tests_per_datapoint];
        cout << "tests[i] = " << test[i] << endl;
    }

    cout << "Benchmark in progress..." << endl;
    for(int i = 0; i < n_tot_tests; i++){
        uint64_t attempts = test[i];
        // To be sure to not find the correct key and try all attempts we start from a specific initial key
        uint64_t initial_key = bin_key - 100 * attempts;

        auto start_bin = chrono::high_resolution_clock::now();
        // Parallel part inside crack_password
        crack_password(initial_key, attempts, bin_plain_text, bin_ciphe_text);
        auto stop_bin = chrono::high_resolution_clock::now();
        auto duration_bin = chrono::duration_cast<chrono::milliseconds >(stop_bin - start_bin).count();
        string a = to_string(duration_bin);
        results[i] = "Binary - Attempts " + to_string((unsigned long long)attempts) + " - " + to_string(duration_bin);
    }

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
        for(int i = 0; i < n_tot_tests; i++){
            f <<  results[i] << endl;
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