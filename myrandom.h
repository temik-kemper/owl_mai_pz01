#ifndef MYRANDOM_H
#define MYRANDOM_H

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <complex>

typedef std::complex<double> complex;

class MyRandom
{
public:
    MyRandom();

    void Init(){srand(1);}
    void Randomize(){time(nullptr);}

    inline double GetRand(){return double(rand())/RAND_MAX;}
    double GetReley();
    double GetGauss();
    complex GetCGauss();
};

#endif // MYRANDOM_H
