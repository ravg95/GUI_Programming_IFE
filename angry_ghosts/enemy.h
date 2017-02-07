#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include "map.h"
#include "bomb.h"
#include "player.h"
class Bomb;
class Enemy:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(QGraphicsItem * parent=0,QGraphicsScene * scene=0,int enemynumber = 0, Player * player= 0);
    void attachtomap(Map* map);
    int x_pos ;
    int y_pos ;
    QGraphicsScene * scene;
    void attachscene(QGraphicsScene * scene);
    int  * current_map;
    Map * themap;
    Player * player;
    QTimer * timer1;
    QTimer * timer2;
    bool candown();
    bool canup();
    int animationcounter=1;
    bool canleft();
    bool canright();
    bool isgoing=false;
    int smallsteps=0;
    int currentdirection=1;
    bool end = false;
    void goup();
    void godown();
    void goleft();
    void goright();
    int enemynumber;
    int lives = 1;
    void theend();
public slots:
    void move();
    void animate();
};

#endif // ENEMY_H
