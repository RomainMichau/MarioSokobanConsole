#include "src/BFS_Stuff/BFS_Objects/Node.h"


Node:: Node(Chapter *chapter, std::vector<bool> accessibleZone, short normalisePos, std::vector<unsigned char> field, unsigned short profondeur, NodeRetrackInfo bfsR,short nbOfBoxes) :
	accessibleZone(accessibleZone), field(field), normalisePos(normalisePos), profondeur(profondeur), chapter(chapter), bfsRetrack(bfsR)
{
	placedBoxes.resize(nbOfBoxes, false);
}

Node::Node(Chapter * chapter, std::vector<bool> accessibleZone, short normalisePos, std::vector<unsigned char> field, unsigned short profondeur, NodeRetrackInfo bfsR, std::vector<bool> placedBoxes):
	accessibleZone(accessibleZone), normalisePos(normalisePos), field(field), profondeur(profondeur), chapter(chapter), bfsRetrack(bfsR),placedBoxes(placedBoxes)

{
}

