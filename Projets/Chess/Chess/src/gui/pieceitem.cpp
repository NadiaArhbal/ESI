#include "pieceitem.h"
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QPainter>
#include <iostream>

PieceItem::PieceItem(std::string path, int id, Point coord, bool selectable, BoardView * bv, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), _path(path), _id(id), _coord(coord), _selectable(selectable),
      _mouseover(false), _selected(false), _listener(bv)
{
    this->setAcceptHoverEvents(true);
    std::basic_string<char> basicStr;
    this->setPixmap(QPixmap(_path.c_str()));
    auto piece = new QGraphicsPixmapItem();
    piece->setZValue(20);
    this->setX(_coord.X());
    this->setY(_coord.Y());
    this->setScale(SCALE);
}

Point PieceItem::getCoord(){
    return _coord;
}

int PieceItem::getId(){
    return _id;
}

bool PieceItem::isSelected(){
    return _selected;
}

void PieceItem::deSelect(){
    _selected = false;
    update();
}

void PieceItem::select()
{
    _selected = true;
    update();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void PieceItem::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

    if(_selected){
        painter->setPen(QPen(QBrush(QColor(180, 225, 250, 255)), 50));
        painter->drawRoundedRect(this->boundingRect().adjusted(3.0, 3.0, -3.0, -3.0), 100.0, 100.0);
    }

}

void PieceItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    _mouseover = true;
    update();
}

void PieceItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _mouseover = false;
    update();
}

void PieceItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(_selectable){
        _selected = !_selected;
        update();
        if (_listener) _listener->newPieceSelected(_id);

    }
}

void PieceItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    update();
}

#pragma GCC diagnostic pop
