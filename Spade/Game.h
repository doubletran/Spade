#pragma once

#include <iostream>
#include<string.h>
#include<vector>
#include <cstdlib>
#include<time.h>
#include "Deck.h"
#include "Player.h"
#include "Round.h"
#include <iomanip>

using namespace std; 
struct Game
{
	Game();
	
	void setup(Player players[]);
	bool spadeBreak;
	int posPlayer;
};

