#ifndef MAZE_MAP
#define MAZE_MAP
/**
 * \file MazeMap.h
 * \brief declaration of the class MazeMap
 * \author Romain Michau
 * \version 2.1
 */
#include "maze.h"

#include <vector>
 /** \class  MazeMap
  *  \brief represent a generic vector of the size of the field DONT WORK WITH BOOL
  *
  */

template <typename T>
class MazeMap
{
private:
	std::vector<T> mapVec; /**< Vector containing data */
public:


	friend bool operator==(MazeMap<T> const& a, MazeMap<T> const& b);


	/** \brief Constructor of the class MazeMap with defaultValue
	 *
	 * \param m: Maze
	 * \param defaultValue: default value for all element of the vector
	 */
	MazeMap(const Maze  *m, T defaultValue)
	{
		mapVec.resize(m->getSize(), defaultValue);
	};

	/** \brief Overload of [], will return a reference of the value at the index wated
	 *
	 * \param index: index wanted
	 *
	 */
	inline  T& operator[] (int index)
	{
		return mapVec[index];

	};

	/** \brief Overload of [], will return a reference of the value at the index wated
	 *
	 * \param index: index wanted
	 *
	 */
	inline T& operator[] (short index)
	{
		return mapVec[index];
	};


	/** \brief Overload of [], will return a reference of the value at the index wated
	 *
	 * \param index: index wanted
	 *
	 */
	inline const T& operator[] (short index)const
	{
		return mapVec[index];
	};


	/** \brief Overload of [], will return a reference of the value at the index wated
	 *
	 * \param index: index wanted
	 *
	 */
	inline T& operator[] (unsigned index)
	{
		return mapVec[index];
	};


	/** \brief return size of the vector
	 *
	 *
	 */
	size_t size() {
		return mapVec.size();
	}





};


#endif


