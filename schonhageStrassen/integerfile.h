#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <string>
#include <fstream>

class integerfile
        : public std::fstream
{
public:
    integerfile();
    int readdigits(int number);
    int getlength();
private:

};

#endif // FILEHANDLER_H
