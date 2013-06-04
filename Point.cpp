#include "Point.h"

Point::Point(float x, float y, float z) {
    Point::x = x;
    Point::y = y;
    Point::z = z;
}

Point Point::operator+(const Point* p) const {
    Point result(p->x + Point::x,
                 p->y + Point::y,
                 p->z + Point::z);

    return result;
}