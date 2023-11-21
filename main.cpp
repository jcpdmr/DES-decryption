#include <iostream>
#include "utility.h"
// #include "testing.h"

int main(){
    // Hex key                0x5465737431323334
    uint64_t bin_key =        0b0101010001100101011100110111010000110001001100100011001100110100;
    string str_key =           "0101010001100101011100110111010000110001001100100011001100110100";

    // Hex plain text         0x4369616F6369616F
    string str_plain_text =    "0100001101101001011000010110111101100011011010010110000101101111";
    uint64_t bin_plain_text = 0b0100001101101001011000010110111101100011011010010110000101101111;

    uint64_t bin_round_keys[16];
    string str_round_keys[16];

    generate_keys(bin_key, bin_round_keys);
    generate_keys(str_key, str_round_keys);

    string ciphertxt;
    uint64_t ciptxt;

    ciphertxt = encrypt(str_plain_text, str_round_keys);
    ciptxt = encrypt(bin_plain_text, bin_round_keys);
    std::cout << "Ciphertext str: " << ciphertxt << std::endl;
    std::cout << "Ciphertext bin: " << std::bitset<64>(ciptxt) << std::endl;

    return 0;
}