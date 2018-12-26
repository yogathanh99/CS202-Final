#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int lowerLight, int upperLight, bool rightToLeft, int moveCounterBound)
{
	mX = x;
	mY = y;
	posYLight = x;

	moveCounter = 0;
	lightCounter = 0;

	this->lowerLight = lowerLight;
	this->upperLight = upperLight;
	this->rightToLeft = rightToLeft;
	this->moveCounterBound = moveCounterBound;
}

int Obstacle::getMX()
{
	return mX;
}

int Obstacle::getMY()
{
	return mY;
}

int Obstacle::getLower()
{
	return lowerLight;
}

int Obstacle::getUpper()
{
	return upperLight;
}

bool Obstacle::getRightToLeft()
{
	return rightToLeft;
}

int Obstacle::getMoveCounterBound()
{
	return moveCounterBound;
}

void Obstacle::inc()
{
	if (moveCounter < moveCounterBound)
		++moveCounter;
	else
		moveCounter = 0;
}

bool Obstacle::isTime()
{
	return (moveCounter == 0);
}

void Obstacle::Move()
{
	++lightCounter;

	if (lightCounter == 1)
	{
		//Green light on
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		gotoXY(posXLight+2, posYLight - 1);
		cout << "LIGHT" << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 10; x++) {
				gotoXY(posXLight + x, posYLight + y);
				cout << char(219);
			}
			cout << endl;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	}
	else if (lightCounter == lowerLight)
	{
		//Red light on
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoXY(posXLight+2, posYLight - 1);
		cout << "LIGHT" << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 10; x++) {
				gotoXY(posXLight + x, posYLight + y);
				cout << char(219);
			}
			cout << endl;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	}

	if (lightCounter == upperLight)
		lightCounter = 0;
	else if (lightCounter > lowerLight)
		return;

	if (rightToLeft) {
		if (mY > 0)
			--mY;
		else
			mY = 145;
	}
	else {
		if (mY < 145)
			++mY;
		else
			mY = 0;
	}

}