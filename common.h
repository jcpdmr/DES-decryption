#ifndef DES_DECRYPTION_COMMON_H
#define DES_DECRYPTION_COMMON_H

#include <cstdint>

extern const int pc1[56];
extern const uint16_t pc1_bin[56];

extern const int pc2[48];
extern const uint16_t pc2_bin[48];

extern const int initial_permutation[64];
extern const uint16_t initial_permutation_bin[64];

extern const int expansion_table[48];
extern const uint16_t expansion_table_bin[48];

extern const int substitution_boxes[8][4][16];
extern const uint64_t substitution_boxes_bin[8][4][16];

extern const int permutation_tab[32];
extern const uint16_t permutation_tab_bin[32];

extern const int inverse_permutation[64];
extern const uint16_t inverse_permutation_bin[64];

#endif //DES_DECRYPTION_COMMON_H
