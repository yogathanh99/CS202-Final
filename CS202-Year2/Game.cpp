#include "Game.h"

int difficulty = 1;

int random(int l, int r) {
	return rand() % (r - l + 1) + l;
}


// Handles most background tasks
void backgroundThread(Game *gP, bool *IS_RUNNING_P, bool *IS_PAUSE_P)
{
	gP->drawFull();

	int fogCounter = 0;

	bool move = true;
	bool fog = true;

	// While no reason to stop, and while human is still alive
	while (*IS_RUNNING_P & !gP->isHumanDead())
	{
		// If pause is true, loops until pause is false
		while (*IS_PAUSE_P)
			;

		if (fogCounter < 350)
			++fogCounter;
		else
			fogCounter = 0;

		if (fogCounter < 275)
			fog = true;
		else
			fog = false;

		gP->updateObstacle(fog);

		gP->updateHuman();

		// Need to constantly check for collision so collision checking is handled by
		// background thread
		gP->isHumanDead();

		Sleep(10);
	}

	// When there is collision, above loop will exit and the below line is printed
	// Depending on input, new game is started or program exits
	if (gP->isHumanDead())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

		gP->drawFull();

		gP->drawBomb();

		// Play explosion sound effect
		if (sfxOn)
			PlaySound(SFX_BOMB, NULL, SND_ASYNC);
		else
			PlaySound(NULL, NULL, 0);

		//cout << "Testing" << endl;
		this_thread::sleep_for(1s);

		// Play game over jingle
		play(SFX_LOSE, true, TYPE_SFX);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoXY(105, 35);
		cout << "YOU ARE DEAD !" << endl;
		gotoXY(95, 36);
		cout << "Press 'y' to continue or 'n' to end" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	}
}

void loadHistory(vector<string> &files) {
	ifstream fin;
	fin.open("history.bin", ios::binary);

	int size;
	fin.read((char*)&size, sizeof(int));

	for (int i = 0; i < size; ++i) {
		int len;
		fin.read((char*)&len, sizeof(int));

		char *arr = new char[len + 1];
		fin.read((char*)arr, sizeof(char)*len);

		string file;
		for (int j = 0; j < len; ++j)
			file += arr[j];

		files.push_back(file);

		delete[] arr;
	}

	fin.close();
}

void saveHistory(const vector<string> &files) {
	ofstream fout;
	fout.open("history.bin", ios::binary);

	int size = files.size();
	fout.write((char *)&size, sizeof(int));

	for (int i = 0; i < size; ++i) {
		int len = files[i].size();
		fout.write((char *)&len, sizeof(int));

		char *arr = new char[len];
		for (int j = 0; j < len; ++j)
			arr[j] = files[i][j];

		fout.write((char*)arr, sizeof(char)*len);

		delete[] arr;
	}

	fout.close();
}

void loadingTime(int i, int sleeps) {
	cout << char(219);
	Sleep(sleeps); 
	gotoXY(171, 31);
	cout << i << "%";
}

void loadingGame() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	play(SFX_LOADING, false, TYPE_SFX);
	system("cls");
	gotoXY(70, 30);
	int x = 0;
	for (int i = 1; i <= 100; i++) {
		gotoXY(70 + x, 31);
		if (i < 50) loadingTime(i, 100);
		else if (i >= 50 && i <= 70) loadingTime(i, 150);
		else if (i > 70 && i <= 85) loadingTime(i, 40);
		else if (i > 85 && i <= 95) loadingTime(i, 200);
		else if (i>95 && i<99) loadingTime(i, 300);
		else if (i==99) loadingTime(i, 1000);
		else loadingTime(i, 400);
		x++;
	}
	gotoXY(120, 32);
	cout << "COMPLETE";
	Sleep(300);
	cout << "!";
	Sleep(350);
	cout << "!";
	Sleep(500);
}

