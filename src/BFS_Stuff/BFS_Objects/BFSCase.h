#ifndef BFSPLUSCASE_H
#define BFSPLUSCASE_H
#include "src/BFS_Stuff/BFS_Objects/MapStat.h"
#include "src/BFS_Stuff/Heuristique/note.h"
class BFSCase {
public:

	~BFSCase() {};
	/**
	* this class represent the specific information about the BFSCase
	* it is used for retrack the path at the end of the BFS
	*/
	class BFSCaseInfo {
	public:

		BFSCaseInfo(int id, int idParent, short playerPosBeforeMove, int playerPosAfterMove)
			:id(id), idParent(idParent), playerPosBeforeMove(playerPosBeforeMove), playerPosAfterMove(playerPosAfterMove)
		{
		};

		BFSCaseInfo() {};
		//ID of the BFSCase
		~BFSCaseInfo() {};
		int id;
		//id of the BFSCase wich create the current state
		int idParent;
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
