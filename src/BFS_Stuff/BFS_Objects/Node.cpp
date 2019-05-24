#include "src/BFS_Stuff/BFS_Objects/Node.h"


Node:: Node(Chapter *chapter, std::vector<bool> accessibleZone, GameState gameState, unsigned short profondeur, NodeRetrackInfo bfsR,short nbOfBoxes) :
	 accessibleZone(accessibleZone),gameState(gameState), profondeur(profondeur), chapter(chapter), bfsRetrack(bfsR)
{
	placedBoxes.resize(nbOfBoxes, false);
}

Node::Node(Chapter * chapter, std::vector<bool> accessibleZone, GameState gameState, unsigned short profondeur, NodeRetrackInfo bfsR, std::vector<bool> placedBoxes):
	accessibleZone(accessibleZone),gameState(gameState),placedBoxes(placedBoxes),  profondeur(profondeur), chapter(chapter), bfsRetrack(bfsR)
{
}

