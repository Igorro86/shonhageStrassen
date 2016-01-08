#include "carringhandler.h"
#include "stdio.h"
#include <vector>
#include "math.h"

carringhandler::carringhandler(int* inputarray, int piecelength, int PointsNumber)
{
    _inputarray=inputarray;
    _piecelength=piecelength;
    _PointsNumber=PointsNumber;
}

int carringhandler::performCarrying()
{
    int carry=0,carrytemp=0;
    std::vector < int* > piecesNumbersToSum;
    piecesNumbersToSum.push_back(new int[2]{0,0});
    _resultLength=_PointsNumber*_piecelength*2;
    int *carriedResult= new int[_resultLength];
    int lastpiecenumber=0;

    for(int i=0; i<_resultLength; i++)
    {
        if(i!=0 && i%_piecelength==0)
        {
            lastpiecenumber++;
            if(lastpiecenumber<_PointsNumber)
            {
                piecesNumbersToSum.push_back(new int[2]{lastpiecenumber,0});
            }
        }

        if(!piecesNumbersToSum.empty())
        {
            if(piecesNumbersToSum[0][INDEX]==(_piecelength*2-1))
            {
               piecesNumbersToSum.erase(piecesNumbersToSum.begin());
            }

            carriedResult[i]=0;
            for(int j=0; j<piecesNumbersToSum.size();j++)
            {
                if(piecesNumbersToSum[j][NUMBER]<_PointsNumber)
                {
                     int digit=getDigit( _inputarray[piecesNumbersToSum[j][NUMBER]],  piecesNumbersToSum[j][INDEX]);
                     carriedResult[i]+=digit;
                     piecesNumbersToSum[j][INDEX]++;
                }
            }
        }

        carriedResult[i]+=carry;
        carrytemp=carriedResult[i];
        carriedResult[i]=carriedResult[i]%10;
        carry=carrytemp/10;
    }

    _carriedResult=carriedResult;
}

int carringhandler::getDigit(int from, int index)
{
    return (from / (int)pow(10, index)) % 10;
}

int* carringhandler::getCarriedResult()
{
    return _carriedResult;
}

int carringhandler::getResultLength()
{
    return _resultLength;
}
