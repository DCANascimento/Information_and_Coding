#include "histograms.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <math.h>

int plot_histogram(std::vector<int> hist, std::string file_name, std::string file_type, int bin_width, int max_value) {

    std::string dir_name = "Histograms";
    std::filesystem::create_directories(dir_name);

    std::string full_path = dir_name + "/" + file_name + "_" + file_type + ".svg";

    // Writes to the new histogram file
    std::ofstream file(full_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << full_path << std::endl;
        return 1;
    }

    // Graph dimensions and layout configurations
    int width = 1000;
    int height = 400;
    int margin_left = 70;
    int margin_right = 30;
    int margin_top = 40;
    int margin_bottom = 60;

    int plot_width = width - margin_left - margin_right;
    int plot_height = height - margin_top - margin_bottom;

    // Find the maximum bar height to scale the Y-axis
    long max_count = 1;
    for (int count : hist) {
        if (count > max_count) {
            max_count = count;
        }
    }

    int num_bins = (max_value + 1) / bin_width;

    // SVG Writer
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height << "\">\n";
    file << "  <rect width=\"100%\" height=\"100%\" fill=\"#ffffff\"/>\n";
    
    // Title
    file << "  <text x=\"" << width / 2 << "\" y=\"25\" text-anchor=\"middle\" font-family=\"Arial\" font-size=\"16\" font-weight=\"bold\" fill=\"#333\">";
    if (file_type.compare("raw16") == 0) {
        file << "Raw16 Image Histogram</text>\n";
    } else if (file_type.compare("pgm8") == 0) {
        file << "Raw16 Image Histogram</text>\n";
    } else if (file_type.compare("ppm_R") == 0) {
        file << "PPM Image Histogram (Red)</text>\n";
    } else if (file_type.compare("ppm_G") == 0) {
        file << "PPM Image Histogram (Green)</text>\n";
    } else if (file_type.compare("ppm_B") == 0) {
        file << "PPM Image Histogram (Blue)</text>\n";
    }


    // X-Axis line
    file << "  <line x1=\"" << margin_left << "\" y1=\"" << (height - margin_bottom) 
         << "\" x2=\"" << (width - margin_right) << "\" y2=\"" << (height - margin_bottom)
         << "\" stroke=\"#333\" stroke-width=\"1.5\"/>\n";
    // Y-Axis line
    file << "  <line x1=\"" << margin_left << "\" y1=\"" << margin_top 
         << "\" x2=\"" << margin_left << "\" y2=\"" << (height - margin_bottom) 
         << "\" stroke=\"#333\" stroke-width=\"1.5\"/>\n";

    // Y Lines and Labels
    int num_y_ticks = 5;
    for (int i = 0; i <= num_y_ticks; ++i) {
        double val = static_cast<double>(max_count * i) / num_y_ticks;
        int y_pos = (height - margin_bottom) - static_cast<int>((static_cast<double>(i) / num_y_ticks) * plot_height);
        
        if (i > 0) {
            file << "  <line x1=\"" << margin_left << "\" y1=\"" << y_pos 
                 << "\" x2=\"" << (width - margin_right) << "\" y2=\"" << y_pos 
                 << "\" stroke=\"#f0f0f0\" stroke-dasharray=\"4,4\"/>\n";
        }
        file << "  <text x=\"" << (margin_left - 10) << "\" y=\"" << (y_pos + 4) 
             << "\" text-anchor=\"end\" font-family=\"Arial\" font-size=\"11\" fill=\"#666\">" << static_cast<long>(val) << "</text>\n";
    }

    int num_x_ticks = 5; // Split the 16-bit range into 5 clean steps
    for (int i = 0; i <= num_x_ticks; ++i) {
        double pixel_val = (max_value / num_x_ticks) * i;
        int x_pos = margin_left + static_cast<int>((pixel_val / max_value) * plot_width);

        // Tick mark
        file << "  <line x1=\"" << x_pos << "\" y1=\"" << (height - margin_bottom) 
             << "\" x2=\"" << x_pos << "\" y2=\"" << (height - margin_bottom + 6) 
             << "\" stroke=\"#333\" stroke-width=\"1\"/>\n";

        // Text label
        file << "  <text x=\"" << x_pos << "\" y=\"" << (height - margin_bottom + 20) 
             << "\" text-anchor=\"middle\" font-family=\"Arial\" font-size=\"10\" fill=\"#666\">" << static_cast<int>(pixel_val) << "</text>\n";
    }

    // Draw histogram
    double bin_width_px = static_cast<double>(plot_width) / num_bins;
    for (int i = 0; i < num_bins; ++i) {
        double bar_h = (static_cast<double>(hist[i]) / max_count) * plot_height;
        double x_pos = margin_left + (i * bin_width_px);
        double y_pos = (height - margin_bottom) - bar_h;

        file << "  <rect x=\"" << x_pos << "\" y=\"" << y_pos 
             << "\" width=\"" << std::max(1.0, bin_width_px - 0.5) 
             << "\" height=\"" << bar_h << "\" fill=\"";


        if (file_type.compare("raw16") == 0) {
            file << "#0064ff\" opacity=\"0.85\"/>\n";
        } else if (file_type.compare("pgm8") == 0) {
            file << "#0064ff\" opacity=\"0.85\"/>\n";
        } else if (file_type.compare("ppm_R") == 0) {
            file << "#ff0000\" opacity=\"0.85\"/>\n";
        } else if (file_type.compare("ppm_G") == 0) {
            file << "#00ff00\" opacity=\"0.85\"/>\n";
        } else if (file_type.compare("ppm_B") == 0) {
            file << "#0000ff\" opacity=\"0.85\"/>\n";
        }
    }

    // Title
    file << "  <text x=\"" << (margin_left + plot_width / 2) << "\" y=\"" << (height - 15) 
         << "\" text-anchor=\"middle\" font-family=\"Arial\" font-size=\"12\" font-weight=\"bold\" fill=\"#333\">Pixel Intensity (0 - max_value)</text>\n";
    
    file << "</svg>\n";
    file.close();

    std::cout << "Successfully generated SVG graph: " << full_path << std::endl;

    return 0;
}


