// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============      *** Implementation of Board class ***       ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <sstream>
#include "board.h"
#include "square.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"
#include "tbombsquare.h"
#include "level.h"
#include "window.h"


using namespace std;

// Create an instance of Board with the level
Board::Board( Level *l , bool graphical, bool bonus) : level(l), latestPoints(0), bonus(bonus) {
	boardSize = level->getBoardSize();
    if (graphical) {
	this->graphical = true;
        theWindow = new Xwindow(500, 550);
        theWindow->fillRectangle(0, 0, 500, 550, 0); // white bottom
        theWindow->fillRectangle(0, 0, 500, 500, 4); // navy blue background

        theWindow->drawString(20, 520, "Square Swapper 5000");
        theWindow->drawString(200, 520, "Score: ");
        // Starting score 0
        drawScore(0);
        theWindow->drawString(200, 535, "To Level: ");
        drawScoreToLevel(level->getTargetScore());
        windowSize = 500;
    } else {
	   this->graphical = false;
    }
}


// This is the destructor for theBoard field inside board.
void Board::clearBoard( ) {
	for ( int row = 0; row < boardSize; row++ ) {
		for ( int column = 0; column < boardSize; column++ ) {
			// Delete each square if not NULL
			if ( theBoard[row][column]  != NULL ) {
                delete theBoard[row][column];
            }
		}
		// Delete the array which holds the pointer each square.
		delete [ ] theBoard[row];
	}
	// Delete the array which holds the pointers to the pointer to each square.
	delete [ ] theBoard;
}

Board::~Board( ) { 
	if ( theBoard != NULL ) {
        clearBoard();
	}
    if (level != NULL) {
		delete level;
	}
    if (theWindow != NULL) {
        delete theWindow;
    }
};

// Initialize the grid by calling the method from the level
void Board::initializeGrid() {
    theBoard = level->initializeBoard(this, theWindow);
}

// This method is used to determine if there are any matches on the board.
// MUST BE CALLED on a valid board (no NULL squares)
bool Board::matchExists( ) {
    bool foundMatch = false;
    // Iterate through rows
    for ( int row = 0; row < boardSize; row++ ) {
        // Iterate through first 8 positions in column
        for ( int column = 0; column < boardSize - 2; column++ ) {
            char colour1 = theBoard[row][column]->getColour();
            char colour2 = theBoard[row][column+1]->getColour();
            char colour3 = theBoard[row][column+2]->getColour();

            // Make sure not locked
            if ( (colour1 != 'l') && (colour2 != 'l') && (colour3 != 'l') ) {
				if ( (colour1 == colour2) && (colour1 == colour3) ) {
            	    foundMatch = true;
           	    	break;
           		}
            }
            
        }
        // If we already found a match break
        if ( foundMatch ) {
            break;
        }
    }

    // If no matches in rows, check for matches in columns
    if ( !foundMatch ) {
        // Iterate through columns
        for ( int column = 0; column < boardSize; column++ ) {
            // Iterate through first 8 positions in row
            for ( int row = 0; row < boardSize - 2; row++ ) {
                char colour1 = theBoard[row][column]->getColour();
                char colour2 = theBoard[row+1][column]->getColour();
                char colour3 = theBoard[row+2][column]->getColour();
                if ( (colour1 != 'l') && (colour2 != 'l') && (colour3 != 'l') ) {
	                if ( (colour1 == colour2) && (colour1 == colour3) ) {
	                    foundMatch = true;
	                    break;
	                }
	            }
            }
            // If we already found a match break
            if ( foundMatch ) {
                break;
            }
        }
    }
    return foundMatch;
}


