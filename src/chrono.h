#ifndef CHRONO_H
#define CHRONO_H
#include "ctime"
#include <iostream>
#include <chrono>
#include <ctime>

class chrono
{
    public:
        chrono();
        virtual ~chrono();
        void lancer_chrono();
         double temps_ecoule();

    protected:

    private:
        time_t deb_time;
        time_t actual_time;
        std::chrono::_V2::system_clock::time_point startc;
        std::chrono::_V2::system_clock::time_point endc;

};

#endif // CHRONO_H
