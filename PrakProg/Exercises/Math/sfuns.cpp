#include<cmath>
#include<numbers> // c++20
#include"sfuns.h"
namespace sfuns{
constexpr double PI = std::numbers::pi; // c++20
// constexpr double PI = 3.14159265358979323846; // pre- c++20
double fgamma(double x){
	if(x<0)return PI/std::sin(PI*x)/fgamma(1-x);
	if(x<9)return fgamma(x+1)/x;
	double lnfgamma=x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*PI/x)/2;
	return std::exp(lnfgamma);
	}


double lngamma(double x) {
    if (x <= 0) 
        return std::numeric_limits<double>::quiet_NaN();

    // Recursion to shift small x upward
    if (x < 9.0)
        return lngamma(x + 1.0) - std::log(x);

    const double pi = std::numbers::pi;

    // Stirling approximation in log form
    double term = x + 1.0 / (12.0*x - 1.0/(10.0*x));
    double lng = x * std::log(term) - x + 0.5 * std::log(2.0*pi/x);

    return lng;
}
}   