#include <iostream>
#include "utility.h"
#include <iomanip>

int main(){
    // Key is "Test1234"
    string key = "0101010001100101011100110111010000110001001100100011001100110100";

    // Plain text is "Ciaociao" converted in ASCII
    string plain_text = "0100001101101001011000010110111101100011011010010110000101101111";

    string round_keys[16];
    generate_keys(key, round_keys);

//    // Print the 16 round keys
//    for(int i = 0; i < 16; i++){
//        cout << "Key " << std::setw(2) << std::setfill('0') << i+1<< ": " << round_keys[i]<<endl;
//    }

    cout <<endl;
    cout << "Plain text: " << plain_text << endl;
    string ciphertext = encrypt(plain_text, round_keys);
    cout << "Ciphertext: "<< ciphertext <<endl;

    // Reverse the order of the keys, for decryption
    for (int i = 0, j = 16 - 1; i < 16/2; i++, j--)
    {
        string temp = round_keys[i];
        round_keys[i] = round_keys[j];
        round_keys[j] = temp;
    }

    string decrypted_text = encrypt(ciphertext, round_keys);
    cout << "Decryptext: "<< decrypted_text <<endl;

    if(decrypted_text == plain_text){
        cout << "Message decrypted successfully! "<<endl;
    }

}