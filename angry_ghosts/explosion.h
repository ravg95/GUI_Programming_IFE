#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "map.h"
#include "bomb.h"
#include "player.h"
class Bomb;
class Player;
class Explosion:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Explosion(QGraphicsScene * scene,QGraphicsItem * parent=0,bool center= true, bool end=true ,int direction=0,Map* map=0,int x_coord=0, int y_coord=0,Bomb*bomb=0,Player * player=0);
    int direction;
    bool center;
    bool end;
    int counter = 0;
    int x_coord;
    int y_coord;
    Player * player;
    Map * map;
    QGraphicsScene * scene;
    Bomb * bomb;
    public slots:
    void stages();
};


#endif // EXPLOSION_H
