spaceInvaders.o: *.cpp
	g++ -Wall -std=c++11 *.cpp -o spaceInvaders.o -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f spaceInvaders.o
