#include <iostream>
#include <constexpr_color.h>

int main() {
    constexpr Rgb rgb = toRgb("#7EA3CE");
    std::cout << "#7EA3CE == RGB(" << int(rgb.r) << ", " << int(rgb.g) << ", " << int(rgb.b) << ')' << std::endl;
    return 0;
}
