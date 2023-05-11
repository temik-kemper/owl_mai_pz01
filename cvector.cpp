#include "cvector.h"

//--------------------class CVector--------------------------------------------
int CVector::error=0;

CVector::CVector(unsigned int s)
{
    if(s == 0)
    {
        this->size=0;
        this->pVector=nullptr;
    }//if(s == 0)
    else
    {
        pVector=new complex [s];
        if(pVector == nullptr)
        {
            this->size=0;
            this->error=-1;
        }//if(pVector == nullptr)
        else
        {
            this->size=s;
            for(unsigned int i=0;i<this->size;i++) this->pVector[i]=0.;
        }//else if(pVector == nullptr)

    }//else if(s == 0)
}//CVector::CVector(unsigned int s)

CVector::CVector(const CVector &v)
{
    if(v.size == 0)
    {
        this->size=0;
        this->pVector=nullptr;
    }//if(v.size == 0)
    else
    {
        this->pVector=new complex [v.size];
        if(this->pVector == nullptr)
        {
            this->size=0;
            this->error=-1;
        }//if(this->pVector == nullptr)
        else
        {
            this->size=v.size;
            for(unsigned int i=0;i<this->size;i++) this->pVector[i]=v.pVector[i];
        }//else if(this->pVector == nullptr)
    }//else if(v.size == 0)

}//CVector::CVector(const CVector &v)

CVector::~CVector()
{
    if(this->pVector != nullptr) delete [] this->pVector;
}//CVector::~CVector()

void CVector::SetSize(unsigned int s)
{
    if(s==0)
    {
        if(this->pVector != nullptr) delete [] this->pVector;

        this->pVector=nullptr;
        this->size=0;
    }//if(s==0)
    else
    {
        complex *pV;
        pV=new complex [s];
        if(pV == nullptr)
        {
            this->error=-1;
        }//if(pV == nullptr)
        else
        {
            for(unsigned int i=0;i<s;i++)
            {
                if(i<this->size) pV[i]=this->pVector[i];
                else pV[i]=0.;
            }//for(unsigned int i=0;i<s;i++)

            if(this->pVector != nullptr) delete [] this->pVector;
            this->size=s;
            this->pVector=pV;
        }//else if(pV == nullptr)


    }//else if(s==0)
}//void CVector::SetSize(unsigned int s)

complex CVector::Get(unsigned int index)const
{
    if(index < this->size) return this->pVector[index];
    else
    {
        this->error=-2;
        return 0.;
    }//else if(index < this->size)
}//complex CVector::Get(unsigned int index)const

void CVector::Set(unsigned int index,complex c)
{
    if(index < this->size) this->pVector[index]=c;
    else this->error=-2;
}//void CVector::Set(unsigned int index,complex c)

CVector& CVector::operator=(const CVector &v)
{
    if(this->pVector != nullptr) delete [] this->pVector;

    if(v.size == 0)
    {
        this->size=0;
        this->pVector=nullptr;
    }//if(v.size == 0)
    else
    {
        this->pVector=new complex [v.size];
        if(this->pVector == nullptr)
        {
            this->size=0;
            this->error=-1;
        }//if(this->pVector == nullptr)
        else
        {
            this->size=v.size;
            for(unsigned int i=0;i<this->size;i++) this->pVector[i]=v.pVector[i];
        }//else if(this->pVector == nullptr)
    }//else if(v.size == 0)

    return *this;
}//CVector& CVector::operator=(const CVector &v)

CVector CVector::operator-()const
{
    CVector v(*this);

    for(unsigned int i=0;i<v.size;i++) v.pVector[i]=-v.pVector[i];

    return v;
}//CVector CVector::operator-()const

CVector operator+(const CVector &v1,const CVector &v2)
{
    CVector v;
    if(v1.size != v2.size) v.error=-2;
    else
    {
        v.SetSize(v1.size);
        for(unsigned int i=0;i<v.size;i++)
        {
            v.pVector[i]=v1.pVector[i]+v2.pVector[i];
        }//for(unsigned int i=0;i<v.size;i++)
    }//if(v1.size != v2.size)

    return v;
}//CVector operator+(const CVector &v1,const CVector &v2)

