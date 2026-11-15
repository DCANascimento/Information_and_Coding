#include "quantizations.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <math.h>

std::vector<uint16_t> quantize_uint16_t(std::vector<uint16_t> pixels, int target_bits) {

    if (target_bits > 16 || target_bits < 1) {
        throw std::invalid_argument("Error: invalid target bits for 16 bit samples");
    }

    int space = pow(2, 16 - target_bits);
    int difference;

    for (int i = 0; i < pixels.size(); i++) {

        difference = pixels[i] % space;

        // After calculating the difference between the pixel value and the highest quantized value below it (through mod), we see if we should round up or down based on the difference
        if (difference > (space / 2)) {
            pixels[i] = std::min(65536, pixels[i] + (space - difference));;
        } else {
            pixels[i] = pixels[i] - difference;
        }

    }

    return pixels;

}



std::vector<uint8_t> quantize_uint8_t(std::vector<uint8_t> pixels, int target_bits) {

    if (target_bits > 8 || target_bits < 0) {
        throw std::invalid_argument("Error: invalid target bits for 8 bit samples");
    }

    int space = pow(2, 8 - target_bits);
    int difference;

    for (int i = 0; i < pixels.size(); i++) {

        difference = pixels[i] % space;

        // Same stuff
        if (difference > (space / 2)) {
            pixels[i] = std::min(255, pixels[i] + (space - difference));;
        } else {
            pixels[i] = pixels[i] - difference;
        }

    }

    return pixels;
    
}