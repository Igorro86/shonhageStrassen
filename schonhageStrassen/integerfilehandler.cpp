#include "integerfilehandler.h"
#include "integerfile.h"
#include "math.h"
#include <vector>
#include <string>

integerfilehandler::integerfilehandler(std::string path)
{
    _path=path;
    initialize();
    calculatePieceLength();
}

void integerfilehandler::initialize()
{
    loadedfile = new integerfile;
    loadedfile->open(_path.c_str());
    if(  loadedfile->good() == false )
    {
        throw std::string("nie ma dostepu do pliku\n");
    }
    _length=  loadedfile->getlength()-1;
    printf("dlugosc pliku %d \n",_length);
}

void integerfilehandler::calculatePieceLength()
{
    /* the way the pieces length are calculated in the book "The Design and Analysis of Computer Algorithms" */
    int k=0,n=0;
    while(n<_length)
    {
        k++;
        /* number of bits */
        n=pow(2,k);
    }
    int b= k&0b1 ?  pow(2,(k/2)) : pow(2,((k-1)/2));

    /* calculate lenght od block */
    _piecelength=n/b;

    printf("dlugosc kawalka %d \n",_piecelength);
}

std::vector < int > integerfilehandler::getPointsSetVect()
{
    std::vector < int > integervect;

    char * buffer = new char [_piecelength];

    while(loadedfile->tellg()<_length && loadedfile->tellg()!=-1)
    {
        loadedfile->read(buffer,_piecelength);
        int loadednumber=0;
        for(int i=0; i<_piecelength;i++)
        {
            int loadeddigit=int(buffer[i]-'0');
            loadeddigit >= 0 ? loadednumber+=loadeddigit*(int)pow(10,_piecelength-i-1) : loadednumber+=0;
        }
        integervect.insert(integervect.begin(),loadednumber);
    }

    delete[] buffer;
    return integervect;
}


int integerfilehandler::getIntegerLength()
{
    return _length;
}
