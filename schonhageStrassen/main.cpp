#include <iostream>
#include "stdio.h"
#include "fft.h"
#include "main.h"
#include <vector>

using namespace std;

int main()
{
    /* fft based on algorithm from page: http://www.relisoft.com/science/physics/fft.html */
    int Q=337;
    int S=85;
    int PointsNumber = 8;

    /* adding example points to transform t, t2, second half of the points is equal 0 */
    int number1[]={4, 3, 2 ,1};
    int number2[]={8, 7, 6 ,5};

    std::vector < int > integer1;
    std::vector < int > integer2;

    int numebersLength=(sizeof(number1)/sizeof(int));
    for(int i=0;i<numebersLength;i++)
    {
        integer1.push_back(number1[i]);
        integer2.push_back(number2[i]);
    }

    /* creating two Fft objects for two ntt transforms, will be one on target version */
    Fft t( PointsNumber,Q,S);
    Fft t2( PointsNumber,Q,S);
    Fft ti( PointsNumber,Q,S);

    t.PutVector(integer1);
    t2.PutVector(integer2);

    /* forward ntt transform */
    t.Transform(FORWARD);
    t2.Transform(FORWARD);

    /* multiplication of transforms results and putting them to the next transform*/
    t.MultiplicateAndAssign(t2);
    ti.PutTransformResult(t);

    /* invert ntt transform */
    ti.Transform(INVERT);

    printf("Result: \n");
    for(int i=0;i<PointsNumber;i++)
    {
         printf("%d\n", ti._X[i]);
    }

    return 0;
}
