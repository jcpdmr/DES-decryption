#include "utility.h"
//#include "testing.h"

namespace fs = std::filesystem;

int main() {


  omp_set_num_threads(N_THREADS);

  int mode = PARALLEL_STRING;

  // Hex key                0x5465737431323334     base10: 6081393814712496948
  uint64_t bin_key =
      0b0101010001100101011100110111010000110001001100100011001100110100;

  // Hex plain text         0x4369616F6369616F
  uint64_t bin_plain_text =
      0b0100001101101001011000010110111101100011011010010110000101101111;
  string str_plain_text =
      "0100001101101001011000010110111101100011011010010110000101101111";

  uint64_t bin_ciphe_text =
      0b0011111011110001111111101100011100110001010011101111111101000001;
  string str_ciph_text =
      "0011111011110001111111101100011100110001010011101111111101000001";

  // Create directory to save data, if it doesn't exist
  if (!fs::exists("./../output")) {
    if (fs::create_directory("./../output")) {
      std::cout << "Directory created successfully" << std::endl;
    } else {
      std::cerr << "Unable to create the directory." << std::endl;
    }
  }

  // Benchmark
  if (mode == PARALLEL_BINARY) {
    benchmark_parallel_binary(bin_plain_text, bin_ciphe_text, bin_key);
  } else if (mode == SEQUENTIAL_BINARY) {
    benchmark_sequential_binary(bin_plain_text, bin_ciphe_text, bin_key);
  } else if (mode == PARALLEL_STRING) {
    benchmark_parallel_string(str_plain_text, str_ciph_text, bin_key);
  } else if (mode == SEQUENTIAL_STRING) {
    benchmark_sequential_string(str_plain_text, str_ciph_text, bin_key);
  }
  return 0;
}