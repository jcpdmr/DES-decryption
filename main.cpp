#include <iostream>
#include "utility.h"

//int main(){
//    // Key is "Test1234"
//    string key = "0101010001100101011100110111010000110001001100100011001100110100";
//
//    // Plain text is "Ciaociao" converted in ASCII
//    string plain_text = "0100001101101001011000010110111101100011011010010110000101101111";
//
//    string round_keys[16];
//    generate_keys(key, round_keys);
//
//    cout <<endl;
//    cout << "Plain text: " << plain_text << endl;
//    string ciphertext = encrypt(plain_text, round_keys);
//    cout << "Ciphertext: "<< ciphertext <<endl;
//
//    // Reverse the order of the keys, for decryption
//    for (int i = 0, j = 16 - 1; i < 16/2; i++, j--)
//    {
//        string temp = round_keys[i];
//        round_keys[i] = round_keys[j];
//        round_keys[j] = temp;
//    }
//
//    string decrypted_text = encrypt(ciphertext, round_keys);
//    cout << "Decryptext: "<< decrypted_text <<endl;
//
//    if(decrypted_text == plain_text){
//        cout << "Message decrypted successfully! "<<endl;
//    }
//
//}

int main(){
    uint64_t bin_key =        0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =           "0101010001100101011100110111010000110001001100100011001100110100";

    string str_plain_text =    "0100001101101001011000010110111101100011011010010110000101101111";
    uint64_t bin_plain_text = 0b0100001101101001011000010110111101100011011010010110000101101111;

    uint64_t bin_round_keys[16];
    string str_round_keys[16];


    // Testing string                 |                           |
    string str_pc1 =                 "00000000000011111111111011110110010010001011000000001101";
    //                                | <- left shift rotate
    string str_c0 =                  "0000000000001111111111101111";
    string str_c1 =                  "0000000000011111111111011110";
    string str_c2 =                  "0000000000111111111110111100";
    //                                                             | <- left shift rotate
    string str_d0 =                                               "0110010010001011000000001101";
    string str_d1 =                                               "1100100100010110000000011010";
    string str_d2 =                                               "1001001000101100000000110101";

    generate_keys(bin_key, bin_round_keys);
    generate_keys(str_key, str_round_keys);

    string perm;
    for(int i : initial_permutation){
        perm += str_plain_text[i - 1];
    }
    string left = perm.substr(0, 32);
    string right = perm.substr(32, 32);


    string right_expanded;
    for(int j : expansion_table) {
        right_expanded += right[j - 1];
    }

    uint64_t bin_perm;
    bin_perm = encrypt(bin_plain_text, bin_round_keys);

//    grid_compare(bin_perm, right_expanded);

    return 0;
}