void profile()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	int x = 98, y = 37;
	gotoXY(x, y);
	cout << "Vo Trung Thanh" << endl;
	gotoXY(x, y + 1);
	cout << "Nguyen Diep Xuan Quang" << endl;
	gotoXY(x, y + 2);
	cout << "Nguyen Ngoc Phong" << endl;
	gotoXY(x, y + 3);
	cout << "Tran Hoang Cong Trong" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void nameGame(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoXY(x, y);
	cout << "  ______ .______        ______       _______.     _______. __ .__   __.  _______      .______        ______       ___      _______  " << endl;
	gotoXY(x, y + 1);
	cout << " /      ||   _  \\      /  __  \\     /       |    /       ||  ||  \\ |  | /  _____|     |   _  \\      /  __  \\     /   \\    |       \\ " << endl;
	gotoXY(x, y + 2);
	cout << "|  ,----'|  |_)  |    |  |  |  |   |   (----`   |   (----`|  ||   \\|  ||  |  __       |  |_)  |    |  |  |  |   /  ^  \\   |  .--.  |" << endl;
	gotoXY(x, y + 3);
	cout << "|  |     |      /     |  |  |  |    \\   \\        \\   \\    |  ||  . `  ||  | |_ |      |      /     |  |  |  |  /  /_\\  \\  |  |  |  |" << endl;
	gotoXY(x, y + 4);
	cout << "|  `----.|  |\\  \\----.|  `--'  |.----)   |   .----)   |   |  ||  |\\   ||  |__| |      |  |\\  \\----.|  `--'  | /  _____  \\ |  '--'  |" << endl;
	gotoXY(x, y + 5);
	cout << " \\______|| _| `._____| \\______/ |_______/    |_______/    |__||__| \\__| \\______|      | _| `._____| \\______/ /__/     \\__\\|_______/ " << endl;
	gotoXY(x, y + 6);
	cout << "" << endl;
}

void startLevel(int level)
{
	system("cls");
	Game g(level);
	g.run();
}

void settingMenu() {
	system("cls");

	const int CHOOSE_ATTRIBUTE = 11;
	const int NORMAL_ATTRIBUTE = 10;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NORMAL_ATTRIBUTE);

	int line = 30;
	bool stop = false;

	while (!stop) {
		// Draw game name
		nameGame(50, 20);

		// Draw new setting menu
		string settingMenu[] = { "1. Sound Effect: ", "2. Music: ", "3. Delete save history", "<< Back " };
		settingMenu[0] += sfxOn ? "ON" : "OFF";
		settingMenu[1] += musicOn ? "ON" : "OFF";

		int numItems = 4;// settingMenu->length();

		for (int i = 0; i < numItems; ++i) {
			gotoXY(100, 30 + i);
			cout << settingMenu[i] << endl;
		}

		gotoXY(100, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CHOOSE_ATTRIBUTE);

		int choice = line - 30;

		cout << settingMenu[choice] << endl;

		// Draw team members
		profile();

		// Wait for user input
		int input = toupper(_getch());

		// ENTER key
		if (input == 13) {

			play(SFX_MENU_SELECT, true, TYPE_SFX);
			switch (line) {
			case 30: //Sound Effect
				sfxOn ^= true;
				break;
			case 31: //Music
				musicOn ^= true;
				break;
			case 32: {
				//Reset game
				ofstream fout;
				fout.open("newGame.txt");
				fout << 1;
				fout.close();

				//Reset history
				vector<string> emptyFiles;
				saveHistory(emptyFiles);

				startGame();
				break;
			}
			case 33:
				stop = true;
				break;
			}

			// Erase old menu item
			gotoXY(100, line);
			for (int j = 0; j < 25; ++j)
				cout << " ";
		}
		else {
			gotoXY(100, line);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NORMAL_ATTRIBUTE);
			cout << settingMenu[choice] << endl;

			//UP key
			if (input == 87)
			{
				play(SFX_MENU_NAVIGATE, false, TYPE_SFX);
				if (line > 30)
					--line;
				else
					line = 29 + numItems;
			}
			//DOWN key
			else if (input == 83)
			{
				play(SFX_MENU_NAVIGATE, false, TYPE_SFX);
				if (line < 29 + numItems)
					++line;
				else
					line = 30;
			}
		}
	}
}

