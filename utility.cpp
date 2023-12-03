#include "utility.h"

using namespace std;

//string permute(string& init_str, const int* pattern, int size){
//    string perm_string;
//    for(int i = 0; i < size; i++){
//        perm_string += init_str[pattern[i] - 1]; // understand why -1
//    }
//    return perm_string;
//}

inline uint64_t permute(const uint64_t &key, const int* pattern, const int n) {
    uint64_t perm_key = 0;
    for(int i = 0; i < n; i++){
        // ((key >> pattern[i]) & 1) check if the bit of key in position 7, 15, 23, ... from
        // the right is a 1 or 0
        // |= () << i add the bit in position 0, 1, 2, ... to the permuted key

        perm_key |= (((key >> pattern[i]) & 1) << (n - 1 - i));
    }
    return perm_key;
}

void grid(bool right_least_sign){
    if(right_least_sign){
        // |64 |63 |62 |61 |60 ...
        for (int i = 63; i >= 0; i--) {
            cout << "|" << setw(2) << setfill(' ') << i << " ";
        }
        cout << endl;
    }
    else{
        // | 0 | 1 | 2 | 3 | 4 ...
        for (int i = 0; i <= 63; i++) {
            cout << "|" << setw(2) << setfill(' ') << i << " ";
        }
        cout << endl;
    }
}

void grid_bin(uint64_t& bin_val){
    //| 0 | 1 | 0 | 1 | 0 ... of the bin value
    for (int i = 63; i >= 0; i--) {
        cout << "| " << ((bin_val >> i) & 1) << " ";
    }
    cout << endl;
}

void grid_str(string& str_val){
    //| 0 | 1 | 0 | 1 | 0 ... of the str value, creating padding if needed
    if ((int)str_val.length() < 64){
        // Add empty padding |  |  |  |
        for(int i = 0; i < 64 - (int)str_val.length(); i++){
            cout << "|   " ;
        }
    }
    for (char i : str_val){
        cout << "| " << i  << " " ;
    }
    cout << endl;
}

void grid_compare(uint64_t& bin_val, string& str_val){
    grid_bin(bin_val);
    grid_str(str_val);
    // Compare
    for (int i = 63; i >= 0; i--){
        if ((int)str_val.length() <= i){
            // If str is less than 64 chars skip the iterations and add empty padding
            cout << "  . " ;
        }
        else{
            // Extracting the i-th value
            int bin_bit = (int)(bin_val >> i) & 1;
            int str_bit = (str_val[(int)str_val.length() - 1 - i] == '1') ? 1 : 0;
            if(bin_bit == str_bit){
                cout << "    ";
            }
            else{
                // Found a different bit, print the bit position
                cout << " " << setw(2) << setfill(' ') << i << " " ;
            }
        }
    }
    cout << "\n" << endl;
}

string shift_left_once(string key_chunk){
    string shifted;
    for(int i = 1; i < 28; i++){
        shifted += key_chunk[i];
    }
    shifted += key_chunk[0];
    return shifted;
}

inline uint64_t shift_left(const uint64_t bin_key, const bool shift_twice){
    // The key has 28 bits
    uint64_t shifted_key;
    // Shift first time
    int most_sign_bit = (int)(bin_key >> 27) & 1;
    shifted_key = (bin_key << 1) & (~(1 << 28)) | most_sign_bit;
    // If needed, shift another time
    if(shift_twice){
        most_sign_bit = (int)(shifted_key>> 27) & 1;
        shifted_key = (shifted_key << 1) & (~(1 << 28)) | most_sign_bit;
    }
    return shifted_key;
}

string shift_left_twice(string key_chunk){
    string shifted;
    for(int i = 0; i < 2; i++){
        for(int j = 1; j < 28; j++){
            shifted += key_chunk[j];
        }
        shifted += key_chunk[0];
        key_chunk= shifted;
        shifted ="";
    }
    return key_chunk;
}

