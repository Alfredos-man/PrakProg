#pragma once
#ifndef INTERP_H
#define INTERP_H

#include <vector>

int binsearch(const std::vector<double>& x, double z);


double linterp(const std::vector<double>& x,
               const std::vector<double>& y,
               double z);


double linterpInteg(const std::vector<double>& x,
                    const std::vector<double>& y,
                    double z);
                    

#endif