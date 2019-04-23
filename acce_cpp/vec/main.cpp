#include<iostream>
#include"vec.h"

using namespace std;
template<typename T>
void dumpVec(const Vec<T>& v)
{
    for(const T& val: v)
    {
        cout << val << " ";
    }
    cout << endl;
}

int main()
{
    Vec<int> v(10, 0);
    dumpVec(v);
    cout << endl;
    v = Vec<int>();
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    dumpVec(v);
    cout << "done" << endl;
    return 0;
}

