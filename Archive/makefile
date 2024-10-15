spaceInvaders.o: *
	g++ -Wall -std=c++11 Player.cpp specialEnemy.cpp powerUp.cpp main.cpp Enemy.cpp bullet.cpp Menu.cpp  -o spaceInvaders.o  -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system; ./spaceInvaders.o

clean:
	rm -f spaceInvaders.o

test:
	g++ -Wall -std=c++11 ./testFiles/test.cpp ./testFiles/testFuncs.cpp Player.cpp Enemy.cpp SpecialEnemy.cpp Bullet.cpp PowerUp.cpp -o test -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system; ./test