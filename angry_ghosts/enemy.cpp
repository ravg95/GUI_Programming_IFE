#include "enemy.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <cstdlib>
#include <time.h>


Enemy::Enemy(QGraphicsItem *parent,QGraphicsScene * scene, int enemynumber, Player * player): QObject(), QGraphicsPixmapItem(parent){
    this->enemynumber = enemynumber;
    this->player = player;
    if(this->enemynumber == 1){
        setPos(45+12*705/13,49);
        this->x_pos = 12;
        this->y_pos = 0;
        this->player->themap->enemiescoords[enemynumber-1][0] = this->x_pos;
        this->player->themap->enemiescoords[enemynumber-1][1] = this->y_pos;
    }
    else if(this->enemynumber == 2){
        setPos(45,49+12*705/13);
        this->x_pos = 0;
        this->y_pos = 12;
        this->player->themap->enemiescoords[enemynumber-1][0] = this->x_pos;
        this->player->themap->enemiescoords[enemynumber-1][1] = this->y_pos;
    }
    else if (this->enemynumber == 3){
        setPos(45+12*705/13,49+12*705/13);
        this->x_pos = 12;
        this->y_pos = 12;
        this->player->themap->enemiescoords[enemynumber-1][0] = this->x_pos;
        this->player->themap->enemiescoords[enemynumber-1][1] = this->y_pos;
    }
    this->timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(animate()));
    timer2->start(120);
    this->timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(move()));
    timer1->start(10);
    this->scene = scene;
    srand (time(NULL));
}

void Enemy::attachtomap(Map *map){
    this->themap = map;
}

void Enemy::attachscene(QGraphicsScene *scene)
{
    this->scene = scene;
}

bool Enemy::candown(){
    if(this->y_pos == 12){
        return false;
    }
    if(this->themap->current_map[this->y_pos+1][this->x_pos] != 0){
        return false;
    }
    return true;
}
bool Enemy::canup(){
    if(this->y_pos == 0){
        return false;
    }
    if(this->themap->current_map[this->y_pos-1][this->x_pos] != 0){
        return false;
    }
    return true;
}
bool Enemy::canright(){
    if(this->x_pos == 12){
        return false;
    }
    if(this->themap->current_map[this->y_pos][this->x_pos+1] != 0){
        return false;
    }
    return true;
}

bool Enemy::canleft(){
    if(this->x_pos == 0){
        return false;
    }
    if(this->themap->current_map[this->y_pos][this->x_pos-1] != 0){
        return false;
    }
    return true;
}


void Enemy::goup(){
    this->isgoing = true;
    this->setPos(this->x(),this->y()-2);
    this->currentdirection = 1;
    this->smallsteps+=2;
    if ( this->smallsteps == 28){
        this->y_pos-=1;
    }
    if (this->smallsteps == 54){
        this->smallsteps = 0;
        this->isgoing = false;
    }
}

void Enemy::godown(){
    this->isgoing = true;
    this->setPos(this->x(),this->y()+2);
    this->currentdirection = 2;
    this->smallsteps+=2;
    if (this->smallsteps == 28){
        this->y_pos+=1;
    }
    if (this->smallsteps == 54){
        this->smallsteps = 0;
        this->isgoing = false;
    }
}

void Enemy::goleft(){
    this->isgoing = true;
    this->setPos(this->x()-2,this->y());
    this->currentdirection = 3;
    this->smallsteps+=2;
    if(this->smallsteps == 28){
        this->x_pos-=1;
    }
    if (this->smallsteps == 54){
        this->smallsteps = 0;
        this->isgoing = false;
    }
}

void Enemy::goright(){
    this->isgoing = true;
    this->setPos(this->x()+2,this->y());
    this->currentdirection = 4;
    this->smallsteps+=2;
    if(this->smallsteps == 28){
        this->x_pos+=1;
    }
    if (this->smallsteps == 54){
        this->smallsteps = 0;
        this->isgoing = false;
    }
}

