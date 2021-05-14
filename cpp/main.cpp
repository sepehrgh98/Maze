#include <iostream>
#include "Maze.h"

int main(int argc, char **argv)
{
    std::cout << "RUNNING ..." << std::endl;
    Maze m(10,10);
    // m.unvisiting();
    m.show();
    // m.solve_DFS();
    // m.solve_BFS();
    // m.show();
    return 0;
}