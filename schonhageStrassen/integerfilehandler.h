#ifndef INTEGERHANDLER_H
#define INTEGERHANDLER_H
#include <string>
#include <vector>
#include "integerfile.h"

class integerfilehandler
{
public:
    integerfilehandler(std::string path);
    void initialize();
    void calculatePieceLength();
    std::vector < int > getPointsSetVect();
private:
    std::string _path;
    int _length, _piecelength;
    integerfile* loadedfile;
};

#endif // INTEGERHANDLER_H
