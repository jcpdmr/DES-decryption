#ifndef DES_DECRYPTION_UTILITY_H
#define DES_DECRYPTION_UTILITY_H

#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <chrono>
#include <fstream>
#include <filesystem>
#include "common.h"

using namespace std;

void generate_keys(string key, string(&round_keys)[16]);
void generate_keys(uint64_t key, uint64_t(&round_keys)[16]);

void generate_inv_keys(uint64_t key, uint64_t(&inv_round_keys)[16]);
void generate_inv_keys(string key, string(&round_keys)[16]);

string shift_left_once(string key_chunk);
string shift_left_twice(string key_chunk);
uint64_t shift_left(uint64_t bin_key, bool shift_twice = false);

string convertDecimalToBinary(int decimal);
int convertBinaryToDecimal(const string& binary);

string Xor(string a, string b);
uint64_t Xor(const uint64_t& a, const uint64_t& b);

string encrypt(string &plain_text, string (&round_keys)[16]);
uint64_t encrypt(const uint64_t& plain_text, const uint64_t (&round_keys)[16]);

void split(const uint64_t &key, uint64_t &left, uint64_t&right, int bit_len_of_block);
uint64_t merge(uint64_t &left, uint64_t&right, int bit_len_of_block);
uint64_t permute(const uint64_t &key, const int* pattern, int n);

void grid(bool right_least_sign = true);
void grid_bin(uint64_t& bin_val);
void grid_str(string& str_val);
void grid_compare(uint64_t& bin_val, string& str_val);

uint64_t swap_bits(uint64_t a);

// TODO: add a password to bin to convert a text password in a string of binary number

#endif //DES_DECRYPTION_UTILITY_H
