// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============        	 *** Header of Board class ***          ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include "window.h"

class Level;
class Square;

class Board {
	Level *level;
	int latestPoints;
	
	// Graphical display
	Xwindow *theWindow;

	bool bonus;
	
	// Helper for destructor
	void clearBoard( );

	// This method is used in conjuction with Board::fillVoids, which simply
	//		takes in a column, and shifts all values in that column to the 
	//		bottom most position, then fill the remaining void squares to 
	//		a new square based on the level.
	void shiftColumn(int column);
	
  public :

  	
  	bool graphical;
  	
	int windowSize;
	
	Square ***theBoard;
	int boardSize;	

	Board(Level *l, bool graphical, bool bonus);
	~Board( );

	// Initialize the grid
	void initializeGrid();

	// This method is used to execute the swap method on the board, where (x,y) are
	//		co-ordinates of the square and the direction represents which cell is 
	//		being swapped. (0 for north, 1 for south, 2 for west, and 3 for east).
	void swap(int x, int y, int direction);
	
	// This method is used to create a new special square when a match has been found
	//      on the board. To use this method, you must pass in a std::vector containing a
	//      set of squares that actually form a proper match. In return, this method
	//      will determine what type of square should be created, and return a pointer
	//      to that newly created square. To ensure it is placed in the proper place on
	//      board, simply check the r and c value of the square.
	Square *createSpecialSquare(std::vector<Square *> matched);

	// Finds all match groups on the board
	// Returns format: [ [s1, s2, s3], [s4, s5, s6, s7, s8], [s9, s10, s11], [s12, s13, s14, s15] ]
	// where s1, ... , s15 are all Square pointers
	std::vector<std::vector<Square *> > findMatchGroups();
	
	// Set the radius of all square's involved in matches longer than 3.
	void setRadius(std::vector<std::vector<Square *> > matchGroups);

	// Resolves all matches and chain reactions until board has no matches
	// Also increments the score
	void resolveMatches();

	// This method is used to fill all empty spots in the board after matches have 
	//		been found. The argument passed in is an array of integers that represent
	//		columns that have had squares removed.
	void fillVoids();

	// Checks if there are no matches ont he board in its current state
	bool matchExists( );


	// This method is used to execute the hint method on the board, which should
	//		return out a valid move (x,y,z).
	int *hint( );

	// Checks if there are no valid moves left, returns true if no moves left
	bool noMovesLeft( );

	// This method is called if there are no valid moves, and calls the scramble
	//		method on the board, mixing up all the current squares.
	void scramble( );

	// Returns the latest points
	int getLatestPoints( );

	// Draws the board graphical display
	void drawBoard();

	// Draws NULL squares on the board's graphical display
	void drawNull( int r, int c );

	// Draws borders for the selected square for keyboard graphical display
	void drawBorder(int colour, int x, int y);

	// Redraws the score on the graphical display
	void drawScore(int x);
	
	// Redraws the score to level on the graphical display
	void drawScoreToLevel(int x);

	// Prints the board to out (cout)
	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
