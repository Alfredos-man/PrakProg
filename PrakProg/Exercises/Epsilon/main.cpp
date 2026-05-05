#include <iostream>
#include<limits>
#include <cmath>
#include <iomanip>


bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9) {
    double diff = std::abs(a - b);

    // absolut check (vigtig nær 0)
    if (diff <= acc) return true;

    // relativ check
    double max_ab = std::max(std::abs(a), std::abs(b));
    return diff <= eps * max_ab;
}

int main(){

    //Opgave 1
    float       f=1.0f; while((float)      (1.0f+f) != 1.0f){f/=2.0f;} f*=2.0f;  //Ideen her er, at man bliver ved med at halvere vores variabel indtil at vores "nye" værdi ikke længere bliver ændret. Derved finder vi epsilon
    double      d=1.0; while((double)     (1.0+d) != 1.0){d/=2.0;} d*=2.0;
    long double l=1.0L; while((long double)(1.0L+l) != 1.0L){l/=2.0L;} l*=2.0L;

    
    std::printf("      float eps=%g\n",f);
    std::printf("     double eps=%g\n",d);
    std::printf("long double eps=%Lg\n",l); //Det giver også god mening at double og long double har mindre epsilon


    std::cout << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << std::numeric_limits<double>::epsilon() << "\n";
    std::cout << std::numeric_limits<long double>::epsilon() << "\n";
    std::cout << "De stemmer overens" << "\n";

    //Opgave 2
    std::cout << "______________________________________________________________________" << "\n";
    std::cout << "Opgave 2" << "\n";

    double epsilon = std::pow(2, -52);
    double tiny = epsilon / 2;

    double a = 1 + tiny + tiny;
    double b = tiny + tiny + 1;

    std::cout << std::boolalpha;
    std::cout << "a==b ? " << (a == b) << "\n";
    std::cout << "a>1  ? " << (a > 1) << "\n";
    std::cout << "b>1  ? " << (b > 1) << "\n";

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "tiny=" << tiny << "\n";
    std::cout << "1+tiny+tiny=" << a << "\n";
    std::cout << "tiny+tiny+1=" << b << "\n";
    std::cout << "Forskellen opstår, fordi floating point-tal afrundes efter hver operation. Når tiny lægges til 1, er det for lille til at ændre værdien, og resultatet forbliver 1. Men når tiny + tiny først beregnes, bliver resultatet epsilon, som er stort nok til at ændre 1. Derfor afhænger resultatet af rækkefølgen, og addition er ikke associativ i floating point aritmetik." << "\n";

        std::cout << "______________________________________________________________________\n";
    std::cout << "Opgave 3\n";

    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1;

    std::cout << std::boolalpha;

    // Direkte sammenligning
    std::cout << "d1 == d2 ? " << (d1 == d2) << "\n";

    // Approx sammenligning
    std::cout << "approx(d1,d2) ? " << approx(d1, d2) << "\n";

    // Print med høj præcision så man kan se forskellen
    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1 = " << d1 << "\n";
    std::cout << "d2 = " << d2 << "\n";
    std::cout << "difference = " << std::abs(d1 - d2) << "\n";
}