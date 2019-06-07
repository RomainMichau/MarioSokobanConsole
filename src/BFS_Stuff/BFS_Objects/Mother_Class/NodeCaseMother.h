#ifndef BFSCASE_MOTHER_H
#define BFSCASE_MOTHER_H
/**
 * \file NodeCaseMother.h
 * \brief declaration of the class NodeCaseMother
 * \author Romain Michau
 * \version 2.1
 */


/*! \class NodeCaseMother
* \brief class used for the Node class
*
* used for the Node class.
* Contains information for retracking the node at the end of the BFS
*/
class NodeCaseMother
{
public:
    /*!
     *  \brief Constructor
     *
     *  Constructor of the class NodeCaseMother
     *
     *  \param id : id of the Node
     *  \param idParent
     */
    NodeCaseMother(int id, int idParent)
    {
        idParentCase = idParent;
        idCase = id;
    };
    virtual ~NodeCaseMother() {};

    int idCase;
    int idParentCase;
};
#endif


