#include <iostream>
#include "vec.h"


int main(){
        std::cout << "init vektor 1" << std::endl;
        vec v1(1.6, 2.3, 3.2);
        v1.printVec();

        std::cout << "init vektor 1" << std::endl;
        vec v2(3.1 ,2.1 ,1.2);
        v2.printVec();

        std::cout << "plus dem sammen" << std::endl;
        vec sumvec = vecPlus(v1, v2);
        sumvec.printVec();

        std::cout << "dot prod" << std::endl;
        double dotVec = dot(v1, v2);
        std::cout << dotVec << std::endl;
        


        //Med overloadet std::cout
        std::cout << "overloaded std::cout med vektore:" << std::endl;
        std::cout << "vektor 1: " << v1 << std::endl;
        std::cout << "vektor 2: " << v2 << std::endl;
        std::cout << "plusset sammen vektor: " << sumvec << std::endl;

    }