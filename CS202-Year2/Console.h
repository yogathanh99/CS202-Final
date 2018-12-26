#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <dos.h>

using namespace std;

void gotoXY(int x, int y);
void showConsoleCursor(bool showFlag);

#endif // !CONSOLE_H