int raw16_histogram(Image_16 img, int bin_width, std::string file_name) {

    uint16_t max_value = 65535;

    int vector_length = (max_value / bin_width) + 1;

    std::vector<int> hist(vector_length, 0);

    std::vector<int> hist_counts(max_value + 1, 0);
    std::vector<int> vertical_counts(max_value + 1, 0);
    std::vector<int> horizontal_counts(max_value + 1, 0);

    size_t img_size = img.pixels.size();

    for (size_t i = 0; i < img_size; i++) {

        hist[img.pixels[i] / bin_width]++;
        hist_counts[img.pixels[i]]++;

        // doesnt trigger on the last line
        if (i < (unsigned int)(img.width * (img.height - 1))) {
            vertical_counts[abs(img.pixels[i] - img.pixels[i + img.width])]++;
        }

        // doesnt trigger on the last collumn
        if (i % img.width != (unsigned int)img.width - 1) {
            horizontal_counts[abs(img.pixels[i] - img.pixels[i + 1])]++;
        }
        
    }


    if (plot_histogram(hist, file_name, "raw16", bin_width, max_value) ) {
        std::cerr << "Error creating the svg file\n";
        return 1;
    }


    double normal_entropy = 0.0;
    double vertical_entropy = 0.0;
    double horizontal_entropy = 0.0;


    for (uint32_t i = 0; i < (unsigned int)max_value + 1; i++) {

        double prob = (double)hist_counts[i] / img_size;
        if (prob > 0) {
            normal_entropy -= (prob * log2(prob));
        }

        double vert_prob = (double)vertical_counts[i] / (img_size - img.width);
        if (vert_prob > 0) {
            vertical_entropy -= (vert_prob * log2(vert_prob));
        }
        
        double hori_prob = (double)horizontal_counts[i] / (img_size - img.height);
        if (hori_prob > 0) {
            horizontal_entropy -= (hori_prob * log2(hori_prob));
        }
    }


    // print
    std::cout << "Normal Entropy: " << normal_entropy << "\n";
    std::cout << "Vertical Comparison Entropy: " << vertical_entropy << "\n";
    std::cout << "Horizontal Comparison Entropy: " << horizontal_entropy << "\n";

    return 0;

}

