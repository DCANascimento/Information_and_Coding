#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "images.h"

Image_16 read_raw16(std::string file_name);
Image_8 read_pgm8(std::string file_name);
Image_8 read_ppm(std::string file_name);

int write_raw16(std::string file_name, Image_16 img);
int write_pgm8(std::string file_name, Image_8 img);
int write_ppm(std::string file_name, Image_8 img);