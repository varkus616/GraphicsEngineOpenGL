#include "Color.hpp"

Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

Color::Color(float red, float green, float blue, float alpha)
    : r(red), g(green), b(blue), a(alpha) {}

Color::Color(int hexValue) {
    set(hexValue);
}

Color::Color(const Color& other)
    : r(other.r), g(other.g), b(other.b), a(other.a) {}

Color::Color(Color&& other) noexcept
    : r(other.r), g(other.g), b(other.b), a(other.a) {
    other.r = other.g = other.b = other.a = 0.0f;
}

Color& Color::operator=(const Color& other) {
    if (this == &other) return *this;
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
    return *this;
}

Color& Color::operator=(Color&& other) noexcept {
    if (this == &other) return *this;
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
    other.r = other.g = other.b = other.a = 0.0f;
    return *this;
}

Color::~Color() {}

// Static constants for basic colors
const Color Color::Red = Color(1.0f, 0.0f, 0.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f);
const Color Color::Cyan = Color(0x00FFFF);
const Color Color::Magenta = Color(0xFF00FF);
const Color Color::Yellow = Color(0xFFFF00);
const Color Color::White = Color(1.0f, 1.0f, 1.0f);
const Color Color::Black = Color(0.0f, 0.0f, 0.0f);

Color Color::fromHex(int hexValue) {
    float red = ((hexValue >> 16) & 0xFF) / 255.0f;
    float green = ((hexValue >> 8) & 0xFF) / 255.0f;
    float blue = (hexValue & 0xFF) / 255.0f;
    return Color(red, green, blue);
}

void Color::set(float red, float green, float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void Color::set(int hexValue) {
    *this = fromHex(hexValue);
}

std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << "Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
    return os;
}