// This method is used to execute the swap method on the board, where (x,y) are
//		co-ordinates of the square and the direction represents which cell is 
//		being swapped. (0 for north, 1 for south, 2 for west, and 3 for east).
void Board::swap(int x, int y, int direction) {
    bool invalidSwap = false;

    // Get position of other square
    int newX = x;
    int newY = y;
    if ( direction == 0 ) {
        newX--;
    } else if ( direction == 1 ) {
        newX++;
    } else if ( direction == 2 ) {
        newY--;
    } else if ( direction == 3 ) {
        newY++;
    }

    // If it is an invalid edge swap
    if (newX < 0 || newX > boardSize - 1 || newY < 0 || newY > boardSize - 1) {
        invalidSwap = true;
        cout << "Invalid swap: Can't swap towards edge" << endl;
    } 
    // If either piece is locked
    else if (theBoard[x][y]->locked || theBoard[newX][newY]->locked) {
        invalidSwap = true;
        cout << "Invalid swap: Piece locked" << endl;
    }
    // Actually swap
    else {
        Square *temp = theBoard[x][y];
        // Put new square into original position
        theBoard[x][y] = theBoard[newX][newY];
        theBoard[x][y]->setPosition(x, y);
        // Fill new position with old square
        theBoard[newX][newY] = temp;
        theBoard[newX][newY]->setPosition(newX, newY);

	    // If it does not make a match, swap back
	    if (!matchExists()) {
	        invalidSwap = true;
	        cout << "Invalid swap: No match made after swap" << endl;
	        // Swap back
	        Square *temp = theBoard[x][y];
	        // Put new square into original position
	        theBoard[x][y] = theBoard[newX][newY];
	        theBoard[x][y]->setPosition(x, y);
	        // Fill new position with old square
	        theBoard[newX][newY] = temp;
	        theBoard[newX][newY]->setPosition(newX, newY);
	    } else {
            if (graphical) {
                //draw the pieces
                theBoard[x][y]->draw();
                theBoard[newX][newY]->draw();
            }

        }

    }

    if (invalidSwap) {
        // Set latest swap to 0 points
        this->latestPoints = 0;
    }

    // Match created, resolve matches!!!
    else {
        resolveMatches( );
    }
}