void split(const uint64_t &key, uint64_t &left, uint64_t&right, int bit_len_of_block){
    left = key >> bit_len_of_block;
    right = key & ((1ULL << bit_len_of_block) - 1);
}

inline uint64_t merge(uint64_t &left, uint64_t&right, const int bit_len_of_block){
    uint64_t merged_key;
    merged_key = (left << bit_len_of_block) | right;
    return merged_key;
}

void generate_keys(uint64_t key, uint64_t(&round_keys)[16]){
    // key is 64 bit, perm_key is 56 bit
    uint64_t perm_key, left, right;
    perm_key = permute(key, pc1_bin, 56);

    split(perm_key, left, right, 28);
    for(int n_key = 0; n_key < 16; n_key++){
        if(n_key == 0 || n_key == 1 || n_key == 8 || n_key == 15 ){
            left = shift_left(left);
            right = shift_left(right);
        }
        else{
            left = shift_left(left, true);
            right = shift_left(right, true);
        }
        uint64_t combined_key = merge(left, right, 28);
        uint64_t round_key;

        round_key = permute(combined_key, pc2_bin, 48);

        // Add the key to the round keys array
        round_keys[n_key] = round_key;
    }
}

void generate_inv_keys(uint64_t key, uint64_t(&inv_round_keys)[16]){
    // key is 64 bit, perm_key is 56 bit
    uint64_t perm_key, left, right;
    perm_key = permute(key, pc1_bin, 56);

    split(perm_key, left, right, 28);
    for(int n_key = 0; n_key < 16; n_key++){
        if(n_key == 0 || n_key == 1 || n_key == 8 || n_key == 15 ){
            left = shift_left(left);
            right = shift_left(right);
        }
        else{
            left = shift_left(left, true);
            right = shift_left(right, true);
        }
        uint64_t combined_key = merge(left, right, 28);
        uint64_t round_key;

        round_key = permute(combined_key, pc2_bin, 48);

        // Add the key to the round keys array, starting from the last to get them in inverted order
        inv_round_keys[15 - n_key] = round_key;
    }
}

void generate_keys(string key, string(&round_keys)[16]){
    string perm_key;
    for(int i : pc1){
        perm_key+= key[i-1];
    }
    string left= perm_key.substr(0, 28);
    string right= perm_key.substr(28, 28);
    for(int n_key = 0; n_key < 16; n_key++){
        if(n_key == 0 || n_key == 1 || n_key==8 || n_key==15 ){
            left= shift_left_once(left);
            right= shift_left_once(right);
        }
        else{
            left= shift_left_twice(left);
            right= shift_left_twice(right);
        }
        string combined_key = left + right;
        string round_key;
        for(int j : pc2){
            round_key += combined_key[j-1];
        }
        round_keys[n_key] = round_key;
    }
}

void generate_inv_keys(string key, string(&round_keys)[16]){
    string perm_key;
    for(int i : pc1){
        perm_key+= key[i-1];
    }
    string left= perm_key.substr(0, 28);
    string right= perm_key.substr(28, 28);
    for(int n_key = 0; n_key < 16; n_key++){
        if(n_key == 0 || n_key == 1 || n_key==8 || n_key==15 ){
            left= shift_left_once(left);
            right= shift_left_once(right);
        }
        else{
            left= shift_left_twice(left);
            right= shift_left_twice(right);
        }
        string combined_key = left + right;
        string round_key;
        for(int j : pc2){
            round_key += combined_key[j-1];
        }
        round_keys[15 - n_key] = round_key;
    }
}

string convertDecimalToBinary(int decimal)
{
    string binary = ((bitset<4>) decimal).to_string();
    return binary;
}

int convertBinaryToDecimal(const string& binary)
{
    int decimal = (int)((bitset<4>) binary).to_ulong();
    return decimal;
}

inline uint64_t Xor(const uint64_t& a, const uint64_t& b){
    uint64_t xor_result;
    xor_result = a ^ b;
    return xor_result;
}

