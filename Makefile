build: main.cpp ConnectFour.o
	g++ -Wall -std=c++11 $^ -o connectfour -lSDL2main -lSDL2 -lSDL2_image

ConnectFour.o: ConnectFour.cpp
	g++ -Wall -std=c++11 -c $^ -o $@
