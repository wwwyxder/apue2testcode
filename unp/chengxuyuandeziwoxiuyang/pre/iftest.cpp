#include <iostream>
#define PI 4
using namespace std;
int main()
{
#if PI>3
    cout<<">3"<<endl;
#else
    cout<<"else"<<endl;
#endif
    return 0;
}