string Xor(string a, string b){
    string result;
    int size = (int) b.size();
    for(int i = 0; i < size; i++){
        if(a[i] != b[i]){
            result += "1";
        }
        else{
            result += "0";
        }
    }
    return result;
}

uint64_t encrypt(const uint64_t& bin_plain_text, const uint64_t (&bin_round_keys)[16]){
    // Initial permutation
    uint64_t bin_perm, bin_left, bin_right;
    bin_perm = permute(bin_plain_text, initial_permutation_bin, 64);

    // Initial split
    split(bin_perm, bin_left, bin_right, 32);
    for(uint64_t bin_round_key : bin_round_keys) {

        // Expansion and Xor
        uint64_t bin_right_expanded;
        uint64_t bin_xored;
        bin_right_expanded = permute(bin_right, expansion_table_bin, 48);
        bin_xored = Xor(bin_round_key, bin_right_expanded);

        // S-box
        uint64_t bin_res = 0;
        for(int j = 0; j < 8; j++){
            uint64_t bin_row, bin_col;
            // To get bin_row we need bits 5 and 0, and OR them to form 5 0
            bin_row = ((bin_xored >> (((8 - j) * 6) - 6)) & 0b1) | ((bin_xored >> (((8 - j) * 6) - 2) & 0b10));
            // To get bin_col we need bits 4,3,2,1
            bin_col = (bin_xored >> (((8 - j) * 6) - 5)) & 0b1111;
            uint64_t bin_val = substitution_boxes_bin[j][bin_row][bin_col];
            bin_res |= ((bin_val) << (((8 - j) * 4) - 4));
        }

        // Second permutation
        uint64_t bin_perm2;
        bin_perm2 = permute(bin_res, permutation_tab_bin, 32);

        // Xor
        bin_xored = Xor(bin_perm2, bin_left);

        // Assignment L and R
        uint64_t bin_temp = bin_right;
        bin_right = bin_xored;
        bin_left = bin_temp;
    }

    // Merge
    uint64_t bin_combined_text = merge(bin_right, bin_left, 32);

    // Inverse Permutation
    uint64_t bin_ciphertext;
    bin_ciphertext = permute(bin_combined_text, inverse_permutation_bin, 64);

    return bin_ciphertext;
}

string encrypt(const string &plain_text, const string (&round_keys)[16]) {
    string perm;
    for(int i : initial_permutation){
        perm += plain_text[i - 1];
    }
    string left = perm.substr(0, 32);
    string right = perm.substr(32, 32);

    for(int round = 0; round < 16; round++) {
        string right_expanded;
        for(int j : expansion_table) {
            right_expanded += right[j-1];
        }
        string xored = Xor(round_keys[round], right_expanded);
        string res;
        for(int j = 0; j < 8; j++){
            string row1 = xored.substr(j * 6,1) + xored.substr(j * 6 + 5,1);
            int row = convertBinaryToDecimal(row1);
            string col1 = xored.substr(j * 6 + 1,1) + xored.substr(j * 6 + 2,1) + xored.substr(j * 6 + 3,1) + xored.substr(j * 6 + 4,1);
            int col = convertBinaryToDecimal(col1);
            int val = substitution_boxes[j][row][col];
            res += convertDecimalToBinary(val);
        }
        string perm2;
        for(int j : permutation_tab){
            perm2 += res[j-1];
        }
        xored = Xor(perm2, left);
        left = xored;
        if(round < 15){
            string temp = right;
            right = xored;
            left = temp;
        }
    }
    string combined_text = left + right;
    string ciphertext;
    for(int i : inverse_permutation){
        ciphertext+= combined_text[i-1];
    }
    return ciphertext;
}

uint64_t swap_bits(uint64_t a) {
    // Method 1
    // Get bit 3 and put in position 0 : (a & (1ULL << 3)) >> 3)
    // Get bit 0 and put in position 3 : ((a & 1ULL) << 3)
    // Get bit 2 and put in position 1 : ((a & (1ULL << 2)) >> 1)
    // Get bit 1 and put in position 2 : ((a & (1ULL << 1)) << 1)
    uint64_t b = ((a & (1ULL << 3)) >> 3) | ((a & 1ULL) << 3) | ((a & (1ULL << 2)) >> 1) | ((a & (1ULL << 1)) << 1);

    return b;
}

