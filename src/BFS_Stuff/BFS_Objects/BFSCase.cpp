#include "src/BFS_Stuff/BFS_Objects/BFSCase.h"

BFSCase:: BFSCase(unsigned nbOfBox, std::vector<bool> accessibleZone, std::vector<unsigned char> field, unsigned short profondeur, BFSCase::BFSCaseInfo bfsR) :
	accessibleZone(accessibleZone), field(field), profondeur(profondeur), mapStat(MapStat(nbOfBox)), bfsRetrack(bfsR)
{

}

BFSCase:: BFSCase(MapStat mapStat, std::vector<bool> accessibleZone, std::vector<unsigned char> field, unsigned short profondeur, BFSCaseInfo bfsR) :
	accessibleZone(accessibleZone), field(field), profondeur(profondeur), mapStat(mapStat), bfsRetrack(bfsR)
{

}

