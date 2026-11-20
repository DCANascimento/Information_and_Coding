#include <iostream>
#include <vector>
#include <cstdint>
#include <math.h>

int compare_uint8(std::vector<uint8_t> original_pixels, std::vector<uint8_t> quantized_pixels) {

    if (original_pixels.size() != quantized_pixels.size()) {
        std::cerr << "Image files have different dimensions\n";
        return 1;
    }

    size_t total_pixels = original_pixels.size();

    uint8_t max_error = 0;
    uint8_t error;

    for (size_t i = 0; i < total_pixels; i++) {

        error = abs(original_pixels[i] - quantized_pixels[i]);
        error = error * error;

        if (error > max_error) {
            max_error = error;
        }

    }

    int psnr = 10 * log10(255 / max_error);

    std::cout << "Maximum Absolute Error: " << max_error << "\n";
    std::cout << "Peak-Signal-To-Noise Ratio: " << psnr << "\n";

    return 0;
}

int compare_uint16(std::vector<uint16_t> original_pixels, std::vector<uint16_t> quantized_pixels) {

    if (original_pixels.size() != quantized_pixels.size()) {
        std::cerr << "Image files have different dimensions\n";
        return 1;
    }

    size_t total_pixels = original_pixels.size();

    uint16_t max_error = 0;
    uint16_t error;

    for (size_t i = 0; i < total_pixels; i++) {

        error = abs(original_pixels[i] - quantized_pixels[i]);
        error = error * error;

        if (error > max_error) {
            max_error = error;
        }

    }

    int psnr = 10 * log10(65535 / max_error);

    std::cout << "Maximum Absolute Error: " << max_error << "\n";
    std::cout << "Peak-Signal-To-Noise Ratio: " << psnr << "\n";

    return 0;
}