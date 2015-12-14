// Use complex numbers from Standard Library>
#include "fft.h"
#include "stdio.h"
#include "math.h"
#include "modoperations.h"

// Points must be a power of 2
Fft::Fft (int Points, int Qm, int Nroot)
    : _PointsNum (Points),_Qm(Qm),_Nroot(Nroot)
{

    ModOperations modular(_Qm);
    _sqrtPoints = sqrt((double)_PointsNum);
    // calculate binary log
    _logPoints = 0;
    Points--;
    while (Points != 0)
    {
        Points >>= 1;
        _logPoints++;
    }

    // This is where the original samples will be stored
    _aTape = new double [_PointsNum];
    for (int i = 0; i < _PointsNum; i++)
        _aTape[i] = 0;

    // This is the in-place FFT buffer
    _X = new int [_PointsNum];

    //calculate roots of unity
    _W = new int [_PointsNum/2];
    _IW = new int [_PointsNum/2];
    for ( int i = 0; i < _PointsNum/2; i++ )
    {
        int re=1;
        for(int k=0;k<i;k++)
        {
            re=modular.Multiplicate(re,_Nroot);
        }
        _W[i] = re;
        _IW[i] = modular.Invert(re);
    }

    // prepare bit-reversed mapping
    _aBitRev = new int [_PointsNum];
    int rev = 0;
    int halfPoints = _PointsNum/2;
    for (int i = 0; i < _PointsNum - 1; i++)
    {
        _aBitRev[i] = rev;
        int mask = halfPoints;
        // add 1 backwards
        while (rev >= mask)
        {
            rev -= mask; // turn off this bit
            mask >>= 1;
        }
        rev += mask;
    }
    _aBitRev [_PointsNum-1] = _PointsNum-1;
}

//
//               0   1   2   3   4   5   6   7
//  level   1
//  step    1                                     0
//  increm  2                                   W
//  j = 0        <--->   <--->   <--->   <--->   1
//  level   2
//  step    2
//  increm  4                                     0
//  j = 0        <------->       <------->      W      1
//  j = 1            <------->       <------->   2   W
//  level   3                                         2
//  step    4
//  increm  8                                     0
//  j = 0        <--------------->              W      1
//  j = 1            <--------------->           3   W      2
//  j = 2                <--------------->            3   W      3
//  j = 3                    <--------------->             3   W
//                                                              3
//

void Fft::Transform (bool invert)
{
    // step = 2 ^ (level-1)
    // increm = 2 ^ level;
    ModOperations modular(_Qm);

    int step = 1;
    for (int level = 1; level <= _logPoints; level++)
    {
        int increm = step * 2;
        for (int j = 0; j < step; j++)
        {
            // U = exp ( - 2 PI j / 2 ^ level )
            int U=0;
            if(invert)
            {
                U = _IW[((_PointsNum/2)/step)*j];
            }
            else
            {
                U =_W[((_PointsNum/2)/step)*j];
            }

            for (int i = j; i < _PointsNum; i += increm)
            {
                // in-place butterfly
                // Xnew[i]      = X[i] + U * X[i+step]
                // Xnew[i+step] = X[i] - U * X[i+step]
                // negative root T2 will be negation in modular arhimetic -U -> q-U
                int T = U;
                int T2 = U;
                T2 = modular.Negative(T2);

                T = modular.Multiplicate(T,_X [i+step]);
                T2 = modular.Multiplicate(T2,_X [i+step]);

                _X [i+step] = _X[i];
                _X [i+step] = modular.Add(_X [i+step],T2);

                _X [i] = modular.Add(_X [i],T);
            }
        }
        step *= 2;
    }
    if(invert)
    {
        for (int j = 0; j < 8; j++)
        {
            _X[j]=modular.Multiplicate(_X[j],modular.Invert(_PointsNum));
        }
    }
}

void Fft::PutAt (int i, double val)
{
    _X [_aBitRev[i]] = val;
}

