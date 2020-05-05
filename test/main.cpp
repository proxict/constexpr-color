#include <constexpr-color/constexpr-color.hpp>
#include <cstdio>

int main() {
    namespace cc = constexprColor;
    static_assert(cc::toRgb("#7EA3CE") == cc::Rgb(126, 163, 206), "HEX to RGB failed");
    static_assert(cc::toRgb(cc::Hsl(38, 1.0f, 0.569f)) == cc::Rgb(255, 174, 35), "HSL to RGB failed");
    static_assert(cc::toHsl(cc::Rgb(197, 176, 140)) == cc::Hsl(38, 0.32948f, 0.660784f), "RGB to HSL failed");
    static_assert(cc::toHsl("#C5B08C") == cc::Hsl(38, 0.32948f, 0.660784f), "HEX to HSL failed");
    puts("Passed");
}
