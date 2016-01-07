#include "integerfile.h"
#include <fstream>
#include <string>
#include <fstream>

integerfile::integerfile()
{
}

int integerfile::readdigits(int number)
{
    int result=0;
    return result;
}

int integerfile::getlength()
{
    this->seekg (0, this->end);
    int length = this->tellg();
    this->seekg (0, this->beg);
    return length;
}
