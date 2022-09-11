#ifndef _MAGIC_COLOR_HPP_
#define _MAGIC_COLOR_HPP_

#include <iostream>

namespace Magic
{
    class Color
    {
    public:
        Color()
            : a(1), r(0), g(0), b(0)
        {
        }
        Color(float a, float r, float g, float b)
            : a(a), r(r), g(g), b(b)
        {
        }

        Color(unsigned int color32)
        :Color(color32 >> 24, (color32 & 0x00FF0000) >> 16, (color32 & 0x0000FF00) >> 8, color32 & 0x000000FF)
        {
        }

        Color(const Color &c)
        :a(c.a), r(c.r), g(c.g),b(c.b)
        {

        }
        Color(const Color &&c)
        :a(c.a), r(c.r), g(c.g),b(c.b)
        {
        }

        Color &operator=(const Color& c)
        {
            if (this != &c)
            {
                a = c.a;
                r = c.r;
                g = c.g;
                b = c.b;
            }
            return *this;
        }


        inline unsigned int Get32BitColor() const
        {
            return (((unsigned int)(a * 0xFF)) << 24) | (((unsigned int)(r * 0xFF)) << 16) | (((unsigned int)(g * 0xFF)) << 8) | ((unsigned int)(b * 0xFF));
        }

        inline Color &operator*=(float v)
        {
            a *= v;
            r *= v;
            g *= v;
            b *= v;

            return *this;
        }

        inline Color &operator*=(const Color &color)
        {
            a *= color.a;
            r *= color.r;
            g *= color.g;
            b *= color.b;

            return *this;
        }

        inline Color &operator+=(const Color &color)
        {
            a += color.a;
            r += color.r;
            g += color.g;
            b += color.b;

            return *this;
        }

        inline Color operator/(float v) const
        {
            v = 1.f / v;
            return Color(a * v, r * v, g * v, b * v);
        }

        inline Color operator*(float v) const
        {
            return Color(a * v, r * v, g * v, b * v);
        }

        inline Color operator*(const Color &color) const
        {
            return Color(a * color.a, r * color.r, g * color.g, b * color.b);
        }

        inline Color operator+(const Color &color) const
        {
            return Color(a + color.a, r + color.r, g + color.g, b + color.b);
        }

        inline Color operator-(const Color &color) const
        {
            return Color(a - color.a, r - color.r, g - color.g, b - color.b);
        }

        friend std::ostream &operator <<(std::ostream &out, const Color &c)
        {
            out << c.a << "," << c.r << "," << c.g << "," << c.b;
            return out;
        }

        union
        {
            struct
            {
                float a, r, g, b;
            };
            float c[4];
        };
    };
}

#endif