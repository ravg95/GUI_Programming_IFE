#ifndef MAP_H
#define MAP_H

#include <QFile>
#include <QGraphicsScene>
#include "crate.h"
#include "bonus.h"
class Map
{
public:
    Map();
    void map_loader();
    int current_map[13][13]= {{0}};
    int explomap[13][13]= {{0}};
    int bonusmap[13][13]= {{0}};
    void clearexplo();
    int enemycounter = 3;
    void enemydown();
    bool enemykilled();
    int cratecounter;
    void setexplo(int x_coord, int y_coord);
    bool isexplo(int x_coord, int y_coord);
    QGraphicsScene * scene;
    int start_map[169] { 0,0,1,1,1,1,1,1,1,1,1,0,0,
                         0,2,1,2,1,2,1,2,1,2,1,2,0,
                         1,1,1,1,1,1,1,1,1,1,1,1,1,
                         1,2,1,2,1,2,1,2,1,2,1,2,1,
                         1,1,1,1,1,1,1,1,1,1,1,1,1,
                         1,2,1,2,1,2,1,2,1,2,1,2,1,
                         1,1,1,1,1,1,1,1,1,1,1,1,1,
                         1,2,1,2,1,2,1,2,1,2,1,2,1,
                         1,1,1,1,1,1,1,1,1,1,1,1,1,
                         1,2,1,2,1,2,1,2,1,2,1,2,1,
                         1,1,1,1,1,1,1,1,1,1,1,1,1,
                         0,2,1,2,1,2,1,2,1,2,1,2,0,
                         0,0,1,1,1,1,1,1,1,1,1,0,0
                        };
    void starting_map(QGraphicsScene * scene);
    Crate * crates[13][13];
    Bonus * bonuses[13][13];
    int bonuscounter = 0;
    int enemiescoords[3][2]{{0}};
    void removecrate(int x_coord, int y_coord);
    void removeallcrates();
    };

#endif // MAPGENERATOR_H
