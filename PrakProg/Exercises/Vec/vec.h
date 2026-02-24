#ifndef VEC_H
#define VEC_H

class vec {
private:
    double x{}, y{}, z{};

public:
    vec() = default;
    vec(double xval, double yval, double zval);

    void printVec() const;
    vec& operator+=(const vec& other);
    vec& operator-=(const vec& other);
    vec& operator*=(double skalar);

};

vec vecPlus(vec a, const vec& b);
vec dot(vec a, const vec& b);

#endif
