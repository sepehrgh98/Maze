CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS = ./obj/Maze.o ./obj/MazeGUI.o ./obj/main.o 
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/Maze.o: ./cpp/Maze.cpp
	$(CXX) $(CXXFLAGS) ./cpp/Maze.cpp -o ./obj/Maze.o
./obj/MazeGUI.o: ./MazeGUI/mazegui.cpp
	$(CXX) $(CXXFLAGS) ./MazeGUI/mazegui.cpp -o ./obj/MazeGUI.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)