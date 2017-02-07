#ifndef BOMB_H
#define BOMB_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include "player.h"
#include "explosion.h"
#include "map.h"
class Player;
class Explosion;
class Bomb:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bomb(QGraphicsItem * parent=0,int x_coord=0, int y_coord=0, int range = 1, QGraphicsScene * scene=0,Map * map=0,Player* player=0);
    int x_coord;
    int y_coord;
    int range;
    Explosion * explosions[100];
    int explosioncounter=0;
    QGraphicsScene * scene;
    Map * themap;
    Player * player;
    void getcoords();
    bool boom = false;
    bool breaker = false;
    QTimer * timer;
    QTimer * timer2;
    QTimer * timer3;
public slots:
    void ticktock();
    void ready();
    void fallstart();
};


#endif // BOMB_H
