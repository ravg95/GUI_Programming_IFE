#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "player.h"
#include "map.h"
#include "crate.h"
#include "enemy.h"
class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    Player * player;
    Map * themap;
    Crate * crates;
    QGraphicsScene * scene;
    QTimer * timer;
    Enemy * enemy1;
    Enemy * enemy2;
    Enemy * enemy3;

    void theend();
};

#endif // GAME_H
