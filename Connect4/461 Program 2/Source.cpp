#include "Board.h"
#include "Player.h"
#include "MCTS.h"
#include <time.h>

void main() {
	srand(time(NULL));
	Player redPlayer("R");
	Player yellowPlayer("Y");
	MCTS test(redPlayer, yellowPlayer);
	Board connect4;
	test.simulate(connect4);
	cout << "end of line";
}