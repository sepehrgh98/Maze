#ifndef MAZEGUI_H
#define MAZEGUI_H

#include <QMainWindow>
#include <iostream>
#include "ui_mazegui.h"
#include <QtGui>
#include <QtCore>
#include <QGraphicsRectItem>
#include <vector>
#include <unordered_map>
#include <stack>
#include <stdlib.h>
#include<time.h>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <queue>



QT_BEGIN_NAMESPACE
namespace Ui { class MazeGUI; }
QT_END_NAMESPACE

class MazeGUI : public QMainWindow
{
    Q_OBJECT

public:
    class Node
    {
    public:
        Node(size_t _id);
        QGraphicsItemGroup* recGroup;
        QGraphicsItemGroup* mainNode;
        QGraphicsItemGroup* top;
        QGraphicsItemGroup* right;
        QGraphicsItemGroup* left;
        QGraphicsItemGroup* down;
        bool visited = false;
        bool is_start = false;
        bool is_end = false;
        bool is_true_dir = false;

        std::vector<std::pair<std::shared_ptr<Node>,int>> availableDirections;
        std::unordered_map<const char*,std::pair<std::shared_ptr<Node>,int>> Directions{
            {"North" , std::pair<std::shared_ptr<Node>,int>{nullptr,0}},
            {"South" , std::pair<std::shared_ptr<Node>,int>{nullptr,0}},
            {"East" , std::pair<std::shared_ptr<Node>,int>{nullptr,0}},
            {"West" , std::pair<std::shared_ptr<Node>,int>{nullptr,0}}
        };
        void Update_availableDirections();
        void set_dir_flags(std::shared_ptr<Node> select);
        QGraphicsEllipseItem * Me;
        std::shared_ptr<Node> parent{nullptr};
        size_t id;

    private:

    };
    MazeGUI(QWidget *parent = nullptr);
    ~MazeGUI();
    void unvisiting();
    long fibo(unsigned n);

private:
    Ui::MazeGUI *ui;
    static inline QGraphicsItemGroup* GMaze;
    QGraphicsScene* scene{nullptr};
    std::vector<std::vector<std::shared_ptr<Node>>> Board;
    int row;
    int col;
    std::shared_ptr<MazeGUI::Node> start{nullptr};
    std::shared_ptr<MazeGUI::Node> end{nullptr};
    QGraphicsEllipseItem* Qstart;
    QGraphicsEllipseItem* Qend;
    void fill();
    void set_margin();
    void Add_neighbors();
    void Maze_Generator();
    void Go_to_Generation(std::stack<std::shared_ptr<Node>>);
    static int Random_generator(size_t);
    void Add_walls();
    void paint_walls();
    void clear();
    void make_dir(std::stack<std::shared_ptr<Node>>&, std::shared_ptr<Node>);
    char DFS_or_BFS;
    int visited_counter = 0;

    std::stack<std::shared_ptr<Node>> True_Dir;
    std::queue<std::shared_ptr<Node>> frontier;



private slots:
    void generatebtnPressed();
    void clearbtnPressed();
    void DFSbtnPressed();
    void BFSbtnPressed();
    void nextbtnPressed();
//    void prebtnPressed();
};
#endif // MAZEGUI_H