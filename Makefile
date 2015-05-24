CXX := g++
CXXFLAGS += -Wall -std=c++11
EXE := connectfour

build: main.cpp ConnectFour.o Tile.o
	$(CXX) $(CXXFLAGS) $^ -o $(EXE) -lSDL2main -lSDL2 -lSDL2_image

ConnectFour.o: ConnectFour.cpp ConnectFour.h Tile.o
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
Tile.o: Tile.cpp Tile.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm -f *.o $(EXE)
	
rebuild: clean build
