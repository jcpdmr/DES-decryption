#include "utility.h"

using namespace std;

//string permute(string& init_str, const int* pattern, int size){
//    string perm_string;
//    for(int i = 0; i < size; i++){
//        perm_string += init_str[pattern[i] - 1]; // understand why -1
//    }
//    return perm_string;
//}

uint64_t permute(uint64_t& key){
    uint64_t perm_key = 0;
    for(int i = 0; i < 56; i++){
        // ((key >> pc1_bin[i]) & 1) check if the bit of key in position 56, 48, 42, ... is a 1 or 0
        // |= () << i add the bit in position 0, 1, 2, ... to the permuted key
        perm_key |= ((key >> pc1_bin[i]) & 1) << (56 - 1 - i);
    }

    return perm_key;
}

void printBinaryWithSpaces(uint64_t value, int bitsPerGroup) {
    bitset<64> binaryValue(value);
    int totalBits = binaryValue.size();

    for (int i = totalBits - 1; i >= 0; --i) {
        cout << binaryValue[i];
        if (i % bitsPerGroup == 0 && i != 0) {
            cout << ' ';
        }
    }

    cout << endl;
}

void grid(){
    // |64 |63 |62 |61 |60 ...
    for (int i = 63; i >= 0; i--) {
        cout << "|" << setw(2) << setfill(' ') << i << " ";
    }
    cout << endl;
}

void grid_bin(uint64_t& bin_val){
    //| 0 | 1 | 0 | 1 | 0 ... of the bin value
    for (int i = 63; i >= 0; i--) {
        cout << "| " << ((bin_val >> i) & 1) << " ";
    }
    cout << endl;
}

void grid_str(string& str_val){
    //| 0 | 1 | 0 | 1 | 0 ... of the str value, creating padding if needed
    if ((int)str_val.length() < 64){
        // Add empty padding |  |  |  |
        for(int i = 0; i < 64 - (int)str_val.length(); i++){
            cout << "|   " ;
        }
    }
    for (char i : str_val){
        cout << "| " << i  << " " ;
    }
    cout << endl;
}

void grid_compare(uint64_t& bin_val, string& str_val){
    grid_bin(bin_val);
    grid_str(str_val);
    // Compare
    for (int i = 63; i >= 0; i--){
            if ((int)str_val.length() <= i){
                // If str is less than 64 chars skip the iterations and add empty padding
                cout << "  . " ;
            }
            else{
                // Extracting the i-th value
                int bin_bit = (int)(bin_val >> i) & 1;
                int str_bit = (str_val[(int)str_val.length() - 1 - i] == '1') ? 1 : 0;
                if(bin_bit == str_bit){
                    cout << "    ";
                }
                else{
                    // Found a different bit, print the bit position
                    cout << " " << setw(2) << setfill(' ') << i << " " ;
                }
            }
        }
    cout << "\n" << endl;
    }

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

void print_keys(string(&round_keys)[16]){
    // Print the 16 round keys
    for(int i = 0; i < 16; i++){
        cout << "Key " << setw(2) << setfill('0') << i+1<< ": " << round_keys[i]<<endl;
    }
}

void generate_keys(string key, string(&round_keys)[16]){
    string perm_key;
    for(int i : pc1){
        perm_key += key[i-1];
    }
    string left= perm_key.substr(0, 28);
    string right= perm_key.substr(28, 28);
    for(int n_key = 0; n_key < 16; n_key++){
        if(n_key == 0 || n_key == 1 || n_key == 8 || n_key == 15 ){
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
        // cout<<"Key "<<i+1<<": "<<round_keys[i]<<endl;
    }
}

string convertDecimalToBinary(int decimal)
{
    string binary;
    while(decimal != 0) {
        binary += (decimal % 2 == 0 ? "0" : "1");
        decimal = decimal/2;
    }
    while(binary.length() < 4){
        binary += "0";
    }
    return binary;
}

int convertBinaryToDecimal(string binary)
{
    int decimal = 0;
    int counter = 0;
    int size = (int) binary.length();
    for(int i = size - 1; i >= 0; i--)
    {
        if(binary[i] == '1'){
            decimal += pow(2, counter);
        }
        counter++;
    }
    return decimal;
}

string Xor(string a, string b){
    string result;
    int size = (int) b.size();
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