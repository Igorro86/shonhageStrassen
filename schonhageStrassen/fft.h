#ifndef FFT_H
#define FFT_H
#include "modoperations.h"
#include <vector>
#include "modoperations.h"

class Fft
{
public:
    Fft(int Points, int Qm, int Nroot);
    void Transform(bool invert);
    void PutVector (std::vector<int> number);
    void PutTransformResult (Fft transform);
    void MultiplicateAndAssign (Fft transform);
    int* _X;
private:
    void PutAt (int i, double val);
    int* _W;
    int* _IW;
    int*_aBitRev;
    double* _aTape;
    int _PointsNum,_sqrtPoints,_logPoints;
    int _Nroot;
    int _Qm;
    ModOperations modular;
};

#endif // FFT_H
