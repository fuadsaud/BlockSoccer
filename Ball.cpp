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

        glTranslatef(playerPosition->x + 0.2,
                     playerPosition->y + 1,
                     playerPosition->z);

        glColor3f(1, 1, 1);
        glutSolidSphere(0.2, 10, 10);

    glPopMatrix();
}

void Ball::attach(Person * p)
{
    player = p;
}