int pgm8_histogram(Image_8 img, int bin_width, std::string file_name) {

    uint8_t max_value = 255;

    int vector_length = (max_value / bin_width) + 1;

    std::vector<int> hist(vector_length, 0);

    std::vector<int> hist_counts(max_value + 1, 0);
    std::vector<int> vertical_counts(max_value + 1, 0);
    std::vector<int> horizontal_counts(max_value + 1, 0);

    size_t img_size = img.pixels.size();

    for (size_t i = 0; i < img_size; i++) {

        hist[img.pixels[i] / bin_width]++;
        hist_counts[img.pixels[i]]++;

        if (i < (unsigned int)(img.width * (img.height - 1))) {
            vertical_counts[abs(img.pixels[i] - img.pixels[i + img.width])]++;
        }

        if (i % img.width != (unsigned int)img.width - 1) {
            horizontal_counts[abs(img.pixels[i] - img.pixels[i + 1])]++;
        }
        
    }


    if (plot_histogram(hist, file_name, "pgm8", bin_width, max_value) ) {
        std::cerr << "Error creating the svg file\n";
        return 1;
    }


    double normal_entropy = 0.0;
    double vertical_entropy = 0.0;
    double horizontal_entropy = 0.0;


    for (uint16_t i = 0; i < (unsigned int)max_value + 1; i++) {

        double prob = (double)hist_counts[i] / img_size;
        if (prob > 0) {
            normal_entropy -= (prob * log2(prob));
        }

        double vert_prob = (double)vertical_counts[i] / (img_size - img.width);
        if (vert_prob > 0) {
            vertical_entropy -= (vert_prob * log2(vert_prob));
        }
        
        double hori_prob = (double)horizontal_counts[i] / (img_size - img.height);
        if (hori_prob > 0) {
            horizontal_entropy -= (hori_prob * log2(hori_prob));
        }
    }


    std::cout << "Normal Entropy: " << normal_entropy << "\n";
    std::cout << "Vertical Comparison Entropy: " << vertical_entropy << "\n";
    std::cout << "Horizontal Comparison Entropy: " << horizontal_entropy << "\n";

    return 0;

}

