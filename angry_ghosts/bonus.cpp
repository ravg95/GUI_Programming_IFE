#include "bonus.h"

Bonus::Bonus(QGraphicsItem * parent,int whichbonus){
     if(whichbonus == 1){
         setPixmap(QPixmap(":/images/bonusbomb.png"));
     }
     else if(whichbonus == 2){
         setPixmap(QPixmap(":/images/bonusrange.png"));
     }
     else if(whichbonus == 3){
         setPixmap(QPixmap(":/images/bonusspeed.png"));
     }
}
