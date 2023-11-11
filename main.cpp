#include <iostream>
#include "utility.h"
#include <iomanip>

int main(){
    string round_keys[16];
    string key = "1010101010111011000010010001100000100111001101101100110011011101";
    string plain_text = "1010101111001101111001101010101111001101000100110010010100110110";

    generate_keys(key, round_keys);
    for(int i = 0; i < 16; i++){
        cout << "Key " << std::setw(2) << std::setfill('0') << i+1<< ": "<<round_keys[i]<<endl;
    }

    cout << "Plain text: " << plain_text << endl;
    string ciphertext = encrypt(plain_text, round_keys);
    cout << "Ciphertext: "<< ciphertext <<endl;

}