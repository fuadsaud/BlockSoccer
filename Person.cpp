#include "Person.h"

Person::Person() {
    Person::position = new Point(0, 0, 0);
    Person::setDirectionAngle(0);
}

Person::Person(Point * initialPosition) {
    Person::position = initialPosition;
    Person::setDirectionAngle(0);
}

float Person::getDirectionAngle() {
    return directionAngle;
}

void Person::setDirectionAngle(float angle) {
    if (angle < 0) {
        angle = 360 - angle;
    } else if (angle > 360) {
        angle = angle - 360;
    }

    directionAngle = angle;
}

Point * Person::getPosition() {
    return position;
}

// Person::move(Point);
// Person::rotate();

void Person::render() {
    glPushMatrix();
        glTranslatef(position->x - 0.25, position->y, position->z);
        glRotatef(directionAngle, 0, 1, 0);

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
        renderArm(0);

        glTranslatef(0.76, 0, 0);
        renderArm(1);
    glPopMatrix();
}

void Person::renderFoot() {
    glColor3f(0, 0, 0);

    Parallelepiped::draw(0.1, 0.1, 0.3);
}

void Person::renderLeg() {
    glColor3f(1, 0.72, 0.51);

    Parallelepiped::draw(0.1, 0.5, 0.1);

    glPushMatrix();
        glTranslatef(0, 0.5, 0);

        glColor3f(0, 0, 1);
        Parallelepiped::draw(0.1, 0.5, 0.1);
    glPopMatrix();
}

void Person::renderBody() {
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

void Person::renderArm(const int leftOrRight) {
    float x = (leftOrRight == 0) ? 0.1 : -0.03;

    glColor3f(1, 0.72, 0.51);
    Parallelepiped::draw(0.1, 0.8, 0.1);

    glPushMatrix();
        glTranslatef(x, 0.7, 0);
        glColor3f(0, 1, 1);
        Parallelepiped::draw(0.03, 0.1, 0.1);
    glPopMatrix();
}