void difficultyMenu() {
	system("cls");

	const int CHOOSE_ATTRIBUTE = 11;
	const int NORMAL_ATTRIBUTE = 10;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NORMAL_ATTRIBUTE);

	int line = 30;
	bool stop = false;

	gotoXY(100, 28);
	cout << "Select a difficulty!" << endl;

	while (!stop) {
		// Draw game name
		nameGame(50, 20);

		// Draw new setting menu
		string difficultyMenu[] = { "   Easy", "   Medium", "   Hard", "<< Back" };

		int numItems = 4;// settingMenu->length();

		for (int i = 0; i < numItems; ++i) {
			gotoXY(100, 30 + i);
			cout << difficultyMenu[i] << endl;
		}

		gotoXY(100, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CHOOSE_ATTRIBUTE);

		int choice = line - 30;

		cout << difficultyMenu[choice] << endl;

		// Draw team members
		profile();

		// Wait for user input
		int input = toupper(_getch());

		// ENTER key
		if (input == 13) {
			play(SFX_MENU_SELECT, true, TYPE_SFX);
			switch (line) {
			case 33: //Sound Effect
				stop = true;
				break;
			default:
				difficulty = line - 30;
				startLevel(0);
				stop = true;
			}
		}
		else {
			gotoXY(100, line);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NORMAL_ATTRIBUTE);
			cout << difficultyMenu[choice] << endl;

			//UP key
			if (input == 87)
			{
				play(SFX_MENU_NAVIGATE, false, TYPE_SFX);
				if (line > 30)
					--line;
				else
					line = 29 + numItems;
			}
			//DOWN key
			else if (input == 83)
			{
				play(SFX_MENU_NAVIGATE, false, TYPE_SFX);
				if (line < 29 + numItems)
					++line;
				else
					line = 30;
			}
		}
	}
}

void startGame()
{
	//loadingGame();

	system("cls");

	int choose = 11;
	int normal = 10;

	nameGame(50, 20);

	string menuLoad[] = { "1. New game", "2. Load game", "3. Settings", "4. Exit" };
	string menuNew[] = { "1. New game", "2. Settings", "3. Exit" };

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normal);
	ifstream fin;
	fin.open("newGame.txt");

	if (!fin) {
		cout << "Unable to open game";
		exit(1); // terminate with error
	}
	else {
		int x;
		fin >> x;
		if (x == 1) MenuNew(menuNew, menuLoad, normal, choose);
		else MenuLoad(menuLoad, normal, choose);
	}
	fin.close();
}

void MenuLoad(string menuLoad[], int normal, int choose) {
	system("cls");

	for (int i = 0; i < 4; ++i) {
		gotoXY(100, 30 + i);
		cout << menuLoad[i] << endl;
	}

	int line = 30;

	bool stop = false;

	while (!stop)
	{
		nameGame(50, 20);

		gotoXY(100, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), choose);
		int choose1 = line - 30;

		cout << menuLoad[choose1] << endl;

		profile();
		int input = toupper(_getch());

		if (input == 13)
		{
			play(SFX_MENU_SELECT, true, TYPE_SFX);
			switch (line)
			{
			case 30:
			{
				difficultyMenu();

				startGame();

				break;
			}
			case 31:
			{
				system("cls");

				vector<string> savedFiles;
				loadHistory(savedFiles);

				cout << "List of saved games:" << endl;
				for (int i = 0; i < savedFiles.size(); ++i)
					cout << i + 1 << ". " << savedFiles[i] << endl;

				string path;
				cout << "Enter path:" << endl;
				getline(cin, path);

				Game g;
				g.loadGameFile(path);

				startGame();

				break;
			}
			case 32: {
				settingMenu();

				startGame();

				break;
			}
			case 33:
				gotoXY(97, 34);
				cout << "Thanks for playing!!" << endl;
				gotoXY(0, 45);
				exit(1);
			}
		}

		gotoXY(100, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normal);
		cout << menuLoad[choose1] << endl;

		if (input == 87)
		{
			play(SFX_MENU_NAVIGATE, false, TYPE_SFX);
			if (line - 1 != 29)
				--line;
			else
				line = 33;
		}
		else if (input == 83)
		{
			play(SFX_MENU_NAVIGATE, false, TYPE_SFX);
			if (line + 1 != 34)
				++line;
			else
				line = 30;
		}
	}
}

void MenuNew(string menuNew[], string menuLoad[], int normal, int choose) {
	for (int i = 0; i < 3; ++i) {
		gotoXY(100, 30 + i);
		cout << menuNew[i] << endl;
	}

	int line = 30;

	bool stop = false;

	while (!stop)
	{
		nameGame(50, 20);

		gotoXY(100, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), choose);
		int choose1 = line - 30;

		cout << menuNew[choose1] << endl;

		profile();
		int input = toupper(_getch());

		if (input == 13)
		{
			play(SFX_MENU_SELECT, true, TYPE_SFX);
			switch (line)
			{
			case 30:
			{
				difficultyMenu();

				startGame();
				break;
			}
			case 31:
			{
				settingMenu();

				startGame();
				break;
			}
			case 32:
				gotoXY(97, 34);
				cout << "Thanks for playing!!" << endl;
				gotoXY(0, 45);
				exit(1);
			}
		}

		gotoXY(100, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normal);
		cout << menuNew[choose1] << endl;

		if (input == 87)
		{
			play(SFX_MENU_NAVIGATE, false, TYPE_SFX);
			if (line - 1 != 29)
				--line;
			else
				line = 32;
		}
		else if (input == 83)
		{
			play(SFX_MENU_NAVIGATE, false, TYPE_SFX);
			if (line + 1 != 33)
				++line;
			else
				line = 30;
		}
	}
}

