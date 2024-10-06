spaceInvaders.o: *
	g++ -Wall -std=c++11 *.cpp -o spaceInvaders.o -lsfml-graphics -lsfml-window -lsfml-system; ./spaceInvaders.o

clean:
	rm -f spaceInvaders.o
