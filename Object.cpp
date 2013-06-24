#include "Object.h"

Object::Object(float m) {
    position = new Point(0, 0, 0);
    setDirectionAngle(0);
    movementAmount = m;
    scenario = 0;
}

Object::Object(Point * initialPosition, float m) {
    position = initialPosition;
    setDirectionAngle(0);
    movementAmount = m;
    scenario = 0;
}

float Object::getDirectionAngle() {
    return directionAngle;
}

void Object::setDirectionAngle(float angle) {
    if (angle < 0) angle = 360 + angle;
    else if (angle > 360) angle = angle - 360;

    directionAngle = angle;
}

Point * Object::getPosition() {
    return position;
}

void Object::lookAt(Point * to)
{
    Point direction(position->x + 10, 0, position->z);
    Point * p = new Point(to->x - position->x, 0, to->z - position->z);

    if (p->z <= 0) direction.z *= -1;

    float pModule = sqrt(pow(p->x, 2) + pow(p->z, 2));
    float dModule = sqrt(pow(direction.x, 2) + pow(direction.z, 2));

    float product = p->x * direction.x + p->z + direction.z;
    float productModule = pModule * dModule;

    if (productModule != 0) {
        float aux = product / productModule;

        if ( aux >= -1 && aux <= 1) {
            float angle = acos(aux) * 180 / M_PI;

            if (p->z <= 0) angle = 360 - angle;

            setDirectionAngle(angle);
        }
    }
}

void Object::move(const int direction) {
    move(direction, movementAmount);
}

void Object::move(const int direction, float amount) {
    Point p(0, 0, 0);
    float x, z, boundary, radAngle = getDirectionAngle() * M_PI / 180;

    switch (direction) {
        case Object::FRONT:
            x = cos(radAngle);
            z = sin(radAngle);
            break;
        case Object::BACK:
            x = -cos(radAngle);
            z = -sin(radAngle);
            break;
        case Object::LEFT:
            radAngle += M_PI / 2;
            x = -cos(radAngle);
            z = -sin(radAngle);
            break;
        case Object::RIGHT:
            radAngle -= M_PI / 2;
            x = -cos(radAngle);
            z = -sin(radAngle);
            break;
    }

    p.x += x * amount;
    p.z += z * amount;

    Point * finalPosition = p + position;

    if (scenario != 0) {
        Point** boundaries = scenario->getBoundaries();

        boundary = fmin(boundaries[0]->x, boundaries[1]->x);
        if (boundary > finalPosition->x) finalPosition->x = boundary;

        boundary = fmax(boundaries[0]->x, boundaries[1]->x);
        if (boundary < finalPosition->x) finalPosition->x = boundary;

        boundary = fmin(boundaries[0]->z, boundaries[1]->z);
        if (boundary > finalPosition->z) finalPosition->z = boundary;

        boundary = fmax(boundaries[0]->z, boundaries[1]->z);
        if (boundary < finalPosition->z) finalPosition->z = boundary;
    }

    position = finalPosition;
}

void Object::rotate(float amount) {
    setDirectionAngle(directionAngle + amount);
}

bool Object::collidingWith(Object * other) {
    Point * myCenter = getPosition();
    Point * otherCenter = other->getPosition();

    double distance = sqrt(pow((double) (myCenter->x - otherCenter->x), 2) +
                           pow((double) (myCenter->z - otherCenter->z), 2)
    );

    if (distance <= (other->getRadius() + getRadius())) {
        return true;
    }

    return false;
}

bool Object::isWithin(Scenario * s) {
    // This checks whether the is outside the field.
    Point** boundaries = s->getBoundaries();

    if (fmin(boundaries[0]->x, boundaries[1]->x) < position->x &&
        fmax(boundaries[0]->x, boundaries[1]->x) > position->x &&
        fmin(boundaries[0]->z, boundaries[1]->z) < position->z &&
        fmax(boundaries[0]->z, boundaries[1]->z) > position->z) {
        return true;
    }

    return false;
}

float Object::getRadius() {
    return radius;
}

void Object::bindTo(Scenario * s) {
    scenario = s;
}