CVector operator-(const CVector &v1,const CVector &v2)
{
    CVector v;
    if(v1.size != v2.size) v.error=-2;
    else
    {
        v.SetSize(v1.size);
        for(unsigned int i=0;i<v.size;i++)
        {
            v.pVector[i]=v1.pVector[i]-v2.pVector[i];
        }//for(unsigned int i=0;i<v.size;i++)
    }//if(v1.size != v2.size)

    return v;
}//CVector operator-(const CVector &v1,const CVector &v2)

CVector operator*(const CVector &v1,const complex &c)
{
    CVector v(v1);

    for(unsigned int i=0;i<v.size;i++) v.pVector[i]*=c;

    return v;
}//CVector operator*(const CVector &v1,const complex &c)

CVector operator/(const CVector &v1,const complex &c)
{
    CVector v(v1);

    for(unsigned int i=0;i<v.size;i++) v.pVector[i]/=c;

    return v;
}//CVector operator/(const CVector &v1,const complex &c)

CVector operator*(const complex &c,const CVector &v1)
{
    CVector v(v1);

    for(unsigned int i=0;i<v.size;i++) v.pVector[i]*=c;

    return v;
}//CVector operator*(const complex &c,const CVector &v1)

CVector& CVector::operator+=(const CVector &v)
{
    if(this->size != v.size) this->error=-2;
    else
    {
        for(unsigned int i=0;i<this->size;i++) this->pVector[i]+=v.pVector[i];
    }//else if(this->size != v.size)

    return *this;
}//CVector& CVector::operator+=(const CVector &v)

CVector& CVector::operator-=(const CVector &v)
{
    if(this->size != v.size) this->error=-2;
    else
    {
        for(unsigned int i=0;i<this->size;i++) this->pVector[i]-=v.pVector[i];
    }//else if(this->size != v.size)

    return *this;
}//CVector& CVector::operator-=(const CVector &v)

CVector& CVector::operator*=(const complex &c)
{
    for(unsigned int i=0;i<this->size;i++) this->pVector[i]*=c;

    return *this;
}//CVector& CVector::operator*=(const complex &c)

CVector& CVector::operator/=(const complex &c)
{
    for(unsigned int i=0;i<this->size;i++) this->pVector[i]/=c;

    return *this;
}//CVector& CVector::operator/=(const complex &c)

double CVector::norm()const
{
    double d=0.;

    for(unsigned int i=0;i<this->size;i++)
        d+= this->pVector[i].real()*this->pVector[i].real()+
            this->pVector[i].imag()*this->pVector[i].imag();

    return sqrt(d);
}//double CVector::norm()const

double CVector::norm2()const
{
    double d=0.;

    for(unsigned int i=0;i<this->size;i++)
        d+= this->pVector[i].real()*this->pVector[i].real()+
            this->pVector[i].imag()*this->pVector[i].imag();

    return (d);
}//double CVector::norm2()const

complex Scalar(const CVector &v1,const CVector &v2)
{
    complex c=0.;

    if(v1.size == v2.size)
    {
        for(unsigned int i=0;i<v1.size;i++)
            c+=v1.pVector[i]*conj(v2.pVector[i]);
    }//if(v1.size == v2.size)
    else v1.error=-2;

    return c;
}//complex Scalar(const CVector &v1,const CVector &v2)

//-------------------\class CVector--------------------------------------------

void Print(const CVector &v)
{
    printf("\n\tv=%u error=%i",v.GetSize(),v.GetError());

    for(unsigned int i=0;i<v.GetSize();i++)
    {
        printf("\n\tv[%u]=(%lg,%lg)",i,v.Get(i).real(),v.Get(i).imag());
    }//for(unsigned int i=0;i<v.GetSize();i++)

    printf("\n\n");
}//void Print(const CVector &v)
