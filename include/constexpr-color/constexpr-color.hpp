#ifndef PROXICT_CONSTEXPR_COLOR_HPP_
#define PROXICT_CONSTEXPR_COLOR_HPP_

#include <algorithm>
#include <cmath>

namespace constexprColor {

namespace detail {

constexpr bool almostEqual(const float a, const float b) {
    return std::fabs(a - b) <= 0.00001f;
}

} // namespace detail

struct Rgb {
    constexpr Rgb() : r(0), g(0), b(0) {}

    constexpr Rgb(const unsigned char r_, const unsigned char g_, const unsigned char b_) : r(r_), g(g_), b(b_) {}

    constexpr Rgb(const unsigned char v) : r(v), g(v), b(v) {}

    constexpr bool operator==(const Rgb& rhs) const {
        return r == rhs.r && g == rhs.g && b == rhs.b;
    }

    constexpr bool operator!=(const Rgb& rhs) const {
        return !(*this == rhs);
    }

    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Hsl {
    constexpr Hsl()
        : hue(0), saturation(0.0f), lightness(0.0f) {}

    constexpr Hsl(const unsigned int hue, const float saturation, const float lightness)
        : hue(hue), saturation(saturation), lightness(lightness) {}

    constexpr bool operator==(const Hsl& rhs) const {
        return hue == rhs.hue &&
            detail::almostEqual(saturation, rhs.saturation) &&
            detail::almostEqual(lightness, rhs.lightness);
    }

    constexpr bool operator!=(const Hsl& rhs) const {
        return !(*this == rhs);
    }

    unsigned int hue;
    float saturation;
    float lightness;
};

struct InvalidHexChar {};

namespace detail {

constexpr int hexToDec(const char c) {
    return (c >= '0' && c <= '9') ? c - '0' :
        ((c >= 'a' && c <= 'f') ? c - 'a' + 10 :
         (c >= 'A' && c <= 'F') ? c - 'A' + 10 : throw InvalidHexChar{});
}

template <typename T>
constexpr T min(T&& v) {
    return std::forward<T>(v);
}

template <typename T,typename ...TArgs>
constexpr T min(const T& v1, const T& v2, const TArgs&... args) {
    return v2 < v1 ? min(v2, args...) : min(v1, args...);
}

template <typename T>
constexpr T max(T&& v) {
    return std::forward<T>(v);
}

template <typename T,typename ...TArgs>
constexpr T max(const T& v1, const T& v2, const TArgs&... args) {
    return v2 > v1 ? max(v2, args...) : max(v1, args...);
}

template <typename T>
constexpr T abs(const T& v) {
    return v < T(0) ? -v : v;
}

constexpr float fmod(const float x, const float y) {
    return x - (std::floor(x / y) * y);
}

namespace hsl {

constexpr float k(const int n, const unsigned int hue) {
    return fmod(n + hue / 30.0f, 12.0f);
}

constexpr float a(const float saturation, const float lightness) {
    return saturation * detail::min(lightness, 1.0f - lightness);
}

constexpr float chroma(const Rgb& rgb) {
    return static_cast<float>(detail::max(rgb.r, rgb.g, rgb.b) - detail::min(rgb.r, rgb.g, rgb.b)) / 255.0f;
}

constexpr float h(const Rgb& rgb) {
    return chroma(rgb) == 0.0f ? 0.0f : (
        detail::max(rgb.r, rgb.g, rgb.b) == rgb.r ? static_cast<float>(rgb.g - rgb.b) / 255.0f / chroma(rgb) + (rgb.g < rgb.b ? 6 : 0):
        (detail::max(rgb.r, rgb.g, rgb.b) == rgb.g ? static_cast<float>(rgb.b - rgb.r) / 255.0f / chroma(rgb) + 2 :
        (static_cast<float>(rgb.r - rgb.g) / 255.0f / chroma(rgb) + 4))
    );
}

constexpr float lightness(const Rgb& rgb) {
    return static_cast<float>(detail::min(rgb.r, rgb.g, rgb.b) + detail::max(rgb.r, rgb.g, rgb.b)) / 255.0f / 2.0f;
}

constexpr unsigned int hue(const float h) {
    return std::round(h * 60.0f) < 0 ? std::round(h * 60.0f) + 360 : std::round(h * 60.0f);
}

} // namespace hsl
} // namespace detail

constexpr Rgb toRgb(const Hsl hsl) {
    return Rgb(
        static_cast<unsigned char>((hsl.lightness -
                detail::hsl::a(hsl.saturation, hsl.lightness) *
                detail::max(-1.0f, detail::min(detail::hsl::k(0, hsl.hue) - 3.0f, 9.0f - detail::hsl::k(0, hsl.hue), 1.0f))) * 255),
        static_cast<unsigned char>((hsl.lightness -
                detail::hsl::a(hsl.saturation, hsl.lightness) *
                detail::max(-1.0f, detail::min(detail::hsl::k(8, hsl.hue) - 3.0f, 9.0f - detail::hsl::k(8, hsl.hue), 1.0f))) * 255),
        static_cast<unsigned char>((hsl.lightness -
                detail::hsl::a(hsl.saturation, hsl.lightness) *
                detail::max(-1.0f, detail::min(detail::hsl::k(4, hsl.hue) - 3.0f, 9.0f - detail::hsl::k(4, hsl.hue), 1.0f))) * 255));
}

constexpr Rgb toRgb(const char* str) {
    return Rgb((detail::hexToDec(str[1]) << 4 | detail::hexToDec(str[2])) & 0xff,
        (detail::hexToDec(str[3]) << 4 | detail::hexToDec(str[4])) & 0xff,
        (detail::hexToDec(str[5]) << 4 | detail::hexToDec(str[6])) & 0xff);
}

constexpr Hsl toHsl(const Rgb& rgb) {
    return Hsl(
        detail::hsl::hue(detail::hsl::h(rgb)),
        detail::hsl::chroma(rgb) == 0.0f ? 0.0f : detail::hsl::chroma(rgb) / (1 - detail::abs(2 * detail::hsl::lightness(rgb) - 1)),
        detail::hsl::lightness(rgb));
}

constexpr Hsl toHsl(const char* str) {
    return Hsl(
        detail::hsl::hue(detail::hsl::h(toRgb(str))),
        detail::hsl::chroma(toRgb(str)) == 0.0f ? 0.0f : detail::hsl::chroma(toRgb(str)) / (1 - detail::abs(2 * detail::hsl::lightness(toRgb(str)) - 1)),
        detail::hsl::lightness(toRgb(str)));
}

} // namespace constexprColor

#endif // PROXICT_CONSTEXPR_COLOR_HPP_
