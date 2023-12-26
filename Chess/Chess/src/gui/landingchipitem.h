#ifndef LANDINGCHIPITEM_H
#define LANDINGCHIPITEM_H
#include <QGraphicsEllipseItem>
#include <point.h>
#include <boardview.h>

class BoardView;

class LandingChipItem: public QGraphicsEllipseItem
{
private:
    int _id;
    Point _coord;
    const double RAD = 50;
    /*!
     * \brief _mouseover used to paint chip when the mouse is on a LandingChipItem
     * \brief _selected used to paint chip when a LandingChipItem is selected by the Player
     */
    bool _mouseover, _selected;
    BoardView *_listener;

public:
    /**
     * @brief landingChipItem constructor
     * @param coord coordinates of the center, represented by a Point
     * @param parent QGraphicsItem
     */
    LandingChipItem(int id, Point coord, BoardView* bv, QGraphicsItem * parent = 0);

    /**
     * @brief getId getter for _id
     */
    int getId();

    /**
     * @brief getCoord getter for graphical coordinates
     * @return Point center
     */
    Point getCoord();

    /*!
     * \brief isSelected getter for _selected
     * \return true if selected, false instead
     */
    bool isSelected();

    /*!
     * \brief deSelect deselects aLandingChipItem
     */
    void deSelect();

    /**
     * @brief paint method called to paint landingChipItem element
     * @param painter painter
     * @param option option
     * @param widget widget
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:

    /*!
     * \brief hoverEnterEvent catches an event when the mouse is on a MarbleCell
     * \param event to catch
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);

    /*!
     * \brief hoverLeaveEvent catches an event when the mouse leaves a MarbleCell
     * \param event to catch
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    /*!
     * \brief mousePressEvent catches an event when the Player clicks on a MarbleCell
     * \param event to catch
     */
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    /*!
     * \brief mouseMoveEvent catches an event when the mouse is moving
     * \param event to catch
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
};

#endif // LANDINGCHIPITEM_H
