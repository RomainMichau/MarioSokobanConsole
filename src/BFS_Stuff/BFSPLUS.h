#ifndef BFSPLUS_H
#define BFSPLUS_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include <unordered_set>
#include <unordered_map>
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include"src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"
class BFSPLUS
{
public:
	BFSPLUS(Maze *m,AHeuristique* heuristique);
	virtual ~BFSPLUS();
	std::vector<unsigned char> runBFS(unsigned &noeudvisite);
	unsigned showSetSize() { return marque.size(); };
	void setHeuristique(AHeuristique *newHeuristique) { heuristique = newHeuristique; };
private:
	std::vector<unsigned short> resolution;
	AHeuristique* heuristique;

	Maze *m;

	struct BestBFSCase
	{
		bool operator()(Node b1, Node b2) const
		{
			return b1.note.get_note_total() < b2.note.get_note_total();
		}
	};

	bool marqued(short acc);
	std::unordered_set<std::string>marque;
	std::unordered_map<int, std::vector< Node::NodeRetrackInfo>> savedPath;

};

#endif // BFSPLUS_H
