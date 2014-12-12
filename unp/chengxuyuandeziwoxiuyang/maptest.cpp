#include <iostream>
#include <map>
#include <set>
using namespace std;
int main()
{
    map<int,set<int> > neighbs;
    int x, y;
    while(cin>>x>>y) {
        neighbs[x].insert(y);
        neighbs[y].insert(x);
    }
    for(map<int, set<int> >::iterator iter = neighbs.begin();iter!=neighbs.end();++iter) {
        cout<<iter->first<<": ";
        for(set<int>::iterator iter2 = (iter->second).begin();iter2!=(iter->second).end();++iter2) {
            if(iter2!=(iter->second).begin()) cout<<", ";
            cout<<*iter2;
        }
        cout<<endl;
    }
    return 0;
}