// Finds all match groups on the board
// Returns format: [ [s1, s2, s3], [s4, s5, s6, s7, s8], [s9, s10, s11], [s12, s13, s14, s15] ]
// where s1, ... , s15 are all Square pointers
vector<vector<Square *> >Board::findMatchGroups() {
    // Keep track of all visited Squares
    bool visited[boardSize][boardSize];
    for (int i = 0; i < boardSize; i++ ) {
        for (int j = 0; j < boardSize; j++) {
            visited[i][j] = false;
        }
    }

    // Variable to build up return value
    vector<vector<Square *> > allMatches;
    // Loop through rows
    for (int i = 0; i < boardSize; i++) {
        // Loop through columns
        for (int j = 0; j < boardSize; j++) {
            // Build a new group of all same colour
            vector<Square *> newGroup;
            vector<Square *> toDo;
            // If not visited
            toDo.push_back(theBoard[i][j]);
            // While you have squares of the same colour, recurse on them
            while (toDo.size() > 0) {
                vector<Square *> nextToDo;
                // Loop through all toDo
                for (unsigned int k = 0; k < toDo.size(); k++) {
                    // If not visited
                    const bool is_in = visited[toDo[k]->r][toDo[k]->c];
                    if (!is_in) {
                        // Add to visited
                        visited[toDo[k]->r][toDo[k]->c] = true;
                        // Add to   matched
                        newGroup.push_back(toDo[k]);
                        
                        // Recurse
                        int row = toDo[k]->r;
                        int col = toDo[k]->c;
                        char type = theBoard[row][col]->getType( );
                        char origColour = theBoard[row][col]->getColour();

                        if ( type != 'l' ) {

                            // Check matches down
                            if (row <= boardSize-3) {
                                char rowCol1 =  theBoard[row+1][col]->getColour();
                                char rowCol2 =  theBoard[row+2][col]->getColour();

                                if ((origColour == rowCol1) && (origColour == rowCol2)) {
                                    // Add only if two squares to the down match
                                    nextToDo.push_back(theBoard[row+1][col]);
                                    nextToDo.push_back(theBoard[row+2][col]);
                                }
                            }
                            // Check matches right
                            if (col <= boardSize-3) {
                                char colCol1 =  theBoard[row][col+1]->getColour();
                                char colCol2 =  theBoard[row][col+2]->getColour();
                                if ((origColour == colCol1) && (origColour == colCol2)) {
                                    // Add only if two squares right match
                                    nextToDo.push_back(theBoard[row][col+1]);
                                    nextToDo.push_back(theBoard[row][col+2]);
                                }
                            }

                            // Check matches up
                            if (row >= 2) {
                                char rowCol1 =  theBoard[row-1][col]->getColour();
                                char rowCol2 =  theBoard[row-2][col]->getColour();

                                if ((origColour == rowCol1) && (origColour == rowCol2)) {
                                    // Add only if two squares to the up match
                                    nextToDo.push_back(theBoard[row-1][col]);
                                    nextToDo.push_back(theBoard[row-2][col]);
                                }
                            }

                            // Check matches left
                            if (col >= 2) {
                                char colCol1 =  theBoard[row][col-1]->getColour();
                                char colCol2 =  theBoard[row][col-2]->getColour();
                                if ((origColour == colCol1) && (origColour == colCol2)) {
                                    // Add only if two squares left match
                                    nextToDo.push_back(theBoard[row][col-1]);
                                    nextToDo.push_back(theBoard[row][col-2]);
                                }
                            }

                            // Check center matches vertically
                            if ( (row <= boardSize-2) && (row >= 1) ) {
                                char rowCol1 = theBoard[row-1][col]->getColour();
                                char rowCol2 = theBoard[row+1][col]->getColour();
                                if ((origColour == rowCol1) && (origColour == rowCol2)) {
                                    // Add only if two squares match vertically
                                    nextToDo.push_back(theBoard[row-1][col]);
                                    nextToDo.push_back(theBoard[row+1][col]);
                                }
                            }

                            // Check center matches horizontally
                            if ( (col <= boardSize-2) && (col >= 1) ) {
                                char colCol1 = theBoard[row][col-1]->getColour();
                                char colCol2 = theBoard[row][col+1]->getColour();
                                if ((origColour == colCol1) && (origColour == colCol2)) {
                                    // Add only if two squares match horizontally
                                    nextToDo.push_back(theBoard[row][col-1]);
                                    nextToDo.push_back(theBoard[row][col+1]);
                                }
                            }


                        }
                    }
                }
                // Set up next iteration
                toDo = nextToDo;
            }
            // Only add as an official group if size is >= 3
            if (newGroup.size() >= 3) {
                allMatches.push_back(newGroup);
            }
        }
    }


    return allMatches;
}

    
// This method is used to create a new special square when a match has been found
//      on the board. To use this method, you must pass in a vector containing a
//      set of squares that actually form a proper match. In return, this method
//      will determine what type of square should be created, and return a pointer
//      to that newly created square. To ensure it is placed in the proper place on
//      board, simply check the r and c value of the square.
Square *Board::createSpecialSquare(vector<Square *> matched) {
    char newColour = matched[0]->getColour( );
    // This if statement is to check if the match is a simple match of 3.
    if ( matched.size( ) == 3 ) {
        return NULL;
    // This if statement is to check if the match is a 4 sized match, and it will
    //      create the corresponding upright or lateral square.
    } else if ( matched.size( ) == 4 ) {
        // This checks if it is an upright match.
        if ( matched[0]->c == matched[1]->c ) {
            int end = boardSize;
            // This for loop finds the top most square in the match.
            for ( int pos = 0; pos < 4; pos++ ) {
                if ( matched[pos]->r < end ) {
                    end = matched[pos]->r;
                }
            }
            int newRow = end + 1 + (rand( ) % 2);
            int newCol = matched[0]->c;
            Square *newSquare = new UprightSquare(newColour);
            newSquare->setBoard(newRow, newCol, this, theWindow);

            return newSquare;
        // Otherwise, it is a lateral match.
        } else {
            int end = boardSize;
            // This for loop finds the left most square in the match.
            for ( int pos = 0; pos < 4; pos++ ) {
                if ( matched[pos]->c < end ) {
                    end = matched[pos]->c;
                }
            }
            int newRow = matched[0]->r;
            int newCol = end + 1 + (rand( ) % 2);
            Square *newSquare = new LateralSquare(newColour);
            newSquare->setBoard(newRow, newCol, this, theWindow);

            return newSquare;
        }
    // This condition occurs when there is a match greater than 5. That means,
    //      that there must be either a 'L' shaped match or a linear match of 5.
    } else  if ( matched.size( ) >= 5 ) {
        // This for loop is used to check if a there is a lateral linear match of 5.
        //      Finding the left most square of the match.
        bool lateralLinear = true;
        int lateralEnd = boardSize;
        for ( int pos = 0; pos < (matched.size( ) - 1); pos++ ) {
            if ( matched[pos]->r != matched[pos+1]->r ) {
                lateralLinear = false;
                break;
            }
            if ( matched[pos]->c < lateralEnd ) {
                lateralEnd = matched[pos]->c;
            }
        }
        // If the match is a lateral linear match, then create a psychedelic square
        //    in the center of the match.
        if ( lateralLinear ) {
            int newRow = matched[0]->r;
            int newCol = lateralEnd + 2;
            Square *newSquare = new PsychedelicSquare(newColour);
            newSquare->setBoard(newRow, newCol, this, theWindow);

            return newSquare;
        }
        // This for loop is used to check if there is an upright linear match of 5.
        //      Finding the top most square of the match. 
        bool uprightLinear = true;
        int uprightEnd = boardSize;
        for ( int pos = 0; pos < (matched.size( ) - 1); pos++ ) {
            if ( matched[pos]->c != matched[pos+1]->c ) {
                uprightLinear = false;
                break;
            }
            if ( matched[pos]->r < uprightEnd ) {
                uprightEnd = matched[pos]->r;
            }
        }
        // If the match is a upright linear match, then create a psychedelic square
        //    in the center of the match.
        if ( uprightLinear ) {
            int newRow = uprightEnd + 2;
            int newCol = matched[0]->c;
            Square *newSquare = new PsychedelicSquare(newColour);
            newSquare->setBoard(newRow, newCol, this, theWindow);

            return newSquare;
        }

        // At this point, if no match has been found, the match can either be a 'T' or a 'L'
        //    shaped match. Which means, we need to find the intersection of the bend to 
        //    create the appropriate special square.
        for ( unsigned int pos = 0; pos < matched.size( ); pos++ ) {
            bool rowMatch = false;
            bool colMatch = false;
            int row = matched[pos]->r;
            int col = matched[pos]->c;
            for ( unsigned int newPos = 0; newPos < matched.size( ); newPos++ ) {
                if ( ( matched[newPos]->r == row ) && ( matched[newPos]->c != col ) ) {
                    rowMatch = true;
                }
                if ( ( matched[newPos]->r != row ) && ( matched[newPos]->c == col ) ) {
                    colMatch = true;
                }
            }
            if ( rowMatch && colMatch ) {
                // The intersection piece has been found, now, determine if it is an 'L'
                //     or a 'T' shape
                int sides = 0;
                for ( unsigned int newPos = 0; newPos < matched.size( ); newPos++ ) {
                    int curRow = matched[newPos]->r;
                    int curCol = matched[newPos]->c;
                    if ( ( curRow == (row - 1) ) || ( curRow == (row + 1) ) || ( curCol == (col - 1) ) || ( curCol == (col + 1) ) ) {
                        sides += 1;
                    }
                }

                if ( ( sides > 2 ) && ( bonus ) ) {
                    Square *newSquare = new TBombSquare(newColour);
                    newSquare->setBoard(row, col, this, theWindow);
                    return newSquare;
                } else {
                    Square *newSquare = new UnstableSquare(newColour);
                    newSquare->setBoard(row, col, this, theWindow);
                    return newSquare;
                }
            }
        }
    }
    return NULL;
}

