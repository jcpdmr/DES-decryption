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
    uint64_t key =          0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =         "0101010001100101011100110111010000110001001100100011001100110100";

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

    grid(false); // It doesn't work for an error in displaying
    grid_bin(key);
    cout << endl;

    uint64_t perm_key;
    perm_key = permute(key);
    grid_compare(perm_key, str_pc1);
    return 0;
}

void grid_compare_testing(){
    uint64_t key =                 0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =                "0101010001100101011100110111010000110001001100100011001100110100";
    string str_short_key =                          "011100110111010000110001111100100011001100110100";
    grid_compare(key, str_key);
    grid_compare(key, str_short_key);
}