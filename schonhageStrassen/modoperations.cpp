#include "modoperations.h"
#include <math.h>

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

long ModOperations::Pow(int x,int y)
{
    long result=1;
    for(int k=0;k<y;k++)
    {
        result=this->Multiplicate(result,x);
    }
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

//input is N-number of digits, output is prime number q
int ModOperations::qFinder(int x)
{
    int qmin=(x/2)*99999999999999999;
    int q;
    bool qchecker=false;
        while(qchecker!=true)
        {
            bool primechecker=false;
            int round_down=0;
                while(primechecker!=true)
                {
                    qmin=qmin+1;
                    round_down=floor(sqrt(qmin));
                        for (int l=2; l<=round_down; l++)
                        {
                            if(qmin%l==0)
                               break;
                            if(l==round_down)
                            {
                                //int qprime=qmin;
                                primechecker=true;
                                break;
                            }
                        }

                }
            //check if q as a prime number is good choice
            //q must have N odd roots of unity, it happens when N is divisor of qmin-1
            if ((qmin-1)%x==0)
            {
                q=qmin;
                qchecker=true;
            }
            else
            {
                primechecker=false;
            }
        }
    return q;
}

//finding lowest root of unity s, inputs are N and q, output is s
int ModOperations::RootOfUnity(int x, int y)
{
    int j=2;
    bool rootofunity=false;
        while(rootofunity!=true)
        {
            if (this->Pow(j,x)==1)
            {
               rootofunity=true;
            }
            else
            {
                j=j+1;
            }
        }
    return j;
}



