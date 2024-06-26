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
#include <omp.h>
#include "common.h"

using namespace std;

#define N_THREADS 12

enum mode{
    PARALLEL_BINARY,
    SEQUENTIAL_BINARY,
    PARALLEL_STRING,
    SEQUENTIAL_STRING
};

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

string encrypt(const string &plain_text, const string (&round_keys)[16]);
uint64_t encrypt(const uint64_t& plain_text, const uint64_t (&round_keys)[16]);

void split(const uint64_t &key, uint64_t &left, uint64_t&right, int bit_len_of_block);
uint64_t merge(uint64_t &left, uint64_t&right, int bit_len_of_block);
uint64_t permute(const uint64_t &key, const int* pattern, int n);

void grid(bool right_least_sign = true);
void grid_bin(uint64_t& bin_val);
void grid_str(string& str_val);
void grid_compare(uint64_t& bin_val, string& str_val);

uint64_t swap_bits(uint64_t a);

void crack_password_parallel_binary(uint64_t initial_key, uint64_t attempts, uint64_t correct_plaintext, uint64_t correct_ciphertext);
void benchmark_parallel_binary(uint64_t correct_plaintext, uint64_t correct_ciphertext, uint64_t bin_key);

void crack_password_sequential_binary(uint64_t initial_key, uint64_t attempts, uint64_t correct_plaintext, uint64_t correct_ciphertext);
void benchmark_sequential_binary(uint64_t correct_plaintext, uint64_t correct_ciphertext, uint64_t bin_key);

void crack_password_parallel_string(uint64_t initial_key, uint64_t attempts, const string& correct_plaintext, const string& correct_ciphertext);
void benchmark_parallel_string(const string& correct_plaintext, const string& correct_ciphertext, const uint64_t bin_key);

void crack_password_sequential_string(uint64_t initial_key, uint64_t attempts, const string& correct_plaintext, const string& correct_ciphertext);
void benchmark_sequential_string(const string& correct_plaintext, const string& correct_ciphertext, uint64_t bin_key);

// TODO: add a password to bin to convert a text password in a string of binary number

#endif //DES_DECRYPTION_UTILITY_H