// Set the radius of all square's involved in matches longer than 3.
void Board::setRadius(vector<vector<Square *> > matchGroups) {
    for (unsigned int i = 0; i < matchGroups.size(); i++) {
        // If match group bigger than 4
        if (matchGroups[i].size() >= 4) {
            // Set the radius 
            for (unsigned int j = 0; j < matchGroups[i].size(); j++) {
                if ( ( matchGroups[i].size( ) == 5 ) && ( bonus ) ) {
                    // This occurs when a square is involved in a match of 5.
                    matchGroups[i][j]->setRadius(5);
                } else if ( ( matchGroups[i].size( ) > 5 ) && ( bonus ) ) {
                    // This is an easter egg for matches of 6 or more involving
                    //      special squares.
                    matchGroups[i][j]->setRadius(6);
                } else {
                    matchGroups[i][j]->setRadius(4);
                }
            }
        }
    }
}


// Resolves all matches and chain reactions until board has no matches
// Also increments the score
void Board::resolveMatches() {
    // Multiply by 2 for each chain reaction
    int scoreMultiplier = 1;
    int totalScore = 0;

    // Each chain reaction 
    // Always start while loop with filled board
    bool match = matchExists( );
    while ( match ) {

        vector<vector<Square *> > matchGroups = findMatchGroups();

        // Keeps track ALL squares each match group explodes (from special squares)
        // Length used to calculate score
        vector<vector<Square *> > finalMatchGroups = matchGroups; 

        // Keeps track of all visited square coordinates
        bool visited[boardSize][boardSize];
        for (int i = 0; i < boardSize; i++ ) {
            for (int j = 0; j < boardSize; j++) {
                visited[i][j] = false;
            }
        }
        // Initialize set visited with all coordates in matchGroups
        for (unsigned int i = 0; i < matchGroups.size(); i++) {
            for (unsigned int j = 0; j < matchGroups[i].size(); j++) {
                visited[matchGroups[i][j]->r][matchGroups[i][j]->c] = true;
            }
        }

        // Create a list of special squares for each match (initialized in their appropriate places)
        // Physically placed on the grid at the end of one chain reaction
        vector<Square *> specials;
        for (unsigned int i = 0; i < matchGroups.size(); i++) {
            Square * newSpecial = createSpecialSquare(matchGroups[i]);
            if (newSpecial != NULL) {
                specials.push_back(newSpecial);
            }
        }       

        // Set radius of all square's involved in matches longer than 3.
        setRadius(matchGroups);

        // Go through each group and resolve special squares
        for (unsigned int i = 0; i < matchGroups.size(); i++) {
            // Deep copy the match group
			vector<Square *> squaresLeft = matchGroups[i];
            // Loop through each coordinate left to do
            while (squaresLeft.size() > 0) {
                vector<Square *> newSquaresLeft;
                for (unsigned int j = 0; j < squaresLeft.size(); j++) {
                    // Square.resolve returns coordinates of all squares affected
                    vector<Square *> squaresAffected = squaresLeft[j]->clearSquare();
                    // Add all new squaresAffected if not visited already
                    for (unsigned int k = 0; k < squaresAffected.size(); k++) {
                        // Make sure square is not already visited
                        if (!visited[squaresAffected[k]->r][squaresAffected[k]->c]) {
                            // Add to count for points
                            finalMatchGroups[i].push_back(squaresAffected[k]);
                            // Add to next iteration of while loop to resolve other square
                            newSquaresLeft.push_back(squaresAffected[k]);
                            // Add to visited so we don't double count
                            visited[squaresAffected[k]->r][squaresAffected[k]->c] = true;;
                        }
                    }
                }
                // Resolve new squares to do
                squaresLeft = newSquaresLeft;
            }
        }

        // Scoring
        for (unsigned int i = 0; i < finalMatchGroups.size(); i++) {
            int sizeGroup = finalMatchGroups[i].size();
            int matchScore = 0;
            if (sizeGroup == 3) {
                matchScore = 3;
            } else if (sizeGroup == 4) {
                matchScore = 8;
            } else if (sizeGroup == 5) {
                matchScore = 15;
            } else if (sizeGroup > 5) {
                matchScore = 4 * sizeGroup;
            }
            // Add score of each match group
            totalScore += matchScore * scoreMultiplier;
        }

        // Double score multipler
        scoreMultiplier *= 2;

        // Delete all old squares
        for (unsigned int i = 0; i < finalMatchGroups.size(); i++) {
            for (unsigned int j = 0; j < finalMatchGroups[i].size(); j++) {
                if ( finalMatchGroups[i][j]->locked ) {
                    level->lockedSquares -= 1;
                }
                int row = finalMatchGroups[i][j]->r;
                int col = finalMatchGroups[i][j]->c;
                delete theBoard[row][col];

                //colour window black
                if (graphical) {
                    drawNull(row, col);    
                }
                
                theBoard[row][col] = NULL;
            }
        }

        // print board with NULLS
        cout << *this;

        // Insert special squares
        for (unsigned int i = 0; i < specials.size(); i++) {
            Square *newSpecial = specials[i];
            int row = newSpecial->r;
            int col = newSpecial->c;
            theBoard[row][col] = newSpecial;
            if (graphical) {
                theBoard[row][col]->draw();
            }
        }

        // Fill all voids
        fillVoids();
    
        // For next iteration of loop
        match = matchExists( );

        // print board again
        cout << *this;

    }

    // Add score
    this->latestPoints = totalScore;
}

