#ifndef GAME_STATE
#define GAME_STATE

class GameState {
public:
	GameState(std::vector<unsigned char> field, unsigned short posPlayer, std::vector<unsigned short> posBox) :
		field(field), posPlayer(posPlayer),posBox(posBox)
	{

	}

	~GameState(){};
	std::vector<unsigned char> field;
	unsigned short posPlayer;
	std::vector<unsigned short> posBox;
};


#endif
