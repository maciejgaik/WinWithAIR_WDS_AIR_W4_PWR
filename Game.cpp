#include "Game.h"

Game::Game(QWidget *parent){
    layout = new QVBoxLayout();
    window = new QWidget();

    //Tworzenie sceny
    gameScene =  new QGraphicsScene();
    gameScene->setSceneRect(0,0,600,800);
    gameScene->setBackgroundBrush(QBrush(QImage(":images/bg.png")));
    QGraphicsView * gameSceneView = new QGraphicsView(gameScene);
    gameSceneView->setFixedSize(605,805);
    layout->addWidget(gameSceneView, 0, Qt::AlignHCenter);

    //Tworzenie gracza i dodawanie do sceny
    makePlayer();

    //Wrogowie
    makeEnemy();

    //Napisy
    makeText();

    //Belka stusowa
    makeStatusBar();

    //Przyciski
    makeButtons();

    //Toolbar
    makeToolbar();

    //Zmiana skinu
    connect(timer1, SIGNAL(timeout()), this, SLOT(checkEcts()));

    //Wykresy
    plot();
    for(int i = 0; i <= 600; i++){
        x.append((600-i)/10.0);
        y0.append(0);
        y1.append(0);
    }

    layout->addWidget(customPlot);
    layout->addWidget(toolBar);
    window->setLayout(layout);
    setCentralWidget(window);

    delay();
}

void Game::plot(){
    customPlot = new QCustomPlot();
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setData(x,y0);
    customPlot->graph(1)->setPen(QPen(Qt::green));
    customPlot->graph(1)->setData(x,y1);
    customPlot->xAxis->setRange(0.0,x.size()/10.0);
    customPlot->xAxis->setRangeReversed(true);
    customPlot->yAxis->setRange(-90.0,90.0);
    customPlot->xAxis->setLabel("Time [s]");
    customPlot->yAxis->setLabel("Degree [\u00B0]");
    customPlot->yAxis->setTicker(fixedTicker);
    customPlot->graph(0)->setName("X");
    customPlot->graph(1)->setName("Y");
    fixedTicker->setTickStep(45.0);
    customPlot->replot();
}

void  Game::end(){
    qApp->quit();
}

void  Game::delay(){
    if(!gameOverFlag){
        if(timer2->isActive()){
            timer2->stop();
            player->stopMove();
            for(int i = 0; i < enemyList.size(); i++){
                enemyList[i]->stopMove();
            }
        }
        else{
            for(int i = 0; i < enemyList.size(); i++){
                enemyList[i]->startMove();
            }
            timer2->start();
            player->startMove();
        }
    }
}

void Game::spawn(){
    if(pEnemy < courseList.size()){
        enemyList.append(new Enemy(enemyMoveInterval, courseList[pEnemy]->getName(), courseList[pEnemy]->getEcts(), courseList[pEnemy]->getStatus()));
        gameScene->addItem(enemyList.back());
        gameScene->addItem(enemyList.back()->nameText);
        gameScene->addItem(enemyList.back()->ectsText);
        pEnemy++;
    }
}

void Game::textStatusBar(){
    if (player->checkConn()){
        statusText->setText("Połączono");
        statusDot->setStyleSheet("background-color: green; border-radius: 5px;");
    }
    else{
        statusText->setText("Nie połączono");
        statusDot->setStyleSheet("background-color: red; border-radius: 5px;");
    }
}

void Game::addPoint(double xGyro, double yGyro){
    if(y0.size() <= 600 && y1.size() <= 600){
        y0.append(yGyro);
        y1.append(xGyro);
    }
    else{
        y0.removeFirst();
        y0.append(yGyro);
        y1.removeFirst();
        y1.append(xGyro);
    }
    customPlot->graph(0)->setData(x,y0);
    customPlot->graph(1)->setData(x,y1);
    customPlot->xAxis->setRange(0.0,x.size()/10.0);
    customPlot->replot();
    customPlot->update();
}

