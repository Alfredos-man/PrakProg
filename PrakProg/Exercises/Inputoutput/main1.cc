#include <iostream>
#include <vector>
#include <string>
#include <cmath>

//opgave 2 i inout

int main(){
    double x;
    std::cout << "x: sin(x): cos(x):" << std::endl;
    while (std::cin >> x){
        std::cout << x <<" "<< std::sin(x)<<" "<< std::cos(x) << std::endl;
    }


    return 0;
}