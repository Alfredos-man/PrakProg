#pragma once

#include <vector>
#include <functional>
#include <tuple>
#include "matrix.h"

namespace la {

using Func = std::function<double(double)>;

std::tuple<Vector, Matrix> lsfit(
    const std::vector<Func>& fs,
    const Vector& x,
    const Vector& y,
    const Vector& dy
);

}