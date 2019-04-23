#ifndef STR_H
#define STR_H

#include"vec.h"
#include<algorithm>
#include<cstring>
#include<algorithm>
#include<iostream>

class Str
{
    friend std::istream& operator>>(std::istream&, Str&);
public:
    typedef Vec<char>::size_type size_type;

    Str(){}

    Str(size_type n, char c):data(n, c){}

    Str(const char* p): Str(p, p + std::strlen(p)){}

    template<typename In>
    Str(In b, In e)
    {
        std::copy(b, e, std::back_inserter(data));
    }

    char& operator[](size_type i)
    {
        return data[i];
    }

    Str& operator+=(const Str& str)
    {
        std::copy(str.data.begin(), str.data.end(), std::back_inserter(data));
        return *this;
    }

    const char& operator[](size_type i) const
    {
        return data[i];
    }

    size_type size(){return data.size();}

    size_type size() const {return data.size();}

private:
    Vec<char> data;

};

std::ostream& operator<<(std::ostream&, const Str&);
Str operator+(const Str& lhs, const Str& rhs);

#endif