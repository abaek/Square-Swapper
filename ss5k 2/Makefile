CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = ss5k -lX11 -lncurses
OBJECTS = main.o window.o player.o board.o level.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o square.o basicsquare.o lateralsquare.o uprightsquare.o unstablesquare.o psychedelicsquare.o tbombsquare.o wallsquare.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	 rm ${OBJECTS} ${EXEC} ${DEPENDS}
