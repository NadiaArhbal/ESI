#ifndef PIECEITEM_H
#define PIECEITEM_H
#include <QGraphicsPixmapItem>

#include <point.h>
#include <boardview.h>

class BoardView;

class PieceItem : public QGraphicsPixmapItem
{
private:
    const double SCALE = static_cast<double>(75) / static_cast<double>(800);

    std::string _path;
    int _id;
    Point _coord;
    bool _selectable, _mouseover, _selected;
    BoardView *_listener;

public:
    /**
     * @brief PieceItem contructor
     * @param id ID of the PieceItem
     * @param coord graphical coordinates of a PieceItem, represented by a Point
     * @param selectable if the piece can be selectable
     * @param parent QGraphicsItem
     */
    PieceItem(std::string path, int id, Point coord, bool selectable, BoardView* bv = 0, QGraphicsItem * parent = 0);

    /**
     * @brief getId getter for _id
     */
    int getId();

    /**
     * @brief getCoord getter for graphical coordinates
     * @return Point center
     */
    Point getCoord();

    /**
     * @brief paint method called to paint PieceItem element
     * @param painter painter
     * @param option option
     * @param widget widget
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    /**
     * @brief isSelected getter for _selected
     * @return true if selected, false instead
     */
    bool isSelected();

    /*!
     * \brief deSelect deselects a PieceItem
     */
    void deSelect();

    /*!
     * \brief deSelect deselects a PieceItem
     */
    void select();

protected:
    /*!
     * \brief hoverEnterEvent catches an event when the mouse is on a PieceItem
     * \param event to catch
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);

    /*!
     * \brief hoverLeaveEvent catches an event when the mouse leaves a PieceItem
     * \param event to catch
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    /*!
     * \brief mousePressEvent catches an event when the Player clicks on a PieceItem
     * \param event to catch
     */
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    /*!
     * \brief mouseMoveEvent catches an event when the mouse is moving
     * \param event to catch
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
};

#endif // PIECEITEM_H
