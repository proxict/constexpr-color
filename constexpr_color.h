#ifndef CONSTEXPR_COLOR_H_
#define CONSTEXPR_COLOR_H_

struct Rgb {
    constexpr Rgb() : r(0), g(0), b(0) {}

    constexpr Rgb(const unsigned char r_, const unsigned char g_, const unsigned char b_) : r(r_), g(g_), b(b_) {}

    constexpr Rgb(const unsigned char v) : r(v), g(v), b(v) {}

    unsigned char r;
    unsigned char g;
    unsigned char b;
};

constexpr int hexToDec(const char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
}

template<int TSize>
constexpr Rgb toRgb(char const (&str)[TSize]) {
    constexpr int len = TSize - 1;
    static_assert(len == 7, "Invalid format, expected #rrggbb format...");
    const char* ptr = str;
    Rgb rgb;
    rgb.r = (hexToDec(ptr[1]) << 4 | hexToDec(ptr[2])) & 0xff;
    rgb.g = (hexToDec(ptr[3]) << 4 | hexToDec(ptr[4])) & 0xff;
    rgb.b = (hexToDec(ptr[5]) << 4 | hexToDec(ptr[6])) & 0xff;
    return rgb;
}

#endif // CONSTEXPR_COLOR_H_
