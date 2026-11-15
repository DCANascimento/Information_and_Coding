#include <vector>
#include <cstdint>

std::vector<uint16_t> quantize_uint16_t(std::vector<uint16_t> pixels, int target_bits);
std::vector<uint8_t> quantize_uint8_t(std::vector<uint8_t> pixels, int target_bits);