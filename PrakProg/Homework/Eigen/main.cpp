#include "jakobi.h"
#include <iostream>
#include <random>
#include <cmath>
#include <exception>
#include <algorithm>
#include <cstdlib>

using namespace pp;

Matrix diag(const Vector& w) {
    Matrix D(w.size(), w.size());
    for (int i = 0; i < w.size(); ++i) D(i,i) = w[i];
    return D;
}

double norm_diff(const Matrix& A, const Matrix& B) {
    if (A.rows() != B.rows() || A.cols() != B.cols())
        throw std::invalid_argument("norm_diff: dimension mismatch");

    double s = 0.0;
    for (int i = 0; i < A.rows(); ++i) {
        for (int j = 0; j < A.cols(); ++j) {
            double d = A(i,j) - B(i,j);
            s += d*d;
        }
    }
    return std::sqrt(s);
}

double vec_norm(const Vector& v) {
    double s = 0.0;
    for (int i = 0; i < v.size(); ++i) {
        s += v[i] * v[i];
    }
    return std::sqrt(s);
}

Matrix identity(int n) {
    Matrix I(n,n);
    for (int i = 0; i < n; ++i) I(i,i) = 1.0;
    return I;
}

Matrix random_symmetric_matrix(int n) {
    Matrix A(n,n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-5.0, 5.0);

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            double x = dist(gen);
            A(i,j) = x;
            A(j,i) = x;
        }
    }

    return A;
}

// opgave B hjælpefunktioner
Matrix build_H(double rmax, double dr) {
    int n = (int)(rmax / dr) - 1;

    if (n < 3)
        throw std::invalid_argument("For faa gitterpunkter: vaelg stoerre rmax eller mindre dr");

    Matrix H(n,n);
    Vector r(n);

    for (int i = 0; i < n; ++i)
        r[i] = dr * (i + 1);

    double factor = -0.5 / (dr * dr);

    for (int i = 0; i < n; ++i) {
        H(i,i) = -2.0 * factor;

        if (i > 0)
            H(i,i-1) = factor;

        if (i < n-1)
            H(i,i+1) = factor;
    }

    for (int i = 0; i < n; ++i)
        H(i,i) += -1.0 / r[i];

    return H;
}

void sort_evd(Vector& w, Matrix& V) {
    int n = w.size();

    std::vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = i;

    std::sort(idx.begin(), idx.end(), [&](int a, int b) {
        return w[a] < w[b];
    });

    Vector w_sorted(n);
    Matrix V_sorted(n, n);

    for (int k = 0; k < n; ++k) {
        w_sorted[k] = w[idx[k]];
        for (int i = 0; i < n; ++i) {
            V_sorted(i,k) = V(i, idx[k]);
        }
    }

    w = w_sorted;
    V = V_sorted;
}

double u1s(double r) {
    return 2.0 * r * std::exp(-r);
}

double u2s(double r) {
    return (1.0 / (2.0 * std::sqrt(2.0))) * r * (2.0 - r) * std::exp(-r / 2.0);
}

double u3s(double r) {
    return (2.0 / (81.0 * std::sqrt(3.0))) *
           r * (27.0 - 18.0 * r + 2.0 * r * r) * std::exp(-r / 3.0);
}

