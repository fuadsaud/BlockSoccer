#include "Person.h"

#include <math.h>
#include <stdio.h>

Person::Person()
{
    Person::position = new Point(0, 0, 0);
    Person::setDirectionAngle(0);
}

Person::Person(Point * initialPosition)
{
    Person::position = initialPosition;
    Person::setDirectionAngle(0);
}

float Person::getDirectionAngle()
{
    return directionAngle;
}

void Person::setDirectionAngle(float angle)
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

Point * Person::getPosition()
{
    return position;
}

void Person::lookAt(Point * to)
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

            if (p->z <= 0) {
                angle = 360 - angle;
            }

            setDirectionAngle(angle);
        }
    }
}

void Person::move(const int direction, int amount)
{
    Point p(0, 0, 0);
    float radAngle = getDirectionAngle() * M_PI / 180;

    switch (direction)
    {
        case Person::FRONT:
            p.x = cos(radAngle) * amount / 10;
            p.z = sin(radAngle) * amount / 10;
            break;
        case Person::BACK:
            p.x -= cos(radAngle) * amount / 10;
            p.z -= sin(radAngle) * amount / 10;
            break;
        case Person::LEFT:
            radAngle += M_PI / 2;
            p.x -= cos(radAngle) * amount / 10;
            p.z -= sin(radAngle) * amount / 10;
            break;
        case Person::RIGHT:
            radAngle -= M_PI / 2;
            p.x -= cos(radAngle) * amount / 10;
            p.z -= sin(radAngle) * amount / 10;
            break;
    }

    position = p + position;
}

void Person::rotate(float amount)
{
    setDirectionAngle(directionAngle + amount);
}

void Person::render()
{
    glPushMatrix();
        glTranslatef(position->x, position->y, position->z);
        glRotatef(90 - directionAngle, 0, 1, 0);
        glTranslatef(-0.25, 0, 0);

        renderFoot();

        glTranslatef(0, 0.1, 0);
        renderLeg();

        glTranslatef(0.5, -0.1, 0);
        renderFoot();

        glTranslatef(0, 0.1, 0);
        renderLeg();

        glTranslatef(-0.5, 1, 0);
        renderBody();

        glTranslatef(-0.13, 0.2, 0);
        renderArm(Person::LEFT);

        glTranslatef(0.76, 0, 0);
        renderArm(Person::RIGHT);
    glPopMatrix();
}

void Person::renderFoot()
{
    glColor3f(0, 0, 0);
    Parallelepiped::draw(0.1, 0.1, 0.3);
}

void Person::renderLeg()
{
    glColor3f(1, 0.72, 0.51);
    Parallelepiped::draw(0.1, 0.5, 0.1);

    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glColor3f(0, 0, 1);
        Parallelepiped::draw(0.1, 0.5, 0.1);
    glPopMatrix();
}

void Person::renderBody()
{
    // Hips
    glColor3f(0, 0, 1);
    Parallelepiped::draw(0.6, 0.3, 0.1);

    glPushMatrix();
        // Chest
        glTranslatef(0, 0.3, 0);
        glColor3f(0, 1, 0);
        Parallelepiped::draw(0.6, 0.7, 0.1);

        // Neck
        glTranslatef(0.25, 0.7, 0);
        glColor3f(1, 0.72, 0.51);
        Parallelepiped::draw(0.1, 0.1, 0.1);

        // Head
        glTranslatef(-0.15, 0.1, -0.1);
        Parallelepiped::draw(0.4, 0.5, 0.3);
    glPopMatrix();
}

void Person::renderArm(const int leftOrRight)
{
    float x = (leftOrRight == Person::LEFT) ? 0.1 : -0.03;

    glColor3f(1, 0.72, 0.51);
    Parallelepiped::draw(0.1, 0.8, 0.1);

    glPushMatrix();
        glTranslatef(x, 0.7, 0);
        glColor3f(0, 1, 1);
        Parallelepiped::draw(0.03, 0.1, 0.1);
    glPopMatrix();
}
