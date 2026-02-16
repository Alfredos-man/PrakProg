#include <iostream>

class vec {
    private: //ved ikke om det er smartere at lave den private
    //Konstruktor hvis ikke man giver nogle paramedre opretter den en klasse med x,y,z = 0
    double x{};
    double y{};
    double z{};

    vec() = default;

     //hvis man giver argumenter:
    vec(double xval, double yval, double zval)
        : x(xval), y(yval), z(zval) {}
    
    vec(const vec&) = default;

    vec(vec&&) = default; 

    //print metode til debugging
    void printVec const(){
        std::cout << " X,Y,Z: " << x << y << z << std::endl;
    }

    void vecPlus(vec a, const vec& b){
        vec r = a;
        r += b; 
        return r;
    }

}

    int main(){
        v1 = vec(1,2,3);
        v1.printVec();

        v2 = vec(3,2,1);
        v2.printVec();

        sumvec = vecPlus(v1, v2);
        
        sumvec.printVec();
        
    }

