#include "Cuboid.h"

void Cuboid::draw(float width, float height, float depth) {
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(width, 0, 0);
    glVertex3f(width, height, 0);
    glVertex3f(0, height, 0);

    glVertex3f(0, 0, depth);
    glVertex3f(width, 0, depth);
    glVertex3f(width, height, depth);
    glVertex3f(0, height, depth);

    glVertex3f(0, height, 0);
    glVertex3f(width, height, 0);
    glVertex3f(width, height, depth);
    glVertex3f(0, height, depth);

    glVertex3f(0, 0, 0);
    glVertex3f(width, 0, 0);
    glVertex3f(width, 0, depth);
    glVertex3f(0, 0, depth);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, depth);
    glVertex3f(0, height, depth);
    glVertex3f(0, height, 0);

    glVertex3f(width, 0, 0);
    glVertex3f(width, 0, depth);
    glVertex3f(width, height, depth);
    glVertex3f(width, height, 0);

    glEnd();
}
