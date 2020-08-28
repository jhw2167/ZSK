
//Main cpp file for running ZSK, include main.h for all includes
//and forward declared functions

#include "main.h"

void myFunc(State *s);

int main(int argc, char *argv[])
{
	Game game;

	while (game.windowIsOpen())
	{
		//Update Game
		game.update();

		//Render Game
		game.render();
	}

	//getchar();
	return 0;
}
//END MAIN METHOD


