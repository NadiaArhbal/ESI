#ifndef POINT_H
#define POINT_H

/**
 * @brief The Point class represents a graphical point
 */
class Point
{
private:
    /**
     * @brief _x x-axis coordinate
     */
    double _x;

    /**
     * @brief _y y-axis coordinate
     */
    double _y;

public:
    /**
     * @brief Point default constructor
     */
    Point();

    /**
     * @brief Point contructor with x and y
     */
    Point(double, double);

    /**
     * @brief X getter for x-axis coordinate
     * @return double
     */
    double X();

    /**
     * @brief Y getter for y-axis coordinate
     * @return double
     */
    double Y();

};

#endif // POINT_H
