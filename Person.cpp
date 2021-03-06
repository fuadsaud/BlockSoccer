#include "Person.h"

Person::Person(Point* initialPosition, Color* shirt, Color* shorts, float m) {
    position = initialPosition;
    setDirectionAngle(0);
    radius = 0.5;
    movementAmount = m;
    shirtColor = shirt;
    shortsColor = shorts;
}

void Person::render() {
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
        renderArm(Object::LEFT);

        glTranslatef(0.76, 0, 0);
        renderArm(Object::RIGHT);
    glPopMatrix();
}

void Person::renderFoot() {
    glColor3f(0, 0, 0);
    Cuboid::draw(0.1, 0.1, 0.3);
}

void Person::renderLeg() {
    glColor3f(1, 0.72, 0.51);
    Cuboid::draw(0.1, 0.5, 0.1);

    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glColor3f(shortsColor->r, shortsColor->g, shortsColor->b);
        Cuboid::draw(0.1, 0.5, 0.1);
    glPopMatrix();
}

void Person::renderBody() {
    // Hips
    glColor3f(shortsColor->r, shortsColor->g, shortsColor->b);
    Cuboid::draw(0.6, 0.3, 0.1);

    glPushMatrix();
        // Chest
        glTranslatef(0, 0.3, 0);
        glColor3f(shirtColor->r, shirtColor->g, shirtColor->b);
        Cuboid::draw(0.6, 0.7, 0.1);

        // Neck
        glTranslatef(.18, .7, 0);
        glColor3f(1, 0.72, 0.51);
        Cuboid::draw(0.2, 0.15, 0.1);

        // Head
        glTranslatef(.075, .35, 0);
        GLUquadricObj *obj = gluNewQuadric();
        gluSphere(obj, .25, 20, 20);
    glPopMatrix();
}

void Person::renderArm(const int leftOrRight) {
    float x = (leftOrRight == Object::LEFT) ? 0.1 : -0.03;

    glColor3f(1, 0.72, 0.51);
    Cuboid::draw(0.1, 0.8, 0.1);

    glPushMatrix();
        glTranslatef(x, 0.7, 0);
        glColor3f(shirtColor->r, shirtColor->g, shirtColor->b);
        Cuboid::draw(0.03, 0.1, 0.1);
    glPopMatrix();
}