int main(int argc, char** argv) {
    if (argc == 3) {
        try {
            double rmax = std::atof(argv[1]);
            double dr   = std::atof(argv[2]);

            if (rmax <= 0.0 || dr <= 0.0)
                throw std::invalid_argument("rmax og dr skal vaere positive");

            Matrix H = build_H(rmax, dr);

            EVD evd(H);
            sort_evd(evd.w, evd.V);

            int n = H.rows();
            Matrix D  = diag(evd.w);
            Matrix VT = transpose(evd.V);
            Matrix I  = identity(n);

            Matrix VTHV = VT * H * evd.V;
            Matrix VDVt = evd.V * D * VT;
            Matrix VTV  = VT * evd.V;
            Matrix VVT  = evd.V * VT;

            std::cerr << "rmax = " << rmax << ", dr = " << dr << "\n";
            std::cerr << "npoints = " << n << "\n\n";

            std::cerr << "Laveste egenvaerdier:\n";
            for (int i = 0; i < std::min(n, 5); ++i) {
                std::cerr << "E[" << i << "] = " << evd.w[i] << "\n";
            }

            std::cerr << "\nForventede hydrogen-vaerdier:\n";
            std::cerr << "E1 = -0.5\n";
            std::cerr << "E2 = -0.125\n";
            std::cerr << "E3 = -0.0555556\n\n";

            for (int k = 0; k < std::min(n, 3); ++k) {
                Vector vk  = evd.V.col(k);
                Vector Hvk = H * vk;
                Vector lvk = vk * evd.w[k];
                Vector res = Hvk - lvk;

                std::cerr << "Residual for state " << k
                          << " = " << vec_norm(res) << "\n";
            }

            std::cerr << "\nFejlmaal:\n";
            std::cerr << "||V^T H V - D|| = " << norm_diff(VTHV, D) << "\n";
            std::cerr << "||V D V^T - H|| = " << norm_diff(VDVt, H) << "\n";
            std::cerr << "||V^T V - I||   = " << norm_diff(VTV, I) << "\n";
            std::cerr << "||V V^T - I||   = " << norm_diff(VVT, I) << "\n";

            double C = 1.0 / std::sqrt(dr);

            // fast globalt fortegn for hver tilstand
            double s1 = 1.0, s2 = 1.0, s3 = 1.0;

            {
                double rref = dr * 1.0;
                double numref = C * evd.V(0, 0);
                double anaref = u1s(rref);
                if (numref * anaref < 0) s1 = -1.0;
            }

            {
                double rref = dr * 2.0;
                double numref = C * evd.V(1, 1);
                double anaref = u2s(rref);
                if (numref * anaref < 0) s2 = -1.0;
            }

            {
                double rref = dr * 3.0;
                double numref = C * evd.V(2, 2);
                double anaref = u3s(rref);
                if (numref * anaref < 0) s3 = -1.0;
            }

            std::cout << "# r num1 ana1 num2 ana2 num3 ana3\n";

            for (int i = 0; i < n; ++i) {
                double r = dr * (i + 1);

                double num1 = s1 * C * evd.V(i, 0);
                double num2 = s2 * C * evd.V(i, 1);
                double num3 = s3 * C * evd.V(i, 2);

                double ana1 = u1s(r);
                double ana2 = u2s(r);
                double ana3 = u3s(r);

                std::cout << r << " "
                          << num1 << " " << ana1 << " "
                          << num2 << " " << ana2 << " "
                          << num3 << " " << ana3 << "\n";
            }

            return 0;
        }
        catch (const std::exception& e) {
            std::cerr << "Fejl: " << e.what() << "\n";
            return 1;
        }
    }
    else if (argc == 1) {
        int n = 4;

        Matrix A = random_symmetric_matrix(n);

        std::cout << "A:\n";
        A.print();

        EVD evd(A);

        Matrix D  = diag(evd.w);
        Matrix VT = transpose(evd.V);
        Matrix I  = identity(n);

        Matrix VTAV = VT * A * evd.V;
        Matrix VDVt = evd.V * D * VT;
        Matrix VTV  = VT * evd.V;
        Matrix VVT  = evd.V * VT;

        std::cout << "\nEigenvalues:\n";
        evd.w.print_vector();

        std::cout << "\nV:\n";
        evd.V.print();

        std::cout << "\nD:\n";
        D.print();

        std::cout << "\nV^T A V:\n";
        VTAV.print();

        std::cout << "\nV D V^T:\n";
        VDVt.print();

        std::cout << "\nV^T V:\n";
        VTV.print();

        std::cout << "\nV V^T:\n";
        VVT.print();

        return 0;
    }
    else {
        std::cerr << "Brug: ./program rmax dr\n";
        return 1;
    }
}