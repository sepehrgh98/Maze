#include "mazegui.h"
#include "ui_mazegui.h"




MazeGUI::Node::Node(size_t _id)
    : id{_id}
{
     QColor red(203,78,78);
     QBrush redBrush(red);
     QPen redPen(red);
     redPen.setWidth(0);
     MazeGUI::GMaze = new QGraphicsItemGroup();
     recGroup = new QGraphicsItemGroup(MazeGUI::GMaze);
     mainNode = new QGraphicsItemGroup(recGroup);
     QGraphicsRectItem *mainBox = new QGraphicsRectItem(QRectF(-10,-10,20,20),mainNode);
     mainBox->setBrush(redBrush);
     mainBox->setPen(redPen);
}

MazeGUI::MazeGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MazeGUI)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #70B67A;");
    ui->mainPage->setHidden(true);

    QPixmap pixmap(":/images/logo.png");
    ui->logoBox->setPixmap(pixmap);
    ui->logoBox->setScaledContents( true );
    ui->logoBox->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);


    Graphics_view_zoom* z = new Graphics_view_zoom(ui->graphicsView);
    z->set_modifiers(Qt::NoModifier);

    ui->controlBar->setHidden(true);
    ui->gobtn->setHidden(true);
    ui->logo2->setPixmap(pixmap);
    ui->logo2->setScaledContents( true );
    ui->logo2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->nextstepbtn->setHidden(true);
    ui->anotherwaybtn->setHidden(true);
    ui->steplabel->setHidden(true);
    ui->stepnumber->setHidden(true);

    ui->stepnumber->setText(QString::number(step));

    ui->levelBox->addItems(QStringList{"Easy","Normal","Hard"});
    ui->levelBox->setCurrentIndex(1);

    //gobtn
    connect(ui->gobtn, SIGNAL(released()), this, SLOT(gobtnPressed()));

    //rowSpinBox
    ui->rowspinBox->setRange(3,100);

    //colSpinBox
    ui->colspinBox->setRange(3,100);

    //generatebtn
    connect(ui->generatebtn, SIGNAL(released()), this, SLOT(generatebtnPressed()));

    //clear
    ui->clearbtn->setEnabled(false);
    ui->clearbtn->setHidden(true);
    connect(ui->clearbtn, SIGNAL(released()), this, SLOT(clearbtnPressed()));

    //DFSbtn
    connect(ui->BFSbtn, SIGNAL(released()), this, SLOT(BFSbtnPressed()));


    //BFSbtn
    connect(ui->DFSbtn, SIGNAL(released()), this, SLOT(DFSbtnPressed()));

    //BSbtn
    connect(ui->BSbtn, SIGNAL(released()), this, SLOT(BSbtnPressed()));

    //nextbtn
    connect(ui->nextstepbtn, SIGNAL(released()), this, SLOT(nextbtnPressed()));

    //anotherbtn
    connect(ui->anotherwaybtn, SIGNAL(released()), this, SLOT(anotherbtnPressed()));

}

void MazeGUI::onProgress( int i )
{
    ui->progressBar->setValue(i);
}

void MazeGUI::ProgressFinished()
{
    ui->welcomePage->setHidden(true);
    ui->mainPage->setHidden(false);
}

MazeGUI::~MazeGUI()
{
    delete ui;
}

void MazeGUI::clear()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(Board[i][j]->Me != nullptr)
            {
                delete Board[i][j]->Me;
            }

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

    //start
    delete Qstart;

    //end
    delete Qend;

    //clear masir
    if(!masir.empty())
    {
        for(auto& rec:masir)
            delete rec;
        masir.clear();
    }

    //clear scene
    scene->clear();

    //clear Board vector
    Board.clear();

    //clear visited_counter
    visited_counter=0;

    //update step
    step=0;
    ui->stepnumber->setText(QString::number(step));

    while (! frontier.empty())
        frontier.pop();

    while (! end_frontier.empty())
        end_frontier.pop();

    ui->graphicsView->update();
}

void MazeGUI::gobtnPressed()
{
    ui->controlBar->setHidden(false);
    ui->logoWidget->setHidden(true);
    ui->DFSbtn->setHidden(false);
    ui->DFSbtn->setEnabled(true);
    ui->BFSbtn->setHidden(false);
    ui->BFSbtn->setEnabled(true);
    ui->BSbtn->setHidden(false);
    ui->BSbtn->setEnabled(true);
    ui->steplabel->setHidden(true);
    ui->stepnumber->setHidden(true);
    ui->nextstepbtn->setHidden(true);
    ui->stepnumber->setText(QString::number(step));
}

