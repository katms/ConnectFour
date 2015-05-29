#include "ConnectFour.h"
#include <ctime>

int main(int argc, char* argv[])
{
	srand(time(0));
	ConnectFour game;
	game.game_loop();
	return 0;
}

