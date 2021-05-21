#include "mazegui.h"
#include "ui_mazegui.h"




MazeGUI::Node::Node(size_t _id)
    : id{_id}
{
//     std::cout << "Node " << id << " created!" << std::endl;
     QBrush cyanBrush(Qt::cyan);
     QPen cyanPen(Qt::cyan);
     cyanPen.setWidth(0);

     MazeGUI::GMaze = new QGraphicsItemGroup();
     recGroup = new QGraphicsItemGroup(MazeGUI::GMaze);
     mainNode = new QGraphicsItemGroup(recGroup);
     QGraphicsRectItem *mainBox = new QGraphicsRectItem(QRectF(-10,-10,20,20),mainNode);
     mainBox->setBrush(cyanBrush);
     mainBox->setPen(cyanPen);
}

MazeGUI::MazeGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MazeGUI)
{
    ui->setupUi(this);

    //rowSpinBox
    ui->rowspinBox->setRange(3,30);

    //colSpinBox
    ui->colspinBox->setRange(3,30);

    //generatebtn
    connect(ui->generatebtn, SIGNAL(released()), this, SLOT(generatebtnPressed()));

    //clear
    ui->clearbtn->setEnabled(false);
    connect(ui->clearbtn, SIGNAL(released()), this, SLOT(clearbtnPressed()));

    //DFSbtn
    ui->BFSbtn->setEnabled(false);
    connect(ui->BFSbtn, SIGNAL(released()), this, SLOT(BFSbtnPressed()));


    //BFSbtn
    ui->DFSbtn->setEnabled(false);
    connect(ui->DFSbtn, SIGNAL(released()), this, SLOT(DFSbtnPressed()));

    //nextbtn
    ui->nextstepbtn->setEnabled(false);
    connect(ui->nextstepbtn, SIGNAL(released()), this, SLOT(nextbtnPressed()));

    //prebtn
    ui->prestepbtn->setEnabled(false);
}

MazeGUI::~MazeGUI()
{
    delete ui;
}

void MazeGUI::clear()
{
    for (int16_t i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            for(auto ch: Board[i][j]->mainNode->childItems())
            {
                delete ch;
            }
            delete Board[i][j]->mainNode;
            for(auto ch: Board[i][j]->top->childItems())
            {
                delete ch;
            }
            delete Board[i][j]->top;
            for(auto ch: Board[i][j]->down->childItems())
            {
                delete ch;
            }
            delete Board[i][j]->down;
            for(auto ch: Board[i][j]->right->childItems())
            {
                delete ch;
            }
            delete Board[i][j]->right;
            for(auto ch: Board[i][j]->left->childItems())
            {
                delete ch;
            }
            delete Board[i][j]->left;
            delete Board[i][j]->recGroup;
            Board[i][j] = nullptr;
        }
    }
    delete Qstart;
    delete Qend;
    visited_counter=0;
    Board.clear();
    scene->clear();
//    delete scene;
    ui->graphicsView->update();
}

void MazeGUI::generatebtnPressed()
{
    std::cout << "generation" << std::endl;
    //graphical view
    scene = new QGraphicsScene(this);
    scene->addLine(-447,0,447,0,QPen(Qt::blue));
    scene->addLine(0,-260,0,260,QPen(Qt::blue));
    ui->graphicsView->setScene(scene);
    row = ui->rowspinBox->value();
    col = ui->colspinBox->value();
    fill();
    set_margin();
    Add_neighbors();
    Maze_Generator();
    ui->clearbtn->setEnabled(true);
    ui->generatebtn->setEnabled(false);
    ui->BFSbtn->setEnabled(true);
    ui->DFSbtn->setEnabled(true);
}

void MazeGUI::clearbtnPressed()
{
    clear();
    ui->generatebtn->setEnabled(true);
    ui->clearbtn->setEnabled(false);
}

void MazeGUI::DFSbtnPressed()
{
    DFS_or_BFS = 'd';
    ui->BFSbtn->setEnabled(false);
    unvisiting();
    QBrush whiteBrush(Qt::white);
    QPen whitePen(Qt::white);
    whitePen.setWidth(0);
    start->Me = new QGraphicsEllipseItem(start->recGroup->pos().rx()-5,start->recGroup->pos().ry()-5,10,10);
    start->Me->setBrush(whiteBrush);
    start->Me->setPen(whitePen);
    scene->addItem(start->Me);
    ui->nextstepbtn->setEnabled(true);
    start->visited = true;
    True_Dir.push(start);
}


