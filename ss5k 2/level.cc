// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============       *** Implementation of Level class ***      ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <cstdlib>
#include <string>
#include "level.h"

using namespace std;

// This is the constructor for the Level class, which should create the 
//		corresponding board objects.
Level::Level(int seed, string configFile, bool graphical, bool bonus) : seed(seed), graphical(graphical), bonus(bonus) {
	//set seed
	srand(seed);
	// Set lockedsquares to empty
	lockedSquares = 0;

	// If from a file, set ifstream and set current file pos to 0
	fileName = configFile;
	fileInputPos = 0;
}

// This is the destructor for the level class.
Level::~Level( ) { }
