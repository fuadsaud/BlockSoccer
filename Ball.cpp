#include "Ball.h"

Ball::Ball() {
    position = new Point();
    radius = 0.2;
}

Ball::Ball(Person * p) {
    attach(p);
    position = new Point();
    radius = 0.2;
}

void Ball::go() {
    if (!isAttached()) move(Object::FRONT);
}

void Ball::render() {
    glPushMatrix();

        if (isAttached()) {
            setDirectionAngle(player->getDirectionAngle());

            Point * playerPosition = player->getPosition();
            float radAngle = M_PI * getDirectionAngle() / 180;

            position->x = playerPosition->x + cos(radAngle) * 0.1;
            position->y = playerPosition->y + 0.5;
            position->z = playerPosition->z + sin(radAngle) * 0.1;
        }

        glTranslatef(position->x, position->y , position->z);

        glColor3f(1, 1, 1);
        glutWireSphere(0.2, 10, 10);
    glPopMatrix();
}

void Ball::attach(Person * p) {
    player = p;
}

bool Ball::isAttached() {
    return player != 0;
}

void Ball::detach() {
    player = 0;
}
