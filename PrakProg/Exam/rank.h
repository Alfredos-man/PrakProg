#ifndef RANK_H
#define RANK_H

#include <vector>

std::vector<double> rank1Eigenvalues(
    std::vector<double> d,
    std::vector<double> u,
    double tol = 1e-12,
    int maxIter = 200
);

#endif