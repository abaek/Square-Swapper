// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// =============== *** Implementation of PsychedelicSquare class ***===============
// ===============                                                  ===============
// ================================================================================

#include <vector>
#include <cstdlib>
#include "psychedelicsquare.h"
#include "board.h"

using namespace std;

// This is the default constructor for the lateral square.
PsychedelicSquare::PsychedelicSquare( char colour, bool locked, char type) : 
															Square(colour, locked, type) {}

// This is the default destructor for the upright square.
PsychedelicSquare::~PsychedelicSquare( ) {
	
}

// This method is used to return all the Squares that need to be resolved alongside
//		the unstable Square.
vector<Square *> PsychedelicSquare::clearSquare( ) {
	vector<Square *> v;
	// This for loop is used to find all the squares on the board that are the same
	//		colour as the psychedelic square.
	int thisColour = this->getColour( );
	Square ***board = (this->currentBoard)->theBoard;
	int boardSize = (this->currentBoard)->boardSize;
	// Increased power resolution, which occurs when psychedelic square involved in match of 5.
	if ( radius == 5 ) {
		// Randomly chooses another colour (could be itself), and explodes it too.
		int randColour = rand( ) % colourCount;
		for ( int row = 0; row < boardSize; row++ ) {
			for (int col = 0; col < boardSize; col++ ) {
				if (( thisColour == (board[row][col]->getColour( ))) || ( randColour == (board[row][col]->getColour( )))) {
					v.push_back(board[row][col]);
				}
			}
		}
	// Easter egg resoluton, which occurs when psychedelic square involved in match of 6+
	} else if ( radius == 6 ) {
		// Explodes the entire board.
		for ( int row = 0; row < boardSize; row++ ) {
			for ( int col = 0; col < boardSize; col++ ) {
				v.push_back(board[row][col]);
			}
		}
	} else {
		// Search through the entire board and find all squares that match the current colour.
		for ( int row = 0; row < boardSize; row++ ) {
			for ( int col = 0; col < boardSize; col++ ) {
				if ( thisColour == (board[row][col]->getColour( ))) {
					v.push_back(board[row][col]);
				}
			}
		}
	}
	return v;
}

// This method is used to draw the unique psychedelic Square
void PsychedelicSquare::draw() {
	Square::draw();
    int colourNum = 5; // Purple
    int graphicalWidth = currentBoard->windowSize;
    int boardSize = currentBoard->boardSize;
    int width = (graphicalWidth/boardSize - 6) / 3;
    int height = (graphicalWidth/boardSize - 6) / 3;
    int posX = (graphicalWidth/boardSize) * c + ( width ) + 3;
    int posY = (graphicalWidth/boardSize) * r + ( height ) + 3;
    window->fillRectangle(posX, posY, width, height, colourNum);
}

