#include "plots.h"
#include <cmath>

double errorfunc(double x){
    if(x < 0) return -errorfunc(-x);
    const double a[5] = {
        0.254829592,
       -0.284496736,
        1.421413741,
       -1.453152027,
        1.061405429
    };

    double t = 1.0 / (1.0 + 0.3275911 * x);
    double sum = t * (a[0] + t * (a[1] + t * (a[2] + t * (a[3] + t * a[4]))));
    return 1.0 - sum * std::exp(-x * x);

}