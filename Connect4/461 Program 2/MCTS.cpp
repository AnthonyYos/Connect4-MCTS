#include "MCTS.h"

MCTS::MCTS()
{
}

MCTS::MCTS(Player player1, Player player2)
{
	p1 = player1;
	p2 = player2;
	possibleMoves.clear();
}

MCTS::~MCTS()
{
}

void MCTS::print(Board currentBoard)
{
	currentBoard.printBoard();
}

void MCTS::fillPositions(Board currentBoard)
{
	int moveCount = currentBoard.getMoveCount();
	string playerValue = p1.getPlayerColor();
	if (moveCount % 2 == 1)
		playerValue = p2.getPlayerColor();

	for (int j = 0; j < currentBoard.getCols(); j++) {
		for (int i = 5; i >= 0; i--) {
			if (currentBoard.isPositionEmpty(i, j)) {
				Board childBoard;
				moveCount = currentBoard.getMoveCount();
				childBoard.setBoard(currentBoard);
				childBoard.assignPiece(i, j, playerValue);
				childBoard.setMoveCount(++moveCount);
				childBoard.setMovePosition(i, j);
				possibleMoves.push_back(childBoard);
				break;
			}
		}
	}
}

double MCTS::playout(Board playingBoard)
{
	string playerValue;
	Player currentPlayer;
	if (playingBoard.getMoveCount() % 2 == 1) {
		currentPlayer = p1; playerValue = "R";
	}
	else {
		currentPlayer = p2; playerValue = "Y";
	}
	for (int i = playingBoard.getMoveCount(); i < 42; i++) {
		if (playingBoard.checkForWin()) {
			if (playerValue == currentPlayer.getPlayerColor()) {
				//playingBoard.printBoard();
				return 1;
			}
			else {
				//playingBoard.printBoard();
				return 0;
			}
		}
		else if (playingBoard.isDraw())
			return .5;
		if (i % 2 == 1) {
			p1.randomDrop(playingBoard);
			currentPlayer = p1;
		}
		else {
			p2.randomDrop(playingBoard);
			currentPlayer = p2;
		}
	}
}

void MCTS::simulate(Board currentBoard)
{
	fillPositions(currentBoard);
	Board loopBoard = possibleMoves.front();
	double trials;
	Player currentPlayer;
	vector<double> winPercentages;
	vector<double> opponentWinPercentages;
	int playerTracker = 0;
	do
	{
		for (int i = 0; i < possibleMoves.size(); i++) {
			double winCount = 0;
			loopBoard.setBoard(possibleMoves[i]);
			if (playerTracker % 2 == 0)
				currentPlayer = p1;
			else currentPlayer = p2;

			if (currentPlayer.getPlayerColor() == "R") {
				trials = 100;
				for (int numTrials = 0; numTrials < trials; numTrials++) {
					double x = playout(loopBoard);
					if (x >= 0)
						winCount += x;
				}
			}
			else {
				trials = 125;
				for (int numTrials = 0; numTrials < trials; numTrials++) {
					double x = playout(loopBoard);
					if (x >= 0)
						winCount += x;
				}
			}
			pair<int, int> movePosition = loopBoard.getMovePosition();
			int x = movePosition.first, y = movePosition.second;
			double win = winCount / trials;
			winPercentages.push_back(win * 100);
			cout << "Player: " << currentPlayer.getPlayerColor() << " at position: " << x << " " << y << " Win percentage: " << win * 100 << "\n";
		}


		double bestWin = winPercentages[0];
		double bestMoveIndex = 0;
		double secondBestIndex=1;
		bool stopOpponent = false;
		for (int i = 1; i < winPercentages.size(); i++)
			if (bestWin < winPercentages[i]) {
				bestWin = winPercentages[i];
				bestMoveIndex = i;
				if (bestMoveIndex == 6)
					for (int x = 0; x < currentBoard.getRows(); x++)
						if (currentBoard.isPositionEmpty(x, i - 1))
							secondBestIndex = i - 1;
						else
							secondBestIndex = i - 2;
				else
					secondBestIndex = i+1;
			}

		if (playerTracker > 0) {
			for (int i = 0; i < opponentWinPercentages.size(); i++)
				if (bestWin < opponentWinPercentages[i]) {
					bestWin = opponentWinPercentages[i];
					bestMoveIndex = i;
					stopOpponent = true;
				}
		}
		if (stopOpponent == false)
			currentBoard.setBoard(possibleMoves[bestMoveIndex]), currentBoard.setMoveCount(currentBoard.getMoveCount() + 1);
		else
			currentBoard.setBoard(possibleMoves[secondBestIndex]), currentBoard.setMoveCount(currentBoard.getMoveCount() + 1);
		opponentWinPercentages.clear(), opponentWinPercentages = winPercentages;
		possibleMoves.clear(), winPercentages.clear();
		currentBoard.printBoard();
		fillPositions(currentBoard);
		playerTracker++;
	} while (!currentBoard.checkForWin() || currentBoard.isDraw());
	cout << "Final board" << "\n";
	currentBoard.printBoard();
}

