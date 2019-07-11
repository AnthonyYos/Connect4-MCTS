#pragma once
#include <string>
#include "Board.h"
using std::string;
class Player
{
public:
	Player();
	Player(string color);
	~Player();
	void randomDrop(Board &connect4);
	string getPlayerColor();
private:
	string playerColor;
};