void crack_password_parallel_binary(const uint64_t initial_key, const uint64_t attempts, const uint64_t correct_plaintext, const uint64_t correct_ciphertext){

    uint64_t correct_key = 0;

    #pragma omp parallel for shared(initial_key, attempts, correct_plaintext, correct_ciphertext, correct_key) default(none)
    for(uint64_t key = initial_key; key < (initial_key + attempts); key++){
        // Generate inverse keys
        uint64_t inv_round_keys[16];
        generate_inv_keys(key, inv_round_keys);

        // Decrypt the ciphertext using inverse keys
        uint64_t plain_txt_attempt = encrypt(correct_ciphertext, inv_round_keys);

        // Check if decrypted text is the correct one
        if(plain_txt_attempt == correct_plaintext){
            correct_key = key - 1;
            #pragma omp cancel for
        }
    }

    if(correct_key){
        cout << "Found key! Binary key: " << bitset<64>(correct_key) << endl;
    }
}

void crack_password_sequential_binary(const uint64_t initial_key, const uint64_t attempts, const uint64_t correct_plaintext, const uint64_t correct_ciphertext){

    uint64_t correct_key = 0;

    for(uint64_t key = initial_key; key < (initial_key + attempts); key++){
        // Generate inverse keys
        uint64_t inv_round_keys[16];
        generate_inv_keys(key, inv_round_keys);

        // Decrypt the ciphertext using inverse keys
        uint64_t plain_txt_attempt = encrypt(correct_ciphertext, inv_round_keys);

        // Check if decrypted text is the correct one
        if(plain_txt_attempt == correct_plaintext){
            correct_key = key - 1;

        }
    }

    if(correct_key){
        cout << "Found key! Binary key: " << bitset<64>(correct_key) << endl;
    }
}

void benchmark_parallel_binary(const uint64_t correct_plaintext, const uint64_t correct_ciphertext, const uint64_t bin_key){
    const int n_datapoints = 9;
    const int tests_per_datapoint = 6;
    uint64_t attempts_per_datapoint[n_datapoints] = {10000, 50000, 100000, 500000, 1000000, 5000000, 10000000, 50000000, 100000000};

    int n_tot_tests = n_datapoints * tests_per_datapoint;

    uint64_t test[n_tot_tests];
    string results[n_tot_tests];

    // Populate the test array assigning the number of attempts to do for each test
    for(int i = 0; i < n_tot_tests; i++){
        test[i] = attempts_per_datapoint[i / tests_per_datapoint];
        // cout << "tests[i] = " << test[i] << endl;
    }


    cout << "Num of datapoints: " << n_datapoints << "    Test per datapoint: " << tests_per_datapoint << "    Attempts per datapoint: " ;
    for(uint64_t i : attempts_per_datapoint){
        cout << i << "  ";
    }
    cout << endl;
    cout << "Parallel Binary Benchmark in progress..." << endl;
    auto start_benchmark_bin = chrono::high_resolution_clock::now();

    for(int i = 0; i < n_tot_tests; i++){
        uint64_t attempts = test[i];
        // To be sure to not find the correct key and try all attempts we start from a specific initial key
        uint64_t initial_key = bin_key - 100 * attempts;

        auto start_bin = chrono::high_resolution_clock::now();
        // Parallel part inside crack_password_parallel_binary
        crack_password_parallel_binary(initial_key, attempts, correct_plaintext, correct_ciphertext);
        auto stop_bin = chrono::high_resolution_clock::now();

        auto duration_bin = chrono::duration_cast<chrono::microseconds >(stop_bin - start_bin).count();
        results[i] = "Binary - Attempts " + to_string((unsigned long long)attempts) + " - " + to_string(duration_bin) + " us";
    }

    auto stop_benchmark_bin = chrono::high_resolution_clock::now();
    auto duration_benchmark_bin = chrono::duration_cast<chrono::milliseconds >(stop_benchmark_bin - start_benchmark_bin).count();
    cout << "Benchmark elapsed time (with implicit barrier): " << duration_benchmark_bin << " ms" << endl;

    // Write the result to a file
    std::ofstream f("./../output/output_data_parallel_binary.txt", std::ios::trunc);
    if(f.is_open()) {
        f << "Num of datapoints: " << n_datapoints << "    Test per datapoint: " << tests_per_datapoint << "    Attempts per datapoint: " ;
        for(uint64_t i : attempts_per_datapoint){
            f << i << "  ";
        }
        f << endl;
        for(int i = 0; i < n_tot_tests; i++){
            f <<  results[i] << endl;
        }
        f << "Benchmark elapsed time (with implicit barrier): " << duration_benchmark_bin << " ms" << endl;
        f.close();
        std::cout << "Data saved successfully" << std::endl;
    }
    else {
        std::cerr << "Unable to open the file" << std::endl;
        exit(-1);
    }
}

