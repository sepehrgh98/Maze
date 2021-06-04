#include "Maze.h"

Maze::Node::Node(size_t _id)
    : id{_id}
{
    // std::cout << "Node " << id << " created!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Maze::Node& n)
{
    os << n.id;
    return os;
}


Maze::Maze(size_t _row, size_t _col)
    : row{_row}
    , col{_col}
{
    std::cout << "Maze constructor!" << std::endl;
    fill();
    set_margin();
    Add_neighbors();
    Maze_Generator();
}


void Maze::Node::set_dir_flags(std::shared_ptr<Node> select)
{
    if (North.first == select)
    {
        North.second = 1;
        ((North.first)->South).second = 1;
    }
    else if (South.first == select)
    {
        South.second = 1;
        ((South.first)->North).second = 1;
    }
    else if (East.first == select)
    {
        East.second = 1;
        ((East.first)->West).second = 1;
    }
    else
    {
        West.second = 1;
        ((West.first)->East).second = 1;
    }
}

void Maze::Node::Update_availableDirections()
{
    
    std::vector<std::pair<std::shared_ptr<Node>,int>>::iterator it;
    it = availableDirections.begin();
    for (size_t i = 0; i < availableDirections.size(); i++)
    {
        if (availableDirections[i].first->visited)
        {
            availableDirections.erase(it+i);
        }
    }
}

void Maze::Maze_Generator()
{
    std::stack<std::shared_ptr<Node>> myDirection;
    size_t start_row = Maze::Random_generator(row-1);
    size_t start_col = Maze::Random_generator(col-1);
    Board[start_row][start_col]->is_start = true;
    start = Board[start_row][start_col];
    myDirection.push(Board[start_row][start_col]);
    myDirection.top()->visited = true;
    visited_counter++;
    Go_to_Generation(myDirection);
    Add_walls();
    unvisiting();
    find_end();
    unvisiting();
}

int Maze::Random_generator(size_t size)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, size);
    return dist(mt);
}

void Maze::Go_to_Generation(std::stack<std::shared_ptr<Node>> myDirection)
{
    myDirection.top()->Update_availableDirections();
    if (visited_counter < row*col)
    {
        if (!myDirection.top()->availableDirections.empty())
        {
            size_t mysize = (myDirection.top()->availableDirections).size();
            std::pair<std::shared_ptr<Node>,int> selected = make_pair(myDirection.top()->availableDirections[ Maze::Random_generator(mysize)].first,myDirection.top()->availableDirections[Maze::Random_generator(mysize)].second);
            selected.first->visited = true;
            visited_counter++;
            selected.first->Update_availableDirections();
            myDirection.top()->set_dir_flags(selected.first);
            myDirection.push(selected.first);
            myDirection.top()->Update_availableDirections();
            Go_to_Generation(myDirection);
        }
        else
        {
            myDirection.pop();
            myDirection.top()->Update_availableDirections();
            Go_to_Generation(myDirection);
        }
    }
    else
    {
        // myDirection.top()->is_end = true;
        // end = myDirection.top();
    }
}

void Maze::fill()
{
    for (size_t i = 0; i < row; i++)
    {
        std::vector<std::shared_ptr<Node>> temp;
        for (size_t j = 0; j < col; j++)
        {
            auto n{std::make_shared<Maze::Node>(i*col + j)};
            temp.push_back(n);
        }
        Board.push_back(temp);
    }
}

void Maze::Add_neighbors()
{
     for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            if (Board[i][j]->North.second != -1)
            {
                Board[i][j]->North.first = Board[i-1][j];
                Board[i][j]->availableDirections.push_back(Board[i][j]->North);
            }
            if (Board[i][j]->South.second != -1)
            {
                Board[i][j]->South.first = Board[i+1][j];
                Board[i][j]->availableDirections.push_back(Board[i][j]->South);
            }
            if (Board[i][j]->East.second != -1)
            {
                Board[i][j]->East.first = Board[i][j+1];
                Board[i][j]->availableDirections.push_back(Board[i][j]->East);
            }
            if (Board[i][j]->West.second != -1)
            {
                Board[i][j]->West.first = Board[i][j-1];
                Board[i][j]->availableDirections.push_back(Board[i][j]->West);
            }
        }
    }
}

