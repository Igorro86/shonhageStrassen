#ifndef FFT_H
#define FFT_H
#include "modoperations.h"

class Fft
{
public:
    Fft(int Points, int Qm, int Nroot);
    void Transform(bool invert);
    void PutAt (int i, double val);
    int* _X;
private:
    int* _W;
    int* _IW;
    int*_aBitRev;
    double* _aTape;
    int _PointsNum,_sqrtPoints,_logPoints;
    int _Nroot;
    int _Qm;
};

#endif // FFT_H
