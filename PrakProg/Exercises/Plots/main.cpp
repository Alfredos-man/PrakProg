#include <iostream>
#include <cmath>

int main() {
    for(double x = -3; x <= 3; x += 0.1) {
        std::cout << x << " " << std::erf(x) << "\n";
    }
    return 0;
}