void Game::makeEnemy(){
    timer2 = new QTimer();

    courseList.append(new Course("       Analiza\nMatematyczna 1", 10));
    courseList.append(new Course("Filozofia", 2));
    courseList.append(new Course("Algebra liniowa", 6));
    courseList.append(new Course("Etyka inzynierska", 1));
    courseList.append(new Course("Technologie\ninformacyjne", 2));
    courseList.append(new Course("  Wlasnosc\nintelektualna", 1));
    courseList.append(new Course("   Podstawy\nprogramowania", 4));
    courseList.append(new Course("Miernictwo", 4));

    courseList.append(new Course("        Rachunek\nprawdopodobienstwa", 2));
    courseList.append(new Course("       Analiza\nmatematyczna 2", 5));
    courseList.append(new Course("Miernictwo 2", 2));
    courseList.append(new Course("Matematyka", 3));
    courseList.append(new Course("Podstawy AiR", 2));
    courseList.append(new Course("Fizyka 1.1", 5));
    courseList.append(new Course("Programowanie\n   obiektowe", 6));
    courseList.append(new Course("Teoria systemów", 3));
    courseList.append(new Course("Fizyka 3.3", 2));

    courseList.append(new Course("Fizyka 3.1", 2));
    courseList.append(new Course("Statystyka", 5));
    courseList.append(new Course("Podstawy przet. syg.", 5));
    courseList.append(new Course("    Podstawy\ntelekomunikacji", 2));
    courseList.append(new Course("Druty", 4));
    courseList.append(new Course("Mechanika\nanalityczna", 4));
    courseList.append(new Course("Jezyk obcy 1", 2));
    courseList.append(new Course("Modele układów\n  dynamicznych", 6));

    courseList.append(new Course(" Podstawy techniki\nmikroprocesorowej 1", 3));
    courseList.append(new Course("Teoria regulacji", 5));
    courseList.append(new Course("PAMSI", 5));
    courseList.append(new Course("            SCR\nSieci komputerowe", 4));
    courseList.append(new Course("Systemy analogowe\n      i cyfrowe", 4));
    courseList.append(new Course("Język 2", 3));
    courseList.append(new Course("Urzadzenia obiektowe\n       automatyki", 6));

    courseList.append(new Course(" Podstawy techniki\nmikroprocesorowej 2", 2));
    courseList.append(new Course("Sterowniki i regulatory", 5));
    courseList.append(new Course("             SCR\nSystemy operacyjne", 4));
    courseList.append(new Course("Interfejsy obiektowe", 5));
    courseList.append(new Course("Stero. proces. ciag.", 3));
    courseList.append(new Course("Robotyka 1", 5));
    courseList.append(new Course("Metody numeryczne", 3));
    courseList.append(new Course("CPOIS", 3));

    courseList.append(new Course("Stero. proces. dysk.", 5));
    courseList.append(new Course("Bazy danych", 3));
    courseList.append(new Course("Robotyka 2", 3));
    courseList.append(new Course("Techniki komputerowe\n         w robotyce.", 3));
    courseList.append(new Course(" Wizualiazacja\ndanych sensor.", 5));
    courseList.append(new Course("Sterowniki robotow", 5));
    courseList.append(new Course("Roboty mobilne", 2));
    courseList.append(new Course("Projekt zespolowy", 4));

    courseList.append(new Course("PZJZEP", 2));
    courseList.append(new Course("Praktyka zawodowa", 6));
    courseList.append(new Course("Projekt spec.", 2));
    courseList.append(new Course("Mechatronika", 1));
    courseList.append(new Course("Robotyka 3", 2));
    courseList.append(new Course("Zaawan. met. program.", 2));
    courseList.append(new Course("Seminarium dyplomowe", 3));
    courseList.append(new Course("Praca dyplomowa", 12));

    connect(timer2, SIGNAL(timeout()), this, SLOT(spawn()));
    timer2->start(2000);
}

void Game::newGame(){
    pEnemy = 0;
    textSpeed = 100;
    enemyMoveInterval = 50;
    timer2->setInterval(2000);
    gameOverFlag = false;
    while(enemyList.size() > 0)
        enemyList.removeLast();
    for(int i = 0; i < courseList.size(); i++)
        courseList[i]->changeStatus(false);
    player->cleanPort();
    gameScene->clear();
    makePlayer();
    makeText();
}

void Game::faster(){
    textSpeed += 10;
    speedText->setPlainText("Predkosc: " + QString::number(textSpeed) + "%");
    timer2->setInterval(0.9*timer2->interval());
    enemyMoveInterval *= 0.9;
    for(int i = 0; i < enemyList.size(); i++){
        enemyList[i]->faster();
    }
}

void Game::slower(){
    textSpeed -= 10;
    speedText->setPlainText("Predkosc: " + QString::number(textSpeed) + "%");
    timer2->setInterval(timer2->interval()/0.9);
    enemyMoveInterval /= 0.9;
    for(int i = 0; i < enemyList.size(); i++){
        enemyList[i]->slower();
    }
}

