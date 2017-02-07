#include "explosion.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>


Explosion::Explosion(QGraphicsScene * scene,QGraphicsItem *parent,bool center,bool end, int direction,Map * map,int x_coord, int y_coord,Bomb* bomb, Player * player): QObject(), QGraphicsPixmapItem(parent){
    this->direction = direction;
    this->end = end;
    this->center = center;
    this->map = map;
    this->x_coord = x_coord;
    this->y_coord = y_coord;
    this->scene = scene;
    this->bomb = bomb;
    this->player = player;
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(stages()));
    timer->start(40);
}

void Explosion::stages()
{

    if(counter < 1){
        if(center){
            setPixmap(QPixmap(":/images/cross1.png"));
        }
        else if(direction == 1){
            if(end){
                setPixmap(QPixmap(":/images/topend1.png"));
            }
            else{
                setPixmap(QPixmap(":/images/updown1.png"));
            }
        }
        else if(direction == 2){\
            if(end){
                setPixmap(QPixmap(":/images/bottomend1.png"));
            }
            else{
                setPixmap(QPixmap(":/images/updown1.png"));
            }

        }
        else if (direction == 3){
            if(end){
                setPixmap(QPixmap(":/images/leftend1.png"));
            }
            else{
                setPixmap(QPixmap(":/images/leftright1.png"));
            }

        }
        else if (direction == 4){
            if(end){
                setPixmap(QPixmap(":/images/rightend1.png"));
            }
            else{
                setPixmap(QPixmap(":/images/leftright1.png"));
            }

        }

    }
    else if( counter < 2 ){
        if(center){
            setPixmap(QPixmap(":/images/cross2.png"));
        }
        else if(direction == 1){
            if(end){
                setPixmap(QPixmap(":/images/topend2.png"));
            }
            else{
                setPixmap(QPixmap(":/images/updown2.png"));
            }
        }
        else if(direction == 2){\
            if(end){
                setPixmap(QPixmap(":/images/bottomend2.png"));
            }
            else{
                setPixmap(QPixmap(":/images/updown2.png"));
            }

        }
        else if (direction == 3){
            if(end){
                setPixmap(QPixmap(":/images/leftend2.png"));
            }
            else{
                setPixmap(QPixmap(":/images/leftright2.png"));
            }

        }
        else if (direction == 4){
            if(end){
                setPixmap(QPixmap(":/images/rightend2.png"));
            }
            else{
                setPixmap(QPixmap(":/images/leftright2.png"));
            }

        }

    }
    else if(counter < 3){
        if(center){
            setPixmap(QPixmap(":/images/cross3.png"));
        }
        else if(direction == 1){
            if(end){
                setPixmap(QPixmap(":/images/topend3.png"));
            }
            else{
                setPixmap(QPixmap(":/images/updown3.png"));
            }
        }
        else if(direction == 2){\
            if(end){
                setPixmap(QPixmap(":/images/bottomend3.png"));
            }
            else{
                setPixmap(QPixmap(":/images/updown3.png"));
            }

        }
        else if (direction == 3){
            if(end){
                setPixmap(QPixmap(":/images/leftend3.png"));
            }
            else{
                setPixmap(QPixmap(":/images/leftright3.png"));
            }

        }
        else if (direction == 4){
            if(end){
                setPixmap(QPixmap(":/images/rightend3.png"));
            }
            else{
                setPixmap(QPixmap(":/images/leftright3.png"));
            }

        }

    }
    else if ( counter < 7){
        if(center){
            setPixmap(QPixmap(":/images/cross4.png"));
        }
        else if(direction == 1){
            if(end){
                setPixmap(QPixmap(":/images/topend4.png"));
            }
            else{
                setPixmap(QPixmap(":/images/updown4.png"));
            }
        }
        else if(direction == 2){\
            if(end){
                setPixmap(QPixmap(":/images/bottomend4.png"));
            }
            else{
                setPixmap(QPixmap(":/images/updown4.png"));
            }

        }
        else if (direction == 3){
            if(end){
                setPixmap(QPixmap(":/images/leftend4.png"));
            }
            else{
                setPixmap(QPixmap(":/images/leftright4.png"));
            }

        }
        else if (direction == 4){
            if(end){
                setPixmap(QPixmap(":/images/rightend4.png"));
            }
            else{
                setPixmap(QPixmap(":/images/leftright4.png"));
            }

        }

    }
    else {
        this->scene->removeItem(this);
        delete this;
        return;
    }
    if(this->player->end){
        counter = 8;
    }
    counter++;
    return;
}
