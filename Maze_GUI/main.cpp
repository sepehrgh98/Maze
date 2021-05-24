#include "mazegui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MazeGUI w;
    w.show();
    Thread t;
    QObject::connect(&t, SIGNAL(finished()), &w, SLOT(ProgressFinished()));
    QObject::connect(&t, SIGNAL(progress(int)), &w, SLOT(onProgress(int)));

    t.start();

    return a.exec();
}
