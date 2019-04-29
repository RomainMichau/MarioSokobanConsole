#ifndef BFSPLUS_H
#define BFSPLUS_H
#include "maze.h"
#include "stock_field.h"
#include "note.h"
class BFSPLUS
{
public:
	BFSPLUS();
	virtual ~BFSPLUS();
	std::vector<unsigned char> bfs_malin(Maze m, bool dynDeadLocks, int &noeudvisite, int noteA, int noteB, int plafond);
	void reinit();
	class BFSPLUSCase {
	public:
		BFSPLUSCase(std::vector<bool> accessibleZone, std::vector<unsigned char> field,Note note,unsigned short profondeur,int classement) :
		accessibleZone(accessibleZone),field(field),note(note),profondeur(profondeur),classement(classement)
		{

		}
		std::vector<bool> accessibleZone;
		std::vector<unsigned char> field;
		Note note;
		unsigned short profondeur;
		int classement;
	};

private:
	std::vector<unsigned short> resolution;
	std::vector<unsigned char> chemin;
	stock_field marque_field;
	std::vector<unsigned short>origin;  //je fais un tableau ou j'alterne la postion precedente et le mouvement
										// necessaire pour arriver a cette nouvelle etat
	void invert(std::vector<unsigned short> &vec);
	bool compare(std::vector<unsigned char> vec);



	struct BestBFSCase
	{
		bool operator()( BFSPLUSCase b1,  BFSPLUSCase b2) const
		{
			return b1.note.get_note_total() < b2.note.get_note_total();
		}
	};

};

#endif // BFSPLUS_H
