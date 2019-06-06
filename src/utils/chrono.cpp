/**
 * \file chrono.cpp
 * \brief implementation of the class chrono
 * \author romain michau
 * \version 2.1
 */
#include "src/utils/Chrono.h"
#include <chrono>
#include <ctime>

Chrono::Chrono()
{
    //ctor
}

Chrono::~Chrono()
{
    //dtor
}



void Chrono::lancer_chrono()
{
    startc = std::chrono::system_clock::now();
}


double Chrono::temps_ecoule()
{
    endc = std::chrono::system_clock::now();
    std::chrono::duration<double> temp=endc-startc;
    return temp.count();


}
