#include "read_images.h"
#include "quantizations.h"
#include "images.h"

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " file_name target_bits\n";
        return 1;
    }

    std::string file_name = argv[1];
    int target_bits = std::stoi(argv[2]);

    std::string file_type = file_name.substr(file_name.size() - 4);

    if (file_type.compare(".raw") == 0) {
    
        std::vector<uint16_t> pixels = read_raw16(file_name);

        pixels = quantize_uint16_t(pixels, target_bits);

        // TODOs
        write_raw16(file_name, pixels);

    } else if (file_type.compare(".pgm") == 0) {

        Image_8 img = read_pgm8(file_name);

        img.pixels = quantize_uint8_t(img.pixels, target_bits);

        // TODOs
        write_pgm8(file_name, img);

    } else if (file_type.compare(".ppm") == 0) {

        Image_8 img = read_ppm(file_name);

        img.pixels = quantize_uint8_t(img.pixels, target_bits);

        // TODOs
        write_ppm(file_name, img);

    } else {
        std::cerr << "Improper input file (must be .raw .pgm or .ppm)\n";
        return 1;
    }


    return 0;

}