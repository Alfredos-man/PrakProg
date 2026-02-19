#include <iostream>
#include "vec.h"


int main(){
        std::cout << "init vektor 1" << std::endl;
        vec v1(1,2,3);
        v1.printVec();

        std::cout << "init vektor 1" << std::endl;
        vec v2(3,2,1);
        v2.printVec();

        std::cout << "plus dem sammen" << std::endl;
        vec sumvec = vecPlus(v1, v2);
        sumvec.printVec();
        
    }