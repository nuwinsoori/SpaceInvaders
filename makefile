# flags
CC = g++
CFLAGS = -Wall -std=c++11
SFMLFLAGS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

# source files
GAME_SRCS = Player.cpp specialEnemy.cpp powerUp.cpp main.cpp Enemy.cpp bullet.cpp Menu.cpp
TEST_SRCS = ./testFiles/test.cpp ./testFiles/testFuncs.cpp Player.cpp Enemy.cpp SpecialEnemy.cpp Bullet.cpp PowerUp.cpp

.PHONY: all
all: game

.PHONY: game
game: spaceInvaders.o
	./spaceInvaders.out

spaceInvaders.o: $(GAME_SRCS)
	$(CC) $(CFLAGS) $(GAME_SRCS) -o spaceInvaders.out $(SFMLFLAGS)

.PHONY: test
test: test.out
	./test.out

test.out: $(TEST_SRCS)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o test.out $(SFMLFLAGS)

.PHONY: clean
clean:
	rm -f spaceInvaders.o

.PHONY: testclean
testclean:
	rm -f test.out
