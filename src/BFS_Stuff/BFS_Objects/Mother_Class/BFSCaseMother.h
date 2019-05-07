#ifndef BFSCASE_MOTHER_H
#define BFSCASE_MOTHER_H

class BFSCaseMother {
public:
	BFSCaseMother(int id, int idParent) :
		idParentCase(idParent), idCase(id) {};
	virtual ~BFSCaseMother() {};
	
	int idCase;
	int idParentCase;
};
#endif


