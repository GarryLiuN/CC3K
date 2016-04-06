CXX = g++
CXXFLAGS = -Wall -MMD -g -std=c++03
EXEC = cc3k
OBJECTS = cc3k.o controller.o game.o textdisplay.o object.o stair.o cell.o character.o player.o enemy.o buff.o buffdeco.o item.o potion.o treasure.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
