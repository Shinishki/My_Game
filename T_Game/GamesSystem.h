#pragma once
#include "Player.h"
#include <string>
#include "level.h"
#include <iostream>

using namespace std;
class GamesSystem
{
public:
	GamesSystem(string levelFileName);

	void playGame();
	void playerMove();
private:

	level _level;
	Player _player;

};
