#include "Player.h"

Player::Player()
{
}

Player::Player(string color)
{
	playerColor = color;
}

Player::~Player()
{
}

void Player::randomDrop(Board &board)
{
	int col = rand() % 7;
	bool dropped = false;
	while (dropped != true) {
		for (int i = board.getRows() - 1; i >= 0; i--) {
			if (board.isPositionEmpty(i, col)) {
				board.assignPiece(i, col, playerColor);
				dropped = true;
				break;
			}
		}
		if (dropped == false)
			col = rand() % 7;
	}
}

string Player::getPlayerColor()
{
	return playerColor;
}


