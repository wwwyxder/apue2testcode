#include <iostream>
using namespace std;
class Base{
public:
    virtual void f(){cout<<"base::f"<<endl;}
    int x;
};
class Derive:public Base
{
public:
    virtual void f(){cout<<"derive::f"<<endl;}
    int x;
};
int main()
{
    Base b;
    Derive d;
    b.f();
    d.f();
    (*(Base*)&d).f();
    Base& t = d;
    t.f();

    cout<<"addr of d: "<<(int*)&d<<endl;
    cout<<"addr of ref of d: "<<(int*)&t<<endl;
    cout<<"addr of (Base)d: "<<(int*)&(Base)d<<endl;
    cout<<"addr of (Derive)d: "<<(int*)&(Derive)d<<endl;

    d.x = 1;
    t.x = 2;
    cout<<"d.x: "<<d.x<<endl;
    cout<<"t.x: "<<t.x<<endl;
    return 0;
}
