#ifndef MODOPERATIONS_H
#define MODOPERATIONS_H

class ModOperations
{
public:
    ModOperations(int q);
    int Multiplicate(int x,int y);
    int Add(int x,int y);
    int Invert(int x);
    int Negative(int x);
 private:
    int _q;
};

#endif // MODOPERATIONS_H
