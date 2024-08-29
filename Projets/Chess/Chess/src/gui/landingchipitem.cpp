#include "landingchipitem.h"

#include <QPen>
#include <QBrush>
#include <QPainter>

LandingChipItem::LandingChipItem(int id, Point coord, BoardView* bv, QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent), _id(id), _coord(coord),
    _mouseover(false), _selected(false), _listener(bv)
{
    this->setAcceptHoverEvents(true);
    auto chip = new QGraphicsEllipseItem(_coord.X(), _coord.Y(), RAD, RAD);
    chip->setZValue(0);
    setRect(_coord.X()+ 0.25*RAD, _coord.Y()+ 0.25*RAD, RAD, RAD);
}

Point LandingChipItem::getCoord(){
    return _coord;
}

int LandingChipItem::getId(){
    return _id;
}

void LandingChipItem::deSelect(){
    _selected = false;
    update();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void LandingChipItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(_mouseover){
        QBrush brush;
        brush.setColor(QColor(240, 249, 255,220));
        brush.setStyle(Qt::SolidPattern);

        painter->setBrush(brush);
    }
    else{
        QBrush brush;
        brush.setColor(QColor(170, 221, 250, 100));
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
    }


    painter->drawEllipse(rect());
}

void LandingChipItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    _mouseover = true;
    update();
}

void LandingChipItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _mouseover = false;
    update();
}

void LandingChipItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    _selected = !_selected;
    update();
    _listener->newChipSelected(_id);
}

void LandingChipItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    update();
}

#pragma GCC diagnostic pop