// This method is used in conjuction with Board::fillVoids, which simply
//		takes in a column, and shifts all values in that column to the 
//		bottom most position, then fill the remaining void squares to 
//		a new square based on the level.
void Board::shiftColumn(int column) {
    int numToFill = 0;
    vector<int> lockedCoords = vector<int>();
    int firstNullPosition = 0;
    bool first = true;

    // Bottom up
    for (int i = boardSize-1; i >= 0; i--) {
        // If the position is NULL, find first non-NULL above it and swap
        if (theBoard[i][column] == NULL) {
            if (first) {
	    	first = false;
	 	    firstNullPosition = i;
	    }
	    bool foundSquareToFill = false;
            // Find first non-NULL square, that is not a wallsquare
            for (int j = i-1; j >= 0; j--) {
                if ((theBoard[j][column] != NULL) && (theBoard[j][column]->getType( ) != 'l')) {
                	if ( theBoard[j][column]->locked ) {
                        lockedCoords.push_back(j);
                    }
                    foundSquareToFill = true;
                    // Swap position j with position i
                    theBoard[i][column] = theBoard[j][column];
                    theBoard[i][column]->r = i;
                    theBoard[i][column]->locked = false;
                    // Set position above to NULL
                    theBoard[j][column] = NULL;
                    break;
                }
            }
            // If we couldn't find anything to fill it's place
            if (!foundSquareToFill) {
                numToFill = i+1;
                break;
            }
        }
    }

    // Draw it
    if (graphical) {
        for (int i = numToFill; i <= firstNullPosition; i++) {
            theBoard[i][column]->draw();
        }
        
    }

    // Create new Squares
    for (int i = (numToFill-1); i >= 0; i--) {
        if ( theBoard[i][column] == NULL ) {
            theBoard[i][column] = level->createSquare();
            theBoard[i][column]->setBoard(i, column, this, theWindow);
            if (graphical) {
                theBoard[i][column]->draw();
            }
        }
    }

    // Lastly, reset all locked co-ordinates to their original position.
    for ( unsigned int pos = 0; pos < lockedCoords.size( ); pos++) {
        int row = lockedCoords[pos];
        theBoard[row][column]->locked = true;
        if (graphical) {
            theBoard[row][column]->draw();    
        }
    }

}

