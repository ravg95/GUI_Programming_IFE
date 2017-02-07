#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include "map.h"
#include "bomb.h"
class Bomb;
class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0,QGraphicsScene * scene=0);
    void attachtomap(Map* map);
    void keyPressEvent(QKeyEvent * event);
    int x_pos = 0;
    int y_pos = 0;
    QGraphicsScene * scene;
    void attachscene(QGraphicsScene * scene);
    int  * current_map;
    Map * themap;
    QTimer * timer1;
    QTimer * timer2;
    QTimer * timer3;
    QTimer * timer4;
    bool candown();
    bool canup();
    int bombcounter=0;
    int animationcounter=1;
    Bomb * bombs[30];
    bool canleft();
    bool canright();
    bool isgoing=false;
    int smallsteps=0;
    int currentdirection=1;
    bool wascaught(int enemynumber);
    bool end = false;
    void goup();
    void godown();
    void goleft();
    void goright();
    int lives = 1;
    int speed =0;
    void increasespeed();
    void start3rdtimer();
    int bombrange= 1;
    void increasebombrange();
    int bomblimit = 1;
    void increasebomblimit();
public slots:
    void move();
    void animate();
    void theend();
    void win();
};

#endif // PLAYER_H
