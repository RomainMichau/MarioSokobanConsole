#include "src/utils/util.h"
#include "src/Maze/Maze.h"
#include "src/utils/Console.h"
#include "src/utils/Coord.h"
#include "src/BFS_Stuff/BFS_Objects/Mother_Class/NodeCaseMother.h"
#include "src/Maze/GameState.h"
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <unordered_set>

Util::Util()
{
	//ctor
}

Util::~Util()
{
	//dtor
}

/*
* empty a queue
*/
void Util::vider(std::queue<unsigned short> &t)
{
	while (!t.empty())
		t.pop();

}

/*
* empty a queue
*/
void Util::vider(std::queue<std::vector<unsigned char>> &t)
{
	while (!t.empty())
		t.pop();

}

/*
* empty a queue
*/
void Util::vider(std::queue< BFSCase_relier_point> &queue)
{
	std::queue<BFSCase_relier_point> empty;
	std::swap(queue, empty);
}

/**
* fait un mini BFS pour localiser la presence d'un aglomerat de box autour de celle envoyer en parametre
*/
std::unordered_set<unsigned short> Util::detectAgglomerateOFBoxes(Maze *m, short initBox)
{
	std::vector<bool> marque;
	marque.resize(m->getSize(), false);
	std::unordered_set< unsigned short> res;
	res.insert(initBox);
	std::queue<short> queue;
	queue.push(initBox);
	marque[initBox] = true;
	while (!queue.empty()) {
		short curPos = queue.front();
		queue.pop();
		for (char dir : m->allDirection) {
			short offset = m->getMoveOffset(dir);
			short newPos = curPos + offset;
			if (!marque[newPos] && m->isSquareBox(newPos)) {
				marque[newPos] = true;
				queue.push(newPos);
				res.insert(newPos);
			}
		}
	}
	return res;
}




/**
* Calculate all the accesble square in the field with BFS
* (endless bfs which end the the queue is empty)
*/
std::vector<bool> Util::calcZoneAccessible(const Maze  *m, short &normPos)
{
	normPos = m->getSize();
	std::vector<bool> marque;
	marque.resize(m->getField().size(), false);
	std::queue<unsigned short> file;
	short position = m->getPosPlayer();
	marque[position] = true;
	file.push(position);

	while (!file.empty())
	{
		position = file.front();
		for (char dir : m->allDirection)
		{
			short offset = m->getMoveOffset(dir);
			short newPos = position + offset;
			if (m->isSquareWalkable(newPos) && !marque[newPos])
			{
				file.push(newPos);
				marque[newPos] = true;
				if (newPos < normPos)
					normPos = newPos;
			}
		}
		file.pop();
	}
	return marque;
}



/**
* this method will receive a vector of succesive position.
* it will give in return a vector of move directctive to follow in passed through each position of the vector
*/
std::vector<unsigned short> Util::relier_point(Maze  m, std::vector <unsigned short> positions)
{
	std::cout << std::endl << "BFS DONE, linking points..." << std::endl;
	std::vector<unsigned short> resolution, temp;
	std::queue< BFSCase_relier_point> queue;
	std::vector <unsigned char> field = m.getField();
	unsigned short currentPosition = positions[0];
	bool win;
	for (unsigned int i = 0; i < positions.size() - 1; i++)
	{
		win = false;
		this->vider(queue);
		queue.push(BFSCase_relier_point(m.getField(), positions[i], 0, -1, -1));
		marque.push_back(BFSCase_relier_point(m.getField(), positions[i], 0, -1, -1));

		while (!win)
		{
			BFSCase_relier_point currentCase = queue.front();
			currentPosition = currentCase.position;
			field = currentCase.field;
			m.change_etat_jeu(field, currentPosition);
			if (currentPosition == positions[i + 1])
				win = true;
			for (char dir : m.allDirection)
			{
				short offset = m.getMoveOffset(dir);
				short newPosition = currentPosition + offset;
				if (!m.isSquareWall(newPosition) && !win)
				{
					if (!m.isSquareBox(newPosition) || (newPosition == positions[i + 1]))
					{
						m.updatePlayer(dir);
						BFSCase_relier_point newCase(m.getField(), m.getPosPlayer(), (int)marque.size(), currentCase.idCase, dir);

						if (!compare(newCase))
						{
							if (m.getPosPlayer() == positions[i + 1])
							{
								win = true;
							}
							queue.push(newCase);
							marque.push_back(newCase);
						}
					}
					if (!win)
						m.change_etat_jeu(field, currentPosition);
				}
			}
			queue.pop();
		}
		temp.resize(0);
		BFSCase_relier_point currentCase = marque.back();
		while (currentCase.idCase != 0)
		{
			temp.push_back(currentCase.mov);
			currentCase = marque[currentCase.idParentCase];
		}
		std::reverse(temp.begin(), temp.end());
		for (unsigned int h = 0; h < temp.size(); h++)
			resolution.push_back(temp[h]);
	}

	return resolution;


}