void Game::checkEcts(){
    if(score->getScore() >= 30 && score->getScore() < 60)        player->changeSkin(2);
    else if(score->getScore() >= 60 && score->getScore() < 90)   player->changeSkin(3);
    else if(score->getScore() >= 90 && score->getScore() < 120)  player->changeSkin(4);
    else if(score->getScore() >= 120 && score->getScore() < 150) player->changeSkin(5);
    else if(score->getScore() == 150 && score->getScore() < 180) player->changeSkin(6);
    //else player->changeSkin(1);
}

void Game::deleteEnemy(){
    for(int i = enemyList.size(); i == 0; i--){
        enemyList.removeLast();
    }
}

void Game::gameOver(bool win){
    delay();
    gameOverText = new QGraphicsTextItem;
    if(!win){
        gameOverText->setPlainText(QString("Przekroczono deficyt!"));
    }
    else if(win){
        gameOverText->setPlainText(QString("    Gratulacje!\nUzyskałeś tytuł\n     inż. AiR!"));
    }
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("times",42));
    gameScene->addItem(gameOverText);
    gameOverText->setPos(gameScene->width()/2-gameOverText->boundingRect().width()/2,gameScene->height()/2-gameOverText->boundingRect().height()/2);
    gameOverFlag = true;
}

void Game::makePlayer(){
    player = new Player();
    gameScene->addItem(player);
   // player->setRect(0,0,100,100);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos((gameScene->width() - player->boundingRect().width()*player->getScale())/2, gameScene->height() - player->boundingRect().height()*player->getScale());
}

void Game::makeText(){
    score = new Score();
    gameScene->addItem(score);
    deficit = new Deficit();
    gameScene->addItem(deficit);
    deficit->setY(17);
    speedText = new QGraphicsTextItem("Predkosc: " + QString::number(textSpeed) + "%");
    speedText->setPos(gameScene->width()-speedText->boundingRect().width(),0);
    speedText->setDefaultTextColor(Qt::darkBlue);
    gameScene->addItem(speedText);
}

void Game::makeButtons(){
    //Przycisk wolniej
    slowerButton = new QPushButton(QObject::tr("<<"));
    connect(slowerButton, SIGNAL(clicked()), this, SLOT(slower()));

    //Przycisk szybciej
    fasterButton = new QPushButton(QObject::tr(">>"));
    connect(fasterButton, SIGNAL(clicked()), this, SLOT(faster()));

    //Przycisk Zamknij
    closeButton = new QPushButton(QObject::tr("Zamknij"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(end()));
    closeButton->setMinimumSize(90,32);

    //Przycisk nowa gra
    newGameButton = new QPushButton(QObject::tr("Reset"));
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));
    newGameButton->setMinimumSize(90,32);

    //Przycisk pauza
    pauseButton = new QPushButton(QObject::tr("Start/Stop"));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(delay()));
    pauseButton->setMinimumSize(90,32);
}

void Game::makeToolbar(){
    QLabel *legendText1 = new QLabel();
    QLabel *legendText2 = new QLabel();
    QLabel *legendDot1= new QLabel();
    QLabel *legendDot2 = new QLabel();
    legendText1->setText("Gyro X");
    legendText2->setText("Gyro Y");
    legendDot1->setFixedSize(10,10);
    legendDot1->setStyleSheet("background-color: rgb(0,255,0); border-radius: 5px;");
    legendDot2->setFixedSize(10,10);
    legendDot2->setStyleSheet("background-color: blue; border-radius: 5px;");

    toolBar = new QToolBar();
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(legendDot1);
    toolBar->addWidget(legendText1);
    toolBar->addWidget(legendDot2);
    toolBar->addWidget(legendText2);
    toolBar->addWidget(spacer);
    toolBar->addWidget(slowerButton);
    toolBar->addWidget(fasterButton);
    toolBar->addWidget(closeButton);
    toolBar->addWidget(newGameButton);
    toolBar->addWidget(pauseButton);
}

void Game::makeStatusBar(){
    statusBar = new QStatusBar();
    setStatusBar(statusBar);
    statusDot = new QLabel(this);
    statusText = new QLabel(this);
    statusDot->setFixedSize(10,10);
    statusDot->setStyleSheet("background-color: red; border-radius: 5px;");
    statusBar->addWidget(statusDot);
    statusText->setText("Nie połączono");
    statusBar->addWidget(statusText);
    timer1 =  new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(textStatusBar()));
    timer1->start(100);
}

