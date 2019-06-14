/**
 * \file MazeMap.cpp
 * \brief implementation of the class MazeMap
 * \author Romain Michau
 * \version 2.1
 */

#include "MazeMap.h"

template<typename T>
bool operator==(MazeMap<T> const& a, MazeMap<T> const& b)
{
	
	return a.mapVec==b.mapVec;
}