#ifndef DES_DECRYPTION_TESTING_H
#define DES_DECRYPTION_TESTING_H

#include "utility.h"

extern string test_round_keys[16];

void generate_keys_testing();

void encrypt_testing();

void swap_bits_testing();

void convertDecimalToBinary_testing();

void convertBinaryToDecimal_testing();

void check_encrypt_testing();

#endif //DES_DECRYPTION_TESTING_H
