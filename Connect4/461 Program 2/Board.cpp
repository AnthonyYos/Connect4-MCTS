#include "Board.h"

Board::Board()
{
	playingBoard.resize(rows, vector<string>(cols));
	numberOfMoves = 0;
}

Board::~Board()
{
}

void Board::printBoard()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (playingBoard[i][j].empty())
				cout << "|" << " ";
			else
				cout << "|" << playingBoard[i][j];
		}
		cout << "|" << "\n";
	}
	cout << "---------------------------------------------------" << "\n";
}

bool Board::isHorizontalMatch(int currentRow, int currentCol)
{
	int maxCol = 3;
	if (playingBoard[currentRow][currentCol].empty() || currentCol > maxCol)
		return false;
	const string playerValue = playingBoard[currentRow][currentCol];
	for (int i = 1; i < 4; i++) {
		if (playingBoard[currentRow][currentCol + i] != playerValue)
			return false;
	}
	return true;
}

bool Board::isVerticalMatch(int currentRow, int currentCol)
{
	int minRow = 3;
	if (playingBoard[currentRow][currentCol].empty() || currentRow < minRow)
		return false;
	const string playerValue = playingBoard[currentRow][currentCol];
	for (int i = 1; i < 4; i++) {
		if (playingBoard[currentRow - i][currentCol] != playerValue)
			return false;
	}
	return true;
}

bool Board::isDiagonalUpMatch(int currentRow, int currentCol)
{
	int maxCol = 3;
	int minRow = 3;
	if (playingBoard[currentRow][currentCol].empty() || currentRow <minRow || currentCol > maxCol)
		return false;
	const string playerValue = playingBoard[currentRow][currentCol];
	for (int i = 1; i < 4; i++) {
		if (playingBoard[currentRow - i][currentCol + i] != playerValue)
			return false;
	}
	return true;
}

bool Board::isDiagonalDownMatch(int currentRow, int currentCol)
{
	int maxRow = 2;
	int maxCol = 3;
	if (playingBoard[currentRow][currentCol].empty() || currentRow > maxRow || currentCol > maxCol)
		return false;
	const string playerValue = playingBoard[currentRow][currentCol];
	for (int i = 1; i < 4; i++) {
		if (playingBoard[currentRow + i][currentCol + i] != playerValue)
			return false;
	}
	return true;
}

bool Board::checkForWin()
{
	for (int i = 5; i >= 0; i--) {
		for (int j = 0; j < cols; j++) {

			if (isHorizontalMatch(i, j)) {
				return true;
			}
			if (isVerticalMatch(i, j)) {
				return true;
			}
			if (isDiagonalUpMatch(i, j)) {
				return true;
			}
			if (isDiagonalDownMatch(i, j)) {
				return true;
			}

		}
	}
	return false;
}

int Board::getRows()
{
	return rows;
}

int Board::getCols()
{
	return cols;
}

bool Board::isPositionEmpty(int currentRow, int currentCol)
{
	return playingBoard[currentRow][currentCol].empty();
}

void Board::assignPiece(int currentRow, int currentCol, string color)
{
	playingBoard[currentRow][currentCol] = color;
}

vector<vector<string>> Board::getBoard(Board currentBoard)
{
	return currentBoard.playingBoard;
}

void Board::setBoard(Board currentBoard)
{
	playingBoard = currentBoard.getBoard(currentBoard);
	lastMovePosition = currentBoard.getMovePosition();
}

int Board::getMoveCount()
{
	return numberOfMoves;
}

void Board::setMoveCount(int n)
{
	numberOfMoves = n;
}

void Board::setMovePosition(int x, int y)
{
	lastMovePosition = { x,y };
}

pair<int, int> Board::getMovePosition()
{
	return lastMovePosition;
}



bool Board::fullBoard()
{
	for (int j = 0; j < cols; j++)
		if (playingBoard[0][j].empty())
			return false;
	return true;
}

bool Board::isDraw()
{
	if (!checkForWin()&&fullBoard())
		return true;
	return false;
}
