#pragma once

#include "Includes.h"

class Point
{
public:
    float x;
    float y;
    float z;

    Point(float x, float y, float z);

    Point* operator+(const Point* p) const;
};
