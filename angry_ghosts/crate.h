#ifndef CRATE_H
#define CRATE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Crate:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Crate(QGraphicsItem * parent=0);
};

#endif //CRATE_H
