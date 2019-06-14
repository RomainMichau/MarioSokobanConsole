/**
 * \file dynDL.cpp
 * \brief implementation of the class dynDl
 * \author Romain Michau
 * \version 2.1
 */

#include "DynDeadLocks.h"
#include <utility>


size_t DynDeadLocks::getHash() const
{
	std::hash<unsigned short> hasher;
	size_t seed = 0;

	for (int i : this->boxesPos)
	{
		seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	seed ^= hasher(this->nPos) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	return seed;
}

bool operator == (const DynDeadLocks &p1, const DynDeadLocks &p2)

{
	return p1.boxesPos == p2.boxesPos && p1.nPos == p2.nPos;
}