void benchmark_sequential_binary(const uint64_t correct_plaintext, const uint64_t correct_ciphertext, const uint64_t bin_key){
    const int n_datapoints = 6;
    const int tests_per_datapoint = 6;
    uint64_t attempts_per_datapoint[n_datapoints] = {10000, 50000, 100000, 500000, 1000000, 5000000};

    int n_tot_tests = n_datapoints * tests_per_datapoint;

    uint64_t test[n_tot_tests];
    string results[n_tot_tests];

    // Populate the test array assigning the number of attempts to do for each test
    for(int i = 0; i < n_tot_tests; i++){
        test[i] = attempts_per_datapoint[i / tests_per_datapoint];
        // cout << "tests[i] = " << test[i] << endl;
    }


    cout << "Num of datapoints: " << n_datapoints << "    Test per datapoint: " << tests_per_datapoint << "    Attempts per datapoint: " ;
    for(uint64_t i : attempts_per_datapoint){
        cout << i << "  ";
    }
    cout << endl;
    cout << "Sequential Binary Benchmark in progress..." << endl;
    auto start_benchmark_bin = chrono::high_resolution_clock::now();

    for(int i = 0; i < n_tot_tests; i++){
        uint64_t attempts = test[i];
        // To be sure to not find the correct key and try all attempts we start from a specific initial key
        uint64_t initial_key = bin_key - 100 * attempts;

        auto start_bin = chrono::high_resolution_clock::now();
        // Parallel part inside crack_password_parallel_binary
        crack_password_sequential_binary(initial_key, attempts, correct_plaintext, correct_ciphertext);
        auto stop_bin = chrono::high_resolution_clock::now();

        auto duration_bin = chrono::duration_cast<chrono::microseconds >(stop_bin - start_bin).count();
        results[i] = "Binary - Attempts " + to_string((unsigned long long)attempts) + " - " + to_string(duration_bin) + " us";
    }

    auto stop_benchmark_bin = chrono::high_resolution_clock::now();
    auto duration_benchmark_bin = chrono::duration_cast<chrono::milliseconds >(stop_benchmark_bin - start_benchmark_bin).count();
    cout << "Benchmark elapsed time: " << duration_benchmark_bin << " ms" << endl;

    // Write the result to a file
    std::ofstream f("./../output/output_data_sequential_binary.txt", std::ios::trunc);
    if(f.is_open()) {
        f << "Num of datapoints: " << n_datapoints << "    Test per datapoint: " << tests_per_datapoint << "    Attempts per datapoint: " ;
        for(uint64_t i : attempts_per_datapoint){
            f << i << "  ";
        }
        f << endl;
        for(int i = 0; i < n_tot_tests; i++){
            f <<  results[i] << endl;
        }
        f << "Benchmark elapsed time: " << duration_benchmark_bin << " ms" << endl;
        f.close();
        std::cout << "Data saved successfully" << std::endl;
    }
    else {
        std::cerr << "Unable to open the file" << std::endl;
        exit(-1);
    }
}

