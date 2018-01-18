#ifndef CASE
#define CASE


#include <iostream>
using namespace std;

template <class T>
class Case{
public:
    Case():val(0){}

    Case(T v):val(v){}
    T getValue()const{return val;}

void setValue(T i){val=i;}
    
private:
    T val;
    friend ostream& operator<<(ostream& out,Case<int> c);

};


#endif