void MazeGUI::anotherbtnPressed()
{
    for(auto& n:visitedNodes)
    {
        if(n->Me != nullptr)
        {
            delete n->Me;
            n->Me = nullptr;
        }


    }
    while (! frontier.empty())
        frontier.pop();

    while (! end_frontier.empty())
        end_frontier.pop();

    if(!masir.empty())
    {
        for(auto& rec:masir)
            delete rec;
        masir.clear();
    }

    step = 0;
    ui->stepnumber->setText(QString::number(step));
    ui->DFSbtn->setHidden(false);
    ui->DFSbtn->setEnabled(true);
    ui->BFSbtn->setHidden(false);
    ui->BFSbtn->setEnabled(true);
    ui->BSbtn->setHidden(false);
    ui->BSbtn->setEnabled(true);
    ui->steplabel->setHidden(true);
    ui->stepnumber->setHidden(true);
    ui->nextstepbtn->setHidden(true);
    ui->anotherwaybtn->setHidden(true);
    ui->HTSlabel->setText("How to Solve?");
}

void MazeGUI::generatebtnPressed()
{
    //graphical view
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    row = ui->rowspinBox->value();
    col = ui->colspinBox->value();
    fill();
    set_margin();
    Add_neighbors();
    Maze_Generator();
    ui->clearbtn->setEnabled(true);
    ui->clearbtn->setHidden(false);
    ui->generatebtn->setEnabled(false);
    ui->generatebtn->setHidden(true);
    ui->gobtn->setHidden(false);
}

void MazeGUI::clearbtnPressed()
{
    clear();
    ui->generatebtn->setEnabled(true);
    ui->generatebtn->setHidden(false);

    ui->clearbtn->setEnabled(false);
    ui->clearbtn->setHidden(true);

    ui->controlBar->setHidden(true);
    ui->logoWidget->setHidden(false);

    ui->gobtn->setHidden(true);
    ui->anotherwaybtn->setHidden(true);
}

void MazeGUI::DFSbtnPressed()
{
    QBrush whiteBrush(Qt::white);
    QPen whitePen(Qt::white);
    whitePen.setWidth(0);

    ui->HTSlabel->setText("DFS");
    DFS_or_BFS_or_BS = 'd';
    ui->BFSbtn->setEnabled(false);
    ui->BFSbtn->setHidden(true);
    ui->DFSbtn->setEnabled(false);
    ui->DFSbtn->setHidden(true);
    ui->BSbtn->setEnabled(false);
    ui->BSbtn->setHidden(true);
    ui->nextstepbtn->setHidden(false);
    ui->anotherwaybtn->setHidden(false);
    ui->steplabel->setHidden(false);
    ui->stepnumber->setHidden(false);

    unvisiting();
    visitedNodes.clear();

    start->Me = new QGraphicsEllipseItem(start->recGroup->pos().rx()-5,start->recGroup->pos().ry()-5,10,10);
    start->Me->setBrush(whiteBrush);
    start->Me->setPen(whitePen);
    scene->addItem(start->Me);
    ui->nextstepbtn->setEnabled(true);
    start->visited = true;
    visitedNodes.push_back(start);
    True_Dir.push(start);
}