void MazeGUI::nextbtnPressed()
{
    QBrush whiteBrush(Qt::white);
    QPen whitePen(Qt::white);
    whitePen.setWidth(0);
    QBrush cyanBrush(Qt::cyan);
    QPen blackPen(Qt::black);
    blackPen.setWidth(0);

    if(DFS_or_BFS == 'd'){
        if (True_Dir.top() != end)
        {
               if (!True_Dir.top()->availableDirections.empty())
                {
                    size_t mysize = (True_Dir.top()->availableDirections).size();
                    std::pair<std::shared_ptr<Node>,int> selected = make_pair(True_Dir.top()->availableDirections[ MazeGUI::Random_generator(mysize)].first,True_Dir.top()->availableDirections[MazeGUI::Random_generator(mysize)].second);
                    selected.first->visited = true;
                    selected.first->Update_availableDirections();
                    selected.first->parent = True_Dir.top();
                    True_Dir.push(selected.first);
                    True_Dir.top()->Update_availableDirections();
                    True_Dir.top()->Me = new QGraphicsEllipseItem(True_Dir.top()->recGroup->pos().rx()-5,True_Dir.top()->recGroup->pos().ry()-5,10,10);
                    True_Dir.top()->Me->setBrush(whiteBrush);
                    True_Dir.top()->Me->setPen(whitePen);
                    scene->addItem(True_Dir.top()->Me);


                }
                else
                {
                   True_Dir.top()->Me = new QGraphicsEllipseItem(True_Dir.top()->recGroup->pos().rx()-5,True_Dir.top()->recGroup->pos().ry()-5,10,10);
                   True_Dir.top()->Me->setBrush(cyanBrush);
                   True_Dir.top()->Me->setPen(blackPen);
                   scene->addItem(True_Dir.top()->Me);
                   True_Dir.pop();
                   True_Dir.top()->Update_availableDirections();

                }
        }else{

            ui->nextstepbtn->setEnabled(false);
            QGraphicsRectItem *Dir;
            while (!True_Dir.empty()) {
                True_Dir.top()->is_true_dir = true;
                if(True_Dir.top()->parent){
                    if((True_Dir.top()->Directions)["North"].first == True_Dir.top()->parent)
                    {
                        Dir = new QGraphicsRectItem(QRectF(True_Dir.top()->recGroup->pos().rx()-2.5,True_Dir.top()->recGroup->pos().ry()-25,5,30));
                    }else if((True_Dir.top()->Directions)["South"].first == True_Dir.top()->parent){
                        Dir = new QGraphicsRectItem(QRectF(True_Dir.top()->recGroup->pos().rx()-2.5,True_Dir.top()->recGroup->pos().ry(),5,30));
                    }else if((True_Dir.top()->Directions)["East"].first == True_Dir.top()->parent){
                        Dir = new QGraphicsRectItem(QRectF(True_Dir.top()->recGroup->pos().rx()-2.5,True_Dir.top()->recGroup->pos().ry()-2.5,30,5));
                    }else{
                        Dir = new QGraphicsRectItem(QRectF(True_Dir.top()->recGroup->pos().rx()-30,True_Dir.top()->recGroup->pos().ry()-2.5,30,5));
                    }
                    Dir->setBrush(whiteBrush);
                    Dir->setPen(whitePen);
                    scene->addItem(Dir);
                }
                True_Dir.pop();

            }
        }
    }else{
        if(frontier.front() != end)
        {
            frontier.front()->visited = true;
            frontier.front()->Update_availableDirections();
            std::shared_ptr<Node> p = frontier.front();

            p->Me = new QGraphicsEllipseItem(p->recGroup->pos().rx()-5,p->recGroup->pos().ry()-5,10,10);
            p->Me->setBrush(whiteBrush);
            p->Me->setPen(whitePen);
            scene->addItem(p->Me);
            frontier.pop();
            for(auto ch : p->availableDirections)
            {
                ch.first->parent = p;
                frontier.push(ch.first);
                frontier.front()->Update_availableDirections();
            }
        }else{
            frontier.front()->Me = new QGraphicsEllipseItem(frontier.front()->recGroup->pos().rx()-5,frontier.front()->recGroup->pos().ry()-5,10,10);
            frontier.front()->Me->setBrush(whiteBrush);
            frontier.front()->Me->setPen(whitePen);
            scene->addItem(frontier.front()->Me);
            std::stack<std::shared_ptr<Node>> short_dir;

            make_dir(short_dir,  end);

            QGraphicsRectItem *Dir;
            while (!short_dir.empty()) {
                short_dir.top()->is_true_dir = true;
                if(short_dir.top()->parent){
                    if((short_dir.top()->Directions)["North"].first == short_dir.top()->parent)
                    {
                        Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry()-25,5,30));
                    }else if((short_dir.top()->Directions)["South"].first == short_dir.top()->parent){
                        Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry(),5,30));
                    }else if((short_dir.top()->Directions)["East"].first == short_dir.top()->parent){
                        Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry()-2.5,30,5));
                    }else{
                        Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-30,short_dir.top()->recGroup->pos().ry()-2.5,30,5));
                    }
                    Dir->setBrush(whiteBrush);
                    Dir->setPen(whitePen);
                    scene->addItem(Dir);
                }
                short_dir.pop();
            }

        }
    }
}

