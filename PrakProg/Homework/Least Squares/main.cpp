#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "QR.h"
#include "lsfit.h"

int main() {
    la::Vector t  = {1, 2, 3, 4, 6, 9, 10, 13, 15}; //fra opgaven
    la::Vector y  = {117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1}; //fra opgaven 
    la::Vector dy = {6, 5, 4, 4, 4, 3, 3, 2, 2}; //fra opgaven

    int n = t.size(); //om man bruger t, y eller dy er lige meget, de har samme støresle 

    la::Vector logy(n);
    la::Vector dlogy(n);

    for (int i = 0; i < n; ++i) {
        logy[i] = std::log(y[i]);
        dlogy[i] = dy[i] / y[i];
    }

    std::vector<la::Func> fs = {
        [](double x) { return 1.0; },
        [](double x) { return x; }
    };

    auto [c, cov] = la::lsfit(fs, t, logy, dlogy);

    double ln_a = c[0];
    double slope = c[1];

    double a = std::exp(ln_a);
    double lambda = -slope;
    double T_half = std::log(2.0) / lambda;

    std::cout << "ln(a)   = " << ln_a << "\n";
    std::cout << "a       = " << a << "\n";
    std::cout << "slope   = " << slope << "\n";
    std::cout << "lambda  = " << lambda << "\n";
    std::cout << "T_1/2   = " << T_half << " days\n";
    




    //Plot delen af opgave A

    std::ofstream data("data.txt");
    for (int i = 0; i < n; ++i) {
        data << t[i] << " " << y[i] << " " << dy[i] << "\n";
    }
    data.close();

    std::ofstream fit("fit.txt");
    for (double ti = 0; ti <= 16; ti += 0.1) {
       double yi = a * std::exp(-lambda * ti);
       fit << ti << " " << yi << "\n";
    }
    fit.close();

    std::cout << "T_1/2 = " << T_half << " days\n";


        //Covarians matricen fra opg B
    std::cout << "Covariance matrix:" << std::endl;
    cov.print();
    std::cout << "Det betyder at usikkerhederne er:" << std::endl;
    double errLn = std::sqrt(cov(0,0));
    double errSlope = std::sqrt(cov(1,1));
    std::cout << "Ln(a): " << errLn << std::endl;
    std::cout << "Slope: " << errSlope << std::endl;




      return 0;
}