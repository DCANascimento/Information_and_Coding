#pragma once

#include <vector>
#include <cstdint>

struct Image_8 {
    uint16_t width;
    uint16_t height;
    uint8_t scale;
    std::vector<uint8_t> pixels;
};

struct Image_16 {
    uint16_t width;
    uint16_t height;
    uint16_t scale;
    std::vector<uint16_t> pixels;
};