void MazeGUI::BFSbtnPressed()
{
    ui->DFSbtn->setEnabled(false);
    DFS_or_BFS = 'b';
    unvisiting();
    QBrush whiteBrush(Qt::white);
    QPen whitePen(Qt::white);
    whitePen.setWidth(0);
    start->Me = new QGraphicsEllipseItem(start->recGroup->pos().rx()-5,start->recGroup->pos().ry()-5,10,10);
    start->Me->setBrush(whiteBrush);
    start->Me->setPen(whitePen);
    scene->addItem(start->Me);
    ui->nextstepbtn->setEnabled(true);
    start->visited = true;
    frontier.push(start);
}

void MazeGUI::fill()
{
    for (int16_t i = 0; i < row; i++)
    {
        std::vector<std::shared_ptr<Node>> temp;
        for (int j = 0; j < col; j++)
        {
            auto n{std::make_shared<MazeGUI::Node>(i*col + j)};
            n->recGroup->setPos(30*j-30,30*i-30);
            temp.push_back(n);
        }
        Board.push_back(temp);
    }
    MazeGUI::GMaze->setPos(0,0);
}

void MazeGUI::set_margin()
{
    for(auto N:Board.front())
    {
        (N->Directions)["North"].second = -1;
    }
    for(auto v:Board)
    {
        (v.front()->Directions)["West"].second = -1;
        (v.back()->Directions)["East"].second = -1;
    }
    for(auto N:Board.back())
    {
        (N->Directions)["South"].second = -1;
    }
}

void MazeGUI::Add_neighbors()
{
     for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {

            if ((Board[i][j]->Directions)["North"].second != -1)
            {
                (Board[i][j]->Directions)["North"].first = Board[i-1][j];
                Board[i][j]->availableDirections.push_back((Board[i][j]->Directions)["North"]);
            }
            if ((Board[i][j]->Directions)["South"].second != -1)
            {
                (Board[i][j]->Directions)["South"].first = Board[i+1][j];
                Board[i][j]->availableDirections.push_back((Board[i][j]->Directions)["South"]);
            }
            if ((Board[i][j]->Directions)["East"].second != -1)
            {
                (Board[i][j]->Directions)["East"].first = Board[i][j+1];
                Board[i][j]->availableDirections.push_back((Board[i][j]->Directions)["East"]);
            }
            if ((Board[i][j]->Directions)["West"].second != -1)
            {
                (Board[i][j]->Directions)["West"].first = Board[i][j-1];
                Board[i][j]->availableDirections.push_back((Board[i][j]->Directions)["West"]);
            }

        }
    }
}