Game::Game() : hu(0, 0) {}

Game::Game(int level) : hu(30, 75)
{
	oldX = hu.getX();
	oldY = hu.getY();

	this->level = level;

	srand(time(NULL));

	int numOfLanes = 5;

	for (int i = 0; i < numOfLanes; i += 1)
	{
		random_device rd;
		mt19937 g(rd());

		vector<int> arr = { 0, 1, 2, 3, 4, 5 };
		shuffle(arr.begin(), arr.end(), g);

		int shift = rand() % 15;

		int lower = 20 + 5 * i;
		int upper = lower + 30 - 7 * i;

		bool rightToLeft = rand() % 2;
		int moveCounterBound;
		switch (difficulty) {
		case 0:
			moveCounterBound = random(7, 9);
			break;
		case 1:
			moveCounterBound = random(5, 7);
			break;
		case 2:
			moveCounterBound = random(3, 5);
			break;
		}

		int diffLimit = 4 + difficulty;
		int lvlLimit = difficulty + level + 1;
		int numObstaclesInLane = min(diffLimit, lvlLimit);

		for (int j = 0; j < numObstaclesInLane; ++j)
		{
			Obstacle* tempOb = new Obstacle((i + 1) * 5, arr[j] * 25 + shift, lower, upper, rightToLeft, moveCounterBound);
			ve.push_back(tempOb);
		}
	}
}

Game::Game(int x, int y) : hu(x, y) {}

// Handles most of the control flow
void Game::run()
{
	using namespace std::chrono_literals;

	// Wait for SFX to finish
	this_thread::sleep_for(1s);

	// Is set to false when human is dead, ESC is pressed, or when human is at finish line
	bool IS_RUNNING = true;

	// Is set to true when "p" is pressed
	// Separate from IS_RUNNING because different flow control is needed
	bool IS_PAUSE = false;

	// Background thread handling pausing, drawing, updating obstacle positions,
	// and checking for collisions
	thread bgThread(backgroundThread, this, &IS_RUNNING, &IS_PAUSE);


	// Play background music for the game
	play(MUSIC_GAME, false, TYPE_MUSIC);

	// Input loop, stop when human is dead, ESC is pressed, or when human is at finish line
	while (true)
	{
		int input = toupper(_getch());

		// If dead, end game. Except when input = "y", then game is reset
		if (hu.isDead())
		{
			exitGame(&bgThread, &IS_RUNNING);

			// To handle the unwanted effect where if the user hold a move button toward an
			// obstacle then the game will jump out
			// It is better when the game stop at a screen, notifying the user that they have lost
			// When the user collides with an obstacle, IS_END is set to true to avoid the _getch
			// loop joining the background thread multiple times
			int input2 = input;

			// If input = "y", reset. If input = "n", end game. Otherwise, read input again
			while (true)
			{
				if (input2 == 89)
					startLevel(level);
				else if (input2 != 78)
				{
					input2 = toupper(_getch());
					continue;
				}

				break;
			}

			break;
		}

		// Input = "p"
		if (input == 80)
		{

			IS_PAUSE = true;

			while (true)
			{
				int input2 = toupper(_getch());

				if (input2 == 80)
				{
					IS_PAUSE = false;
					break;
				}
			}
		}

		// Input = ESC
		if (input == 27)
		{
			exitGame(&bgThread, &IS_RUNNING);
			PlaySound(NULL, NULL, 0);
			break;
		}
		// Input 'l' to save game
		if (input == 76)
		{
			exitGame(&bgThread, &IS_RUNNING);

			string path = saveGame();

			cout << "y to continue, n to end" << endl;

			while (true)
			{
				int input2 = toupper(_getch());

				if (input2 == 89)
					loadGameFile(path);
				else if (input2 != 78)
					continue;

				break;
			}

			PlaySound(NULL, NULL, 0);

			break;
		}
		// Input 't' to load old game
		if (input == 84)
		{
			ifstream fin;
			fin.open("newGame.txt");

			if (!fin) {
				cout << "Unable to open game";
				exit(1); // terminate with error
			}
			else {
				int x;
				fin >> x;
				if (x == 1) {
					gotoXY(90, 40);
					cout << "You have no save file!";
					_getch();
					fin.close();

				}
				else {
					fin.close();
					exitGame(&bgThread, &IS_RUNNING);

					loadGame();

					break;
				}
			}
		}

		// Up, down, left, right
		moveHuman(input);

		// Human at finish line
		if (hu.atFinish())
		{
			Sleep(100);
			exitGame(&bgThread, &IS_RUNNING);

			play(SFX_WIN, true, TYPE_SFX);

			if (level < 10)
			{
				cout << "On to level " << (level + 1) << endl;
				cout << "Press any key to continue" << endl;
				_getch();
				//_getch();
				//Sleep(1000);
				startLevel(level + 1);
			}
			else
			{
				cout << "You have won. Back to level 0" << endl;
				cout << "Press any key to continue" << endl;
				_getch();
				//_getch();
				//Sleep(1000);
				startLevel(0);
			}

			break;
		}

		Sleep(10);
	}
}

