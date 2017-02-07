#include "crate.h"
#include <QGraphicsScene>
#include <QKeyEvent>

Crate::Crate(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    QPixmap img(":/images/crate.png");
    QPixmap img2 = img.scaled(50, 50, Qt::KeepAspectRatio);
    setPixmap(QPixmap(img2));
}

