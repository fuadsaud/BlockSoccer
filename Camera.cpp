#include "Camera.h"
#include <iostream>

Camera::Camera(Person * p) {
    person = p;
}

void Camera::look() {
    Point * p = person->getPosition();
    float angle = person->getDirectionAngle();

    float radAngle = PI * angle / 180;

    // float ex = p->x - cos(radAngle);
    // float ey = p->y + 1;
    // float ez = p->z - sin(radAngle);

    // float dx = p->x + cos(radAngle);
    // float dy = p->y;
    // float dz = p->z + sin(radAngle);

    // Camera is always centered on the player.
    float ex = p->x;
    // Makes the camer appear higher.
    float ey = p->y + 3.5;
    // Sets the eye on the back of the player (the lesser, the farther).
    float ez = p->z - 3;

    float dx = p->x + cos(radAngle);
    float dy = p->y + 2;
    float dz = p->z + sin(radAngle);

    std::cerr << "Point(" << ex << ", " << ey << ", " << ez << ")" << std::endl;
    std::cerr << "Point(" << dx << ", " << dy << ", " << dz << ")" << std::endl;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // TODO: this call to perspective shouldn't be here
    gluPerspective(60, 800 / (double) 600, 0.2, 200);
    gluLookAt(ex, ey, ez, dx, dy, dz, 0, 1, 0);
    // gluLookAt(0, 3.5, -3,
    //           0,   2,  2,
    //           0,   1,  0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
