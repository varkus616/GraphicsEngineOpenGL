#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

class Color {
public:
    float r, g, b, a;

    Color();

    Color(float red, float green, float blue, float alpha = 1.0f);
    Color(int hexValue); // Constructor using hex value (e.g., 0xFF0000 for red)

    Color(const Color& other);

    Color(Color&& other) noexcept;

    Color& operator=(const Color& other);

    Color& operator=(Color&& other) noexcept;

    ~Color();

    // Static constants for basic colors
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Cyan;
    static const Color Magenta;
    static const Color Yellow;
    static const Color White;
    static const Color Black;

    static Color fromHex(int hexValue);
    void set(float red, float green, float blue, float alpha = 1.0f);
    void set(int hexValue);

    // Overload stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Color& color);
};

#endif // COLOR_HPP
