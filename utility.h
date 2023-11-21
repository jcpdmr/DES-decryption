#ifndef DES_DECRYPTION_UTILITY_H
#define DES_DECRYPTION_UTILITY_H

#include <string>
#include <iostream>
#include <cmath>
#include <bitset>
#include "common.h"

using namespace std;

void generate_keys(string key, string(&round_keys)[16]);
string shift_left_once(string key_chunk);
string shift_left_twice(string key_chunk);
string convertDecimalToBinary(int decimal);
int convertBinaryToDecimal(const string& binary);
string Xor(string a, string b);
string encrypt(string &plain_text, string (&round_keys)[16]);

#endif //DES_DECRYPTION_UTILITY_H
