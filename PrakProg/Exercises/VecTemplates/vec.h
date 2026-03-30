#include<iostream>
#include "vec.h"

//fra vec opgaven



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

vec& vec::operator-=(const vec& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

vec& vec::operator*=(double skalar) {
    x *= skalar;
    y *= skalar;
    z *= skalar;
    return *this;
}

vec vecPlus(vec a, const vec& b){
    a += b;
    return a;
}

double dot(vec a, const vec& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

std::ostream& operator<<(std::ostream& os, const vec& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}