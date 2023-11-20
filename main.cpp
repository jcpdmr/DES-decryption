#include <iostream>
#include "utility.h"
#include "testing.h"


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

    generate_keys(bin_key, bin_round_keys);
    generate_keys(str_key, str_round_keys);

    uint64_t bin_results[16];
    uint64_t bin_xoreds[16];
    string str_results[16];
    string str_xoreds[16];

//    swap_bits_testing();
    encrypt_testing();

//    encrypt(str_plain_text, str_round_keys, str_xoreds, str_results);
//
//    uint64_t bin_perm;
//    bin_perm = encrypt(bin_plain_text, bin_round_keys, bin_xoreds, bin_results);
//
//    for(int round = 0; round < 1; round++){
//        cout << "ROUND: " << round << endl;
//        grid();
//        grid_compare(bin_xoreds[round], str_xoreds[round]);
//        grid_compare(bin_results[round], str_results[round]);

//    }
//    for(int round = 0; round < 16; round++){
//        cout << "ROUND: " << round << endl;
//        grid();
//        grid_compare(bin_results[round], str_results[round]);
//    }


//    grid_compare(bin_perm, right_expanded);

    return 0;
}