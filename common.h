#ifndef DES_DECRYPTION_COMMON_H
#define DES_DECRYPTION_COMMON_H

extern const int pc1[56];
extern const int pc1_bin[56];

extern const int pc2[48];
extern const int pc2_bin[48];

extern const int initial_permutation[64];
extern const int initial_permutation_bin[64];

extern const int expansion_table[48];

extern const int substitution_boxes[8][4][16];

extern const int permutation_tab[32];

extern const int inverse_permutation[64];

#endif //DES_DECRYPTION_COMMON_H
