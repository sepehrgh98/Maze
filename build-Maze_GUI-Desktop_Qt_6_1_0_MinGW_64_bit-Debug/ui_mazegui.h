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
#include <QtWidgets/QComboBox>
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
    QWidget *mainPage;
    QFrame *setBar;
    QLabel *rowlabel;
    QSpinBox *rowspinBox;
    QLabel *collabel;
    QPushButton *generatebtn;
    QSpinBox *colspinBox;
    QPushButton *clearbtn;
    QLabel *levellabel;
    QComboBox *levelBox;
    QGraphicsView *graphicsView;
    QFrame *controlBar;
    QLabel *HTSlabel;
    QPushButton *DFSbtn;
    QPushButton *BFSbtn;
    QPushButton *nextstepbtn;
    QLabel *steplabel;
    QLabel *stepnumber;
    QPushButton *anotherwaybtn;
    QPushButton *BSbtn;
    QWidget *logoWidget;
    QLabel *maze2;
    QPushButton *gobtn;
    QLabel *logo2;
    QWidget *welcomePage;
    QLabel *logoBox;
    QLabel *maze;
    QLabel *uni;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MazeGUI)
    {
        if (MazeGUI->objectName().isEmpty())
            MazeGUI->setObjectName(QString::fromUtf8("MazeGUI"));
        MazeGUI->resize(1412, 731);
        centralwidget = new QWidget(MazeGUI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainPage = new QWidget(centralwidget);
        mainPage->setObjectName(QString::fromUtf8("mainPage"));
        mainPage->setGeometry(QRect(20, 10, 1371, 681));
        setBar = new QFrame(mainPage);
        setBar->setObjectName(QString::fromUtf8("setBar"));
        setBar->setGeometry(QRect(10, 0, 191, 271));
        setBar->setStyleSheet(QString::fromUtf8("QFrame#setBar\n"
"{\n"
"	background-color: #2A3C3D;\n"
"    border-radius: 7px;\n"
"}"));
        setBar->setFrameShape(QFrame::StyledPanel);
        setBar->setFrameShadow(QFrame::Raised);
        rowlabel = new QLabel(setBar);
        rowlabel->setObjectName(QString::fromUtf8("rowlabel"));
        rowlabel->setGeometry(QRect(20, 30, 55, 16));
        rowlabel->setStyleSheet(QString::fromUtf8("QLabel#rowlabel\n"
"{\n"
"color:#E5D7C5;\n"
"font-weight: bold;\n"
"font-size:15px;\n"
"\n"
"}"));
        rowspinBox = new QSpinBox(setBar);
        rowspinBox->setObjectName(QString::fromUtf8("rowspinBox"));
        rowspinBox->setGeometry(QRect(100, 30, 71, 22));
        rowspinBox->setStyleSheet(QString::fromUtf8("QSpinBox#rowspinBox{\n"
"color: #2A3C3D;\n"
"background-color: #E5D7C5;\n"
"}\n"
""));
        collabel = new QLabel(setBar);
        collabel->setObjectName(QString::fromUtf8("collabel"));
        collabel->setGeometry(QRect(20, 70, 61, 20));
        collabel->setStyleSheet(QString::fromUtf8("QLabel#collabel\n"
"{\n"
"color:#E5D7C5;\n"
"font-weight: bold;\n"
"font-size:15px;\n"
"\n"
"}"));
        generatebtn = new QPushButton(setBar);
        generatebtn->setObjectName(QString::fromUtf8("generatebtn"));
        generatebtn->setGeometry(QRect(30, 170, 121, 28));
        generatebtn->setStyleSheet(QString::fromUtf8("QPushButton#generatebtn {\n"
"    background-color: #CB4E4E;\n"
"    border-style: outset;\n"
"    border-radius: 10px;\n"
"	font: 8pt \"Franklin Gothic Demi\";\n"
"    border-color: beige;\n"
"	color:#2A3C3D;\n"
"	font-size:18px;\n"
"\n"
"}"));
        colspinBox = new QSpinBox(setBar);
        colspinBox->setObjectName(QString::fromUtf8("colspinBox"));
        colspinBox->setGeometry(QRect(100, 70, 71, 22));
        colspinBox->setStyleSheet(QString::fromUtf8("QSpinBox#colspinBox{\n"
"color: #2A3C3D;\n"
"background-color: #E5D7C5;\n"
"}"));
        clearbtn = new QPushButton(setBar);
        clearbtn->setObjectName(QString::fromUtf8("clearbtn"));
        clearbtn->setGeometry(QRect(30, 210, 121, 28));
        clearbtn->setStyleSheet(QString::fromUtf8("QPushButton#clearbtn {\n"
"    background-color: #CB4E4E;\n"
"    border-style: outset;\n"
"    border-radius: 10px;\n"
"	font: 8pt \"Franklin Gothic Demi\";\n"
"    border-color: beige;\n"
"	color:#2A3C3D;\n"
"	font-size:18px;\n"
"\n"
"}\n"
""));
        clearbtn->setCheckable(false);
        clearbtn->setChecked(false);
        levellabel = new QLabel(setBar);
        levellabel->setObjectName(QString::fromUtf8("levellabel"));
        levellabel->setGeometry(QRect(20, 110, 61, 20));
        levellabel->setStyleSheet(QString::fromUtf8("QLabel#levellabel\n"
"{\n"
"color:#E5D7C5;\n"
"font-weight: bold;\n"
"font-size:15px;\n"
"\n"
"}"));
        levelBox = new QComboBox(setBar);
        levelBox->setObjectName(QString::fromUtf8("levelBox"));
        levelBox->setGeometry(QRect(100, 110, 73, 22));
        levelBox->setStyleSheet(QString::fromUtf8("QSpinBox#levelBox{\n"
"color: #2A3C3D;\n"
"background-color: #E5D7C5;\n"
"}\n"
""));
        graphicsView = new QGraphicsView(mainPage);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(210, 0, 1161, 671));
        graphicsView->setStyleSheet(QString::fromUtf8("background-color: #2A3C3D;\n"
"    border-radius: 7px;\n"
""));
        controlBar = new QFrame(mainPage);
        controlBar->setObjectName(QString::fromUtf8("controlBar"));
        controlBar->setGeometry(QRect(10, 280, 191, 391));
        controlBar->setStyleSheet(QString::fromUtf8("QFrame#controlBar\n"
"{\n"
"	background-color: #2A3C3D;\n"
"    border-radius: 7px;\n"
"}"));
        controlBar->setFrameShape(QFrame::StyledPanel);
        controlBar->setFrameShadow(QFrame::Raised);
        HTSlabel = new QLabel(controlBar);
        HTSlabel->setObjectName(QString::fromUtf8("HTSlabel"));
        HTSlabel->setGeometry(QRect(30, 30, 131, 41));
        HTSlabel->setStyleSheet(QString::fromUtf8("QLabel#HTSlabel\n"
"{\n"
"color:#E5D7C5;\n"
"font-weight: bold;\n"
"font-size:18px;\n"
"}"));
        HTSlabel->setAlignment(Qt::AlignCenter);
        DFSbtn = new QPushButton(controlBar);
        DFSbtn->setObjectName(QString::fromUtf8("DFSbtn"));
        DFSbtn->setGeometry(QRect(30, 90, 121, 28));
        DFSbtn->setStyleSheet(QString::fromUtf8("QPushButton#DFSbtn {\n"
"    background-color: #CB4E4E;\n"
"    border-style: outset;\n"
"    border-radius: 10px;\n"
"	font: 8pt \"Franklin Gothic Demi\";\n"
"    border-color: beige;\n"
"	color:#2A3C3D;\n"
"	font-size:18px;\n"
"}"));
        BFSbtn = new QPushButton(controlBar);
        BFSbtn->setObjectName(QString::fromUtf8("BFSbtn"));
        BFSbtn->setGeometry(QRect(32, 140, 121, 28));
        BFSbtn->setStyleSheet(QString::fromUtf8("QPushButton#BFSbtn {\n"
"    background-color: #CB4E4E;\n"
"    border-style: outset;\n"
"    border-radius: 10px;\n"
"	font: 8pt \"Franklin Gothic Demi\";\n"
"    border-color: beige;\n"
"	color:#2A3C3D;\n"
"	font-size:18px;\n"
"}"));
        nextstepbtn = new QPushButton(controlBar);
        nextstepbtn->setObjectName(QString::fromUtf8("nextstepbtn"));
        nextstepbtn->setGeometry(QRect(60, 240, 61, 61));
        nextstepbtn->setStyleSheet(QString::fromUtf8("QPushButton#nextstepbtn {\n"
"    background-color: #CB4E4E;\n"
"    border-style: outset;\n"
"    border-radius: 30px;\n"
"	font: 8pt \"Franklin Gothic Demi\";\n"
"    border-color: beige;\n"
"	color:#2A3C3D;\n"
"	font-size:18px;\n"
"	font-weight:bold;\n"
"}"));
        steplabel = new QLabel(controlBar);
        steplabel->setObjectName(QString::fromUtf8("steplabel"));
        steplabel->setGeometry(QRect(50, 110, 81, 21));
        steplabel->setStyleSheet(QString::fromUtf8("QLabel#steplabel\n"
"{\n"
"color:#E5D7C5;\n"
"font-weight: bold;\n"
"font-size:18px;\n"
"text-align:center;\n"
"}"));
        steplabel->setAlignment(Qt::AlignCenter);
        stepnumber = new QLabel(controlBar);
        stepnumber->setObjectName(QString::fromUtf8("stepnumber"));
        stepnumber->setGeometry(QRect(50, 140, 81, 81));
        stepnumber->setStyleSheet(QString::fromUtf8("QLabel#stepnumber\n"
"{\n"
"color:#E5D7C5;\n"
"font-weight: bold;\n"
"font-size:20px;\n"
"}"));
        stepnumber->setAlignment(Qt::AlignCenter);
        anotherwaybtn = new QPushButton(controlBar);
        anotherwaybtn->setObjectName(QString::fromUtf8("anotherwaybtn"));
        anotherwaybtn->setGeometry(QRect(10, 340, 111, 41));
        anotherwaybtn->setStyleSheet(QString::fromUtf8("QPushButton#anotherwaybtn {\n"
"    background-color: #CB4E4E;\n"
"    border-style: outset;\n"
"    border-radius: 20px;\n"
"	font: 8pt \"Franklin Gothic Demi\";\n"
"    border-color: beige;\n"
"	color:#2A3C3D;\n"
"	font-size:17px;\n"
"	font-weight:bold;\n"
"}"));
        BSbtn = new QPushButton(controlBar);
        BSbtn->setObjectName(QString::fromUtf8("BSbtn"));
        BSbtn->setGeometry(QRect(30, 190, 121, 28));
        BSbtn->setStyleSheet(QString::fromUtf8("QPushButton#BSbtn{\n"
"    background-color: #CB4E4E;\n"
"    border-style: outset;\n"
"    border-radius: 10px;\n"
"	font: 8pt \"Franklin Gothic Demi\";\n"
"    border-color: beige;\n"
"	color:#2A3C3D;\n"
"	font-size:18px;\n"
"}"));
        logoWidget = new QWidget(mainPage);
        logoWidget->setObjectName(QString::fromUtf8("logoWidget"));
        logoWidget->setGeometry(QRect(10, 280, 191, 391));
        maze2 = new QLabel(logoWidget);
        maze2->setObjectName(QString::fromUtf8("maze2"));
        maze2->setGeometry(QRect(50, 160, 111, 41));
        maze2->setStyleSheet(QString::fromUtf8("QLabel#maze2\n"
"{\n"
"font: 87 20pt \"Arial Black\";\n"
"color: rgb(42, 61, 60);\n"
"}"));
        gobtn = new QPushButton(logoWidget);
        gobtn->setObjectName(QString::fromUtf8("gobtn"));
        gobtn->setGeometry(QRect(50, 240, 91, 31));
        gobtn->setStyleSheet(QString::fromUtf8("QPushButton#gobtn{\n"
"    background-color: #CB4E4E;\n"
"    border-style: outset;\n"
"    border-radius: 10px;\n"
"	font: 8pt \"Franklin Gothic Demi\";\n"
"	color:#2A3C3D;\n"
"	font-size:18px;\n"
"	font-weight:bold;\n"
"	border: 3px solid #2A3C3D;\n"
"}"));
        logo2 = new QLabel(logoWidget);
        logo2->setObjectName(QString::fromUtf8("logo2"));
        logo2->setGeometry(QRect(40, 40, 101, 101));
        welcomePage = new QWidget(centralwidget);
        welcomePage->setObjectName(QString::fromUtf8("welcomePage"));
        welcomePage->setGeometry(QRect(20, 30, 1371, 651));
        welcomePage->setStyleSheet(QString::fromUtf8("QWidget#welcomePage{\n"
"	border: 8px solid #2A3C3D\n"
"}"));
        logoBox = new QLabel(welcomePage);
        logoBox->setObjectName(QString::fromUtf8("logoBox"));
        logoBox->setGeometry(QRect(390, 160, 211, 201));
        maze = new QLabel(welcomePage);
        maze->setObjectName(QString::fromUtf8("maze"));
        maze->setGeometry(QRect(590, 200, 161, 61));
        maze->setStyleSheet(QString::fromUtf8("QLabel#maze\n"
"{\n"
"font: 87 30pt \"Arial Black\";\n"
"color: rgb(42, 61, 60);\n"
"}"));
        uni = new QLabel(welcomePage);
        uni->setObjectName(QString::fromUtf8("uni"));
        uni->setGeometry(QRect(590, 260, 631, 41));
        uni->setStyleSheet(QString::fromUtf8("QLabel#uni\n"
"{\n"
"font: 87 15pt \"Arial Black\";\n"
"color: rgb(42, 61, 60);\n"
"}"));
        progressBar = new QProgressBar(welcomePage);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(280, 422, 941, 31));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar\n"
