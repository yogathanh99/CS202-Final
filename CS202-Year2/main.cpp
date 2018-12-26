#include "Game.h"

int main()
{	
	//set fullscreen for console
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	
	showConsoleCursor(false);

	loadingGame();

	startGame();
	
	return 0;
}