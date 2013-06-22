#include "Camera.h"

Camera::Camera(Person * p) {
    person = p;
}

void Camera::syncWithPerson() {
    Point * p = person->getPosition();
    float angle = person->getDirectionAngle();

    float radAngle = M_PI * angle / 180;

    // Camera is always centered on the player.
    float eyeX = p->x - cos(radAngle) * 3;
    // Makes the camera appear higher.
    float eyeY = p->y + 3;
    // Sets the eye on the back of the player (the lesser, the farther).
    float eyeZ = p->z - sin(radAngle) * 3;

    float directionX = p->x;
    float directionY = p->y + 2;
    float directionZ = p->z;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, 800 / (double) 600, 0.2, 200);
    gluLookAt(eyeX, eyeY, eyeZ,  directionX, directionY, directionZ,  0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
