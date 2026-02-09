#include <iostream>
#include<limits>

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

}