// This method is used to fill all empty spots in the board after matches have 
//		been found. The argument passed in is an array of integers that represent
//		columns that have had squares removed.
void Board::fillVoids() {
	// This is the default value for the method, which will check each column.
	for ( int column = 0; column < boardSize; column++ ) {
		shiftColumn(column);
	}
}

// This method is used to determine if there are any more moves left on the board.
//		Similarly, if there are no more moves on the board, then there must not be 
//		any valid hint.
bool Board::noMovesLeft( ) {
    int *coords = hint( );
    if ( coords[0] != -1 ) {
        delete coords;
    	return false;
    } else {
        delete coords;
    	return true;
    }
}

// Returns the points for the latest match
int Board::getLatestPoints( ) {
	return latestPoints;
}

// This method is used to execute the hint method on the board, which should
//      return out a valid move (x,y,z).
int *Board::hint( ) {
    
    int x, y, z = -1;

    // This nested for loop is to check each individual square, starting at the top
    //      left corner.
    for ( int row = 0; row < boardSize; row++ ) {
        bool matchFound = false;

        for ( int column = 0; column < boardSize; column++ ) {
            char colour = theBoard[row][column]->getColour( );
            bool lock = theBoard[row][column]->locked;

		    // These variables are to help determine which positions needs to be checked
			bool right = true;
            bool bottomRight = true;
            bool bottom = true;
            bool bottomLeft = true;
            
            if ( row == (boardSize - 2) ) {
                bottom = false;
            } else if ( row == (boardSize - 1) ) {
                bottom = false;
                bottomRight = false;
                bottomLeft = false;
            }

            if ( column == 0 ) {
                bottomLeft = false;
            } else if ( column == (boardSize - 2) ) {
                right = false;
            } else if ( column == (boardSize - 1) ) {
                right = false;
                bottomRight = false;
            }

            // Check if the current square is locked, if it is, only check the position
            //		 on the top and to the left of the current square to see if a match
            //		 can be made.
            if ( lock ) {
            	if ( right ) {
                	char rightColour = theBoard[row][column+2]->getColour( );
                	if ( colour == rightColour ) {
                    	char check;
                    	bool checkLeft = true;
                    	if ( column == 0 ) {
                    	    checkLeft = false;
                    	}

                    	if ( checkLeft ) {
                    	    check = theBoard[row][column-1]->getColour( );
                    	    if ( check == colour ) {
                    	        x = row;
                    	        y = column + 2;
                    	        z = 2;
                    	        matchFound = true;
                    	        break;
                    	    }
                    	}
                	}
                }

                if ( bottom ) {
                	char bottomColour = theBoard[row+2][column]->getColour( );
                	if ( colour == bottomColour ) {
                	    char check;
                	    bool checkTop = true;
                	    if ( row == 0 ) {
                	        checkTop = false;
                	    }

                    	if ( checkTop ) {
                    	    check = theBoard[row-1][column]->getColour( );
                    	    if ( check == colour ) {
                    	        x = row + 1;
                    	        y = column;
                    	        z = 0;
                    	        matchFound = true;
                    	        break;
                    	    }
                    	}
                	}
            	}

            // Executed when the current square is not locked and a comprehensive check
            //			is required.
            } else {	           

	            if ( right ) {
	                char rightColour = theBoard[row][column+2]->getColour( );
	                if ( colour == rightColour ) {
	                    char check;
	                    bool checkRight = true;
	                    bool checkLeft = true;
	                    if ( column == 0 ) {
	                        checkLeft = false;
	                    } else if ( column == (boardSize - 3) ) {
	                        checkRight = false;
	                    }

	                    if ( checkRight ) {
	                        check = theBoard[row][column+3]->getColour( );
	                        if ( check == colour ) {
	                            x = row;
	                            y = column;
	                            z = 3;
	                            matchFound = true;
	                            break;
	                        }
	                    }

	                    if ( checkLeft ) {
	                        check = theBoard[row][column-1]->getColour( );
	                        if ( check == colour ) {
	                            x = row;
	                            y = column + 2;
	                            z = 2;
	                            matchFound = true;
	                            break;
	                        }
	                    }
	                }
	            }

	            if ( bottomRight ) {
	                char bottomRightColour = theBoard[row+1][column+1]->getColour( );
	                if ( colour == bottomRightColour ) {
	                    char check;
	                    bool checkRight = true;
	                    bool checkBottom = true;
	                    if ( column == (boardSize - 2) ) {
	                        checkRight = false;
	                    }
	                    if ( row == (boardSize - 2) ) {
	                        checkBottom = false;
	                    }

	                    if ( checkRight ) {
	                        check = theBoard[row+1][column+2]->getColour( );
	                        if ( check == colour ) {
	                            x = row;
	                            y = column;
	                            z = 1;
	                            matchFound = true;
	                            break;
	                        }
	                    }

	                    if ( checkBottom ) {
	                        check = theBoard[row+2][column+1]->getColour( );
	                        if ( check == colour ) {
	                            x = row;
	                            y = column;
	                            z = 3;
	                            matchFound = true;
	                            break;
	                        }
	                    }
	                }
	            }

	            if ( bottom ) {
	                char bottomColour = theBoard[row+2][column]->getColour( );
	                if ( colour == bottomColour ) {
	                    char check;
	                    bool checkBottom = true;
	                    bool checkTop = true;
	                    if ( row == (boardSize - 3) ) {
	                        checkBottom = false;
	                    } else if ( row == 0 ) {
	                        checkTop = false;
	                    }

	                    if ( checkBottom ) {
	                        check = theBoard[row+3][column]->getColour( );
	                        if ( check == colour ) {
	                            x = row;
	                            y = column;
	                            z = 1;
	                            matchFound = true;
	                            break;
	                        }
	                    }

	                    if ( checkTop ) {
	                        check = theBoard[row-1][column]->getColour( );
	                        if ( check == colour ) {
	                            x = row + 1;
	                            y = column;
	                            z = 0;
	                            matchFound = true;
	                            break;
	                        }
	                    }
	                }
	            }

	            if ( bottomLeft ) {
	                char bottomLeftColour = theBoard[row+1][column-1]->getColour( );
	                if ( colour == bottomLeftColour ) {
	                    char check;
	                    bool checkBottom = true;
	                    bool checkLeft = true;
	                    if ( column == 1 ) {
	                        checkLeft = false;
	                    }
	                    if ( row == (boardSize - 2) ) {
	                        checkBottom = false;
	                    }

	                    if ( checkBottom ) {
	                        check = theBoard[row+2][column-1]->getColour( );
	                        if ( check == colour ) {
	                            x = row;
	                            y = column;
	                            z = 2;
	                            matchFound = true;
	                            break;
	                        }
	                    }

	                    if ( checkLeft ) {
	                        check = theBoard[row+1][column-2]->getColour( );
	                        if ( check == colour ) {
	                            x = row;
	                            y = column;
	                            z = 1;
	                            matchFound = true;
	                            break;
	                        }
	                    }
	                }
	            }

	            if ( right && bottomRight ) {
	                char rightColour = theBoard[row][column+2]->getColour( );
	                char bottomRightColour = theBoard[row+1][column+1]->getColour( );
	                if ( ( colour == rightColour ) && ( colour == bottomRightColour ) ) {
	                    x = row + 1;
	                    y = column + 1;
	                    z = 0;
	                    matchFound = true;
	                    break;
	                }
	            }

	            if ( bottomRight && bottom ) {
	                char bottomRightColour = theBoard[row+1][column+1]->getColour( );
	                char bottomColour = theBoard[row+2][column]->getColour( );
	                if ( ( colour == bottomColour ) && ( colour == bottomRightColour ) ) {
	                    x = row + 1;
	                    y = column + 1;
	                    z = 2;
	                    matchFound = true;
	                    break;
	                }
	            }

	            if ( bottom && bottomLeft ) {
	                char bottomColour = theBoard[row+2][column]->getColour( );
	                char bottomLeftColour = theBoard[row+1][column-1]->getColour( );
	                if ( ( colour == bottomColour ) && ( colour == bottomLeftColour ) ) {
	                    x = row + 1;
	                    y = column - 1;
	                    z = 3;
	                    matchFound = true;
	                    break;
	                }
	            }

        	    if ( bottomLeft && bottomRight ) {
        	        char bottomLeftColour = theBoard[row+1][column-1]->getColour( );
        	        char bottomRightColour = theBoard[row+1][column+1]->getColour( );
        	        if ( ( colour == bottomLeftColour ) && ( colour == bottomRightColour ) ) {
        	            x = row;
        	            y = column;
        	            z = 1;
        	            matchFound = true;
        	            break;
        	        }
    	        }
    	    }

    	    if ( matchFound ) {
    	        break;
    	    }
    	}
    }

    int *coords = new int[3];
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
	return coords;
}

