#include "testing.h"

// Testing variables created using 0101010001100101011100110111010000110001001100100011001100110100 as key
// and 0100001101101001011000010110111101100011011010010110000101101111 as plain text

string test_round_keys[16] = {
        "110100001010011010101110010001110010000001010110", // Key 01
        "111100001010111010100110110000001000001100010011", // Key 02
        "111100001011111000100010010101110010011000001000", // Key 03
        "111000001011011001110110011110000001000101001000", // Key 04
        "111001001101011001010110000000001111000000101110", // Key 05
        "011001101101001101110010011001000011110010100000", // Key 06
        "101011101101000101110011101010000000100001111011", // Key 07
        "101011110100001101011011000001111101101000010010", // Key 08
        "001011110101001111011011100010000000101100001010", // Key 09
        "001111110101000111001001110101000101001000010100", // Key 10
        "000110110100100111011001010100010000001011101000", // Key 11
        "000111010110100110011101100100001011100000001001", // Key 12
        "000101110010110110001101001000100011011000110100", // Key 13
        "010110110010110010100101001110010010100110100010", // Key 14
        "110110011010110010101100001001000100100000010011", // Key 15
        "110000011010110010101110101100100000100111000000" // Key 16
};


string msg_after_IP =   "1111111100000000100010001111111100000000111111101010101010011001";

string l0 =                                             "11111111000000001000100011111111";
string r0 =                                             "00000000111111101010101010011001";
string exp_r0 =                         "100000000001011111111101010101010101010011110010";
string k0_xored_ex_r0 =                 "010100001011000101010011000100100111010010100100";
string sub_k0_xored_ex_r0 =                             "01100010000001110100110011000100";
string per_sub_k0_xored_ex_r0 =                         "11010000010101001001001000101001";

string l1 =                                             "00000000111111101010101010011001";
string r1 =                                             "00101111010101000001101011010110";

string l2 =                                             "00101111010101000001101011010110";
string r2 =                                             "01111111001010001010010001011001";

string l3 =                                             "01111111001010001010010001011001";
string r3 =                                             "01111000010100111110010101001010";

string l15 =                                            "00111010100111100111110101001000";
string r15 =                                            "01001110010101110110010101101101";

string l16 =                                            "01001110010101110110010101101101";
string r16 =                                            "11101110010101110110110111011010";

string merged =         "1110111001010111011011011101101001001110010101110110010101101101";

string msg_aft_inv_IP = "0011111011110001111111101100011100110001010011101111111101000001";

string test_ciphertxt = "0011111011110001111111101100011100110001010011101111111101000001";

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
    for(int i = 0; i < 16; i++){
        grid_compare(bin_round_keys[i], test_round_keys[i]);
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
//    grid_compare(bin_perm, msg_after_IP);




    // Initial split
    split(bin_perm, bin_left, bin_right, 32);
    // -----------------------
    str_left = str_perm.substr(0, 32);
    str_right = str_perm.substr(32, 32);
//    cout << "Initial split " <<endl;
//    grid_compare(bin_left, l0);
//    grid_compare(bin_right, r0);
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
        for (int j: expansion_table) {
            str_right_expanded += str_right[j - 1];
        }
        string str_xored = Xor(str_round_keys[round], str_right_expanded);

//        cout << "ROUND: " << round << "   Expansion and Xor" <<endl;
//        if (round == 0){
//          grid_compare(bin_xored, k0_xored_ex_r0);
//        }
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
//        if(round == 0){
//            grid_compare(bin_res, sub_k0_xored_ex_r0);
//        }
//        grid_compare(bin_res, str_res);
//        cout << endl;




        // Second permutation
        uint64_t bin_perm2;
        bin_perm2 = permute(bin_res, permutation_tab_bin, 32);
        // -----------------
        string str_perm2;
        for(int j : permutation_tab){
            str_perm2 += str_res[j-1];
        }

//        cout << "ROUND: " << round  << "   After second permutation"<< endl;
//        if(round == 0){
//            grid_compare(bin_perm2, per_sub_k0_xored_ex_r0);
//        }
//        grid_compare(bin_res, str_res);
//        cout << endl;



        // Xor
        bin_xored = Xor(bin_perm2, bin_left);
        bin_left = bin_xored;
        // ---------------
        str_xored = Xor(str_perm2, str_left);

//        cout << "ROUND: " << round  << "   After xor"<< endl;
//        if(round == 0){
//            grid_compare(bin_perm2, per_sub_k0_xored_ex_r0);
//        }
//        grid_compare(bin_xored, str_xored);
//        cout << endl;



        // Assignment L and R
        uint64_t bin_temp = bin_right;
        bin_right = bin_xored;
        bin_left = bin_temp;
        // --------------
        string str_temp = str_right;
        str_right = str_xored;
        str_left = str_temp;


//        cout << "ROUND: " << round  << "   After assignment L and R"<< endl;
//        if(round == 0) {
//            grid_compare(bin_left, l1);
//            grid_compare(bin_right, r1);
//        }
//        if(round == 15){
//            grid_compare(bin_left, l16);
//            grid_compare(bin_right, r16);
//        }
//        grid_compare(bin_left, str_left);
//        grid_compare(bin_right, str_right);
//        cout << endl;
    }



    // Merge
    uint64_t bin_combined_text = merge(bin_right, bin_left, 32);
    // -----------
    string str_combined_text = str_right + str_left;

//    cout << "After merge " << endl;
//    grid_compare(bin_combined_text, merged);
//    grid_compare(bin_combined_text, str_combined_text);
//    cout << endl;


    // Inverse Permutation
    uint64_t bin_ciphertext;
    bin_ciphertext = permute(bin_combined_text, inverse_permutation_bin, 64);
    // ----------------
    string str_ciphertext;
    for(int i : inverse_permutation){
        str_ciphertext+= str_combined_text[i-1];
    }
//    cout << "After inverse permutation " << endl;
//    grid_compare(bin_ciphertext, test_ciphertxt);
    grid_compare(bin_ciphertext, str_ciphertext);


}

void convertDecimalToBinary_testing(){
    int value = 2;

    // New code
    int int_decimal = value;
    bitset<4> bit_decimal = int_decimal;
    string str_decimal = bit_decimal.to_string();
    cout << "New function     : " << str_decimal << endl;

}

void convertBinaryToDecimal_testing(){

    string val = "1101";

    // New
    int int_decimal = (int)((bitset<4>) val).to_ulong();
    cout << "New function     : " << int_decimal << endl;
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