void MazeGUI::Maze_Generator()
{
    std::stack<std::shared_ptr<Node>> myDirection;
    size_t start_row = MazeGUI::Random_generator(row-1);
    size_t start_col = MazeGUI::Random_generator(col-1);
    Board[start_row][start_col]->is_start = true;
    start = Board[start_row][start_col];
    myDirection.push(Board[start_row][start_col]);
    myDirection.top()->visited = true;
    visited_counter++;
    Go_to_Generation(myDirection);
    Add_walls();
    paint_walls();
}

int MazeGUI::Random_generator(size_t size)
{
//    std::random_device random_device; // create object for seeding
//    std::mt19937 engine{random_device()}; // create engine and seed it
//    std::uniform_int_distribution<> dist(0,size); // create distribution for integers with [1; 9] range
//    std::cout << dist(engine) << ", " << size << std::endl;
//    return dist(engine)-1;
    srand(time(NULL));
    int val = rand()%(size);
    std::cout << rand() << ", " << size << std::endl;
    return val;
//    auto tstart = std::chrono::high_resolution_clock::now();
//    std::time_t timenow = std::chrono::system_clock::to_time_t(tstart);
//    std::cout << timenow << ", " << size << std::endl;
//    return timenow%size;
//    uint64_t us = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
//    return us%size;
}

long MazeGUI::fibo(unsigned n)
{
    if(n < 2) return n;
    return fibo(n-1) + fibo(n-2);
}

void MazeGUI::Go_to_Generation(std::stack<std::shared_ptr<Node>> myDirection)
{
    myDirection.top()->Update_availableDirections();
    if (visited_counter < row*col)
    {
        if (!myDirection.top()->availableDirections.empty())
        {
            size_t mysize = (myDirection.top()->availableDirections).size();
            std::pair<std::shared_ptr<Node>,int> selected = make_pair(myDirection.top()->availableDirections[ MazeGUI::Random_generator(mysize)].first,myDirection.top()->availableDirections[MazeGUI::Random_generator(mysize)].second);
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
        myDirection.top()->is_end = true;
        end = myDirection.top();
    }
}

void MazeGUI::Node::Update_availableDirections()
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

void MazeGUI::Node::set_dir_flags(std::shared_ptr<Node> select)
{
    if (Directions["North"].first == select)
    {
        Directions["North"].second = 1;
        (((Directions["North"].first)->Directions)["South"]).second = 1;
    }
    else if (Directions["South"].first == select)
    {
        Directions["South"].second = 1;
        (((Directions["South"].first)->Directions)["North"]).second = 1;
    }
    else if (Directions["East"].first == select)
    {
        Directions["East"].second = 1;
        (((Directions["East"].first)->Directions)["West"]).second = 1;
    }
    else
    {
        Directions["West"].second = 1;
        (((Directions["West"].first)->Directions)["East"]).second = 1;
    }
}

void MazeGUI::Add_walls()
{

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {

            if (((Board[i][j]->Directions)["North"]).second == 0)
            {
                (Board[i][j]->Directions)["North"].second = -1;
            }

            if (((Board[i][j]->Directions)["South"]).second == 0)
            {
                (Board[i][j]->Directions)["South"].second = -1;
            }

            if (((Board[i][j]->Directions)["East"]).second == 0)
            {
                (Board[i][j]->Directions)["East"].second = -1;
            }

            if (((Board[i][j]->Directions)["West"]).second == 0)
            {
                (Board[i][j]->Directions)["West"].second = -1;
            }

        }
    }

}

