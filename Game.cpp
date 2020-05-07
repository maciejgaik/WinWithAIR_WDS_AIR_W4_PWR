#include "Game.h"

Game::Game(QWidget *parent){
    layout = new QVBoxLayout();
    window = new QWidget();

    //Tworzenie sceny
    gameScene =  new QGraphicsScene();
    gameScene->setSceneRect(0,0,600,800);
    QGraphicsView * gameSceneView = new QGraphicsView(gameScene);
    gameSceneView->setFixedSize(600,800);
    layout->addWidget(gameSceneView, 0, Qt::AlignHCenter);

    //Tworzenie gracza i dodawanie do sceny
    player = new Player();
    gameScene->addItem(player);
    player->setRect(0,0,100,100);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos((gameScene->width() - player->rect().width())/2, gameScene->height() - player->rect().height());

    //Wrogowie
    makeEnemy();

    //Punktacja
    score = new Score();
    gameScene->addItem(score);

    deficit = new Deficit();
    gameScene->addItem(deficit);
    deficit->setY(17);

    //Belka stusowa
    statusBar = new QStatusBar();

    setStatusBar(statusBar);
    dot = new QLabel(this);
    text = new QLabel(this);
    dot->setFixedSize(10,10);
    dot->setStyleSheet("background-color: red; border-radius: 5px;");
    statusBar->addWidget(dot);
    text->setText("Nie połączono");
    statusBar->addWidget(text);

    //Polaczenie z portem
    timer1 =  new QTimer();
    connect(timer1, SIGNAL(timeout()), player, SLOT(UART())); //Proba nawiazania polaczenia co 2s
    timer1->start(2000);

    timer2 =  new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(textStatusBar()));
    timer2->start(100);

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

    //Przycisk Zamknij
    toolBar = new QToolBar();
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(legendDot1);
    toolBar->addWidget(legendText1);
    toolBar->addWidget(legendDot2);
    toolBar->addWidget(legendText2);
    toolBar->addWidget(spacer);
    closeButton = new QPushButton(QObject::tr("Zamknij"));
    toolBar->addWidget(closeButton);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(end()));


    //Przycisk pauza
    pauseButton = new QPushButton(QObject::tr("Pauza"));
    toolBar->addWidget(pauseButton);
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(delay()));

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

    pEnemy = 0;
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
    if(timer1->isActive()){
        timer1->stop();
        timer4->stop();
        for(int i = 0; i < enemyList.size(); i++){
            enemyList[i]->stopMove();
        }
    }
    else{
        for(int i = 0; i < enemyList.size(); i++){
            enemyList[i]->startMove();
        }
        timer1->start();
        timer4->start();
    }
}

void Game::spawn(){
    enemyList.append(new Enemy(courseList[pEnemy]->getName(), courseList[pEnemy]->getEcts()));
    if(pEnemy <= courseList.size()){
        gameScene->addItem(enemyList.back());
        qDebug() << enemyList.back()->getName() << enemyList.back()->getEcts();
        pEnemy++;
    }
}

void Game::textStatusBar(){
    if (player->checkConn()){
        //statusBar->showMessage("Połączono");
        text->setText("Połączono");
        //statusBar->addWidget(text);
        dot->setStyleSheet("background-color: green; border-radius: 5px;");
    }
    else{
        //statusBar->showMessage("Nie połączono");
        text->setText("Nie połączono");
        //statusBar->addWidget(text);
        dot->setStyleSheet("background-color: red; border-radius: 5px;");
    }
}

void Game::addPoint(double xGyro, double yGyro){
    if(y0.size() <= 600 && y1.size() <= 600){
        y0.append(xGyro);
        y1.append(yGyro);
    }
    else{
        y0.removeFirst();
        y0.append(xGyro);
        y1.removeFirst();
        y1.append(yGyro);
    }
    customPlot->graph(0)->setData(x,y0);
    customPlot->graph(1)->setData(x,y1);
    customPlot->xAxis->setRange(0.0,x.size()/10.0);
    customPlot->replot();
    customPlot->update();
}

void Game::makeEnemy(){
    timer4 = new QTimer();

    courseList.append(new Course("Analiza Matematyczna 1", 10));
    courseList.append(new Course("Filozofia", 2));
    courseList.append(new Course("Algebra liniowa", 6));
    courseList.append(new Course("Etyka inzynierska", 1));
    courseList.append(new Course("Technologie informacyjne", 2));
    courseList.append(new Course("Wlasnosc intelektualna", 1));
    courseList.append(new Course("Podstawy programowania", 4));
    courseList.append(new Course("Miernictwo", 4));

    courseList.append(new Course("Rachunek prawdopodobienstwa", 2));
    courseList.append(new Course("Analiza matematyczna 2", 5));
    courseList.append(new Course("Miernictwo 2", 2));
    courseList.append(new Course("Matematyka", 3));
    courseList.append(new Course("Podstawy AiR", 2));
    courseList.append(new Course("Fizyka 1.1", 5));
    courseList.append(new Course("Programowanie obiektowe", 6));
    courseList.append(new Course("Teoria systemów", 3));
    courseList.append(new Course("Fizyka 3.3", 2));

    courseList.append(new Course("Fizyka 3.1", 2));
    courseList.append(new Course("Statystyka", 5));
    courseList.append(new Course("Podstawy przet. syg.", 5));
    courseList.append(new Course("Podstawy telekomunikacji", 2));
    courseList.append(new Course("Druty", 4));
    courseList.append(new Course("Mechanika analityczna", 4));
    courseList.append(new Course("Jezyk obcy 1", 2));
    courseList.append(new Course("Modele u. dynamicznych", 6));

    courseList.append(new Course("Podstawy tech. mikroproc. 1", 3));
    courseList.append(new Course("Teoria regulacji", 5));
    courseList.append(new Course("PAMSI", 5));
    courseList.append(new Course("SCR - Sieci komputerowe", 4));
    courseList.append(new Course("Systemy analog. i cyf.", 4));
    courseList.append(new Course("Język 2", 3));
    courseList.append(new Course("Urzadzenia obiekt. automa.", 6));

    courseList.append(new Course("Podstawy tech. mikroproc. 2", 2));
    courseList.append(new Course("Sterowniki i regulatory", 5));
    courseList.append(new Course("SCR - Systemy operacyjne", 4));
    courseList.append(new Course("Interfejsy obiektowe", 5));
    courseList.append(new Course("Stero. proces. ciag.", 3));
    courseList.append(new Course("Robotyka 1", 5));
    courseList.append(new Course("Metody numeryczne", 3));
    courseList.append(new Course("CPOIS", 3));

    courseList.append(new Course("Stero. proces. dysk.", 5));
    courseList.append(new Course("Bazy danych", 3));
    courseList.append(new Course("Robotyka 2", 3));
    courseList.append(new Course("Tech. komput. w robo.", 3));
    courseList.append(new Course("Wizualiazacja d. sensor.", 5));
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

    connect(timer4, SIGNAL(timeout()), this, SLOT(spawn()));
    timer4->start(2000);
}
