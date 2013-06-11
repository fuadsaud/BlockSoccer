#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Person * p)
{
    attach(p);
}

void Ball::move(const int direction, int amount)
{

}

void Ball::render()
{
    glPushMatrix();
        Point * playerPosition = player->getPosition();
        float angle = player->getDirectionAngle();

        float radAngle = M_PI * angle / 180;

        glTranslatef(playerPosition->x + cos(radAngle) * 0.1,
                     playerPosition->y + 0.5,
                     playerPosition->z + sin(radAngle) * 0.1);

        glColor3f(1, 1, 1);
        glutSolidSphere(0.2, 10, 10);
    glPopMatrix();
}

void Ball::attach(Person * p)
{
    player = p;
}