void MazeGUI::paint_walls()
{
    QBrush cyanBrush(Qt::cyan);
    QPen cyanPen(Qt::cyan);
    cyanPen.setWidth(0);

    QBrush greenBrush(Qt::green);
    QPen greenPen(Qt::green);
    greenPen.setWidth(0);

    QBrush redBrush(Qt::red);
    QPen redPen(Qt::red);
    redPen.setWidth(0);

    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    blackPen.setWidth(0);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(Board[i][j]->is_start)
            {
              Qstart = new QGraphicsEllipseItem(Board[i][j]->recGroup->pos().rx()-8,Board[i][j]->recGroup->pos().ry()-8,16,16);
              Qstart->setBrush(redBrush);
              Qstart->setPen(redPen);
            }
            if(Board[i][j]->is_end)
            {
                Qend = new QGraphicsEllipseItem(Board[i][j]->recGroup->pos().rx()-8,Board[i][j]->recGroup->pos().ry()-8,16,16);
                Qend->setBrush(greenBrush);
                Qend->setPen(greenPen);
            }
            if((Board[i][j]->Directions)["North"].second == 1)
            {
                Board[i][j]->top = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *topBox = new QGraphicsRectItem(QRectF(-20,-15,40,5),Board[i][j]->top);
                topBox->setBrush(cyanBrush);
                topBox->setPen(cyanPen);
                Board[i][j]->top->setZValue(-1);
            }else if((Board[i][j]->Directions)["North"].second == -1)
            {
                Board[i][j]->top = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *topBox = new QGraphicsRectItem(QRectF(-20,-15,40,5),Board[i][j]->top);
                topBox->setBrush(blackBrush);
                topBox->setPen(blackPen);
                Board[i][j]->top->setZValue(1);
            }
            if((Board[i][j]->Directions)["South"].second == 1)
            {
                Board[i][j]->down = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *downtBox = new QGraphicsRectItem(QRectF(-20,10,40,5),Board[i][j]->down);
                downtBox->setBrush(cyanBrush);
                downtBox->setPen(cyanPen);
                Board[i][j]->down->setZValue(-1);
            }else if((Board[i][j]->Directions)["South"].second ==  -1)
            {
                Board[i][j]->down = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *downtBox = new QGraphicsRectItem(QRectF(-20,10,40,5),Board[i][j]->down);
                downtBox->setBrush(blackBrush);
                downtBox->setPen(blackPen);
                Board[i][j]->down->setZValue(2);
            }
            if((Board[i][j]->Directions)["East"].second == 1)
            {
                Board[i][j]->right = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *rightBox = new QGraphicsRectItem(QRectF(10,-20,5,40),Board[i][j]->right);
                rightBox->setBrush(cyanBrush);
                rightBox->setPen(cyanPen);
                Board[i][j]->right->setZValue(-1);
            }else if((Board[i][j]->Directions)["East"].second == -1)
            {
                Board[i][j]->right = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *rightBox = new QGraphicsRectItem(QRectF(10,-20,5,40),Board[i][j]->right);
                rightBox->setBrush(blackBrush);
                rightBox->setPen(blackPen);
                Board[i][j]->right->setZValue(1);
            }
            if((Board[i][j]->Directions)["West"].second == 1)
            {
                Board[i][j]->left = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *leftBox = new QGraphicsRectItem(QRectF(-15,-20,5,40),Board[i][j]->left);
                leftBox->setBrush(cyanBrush);
                leftBox->setPen(cyanPen);
                Board[i][j]->left->setZValue(-1);
            }else if((Board[i][j]->Directions)["West"].second == -1)
            {
                Board[i][j]->left = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *leftBox = new QGraphicsRectItem(QRectF(-15,-20,5,40),Board[i][j]->left);
                leftBox->setBrush(blackBrush);
                leftBox->setPen(blackPen);
                Board[i][j]->left->setZValue(1);
            }
            scene->addItem(Board[i][j]->recGroup);

        }
    }

    scene->addItem(Qstart);
    scene->addItem(Qend);
