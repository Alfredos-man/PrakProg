#include "jakobi.h"
#include <iostream>
#include <random>
#include <cmath>
#include <exception>
#include <algorithm>

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

    //opgave B hjælpe funktioner
    Matrix build_H(double rmax, double dr) {
    int n = (int)(rmax / dr) - 1;

    Matrix H(n,n);
    Vector r(n);

    for (int i = 0; i < n; ++i)
        r[i] = dr * (i + 1);

    double factor = -0.5 / (dr * dr);

    for (int i = 0; i < n; ++i) {
        H(i,i) = -2 * factor;

        if (i > 0)
            H(i,i-1) = factor;

        if (i < n-1)
            H(i,i+1) = factor;
    }

    for (int i = 0; i < n; ++i)
        H(i,i) += -1.0 / r[i];

    return H;
}

void sort_evd(pp::Vector& w, pp::Matrix& V) {
    int n = w.size();

    // lav indeks array
    std::vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = i;

    // sortér indeks efter w
    std::sort(idx.begin(), idx.end(), [&](int a, int b) {
        return w[a] < w[b];
    });

    // kopiér gamle værdier
    pp::Vector w_sorted(n);
    pp::Matrix V_sorted(n, n);

    for (int k = 0; k < n; ++k) {
        w_sorted[k] = w[idx[k]];

        for (int i = 0; i < n; ++i) {
            V_sorted(i,k) = V(i, idx[k]); // kolonne
        }
    }

    w = w_sorted;
    V = V_sorted;
}


int main(int argc, char** argv) {
    if (argc == 3){
    try {
        double rmax = std::atof(argv[1]);
double dr   = std::atof(argv[2]);

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


// plotdata -> fil via stdout
double C = 1.0 / std::sqrt(dr);

// header
std::cout << "# r num1 ana1 num2 ana2 num3 ana3\n";

for (int i = 0; i < n; ++i) {
    double r = dr * (i + 1);

    double num1 = C * evd.V(i, 0);
    double num2 = C * evd.V(i, 1);
    double num3 = C * evd.V(i, 2);

    double ana1 = 2.0 * r * std::exp(-r);
    double ana2 = (1.0 / (2.0 * std::sqrt(2.0))) * r * (2.0 - r) * std::exp(-r / 2.0);
    double ana3 = (2.0 / (81.0 * std::sqrt(3.0))) *
                  r * (27.0 - 18.0 * r + 2.0 * r * r) * std::exp(-r / 3.0);

    // egenvektorer kan have modsat fortegn af analytisk løsning
    // så evt. vend fortegn hvis du vil have kurverne til at ligge oven i hinanden
    if (num1 * ana1 < 0) num1 = -num1;
    if (num2 * ana2 < 0) num2 = -num2;
    if (num3 * ana3 < 0) num3 = -num3;

    std::cout << r << " "
              << num1 << " " << ana1 << " "
              << num2 << " " << ana2 << " "
              << num3 << " " << ana3 << "\n";
}

return 0;}
    catch (const std::exception& e) {
        std::cerr << "Fejl: " << e.what() << "\n";
        return 1;
    }

    }
    else(argc == 1);
    {
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
    

}
