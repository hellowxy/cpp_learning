#include"Str.h"
#include<cctype>
#include<iostream>
using namespace std;

istream& operator>>(istream& in, Str& str)
{
    str.data.clear();
    char c;
    while(in.get(c) && isspace(c))
    {
    }

    if(in)
    {
        do
        {
            str.data.push_back(c);
        } while (in.get(c) && !isspace(c));
    }
    return in;
}

ostream& operator<<(ostream& out, const Str& str)
{
    for(Str::size_type i = 0; i < str.size(); i++)
    {
        out << str[i];
    }
    return out;
}

Str operator+(const Str& lhs, const Str& rhs)
{
    Str r = lhs;
    r += rhs;
    return r;
}