#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QStatusBar>
#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include <QWidget>
#include <QToolBar>
#include <QLayout>
#include <QGroupBox>
#include <qcustomplot.h>
#include <QVector>
#include <QLabel>
#include <iostream>

#include "Player.h"
#include "Score.h"
#include "Deficit.h"
#include "Course.h"
#include "Enemy.h"

class Game: public QMainWindow{
    Q_OBJECT
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    QPushButton *closeButton;
    QPushButton *pauseButton;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QVBoxLayout *layout;
    QWidget *window;
    QLabel *dot;
    QLabel *text;

    //Wykres
    QCustomPlot *customPlot;
    QVector<double> x;
    QVector<double> y0;
    QVector<double> y1;
    void plot();
    void makeEnemy();

    int pEnemy;

public:
    Game(QWidget *parent = 0);
    QGraphicsScene *gameScene;
    QStatusBar *bar;
    Player *player;
    Score *score;
    Deficit *deficit;
    QList<Enemy *> enemyList;
    QList<Course *> courseList;

    //Dodawnaie punktu do wykresu
    void addPoint(double y0, double y1);

private slots:
    //Zakonczenie dzialania
    void end();

    //Zatrzymywanie dzialania
    void delay();

    //Generowanie bloczkow
    void spawn();

    //Wyswietlanie tekstu na belce statusowej
    void textStatusBar();
};

#endif // GAME_H
