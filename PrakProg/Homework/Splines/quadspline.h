#ifndef QUADSPLINE_H
#define QUADSPLINE_H

#include <vector>

class qspline {
private:
    std::vector<double> x, y, b, c;

public:
    qspline(const std::vector<double>& xs,
            const std::vector<double>& ys);

    double eval(double z) const;
    double deriv(double z) const;
    double integ(double z) const;
};

#endif