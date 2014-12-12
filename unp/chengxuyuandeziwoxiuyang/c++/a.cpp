#include <iostream>
using namespace std;
struct A{
    int a;
    int b;
    void f(){
        cout<<"H~"<<endl;
    }
    ~A(){};
};
struct VA{
    int a;
    int b;
    void f(){
        cout<<"H~"<<endl;
    }
    virtual ~VA(){};
};
struct VA2{
    int a;
    int b;
    virtual void f(){
        cout<<"H~"<<endl;
    }
    virtual ~VA2(){};
};
int main()
{
    A a;
    cout<<"without virtual function: "<<sizeof(a)<<endl;
    VA va;
    cout<<"with virtual function: "<<sizeof(va)<<endl;
    VA2 va2;
    cout<<"with virtual function: "<<sizeof(va2)<<endl;
    return 0;
}
