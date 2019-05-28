#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiquePivot.h"
#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiqueClassique.h"
#include "FHeuristique.h"


FHeuristique::FHeuristique(Maze *m, int coefA, int coefB) :m(m), coefA(coefA), coefB(coefB) {}

FHeuristique::~FHeuristique()
{
}

AHeuristique * FHeuristique::getInstance()
{
	// calculatiing and setting frequentationMap
	std::vector<short> freqMap = calcFrequentationSquares();

	// get an estimation of the distance beetween all the squares and goals
	std::vector<short> distanceMap = calcMapDistanceFromNearestGoals();

	// with the distance map and the previously calculated frequentation map, we calculate the piovtPoint
	short posPivotPointPos = calcPivotPointPos(distanceMap, freqMap);
	std::unordered_map<short, short> tunnelMap=tunnelDetector();
	if (checkIfPivotLevel(posPivotPointPos))
		return new HeuristiquePivot(m, coefA, coefB, HeuristiquePivot::GameStat(freqMap, posPivotPointPos, u.getDistMapOfSquare(m, posPivotPointPos), tunnelMap));
	else
		return new HeuristiqueClassique(m, coefA, coefB);
}

HeuristiqueClassique * FHeuristique::getClassicalHeuritique()
{
	return new HeuristiqueClassique(m, coefA, coefB);
}




/**
* for each square calculate the distance with the nearest goal
*/
std::vector<short> FHeuristique::calcMapDistanceFromNearestGoals()
{
	std::vector<short> res;
	std::vector<unsigned char> field = m->getField();
	for (unsigned square = 0; square < m->getField().size(); square++)
	{
		if (m->isSquareWall(square) || m->isSquareDeadSquare(square))
		{
			res.push_back(-1);
			continue;
		}
		unsigned size = u.getPathSquareToGoalBM(m, square).size();
		res.push_back(size);
	}
	return res;
}


/**
* return a vector of the size of the field
* for each box we calculate the path to go to the goal
* each square is represented by the number of box wich have run on it
*
* [WARNING] Is not 100% trustable, so in case of failure, you must try the other type of heurtistique
*/
std::vector<short> FHeuristique::calcFrequentationSquares()
{
	std::vector<short> res;
	res.resize(m->getField().size(), 0);
	std::vector<unsigned char> field = m->getField();
	for (int box : m->getPosBoxes())
	{

		std::deque<short> path = u.getPathSquareToGoalBM(m, box);

		//the last element is the goal himself, so we remove him
		if (path.size() > 0)
		{
			path.pop_back();
		}
		for (short sq : path)
		{
			res[sq]++;
		}
	}
	return res;
}



/**
* return the pivot point of mapStat
* definit of pivotPoint: the point with the most frequentation.
* if there is many point with the same max frequentation, then the farest from the goal win
* @see MapStat
*	-a distMap defined (with method calcMapDistanceFromIdealGoal or calcMapDistanceFromNearestGoals)
*
*@param: distMap: represent the distance from all the saure to the goal
*/
short FHeuristique::calcPivotPointPos(std::vector<short> distMap, std::vector<short> freqMap)
{

	short pivotPoint = -1;
	int mostFreqValue = 0;
	int longestDistance = 0;
	for (unsigned i = 0; i < freqMap.size(); i++)
	{
		short dist = distMap[i];
		short freq = freqMap[i];
		if (freq > mostFreqValue)

		{
			mostFreqValue = freq;
			longestDistance = dist;
			pivotPoint = i;
		}
		else if (freq == mostFreqValue && dist > longestDistance)
		{
			longestDistance = dist;
			pivotPoint = i;
		}
	}
	return pivotPoint;
}
/**
* detect the presence of tunnel in the maze
* tunnel is a path compose of a least two tunnelSquare
* tunnelSquare: square which have only 2 walkable adjacent square. Each of this square must be in oppossite direction
* return a map:
* entryTunnelSquare => exitTunnelSquare
*/
std::unordered_map<short, short> FHeuristique::tunnelDetector()
{
	std::unordered_map<short, short> res;
	//on regarde toute les cases du jeu
	for (short square = 0; square < m->getSize(); square++) {
		if (square == 103)
			std::cout << 139;
		if (!m->isSquareWalkable(square) || m->isSquareGoal(square)) {
			continue;
		}
		//on compte le nb de direction faisable depuis cette case
		std::vector<char> possibleDir = m->getPossibleDirFromSquare(square);

		//si 2 direction sont possible
		if (possibleDir.size() == 2) {
			char dir0 = possibleDir[0];
			char dir1 = possibleDir[1];
			short offsetDir0 = m->getMoveOffset(dir0);
			short offsetDir1 = m->getMoveOffset(dir1);
			short neigbourh0 = square + offsetDir0;
			short neigbourh1 = square + offsetDir1;
			std::vector<char> dirNeigbourh0 = m->getPossibleDirFromSquare(neigbourh0);
			std::vector<char> dirNeigbourh1 = m->getPossibleDirFromSquare(neigbourh1);
			//the two dir must be opposite
			if (offsetDir0 != -offsetDir1)
				continue;

			/**
			* only the enter and the end is intersting for us, so we check than one neigbourg is not a TunnelSquare, and than the other is
			*/


			char dirToTunnelNeigbourh;

			if (dirNeigbourh0 == possibleDir && dirNeigbourh1.size() > 2) {
				dirToTunnelNeigbourh = dir0;
			}
			else if (dirNeigbourh1 == possibleDir && dirNeigbourh0.size() > 2) {
				dirToTunnelNeigbourh = dir1;
			}
			else {
				continue;
			}

			short nextSquare = square;
			std::vector<char> newPossibleDir = possibleDir;
			while (newPossibleDir == possibleDir) {
				nextSquare += m->getMoveOffset(dirToTunnelNeigbourh);
				newPossibleDir = m->getPossibleDirFromSquare(nextSquare);
			}
			res[square] = nextSquare - m->getMoveOffset(dirToTunnelNeigbourh);

		}
	}
	return res;
}
/**
* return true if the level sent in parameters is indeed a pivot level
* method to verify;
*	for each box we checks that it need to pass throug the pivot to reach each goal
*	1 exception:
*		if the box if nearer from the goal than the pivot, then its
*/
bool FHeuristique::checkIfPivotLevel(short pivotPos)
{

	for (short box : m->getPosBoxes())
	{
		//	for(short box=0;box<m->getSize();box++){
		for (short goal : m->getGoals())
		{
			short distPivotGoal = u.getPathSquareToSquareBM(m, pivotPos, goal).size();

			std::deque<short> path = u.getPathSquareToSquareBM(m, box, goal);
			if (path.size() < distPivotGoal)
				continue;
			bool passByPivot = false;
			for (short squarePath : path)
			{
				if (squarePath == pivotPos)
				{
					passByPivot = true;
					break;
				}
			}
			if (!passByPivot)
				return false;
		}
	}
	return true;
}
