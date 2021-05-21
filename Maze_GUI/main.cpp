#include "mazegui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MazeGUI w;
    w.show();
    return a.exec();
}
