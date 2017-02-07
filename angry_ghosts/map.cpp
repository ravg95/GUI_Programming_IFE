#include "map.h"
#include <cstdlib>
#include <time.h>

Map::Map(){
    srand (time(NULL));
    this->enemycounter = 3;
}

void Map::map_loader(){
    int counter_1 = 0, counter_2 = 0;
    for(counter_1 = 0; counter_1 < 13; counter_1++){
        for(counter_2 = 0; counter_2 < 13; counter_2++){
           this->current_map[counter_1][counter_2] = this->start_map[counter_1*13+counter_2];
        }
    }
}

void Map::clearexplo(){
    int counter_1 = 0, counter_2 = 0;
    for(counter_1 = 0; counter_1 < 13; counter_1++){
        for(counter_2 = 0; counter_2 < 13; counter_2++){
           this->explomap[counter_1][counter_2] = 0;
        }
    }
}

void Map::enemydown(){
this->enemycounter--;
}

bool Map::enemykilled(){
    if ( this->enemycounter < 3){
    return true;
    }
    return false;
}

void Map::setexplo(int x_coord, int y_coord){
    this->explomap[x_coord][y_coord] =1;
}

bool Map::isexplo(int x_coord, int y_coord){
    if(this->explomap[x_coord][y_coord]==1){
        return true;
    }
    return false;
}

void Map::starting_map(QGraphicsScene *scene){
    this->cratecounter = 0;
    this->scene = scene;
    int counter_1, counter_2;
    for(counter_1 = 0; counter_1 < 13; counter_1++){
        for(counter_2 = 0; counter_2 < 13; counter_2++){
            if((current_map[counter_1][counter_2]) == 1){
                crates[counter_1][counter_2] = new Crate();
                crates[counter_1][counter_2]->setPos((705*(counter_1)/13)+47,(705*(counter_2)/13)+49);
                scene->addItem(crates[counter_1][counter_2]);
                this->cratecounter++;
            }
        }
    }
}

void Map::removecrate(int x_coord, int y_coord){
    int whichbonus = rand() %15 + 1;
    this->scene->removeItem(crates[x_coord][y_coord]);
    delete crates[x_coord][y_coord];
    this->current_map[y_coord][x_coord]=0;
    this->cratecounter--;
    if(whichbonus < 4 ){
        this->bonuses[y_coord][x_coord] = new Bonus(0,whichbonus);
        this->scene->addItem(this->bonuses[y_coord][x_coord]);
        this->bonuses[y_coord][x_coord]->setPos(52+x_coord*705/13,54+y_coord*705/13);
        this->bonuscounter++;
        this->bonusmap[x_coord][y_coord]=whichbonus;
    }

}

void Map::removeallcrates(){
    int counter_1, counter_2;
    for(counter_1 = 0; counter_1 < 13; counter_1++){
        for(counter_2 = 0; counter_2 < 13; counter_2++){
            if((current_map[counter_2][counter_1]) == 1){
                this->scene->removeItem(crates[counter_1][counter_2]);
                delete crates[counter_1][counter_2];
            }
            if((this->bonusmap[counter_1][counter_2]) != 0){
                this->scene->removeItem(bonuses[counter_2][counter_1]);
                delete bonuses[counter_2][counter_1];

            }

        }
    }
}

