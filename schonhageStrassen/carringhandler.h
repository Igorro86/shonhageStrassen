#ifndef CARRINGHANDLER_H
#define CARRINGHANDLER_H
#define NUMBER 0
#define INDEX 1

class carringhandler
{
public:
    carringhandler(int*, int, int );
    int performCarrying();
    int* getCarriedResult();
    int getResultLength();
private:
    int getDigit(int , int );
    int* _inputarray;
    int* _carriedResult;
    int _piecelength;
    int _PointsNumber;
    int _resultLength;
};

#endif // CARRINGHANDLER_H
