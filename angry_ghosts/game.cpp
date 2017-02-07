#include "game.h"
#include "map.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QImage>

Game::Game(QWidget *parent){
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,800);
    setBackgroundBrush(QBrush(QImage(":/images/map.png")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,800);
    themap = new Map;
    themap->map_loader();
    themap->starting_map(scene);
    player = new Player(0,scene);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->attachscene(scene);
    player->attachtomap(themap);
    enemy1 = new Enemy(0,scene,1,player);
    enemy2 = new Enemy(0,scene,2,player);
    enemy3 = new Enemy(0,scene,3,player);
    enemy1->attachscene(scene);
    enemy2->attachscene(scene);
    enemy3->attachscene(scene);
    enemy1->attachtomap(themap);
    enemy2->attachtomap(themap);
    enemy3->attachtomap(themap);
    scene->addItem(enemy1);
    scene->addItem(enemy2);
    scene->addItem(enemy3);
    scene->addItem(player);
    show();
}
