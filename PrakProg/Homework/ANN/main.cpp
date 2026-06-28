#include "ann.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

double g(double x){
    return std::cos(5*x-1)*std::exp(-x*x);
}

double dg(double x){
    return std::exp(-x*x)*
           (-5*std::sin(5*x-1)-2*x*std::cos(5*x-1));
}

void taskA(){
    std::vector<double> xs, ys;

    const int N = 100;

    for(int i=0;i<N;i++){
        double x = -1.0 + 2.0*i/(N-1);
        xs.push_back(x);
        ys.push_back(g(x));
    }

    Ann net(15);

    net.train(xs,ys,10000,0.001);

    std::ofstream out("data_a.txt");

    for(double x=-1.0;x<=1.0;x+=0.01){
        out << x << " "
            << g(x) << " "
            << net.response(x) << "\n";
    }
}

void taskB(){
    std::vector<double> xs, ys;

    const int N = 100;

    for(int i=0;i<N;i++){
        double x = -1.0 + 2.0*i/(N-1);
        xs.push_back(x);
        ys.push_back(g(x));
    }

    Ann net(15);

    net.train(xs,ys,10000,0.001);

    std::ofstream out("data_b.txt");

    for(double x=-1.0;x<=1.0;x+=0.01){
        out << x << " "
            << g(x) << " "
            << net.response(x) << " "
            << dg(x) << " "
            << net.dresponse(x) << " "
            << net.ddresponse(x) << " "
            << net.antiDerivative(x)
            << "\n";
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cerr << "Usage:\n";
        std::cerr << "./main A\n";
        std::cerr << "./main B\n";
        return 1;
    }

    std::string arg = argv[1];

    if(arg == "A"){
        taskA();
    }
    else if(arg == "B"){
        taskB();
    }
    else{
        std::cerr << "Unknown option '" << arg << "'\n";
        return 1;
    }

    return 0;
}