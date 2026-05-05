#include <cmath>
#include <numbers>
#include <iostream>
#include "sfuns.h"
#include <complex>

int main(){

    using complex = std::complex<double>;
    const complex i(0.0 , 1.0);

    double a = std::sqrt(2.0);
    double b = std::pow(2 , 0.2);
    double c = std::exp(std::numbers::pi);
    double d = std::pow(std::numbers::pi, std::numbers::e);

    complex e_pow_i   = std::exp(i);           // e^i
    complex pi_pow_e  = std::pow(std::numbers::pi, std::exp(1));      // π^e (real)
    complex pi_pow_i  = std::pow(std::numbers::pi, i);      // π^i
    complex e_pow_i_i = std::pow(i, i);       // i^i
    complex log_i     = std::log(i);          // log(i)

    std::cout << "√2 =" << a << std::endl;
    std::cout << "2^(1/5) =" << b << std::endl;
    std::cout << "e^π =" << c << std::endl;
    std::cout << "π^e =" << d << std::endl;
    std::cout << "complex numbers:" << "\n";
    std::cout << "e^i          = " << e_pow_i << "\n";
    std::cout << "pi^e         = " << pi_pow_e << "\n";
    std::cout << "pi^i         = " << pi_pow_i << "\n";
    std::cout << "i^i          = " << e_pow_i_i << "\n";
    std::cout << "log(i)       = " << log_i << "\n";

    for(int i = 1; i <= 10; i++){  //nu tager gamma funktionen int, kan den dette fordi int også kan skrives som doubles? 
        std::cout << "for x = " << i << " : " << sfuns::fgamma(i) << std::endl;
    }
    std::cout << "Ln gamma funktionen:" << std::endl;
    for (int i = 0; i <= 10; i++){
        std::cout << "for x = " << i << " : " << sfuns::lngamma(i) << std::endl;
    }

    return 0;
}

