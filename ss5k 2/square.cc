// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============      *** Implementation of Square class ***      ===============
// ===============                                                  ===============
// ================================================================================

#include "square.h"
#include "window.h"
#include "board.h"

using namespace std;

// The constructor for the Square 
Square::Square( char colour, bool locked, char type, int radius, int colourCount) : 
                    type(type), colour(colour), radius(radius), colourCount(colourCount), locked(locked){}

// This is the default constructor for the Square class.
Square::~Square( ) { 
	// delete [ ] neighbours;
} 


// Getter for the private type field
char Square::getType( ) {
	return type;
}

// Getter for the private type field
char Square::getColour( ) {
	return colour;
}

// Setter for the r, c, and board field.
void Square::setBoard(int row, int col, Board *b, Xwindow *w) {
    r = row;
    c = col;
    currentBoard = b;
    window = w;
}

// Set r and c
void Square::setPosition(int row, int col) {
    r = row;
    c = col;
}

// Setter for the radius field.
void Square::setRadius(int n) {
    radius = n;
}

// This method is used to draw the unique psychedelic Square
void Square::draw() {
    int colourNum = colour - '0';
    int graphicalWidth = currentBoard->windowSize;
    int boardSize = currentBoard->boardSize;
    int width = graphicalWidth/boardSize - 6;
    int height = graphicalWidth/boardSize - 6;
    int posX = (graphicalWidth/boardSize) * c + 3;
    int posY = (graphicalWidth/boardSize) * r + 3;
    window->fillRectangle(posX, posY, width, height, colourNum);

    if (locked) {
        width = 2;
        height = graphicalWidth/boardSize - 6;
        posY = (graphicalWidth/boardSize) * r + 3;
        int widthInc = 3;
        while (widthInc < ((graphicalWidth/boardSize) - 10)) {
            int posX = ((graphicalWidth/boardSize) * c) + 3 + widthInc;
            widthInc += 5;
            window->fillRectangle(posX, posY, width, height, 8); // gray
        }

    }
}

// This method is used to determine if the current square is further left or above then the other square.
bool Square::operator<(const Square& s) const 
{
    if (r < s.r) {
        return true;
    } else if (r > s.r) {
        return false;
    } else {
        return c < s.c;
    }
}


