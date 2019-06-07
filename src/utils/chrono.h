#ifndef CHRONO_H
#define CHRONO_H
/**
 * \file chrono.h
 * \brief declaration of the class chrono
 * \author Romain Michau
 * \version 2.1
 */
#include <iostream>
#include <chrono>
#include <ctime>

#include "ctime"

/** \class Chrono
 *  \brief the class in charge of measuring time in the game
 */
class Chrono
{

private:

    std::chrono::system_clock::time_point startc;/**< Time at the begining */
    std::chrono::system_clock::time_point endc; /**< Time at the end */
public:

    /** \brief Constructor of the class Chrono
     *
     *
     */
    Chrono();
    /** \brief Destructor of the class Chrono
     *
     */
    virtual  ~Chrono();
    /** \brief Launch chronometer
     *
     * \return void
     *
     */
    void lancer_chrono();

    /** \brief
     *
     * \return time
     *
     */
    double temps_ecoule();





};

#endif // CHRONO_H
