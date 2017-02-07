#ifndef BONUS_H
#define BONUS_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>


class Bonus :public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bonus(QGraphicsItem * parent=0,int whichbonus = 0);
};


#endif // BONUS_H
