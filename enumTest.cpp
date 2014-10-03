#include <iostream>
using namespace std;
enum Num{
One,Two,Three
};
enum Alpha{
A,B,C
};
void p(Num n){
    cout<<n<<endl;
}
int main()
{
    p(One);
}
