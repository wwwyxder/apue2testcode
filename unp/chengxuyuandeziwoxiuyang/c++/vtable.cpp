#include <iostream>
using namespace std;
class Base
{
public:
    virtual void f() {cout<<"Base::f"<<endl;}
    virtual void g() {cout<<"Base::g"<<endl;}
    virtual void h() {cout<<"Base::h"<<endl;}
};
class Derive:public Base
{
public:
    virtual void g() {cout<<"Derive:g"<<endl;}
};
typedef void (*Fun)(void);

int main()
{
    Base b1,b2;
    Fun p = NULL;
    int* head = (int*)&b1;
    cout<<"vtable head pointor: "<<head<<endl;
    int* pfirstFun = (int*)*head;
    cout<<"first fun: "<<pfirstFun<<endl;
    head = (int*)&b2;
    cout<<"vtable head pointor 2: "<<head<<endl;
    pfirstFun = (int*)*head;
    cout<<"first fun 2: "<<pfirstFun<<endl; //the sam

    p = (Fun)*pfirstFun;
    p();
    ((Fun)*(pfirstFun+1))();
    ((Fun)*(pfirstFun+2))();
    Derive d;
    head = (int*)&d;
    pfirstFun = (int*)*head;
    cout<<"derive:"<<endl;
    for(int i=0;i<=2;++i) 
    {
        p = (Fun)*(pfirstFun+i);
        p();
    }
    return 0;
}
