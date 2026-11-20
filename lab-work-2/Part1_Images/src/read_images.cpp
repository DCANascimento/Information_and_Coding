#include "read_images.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#include "images.h"

Image_16 read_raw16(std::string file_name) {

    // opens the file in the end, to count the total size
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    int total_pixels = file_size / sizeof(uint16_t);

    std::cout << "File size: " << file_size << " bytes\n";

    std::vector<uint16_t> pixels(total_pixels);

    if (!file.read(reinterpret_cast<char*>(pixels.data()), file_size)) {
        throw std::runtime_error("Failed to read from file");
    }

    file.close();

    Image_16 img;

    // Getting width and height from the file_name
    // finds the position of the widthxheight portion
    int start = file_name.find("u16be-1x") + 8;
    int end = file_name.find(".raw") - 1;

    std::string dimensions = file_name.substr(start, end - start);

    int middle = dimensions.find("x");

    img.width = std::stoi(dimensions.substr(0, middle - 1));
    img.height = std::stoi(dimensions.substr(middle + 1));

    std::cout << img.width << img.height << "\n";

    img.scale = 65536;
    img.pixels = pixels;

    return img;
}

Image_8 read_pgm8(std::string file_name) {

    // opens the file in the end, to count the total size
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    // Skips P5
    file.seekg(3, std::ios::beg);

    int width;
    int height;

    int width_done = 0;

    char full_buffer[50];
    char buffer;
    int count = 0;

    while (file.read(&buffer, sizeof(char))) {

        if (static_cast<int>(buffer) == 32 || static_cast<int>(buffer) == 10) {

            if (width_done) {
                height = atoi(full_buffer);
                break;
            } else {
                width = atoi(full_buffer);
                
                for (int i = 0; i < count; i++) {
                    // ascii value of '0', holy genius
                    full_buffer[i] = 48;
                }

                width_done = 1;
            }
            count = 0;

        } else {
            full_buffer[count++] = buffer;
        }

    }

    int total_pixels = width * height;
    std::vector<uint8_t> pixels(total_pixels);

    std::cout << "total pixels: " << total_pixels << "\n";

    // Skip 255 gray scale thing
    file.read(&full_buffer[0], sizeof(char) * 4);

    if (!file.read(reinterpret_cast<char*>(pixels.data()), (total_pixels * sizeof(uint8_t)))) {
        throw std::runtime_error("Failed to read from file");
    }

    file.close();

    // Teste
    //uint8_t old_buffer;
    //std::FILE* f = std::fopen("../datasets/imgs-pgm8/barbara.pgm", "r");
    //int old_count = 0;
    //while (std::fread(&old_buffer, sizeof(uint8_t), 1, f) && old_count++ < 100) {
    //    std::cout << static_cast<int>(old_buffer) << "\n";
    //    std::cout << old_buffer << "\n";
    //}
    //std::fclose(f);

    Image_8 img;

    img.width = width;
    img.height = height;

    //lets assume for now, too lazy to change code
    img.scale = 255;
    img.pixels = pixels;

    return img;

}


Image_8 read_ppm(std::string file_name) {

    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    // Skips P6, similar to pgm
    file.seekg(3, std::ios::beg);

    int width;
    int height;

    int width_done = 0;

    char full_buffer[50];
    char buffer;
    int count = 0;

    while (file.read(&buffer, sizeof(char))) {

        if (static_cast<int>(buffer) == 32 || static_cast<int>(buffer) == 10) {

            if (width_done) {
                height = atoi(full_buffer);
                break;
            } else {
                width = atoi(full_buffer);
                
                for (int i = 0; i < count; i++) {
                    full_buffer[i] = 48;
                }

                width_done = 1;
            }
            count = 0;

        } else {
            full_buffer[count++] = buffer;
        }

    }

    int total_pixels = width * height;

    // * 3 because of the RGB
    std::vector<uint8_t> pixels(total_pixels * 3);

    std::cout << "total pixels: " << total_pixels << "\n";

    // Skip 255 gray scale thing
    file.read(&full_buffer[0], sizeof(char) * 4);

    if (!file.read(reinterpret_cast<char*>(pixels.data()), (total_pixels * 3 * sizeof(uint8_t)))) {
        throw std::runtime_error("Failed to read from file");
    }

    file.close();

    Image_8 img;

    img.width = width;
    img.height = height;
    img.scale = 255;
    img.pixels = pixels;

    return img;

}


// Writes

int write_raw16(std::string file_name, std::vector<uint16_t> pixels) {

    std::ofstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << file_name << std::endl;
        return 1;
    }

    for (uint16_t pixel : pixels) {
        file.write(reinterpret_cast<const char*>(&pixel), sizeof(pixel));
    }

    file.close();

    return 0;

}


int write_pgm8(std::string file_name, Image_8 img) {

    std::ofstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << file_name << std::endl;
        return 1;
    }

    char dimensions[10];

    file << "P5\n";

    sprintf(dimensions, "%d %d\n", img.width, img.height);
    file << dimensions;

    file << "255\n";

    for (uint8_t pixel : img.pixels) {
        file.write(reinterpret_cast<const char*>(&pixel), sizeof(pixel));
    }

    file.close();

    return 0;

}


int write_ppm(std::string file_name, Image_8 img) {

    std::ofstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << file_name << std::endl;
        return 1;
    }

    char dimensions[10];

    file << "P5\n";

    sprintf(dimensions, "%d %d\n", img.width, img.height);
    file << dimensions;

    file << "255\n";

    for (uint8_t pixel : img.pixels) {
        file.write(reinterpret_cast<const char*>(&pixel), sizeof(pixel));
    }

    file.close();

    return 0;

}
