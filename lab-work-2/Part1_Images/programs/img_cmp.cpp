#include "read_images.h"
#include "comparisons.h"
#include "images.h"

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " original_file quantized_file\n";
        return 1;
    }

    std::string original_file = argv[1];
    std::string quantized_file = argv[2];

    std::string file_type = original_file.substr(original_file.size() - 4);

    if (file_type.compare(original_file.substr(original_file.size() - 4)) != 0) {
        std::cerr << "Error: Different types of image files\n";
        return 1;
    }

    if (file_type.compare(".raw") == 0) {
    
        Image_16 original_image = read_raw16("../datasets/img-raw16/" + original_file);
        Image_16 quantized_image = read_raw16("Quants/" + quantized_file);

        if (compare_uint16(original_image.pixels, quantized_image.pixels)) {
            return 1;
        }


    } else if (file_type.compare(".pgm") == 0) {

        Image_8 original_img = read_pgm8("../datasets/img-pgm8/" + original_file);
        Image_8 quantized_img = read_pgm8("Quants/" + quantized_file);

        if (compare_uint8(original_img.pixels, quantized_img.pixels)) {
            return 1;
        }

    } else if (file_type.compare(".ppm") == 0) {

        Image_8 original_img = read_ppm("../datasets/img-ppm/" + original_file);
        Image_8 quantized_img = read_ppm("Quants/" + quantized_file);

        if (compare_uint8(original_img.pixels, quantized_img.pixels)) {
            return 1;
        }

    } else {
        std::cerr << "Improper input file (must be .raw .pgm or .ppm)\n";
        return 1;
    }


    return 0;

}