void Maze::show()
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t k = 0; k < col; k++)
        {
            if ((Board[i][k]->North).second == -1)
               std::cout  <<  " ____";
            else 
                std::cout << "     ";
        }
       std::cout << std::endl;
       for (size_t j = 0; j < col; j++)
       {
            if ((Board[i][j]->West).second  == -1)
                std::cout << "| ";
            else
                std::cout << "  ";

            if (Board[i][j]->is_start)
                std::cout << " s ";
            else if (Board[i][j]->is_end)
                std::cout << " e ";
            else
            {
                if (Board[i][j]->visited)
                {
                    if (Board[i][j]->is_true_dir)
                        std::cout << " * ";
                    else
                        std::cout << " v ";

                }
                else
                    std::cout << "   ";
                // std::cout << "   ";

            }
            if (j == col -1)
                std::cout << " |";
            
       }
       std::cout << std::endl;
       if (i == row -1)
       {
        for (size_t k = 0; k < col; k++)
        {
            if ((Board[i][k]->South).second == -1)
               std::cout  <<  " ____";
            else 
                std::cout << "     ";
        }
       }
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void Maze::set_margin()
{
    for(auto N:Board.front())
    {
        (N->North).second = -1;
    }
    for(auto v:Board)
    {
        (v.front()->West).second = -1;
        (v.back()->East).second = -1;
    }
    for(auto N:Board.back())
    {
        (N->South).second = -1;
    }
}

void Maze::Add_walls()
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            if ((Board[i][j]->North).second == 0)
                (Board[i][j]->North).second = -1;
            if ((Board[i][j]->South).second == 0)
                (Board[i][j]->South).second = -1;
            if ((Board[i][j]->East).second == 0)
                (Board[i][j]->East).second = -1;
            if ((Board[i][j]->West).second == 0)
                (Board[i][j]->West).second = -1;
        }
    }

}

void Maze::unvisiting()
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            Board[i][j]->availableDirections.clear();
            Board[i][j]->visited = false;
            if (Board[i][j]->North.second != -1)
                Board[i][j]->availableDirections.push_back(Board[i][j]->North);
            if (Board[i][j]->South.second != -1)
                Board[i][j]->availableDirections.push_back(Board[i][j]->South);
            if (Board[i][j]->East.second != -1)
                Board[i][j]->availableDirections.push_back(Board[i][j]->East);
            if (Board[i][j]->West.second != -1)
                Board[i][j]->availableDirections.push_back(Board[i][j]->West);
        }
    }
}

void Maze::solve_DFS()
{
    std::stack<std::shared_ptr<Node>> True_Dir;
    start->visited = true;
    True_Dir.push(start);
    Go_deap(True_Dir);

    while (!True_Dir.empty()) {
        True_Dir.top()->is_true_dir = true;
        std::cout << *True_Dir.top();
        True_Dir.pop();
        if (!True_Dir.empty())
            std::cout << " -> ";
    }
    std::cout << std::endl;
}

void Maze::Go_deap(std::stack<std::shared_ptr<Node>>& True_Dir)
{
    if (True_Dir.top() != end)
    {
       if (!True_Dir.top()->availableDirections.empty())
        {
            size_t mysize = (True_Dir.top()->availableDirections).size();
            std::pair<std::shared_ptr<Node>,int> selected = make_pair(True_Dir.top()->availableDirections[ Maze::Random_generator(mysize)].first,True_Dir.top()->availableDirections[Maze::Random_generator(mysize)].second);
            selected.first->visited = true;
            selected.first->Update_availableDirections();
            True_Dir.push(selected.first);
            True_Dir.top()->Update_availableDirections();
            Go_deap(True_Dir);
        }
        else
        {
            True_Dir.pop();
            True_Dir.top()->Update_availableDirections();
            Go_deap(True_Dir);
        }
    }
    
}

void Maze::solve_BFS()
{
    std::queue<std::shared_ptr<Node>> frontier;
    frontier.push(start);
    while (frontier.front() != end)
    {
        frontier.front()->visited = true;
        frontier.front()->Update_availableDirections();
        std::shared_ptr<Node> p = frontier.front();
        frontier.pop();
        for(auto ch : p->availableDirections)
        {
            ch.first->parent = p;
            frontier.push(ch.first);
            frontier.front()->Update_availableDirections();
        }
    }
    std::stack<std::shared_ptr<Node>> short_dir;
    end->make_dir(short_dir);
    while (!short_dir.empty()) {
        short_dir.top()->is_true_dir = true;
        std::cout << *short_dir.top();
        short_dir.pop();
        if (!short_dir.empty())
            std::cout << " -> ";
    }
    std::cout << std::endl;
    
}

void Maze::Node::make_dir(std::stack<std::shared_ptr<Node>>& short_dir)
{
    if (parent != nullptr)
    {
        short_dir.push(parent);
        parent->make_dir(short_dir);
    }
    
}


void Maze::find_end()
{
    std::queue<std::shared_ptr<Node>> frontier;
    frontier.push(start);
    size_t visited_node_counter=0;
    while(visited_node_counter < row*col)
    {
        
        frontier.front()->visited = true;
        frontier.front()->Update_availableDirections();
        std::shared_ptr<Node> p = frontier.front();
        frontier.pop();
        for(auto ch : p->availableDirections)
        {
            ch.first->parent = p;
            frontier.push(ch.first);
            frontier.front()->Update_availableDirections();
        }
        visited_node_counter++;
        if (visited_node_counter == row*col/3)
        {
            end = p->availableDirections[Maze::Random_generator(p->availableDirections.size())].first;
            end->is_end = true;
            break;
        }
            
    }
}