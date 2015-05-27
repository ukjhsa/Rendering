#ifndef PPM_IMAGE_H
#define PPM_IMAGE_H

#include <vector>
#include <string>
#include "Color.h"

class PPMImage
{
public:
    PPMImage() = default;
    PPMImage(int row_size, int col_size);
    PPMImage(const PPMImage& rhs) = default;
    ~PPMImage() = default;



/**
\brief Initialize the PPMImage.
*/
    void init(int row_size, int col_size);
/**
\brief Fill the color of image by the specific color.
*/
    void fill(Color background);
/**
\brief Return the color by specific row and column on the image.
*/
    Color read_pixel(int row, int col);
/**
\brief Write the color by specific row and column on the image.
*/
    void write_pixel(int row, int col, Color p);
/**
\brief Export image data to a file.
*/
    void export_image(const std::string& file_name);

private:
    int row_, col_;
    std::vector< std::vector<Color> > pixels_;
};

#endif // PPM_IMAGE_H
