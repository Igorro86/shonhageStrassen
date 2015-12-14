#include <iostream>
#include "stdio.h"
#include "fft.h"
#include "main.h"

using namespace std;

int main()
{
    /* fft based on algorithm from page: http://www.relisoft.com/science/physics/fft.html */
    int Q=337;
    int S=85;

    ModOperations modular(Q);
    int PointsNumber = 8;
    int Xtemp[PointsNumber];

    /* creating two Fft objects for two ntt transforms, will be one on target version */
    Fft t( PointsNumber,Q,S);
    Fft t2( PointsNumber,Q,S);
    Fft ti( PointsNumber,Q,S);

    /* adding example points to transform t, t2, second half of the points is equal 0 */
    t.PutAt(0,4);
    t.PutAt(1,3);
    t.PutAt(2,2);
    t.PutAt(3,1);

    t2.PutAt(0,8);
    t2.PutAt(1,7);
    t2.PutAt(2,6);
    t2.PutAt(3,5);

    /* forward ntt transform */
    t.Transform(FORWARD);
    t2.Transform(FORWARD);

    printf("multiplipation: \n");

    /* multiplication of transforms results and putting them to the next transform*/

    for(int i=0;i<PointsNumber;i++)
    {
         Xtemp[i]=modular.Multiplicate(t._X[i],t2._X[i]);
         printf("%d \n",t._X[i]);
         ti.PutAt(i,Xtemp[i]);
    }

    /* invert ntt transform */
    ti.Transform(INVERT);

    printf("Result: \n");

    for(int i=0;i<PointsNumber;i++)
    {
         printf("%d\n", ti._X[i]);
    }

    return 0;
}