void MazeGUI::nextbtnPressed()
{
    step++;
    ui->stepnumber->setText(QString::number(step));
    QBrush whiteBrush(Qt::white);
    QPen whitePen(Qt::white);
    whitePen.setWidth(0);
    QPen blackPen(Qt::black);
    blackPen.setWidth(0);
    QColor red(203,78,78);
    QBrush redBrush(red);

    if(DFS_or_BFS_or_BS == 'd'){
        if (True_Dir.top() != end)
        {
               if (!True_Dir.top()->availableDirections.empty())
                {
                    size_t mysize = (True_Dir.top()->availableDirections).size();
                    std::pair<std::shared_ptr<Node>,int> selected = make_pair(True_Dir.top()->availableDirections[ MazeGUI::Random_generator(mysize)].first,True_Dir.top()->availableDirections[MazeGUI::Random_generator(mysize)].second);
                    selected.first->visited = true;
                    visitedNodes.push_back(selected.first);
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
                   delete True_Dir.top()->Me;
                   True_Dir.top()->Me = new QGraphicsEllipseItem(True_Dir.top()->recGroup->pos().rx()-5,True_Dir.top()->recGroup->pos().ry()-5,10,10);
                   True_Dir.top()->Me->setBrush(redBrush);
                   True_Dir.top()->Me->setPen(whitePen);
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
                        masir.push_back(Dir);
                    }else if((True_Dir.top()->Directions)["South"].first == True_Dir.top()->parent){
                        Dir = new QGraphicsRectItem(QRectF(True_Dir.top()->recGroup->pos().rx()-2.5,True_Dir.top()->recGroup->pos().ry(),5,30));
                        masir.push_back(Dir);
                    }else if((True_Dir.top()->Directions)["East"].first == True_Dir.top()->parent){
                        Dir = new QGraphicsRectItem(QRectF(True_Dir.top()->recGroup->pos().rx()-2.5,True_Dir.top()->recGroup->pos().ry()-2.5,30,5));
                        masir.push_back(Dir);
                    }else{
                        Dir = new QGraphicsRectItem(QRectF(True_Dir.top()->recGroup->pos().rx()-30,True_Dir.top()->recGroup->pos().ry()-2.5,30,5));
                        masir.push_back(Dir);
                    }
                    Dir->setBrush(whiteBrush);
                    Dir->setPen(whitePen);
                    scene->addItem(Dir);
                }
                True_Dir.pop();

            }
            ui->nextstepbtn->setHidden(true);
            ui->nextstepbtn->setEnabled(false);
        }
    }
    if(DFS_or_BFS_or_BS == 'b'){
        if(frontier.front() != end)
        {
            frontier.front()->visited = true;
            visitedNodes.push_back(frontier.front());
            frontier.front()->Update_availableDirections();
            std::shared_ptr<Node> p = frontier.front();
            if(frontier.front() != start)
            {
                p->Me = new QGraphicsEllipseItem(p->recGroup->pos().rx()-5,p->recGroup->pos().ry()-5,10,10);
                p->Me->setBrush(whiteBrush);
                p->Me->setPen(whitePen);
                scene->addItem(p->Me);
            }

            frontier.pop();
            for(auto& ch : p->availableDirections)
            {
                ch.first->parent = p;
                frontier.push(ch.first);
                frontier.front()->Update_availableDirections();
            }
        }else{
            frontier.front()->visited = true;
            visitedNodes.push_back(frontier.front());
            frontier.front()->Me = new QGraphicsEllipseItem(frontier.front()->recGroup->pos().rx()-5,frontier.front()->recGroup->pos().ry()-5,10,10);
            frontier.front()->Me->setBrush(whiteBrush);
            frontier.front()->Me->setPen(whitePen);
            scene->addItem(frontier.front()->Me);

            std::stack<std::shared_ptr<Node>> short_dir;
            make_dir(short_dir,  end, false);

            QGraphicsRectItem *Dir;
            while (!short_dir.empty()) {
                short_dir.top()->is_true_dir = true;
                if(short_dir.top()->parent){
                    if((short_dir.top()->Directions)["North"].first == short_dir.top()->parent)
                    {
                        Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry()-25,5,30));
                        masir.push_back(Dir);
                    }else if((short_dir.top()->Directions)["South"].first == short_dir.top()->parent){
                        Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry(),5,30));
                        masir.push_back(Dir);
                    }else if((short_dir.top()->Directions)["East"].first == short_dir.top()->parent){
                        Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry()-2.5,30,5));
                        masir.push_back(Dir);
                    }else{
                        Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-30,short_dir.top()->recGroup->pos().ry()-2.5,30,5));
                        masir.push_back(Dir);
                    }
                    Dir->setBrush(whiteBrush);
                    Dir->setPen(whitePen);
                    scene->addItem(Dir);
                }
                short_dir.pop();
            }
            ui->nextstepbtn->setHidden(true);
            ui->nextstepbtn->setEnabled(false);
        }
    }
    if(DFS_or_BFS_or_BS == 'B')
    {
        find_bidirectional(frontier, false);
        find_bidirectional(end_frontier, true);
        if(frontier.front()->end_visit)
        {
            paint_dir(frontier.front());
        }else if(end_frontier.front()->visited)
        {
            paint_dir(end_frontier.front());
        }else if(frontier.front() == end_frontier.front())
        {
            QColor yellow(253,202,53);
            QBrush yellowBrush(yellow);
            QPen yellowPen(yellow);
            yellowPen.setWidth(0);
            frontier.front()->Me = new QGraphicsEllipseItem(frontier.front()->recGroup->pos().rx()-5,frontier.front()->recGroup->pos().ry()-5,10,10);
            frontier.front()->Me->setBrush(yellowBrush);
            frontier.front()->Me->setPen(yellowPen);
            scene->addItem(frontier.front()->Me);
            paint_dir(frontier.front());
        }
    }
}

