
#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "zombies.h"
using namespace std;
class level
{
public:
	level();
	void loadlevel(string fileName, Player& player);
	void print();

	void MovePlayer(char input, Player& player);
	void updateEnemies(Player& player);

	string chooselevel();

	//getters
	char getTile(int x, int y);
	//setters
	void setTile(int x, int y, char tile);
private:
	bool _Key = false;
	void processzombiesMove(Player& player, int zombiesIndex, int targetX, int targetY);
	void processPlayerMove(Player& player, int targetX, int targetY);
	void battleMonster(Player& player, int targetX, int targetY);
	vector<string> _levelData;
	vector <zombies> _enemies;
};