// This method is called if there are no valid moves, and calls the scramble
//      method on the board, mixing up all the current squares.
void Board::scramble( ) {
    bool first = true;
    while (matchExists() || first) {
        first = false;
        // Swap 2 squares many times
        for ( int i = 0; i < 100; i++ ) {

            // Creats random integer between 0-9 inclusive
            int x1 = rand() % boardSize;
            int y1 = rand() % boardSize;

            if ( theBoard[x1][y1]->getType( ) == 'l' ) {
            	break;
            } 

            int x2 = rand() % boardSize;
            int y2 = rand() % boardSize;

			if ( theBoard[x2][y2]->getType( ) == 'l' ) {
            	break;
            }

            bool locked1 = theBoard[x1][y1]->locked;
            bool locked2 = theBoard[x2][y2]->locked;
            Square *temp = theBoard[x1][y1];
            theBoard[x1][y1] = theBoard[x2][y2];
            theBoard[x1][y1]->setPosition(x1, y1);
            theBoard[x1][y1]->locked = locked1;
            theBoard[x2][y2] = temp;
            theBoard[x2][y2]->setPosition(x2, y2);
            theBoard[x2][y2]->locked = locked2;

        }
    }
}

// Draws the board graphically
void Board::drawBoard() {
    for ( int row = 0; row < boardSize; row++ ) {
        for ( int column = 0; column < boardSize; column++ ) {
            theBoard[row][column]->draw();
        }
    }
}