void MazeGUI::paint_dir(std::shared_ptr<Node> middle)
{
    QColor yellow(253,202,53);
    QColor blue(14,165,167);
    QBrush blueBrush(blue);
    QBrush yellowBrush(yellow);
    QPen bluePen(blue);
    bluePen.setWidth(0);
    QPen yellowPen(yellow);
    yellowPen.setWidth(0);
    std::stack<std::shared_ptr<Node>> short_dir;
    make_dir(short_dir,  middle, false);
    QGraphicsRectItem *Dir;
    while (!short_dir.empty()) {
        short_dir.top()->is_true_dir = true;
        if(short_dir.top()->parent){
            if((short_dir.top()->Directions)["North"].first == short_dir.top()->parent)
            {
                Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry()-25,5,30));
                masir.push_back(Dir);
            }else if((short_dir.top()->Directions)["South"].first == short_dir.top()->parent){
                Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry(),5,30));
                masir.push_back(Dir);
            }else if((short_dir.top()->Directions)["East"].first == short_dir.top()->parent){
                Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-2.5,short_dir.top()->recGroup->pos().ry()-2.5,30,5));
                masir.push_back(Dir);
            }else{
                Dir = new QGraphicsRectItem(QRectF(short_dir.top()->recGroup->pos().rx()-30,short_dir.top()->recGroup->pos().ry()-2.5,30,5));
                masir.push_back(Dir);
            }
            Dir->setBrush(blueBrush);
            Dir->setPen(bluePen);
            scene->addItem(Dir);
           }
           short_dir.pop();
    }
    if(middle->end_parent != nullptr)
    {
        std::stack<std::shared_ptr<Node>> short_dir_end;
        make_dir(short_dir_end,  middle, true);
        QGraphicsRectItem *Dir;
        while (!short_dir_end.empty()) {
            short_dir_end.top()->is_true_dir = true;
            if(short_dir_end.top()->parent){
                if((short_dir_end.top()->Directions)["North"].first == short_dir_end.top()->parent)
                {
                    Dir = new QGraphicsRectItem(QRectF(short_dir_end.top()->recGroup->pos().rx()-2.5,short_dir_end.top()->recGroup->pos().ry()-25,5,30));
                    masir.push_back(Dir);
                }else if((short_dir_end.top()->Directions)["South"].first == short_dir_end.top()->parent){
                    Dir = new QGraphicsRectItem(QRectF(short_dir_end.top()->recGroup->pos().rx()-2.5,short_dir_end.top()->recGroup->pos().ry(),5,30));
                    masir.push_back(Dir);
                }else if((short_dir_end.top()->Directions)["East"].first == short_dir_end.top()->parent){
                    Dir = new QGraphicsRectItem(QRectF(short_dir_end.top()->recGroup->pos().rx()-2.5,short_dir_end.top()->recGroup->pos().ry()-2.5,30,5));
                    masir.push_back(Dir);
                }else{
                    Dir = new QGraphicsRectItem(QRectF(short_dir_end.top()->recGroup->pos().rx()-30,short_dir_end.top()->recGroup->pos().ry()-2.5,30,5));
                    masir.push_back(Dir);
                }
                Dir->setBrush(yellowBrush);
                Dir->setPen(yellowPen);
                scene->addItem(Dir);
               }
               short_dir_end.pop();
        }
    }
    ui->nextstepbtn->setHidden(true);
    ui->nextstepbtn->setEnabled(false);
}