void crack_password_sequential_string(uint64_t initial_key, uint64_t attempts, const string& correct_plaintext, const string& correct_ciphertext){

    uint64_t correct_key = 0;

    for(uint64_t key = initial_key; key < (initial_key + attempts); key++){
        // Generate inverse keys
        string str_key = to_string(key);
        string inv_round_keys[16];
        generate_inv_keys(str_key, inv_round_keys);

        // Decrypt the ciphertext using inverse keys
        string plain_txt_attempt = encrypt(correct_ciphertext, inv_round_keys);

        // Check if decrypted text is the correct one
        if(plain_txt_attempt == correct_plaintext){
            correct_key = key - 1;
        }
    }

    if(correct_key){
        cout << "Found key! Binary key: " << bitset<64>(correct_key) << endl;
    }
}

void crack_password_parallel_string(uint64_t initial_key, uint64_t attempts, const string& correct_plaintext, const string& correct_ciphertext){

    uint64_t correct_key = 0;
    #pragma omp parallel for shared(initial_key, attempts, correct_plaintext, correct_ciphertext, correct_key) default(none)
    for(uint64_t key = initial_key; key < (initial_key + attempts); key++){
        // Generate inverse keys
        string str_key = to_string(key);
        string inv_round_keys[16];
        generate_inv_keys(str_key, inv_round_keys);

        // Decrypt the ciphertext using inverse keys
        string plain_txt_attempt = encrypt(correct_ciphertext, inv_round_keys);

        // Check if decrypted text is the correct one
        if(plain_txt_attempt == correct_plaintext){
            correct_key = key - 1;
            #pragma omp cancel for
        }
    }

    if(correct_key){
        cout << "Found key! Binary key: " << bitset<64>(correct_key) << endl;
    }
}

void benchmark_sequential_string(const string& correct_plaintext, const string& correct_ciphertext, const uint64_t bin_key){
    const int n_datapoints = 4;
    const int tests_per_datapoint = 6;
    uint64_t attempts_per_datapoint[n_datapoints] = {10000, 50000, 100000, 500000};

    int n_tot_tests = n_datapoints * tests_per_datapoint;

    uint64_t test[n_tot_tests];
    string results[n_tot_tests];

    // Populate the test array assigning the number of attempts to do for each test
    for(int i = 0; i < n_tot_tests; i++){
        test[i] = attempts_per_datapoint[i / tests_per_datapoint];
        // cout << "tests[i] = " << test[i] << endl;
    }


    cout << "Num of datapoints: " << n_datapoints << "    Test per datapoint: " << tests_per_datapoint << "    Attempts per datapoint: " ;
    for(uint64_t i : attempts_per_datapoint){
        cout << i << "  ";
    }
    cout << endl;
    cout << "Sequential String Benchmark in progress..." << endl;
    auto start_benchmark_bin = chrono::high_resolution_clock::now();

    for(int i = 0; i < n_tot_tests; i++){
        uint64_t attempts = test[i];
        // To be sure to not find the correct key and try all attempts we start from a specific initial key
        uint64_t initial_key = bin_key - 100 * attempts;

        auto start_bin = chrono::high_resolution_clock::now();
        // Parallel part inside crack_password_parallel_binary
        crack_password_sequential_string(initial_key, attempts, correct_plaintext, correct_ciphertext);
        auto stop_bin = chrono::high_resolution_clock::now();

        auto duration_bin = chrono::duration_cast<chrono::microseconds >(stop_bin - start_bin).count();
        results[i] = "String - Attempts " + to_string((unsigned long long)attempts) + " - " + to_string(duration_bin) + " us";
    }

    auto stop_benchmark_bin = chrono::high_resolution_clock::now();
    auto duration_benchmark_bin = chrono::duration_cast<chrono::milliseconds >(stop_benchmark_bin - start_benchmark_bin).count();
    cout << "Benchmark elapsed time: " << duration_benchmark_bin << " ms" << endl;

    // Write the result to a file
    std::ofstream f("./../output/output_data_sequential_string.txt", std::ios::trunc);
    if(f.is_open()) {
        f << "Num of datapoints: " << n_datapoints << "    Test per datapoint: " << tests_per_datapoint << "    Attempts per datapoint: " ;
        for(uint64_t i : attempts_per_datapoint){
            f << i << "  ";
        }
        f << endl;
        for(int i = 0; i < n_tot_tests; i++){
            f <<  results[i] << endl;
        }
        f << "Benchmark elapsed time: " << duration_benchmark_bin << " ms" << endl;
        f.close();
        std::cout << "Data saved successfully" << std::endl;
    }
    else {
        std::cerr << "Unable to open the file" << std::endl;
        exit(-1);
    }
}