int ppm_histogram(Image_8 img, int bin_width, std::string file_name) {

    uint8_t max_value = 255;

    int vector_length = (max_value / bin_width) + 1;

    std::vector<int> hist_R(vector_length, 0);
    std::vector<int> hist_counts_R(max_value + 1, 0);
    std::vector<int> vertical_counts_R(max_value + 1, 0);
    std::vector<int> horizontal_counts_R(max_value + 1, 0);

    std::vector<int> hist_G(vector_length, 0);
    std::vector<int> hist_counts_G(max_value + 1, 0);
    std::vector<int> vertical_counts_G(max_value + 1, 0);
    std::vector<int> horizontal_counts_G(max_value + 1, 0);

    std::vector<int> hist_B(vector_length, 0);
    std::vector<int> hist_counts_B(max_value + 1, 0);
    std::vector<int> vertical_counts_B(max_value + 1, 0);
    std::vector<int> horizontal_counts_B(max_value + 1, 0);

    size_t img_size = img.pixels.size() / 3;

    for (size_t i = 0; i < img_size; i++) {

        size_t true_i = i * 3;

        hist_R[img.pixels[true_i] / bin_width]++;
        hist_G[img.pixels[true_i + 1] / bin_width]++;
        hist_B[img.pixels[true_i + 2] / bin_width]++;

        hist_counts_R[img.pixels[true_i]]++;
        hist_counts_G[img.pixels[true_i + 1]]++;
        hist_counts_B[img.pixels[true_i + 2]]++;

        if (i < (unsigned int)(img.width * (img.height - 1))) {
            vertical_counts_R[abs(img.pixels[true_i] - img.pixels[true_i + img.width * 3])]++;
            vertical_counts_G[abs(img.pixels[true_i + 1] - img.pixels[true_i + 1 + img.width * 3])]++;
            vertical_counts_B[abs(img.pixels[true_i + 2] - img.pixels[true_i + 2 + img.width * 3])]++;
        }

        if (i % img.width != (unsigned int)img.width - 1) {
            horizontal_counts_R[abs(img.pixels[true_i] - img.pixels[true_i + 1])]++;
            horizontal_counts_G[abs(img.pixels[true_i + 1] - img.pixels[true_i + 1 + 1])]++;
            horizontal_counts_B[abs(img.pixels[true_i + 2] - img.pixels[true_i + 2 + 1])]++;
        }
        
    }


    if (plot_histogram(hist_R, file_name, "ppm_R", bin_width, max_value) ) {
        std::cerr << "Error creating the svg file\n";
        return 1;
    }

    if (plot_histogram(hist_G, file_name, "ppm_G", bin_width, max_value) ) {
        std::cerr << "Error creating the svg file\n";
        return 1;
    }

    if (plot_histogram(hist_B, file_name, "ppm_B", bin_width, max_value) ) {
        std::cerr << "Error creating the svg file\n";
        return 1;
    }


    double normal_entropy_R = 0.0;
    double normal_entropy_G = 0.0;
    double normal_entropy_B = 0.0;

    double vertical_entropy_R = 0.0;
    double vertical_entropy_G = 0.0;
    double vertical_entropy_B = 0.0;

    double horizontal_entropy_R = 0.0;
    double horizontal_entropy_G = 0.0;
    double horizontal_entropy_B = 0.0;


    for (uint16_t i = 0; i < (unsigned int)max_value + 1; i++) {

        // R
        double prob = (double)hist_counts_R[i] / img_size;
        if (prob > 0) {
            normal_entropy_R -= (prob * log2(prob));
        }

        double vert_prob = (double)vertical_counts_R[i] / (img_size - img.width);
        if (vert_prob > 0) {
            vertical_entropy_R -= (vert_prob * log2(vert_prob));
        }
        
        double hori_prob = (double)horizontal_counts_R[i] / (img_size - img.height);
        if (hori_prob > 0) {
            horizontal_entropy_R -= (hori_prob * log2(hori_prob));
        }


        // G
        prob = (double)hist_counts_G[i] / img_size;
        if (prob > 0) {
            normal_entropy_G -= (prob * log2(prob));
        }

        vert_prob = (double)vertical_counts_G[i] / (img_size - img.width);
        if (vert_prob > 0) {
            vertical_entropy_G -= (vert_prob * log2(vert_prob));
        }
        
        hori_prob = (double)horizontal_counts_G[i] / (img_size - img.height);
        if (hori_prob > 0) {
            horizontal_entropy_G -= (hori_prob * log2(hori_prob));
        }


        // B
        prob = (double)hist_counts_B[i] / img_size;
        if (prob > 0) {
            normal_entropy_B -= (prob * log2(prob));
        }

        vert_prob = (double)vertical_counts_B[i] / (img_size - img.width);
        if (vert_prob > 0) {
            vertical_entropy_B -= (vert_prob * log2(vert_prob));
        }
        
        hori_prob = (double)horizontal_counts_B[i] / (img_size - img.height);
        if (hori_prob > 0) {
            horizontal_entropy_B -= (hori_prob * log2(hori_prob));
        }

    }


    std::cout << "Normal Entropies (R/G/B): " << normal_entropy_R << "/" << normal_entropy_G << "/" << normal_entropy_B << "\n";
    std::cout << "Vertical Comparison Entropies (R/G/B): " << vertical_entropy_R << "/" << vertical_entropy_G << "/" << vertical_entropy_B << "\n";
    std::cout << "Horizontal Comparison Entropies (R/G/B): " << horizontal_entropy_R << "/" << horizontal_entropy_G << "/" << horizontal_entropy_B << "\n";

    return 0;

}


