#ifndef CVECTORDFT_H
#define CVECTORDFT_H

#include "cvector.h"

class CVectorDFT:public CVector
{
public:
    CVectorDFT(unsigned int s=0):CVector(s){}
    CVectorDFT(const CVectorDFT &v):CVector(v){}
    CVectorDFT(const CVector &v):CVector(v){}

    CVectorDFT DFT()const;
    CVectorDFT IDFT()const;
    CVectorDFT Restore(unsigned int n)const;


};

#endif // CVECTORDFT_H