void MazeGUI::find_bidirectional(std::queue<std::shared_ptr<Node>>& fr , bool end_path)
{
    QColor yellow(253,202,53);
    QColor blue(14,165,167);
    QBrush blueBrush(blue);
    QBrush yellowBrush(yellow);
    QPen bluePen(blue);
    bluePen.setWidth(0);
    QPen yellowPen(yellow);
    yellowPen.setWidth(0);

    std::shared_ptr<Node> p = fr.front();
    if(end_path)
    {
        fr.front()->end_visit = true;
        visitedNodes.push_back(fr.front());
        fr.front()->Update_availableDirections_end();
        p->Me = new QGraphicsEllipseItem(p->recGroup->pos().rx()-5,p->recGroup->pos().ry()-5,10,10);
        p->Me->setBrush(yellowBrush);
        p->Me->setPen(yellowPen);
        scene->addItem(p->Me);
    }
    else
    {
        fr.front()->visited = true;
        visitedNodes.push_back(fr.front());
        fr.front()->Update_availableDirections();
        p->Me = new QGraphicsEllipseItem(p->recGroup->pos().rx()-5,p->recGroup->pos().ry()-5,10,10);
        p->Me->setBrush(blueBrush);
        p->Me->setPen(bluePen);
        scene->addItem(p->Me);
    }

    fr.pop();
    for(auto& ch : p->availableDirections)
    {
        if(end_path)
        {
            ch.first->end_parent = p;
            fr.push(ch.first);
            fr.front()->Update_availableDirections_end();
        }
        else{
            ch.first->parent = p;
            fr.push(ch.first);
            fr.front()->Update_availableDirections();
        }
    }
}

void MazeGUI::BFSbtnPressed()
{
    ui->BFSbtn->setEnabled(false);
    ui->BFSbtn->setHidden(true);
    ui->DFSbtn->setEnabled(false);
    ui->DFSbtn->setHidden(true);
    ui->BSbtn->setEnabled(false);
    ui->BSbtn->setHidden(true);
    ui->nextstepbtn->setHidden(false);
    ui->anotherwaybtn->setHidden(false);
    ui->HTSlabel->setText("BFS");

    ui->steplabel->setHidden(false);
    ui->stepnumber->setHidden(false);

    DFS_or_BFS_or_BS = 'b';
    unvisiting();
    visitedNodes.clear();
    QBrush whiteBrush(Qt::white);
    QPen whitePen(Qt::white);
    whitePen.setWidth(0);
    start->Me = new QGraphicsEllipseItem(start->recGroup->pos().rx()-5,start->recGroup->pos().ry()-5,10,10);
    start->Me->setBrush(whiteBrush);
    start->Me->setPen(whitePen);
    scene->addItem(start->Me);
    ui->nextstepbtn->setEnabled(true);
    frontier.push(start);
}

void MazeGUI::BSbtnPressed()
{
    ui->BFSbtn->setEnabled(false);
    ui->BFSbtn->setHidden(true);
    ui->DFSbtn->setEnabled(false);
    ui->DFSbtn->setHidden(true);
    ui->BSbtn->setEnabled(false);
    ui->BSbtn->setHidden(true);
    ui->nextstepbtn->setHidden(false);
    ui->anotherwaybtn->setHidden(false);
    ui->HTSlabel->setText("Bidirectional");

    ui->steplabel->setHidden(false);
    ui->stepnumber->setHidden(false);

    DFS_or_BFS_or_BS = 'B';
    unvisiting();
    visitedNodes.clear();

    QColor yellow(253,202,53);
    QColor blue(14,165,167);
    QBrush blueBrush(blue);
    QBrush yellowBrush(yellow);
    QPen bluePen(blue);
    bluePen.setWidth(0);
    QPen yellowPen(yellow);
    yellowPen.setWidth(0);

    start->Me = new QGraphicsEllipseItem(start->recGroup->pos().rx()-5,start->recGroup->pos().ry()-5,10,10);
    start->Me->setBrush(blueBrush);
    start->Me->setPen(bluePen);
    scene->addItem(start->Me);
    ui->nextstepbtn->setEnabled(true);
    frontier.push(start);

    end->Me = new QGraphicsEllipseItem(end->recGroup->pos().rx()-5,end->recGroup->pos().ry()-5,10,10);
    end->Me->setBrush(yellowBrush);
    end->Me->setPen(yellowPen);
    scene->addItem(end->Me);
    ui->nextstepbtn->setEnabled(true);
    end_frontier.push(end);
}

void MazeGUI::fill()
{
    for (int16_t i = 0; i < row; i++)
    {
        std::vector<std::shared_ptr<Node>> temp;
        for (int j = 0; j < col; j++)
        {
            auto n{std::make_shared<MazeGUI::Node>(i*col + j)};
            n->recGroup->setPos(30*j-30*col/2,30*i-30*row/2);
            temp.push_back(n);
        }
        Board.push_back(temp);
    }
    MazeGUI::GMaze->setPos(0,0);
}