/*
*return true if th tstCase is alrea	dy marqueds
*/
bool Util::compare(BFSCase_relier_point tstCase)
{
	for (std::vector<BFSCase_relier_point>::iterator ccase = marque.begin(); ccase != marque.end(); ++ccase)
	{
		if (ccase->field == tstCase.field&&ccase->position == tstCase.position)
		{
			return true;
		}
	}
	return false;
}


/**
 * Permet de choisir un niveau a jouer. Renvoit le chemin du niveau en String
 * @return renvoit le chemin du niveau
 */
std::string Util::choose_level()
{
	std::string path;
	unsigned short a, b;
	float c;

	std::ostringstream oss;
	Console::getInstance()->setColor(_COLOR_RED);
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "choose a level:";
	Console::getInstance()->setColor(_COLOR_YELLOW);
	std::cout << std::endl << "easy 1: 11" << std::endl << "easy 2: 12" << std::endl << "easy 3: 13" << std::endl << "easy 4: 14" << std::endl << "easy 5: 15" << std::endl;
	std::cout << "easy 6: 16" << std::endl << "easy 7: 17" << std::endl << "easy 8: 18" << std::endl << "easy 9: 19" << std::endl << "easy 10: 110" << std::endl << std::endl;
	Console::getInstance()->setColor(_COLOR_BLUE);
	std::cout << "medium 1: 21" << std::endl << "medium 2: 22" << std::endl << "medium 3: 23" << std::endl << std::endl;
	Console::getInstance()->setColor(_COLOR_GREEN);
	std::cout << "hard 1: 31" << std::endl << "hard 2: 32" << std::endl << "hard 3: 33" << std::endl << std::endl;
	Console::getInstance()->setColor(_COLOR_PURPLE);
	std::cout << "test 1: 41" << std::endl << "test 2: 42" << std::endl << "test 3: 43" << std::endl << std::endl;
	Console::getInstance()->setColor(_COLOR_WHITE);


	std::cout << "level: ";
	std::cin >> a;
	std::cout << std::endl << std::endl;
	path = "C:/levels/";
	b = a / 10;
	c = a;
	c = c / 10;
	if (b == 1)
	{
		path = path + "easy/easy_";
	}
	if (b == 2)
	{
		path = path + "medium/medium_";
	}
	if (b == 3)
	{
		path = path + "hard/hard_";
	}
	if (b == 4)
	{

		path = path + "test/test_";

	}

	if (a != 110)
	{
		c = round(10 * (c - floor(c)));
		oss << c;
		path = path + oss.str();
	}

	if (a == 110)
		path = "./levels/easy_10";
	path = path + ".dat";
	std::cout << path << std::endl;
	std::ifstream fichier(path.c_str());
	return path;
}

