#include <iostream>

template <typename T>

class vec {
public:
    T x, y, z;

    vec(T xval, T yval, T zval)
        : x(xval), y(yval), z(zval) {}

    void printVec() const {
        std::cout << "X,Y,Z: " << x << ", " << y << ", " << z << "\n";
    }

    vec& operator+=(const vec& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec& operator-=(const vec& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vec& operator*=(T skalar) {
        x *= skalar;
        y *= skalar;
        z *= skalar;
        return *this;
    }
};

template <typename T>
vec<T> vecPlus(vec<T> a, const vec<T>& b) {
    a += b;
    return a;
}

template <typename T>
T dot(vec<T> a, const vec<T>& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const vec<T>& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

