#ifndef BFSPLUSCASE_H
#define BFSPLUSCASE_H
#include "src/BFS_Stuff/BFS_Objects/MapStat.h"
class BFSCase {
public:
	
	BFSCase(int nbOfBox, std::vector<bool> accessibleZone, std::vector<unsigned char> field,  unsigned short profondeur, int classement) :
		accessibleZone(accessibleZone), field(field), profondeur(profondeur), classement(classement),mapStat(MapStat(nbOfBox))
	{

	}

	BFSCase(MapStat mapStat, std::vector<bool> accessibleZone, std::vector<unsigned char> field, unsigned short profondeur, int classement) :
		accessibleZone(accessibleZone), field(field), profondeur(profondeur), classement(classement),mapStat(mapStat)
	{

	}

	std::vector<bool> accessibleZone;
	std::vector<unsigned char> field;
	Note note;
	unsigned short profondeur;
	int classement;
	MapStat mapStat;
};

#endif