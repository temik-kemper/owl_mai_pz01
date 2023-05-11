#include "cvectordft.h"

CVectorDFT CVectorDFT::DFT()const
{
    complex x,cr,m;
    double fi;
    CVectorDFT v(this->GetSize());

    for(unsigned int i1=0;i1<v.GetSize();i1++)
    {
        //Цикл по частоте
        fi=-2.*M_PI*i1/v.GetSize();
        m=complex(cos(fi),sin(fi));
        x=0.;cr=1.;
        for(unsigned int i2=0;i2<this->GetSize();i2++)
        {
            //Цикл по времени
            x+=this->Get(i2)*cr;
            cr*=m;
        }//for(unsigned int i2=0;i2<this->GetSize();i2++)
        x/=this->GetSize();
        v[i1]=x;
    }//for(unsigned int i1=0;i1<v.GetSize();i1++)

    return v;
}//CVectorDFT CVectorDFT::DFT()const

CVectorDFT CVectorDFT::IDFT()const
{
    complex x,cr,m;
    double fi;
    CVectorDFT v(this->GetSize());

    for(unsigned int i1=0;i1<v.GetSize();i1++)
    {
        //Цикл по частоте
        fi=2.*M_PI*i1/v.GetSize();
        m=complex(cos(fi),sin(fi));
        x=0.;cr=1.;
        for(unsigned int i2=0;i2<this->GetSize();i2++)
        {
            //Цикл по времени
            x+=this->Get(i2)*cr;
            cr*=m;
        }//for(unsigned int i2=0;i2<this->GetSize();i2++)

        v[i1]=x;
    }//for(unsigned int i1=0;i1<v.GetSize();i1++)

    return v;
}//CVectorDFT CVectorDFT::IDFT()const

CVectorDFT CVectorDFT::Restore(unsigned int n)const
{
    complex cr,m;
    double fi;
    CVectorDFT v;
    if(this->GetSize() == 0) return v;

    v.SetSize(this->GetSize());
    if(v.GetError() < 0) return v;

    for(unsigned int i1=0;i1<n;i1++)
    {
        //Цикл по частоте
        if(i1 > this->GetSize()/2) break;

        fi=2.*M_PI*i1/v.GetSize();
        m=complex(cos(fi),sin(fi));
        cr=1.;
        for(unsigned int i2=0;i2<v.GetSize();i2++)
        {
            //Цикл по времени
            if(i1 == 0)
            {
                v[i2]+=this->Get(0);
            }//if(i1 == 0)
            else
            {
                v[i2]+=Get(i1)*cr;
                if(i1<=(this->GetSize()-1)/2)
                    v[i2]+=Get(this->GetSize()-i1)*conj(cr);
                cr*=m;
            }//else if(i1 == 0)

        }//for(unsigned int i2=0;i2<v.GetSize();i2++)
    }//for(unsigned int i1=0;i1<n;i1++)

    return v;
}//CVectorDFT CVectorDFT::Restore(unsigned int n)const
