#pragma once
#include <vector>
#include <cmath>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <iomanip>


namespace la {

struct Vector {
    std::vector<double> a;

    Vector() = default;
    explicit Vector(int n) : a(n, 0.0) {}
    Vector(std::initializer_list<double> init) : a(init) {}

    int size() const { 
        return (int)a.size(); 
    }

    double& operator[](int i) { return a[i]; }
    double  operator[](int i) const { return a[i]; }

    double norm() const {
        double s = 0.0;
        for (double x : a) s += x * x;
        return std::sqrt(s);
    }

    Vector& operator+=(const Vector& other) {
        if (size() != other.size()) throw std::invalid_argument("Vector += size mismatch");
        for (int i = 0; i < size(); ++i) a[i] += other[i];
        return *this;
    }

    Vector& operator-=(const Vector& other) {
        if (size() != other.size()) throw std::invalid_argument("Vector -= size mismatch");
        for (int i = 0; i < size(); ++i) a[i] -= other[i];
        return *this;
    }

    Vector& operator*=(double s) {
        for (double& x : a) x *= s;
        return *this;
    }

    Vector& operator/=(double s) {
        if (s == 0.0) throw std::invalid_argument("Vector /= divide by zero");
        for (double& x : a) x /= s;
        return *this;
    }
};

inline Vector operator+(Vector v, const Vector& w) { return v += w; }
inline Vector operator-(Vector v, const Vector& w) { return v -= w; }
inline Vector operator*(Vector v, double s) { return v *= s; }
inline Vector operator*(double s, Vector v) { return v *= s; }
inline Vector operator/(Vector v, double s) { return v /= s; }

inline double dot(const Vector& u, const Vector& v) {
    if (u.size() != v.size()) throw std::invalid_argument("dot size mismatch"); //sikre error ved dimentionsfejl
    double s = 0.0;
    for (int i = 0; i < u.size(); ++i) s += u[i] * v[i];
    return s;
}

struct Matrix {
    int n = 0, m = 0;              // rows, cols
    std::vector<double> a;         // row-major: a[i*m + j]

    Matrix() = default;
    Matrix(int rows, int cols) : n(rows), m(cols), a((size_t)rows * cols, 0.0) {
        if (rows < 0 || cols < 0) throw std::invalid_argument("Matrix: negative size");
    }

    int rows() const { return n; }
    int cols() const { return m; }

    double& operator()(int i, int j) { return a[(size_t)i * m + j]; }
    double  operator()(int i, int j) const { return a[(size_t)i * m + j]; }

    Vector col(int j) const {
        Vector v(n);
        for (int i = 0; i < n; ++i) v[i] = (*this)(i, j);
        return v;
    }

    void set_col(int j, const Vector& v) {
        if (v.size() != n) throw std::invalid_argument("set_col size mismatch");
        for (int i = 0; i < n; ++i) (*this)(i, j) = v[i];
    }

    void print() const {
    std::cout<<"Start"<<std::endl;
    for(int i = 0; i < rows(); ++i){
        for(int j = 0; j < cols(); ++j){
            std::cout << std::setw(10) << (*this)(i,j) << " ";
        }
        std::cout << "\n";
    }
    std::cout<<"Slut"<<std::endl;
}


};

inline Matrix operator*(const Matrix& A, const Matrix& B) {
    if (A.cols() != B.rows()) throw std::invalid_argument("Matrix*Matrix dim mismatch");
    Matrix C(A.rows(), B.cols());
    for (int i = 0; i < C.rows(); ++i)
        for (int k = 0; k < A.cols(); ++k) {
            double aik = A(i, k);
            for (int j = 0; j < C.cols(); ++j)
                C(i, j) += aik * B(k, j);
        }
    return C;
}

inline Vector operator*(const Matrix& A, const Vector& x) {
    if (A.cols() != x.size()) throw std::invalid_argument("Matrix*Vector dim mismatch");
    Vector b(A.rows());
    for (int i = 0; i < A.rows(); ++i) {
        double s = 0.0;
        for (int j = 0; j < A.cols(); ++j) s += A(i, j) * x[j];
        b[i] = s;
    }
    return b;
}

inline Matrix transpose(const Matrix& A) {
    Matrix T(A.cols(), A.rows());
    for (int i = 0; i < A.rows(); ++i)
        for (int j = 0; j < A.cols(); ++j)
            T(j, i) = A(i, j);
    return T;
}

} // namespace la