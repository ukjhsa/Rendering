#include <cstdlib>
#include <cassert>
#include <vector>
#include <fstream>
#include "Color.h"
#include "PPMImage.h"

PPMImage::PPMImage(int row_size, int col_size) :
    row_(row_size), col_(col_size),
    pixels_(row_size, std::vector<Color>(col_size, Color(0, 0, 0)))
{
}

void PPMImage::init(int row_size, int col_size)
{
    row_ = row_size;
    col_ = col_size;
    pixels_.resize(row_size, std::vector<Color>(col_size, Color(0, 0, 0)));
}

void PPMImage::fill(Color background)
{
    for (auto& each_row : pixels_) {
        for (auto& cell : each_row) {
            cell = background;
        }
    }
}

Color PPMImage::read_pixel(int row, int col)
{
    return pixels_[row][col];
}

void PPMImage::write_pixel(int row, int col, Color pixel)
{
    pixels_[row][col] = pixel;
}

void PPMImage::export_image(const std::string& file_name)
{
    std::ofstream ofs(file_name, std::ios::binary);
    if (ofs.is_open()) {
        ofs << "P6 " << row_ << " " << col_ << " 255" << std::endl;
        for (auto each_row : pixels_) {
            for (auto cell : each_row) {
                ofs << (char)cell.R() << (char)cell.G() << (char)cell.B();
            }
        }
    }
}
