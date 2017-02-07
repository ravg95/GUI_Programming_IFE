#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>


Player::Player(QGraphicsItem *parent,QGraphicsScene * scene): QObject(), QGraphicsPixmapItem(parent){
    setPos(45,49);
    this->timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(animate()));
    timer2->start(120);
    this->timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(move()));
    timer1->start(16);
    this->timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(theend()));
    timer3->start(50);
    this->timer4 = new QTimer(this);
    connect(timer4,SIGNAL(timeout()),this,SLOT(win()));
    timer4->start(150);
    this->scene = scene;
}

void Player::attachtomap(Map *map){
    this->themap = map;
}


void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        if(this->canleft() && !isgoing){
            this->goleft();
            this->currentdirection = 3;
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(this->canright() && !isgoing){
            this->goright();
            this->currentdirection = 4;
        }
    }
    else if (event->key() == Qt::Key_Up){
        if(this->canup() && !isgoing){
            this->goup();
            this->currentdirection = 1;
        }
    }
    else if (event->key() == Qt::Key_Down){
        if(this->candown() && !isgoing){
            this->godown();
            this->currentdirection = 2;
        }
    }
    else if (event->key() == Qt::Key_Space && this->bombcounter<this->bomblimit){
        bombs[bombcounter] = new Bomb(0,this->x_pos,this->y_pos,this->bombrange,this->scene,this->themap,this);
        bombs[bombcounter]->themap = this->themap;
        this->scene->addItem(bombs[bombcounter]);
        bombs[bombcounter]->setPos(47+(this->x_pos)*705/13,49+(this->y_pos)*705/13);
        bombcounter++;
    }
}

void Player::attachscene(QGraphicsScene *scene)
{
    this->scene = scene;
}

bool Player::candown(){
    if(this->y_pos == 12){
        return false;
    }
    if(this->themap->current_map[this->y_pos+1][this->x_pos] != 0){
        return false;
    }
    return true;
}
bool Player::canup(){
    if(this->y_pos == 0){
        return false;
    }
    if(this->themap->current_map[this->y_pos-1][this->x_pos] != 0){
        return false;
    }
    return true;
}
bool Player::canright(){
    if(this->x_pos == 12){
        return false;
    }
    if(this->themap->current_map[this->y_pos][this->x_pos+1] != 0){
        return false;
    }
    return true;
}

bool Player::wascaught(int enemynumber){
    if((this->themap->enemiescoords[enemynumber][0] == this->x_pos) && (this->themap->enemiescoords[enemynumber][1] == this->y_pos)){
        return true;
    }
    return false;
}

bool Player::canleft(){
    if(this->x_pos == 0){
        return false;
    }
    if(this->themap->current_map[this->y_pos][this->x_pos-1] != 0){
        return false;
    }
    return true;
}


void Player::goup(){
    this->isgoing = true;
    this->setPos(this->x(),this->y()-2);
    this->smallsteps+=2;
    if ( this->smallsteps == 28){
        this->y_pos-=1;
    }
    if (this->smallsteps == 54){
        this->smallsteps = 0;
        this->isgoing = false;
    }
}

void Player::godown(){
    this->isgoing = true;
    this->setPos(this->x(),this->y()+2);
    this->smallsteps+=2;
    if (this->smallsteps == 28){
        this->y_pos+=1;
    }
    if (this->smallsteps == 54){
        this->smallsteps = 0;
        this->isgoing = false;
    }
}

void Player::goleft(){
    this->isgoing = true;
    this->setPos(this->x()-2,this->y());
    this->smallsteps+=2;
    if(this->smallsteps == 28){
        this->x_pos-=1;
    }
    if (this->smallsteps == 54){
        this->smallsteps = 0;
        this->isgoing = false;
    }
}

void Player::goright(){
    this->isgoing = true;
    this->setPos(this->x()+2,this->y());
    this->smallsteps+=2;
    if(this->smallsteps == 28){
        this->x_pos+=1;
    }
    if (this->smallsteps == 54){
        this->smallsteps = 0;
        this->isgoing = false;
    }
}

void Player::increasespeed()
{
    if(this->speed < 12){
        this->speed += 2;
        this->timer1->stop();
        this->timer1->start(16-this->speed);
    }
}

void Player::increasebombrange(){
    this->bombrange +=1;
}

void Player::increasebomblimit(){
    this->bomblimit += 1;
}

void Player::theend(){
    if(!this->end){
        return;
    }
    this->end = false;
    this->themap->removeallcrates();
    this->timer1->stop();
    this->timer2->stop();
    this->timer3->stop();
    this->timer4->stop();
    this->setPos(0,0);
    this->setPixmap(QPixmap(":/images/gameover.png"));
}

void Player::win(){
    if(this->themap->cratecounter != 0){
        return;
    }
    this->setPos(0,0);
    this->themap->removeallcrates();
    this->timer1->stop();
    this->timer2->stop();
    this->timer3->stop();
    this->timer4->stop();
    this->setPixmap(QPixmap(":/images/win.png"));
}

void Player::move()
{
    if(this->themap->bonusmap[this->x_pos][this->y_pos] != 0){
        if (this->themap->bonusmap[this->x_pos][this->y_pos] == 1){
            this->increasebomblimit();
        }
        else if (this->themap->bonusmap[this->x_pos][this->y_pos] == 2){
            this->increasebombrange();
        }
        else if (this->themap->bonusmap[this->x_pos][this->y_pos] == 3){
            this->increasespeed();
        }
     this->scene->removeItem(this->themap->bonuses[this->y_pos][this->x_pos]);
     delete this->themap->bonuses[this->y_pos][this->x_pos];
     this->themap->bonusmap[this->x_pos][this->y_pos] =0;

    }
    if(this->themap->isexplo(this->x_pos,this->y_pos)){
        this->end = true;
    }
    if(wascaught(0)){
        this->end = true;
    }
    if( wascaught(1)){
        this->end = true;
    }
    if(wascaught(2)){
        this->end = true;
    }
    if(this->isgoing){
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
}

void Player::animate(){

    if(this->animationcounter == 1 && this->currentdirection == 1){
        this->setPixmap(QPixmap(":/images/ghostupblue1.png"));
    }
    else if(this->animationcounter == 1 && this->currentdirection == 2){
        this->setPixmap(QPixmap(":/images/ghostdownblue1.png"));
    }
    else if(this->animationcounter == 1 && this->currentdirection == 3){
        this->setPixmap(QPixmap(":/images/ghostleftblue1.png"));
    }
    else if(this->animationcounter == 1 && this->currentdirection == 4){
        this->setPixmap(QPixmap(":/images/ghostrightblue1.png"));
    }
    else if(this->animationcounter == 2 && this->currentdirection == 1){
        this->setPixmap(QPixmap(":/images/ghostupblue2.png"));
    }
    else if(this->animationcounter == 2 && this->currentdirection == 2){
        this->setPixmap(QPixmap(":/images/ghostdownblue2.png"));
    }
    else if(this->animationcounter == 2 && this->currentdirection == 3){
        this->setPixmap(QPixmap(":/images/ghostleftblue2.png"));
    }
    else if(this->animationcounter == 2 && this->currentdirection == 4){
        this->setPixmap(QPixmap(":/images/ghostrightblue2.png"));
    }
    this->animationcounter++;
    if(this->animationcounter == 3){
        this->animationcounter = 1;
    }
}
