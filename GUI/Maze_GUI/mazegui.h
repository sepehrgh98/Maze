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
#include <graphics_view_zoom.h>
#include <QPixmap>
#include <QThread>


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

        //class methods
        void Update_availableDirections();
        void Update_availableDirections_end();
        void set_dir_flags(std::shared_ptr<Node> select);

        //logical fields
        bool visited = false;
        bool end_visit = false;
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
        std::shared_ptr<Node> parent{nullptr};
        std::shared_ptr<Node> end_parent{nullptr};
        size_t id;

        //graphical fields
        QGraphicsItemGroup* recGroup;
        QGraphicsItemGroup* mainNode;
        QGraphicsItemGroup* top;
        QGraphicsItemGroup* right;
        QGraphicsItemGroup* left;
        QGraphicsItemGroup* down;
        QGraphicsEllipseItem * Me{nullptr};

    };
    //class methods
    MazeGUI(QWidget *parent = nullptr);
    ~MazeGUI();
    void unvisiting();


private:
    //class methods
    void fill();
    void set_margin();
    void Add_neighbors();
    void Maze_Generator();
    void Go_to_Generation(std::stack<std::shared_ptr<Node>>);
    void Add_walls();
    void paint_walls();
    void clear();
    void make_dir(std::stack<std::shared_ptr<Node>>&, std::shared_ptr<Node>,bool);
    void find_end();
    void find_bidirectional(std::queue<std::shared_ptr<Node>>&, bool end_path);
    void paint_dir(std::shared_ptr<Node>);

    //static methods
    static int Random_generator(size_t);

    //logical fields
    int row;
    int col;
    std::vector<std::vector<std::shared_ptr<Node>>> Board;
    std::shared_ptr<MazeGUI::Node> start{nullptr};
    std::shared_ptr<MazeGUI::Node> end{nullptr};
    char DFS_or_BFS_or_BS;
    int visited_counter = 0;
    size_t step{0};
    std::stack<std::shared_ptr<Node>> True_Dir;
    std::queue<std::shared_ptr<Node>> frontier;
    std::queue<std::shared_ptr<Node>> end_frontier;
    std::vector<std::shared_ptr<Node>> visitedNodes;

    //graphical fields
    Ui::MazeGUI *ui;
    static inline QGraphicsItemGroup* GMaze;
    QGraphicsScene* scene{nullptr};
    QGraphicsEllipseItem* Qstart;
    QGraphicsEllipseItem* Qend;
    std::vector<QGraphicsRectItem *> masir;

private slots:
    void generatebtnPressed();
    void clearbtnPressed();
    void gobtnPressed();
    void DFSbtnPressed();
    void BFSbtnPressed();
    void BSbtnPressed();
    void nextbtnPressed();
    void anotherbtnPressed();
    void onProgress( int i );
    void ProgressFinished();
};
#endif // MAZEGUI_H

class Thread : public QThread
{
    Q_OBJECT

    signals:
        void progress( int value );

    private:
        void run()
        {
            for(int i = 0; i <= 100; i++ )
            {
                emit progress( i );
                QThread::msleep(50);
            }
        }
};
