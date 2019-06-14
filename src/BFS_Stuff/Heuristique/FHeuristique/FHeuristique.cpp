/**
 * \file FHeurisitique.cpp
 * \brief implementation of the class FHeurisitique
 * \author Romain Michau
 * \version 2.1
 */

#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiquePivot.h"
#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiqueClassique.h"
#include "FHeuristique.h"


FHeuristique::FHeuristique(Maze *m, short coefA, short coefB) :m(m), coefA(coefA), coefB(coefB) {}

FHeuristique::~FHeuristique()
{
}

AHeuristique * FHeuristique::getInstance()
{
    // calculatiing and setting frequentationMap
    MazeMap<short> freqMap = calcFrequentationSquares(); 

    // get an estimation of the distance beetween all the squares and goals
	MazeMap<short> distanceMap = calcMapDistanceFromNearestGoals();

    // with the distance map and the previously calculated frequentation map, we calculate the piovtPoint
    short posPivotPointPos = calcPivotPointPos(distanceMap, freqMap);
    std::unordered_map<short, short> tunnelMap=tunnelDetector();
    if (checkIfPivotLevel(posPivotPointPos))
        return new HeuristiquePivot(m, coefA, coefB, HeuristiquePivot::GameStatistique(freqMap, posPivotPointPos, u.getDistMapOfSquare(m, posPivotPointPos), tunnelMap));
    else
        return new HeuristiqueClassique(m, coefA, coefB);
}

HeuristiqueClassique * FHeuristique::getClassicalHeuritique()
{
    return new HeuristiqueClassique(m, coefA, coefB);
}


MazeMap<short> FHeuristique::calcMapDistanceFromNearestGoals()
{
	MazeMap<short> res(m,-1);
    std::vector<unsigned char> field = m->getField();
    for (unsigned square = 0; square < m->getField().size(); square++)
    {
        if (m->isSquareWall(square) || m->isSquareDeadSquare(square))
        {
			res[square] = -1;
            continue;
        }
        unsigned size = u.getPathSquareToGoalBM(m, square).size();
		res[square] = size;

    }
    return res;
}


MazeMap<short> FHeuristique::calcFrequentationSquares()
{
	MazeMap<short> res(m,0);
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


short FHeuristique::calcPivotPointPos(MazeMap<short> distMap, MazeMap<short> freqMap)
{

    short pivotPointPos = -1;
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
            pivotPointPos = i;
        }
        else if (freq == mostFreqValue && dist > longestDistance)
        {
            longestDistance = dist;
            pivotPointPos = i;
        }
    }
    return pivotPointPos;
}

std::unordered_map<short, short> FHeuristique::tunnelDetector()
{
    std::unordered_map<short, short> res;
    //on regarde toute les cases du jeu
    for (short square = 0; square < m->getSize(); square++)
    {
        if (square == 103)
            std::cout << 139;
        if (!m->isSquareWalkable(square) || m->isSquareGoal(square))
        {
            continue;
        }
        //on compte le nb de direction faisable depuis cette case
        std::vector<char> possibleDir = m->getPossibleDirFromSquareIBox(square);

        //si 2 direction sont possible
        if (possibleDir.size() == 2)
        {
            char dir0 = possibleDir[0];
            char dir1 = possibleDir[1];
            short offsetDir0 = m->getMoveOffset(dir0);
            short offsetDir1 = m->getMoveOffset(dir1);
            short neigbourh0 = square + offsetDir0;
            short neigbourh1 = square + offsetDir1;
            std::vector<char> dirNeigbourh0 = m->getPossibleDirFromSquareIBox(neigbourh0);
            std::vector<char> dirNeigbourh1 = m->getPossibleDirFromSquareIBox(neigbourh1);
            //the two dir must be opposite
            if (offsetDir0 != -offsetDir1)
                continue;

            /**
            * only the enter and the end is intersting for us, so we check than one neigbourg is not a TunnelSquare, and than the other is
            */


            char dirToTunnelNeigbourh;

            if (dirNeigbourh0 == possibleDir && dirNeigbourh1.size() > 2)
            {
                dirToTunnelNeigbourh = dir0;
            }
            else if (dirNeigbourh1 == possibleDir && dirNeigbourh0.size() > 2)
            {
                dirToTunnelNeigbourh = dir1;
            }
            else
            {
                continue;
            }

            short nextSquare = square;
            std::vector<char> newPossibleDir = possibleDir;
            while (newPossibleDir == possibleDir)
            {
                nextSquare += m->getMoveOffset(dirToTunnelNeigbourh);
                newPossibleDir = m->getPossibleDirFromSquareIBox(nextSquare);
            }
            res[square] = nextSquare - m->getMoveOffset(dirToTunnelNeigbourh);

        }
    }
    return res;
}

bool FHeuristique::checkIfPivotLevel(short pivotPos)
{

    for (short box : m->getPosBoxes())
    {
        //	for(short box=0;box<m->getSize();box++){
        for (short goal : m->getGoals())
        {
           unsigned short distPivotGoal = u.getPathSquareToSquareBM(m, pivotPos, goal).size();

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
