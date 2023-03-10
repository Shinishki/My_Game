#include "level.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <conio.h>
level::level()
{
}


void level::loadlevel(string fileName, Player& player) {

	//Loads the level
	ifstream file;
	file.open(fileName);

	if (file.fail()) {
		perror(fileName.c_str());
		//Pause :/
		system("PAUSE");
		exit(1);

	}

	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);

	}
	file.close();

	//Process the level
	char tile;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@'://player
				player.setPosition(j, i);
				break;
			case 'S'://Snake
				_enemies.push_back(zombies("Snake", tile, 1, 3, 1, 10, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'g':
				_enemies.push_back(zombies("Goblin", tile, 2, 10, 5, 35, 150));
				_enemies.back().setPosition(j, i);
				break;
			case 'O':
				_enemies.push_back(zombies("Ogre", tile, 4, 20, 40, 200, 500));
				_enemies.back().setPosition(j, i);
				break;
			case 'D':
				_enemies.push_back(zombies("Dragon", tile, 100, 2000, 2000, 2000, 5000000));
				_enemies.back().setPosition(j, i);
				break;
			case 'B':
				_enemies.push_back(zombies("Bandit", tile, 3, 15, 10, 100, 250));
				_enemies.back().setPosition(j, i);
				break;
			}
		}
	}

}

void level::print() {

	std::cout << string(100, '\n');

	for (int i = 0; i < _levelData.size(); i++) {
		printf("%s\n", _levelData[i].c_str());


	}
	printf("\n");

}

void level::MovePlayer(char input, Player& player) {
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);



	switch (input) {
	case 'W': //up
	case 'w':

		processPlayerMove(player, playerX, playerY - 1);

		break;
	case 'S': //down
	case 's':

		processPlayerMove(player, playerX, playerY + 1);

		break;
	case 'A': // left
	case 'a':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'D'://right
	case 'd':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("INVALID INPUT!\n");
		system("PAUSE");
	}

}

void level::updateEnemies(Player& player) {
	char aiMove;
	int playerX;
	int playerY;
	int zombiesX;
	int zombiesY;


	player.getPosition(playerX, playerY);
	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(zombiesX, zombiesY);

		switch (aiMove) {
		case 'w':

			processzombiesMove(player, i, zombiesX, zombiesY - 1);

			break;
		case 's':

			processzombiesMove(player, i, zombiesX, zombiesY + 1);

			break;
		case 'a':
			processzombiesMove(player, i, zombiesX - 1, zombiesY);
			break;
		case 'd':
			processzombiesMove(player, i, zombiesX + 1, zombiesY);
			break;

		}
	}
}



char level::getTile(int x, int y) {
	return _levelData[y][x];
}

void level::setTile(int x, int y, char tile) {
	_levelData[y][x] = tile;

}

void level::processPlayerMove(Player& player, int targetX, int targetY) {
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;
	case'%':
		_Key = true;
		setTile(targetX, targetY, '.');
	case '$':
		if (_Key == true) {
			setTile(targetX, targetY, '.');
		}
		break;
	case '#':
		break;
	default:
		battleMonster(player, targetX, targetY);

	}


}

void level::processzombiesMove(Player& player, int zombiesIndex, int targetX, int targetY) {
	int playerX;
	int playerY;
	int zombiesX;
	int zombiesY;

	_enemies[zombiesIndex].getPosition(zombiesX, zombiesY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		_enemies[zombiesIndex].setPosition(targetX, targetY);
		setTile(zombiesX, zombiesY, '.');
		setTile(targetX, targetY, _enemies[zombiesIndex].getTile());
		break;
	case '@':
		battleMonster(player, zombiesX, zombiesY);
		break;
	case '#':
		break;
	default:
		break;
	}




}

void level::battleMonster(Player& player, int targetX, int targetY) {
	int zombiesX;
	int zombiesY;
	int attackRoll;
	int attackResult;
	int playerX;
	int playerY;
	string zombiesName;

	player.getPosition(playerX, playerY);


	for (int i = 0; i < _enemies.size(); i++) {
		_enemies[i].getPosition(zombiesX, zombiesY);
		zombiesName = _enemies[i].getName();
		if (targetX == zombiesX && targetY == zombiesY) {
			//battle
			attackRoll = player.attack();
			printf("\nPlayer attacked %s with a roll of: %d\n", zombiesName.c_str(), attackRoll);
			attackResult = _enemies[i].takeDamage(attackRoll);
			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print();
				printf("Monster died!\n");

				//Remove the zombies
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				//Pause bad habit :/
				system("PAUSE");
				player.addExperience(attackResult);



				return;
			}
			//Monster turn
			attackRoll = _enemies[i].attack();
			printf("%s attacked player with a roll of: %d\n", zombiesName.c_str(), attackRoll);

			attackResult = player.takeDamage(attackRoll);

			if (attackResult != 0) {

				setTile(playerX, playerY, 'X');
				printf("You died!\n");
				print();
				//Pause.
				system("PAUSE");

				exit(0);
				return;
			}
			//Pause.
			system("PAUSE");

			return;
		}

	}


}
//choose the level
string level::chooselevel() {

	int lvl;
	string Tlvl;
	cout << "Choose level (1/2/3) : ";
	cin >> lvl;
	
	if(lvl==1)
		Tlvl = "level1.txt";
	if(lvl == 2)
		Tlvl = "level2.txt";
	if(lvl == 3)
		Tlvl = "level3.txt";
	return Tlvl;
}