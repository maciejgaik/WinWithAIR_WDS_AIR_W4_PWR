#ifndef GAME_H
#define GAME_H

/*!
 *
 * \file
 * \brief Definicja klasy Game
 * Plik zawiera definicję klasy Game, ktora jest
 * klasa pochodna QMainWindow. Klasa odpowida za
 * tworzenie okna rozgrywki i wszelkich jej elemntow
 *
 */

#include <QApplication>
#include <QGraphicsScene>
#include <QImage>
#include <QBrush>
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
#include <QCP/qcustomplot.h>
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

    /*!
     * \brief timer1 - sprawdzanie połaczenia z kontrolerem co 100ms
     */
    QTimer *timer1;

    /*!
     * \brief timer2 - generowanie bloczka co okreslony czas
     */
    QTimer *timer2;

    /*!
     * \brief Przyciski zakonczenia gry
     */
    QPushButton *closeButton;

    /*!
     * \brief Przycisk wstrzymania/wznowienia rozgrywki
     */
    QPushButton *pauseButton;

    /*!
     * \brief Przycisk nowej gry
     */
    QPushButton *newGameButton;

    /*!
     * \brief Przycisk przyspieszenia gry
     */
    QPushButton *fasterButton;

    /*!
     * \brief Przycisk zwolnienia gry
     */
    QPushButton *slowerButton;

    /*!
     * \brief Belka statusowa
     */
    QStatusBar *statusBar;

    /*!
     * \brief Belka z legendą i przyciskami
     */
    QToolBar *toolBar;

    /*!
     * \brief Layout wertyklany
     */
    QVBoxLayout *layout;

    /*!
     * \brief Główne okno
     */
    QWidget *window;

    /*!
     * \brief Kropka statusu połączenia z kontrolerem
     */
    QLabel *statusDot;

    /*!
     * \brief Napis statusu połączenia z kontrolerem
     */
    QLabel *statusText;

    /*!
     * \brief Napisy na scenie konca gry
     */
    QGraphicsTextItem *gameOverText;

    /*!
     * \brief Napisy na scenie predkosci rozgrywki w %
     */
    QGraphicsTextItem *speedText;

    /*!
     * \brief Wykresy obrotu w osiach X i Y w stopniach
     */
    QCustomPlot *customPlot;

    /*!
     * \brief x - wektor wartosci osi X na wykresie (sekundy)
     */
    QVector<double> x;

    /*!
     *
     * \brief y0 - wektor wartosci obrotu w osi X (stopnie)
     */
    QVector<double> y0;

    /*!
     * \brief y1 - wektor wartosci obrotu w osi Y (stopnie)
     */
    QVector<double> y1;

    /*!
     * \brief Domyslna wartosc interwalu ruchu bloczków
     */
    int enemyMoveInterval = 50;

    /*!
     * \brief Standardowa przedkosc gry
     */
    int textSpeed = 100;

    /*!
     * \brief flaga zakonnczenia gry
     */
    bool gameOverFlag = false;

    /*!
     * \brief Rysuje wykresy wartosci z żyroskopu
     */
    void plot();

    /*!
     * \brief Tworzy listę kursów i co okreslony czas
     *  kopiuje je do listy bloczków
     */
    void makeEnemy();

    /*!
     * \brief Czyszczenie listy enemyList
     */
    void deleteEnemy();

    /*!
     * \brief Inicjalizuje obiekt klasy Player, ustawia
     * jego pozycje oraz dodaje do sceny
     */
    void makePlayer();

    /*!
     * \brief Inicjalizuje obiekty klasy QGraphicsTextItem
     * i dodaje je do sceny
     */
    void makeText();

    /*!
     * \brief Inicjalizuje obiekty klasy QPushButton i łączy z
     * odpowienimi slotami
     */
    void makeButtons();

    /*!
     * \brief Inicjalizuje obiekt klasy ToolBar i dodaje do
     * niego odpowiednie elementy
     */
    void makeToolbar();

    /*!
     * \brief Inicjalizuje obiekt klasy StatusBar i dodaje do
     * niego odpowiednie elementy
     */
    void makeStatusBar();

public:
    /*!
     * \brief Główny kontruktor aplikacji, odpwiedzialny za
     * stworzenie okna, sceny, dodanie sceny, belki statusowej,
     * belki narzędziowej, wykresów oraz layoutu
     * \param parent - wskaźnik na rodzica, domyslnie = 0
     */
    Game(QWidget *parent = 0);

    /*!
     * \brief Scena rozgrywki
     */
    QGraphicsScene *gameScene;

    /*!
     * \brief Obiekt gracza
     */
    Player *player;

    /*!
     * \brief Liczba zdobytych ects
     */
    Score *score;

    /*!
     * \brief Liczba niezdobytych ects
     */
    Deficit *deficit;

    /*!
     * \brief Lista bloczków na scenie
     */
    QList<Enemy *> enemyList;

    /*!
     * \brief Lista wszytskich kursów
     */
    QList<Course *> courseList;

    /*!
     * \brief Określa ostatnio dodany element z listy kursów
     */
    int pEnemy = 0;

    /*!
     * \brief Dodawanie punktów do wykresów
     * \param [in] y0 - współrzędna Y wykresu 0 (stopnie)
     * \param [in] y1 - współrzędna Y wykresu 1 (stopnie)
     */
    void addPoint(double y0, double y1);

    /*!
     * \brief Funkcja w zależnosci od wygranej/przegranej
     * wyswietla odpowiedni napis
     * \param [in] win - false - przegrane, true - wygrana
     */
    void gameOver(bool win);

private slots:
    /*!
     * \brief Powoduje zakonczenie rozgrywki i zamkniecie okna.
     */
    void end();

    /*!
     * \brief Metoda odpowiedzialna jest za kopiowanie obiektow
     * do listy enemyList z coursList oraz dodanie ich do sceny.
     */
    void spawn();

    /*!
     * \brief Wyswietla status połączenie na belce statusowej.
     */
    void textStatusBar();

    /*!
     * \brief Powoduje wstrzymanie lub wzowienie gry.
     */
    void delay();

    /*!
     * \brief Powoduje wyczyszczenie sceny, wyzerowanie zebranych
     * i przepuszconych punktów, wyczyszenie listy enemylist.
     * Wszelkie zmienione wartosci są inicjalizowane wartosciami
     * początkowymi.
     */
    void newGame();

    /*!
     * \brief Powoduje zmniejszanie interwałów timerów.
     */
    void faster();

    /*!
     * \brief Powoduje zwiększanie interwałów timerów.
     */
    void slower();

    /*!
     * \brief Monitoruje sumę zebranych punktów i na odpowiednich
     * poziomach zmienia skin gracza
     */
    void checkEcts();
};

#endif // GAME_H
