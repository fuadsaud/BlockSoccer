#pragma once

#define POINT_H

class Point
{
public:
    float x;
    float y;
    float z;

    Point(float x, float y, float z);

    Point* operator+(const Point* p) const;
};
