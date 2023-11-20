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

void swap_bits_testing(){
    uint64_t a = 0b0011;
    uint64_t b = swap_bits(a);

    std::cout << "a: " << std::bitset<4>(a) << std::endl;
    std::cout << "b: " << std::bitset<4>(b) << std::endl;
}


void encrypt_testing(){

    uint64_t bin_key =        0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =           "0101010001100101011100110111010000110001001100100011001100110100";

    string str_plain_text =    "0100001101101001011000010110111101100011011010010110000101101111";
    uint64_t bin_plain_text = 0b0100001101101001011000010110111101100011011010010110000101101111;

    uint64_t bin_round_keys[16];
    string str_round_keys[16];

    generate_keys(bin_key, bin_round_keys);
    generate_keys(str_key, str_round_keys);

    generate_keys(bin_key, bin_round_keys);
    generate_keys(str_key, str_round_keys);

    // Main encryption algorithm

    // Initial permutation
    uint64_t bin_perm, bin_left, bin_right;
    bin_perm = permute(bin_plain_text, initial_permutation_bin, 64);
    // -----------------------
    string str_perm, str_left, str_right;
    for(int i : initial_permutation){
        str_perm += str_plain_text[i - 1];
    }

//    cout << "Initial perm " <<endl;
//    grid_compare(bin_perm, str_perm);




    // Initial split
    split(bin_perm, bin_left, bin_right, 32);
    // -----------------------
    str_left = str_perm.substr(0, 32);
    str_right = str_perm.substr(32, 32);
//    cout << "Initial split " <<endl;
//    grid_compare(bin_left, str_left);
//    grid_compare(bin_right, str_right);


    for(int round = 0; round < 16; round++) {


        // Expansion and Xor
        uint64_t bin_right_expanded;
        uint64_t bin_xored;
        bin_right_expanded = permute(bin_right, expansion_table_bin, 48);
        bin_xored = Xor(bin_round_keys[round], bin_right_expanded);
        // -----------------------
        string str_right_expanded;
        for(int j : expansion_table) {
            str_right_expanded += str_right[j-1];
        }
        string str_xored = Xor(str_round_keys[round], str_right_expanded);

//        cout << "ROUND: " << round << "   Expansion and Xor" <<endl;
//        grid_compare(bin_xored, str_xored);



        // S-box
        uint64_t bin_res = 0;
        string str_res;
        for(int j = 0; j < 8; j++){
            uint64_t bin_row, bin_col;
            // To get bin_row we need bits 5 and 0, and OR them to form 5 0
            bin_row = ((bin_xored >> (((8 - j) * 6) - 6)) & 0b1) | ((bin_xored >> (((8 - j) * 6) - 2) & 0b10));
            // To get bin_col we need bits 4,3,2,1
            bin_col = (bin_xored >> (((8 - j) * 6) - 5)) & 0b1111;
            uint64_t bin_val = substitution_boxes_bin[j][bin_row][bin_col];
            bin_val = swap_bits(bin_val);
            bin_res |= ((bin_val) << (((8 - j) * 4) - 4));
            // ---------------------------
            string str_row1 = str_xored.substr(j * 6,1) + str_xored.substr(j * 6 + 5,1);
            int str_row = convertBinaryToDecimal(str_row1);
            string str_col1 = str_xored.substr(j * 6 + 1,1) + str_xored.substr(j * 6 + 2,1) + str_xored.substr(j * 6 + 3,1) + str_xored.substr(j * 6 + 4,1);
            int str_col = convertBinaryToDecimal(str_col1);
            int str_int_val = substitution_boxes[j][str_row][str_col];
            string str_val = convertDecimalToBinary(str_int_val);
            str_res += str_val;

//            cout << "ROUND: " << round << "   S-box: " << j << endl;
//            cout << "Value of S-box Bin - Str: " << bin_val << "   " << str_int_val << endl;
//            grid_compare(bin_val, str_val);
//            cout << endl;
        }
//        cout << "ROUND: " << round  << "   After S-box"<< endl;
//        grid_compare(bin_res, str_res);
//        cout << endl;

        // Second permutation
        uint64_t bin_perm2;
        bin_perm2 = permute(bin_res, permutation_tab_bin, 32);
        bin_xored = Xor(bin_perm2, bin_left);
        bin_left = bin_xored;
        // -----------------
        string str_perm2;
        for(int j : permutation_tab){
            str_perm2 += str_res[j-1];
        }
        str_xored = Xor(str_perm2, str_left);
        str_left = str_xored;

//        cout << "ROUND: " << round  << "   After second permutation"<< endl;
//        grid_compare(bin_res, str_res);
//        cout << endl;


        // Special swap
        if(round < 15){
            uint64_t bin_temp = bin_right;
            bin_right = bin_xored;
            bin_left = bin_temp;
            // ----------------
            string str_temp = str_right;
            str_right = str_xored;
            str_left = str_temp;
        }
    }



    // Merge
    uint64_t bin_combined_text = merge(bin_left, bin_right, 32);
    // -----------
    string str_combined_text = str_left + str_right;

    cout << "After merge " << endl;
    grid_compare(bin_combined_text, str_combined_text);
    cout << endl;
    // 1110 1110 0101 0111 0110 1101 1101 1010 0100 1110 0101 0111 0110 0101 0110 1101


    // Inverse Permutation
    uint64_t bin_ciphertext;
    bin_ciphertext = permute(bin_combined_text, inverse_permutation_bin, 64);
    // ----------------
    string str_ciphertext;
    for(int i = 0; i < 64; i++){
        str_ciphertext+= str_combined_text[inverse_permutation[i]-1];
    }

    grid_compare(bin_ciphertext, str_ciphertext);

}


