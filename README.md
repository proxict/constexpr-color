[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

constexpr-color
---------------

**constexpr-color** can convert a color written in a hexadecimal format like `#ffaf23` to an RGB format like `RGB(255, 175, 35)`

 - Requires >= C++14 standard

Usage example:
--------------
```c++
#include <iostream>
#include <constexpr_color.h>

int main() {
    constexpr Rgb rgb = toRgb("#7EA3CE");
    std::cout << "#7EA3CE == RGB(" << int(rgb.r) << ", " << int(rgb.g) << ", " << int(rgb.b) << ')' << std::endl;
    return 0;
}
```
