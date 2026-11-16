#include <iostream>
#include <vector>
#include <cstdint>

int compare_uint8(std::vector<uint8_t> original_pixels, std::vector<uint8_t> quantized_pixels) {

    if (original_pixels.size() != quantized_pixels.size()) {
        std::cerr << "Image files have different dimensions\n";
        return 1;
    }

    uint8_t max_error = 0;
    uint8_t error;

    for (size_t i = 0; i < original_pixels.size(); i++) {

        error = abs(original_pixels[i] - quantized_pixels[i]);

        if (error > max_error) {
            max_error = error;
        }

    }


    std::cout << "Maximum Absolute Error: " << max_error << "\n";

    // Also calculate signal to noise ratio (TODO)



    return 0;
}

int compare_uint16(std::vector<uint16_t> original_pixels, std::vector<uint16_t> quantized_pixels) {

    if (original_pixels.size() != quantized_pixels.size()) {
        std::cerr << "Image files have different dimensions\n";
        return 1;
    }

    uint16_t max_error = 0;
    uint16_t error;

    for (size_t i = 0; i < original_pixels.size(); i++) {

        error = abs(original_pixels[i] - quantized_pixels[i]);

        if (error > max_error) {
            max_error = error;
        }

    }

    std::cout << "Maximum Absolute Error: " << max_error << "\n";

    // Same here (TODO)

    return 0;
}