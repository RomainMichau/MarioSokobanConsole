/**
 * \file dynDl.h
 * \brief declaration of the class dynDl
 * \author Romain Michau
 * \version 2.1
 */

#ifndef DYN_DEADLOCK_H
#define DYN_DEADLOCK_H


#include <fstream>
#include <iomanip>
#include <unordered_set>





/** \class dynDl
 * \brief Contain the definition of a dynamique deadlocks
 *
 */
class DynDeadLocks{



private:
	const std::unordered_set<unsigned short> boxesPos;
	const unsigned short nPos;
public:
	DynDeadLocks(std::unordered_set<unsigned short> boxesPos, unsigned nPos):boxesPos(boxesPos),nPos(nPos){}
	~DynDeadLocks() {};
	friend bool operator== (const DynDeadLocks &c1, const DynDeadLocks &c2);
	size_t getHash() const;
	std::unordered_set<unsigned short> getBoxesPos() const { return boxesPos; };
	unsigned short getNPos()const { return nPos; };
};


#endif // DYN_DEADLOCK_H
