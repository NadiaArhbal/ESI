#include "point.h"

Point::Point(){

}

Point::Point(double x, double y) : _x(x), _y(y)
{

}

double Point::X(){
    return _x;
}

double Point::Y(){
    return _y;
}
