#include "myrandom.h"

MyRandom::MyRandom()
{
    this->Randomize();
}//MyRandom::MyRandom()

double MyRandom::GetReley()
{
    int i;
    i=rand();
    if(i==0)  i=1;
    return sqrt(-2.*log(double(i)/RAND_MAX));
}//double MyRandom::GetReley()

double MyRandom::GetGauss()
{
    double d=0.;
    for(int i=0;i<12;i++) d+=this->GetRand();

    return d-6.;
}//double MyRandom::GetGauss()

complex MyRandom::GetCGauss()
{
    double a,fi;
    a=this->GetReley();
    fi=2.*M_PI*this->GetRand();

    return complex(a*cos(fi),a*sin(fi));
}//complex MyRandom::GetCGauss()