// Draws a NULL at a position
void Board::drawNull(int r, int c) {
    int colourNum = 4;
    int width = windowSize/boardSize - 2;
    int height = windowSize/boardSize - 2;
    int posX = (windowSize/boardSize) * c + 1;
    int posY = (windowSize/boardSize) * r + 1;
    theWindow->fillRectangle(posX, posY, width, height, colourNum);
}

// Draws a border for the selected square
void Board::drawBorder(int colour, int x, int y) {
    if (theBoard[x][y] != NULL) {
        // fill background
        int width = windowSize/boardSize;
        int height = windowSize/boardSize;
        int posX = (windowSize/boardSize) * y;
        int posY = (windowSize/boardSize) * x;
        theWindow->fillRectangle(posX, posY, width, height, colour);
        // draw new square on top 
        theBoard[x][y]->draw();
    }

}

// Draws the score
void Board::drawScore(int score) {
    if (graphical) {
        string Result;          // string which will contain the result
        ostringstream convert;   // stream used for the conversion
        convert << score;      // insert the textual representation of 'Number' in the characters in the stream
        Result = convert.str(); // set 'Result' to the contents of the stream
        theWindow->fillRectangle(255, 510, 100, 15, 0);
        theWindow->drawString(255, 520, Result.c_str());     
    }
}

// Draw the score to level
void Board::drawScoreToLevel(int score) {
    if (graphical) {
        string Result;              //String which will contain the result
        ostringstream convert;       // stream used for the conversion
        convert << score;            // insert the textual representation of 'Number' in the characters in the stream
        Result = convert.str();     // set 'Result' to the contents of the stream
        theWindow->fillRectangle(255, 530, 100, 25, 0);
        theWindow->drawString(255, 535, Result.c_str());

    }
}

// Prints the board
ostream &operator<< (ostream &out, const Board &b) {
    for (int i = 0; i < b.boardSize; i++ ) {
        out << "----"; 
    }
    out << "--" << endl;
    out << "   ";
    for (int i = 0; i < b.boardSize; i++) {
        if (i < 10) {
            out << " " << i << "  ";
        } else{
            out << " " << i << " ";
        }
    }
    out << endl;
    for (int i = 0; i < b.boardSize; i++ ) {
        out << "----"; 
    }
    out << "--" << endl;
	for ( int row = 0; row < b.boardSize; row++ ) {
        out << row << ": ";
		for ( int column = 0; column < b.boardSize; column++ ) {
			string display = "";
			Square *piece = b.theBoard[row][column];
            if (piece == NULL) {
                out << "NULL";
            }  else {
                bool locked = piece->locked;
                if ( locked ) {
                    display = display + "l";
                } else {
                    display = display + "_";
                }
                display = display + piece->getType();
                display = display + piece->getColour();
                if ( column == (b.boardSize - 1) ) {
                    out << display;
                } else {
                    out << display << " ";
                }
            }

		}
		out << endl;
	}
	return out;
}
