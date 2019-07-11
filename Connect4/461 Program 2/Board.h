#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using std::cout;
using std::vector;
using std::string;
using std::pair;

class Board
{
public:
	Board();
	~Board();
	void printBoard();
	bool isHorizontalMatch(int currentRow,int currentCol);
	bool isVerticalMatch(int currentRow,int currentCol);
	bool isDiagonalUpMatch(int currentRow, int currentCol);
	bool isDiagonalDownMatch(int currentRow, int currentCol);
	bool checkForWin();
	int getRows();
	int getCols();
	bool isPositionEmpty(int currentRow,int currentCol);
	void assignPiece(int currentRow, int currentCol,string color);
	vector<vector<string>> getBoard(Board currentBoard);
	void setBoard(Board currentBoard);
	int getMoveCount();
	void setMoveCount(int n);
	void setMovePosition(int x,int y);
	pair<int, int> getMovePosition();
	bool fullBoard();
	bool isDraw();

private:
	const int rows=6;
	const int cols=7;
	vector<vector<string>> playingBoard;
	int numberOfMoves;
	pair<int, int> lastMovePosition;

};

