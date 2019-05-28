#ifndef BFSCASE_MOTHER_H
#define BFSCASE_MOTHER_H

class NodeCaseMother
{
public:
    NodeCaseMother(int id, int idParent)
    {
        idParentCase=idParent;
        idCase=id;
    };
    virtual ~NodeCaseMother() {};

    int idCase;
    int idParentCase;
};
#endif


