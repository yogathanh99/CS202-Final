#ifndef _GAME_H_
#define _GAME_H_

#include "Console.h"
#include "Human.h"
#include "Obstacle.h"
#include "Sound.h"

class Game
{

private:
	Human hu;
	int oldX, oldY;
	int level;
	vector<Obstacle*> ve;

public:
	Game();
	Game(int level);
	Game(int x, int y);

	void run();

	void updateHuman();

	void drawFull();

	void exitGame(thread* t, bool* IS_RUNNING_P);

	bool isHumanDead();

	void moveHuman(int input);

	string saveGame();

	void loadGame();

	void loadGameFile(string path);

	void updateObstacle(bool fog);

	void drawBomb();

	~Game();

};

void backgroundThread(Game* gP, bool* IS_RUNNING_P, bool* IS_PAUSE_P);

void loadingTime(int i, int sleeps);

void loadingGame();

void startLevel(int level);

void startGame();

void MenuLoad(string menuLoad[], int normal, int choose);

void MenuNew(string menuNew[], string menuLoad[], int normal, int choose);

void profile();

void nameGame(int x, int y);

void settingMenu();

struct ObstacleS
{
	int mX, mY;
	int lowerLight, upperLight;
	bool rightToLeft; // rightToLeft = true mean reversed lane
	int moveCounterBound; //lower move counter bound mean higher speed
};

extern int difficulty;

#endif