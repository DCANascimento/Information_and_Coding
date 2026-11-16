#pragma once

#include <vector>
#include <cstdint>

struct Image_8 {
    int width;
    int height;
    int scale;
    std::vector<uint8_t> pixels;
};

struct Image_16 {
    int width;
    int height;
    int scale;
    std::vector<uint16_t> pixels;
};