void Enemy::theend(){
    this->scene->removeItem(this);
    delete this;
}

void Enemy::move(){
    int whichdirection = rand() %16 + 1;
    if(this->themap->isexplo(this->x_pos,this->y_pos)){
        this->player->end = true;
        theend();
    }
    else if(this->isgoing){
        if(this->currentdirection == 1){
            this->goup();
        }
        else if (this->currentdirection == 2){
            this->godown();
        }
        else if (this->currentdirection == 3){
            this->goleft();
        }
        else if (this->currentdirection == 4){
            this->goright();
        }
    }
    else if(whichdirection <= 4 ){
        if(this->canup()){
            this->goup();
        }
    }
    else if(whichdirection > 4 && whichdirection <= 8 ){
        if(this->candown()){
            this->godown();
        }
    }
    else if(whichdirection > 8 && whichdirection <= 12 ){
        if(this->canleft()){
            this->goleft();
        }
    }
    else if(whichdirection > 12 && whichdirection <=16 ){
        if(this->canright()){
            this->goright();
        }
    }
}

void Enemy::animate()
{
    if(this->enemynumber == 1){
        this->player->themap->enemiescoords[0][0] = this->x_pos;
        this->player->themap->enemiescoords[0][1] = this->y_pos;
        if(this->animationcounter == 1 && this->currentdirection == 1){
            this->setPixmap(QPixmap(":/images/ghostuporange1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 2){
            this->setPixmap(QPixmap(":/images/ghostdownorange1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 3){
            this->setPixmap(QPixmap(":/images/ghostleftorange1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 4){
            this->setPixmap(QPixmap(":/images/ghostrightorange1.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 1){
            this->setPixmap(QPixmap(":/images/ghostuporange2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 2){
            this->setPixmap(QPixmap(":/images/ghostdownorange2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 3){
            this->setPixmap(QPixmap(":/images/ghostleftorange2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 4){
            this->setPixmap(QPixmap(":/images/ghostrightorange2.png"));
        }
    }
    if(this->enemynumber == 2){
        this->player->themap->enemiescoords[1][0] = this->x_pos;
        this->player->themap->enemiescoords[1][1] = this->y_pos;
        if(this->animationcounter == 1 && this->currentdirection == 1){
            this->setPixmap(QPixmap(":/images/ghostupred1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 2){
            this->setPixmap(QPixmap(":/images/ghostdownred1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 3){
            this->setPixmap(QPixmap(":/images/ghostleftred1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 4){
            this->setPixmap(QPixmap(":/images/ghostrightred1.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 1){
            this->setPixmap(QPixmap(":/images/ghostupred2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 2){
            this->setPixmap(QPixmap(":/images/ghostdownred2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 3){
            this->setPixmap(QPixmap(":/images/ghostleftred2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 4){
            this->setPixmap(QPixmap(":/images/ghostrightred2.png"));
        }
    }
    if(this->enemynumber == 3){
        this->player->themap->enemiescoords[2][0] = this->x_pos;
        this->player->themap->enemiescoords[2][1] = this->y_pos;
        if(this->animationcounter == 1 && this->currentdirection == 1){
            this->setPixmap(QPixmap(":/images/ghostup1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 2){
            this->setPixmap(QPixmap(":/images/ghostdown1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 3){
            this->setPixmap(QPixmap(":/images/ghostleft1.png"));
        }
        else if(this->animationcounter == 1 && this->currentdirection == 4){
            this->setPixmap(QPixmap(":/images/ghostright1.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 1){
            this->setPixmap(QPixmap(":/images/ghostup2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 2){
            this->setPixmap(QPixmap(":/images/ghostdown2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 3){
            this->setPixmap(QPixmap(":/images/ghostleft2.png"));
        }
        else if(this->animationcounter == 2 && this->currentdirection == 4){
            this->setPixmap(QPixmap(":/images/ghostright2.png"));
        }
    }
    this->animationcounter++;
    if(this->animationcounter == 3){
        this->animationcounter = 1;
    }
}