//uint64_t encrypt(const uint64_t& plain_text, const uint64_t (&round_keys)[16], uint64_t (&xoreds)[16], uint64_t (&results)[16]){
//    uint64_t perm, left, right;
//    perm = permute(plain_text, initial_permutation_bin, 64);
//
//    split(perm, left, right, 32);
//    for(int round = 0; round < 1; round++) {
//
//        uint64_t right_exp;
//        right_exp = permute(right, expansion_table_bin, 48);
//        // xored is 48 bits
//        uint64_t xored = Xor(round_keys[round], right_exp);
//
//        xoreds[round] = xored;// Debug
//
//        uint64_t res = 0;
//        for(int j = 8; j > 0; j--){
//            uint64_t row, col;
//            // To get row we need bits 5 and 0, and OR them to form 5 0
//            row = ((xored >> ((j * 6) - 6)) & 0b1) | ((xored >> ((j * 6) - 2) & 0b10));
//            // To get col we need bits 4,3,2,1
//            col = (xored >> ((j * 6) - 5)) & 0b1111;
//
//            res |= ((substitution_boxes_bin[8 - j][row][col]) << ((j * 4) - 4));
//        }
//        results[round] = res; // Debug
//        uint64_t perm2;
//        perm2 = permute(res, permutation_tab_bin, 32);
//        xored = Xor(perm2, left);
//        left = xored;
//        if(round < 15){
//            uint64_t temp = right;
//            right = xored;
//            left = temp;
//        }
//    }
//
//}

//string encrypt(string &plain_text, string (&round_keys)[16], string (&xoreds)[16], string (&results)[16]){
//    string perm;
//    for(int i : initial_permutation){
//        perm += plain_text[i - 1];
//    }
//
//    string left = perm.substr(0, 32);
//    string right = perm.substr(32, 32);
//
//
//    for(int round = 0; round < 1; round++) {
//        string right_expanded;
//        for(int j : expansion_table) {
//            right_expanded += right[j-1];
//        }
//        string xored = Xor(round_keys[round], right_expanded);
//
//        xoreds[round] = xored; // Debug
//
//        string res;
//        for(int j = 0; j < 8; j++){
//            string row1 = xored.substr(j * 6,1) + xored.substr(j * 6 + 5,1);
//            int row = convertBinaryToDecimal(row1);
//            string col1 = xored.substr(j * 6 + 1,1) + xored.substr(j * 6 + 2,1) + xored.substr(j * 6 + 3,1) + xored.substr(j * 6 + 4,1);
//            int col = convertBinaryToDecimal(col1);
//            int val = substitution_boxes[j][row][col];
//            res += convertDecimalToBinary(val);
//        }
//
//        results[round] = res; // Debug
//
//        string perm2;
//        for(int j : permutation_tab){
//            perm2 += res[j-1];
//        }
//        xored = Xor(perm2, left);
//        left = xored;
//        if(round < 15){
//            string temp = right;
//            right = xored;
//            left = temp;
//        }
//    }
////    string combined_text = left + right;
////    string ciphertext;
////    for(int i : inverse_permutation){
////        ciphertext+= combined_text[i-1];
////    }
////    return ciphertext;
//}