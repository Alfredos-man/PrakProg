#pragma once
#include <functional>
#include <vector>


namespace la {

using Func = std::function<double(double)>;

Vector lsfit(
    const std::vector<Func>& fs,
    const Vector& x,
    const Vector& y,
    const Vector& dy
);

}