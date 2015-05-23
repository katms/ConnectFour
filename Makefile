build: main.cpp ConnectFour.o Tile.o
	g++ -Wall -std=c++11 $^ -o connectfour -lSDL2main -lSDL2 -lSDL2_image

ConnectFour.o: ConnectFour.cpp Tile.o
	g++ -Wall -std=c++11 -c $^ -o $@
	
Tile.o: Tile.cpp
	g++ -Wall -std=c++11 -c $^ -o $@
	
clean:
	rm -f *.o connectfour