void Game::updateHuman()
{
	int newX = hu.getX();
	int newY = hu.getY();

	string textureH[] = {
		"   ",
		" o/  ",
		"/|",
		"/ \\" };

	for (int i = 0; i < 4; ++i)
	{
		gotoXY(oldY, oldX + i);
		cout << "   ";
		gotoXY(newY, newX + i);
		cout << textureH[i];
	}

	oldX = newX;
	oldY = newY;
}

vector<string> getTexture(Obstacle *o) {
	vector<string> texture;
	if (o->getRightToLeft()) {
		texture.push_back("     ______   ");
		texture.push_back(" __.'//_||_|\ ");
		texture.push_back("//_ _    _   )");
		texture.push_back(" '-(_)--(_)-'=");
	}
	else {
		texture.push_back("  ______     ");
		texture.push_back(" /|_||_\\`.__ ");
		texture.push_back("(   _    _ _\\");
		texture.push_back("=`-(_)--(_)-'");
	}
	return texture;
}


void Game::drawFull()
{
	system("cls");

	string textureH[] = {
		"   ",
		"\\o/ ",
		" |",
		"/ \\" };

	for (int i = 0; i < 4; ++i)
	{
		gotoXY(hu.getY(), hu.getX() + i);
		cout << textureH[i];
	}


	for (int i = 0; i < ve.size(); ++i)
	{
		vector<string> textureV = getTexture(ve[i]);
		for (int j = 0; j < 4; ++j)
		{
			gotoXY(ve[i]->getMY(), ve[i]->getMX() + j);
			cout << textureV[j];
		}
	}

	gotoXY(0, 1);
	cout << "Level: " << level;

	string difficultyStr = "Difficulty: ";
	switch (difficulty) {
	case 0:
		difficultyStr += "EASY";
		break;
	case 1:
		difficultyStr += "NORMAL";
		break;
	case 2:
		difficultyStr += "HARD";
		break;
	}

	gotoXY(0, 0);
	cout << difficultyStr;

	gotoXY(175, 0);
	cout << "     INSTRUCTION    " << endl;

	gotoXY(175, 1);
	cout << "[WASD]: Move";

	gotoXY(175, 2);
	cout << "[L]: Save";

	gotoXY(175, 3);
	cout << "[T]: Load";

	gotoXY(175, 4);
	cout << "[ESC]: Exit";

	gotoXY(0, 36);
}

// Signals the background thread to stop
void Game::exitGame(thread *t, bool *IS_RUNNING_P)
{
	// Set bool to false, the loop in the background thread will exit
	*IS_RUNNING_P = false;

	// After the background thread is finished, merge it back into the main thread
	t->join();

	drawFull();
}

bool Game::isHumanDead()
{
	if (hu.isDead())
	{
		return true;
	}

	for (int i = 0; i < ve.size(); ++i)
	{
		if (hu.collide(ve[i])) break;
	}
	return hu.isDead();
}

void Game::moveHuman(int input)
{
	if (input == 87)
		hu.up();
	else if (input == 83)
		hu.down();
	else if (input == 65)
		hu.left();
	else if (input == 68)
		hu.right();
}

