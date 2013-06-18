#include "Object.h"
#include <iostream>

Object::Object()
{
    Object::position = new Point(0, 0, 0);
    Object::setDirectionAngle(0);
}

Object::Object(Point * initialPosition)
{
    Object::position = initialPosition;
    Object::setDirectionAngle(0);
}

float Object::getDirectionAngle()
{
    return directionAngle;
}

void Object::setDirectionAngle(float angle)
{
    if (angle < 0)
    {
        angle = 360 + angle;
    } else if (angle > 360)
    {
        angle = angle - 360;
    }

    directionAngle = angle;
}

Point * Object::getPosition()
{
    return position;
}

void Object::lookAt(Point * to)
{
    Point direction(position->x + 10, 0, position->z);
    Point * p = new Point(to->x - position->x, 0, to->z - position->z);

    if (p->z <= 0)
    {
        direction.z *= -1;
    }

    float pModule = sqrt(pow(p->x, 2) + pow(p->z, 2));
    float dModule = sqrt(pow(direction.x, 2) + pow(direction.z, 2));

    float product = p->x * direction.x + p->z + direction.z;
    float productModule = pModule * dModule;

    if (productModule != 0)
    {
        float aux = product / productModule;

        if ( aux >= -1 && aux <= 1)
        {
            float angle = acos(aux) * 180 / M_PI;

            if (p->z <= 0)
            {
                angle = 360 - angle;
            }

            setDirectionAngle(angle);
        }
    }
}

void Object::move(const int direction, float amount)
{
    Point p(0, 0, 0);
    float radAngle = getDirectionAngle() * M_PI / 180;

    switch (direction)
    {
        case Object::FRONT:
            p.x = cos(radAngle) * amount;
            p.z = sin(radAngle) * amount;
            break;
        case Object::BACK:
            p.x -= cos(radAngle) * amount;
            p.z -= sin(radAngle) * amount;
            break;
        case Object::LEFT:
            radAngle += M_PI / 2;
            p.x -= cos(radAngle) * amount;
            p.z -= sin(radAngle) * amount;
            break;
        case Object::RIGHT:
            radAngle -= M_PI / 2;
            p.x -= cos(radAngle) * amount;
            p.z -= sin(radAngle) * amount;
            break;
    }

    position = p + position;
}

void Object::rotate(float amount)
{
    setDirectionAngle(directionAngle + amount);
}

bool Object::collidingWith(Object o)
{
    bool result = false;
    Point * myCenter = getPosition();
    Point * otherCenter = o.getPosition();
    double distance = sqrt(pow((double) (myCenter->x - otherCenter->x), 2) +
                           pow((double) (myCenter->z - otherCenter->z), 2)
    );

    if (distance <= (o.getRadius() + getRadius()))
    {
        result = true;
    }

    return result;
}

float Object::getRadius()
{
    return radius;
}
