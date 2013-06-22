#include "Point.h"

Point::Point() {
    Point::x = 0;
    Point::y = 0;
    Point::z = 0;
}

Point::Point(float x, float y, float z) {
    Point::x = x;
    Point::y = y;
    Point::z = z;
}

Point* Point::operator+(const Point* p) const {
    Point self = *this;

    Point* result = new Point(
                 p->x + self.x,
                 p->y + self.y,
                 p->z + self.z);

    return result;
}
