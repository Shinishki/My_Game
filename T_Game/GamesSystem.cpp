#include "GamesSystem.h"
#include <iostream>
#include <conio.h>
using namespace std;

//constructor sets up the game
GamesSystem::GamesSystem(string levelFileName)
{
	_player.init(1, 100, 10, 10, 0);



	_level.loadlevel(levelFileName, _player);
	_level.print();
	//bad way to pause I should replace it 
	system("PAUSE");
}


void GamesSystem::playGame() {


	bool isDone = false;

	while (isDone != true) {
		_level.print();
		playerMove();
		_level.updateEnemies(_player);
	}

}
void GamesSystem::playerMove() {
	char input;
	printf("Enter a move command(w/s/a/d: ");

	//cool command to read single characters without having to press enter
	//Makes the character move instantly when pressing Key :|
	input = _getch();

	//taking the key pressed -> switch case
	_level.MovePlayer(input, _player);
}