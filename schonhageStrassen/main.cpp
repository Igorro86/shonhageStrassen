#include <iostream>
#include "stdio.h"
#include "fft.h"
#include "main.h"
#include "integerfilehandler.h"
#include <vector>
#include "carringhandler.h"
#include "modoperations.h"

using namespace std;


int main()
{
    integerfilehandler intreader1("liczba.txt");
    integerfilehandler intreader2("liczba2.txt");
    int PointsNumber = 8;
    int Q=ModOperations::qFinder(PointsNumber);
    ModOperations mod(Q);
    /* fft based on algorithm from page: http://www.relisoft.com/science/physics/fft.html */
    //int Q=337;
    //int S=85;
    int S=mod.RootOfUnity(PointsNumber,Q);

    int* resultarray;
    std::vector < int > integer1=intreader1.getPointsSetVect();
    for(int i=0; i<integer1.size();i++)
    {
            printf("%d \n", integer1[i]);
    }

    printf("\n");
    std::vector < int > integer2=intreader2.getPointsSetVect();
    for(int i=0; i<integer2.size();i++)
    {
            printf("%d \n", integer2[i]);
    }

    /* creating two Fft objects for two ntt transforms */
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

    printf("zrobione \n\n");

    //resultvect.push_back(ti._X);
    resultarray=ti._X;

    for(int i=0; i<1;i++)
    {
        printf("wyniczek: %d\n",i);
        for(int j=0;j<PointsNumber;j++)
        {
             printf("%d\n", resultarray[j]);
        }
    }

    printf("\n");

    carringhandler resultCarrier(resultarray,16,PointsNumber);
    resultCarrier.performCarrying();
    int* carriedResult=resultCarrier.getCarriedResult();
    int resultLength=resultCarrier.getResultLength();

    printf("result: \n");
    for(int i=0; i<resultLength; i++)
    {
        printf("%d", carriedResult[resultLength-i-1]);
    }
    printf("\n");

    return 0;
}


