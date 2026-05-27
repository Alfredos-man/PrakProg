#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include <vector>

class cspline {
private:
    std::vector<double> x, y, b, c, d;

public:
    cspline(const std::vector<double>& xs,
            const std::vector<double>& ys);

    double eval(double z) const;
    double deriv(double z) const;
    double integ(double z) const;
};

#endif