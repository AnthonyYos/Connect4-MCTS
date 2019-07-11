#pragma once
#include "Board.h"
#include "Player.h"


class MCTS
{
public:
	MCTS();
	MCTS(Player player1, Player player2);
	~MCTS();
	void print(Board currentBoard);
	void fillPositions(Board currentBoard);
	double playout(Board playingBoard);
	void simulate(Board currentBoard);

private:
	Player p1;
	Player p2;
	Board connect4;
	vector<Board> possibleMoves;
};

