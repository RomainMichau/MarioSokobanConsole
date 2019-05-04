#include "src/utils/chrono.h"
#include <chrono>
#include <ctime>

chrono::chrono()
{
    //ctor
}

chrono::~chrono()
{
    //dtor
}



void chrono::lancer_chrono()
{
    startc = std::chrono::system_clock::now();
}


double chrono::temps_ecoule()
{
    endc = std::chrono::system_clock::now();
    std::chrono::duration<double> temp=endc-startc;
    return temp.count();


}
