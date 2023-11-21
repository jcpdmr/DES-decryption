#include <iostream>
#include "utility.h"

using namespace std;

//string permute(string& init_str, const int* pattern, int size){
//    string perm_string;
//    for(int i = 0; i < size; i++){
//        perm_string += init_str[pattern[i] - 1]; // understand why -1
//    }
//    return perm_string;
//}

string shift_left_once(string key_chunk){
    string shifted;
    for(int i = 1; i < 28; i++){
        shifted += key_chunk[i];
    }
    shifted += key_chunk[0];
    return shifted;
}

string shift_left_twice(string key_chunk){
    string shifted;
    for(int i = 0; i < 2; i++){
        for(int j = 1; j < 28; j++){
            shifted += key_chunk[j];
        }
        shifted += key_chunk[0];
        key_chunk= shifted;
        shifted ="";
    }
    return key_chunk;
}

void generate_keys(string key, string(&round_keys)[16]){
    string perm_key;
    for(int i : pc1){
        perm_key+= key[i-1];
    }
    string left= perm_key.substr(0, 28);
    string right= perm_key.substr(28, 28);
    for(int n_key = 0; n_key < 16; n_key++){
        if(n_key == 0 || n_key == 1 || n_key==8 || n_key==15 ){
            left= shift_left_once(left);
            right= shift_left_once(right);
        }
        else{
            left= shift_left_twice(left);
            right= shift_left_twice(right);
        }
        string combined_key = left + right;
        string round_key;
        for(int j : pc2){
            round_key += combined_key[j-1];
        }
        round_keys[n_key] = round_key;
        // std::cout<<"Key "<<i+1<<": "<<round_keys[i]<<endl;
    }
}

string convertDecimalToBinary(int decimal)
{
    string binary = ((bitset<4>) decimal).to_string();
    return binary;
}

int convertBinaryToDecimal(const string& binary)
{
    int decimal = (int)((bitset<4>) binary).to_ulong();
    return decimal;
}

string Xor(string a, string b){
    string result;
    int size = (int)b.size();
    for(int i = 0; i < size; i++){
        if(a[i] != b[i]){
            result += "1";
        }
        else{
            result += "0";
        }
    }
    return result;
}

string encrypt(string &plain_text, string (&round_keys)[16]) {
    string perm;
    for(int i : initial_permutation){
        perm += plain_text[i - 1];
    }
    string left = perm.substr(0, 32);
    string right = perm.substr(32, 32);

    for(int round = 0; round < 16; round++) {
        string right_expanded;
        for(int j : expansion_table) {
            right_expanded += right[j-1];
        }
        string xored = Xor(round_keys[round], right_expanded);
        string res;
        for(int j = 0; j < 8; j++){
            string row1 = xored.substr(j * 6,1) + xored.substr(j * 6 + 5,1);
            int row = convertBinaryToDecimal(row1);
            string col1 = xored.substr(j * 6 + 1,1) + xored.substr(j * 6 + 2,1) + xored.substr(j * 6 + 3,1) + xored.substr(j * 6 + 4,1);
            int col = convertBinaryToDecimal(col1);
            int val = substitution_boxes[j][row][col];
            res += convertDecimalToBinary(val);
        }
        string perm2;
        for(int j : permutation_tab){
            perm2 += res[j-1];
        }
        xored = Xor(perm2, left);
        left = xored;
        if(round < 15){
            string temp = right;
            right = xored;
            left = temp;
        }
    }
    string combined_text = left + right;
    string ciphertext;
    for(int i : inverse_permutation){
        ciphertext+= combined_text[i-1];
    }
    return ciphertext;
}