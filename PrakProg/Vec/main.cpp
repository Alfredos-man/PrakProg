#include <iostream>
#include "vec.h"


int main(){
        vec v1(1,2,3);
        v1.printVec();

        vec v2(3,2,1);
        v2.printVec();

        
        vec sumvec = vecPlus(v1, v2);
        sumvec.printVec();
        
    }