#ifndef COLOR_H
#define COLOR_H

#include <istream>

class Color
{
public:
    Color();
    Color(int R, int G, int B);
    Color(const Color& rhs) = default;



/**
\brief Return the Red color.
*/
    int R() const { return R_; }
/**
\brief Return the Green color.
*/
    int G() const { return G_; }
/**
\brief Return the Blue color.
*/
    int B() const { return B_; }



/**
\brief Set the Red, Green, Blue color.
*/
    void set_color(int R, int G, int B);



/**
\brief The operator assignment.
*/
    Color& operator=(const Color& rhs);
/**
\brief The operator plus assignment.
*/
    Color& operator+=(const Color& rhs);



private:
    unsigned char R_, G_, B_;

    unsigned char check_bound(int scalar) const;
};

Color operator+ (const Color& lhs, const Color& rhs);
Color operator* (double f, const Color& color);
Color operator* (const Color& color, double f);

std::istream& operator>> (std::istream& is, Color& color);

#endif // COLOR_H