void MazeGUI::set_margin()
{
    for(auto& N:Board.front())
    {
        (N->Directions)["North"].second = -1;
    }
    for(auto& v:Board)
    {
        (v.front()->Directions)["West"].second = -1;
        (v.back()->Directions)["East"].second = -1;
    }
    for(auto& N:Board.back())
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
    unvisiting();
    find_end();

    unvisiting();
    paint_walls();
}

void MazeGUI::find_end()
{
    std::queue<std::shared_ptr<Node>> fr;
    fr.push(start);
    int visited_node_counter=0;
    int levelRange{};
    if(ui->levelBox->currentText() == "Easy")
        levelRange = row*col/4;
    else if(ui->levelBox->currentText() == "Normal")
        levelRange = row*col/2;
    else if(ui->levelBox->currentText() == "Hard")
        levelRange = 3*row*col/4;


    while(visited_node_counter < row*col)
    {

        fr.front()->visited = true;
        visited_node_counter++;
        fr.front()->Update_availableDirections();
        std::shared_ptr<Node> p = fr.front();
        fr.pop();
        for(auto& ch : p->availableDirections)
        {
            ch.first->parent = p;
            fr.push(ch.first);
            fr.front()->Update_availableDirections();
        }

        if (visited_node_counter == levelRange)
        {
            if(p->availableDirections.empty())
                end = p;
            else
                end = p->availableDirections[MazeGUI::Random_generator(p->availableDirections.size())].first;
            end->is_end = true;
            break;
        }

    }
}

int MazeGUI::Random_generator(size_t size)
{
    quint32 val = QRandomGenerator::global()->generate();
    if (size != 0)
        return val%size;
    else
        return -1;
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

void MazeGUI::Node::Update_availableDirections_end()
{

    std::vector<std::pair<std::shared_ptr<Node>,int>>::iterator it;
    it = availableDirections.begin();
    for (size_t i = 0; i < availableDirections.size(); i++)
    {
        if (availableDirections[i].first->end_visit)
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
    QColor red(203,78,78);
    QColor yellow(253,202,53);
    QColor blue(14,165,167);
    QBrush redBrush(red);
    QBrush blueBrush(blue);
    QBrush yellowBrush(yellow);
    QBrush blackBrush(Qt::black);
    QPen redPen(red);
    redPen.setWidth(0);
    QPen cyanPen(Qt::cyan);
    cyanPen.setWidth(0);
    QPen yellowPen(yellow);
    yellowPen.setWidth(0);
    QPen blackPen(Qt::black);
    blackPen.setWidth(0);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(Board[i][j]->is_start)
            {
              Qstart = new QGraphicsEllipseItem(Board[i][j]->recGroup->pos().rx()-8,Board[i][j]->recGroup->pos().ry()-8,16,16);
              Qstart->setBrush(blueBrush);
              Qstart->setPen(blackPen);
            }
            if(Board[i][j]->is_end)
            {
                Qend = new QGraphicsEllipseItem(Board[i][j]->recGroup->pos().rx()-8,Board[i][j]->recGroup->pos().ry()-8,16,16);
                Qend->setBrush(yellowBrush);
                Qend->setPen(blackPen);
            }
            if((Board[i][j]->Directions)["North"].second == 1)
            {
                Board[i][j]->top = new QGraphicsItemGroup(Board[i][j]->recGroup);
                QGraphicsRectItem *topBox = new QGraphicsRectItem(QRectF(-20,-15,40,5),Board[i][j]->top);
                topBox->setBrush(redBrush);
                topBox->setPen(redPen);
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
                downtBox->setBrush(redBrush);
                downtBox->setPen(redPen);
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
                rightBox->setBrush(redBrush);
                rightBox->setPen(redPen);
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
                leftBox->setBrush(redBrush);
                leftBox->setPen(redPen);
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
}

void MazeGUI::unvisiting()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Board[i][j]->availableDirections.clear();
            Board[i][j]->visited = false;
            Board[i][j]->end_visit = false;
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

void MazeGUI::make_dir(std::stack<std::shared_ptr<Node>>& short_dir, std::shared_ptr<MazeGUI::Node> node, bool is_end)
{
     short_dir.push(node);
     if(is_end)
     {
         if (node->end_parent != nullptr)
            make_dir(short_dir, node->end_parent,true);
     }
     else
     {
         if (node->parent != nullptr)
            make_dir(short_dir, node->parent,false);
     }


}
