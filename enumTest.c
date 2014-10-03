#include <stdio.h>
enum Num{
One,Two,Three
};
enum Alpha{
A,B,C
};
void f(enum Num n)
{}
int main()
{
    f(One);
    f(A);
    enum Num n = B;
    n = A;
    return 0;
}
