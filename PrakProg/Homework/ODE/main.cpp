#include <iostream>
#include "ODE.h"

int main() {
    odefun f = [](double x, const vec& y) {
        return vec{y[1],-y[0]};
    };

    vec y0 = {1.0, 0.0};

    auto [xs, ys] = driver(f, 0.0, y0, 10);

    for(size_t i=0;i<xs.size();i++) {
        std::cout << xs[i] << " " << ys[i][0] << "\n";
    }

    return 0;
}