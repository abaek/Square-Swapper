// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============       	 *** Header of Player class ***          ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>

class Board;
class Level;

class Player {
	int seed;
	std::string configFile;
	// Field for current level.
	int level;
	// Field for whether game is played with graphical version.
	bool graphical;
	// Field for whether game is played with bonus features.
	bool bonus;
	// Field for total levels created for the game.
	int totalLevels;

	// Pointer to the current board being played on.
	Board *currentBoard;
	// Pointer to the current level that is being played on.
	Level *currentLevel;
	// Field for total score obtained in the game thus far.
	int score;
	
  public :
  	// Field for the name of the player.
  	std::string name;

	Player( );
	~Player( );
	
	// This is the setter method for the seed field.
	void setSeed(int seed);
	
	// This is the setter method for the configFile field.
	void setConfigFile(std::string configFile);
	
	// This is the setter method for the level field for the -startlevel option.
	void setLevel(int level);
	
	// This is the setter method for the level field for the levelup command.
	void levelUp();
	
	// This is the setter method for the level field for the leveldown command.
	void levelDown();
	
	// This is the setter method for the graphical field for the -text option.
	void setGraphical(bool cmd);

	// This is the setter method for the bonus field for the -nobonus option.
	void setBonus(bool cmd);
	
	// This method is used to start the game, based on the seed, configFile, and level
	//		fields inside the Player object.
	void restart( );
	
	// This method is used to execute the swap method on the board, where (x,y) are
	//		co-ordinates of the square and the direction represents which cell is 
	//		being swapped. (0 for north, 1 for south, 2 for west, and 3 for east).
	void swap(int x, int y, int direction);
	
	// This method is used to execute the hint method on the board, which should
	//		print out a valid move (x,y,z) to the standard output.
	void hint( );
	
	// This method is used to check whether or not there are any valids moves left
	//		on the board.
	bool validScramble( );

	// Checks if there are no matches ont he board in its current state
	bool matchExists( );
		
	// This method is called if there are no valid moves, and calls the scramble
	//		method on the board, mixing up all the current squares.
	void scramble( );

	// This method is called to print the board.
	void printBoard( );

	// This method is called to print the graphical of the board.
	void printGraphical();

	// This method is used as a helper for print graphical, and is used to draw each square.
	void drawBorder(int colour, int x, int y);
};

#endif
