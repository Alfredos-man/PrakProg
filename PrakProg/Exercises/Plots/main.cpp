#include <cstdio>
#include <vector>
#include <utility>
#include <iostream>
#include "plots.h"

int main() {
    std::vector<std::pair<double,double>> tabulated = {
        {0.0, 0.0},
        {0.5, 0.5204998778},
        {1.0, 0.8427007929},
        {1.5, 0.9661051465},
        {2.0, 0.9953222650}
    };

    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        std::cerr << "Kunne ikke starte gnuplot\n";
        return 1;
    }

    fprintf(gp, "set title 'Error function erf(x)'\n");
    fprintf(gp, "set xlabel 'x'\n");
    fprintf(gp, "set ylabel 'erf(x)'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot '-' with lines title 'approximation', '-' with points pt 7 title 'tabulated values'\n");

    for (double x = -2.5; x <= 2.5; x += 0.01) {
        fprintf(gp, "%f %f\n", x, errorfunc(x));
    }
    fprintf(gp, "e\n");

    for (auto [x, y] : tabulated) {
        fprintf(gp, "%f %f\n", x, y);
    }
    fprintf(gp, "e\n");

    fflush(gp);
    pclose(gp);
}