/**
	* Return the path beetween the square  send in parameters and the nearest goal.
	* If no possible path, return empty vector
	* path is the id of all the square.
	*calculating in "pushingBox movement"
	*@param:squareID number of the square in the field
	*@return if the square can not reached a goal, return empty vector. If it is a wall or a goal return empty vector
	* else will return a path of all the square ID to reach the goal

*/
std::deque<short> Util::getPathSquareToGoalBM(const Maze  *m, short square)
{
	std::deque<short> res;

	/**
	* Si il ne s'agit pas d'une case marquable comme deadSquare
	*/
	if (m->isSquareGoal(square) || m->isSquareWall(square) || m->isSquareDeadSquare(square))
	{
		return res;
	}
	std::queue< unsigned short> queue;
	std::vector<bool> marque;

	//map to retrace the path to the goal
	//  square=>previous_square
	std::unordered_map<short, short> origin;
	marque.resize(m->getField().size(), false);
	queue.push(square);
	marque[square] = true;
	bool goal_reached = false;
	short lastPos;
	while (!queue.empty())
	{
		unsigned char pos = queue.front();
		queue.pop();
		for (char dir : m->allDirection)
		{
			short offset = m->getMoveOffset(dir);
			short newPos = pos + offset;
			short playerPos = pos - offset;
			//si on sort du terrain, on abbandone
			if (playerPos < 0 || newPos >= (short)m->getSize() || playerPos >= (short)m->getSize() || newPos < 0)
				continue;
			//si la nouvelle case de la box est marqué, ou deadSq ou mur on abbandone
			if (marque[newPos] || !(m->isSquareWalkable(newPos) || m->isSquareBox(newPos)) || m->isSquareDeadSquare(newPos))
				continue;
			//Si la player pos est innaccesilbe on abbandonne
			if (!(m->isSquareWalkable(playerPos) || m->isSquareBox(playerPos)))
			{
				continue;
			}
			origin.insert({ newPos, pos });
			queue.push(newPos);
			marque[newPos] = true;
			lastPos = newPos;
			if (m->isSquareGoal(newPos))
			{
				goal_reached = true;
				break;
			}
		}
		if (goal_reached)
		{
			break;
		}
	}

	while (goal_reached&&lastPos != square)
	{
		res.push_front(lastPos);
		lastPos = origin[lastPos];
	}
	return res;
}

/**
	* Return the path beetween the fromSquare  send in parameters and the toSquare .
	* If no possible path, return empty vector
	* path is the id of all the square.
	*@param:fromSquare number of the square in the field
	*@return if the square can not reached a goal, return empty vector. If it is a wall or a goal return empty vector
	* else will return a path of all the square ID to reach the goal
	*calculating in "pushingBox movement"

*/
std::deque<short> Util::getPathSquareToSquareBM(const Maze  *m, short fromSquare, short toSquare)
{
	std::deque<short> res;
	short square = fromSquare;
	/**
	* Si il ne s'agit pas d'une case marquable comme deadSquare
	*/
	if (m->isSquareWall(square) || m->isSquareDeadSquare(square))
	{
		return res;
	}
	std::queue< unsigned short> queue;
	std::vector<bool> marque;

	//map to retrace the path to the goal
	//  square=>previous_square
	std::unordered_map<short, short> origin;
	marque.resize(m->getField().size(), false);
	queue.push(square);
	marque[square] = true;
	bool goal_reached = false;
	short lastPos;
	while (!queue.empty())
	{
		unsigned char pos = queue.front();
		queue.pop();
		for (char dir : m->allDirection)
		{
			short offset = m->getMoveOffset(dir);
			short newPos = pos + offset;
			short playerPos = pos - offset;
			//si on sort du terrain, on abbandone
			if (playerPos < 0 || newPos >= (short)m->getSize() || playerPos >= (short)m->getSize() || newPos < 0)
				continue;
			//si la nouvelle case de la box est marqué, ou deadSq ou mur on abbandone
			if (marque[newPos] || !(m->isSquareWalkable(newPos) || m->isSquareBox(newPos)) || m->isSquareDeadSquare(newPos))
				continue;
			//Si la player pos est innaccesilbe on abbandonne
			if (!(m->isSquareWalkable(playerPos) || m->isSquareBox(playerPos)))
			{
				continue;
			}
			origin.insert({ newPos, pos });
			queue.push(newPos);
			marque[newPos] = true;
			lastPos = newPos;
			if (newPos == toSquare)
			{
				goal_reached = true;
				break;
			}
		}
		if (goal_reached)
		{
			break;
		}
	}

	while (goal_reached&&lastPos != square)
	{
		res.push_front(lastPos);
		lastPos = origin[lastPos];
	}
	return res;
}



