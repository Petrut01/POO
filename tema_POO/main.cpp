#include <iostream>
#include <cmath>
#include <bits/stdC++.h>
using namespace std;
class Numar_Complex
{
    double re,im;
public:
    Numar_Complex();
    Numar_Complex(const Numar_Complex &obj);
    double getre();
    double getim();
    void set_re(double x);
    void set_im(double y);
    void Afisare();
    double Modul();
    Numar_Complex operator + (Numar_Complex const &obj)
    {
        Numar_Complex res;
        res.re = re + obj.re;
        res.im = im + obj.im;
        return res;
    }
    Numar_Complex operator * (Numar_Complex const &obj)
    {
        Numar_Complex res;
        res.re=re*obj.re-im*obj.im;
        res.im=im*obj.re+re*obj.im;
        return res;
    }
    Numar_Complex operator / (Numar_Complex const &obj)
    {
        Numar_Complex res;
        res.re=(re*obj.re+im*obj.im)/(obj.re*obj.re+obj.im*obj.im);
        res.im=(im*obj.re-re*obj.im)/(obj.re*obj.re+obj.im*obj.im);
        return res;
    }

    friend ostream & operator << (ostream &out, const Numar_Complex &c);
    friend istream & operator >> (istream &in,  Numar_Complex &c);
    friend void sqrt(Numar_Complex a);
};
Numar_Complex::Numar_Complex(const Numar_Complex &obj)
    {
        re=obj.re;
        im=obj.im;
    }
Numar_Complex::Numar_Complex()
{
    re=0;
    im=0;
}
double Numar_Complex::getim()
    {
        return im;
    }
double Numar_Complex::getre()
    {
        return re;
    }
void Numar_Complex::set_re(double x)
    {
        re=x;
    }
void Numar_Complex::set_im(double y)
    {
        im=y;
    }
ostream & operator << (ostream &out, const Numar_Complex &c)
{
    if(c.im==0)
        out<<c.re;
    else if(c.re==0)
        out<<c.im<<"*i";
    else
        out<<c.re<<"+"<<c.im<<"*i";
    return out;
}

istream & operator >> (istream &in,  Numar_Complex &c)
{
    cout << "Introduceti partea reala ";
    in >> c.re;
    cout << "Introduceti partea imaginara ";
    in >> c.im;
    return in;
}
void Numar_Complex::Afisare()
{
    if(im==0)
        cout<<re<<" ";
    else if(re==0)
        cout<<im<<"*i"<<" ";
    else
        if(im>0)
            cout<<re<<"+"<<im<<"*i"<<" ";
        else cout<<re<<im<<"*i";
}
double Numar_Complex::Modul()
{
    return sqrt(pow(re,2)+pow(im,2));

}
void sqrt(Numar_Complex a)
{
    cout<< sqrt(complex<double>(a.re,a.im));
}
class Vector_Complex{
    int n;
    Numar_Complex v[100];
    friend class Numar_Complex;
public:

    Vector_Complex(int n,double x);
    Vector_Complex(int n);
    void Afisare_Vector(int n);
    Vector_Complex(const Vector_Complex &obj);
    ~Vector_Complex();
    void Suma_Vector(int n);
    void Sortare(int n);
    void Vector_Module(int n);
    Numar_Complex operator *(Vector_Complex const &obj){
        Numar_Complex p;
        p.set_im(0);
        p.set_re(0);
        int i;
        for(i=0;i<n;i++)
            p=p+(v[i]*obj.v[i]);
        return p;
    }
};
Vector_Complex::Vector_Complex(int n,double x){

    for(int i=0;i<n;i++)
        {v[i].set_re(x);
        v[i].set_im(x);}
}
Vector_Complex::~Vector_Complex(){
    n=0;
}
Vector_Complex::Vector_Complex(int n){
    double x,y;
    for(int i=0;i<n;i++)
        {
            cin>>x>>y;
            v[i].set_re(x);
            v[i].set_im(y);
        }
}
void Vector_Complex::Afisare_Vector(int n){
    for(int i=0 ;i<n; i++)
       v[i].Afisare();
    cout<<endl;
}
Vector_Complex::Vector_Complex(const Vector_Complex &obj)
{
    for(int i=0;i<n;i++)
        v[i]=obj.v[i];
}
void Vector_Complex::Vector_Module(int n)
{
    double a[100];
    for(int i=0;i<n;i++)
        a[i]=v[i].Modul();
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";

}
void Vector_Complex::Sortare(int n){
    int i,ok;
    do{ ok=0;
        for(i=0;i<n-1;i++)
            if(v[i].Modul()>v[i+1].Modul())
                {
                swap(v[i],v[i+1]);
                ok=1;}
    }while(ok!=0);
}
void Vector_Complex::Suma_Vector(int n){
    Numar_Complex s;
    s.set_re(0);
    s.set_im(0);
    for(int i=0;i<n;i++)
        s=s+v[i];
    s.Afisare();
}

int main()
{   int n;
    cin>>n;
    Vector_Complex a[n](3);
    int i;
    for(i=0;i<n;i++)
        a[i].Afisare_Vector(3);

}