string Game::saveGame()
{
	drawFull();

	cout << "Saving" << endl;

	string path;
	cout << "Enter path:" << endl;
	getline(cin, path);

	ofstream fout;
	fout.open(path, ios::binary);

	int memblock[] = { hu.getX(), hu.getY() };
	fout.write((char *)memblock, sizeof(int) * 2);

	fout.write((char *)&difficulty, sizeof(int));

	fout.write((char *)&level, sizeof(int));

	int size = ve.size();
	fout.write((char *)&size, sizeof(int));

	ObstacleS *arr = new ObstacleS[size];

	for (int i = 0; i < ve.size(); ++i)
	{
		arr[i].mX = ve[i]->getMX();
		arr[i].mY = ve[i]->getMY();
		arr[i].lowerLight = ve[i]->getLower();
		arr[i].upperLight = ve[i]->getUpper();
		arr[i].rightToLeft = ve[i]->getRightToLeft();
		arr[i].moveCounterBound = ve[i]->getMoveCounterBound();
	}

	fout.write((char *)arr, sizeof(ObstacleS) * size);

	delete[] arr;

	fout.close();

	vector<string> savedFiles;
	loadHistory(savedFiles);

	bool isDuplicate = false;
	for (int i = 0; i < savedFiles.size(); ++i) {
		if (savedFiles[i] == path) {
			isDuplicate = true;
			break;
		}
	}

	if (!isDuplicate)
		savedFiles.push_back(path);

	saveHistory(savedFiles);

	ofstream fout1;
	fout1.open("newGame.txt");
	fout1 << 0;
	fout1.close();

	return path;
}

void Game::loadGame()
{
	drawFull();

	vector<string> savedFiles;
	loadHistory(savedFiles);

	cout << "List of saved games:" << endl;
	for (int i = 0; i < savedFiles.size(); ++i)
		cout << i + 1 << ". " << savedFiles[i] << endl;

	string path;
	cout << "Enter path:" << endl;
	getline(cin, path);

	PlaySound(NULL, NULL, 0);

	loadGameFile(path);
}

void Game::loadGameFile(string path)
{
	ifstream fin;
	fin.open(path, ios::binary);

	if (!fin.is_open())
		return;

	int memblock[2];
	fin.read((char *)memblock, sizeof(int) * 2);

	Game g(memblock[0], memblock[1]);

	fin.read((char *)&difficulty, sizeof(int));

	fin.read((char *)&(g.level), sizeof(int));

	int size;
	fin.read((char *)&size, sizeof(int));

	ObstacleS *arr = new ObstacleS[size];
	fin.read((char *)arr, sizeof(ObstacleS) * size);

	for (int i = 0; i < size; ++i)
	{
		Obstacle *tempOb = new Obstacle(arr[i].mX, arr[i].mY, arr[i].lowerLight, arr[i].upperLight, arr[i].rightToLeft, arr[i].moveCounterBound);
		g.ve.push_back(tempOb);
	}

	delete[] arr;

	fin.close();

	g.run();
}

void Game::updateObstacle(bool fog)
{
	ve[0]->inc();

	if (!ve[0]->isTime())
		return;

	// eraseObstacle();

	string empty = "              ";

	for (int i = 0; i < ve.size(); ++i)
	{
		int oldX = ve[i]->getMX();
		int oldY = ve[i]->getMY();

		ve[i]->Move();

		int newX = ve[i]->getMX();
		int newY = ve[i]->getMY();

		vector<string> texture = getTexture(ve[i]);

		for (int j = 0; j < 4; ++j)
		{
			if (ve[i]->getRightToLeft()) {
				if (oldY == 0) {
					gotoXY(oldY, oldX + j);
					cout << empty;
				}
				else {
					gotoXY(oldY + 13, oldX + j);
					cout << " ";
				}
			}
			else {
				gotoXY(oldY, oldX + j);
				if (newY == 0)
					cout << empty;
				else
					cout << " ";
			}

			gotoXY(newY, newX + j);
			cout << texture[j];
		}
	}
}

void Game::drawBomb()
{
	string bomb[] = {
		"(\\|/)",
		"|-B-|",
		"(/|\\)" };

	for (int i = 0; i < 3; ++i)
	{
		gotoXY(hu.getY(), hu.getX() + i + 1);
		cout << bomb[i];
	}
}

Game::~Game()
{
	for (int i = 0; i < ve.size(); ++i)
		delete ve[i];
}