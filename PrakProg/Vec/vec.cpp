#include<iostream>
#include "vec.h"

vec::vec(double xval, double yval, double zval)
    : x(xval), y(yval), z(zval) {}

void vec::printVec() const {
    std::cout << "X,Y,Z: " << x << ", " << y << ", " << z << "\n";
}

vec& vec::operator+=(const vec& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec vecPlus(vec a, const vec& b) {
    a += b;
    return a;
}
