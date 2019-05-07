#ifndef BFSPLUS_H
#define BFSPLUS_H
#include "src/Maze/maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include <unordered_set>
#include "src/BFS_Stuff/BFS_Objects/BFSCase.h"
class BFSPLUS
{
public:
	BFSPLUS(Maze *m);
	virtual ~BFSPLUS() ;
	std::vector<unsigned char> runBFS(unsigned &noeudvisite, int noteA, int noteB);
	void reinit();
	int showSetSize() { return marque.size(); };

private:
	std::vector<unsigned short> resolution;
	std::vector<unsigned char> chemin;
	

	Maze *m;

	struct BestBFSCase
	{
		bool operator()(BFSCase b1, BFSCase b2) const
		{
			return b1.note.get_note_total() < b2.note.get_note_total();
		}
	};

	bool hasAccessZoneChange(char offset);
	bool marqued();
	std::unordered_set<std::string> marque;

};

#endif // BFSPLUS_H
