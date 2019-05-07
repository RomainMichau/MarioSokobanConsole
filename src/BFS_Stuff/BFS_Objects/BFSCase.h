#ifndef BFSPLUSCASE_H
#define BFSPLUSCASE_H
#include "src/BFS_Stuff/BFS_Objects/MapStat.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/BFS_Stuff/BFS_Objects/Mother_Class/BFSCaseMother.h"
class BFSCase {
public:

	~BFSCase() {};
	/**
	* this class represent the specific information about the BFSCase
	* it is used for retrack the path at the end of the BFS
	*/
	class BFSCaseInfo: public BFSCaseMother {
	public:

		BFSCaseInfo(int id, int idParent, short playerPosBeforeMove, int playerPosAfterMove)
			: playerPosBeforeMove(playerPosBeforeMove), playerPosAfterMove(playerPosAfterMove),BFSCaseMother(id,idParent)
		{
		};

		BFSCaseInfo():BFSCaseMother(-1, -1) {};
		//ID of the BFSCase
		~BFSCaseInfo() {};
		
		//pos of the player before he pushed the box
		short playerPosBeforeMove;
		//pos of the player after he pushed the box
		short playerPosAfterMove;
	};

	BFSCase(unsigned nbOfBox, std::vector<bool> accessibleZone, std::vector<unsigned char> field, unsigned short profondeur, BFSCaseInfo bfsR);

	BFSCase(MapStat mapStat, std::vector<bool> accessibleZone, std::vector<unsigned char> field, unsigned short profondeur, BFSCaseInfo bfsR);
	std::vector<bool> accessibleZone;
	std::vector<unsigned char> field;
	Note note;
	unsigned short profondeur;
	MapStat mapStat;


	BFSCaseInfo  bfsRetrack;


};


#endif
