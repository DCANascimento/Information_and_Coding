#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "images.h"

int plot_histogram(std::vector<int> hist_counts, std::string file_name, std::string file_type, int bin_width, int max_value);

int raw16_histogram(Image_16 img, int bin_width, std::string file_name);
int pgm8_histogram(Image_8 img, int bin_width, std::string file_name);
int ppm_histogram(Image_8 img, int bin_width, std::string file_name);