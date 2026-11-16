#pragma once

#include <vector>
#include <cstdint>

struct Image_8 {
    int width;
    int height;
    int scale;
    std::vector<uint8_t> pixels;
};