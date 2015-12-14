#include "modoperations.h"

ModOperations::ModOperations(int q)
{
    _q=q;
}

int ModOperations::Multiplicate(int x,int y)
{
    int result=x*y;
    return result % _q;
}

int ModOperations::Add(int x,int y)
{
    int result=x+y;
    return result % _q;
}

int ModOperations::Invert(int x)
{
    int multiplier=0;
    int remainder=0;
        while(remainder !=1)
        {
           multiplier = multiplier + 1;
           int c= x * multiplier;
           remainder= c % _q;
        }
    return multiplier % _q;
}

int ModOperations::Negative(int x)
{
    x = (_q-x) % _q;
    return x;
}
