/********************************************************************************
** Form generated from reading UI file 'mazegui.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAZEGUI_H
#define UI_MAZEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MazeGUI
{
public:
    QWidget *centralwidget;
    QFrame *setBar;
    QLabel *rowlabel;
    QSpinBox *rowspinBox;
    QLabel *collabel;
    QPushButton *generatebtn;
    QSpinBox *colspinBox;
    QPushButton *clearbtn;
    QFrame *controlBar;
    QLabel *HTSlabel;
    QPushButton *DFSbtn;
    QPushButton *BFSbtn;
    QPushButton *nextstepbtn;
    QPushButton *prestepbtn;
    QProgressBar *progressBar;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MazeGUI)
    {
        if (MazeGUI->objectName().isEmpty())
            MazeGUI->setObjectName(QString::fromUtf8("MazeGUI"));
        MazeGUI->resize(1165, 661);
        centralwidget = new QWidget(MazeGUI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        setBar = new QFrame(centralwidget);
        setBar->setObjectName(QString::fromUtf8("setBar"));
        setBar->setGeometry(QRect(30, 30, 191, 221));
        setBar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        setBar->setFrameShape(QFrame::StyledPanel);
        setBar->setFrameShadow(QFrame::Raised);
        rowlabel = new QLabel(setBar);
        rowlabel->setObjectName(QString::fromUtf8("rowlabel"));
        rowlabel->setGeometry(QRect(40, 30, 55, 16));
        rowspinBox = new QSpinBox(setBar);
        rowspinBox->setObjectName(QString::fromUtf8("rowspinBox"));
        rowspinBox->setGeometry(QRect(110, 30, 42, 22));
        collabel = new QLabel(setBar);
        collabel->setObjectName(QString::fromUtf8("collabel"));
        collabel->setGeometry(QRect(40, 70, 55, 20));
        generatebtn = new QPushButton(setBar);
        generatebtn->setObjectName(QString::fromUtf8("generatebtn"));
        generatebtn->setGeometry(QRect(40, 120, 91, 28));
        generatebtn->setStyleSheet(QString::fromUtf8(""));
        colspinBox = new QSpinBox(setBar);
        colspinBox->setObjectName(QString::fromUtf8("colspinBox"));
        colspinBox->setGeometry(QRect(110, 70, 42, 22));
        clearbtn = new QPushButton(setBar);
        clearbtn->setObjectName(QString::fromUtf8("clearbtn"));
        clearbtn->setGeometry(QRect(40, 160, 91, 28));
        clearbtn->setStyleSheet(QString::fromUtf8(""));
        clearbtn->setCheckable(false);
        clearbtn->setChecked(false);
        controlBar = new QFrame(centralwidget);
        controlBar->setObjectName(QString::fromUtf8("controlBar"));
        controlBar->setGeometry(QRect(30, 270, 191, 331));
        controlBar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        controlBar->setFrameShape(QFrame::StyledPanel);
        controlBar->setFrameShadow(QFrame::Raised);
        HTSlabel = new QLabel(controlBar);
        HTSlabel->setObjectName(QString::fromUtf8("HTSlabel"));
        HTSlabel->setGeometry(QRect(60, 30, 81, 41));
        DFSbtn = new QPushButton(controlBar);
        DFSbtn->setObjectName(QString::fromUtf8("DFSbtn"));
        DFSbtn->setGeometry(QRect(50, 120, 93, 28));
        BFSbtn = new QPushButton(controlBar);
        BFSbtn->setObjectName(QString::fromUtf8("BFSbtn"));
        BFSbtn->setGeometry(QRect(50, 170, 93, 28));
        nextstepbtn = new QPushButton(controlBar);
        nextstepbtn->setObjectName(QString::fromUtf8("nextstepbtn"));
        nextstepbtn->setGeometry(QRect(120, 270, 41, 41));
        prestepbtn = new QPushButton(controlBar);
        prestepbtn->setObjectName(QString::fromUtf8("prestepbtn"));
        prestepbtn->setGeometry(QRect(40, 270, 41, 41));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(237, 572, 901, 31));
        progressBar->setValue(24);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(240, 30, 901, 531));
        MazeGUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MazeGUI);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1165, 26));
        MazeGUI->setMenuBar(menubar);
        statusbar = new QStatusBar(MazeGUI);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MazeGUI->setStatusBar(statusbar);
        QWidget::setTabOrder(rowspinBox, colspinBox);
        QWidget::setTabOrder(colspinBox, DFSbtn);
        QWidget::setTabOrder(DFSbtn, BFSbtn);
        QWidget::setTabOrder(BFSbtn, nextstepbtn);
        QWidget::setTabOrder(nextstepbtn, prestepbtn);
        QWidget::setTabOrder(prestepbtn, generatebtn);

        retranslateUi(MazeGUI);

        QMetaObject::connectSlotsByName(MazeGUI);
    } // setupUi

    void retranslateUi(QMainWindow *MazeGUI)
    {
        MazeGUI->setWindowTitle(QCoreApplication::translate("MazeGUI", "MazeGUI", nullptr));
        rowlabel->setText(QCoreApplication::translate("MazeGUI", "row :", nullptr));
        collabel->setText(QCoreApplication::translate("MazeGUI", "column :", nullptr));
        generatebtn->setText(QCoreApplication::translate("MazeGUI", "GENERATE", nullptr));
        clearbtn->setText(QCoreApplication::translate("MazeGUI", "CLEAR", nullptr));
        HTSlabel->setText(QCoreApplication::translate("MazeGUI", "How to Solve?", nullptr));
        DFSbtn->setText(QCoreApplication::translate("MazeGUI", "DFS", nullptr));
        BFSbtn->setText(QCoreApplication::translate("MazeGUI", "BFS", nullptr));
        nextstepbtn->setText(QCoreApplication::translate("MazeGUI", ">>", nullptr));
        prestepbtn->setText(QCoreApplication::translate("MazeGUI", "<<", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MazeGUI: public Ui_MazeGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZEGUI_H
