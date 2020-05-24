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
#include <QGraphicsTextItem>

#include "Player.h"
#include "Score.h"
#include "Deficit.h"
#include "Course.h"
#include "Enemy.h"

class Game: public QMainWindow{
    Q_OBJECT

    QTimer *timer1;
    QTimer *timer2;
    QPushButton *closeButton;
    QPushButton *pauseButton;
    QPushButton *newGameButton;
    QPushButton *fasterButton;
    QPushButton *slowerButton;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QVBoxLayout *layout;
    QWidget *window;
    QLabel *dot;
    QLabel *text;
    QGraphicsTextItem *gameOverText;
    QGraphicsTextItem *speedText;
    QCustomPlot *customPlot;
    QVector<double> x;
    QVector<double> y0;
    QVector<double> y1;
    int enemyMoveInterval = 50;
    int textSpeed = 100;
    bool gameOverFlag = false;

    void plot();
    void makeEnemy();
    void deleteEnemy();
    void makePlayer();
    void makeText();
    void makeButtons();
    void makeToolbar();
    void makeStatusBar();

public:
    Game(QWidget *parent = 0);
    QGraphicsScene *gameScene;
    QStatusBar *bar;
    Player *player;
    Score *score;
    Deficit *deficit;
    QList<Enemy *> enemyList;
    QList<Course *> courseList;
    int pEnemy = 0;

    //Dodawnaie punktu do wykresu
    void addPoint(double y0, double y1);
    void gameOver();

private slots:
    //Zakonczenie dzialania
    void end();

    //Generowanie bloczkow
    void spawn();

    //Wyswietlanie tekstu na belce statusowej
    void textStatusBar();

    //Zatrzymywanie dzialania
    void delay();

    void newGame();

    void faster();
    void slower();
};

#endif // GAME_H