"{\n"
"border: 5px solid #2A3C3D;\n"
"border-radius: 20px;\n"
"background: #70B67A;\n"
"text-align: right;\n"
"color:#2A3C3D;\n"
"font-weight: bold;\n"
"padding-right: 3px;\n"
"}\n"
"QProgressBar::chunk {\n"
"background: #2A3C3D\n"
"}"));
        progressBar->setValue(24);
        MazeGUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MazeGUI);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1412, 26));
        MazeGUI->setMenuBar(menubar);
        statusbar = new QStatusBar(MazeGUI);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MazeGUI->setStatusBar(statusbar);
        QWidget::setTabOrder(rowspinBox, colspinBox);
        QWidget::setTabOrder(colspinBox, DFSbtn);
        QWidget::setTabOrder(DFSbtn, BFSbtn);
        QWidget::setTabOrder(BFSbtn, nextstepbtn);
        QWidget::setTabOrder(nextstepbtn, generatebtn);

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
        levellabel->setText(QCoreApplication::translate("MazeGUI", "Level :", nullptr));
        HTSlabel->setText(QCoreApplication::translate("MazeGUI", "How to Solve?", nullptr));
        DFSbtn->setText(QCoreApplication::translate("MazeGUI", "DFS", nullptr));
        BFSbtn->setText(QCoreApplication::translate("MazeGUI", "BFS", nullptr));
        nextstepbtn->setText(QCoreApplication::translate("MazeGUI", ">>", nullptr));
        steplabel->setText(QCoreApplication::translate("MazeGUI", "STEP:", nullptr));
        stepnumber->setText(QString());
        anotherwaybtn->setText(QCoreApplication::translate("MazeGUI", "change way", nullptr));
        BSbtn->setText(QCoreApplication::translate("MazeGUI", "Bidirectional", nullptr));
        maze2->setText(QCoreApplication::translate("MazeGUI", "MAZE", nullptr));
        gobtn->setText(QCoreApplication::translate("MazeGUI", "Go!", nullptr));
        logo2->setText(QCoreApplication::translate("MazeGUI", "TextLabel", nullptr));
        logoBox->setText(QCoreApplication::translate("MazeGUI", "TextLabel", nullptr));
        maze->setText(QCoreApplication::translate("MazeGUI", "MAZE", nullptr));
        uni->setText(QCoreApplication::translate("MazeGUI", "Amirkabir University of Technology", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MazeGUI: public Ui_MazeGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZEGUI_H