//    for (int i = 0; i < row; i++)
//    {
//        for (int j = 0; j < col; j++)
//        {
//            if((Board[i][j]->Directions)["North"].second == 1)
//            {
//                Board[i][j]->top = new QGraphicsItemGroup(Board[i][j]->recGroup);
//                QGraphicsRectItem *topBox = new QGraphicsRectItem(QRectF(-20,-15,40,5),Board[i][j]->top);
//                topBox->setBrush(cyanBrush);
//                topBox->setPen(cyanPen);
//                topBox->setZValue(-1);
//            }
//            if((Board[i][j]->Directions)["South"].second == 1)
//            {
//                Board[i][j]->down = new QGraphicsItemGroup(Board[i][j]->recGroup);
//                QGraphicsRectItem *downtBox = new QGraphicsRectItem(QRectF(-20,10,40,5),Board[i][j]->down);
//                downtBox->setBrush(cyanBrush);
//                downtBox->setPen(cyanPen);
//                downtBox->setZValue(-2);
//            }
//            if((Board[i][j]->Directions)["East"].second == 1)
//            {
//                Board[i][j]->right = new QGraphicsItemGroup(Board[i][j]->recGroup);
//                QGraphicsRectItem *rightBox = new QGraphicsRectItem(QRectF(10,-20,5,40),Board[i][j]->right);
//                rightBox->setBrush(cyanBrush);
//                rightBox->setPen(cyanPen);
//                rightBox->setZValue(-3);
//            }
//            if((Board[i][j]->Directions)["West"].second == 1)
//            {
//                Board[i][j]->left = new QGraphicsItemGroup(Board[i][j]->recGroup);
//                QGraphicsRectItem *leftBox = new QGraphicsRectItem(QRectF(-15,-20,5,40),Board[i][j]->left);
//                leftBox->setBrush(cyanBrush);
//                leftBox->setPen(cyanPen);
//                leftBox->setZValue(-4);
//            }
//            scene->addItem(Board[i][j]->recGroup);

//        }

//    }


//    for (int i = 0; i < row; i++)
//    {
//        for (int j = 0; j < col; j++)
//        {
//            if((Board[i][j]->Directions)["North"].second == -1)
//            {
//                Board[i][j]->top = new QGraphicsItemGroup(Board[i][j]->recGroup);
//                QGraphicsRectItem *topBox = new QGraphicsRectItem(QRectF(-20,-15,40,5),Board[i][j]->top);
//                topBox->setBrush(blackBrush);
//                topBox->setPen(blackPen);
//                topBox->setZValue(1);
//            }
//            if((Board[i][j]->Directions)["South"].second ==  -1)
//            {
//                Board[i][j]->down = new QGraphicsItemGroup(Board[i][j]->recGroup);
//                QGraphicsRectItem *downtBox = new QGraphicsRectItem(QRectF(-20,10,40,5),Board[i][j]->down);
//                downtBox->setBrush(blackBrush);
//                downtBox->setPen(blackPen);
//                downtBox->setZValue(2);
//            }
//            if((Board[i][j]->Directions)["East"].second == -1)
//            {
//                Board[i][j]->right = new QGraphicsItemGroup(Board[i][j]->recGroup);
//                QGraphicsRectItem *rightBox = new QGraphicsRectItem(QRectF(10,-20,5,40),Board[i][j]->right);
//                rightBox->setBrush(blackBrush);
//                rightBox->setPen(blackPen);
//                rightBox->setZValue(3);
//            }
//            if((Board[i][j]->Directions)["West"].second == -1)
//            {
//                Board[i][j]->left = new QGraphicsItemGroup(Board[i][j]->recGroup);
//                QGraphicsRectItem *leftBox = new QGraphicsRectItem(QRectF(-15,-20,5,40),Board[i][j]->left);
//                leftBox->setBrush(blackBrush);
//                leftBox->setPen(blackPen);
//                leftBox->setZValue(4);
//            }
//            scene->addItem(Board[i][j]->recGroup);
//        }

//    }
}

void MazeGUI::unvisiting()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Board[i][j]->availableDirections.clear();
            Board[i][j]->visited = false;
            if ((Board[i][j]->Directions)["North"].second != -1)
                Board[i][j]->availableDirections.push_back((Board[i][j]->Directions)["North"]);
            if ((Board[i][j]->Directions)["South"].second != -1)
                Board[i][j]->availableDirections.push_back((Board[i][j]->Directions)["South"]);
            if ((Board[i][j]->Directions)["East"].second != -1)
                Board[i][j]->availableDirections.push_back((Board[i][j]->Directions)["East"]);
            if ((Board[i][j]->Directions)["West"].second != -1)
                Board[i][j]->availableDirections.push_back((Board[i][j]->Directions)["West"]);
        }
    }
}

void MazeGUI::make_dir(std::stack<std::shared_ptr<Node>>& short_dir, std::shared_ptr<MazeGUI::Node> node)
{
     short_dir.push(node);
     if (node->parent != nullptr)
        make_dir(short_dir, node->parent);
//    if (parent != nullptr)
//    {
//        short_dir.push(parent);
//        parent->make_dir(short_dir);
//    }

}
