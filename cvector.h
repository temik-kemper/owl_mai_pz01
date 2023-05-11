#ifndef CVECTOR_H
#define CVECTOR_H

#include <complex>
#include <stdio.h>

//using namespace std;
typedef std::complex<double> complex;

class CVector
{
private:
//protected:
    unsigned int size;
//    std::complex<double> *pVector;
    complex *pVector;

    static int error;
public:
    static int GetError(){return error;}
    static void SetError(int e=0){error=e;}

    CVector(unsigned int s=0);
    CVector(const CVector &v);
    ~CVector();

    inline unsigned int GetSize()const{return this->size;}
    void SetSize(unsigned int s=0);

    complex Get(unsigned int index)const;
    void Set(unsigned int index,complex c=0.);

    CVector& operator=(const CVector &v);
    CVector operator-()const;
    inline complex& operator[](unsigned int index){return this->pVector[index];}

    friend CVector operator+(const CVector &v1,const CVector &v2);
    friend CVector operator-(const CVector &v1,const CVector &v2);
    friend CVector operator*(const CVector &v1,const complex &c);
    friend CVector operator/(const CVector &v1,const complex &c);
    friend CVector operator*(const complex &c,const CVector &v1);

    CVector& operator+=(const CVector &v);
    CVector& operator-=(const CVector &v);
    CVector& operator*=(const complex &c);
    CVector& operator/=(const complex &c);

    double norm()const;
    double norm2()const;

    friend complex Scalar(const CVector &v1,const CVector &v2);
};

void Print(const CVector &v);

#endif // CVECTOR_H