void benchmark_parallel_string(const string& correct_plaintext, const string& correct_ciphertext, const uint64_t bin_key){
    const int n_datapoints = 5;
    const int tests_per_datapoint = 6;
    uint64_t attempts_per_datapoint[n_datapoints] = {10000, 50000, 100000, 500000, 1000000};

    int n_tot_tests = n_datapoints * tests_per_datapoint;

    uint64_t test[n_tot_tests];
    string results[n_tot_tests];

    // Populate the test array assigning the number of attempts to do for each test
    for(int i = 0; i < n_tot_tests; i++){
        test[i] = attempts_per_datapoint[i / tests_per_datapoint];
        // cout << "tests[i] = " << test[i] << endl;
    }


    cout << "Num of datapoints: " << n_datapoints << "    Test per datapoint: " << tests_per_datapoint << "    Attempts per datapoint: " ;
    for(uint64_t i : attempts_per_datapoint){
        cout << i << "  ";
    }
    cout << endl;
    cout << "Parallel String Benchmark in progress..." << endl;
    auto start_benchmark_bin = chrono::high_resolution_clock::now();

    for(int i = 0; i < n_tot_tests; i++){
        uint64_t attempts = test[i];
        // To be sure to not find the correct key and try all attempts we start from a specific initial key
        uint64_t initial_key = bin_key - 100 * attempts;

        auto start_bin = chrono::high_resolution_clock::now();
        // Parallel part inside crack_password_parallel_binary
        crack_password_parallel_string(initial_key, attempts, correct_plaintext, correct_ciphertext);
        auto stop_bin = chrono::high_resolution_clock::now();

        auto duration_bin = chrono::duration_cast<chrono::microseconds >(stop_bin - start_bin).count();
        results[i] = "String - Attempts " + to_string((unsigned long long)attempts) + " - " + to_string(duration_bin) + " us";
    }

    auto stop_benchmark_bin = chrono::high_resolution_clock::now();
    auto duration_benchmark_bin = chrono::duration_cast<chrono::milliseconds >(stop_benchmark_bin - start_benchmark_bin).count();
    cout << "Benchmark elapsed time: " << duration_benchmark_bin << " ms" << endl;

    // Write the result to a file
    std::ofstream f("./../output/output_data_parallel_string.txt", std::ios::trunc);
    if(f.is_open()) {
        f << "Num of datapoints: " << n_datapoints << "    Test per datapoint: " << tests_per_datapoint << "    Attempts per datapoint: " ;
        for(uint64_t i : attempts_per_datapoint){
            f << i << "  ";
        }
        f << endl;
        for(int i = 0; i < n_tot_tests; i++){
            f <<  results[i] << endl;
        }
        f << "Benchmark elapsed time: " << duration_benchmark_bin << " ms" << endl;
        f.close();
        std::cout << "Data saved successfully" << std::endl;
    }
    else {
        std::cerr << "Unable to open the file" << std::endl;
        exit(-1);
    }
}