/**
	* Return the path beetween the fromSquare  send in parameters and the toSquare .
	* If no possible path, return empty vector
	* path is the id of all the square.
	*@param:fromSquare number of the square in the field
	*@return if the square can not reached a goal, return empty vector. If it is a wall or a goal return empty vector
	* else will return a path of all the square ID to reach the goal
	*calculating in "moving player movement"
*/
std::deque<short> Util::getPathSquareToSquarePM(const Maze  *m, short fromSquare, short toSquare)
{
	std::deque<short> res;
	short square = fromSquare;
	/**
	* Si il ne s'agit pas d'une case marquable comme deadSquare
	*/
	if (m->isSquareWall(square))
	{
		return res;
	}
	std::queue< unsigned short> queue;
	std::vector<bool> marque;

	//map to retrace the path to the goal
	//  square=>previous_square
	std::unordered_map<short, short> origin;
	marque.resize(m->getField().size(), false);
	queue.push(square);
	marque[square] = true;
	bool goal_reached = false;
	short lastPos;
	while (!queue.empty())
	{
		unsigned char pos = queue.front();
		queue.pop();
		for (char dir : m->allDirection)
		{
			short offset = m->getMoveOffset(dir);
			short newPos = pos + offset;
			//si on sort du terrain, on abbandone
			if (newPos < 0 || newPos >= (short)m->getSize())
				continue;
			//si la nouvelle case de la box est marqué, ou pas walkable ou mur on abbandone ou un deadsquare
			if (marque[newPos] || !(m->isSquareWalkable(newPos) || m->isSquareBox(newPos)) || m->isSquareDeadSquare(newPos))
				continue;

			origin.insert({ newPos, pos });
			queue.push(newPos);
			marque[newPos] = true;
			lastPos = newPos;
			if (newPos == toSquare)
			{
				goal_reached = true;
				break;
			}
		}
		if (goal_reached)
		{
			break;
		}
	}

	while (goal_reached&&lastPos != square)
	{
		res.push_front(lastPos);
		lastPos = origin[lastPos];
	}
	return res;
}
/**
* return the dist map to go to this.
* calcuate in ignoring box
*  calcuate in "pushingBox movement"
*/
std::vector<short> Util::getDistMapOfSquare(const Maze  *m, short toSquare)
{
	std::vector<short> res;
	std::vector<unsigned char> field = m->getField();
	for (unsigned square = 0; square < m->getField().size(); square++)
	{
		if (square == toSquare)
		{
			res.push_back(0);
			continue;
		}
		if (m->isSquareWall(square) || m->isSquareDeadSquare(square))
		{
			res.push_back(-1);
			continue;
		}
		unsigned size = this->getPathSquareToSquareBM(m, square, toSquare).size();
		size = size == 0 ? -1 : size;
		res.push_back(size);
	}
	return res;
}


void Util::dispVector(const Maze  *m, std::vector<short> vec)
{
	int i = 1;
	for (short sq : vec)
	{
		std::cout << sq << " ";
		if (sq >= 0 && sq < 10)
		{
			std::cout << " ";
		}
		if (i % (m->getCol()) == 0 && i > 0)
			std::cout << std::endl;
		i++;
	}
}


void Util::dispVector(const Maze  *m, std::vector<bool> vec)
{
	int i = 1;
	for (short sq : vec)
	{
		if (sq)
		{
			Console::getInstance()->setColor(_COLOR_GREEN);
		}
		else
		{
			Console::getInstance()->setColor(_COLOR_RED);

		}
		std::cout << "  " << sq;

		if (i % (m->getCol()) == 0 && i > 0)
			std::cout << std::endl;
		i++;
	}
	Console::getInstance()->setColor(_COLOR_DEFAULT);

}

