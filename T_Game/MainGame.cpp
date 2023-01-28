#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include "level.h"
#include "GamesSystem.h"
//Made with the help of tutorials

using namespace std;
level lvl;


int main() {

	string crt_lvl = lvl.chooselevel();

	GamesSystem GamesSystem(crt_lvl);

	GamesSystem.playGame();
}