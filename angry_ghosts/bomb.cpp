#include "bomb.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>


Bomb::Bomb(QGraphicsItem *parent, int x_coord, int y_coord, int range, QGraphicsScene * scene,Map * map,Player *player): QObject(), QGraphicsPixmapItem(parent){
    QPixmap img(":/images/bomb.png");
    QPixmap img2 = img.scaled(53, 53, Qt::KeepAspectRatio);
    setPixmap(QPixmap(img2));
    this->scene = scene;
    this->timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ticktock()));
    timer->start(3000);
    this->timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(fallstart()));
    this->timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(ready()));
    timer2->start(20);
    this->x_coord = x_coord;
    this->y_coord = y_coord;
    this->range = range;
    this->player = player;
    this->themap = map;
}

void Bomb::ticktock()
{
    this->boom = true;
    this->explosions[this->explosioncounter] = new Explosion(this->scene,0,1,0,0,0,0,0,0,this->player);
    this->scene->addItem(this->explosions[this->explosioncounter]);
    this->explosions[this->explosioncounter]->setPos(47+(this->x_coord)*705/13,49+(this->y_coord)*705/13);
    this->themap->setexplo(this->x_coord,this->y_coord);
    this->explosioncounter++;
    this->scene->removeItem(this);
    int currentrange=1;
    while(currentrange<=this->range){
        if((y_coord+currentrange)>12){
            break;
        }
        if((this->themap->current_map[this->y_coord+currentrange][this->x_coord]) == 2){
            break;
        }
        if((this->themap->current_map[this->y_coord+currentrange][this->x_coord]) == 1){
            this->themap->removecrate(this->x_coord, this->y_coord+currentrange);
            this->breaker = true;
        }
        if(currentrange == this->range){
        this->explosions[this->explosioncounter] = new Explosion(this->scene,0,0,1,2,this->themap,this->x_coord, this->y_coord+currentrange,this,this->player);
        }
        else{
        this->explosions[this->explosioncounter] = new Explosion(this->scene,0,0,0,2,this->themap,this->x_coord, this->y_coord+currentrange,this,this->player);
        }
        this->scene->addItem(this->explosions[this->explosioncounter]);
        this->explosions[this->explosioncounter]->setPos(47+(this->x_coord)*705/13,49+(this->y_coord+currentrange)*705/13);
        this->themap->setexplo(this->x_coord,this->y_coord+currentrange);
        this->explosioncounter++;
        currentrange++;
        if(this->breaker) break;
    }
    this->breaker = false;
    currentrange =1;
    while(currentrange<=this->range){
        if(y_coord - currentrange < 0){
            break;
        }
        if((this->themap->current_map[this->y_coord-currentrange][this->x_coord]) == 2){
            break;
        }
        else if((this->themap->current_map[this->y_coord-currentrange][this->x_coord]) == 1){
            this->themap->removecrate(this->x_coord, this->y_coord-currentrange);
            this->breaker = true;
        }
        if(currentrange == this->range){
        this->explosions[this->explosioncounter] = new Explosion(this->scene,0,0,1,1,this->themap,this->x_coord, this->y_coord-currentrange,this,this->player);
        }
        else{
        this->explosions[this->explosioncounter] = new Explosion(this->scene,0,0,0,1,this->themap,this->x_coord, this->y_coord-currentrange,this,this->player);
        }
        this->scene->addItem(this->explosions[this->explosioncounter]);
        this->explosions[this->explosioncounter]->setPos(47+(this->x_coord)*705/13,49+(this->y_coord-currentrange)*705/13);
        this->themap->setexplo(this->x_coord,this->y_coord-currentrange);
        this->explosioncounter++;
        currentrange++;
        if(this->breaker) break;
    }
    this->breaker = false;
    currentrange =1;
    while(currentrange<=this->range){
        if(x_coord-currentrange < 0){
            break;
        }
        if((this->themap->current_map[this->y_coord][this->x_coord-currentrange]) == 2){
            break;
        }
        if((this->themap->current_map[this->y_coord][this->x_coord-currentrange]) == 1){
            this->themap->removecrate(this->x_coord-currentrange, this->y_coord);
            this->breaker = true;
        }
        if(currentrange == this->range){
        this->explosions[this->explosioncounter] = new Explosion(this->scene,0,0,1,3,this->themap,this->x_coord-currentrange, this->y_coord,this,this->player);
        }
        else{
        this->explosions[this->explosioncounter] = new Explosion(this->scene,0,0,0,3,this->themap,this->x_coord-currentrange, this->y_coord,this,this->player);
        }
        this->scene->addItem(this->explosions[this->explosioncounter]);
        this->explosions[this->explosioncounter]->setPos(47+(this->x_coord-currentrange)*705/13,49+(this->y_coord)*705/13);
        this->themap->setexplo(this->x_coord-currentrange,this->y_coord);
        this->explosioncounter++;
        currentrange++;
        if(breaker) break;
    }
    currentrange =1;
    this->breaker = false;
    while(currentrange<=this->range){
        if(x_coord + currentrange > 12 ){
            break;
        }
        if((this->themap->current_map[this->y_coord][this->x_coord+currentrange]) == 2){
            break;
        }
        if((this->themap->current_map[this->y_coord][this->x_coord+currentrange])  == 1){
           this->themap->removecrate(this->x_coord+currentrange, this->y_coord);
            this->breaker = true;
        }
        if(currentrange == this->range){
        this->explosions[this->explosioncounter] = new Explosion(this->scene,0,0,1,4,this->themap,this->x_coord+currentrange, this->y_coord,this,this->player);
        }
        else{
        this->explosions[this->explosioncounter] = new Explosion(this->scene,0,0,0,4,this->themap,this->x_coord+currentrange, this->y_coord,this,this->player);
        }
        this->scene->addItem(this->explosions[this->explosioncounter]);
        this->explosions[this->explosioncounter]->setPos(47+(this->x_coord+currentrange)*705/13,49+(this->y_coord)*705/13);
        this->themap->setexplo(this->x_coord+currentrange,this->y_coord);
        this->explosioncounter++;
        currentrange++;
        if(this->breaker) break;
    }


    timer3->start(30);
    timer->stop();
    return;
}

void Bomb::ready(){
    if(this->player->end){
        timer->stop();
        timer2->stop();
        delete this;
        return;
    }
    if(this->boom)return;
    if(this->themap->isexplo(x_coord, y_coord)){
        timer->stop();
        timer2->stop();
        timer->start(10);
    }
}
void Bomb::fallstart(){
       this->themap->clearexplo();
       player->bombcounter--;
       delete this;
}
