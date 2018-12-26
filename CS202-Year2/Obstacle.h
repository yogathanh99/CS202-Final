#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "Console.h"

class Obstacle {

private:
	int posXLight = 160, posYLight;
	int mX, mY;
	int moveCounter;
	int lightCounter;
	int lowerLight, upperLight;

	bool rightToLeft; // rightToLeft = true mean reversed lane
	int moveCounterBound; //lower move counter bound mean higher speed
public:
	Obstacle(int x, int y, int lowerLight, int upperLight, bool rightToLeft, int moveCounterBound);

	int getMX();
	int getMY();
	int getLower();
	int getUpper();
	bool getRightToLeft();
	int getMoveCounterBound();

	void inc();

	bool isTime();

	void Move();

};

#endif