#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <map>
#include <stack>
#include <unordered_set>
#include <memory>
#include <random>
#include <queue>



class Maze
{
public:
    class Node
    {
        public:
            Node(size_t _id);
            Node(Node& n1);
            friend std::ostream& operator<<(std::ostream& os, const Maze::Node& n);
            void Update_availableDirections();
            void set_dir_flags(std::shared_ptr<Node> select);
            void search_children();
            void make_dir(std::stack<std::shared_ptr<Node>>&);
            bool visited = false;
            bool is_start = false;
            bool is_end = false;
            bool is_true_dir = false;
            std::pair<std::shared_ptr<Node>,int> North = {nullptr,0};
            std::pair<std::shared_ptr<Node>,int> South = {nullptr,0};
            std::pair<std::shared_ptr<Node>,int> East = {nullptr,0};
            std::pair<std::shared_ptr<Node>,int> West = {nullptr,0};
            std::vector<std::pair<std::shared_ptr<Node>,int>> availableDirections;
            std::shared_ptr<Node> parent{nullptr};
        private:
            size_t id;
    };
    Maze(size_t _row, size_t _col);
    double noONodes(){return row*col;};
    void show();
    void unvisiting();
    void solve_DFS();
    void solve_BFS();

private:
    std::vector<std::vector<std::shared_ptr<Node>>> Board;
    size_t row;
    size_t col;
    std::shared_ptr<Maze::Node> start{nullptr};
    std::shared_ptr<Maze::Node> end{nullptr};
    void Maze_Generator();
    static int Random_generator(size_t);
    void fill();
    void Add_neighbors();
    void set_margin();
    void Go_to_Generation(std::stack<std::shared_ptr<Node>>);
    void Go_deap(std::stack<std::shared_ptr<Node>>&);
    void Go_bread(std::stack<std::shared_ptr<Node>>&);
    void Add_walls();
    size_t visited_counter = 0;
};



#endif