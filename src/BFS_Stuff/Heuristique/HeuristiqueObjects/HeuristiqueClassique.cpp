/**
 * \file HeuristiqueClassique.cpp
 * \brief implementation of the class HeuristiqueClassique
 * \author Romain Michau
 * \version 2.1
 */

#include "HeuristiqueClassique.h"

HeuristiqueClassique::HeuristiqueClassique(Maze * m, int coefA, int coefB)
    :AHeuristique(m, coefA,coefB,false)
{
}

HeuristiqueClassique::~HeuristiqueClassique()
{
}


void HeuristiqueClassique::calcHeuristiqueNote(Node *node, short boxPushedID, short newPos)
{


    std::vector<unsigned short> box = m->getPosBoxes();
    unsigned short distanecNoteBFS = calc_note_distance_box_bfs_multiple_box();

    note.set_note_distance_box(distanecNoteBFS);

    //[OPTIMIZER]
    //we add a penalty for each box which is not on a ideal Goal
    short note_caisse_place = 0;
    for (unsigned int i = 0; i < box.size(); i++)
    {
        short pos = box[i];
        if (!m->isSquareBoxPlaced(pos))
            note_caisse_place++;
    }
    note.set_note_caisse_place(note_caisse_place);
    note.calculTotal();
    node->note = note;
}





/**
* calcul la sommes des distance entre caisse et goal avec un bfs
*/
unsigned short HeuristiqueClassique::calc_note_distance_box_bfs_multiple_box()
{
    std::vector<unsigned short> boxes = m->getPosBoxes();
    std::vector<unsigned short> goals = m->getGoals();
    std::queue<unsigned short> queue;
    std::vector<bool> marque;
    bool goalReached = false, instant = false;
    unsigned  somme = 0;
    std::vector<unsigned short> origin;
    unsigned short   position;
    unsigned cpt = 0;
    unsigned short goalreserve = 0, bestdistance;
    std::vector<unsigned short> pluscourt;
    marque.resize(m->getField().size(), false);

    for (unsigned int box = 0; box < boxes.size(); box++)                                         ////////////Calcul note distance des box
    {
        bestdistance = 10000;
        for (unsigned int goal = 0; goal < goals.size(); goal++)
        {
            u.vider(queue);
            cpt = 0;
            if (goals[goal] == 0)
                continue;
            queue.push(boxes[box]);
            marque[boxes[box]] = true;
            goalReached = false;
            origin.push_back(9999);
            instant = false;
            //we check if the box is already on a goal
            // if yes, no need to BFS
            if (m->isSquareBoxPlaced(boxes[box]))
            {
                origin.push_back(cpt);
                goalReached = true;
                instant = true;
            }
            while (!goalReached)
            {

                position = queue.front();
                for (char dir : m->allDirection)
                {
                    short newPos = position + m->getMoveOffset(dir);

                    if (!m->isSquareWall(newPos) && !marque[newPos] && !goalReached && !m->isSquareDeadSquare(newPos))
                    {
                        if (newPos == goals[goal])
                            goalReached = true;
                        marque[newPos] = true;
                        queue.push(newPos);
                        origin.push_back(cpt);
                    }
                }
                queue.pop();
                cpt++;
            }
            goalReached = false;
            cpt = origin.size() - 1;
            int distance = 0;
            while (origin[cpt] != 9999)
            {
                distance++;
                cpt = origin[cpt];
            }
            if (instant)
            {
                distance = 0;
                instant = false;
            }
            if (distance < bestdistance)
            {
                bestdistance = distance;
                goalreserve = goal;
            }
            marque.resize(0);
            marque.resize(m->getField().size(), false);
            origin.resize(0);

        }
        goals[goalreserve] = 0;
        pluscourt.push_back(bestdistance);
    }

    std::sort(pluscourt.begin(), pluscourt.end());
    for (unsigned int i = 0; i < pluscourt.size(); i++)
    {
        somme = somme + (pluscourt[i] * (pluscourt.size() - i));
    }
    return somme;
}
