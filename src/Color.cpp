#include <istream>
#include "Color.h"

Color::Color() : Color(0, 0, 0)
{
}

Color::Color(int R, int G, int B) :
    R_(check_bound(R)), G_(check_bound(G)), B_(check_bound(B))
{
}

void Color::set_color(int R, int G, int B)
{
    R_ = check_bound(R);
    G_ = check_bound(G);
    B_ = check_bound(B);
}

Color& Color::operator=(const Color& rhs)
{
    Color temp(rhs);
    std::swap(R_, temp.R_);
    std::swap(G_, temp.G_);
    std::swap(B_, temp.B_);
    return *this;
}

Color& Color::operator+=(const Color& rhs)
{
    R_ = check_bound(R() + rhs.R());
    G_ = check_bound(G() + rhs.G());
    B_ = check_bound(B() + rhs.B());
    return *this;
}

unsigned char Color::check_bound(int scalar) const
{
    if (scalar > 255) {
        return 255;
    }
    else if (scalar < 0) {
        return 0;
    }
    else {
        return static_cast<unsigned char>(scalar);
    }
}

Color operator+(const Color& lhs, const Color& rhs)
{
    Color temp(lhs);
    return temp += rhs;
}

Color operator*(double f, const Color& color)
{
    Color c(static_cast<int>(f * color.R()),
            static_cast<int>(f * color.G()),
            static_cast<int>(f * color.B()));
    return c;
}

Color operator*(const Color& color, double f)
{
    return f * color;
}

std::istream& operator>>(std::istream& is, Color& color)
{
    int r = 0, g = 0, b = 0;
    is >> r >> g >> b;
    color.set_color(r, g, b);
    return is;
}