/**
* return the path beewteen fromSquare and toSquare with BFSPlus like method
*/
std::vector< Node::NodeRetrackInfo> Util::getPathSquareToSquareZoneMethod(const Maze * orM, short fromSquare, short toSquare, short posPlayer)
{
	std::unordered_set<std::string > marqueZoneBFS;

	short posBox = fromSquare;
	Maze m = *orM;

	short idBox;
	for (int i = 0; i < m.getPosBoxes().size(); i++)
	{
		if (m.getPosBoxes()[i] == fromSquare)
		{
			idBox = i;
			break;
		}
	}

	m.setPlayerPos(posPlayer);

	std::vector<bool> new_zone_accessible;
	short pos_or;
	std::vector<unsigned char>  field_originel = m.getField();
	std::vector<unsigned short> posBoxes = m.getPosBoxes();
	std::vector<bool> zone_originel = calcZoneAccessible(&m, pos_or);
	//	marque.clear();

	int position_player_or = m.getPosPlayer();
	int classement = 0;
	unsigned short newPositionOfBox, pos_originel = m.getPosPlayer();
	unsigned short profondeur;

	marqued(pos_or, &m, marqueZoneBFS);
	// Vector used for stocking all the bfs state. used for recreatnig the path at the end of the bfs
	std::vector< Node::NodeRetrackInfo>caseTracker;
	std::vector< Node::NodeRetrackInfo>res;
	std::queue<Node> queue;
	Node::NodeRetrackInfo bfsR(0, -1, position_player_or, -1);
	//bfsR.
	Node initCase(NULL, zone_originel, GameState(m.getField(), pos_or, m.getPosBoxes()), std::unordered_set<unsigned short>(),(unsigned short)0, bfsR, m.getPosBoxes().size());
	caseTracker.push_back(bfsR);
	queue.push(initCase);
	bool win = false;
	while (!win && !queue.empty())
	{
		Node currentCase = queue.front();
		queue.pop();
		profondeur = currentCase.profondeur;
		GameState curGameState = currentCase.gameState;
		short newNPos;
		std::vector<bool> 	zone_accessible = currentCase.accessibleZone;
		/**
		* We set the game in the state
		*/
		m.change_etat_jeu(curGameState);
		posBoxes = m.getPosBoxes();


		/**
		we look for pushed all boxes in all directions possibles
		*/
		for (char direction : m.allDirection)
		{
			short posBox = m.getPosBoxes()[idBox];

			short offset = m.getMoveOffset(direction);

			//position of the player for push the box
			short pusherPlace = posBox - offset;
			//position of th ebox after pushing it
			short newPosBox = posBox + offset;
			std::vector<char> adjDir = m.getAdjacentDirection(direction);

			//We look if the current box can be pushed in the direction
			if (zone_accessible[pusherPlace] && (m._canPushBox(posBox, direction, newPositionOfBox) && !m.isSquareDeadSquare(newPosBox)))
			{
				//[OPTIMIZER]
				//If yes we check that it will not create any dynamical deadlocks
				m.setPlayerPos(pusherPlace);

				//we push the box in the wanted direction
				m.updatePlayer(direction);

				//[OPTIMIZER TODO]
				//we check that we didn't already marque this case and marqued it if ut is not the case
				//We estimate if the accessible zone need to be recalculate (if a path path h as been open or closed we nn
				new_zone_accessible = calcZoneAccessible(&m, newNPos);



				//[OPTIMIZER]
				if (!marqued(newNPos, &m, marqueZoneBFS))
				{
					std::unordered_set<unsigned short> aglom = this->detectAgglomerateOFBoxes(&m, newPosBox);
					Node::NodeRetrackInfo bfsR(caseTracker.size(), currentCase.bfsRetrack.idCase, posBoxes[idBox] - offset, posBoxes[idBox]);
					Node newCase(currentCase.chapter, new_zone_accessible, GameState(m.getField(), newNPos, m.getPosBoxes()),aglom, profondeur + 1, bfsR, currentCase.placedBoxes);
					queue.push(newCase);
					caseTracker.push_back(bfsR);
				}
				m.change_etat_jeu(curGameState);

				if (newPosBox == toSquare)
				{
					win = true;
					break;
				}
			}
		}

	}

	std::vector<unsigned char> chemin;

	//ON recrée le chemin

	if (!win)
	{
		return res;
	}
	Node::NodeRetrackInfo retrack = caseTracker.back();
	while (retrack.idCase != 0)
	{
		res.push_back(retrack);
		retrack = caseTracker[retrack.idParentCase];
	}

	//setting back the game in its original field

	std::reverse(res.begin(), res.end());
	return res;
}


/**
* return true if the current boxPos of *m is already marqued
* if it is not the case it wil marque it
*/
bool Util::marqued(short acc, const  Maze *m, std::unordered_set<std::string > & marqueZoneBFS)
{
	std::vector<unsigned short> nposBoxes = m->getPosBoxes();
	std::vector<unsigned char> field = m->getField();
	std::stringstream result;
	nposBoxes.push_back(acc);
	std::copy(nposBoxes.begin(), nposBoxes.end(), std::ostream_iterator<short>(result, "."));
	std::string hashG = result.str();

	bool marqued = marqueZoneBFS.find(hashG) != marqueZoneBFS.end();
	if (!marqued)
	{
		marqueZoneBFS.insert(hashG);
	}

	return marqued;
}
