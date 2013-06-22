#include "Scene.h"

Scene::Scene(Game *g)
{
    game = g;
    player = new Person();
    camera = new Camera(player);
    ball = new Ball(player);
    opponents.push_back(Person(new Point(10, 0,   0)));
    opponents.push_back(Person(new Point(10, 0, -10)));
    opponents.push_back(Person(new Point(10, 0,  10)));
    opponents.push_back(Person(new Point(15, 0,   0)));

    goalKepper = new Person(new Point(48, 0, 0));

    init(camera);
}

void Scene::init(Camera * camera)
{
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutSetCursor(GLUT_CURSOR_NONE);

    camera->syncWithPerson();
}

void Scene::display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawScenario();
    goalKepper->render();

    for(unsigned int i = 0; i < opponents.size(); i++)
        opponents[i].render();

    ball->render();
    player->render();
}

void Scene::background()
{
    ballBehavior();
    adversaryTeamBehavior();
    collisionMonitor();
    glutPostRedisplay();
}

void Scene::drawScenario()
{
    float w = 100;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.14, 0.34, 0.02);
    glBegin(GL_QUADS);
        glVertex3f(-w / 2, 0, -w / 4);
        glVertex3f(-w / 2, 0,  w / 4);
        glVertex3f( w / 2, 0,  w / 4);
        glVertex3f( w / 2, 0, -w / 4);

    glEnd();

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);

    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-w / 2 + 1.5, 0.01, -w / 4 + 1.5);
        glVertex3f( w / 2 - 1.5, 0.01, -w / 4 + 1.5);
        glVertex3f( w / 2 - 1.5, 0.01,  w / 4 - 1.5);
        glVertex3f(-w / 2 + 1.5, 0.01,  w / 4 - 1.5);
        glVertex3f(-w / 2 + 1.5, 0.01, -w / 4 + 1.5);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0.01, -w / 4 + 1.5);
        glVertex3f(0, 0.01,  w / 4 - 1.5);
    glEnd();

    glBegin(GL_LINE_LOOP);
        for(unsigned int i = 0; i < 360; i++)
        {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle) * 4, 0.01, sin(angle) * 4);
        }
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-w / 2 + 1.5, 0.01, -13);
        glVertex3f(-w / 2 + 15,  0.01, -13);
        glVertex3f(-w / 2 + 15,  0.01,  13);
        glVertex3f(-w / 2 + 1.5, 0.01,  13);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-w / 2 + 1.5, 0.01, -7);
        glVertex3f(-w / 2 + 8,   0.01, -7);
        glVertex3f(-w / 2 + 8,   0.01,  7);
        glVertex3f(-w / 2 + 1.5, 0.01,  7);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(w / 2 - 1.5, 0.01, -7);
        glVertex3f(w / 2 - 8,   0.01, -7);
        glVertex3f(w / 2 - 8,   0.01,  7);
        glVertex3f(w / 2 -1.5,  0.01,  7);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(w / 2 - 1.5, 0.01, -13);
        glVertex3f(w / 2 - 15,  0.01, -13);
        glVertex3f(w / 2 - 15,  0.01,  13);
        glVertex3f(w / 2 - 1.5, 0.01,  13);
    glEnd();

    glBegin(GL_LINE_LOOP);
        for(unsigned int i = 90; i < 270; i++)
        {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle) *2 + w / 2 - 15, 0.01, sin(angle) * 4);
        }
    glEnd();

    glBegin(GL_LINE_LOOP);
        for(unsigned int i = 270; i < 450; i++)
        {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle) * 2 - w / 2 + 15, 0.01, sin(angle) * 4);
        }
    glEnd();

    glPushMatrix();
        glTranslatef(w / 2 - 1.5, 0, -5);
        glRotatef(-90, 1, 0, 0);
        GLUquadricObj *quadObj = gluNewQuadric();
        gluCylinder(quadObj, 0.1, 0.1, 3.5, 10, 10);

        glTranslatef(0, -10, 0);
        gluCylinder(quadObj, 0.1, 0.1, 3.5, 10, 10);

        glTranslatef(0, 0, 3.4);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quadObj, 0.1, 0.1, 10, 10, 10);
    glPopMatrix();
}

void Scene::keyboard(const char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            player->move(Object::FRONT, PLAYER_MOVEMENT_AMOUNT);
            break;
        case 's':
        case 'S':
            player->move(Object::BACK, PLAYER_MOVEMENT_AMOUNT);
            break;
        case 'a':
        case 'A':
            player->move(Object::LEFT, PLAYER_MOVEMENT_AMOUNT);
            break;
        case 'd':
        case 'D':
            player->move(Object::RIGHT, PLAYER_MOVEMENT_AMOUNT);
            break;
        case ' ':
            ball->detach();
            break;
        case 'q':
        case 'Q':
            exit(0);
    }

    camera->syncWithPerson();
}

void Scene::passiveMotion(int x, int y)
{
    float height = 800, width = 600;

    if (x != width / 2)
    {
        float distance = (x - width / 2) / 10;

        player->rotate(distance);
        camera->syncWithPerson();

        glutWarpPointer(width / 2, height / 2);
    }
}

void Scene::adversaryTeamBehavior()
{
    Point * p = player->getPosition();

    srand(time(0));

    for(unsigned int i = 0; i < opponents.size(); i++)
    {
        opponents[i].lookAt(p);
        opponents[i].move(Person::FRONT, PLAYER_MOVEMENT_AMOUNT * 0.9);
    }

    goalKepper->lookAt(p);

    Point * kp = goalKepper->getPosition();
    float move = p->z;

    if (move > 5) move = 5;
    else if (move < -5) move = -5;

    kp->z = move;
}

void Scene::ballBehavior()
{
    if (!ball->attached()) ball->go();
}

void Scene::collisionMonitor()
{
    Point * playerPosition = player->getPosition();

    std::vector<Person> allOpponents(opponents);
    allOpponents.push_back(*goalKepper);

    // This checks wheter the player is outside the field.
    if (playerPosition->x < -50 || playerPosition->x > 50 ||
        playerPosition->z < -25 || playerPosition->z > 25 )
    {
        end(false);
    }

    Point * ballPosition = ball->getPosition();

    // This checks wheter the ball is outside the field.
    if (ballPosition->x < -50 || ballPosition->x > 50 ||
        ballPosition->z < -25 || ballPosition->z > 25 )
    {
        if (ballPosition->x > 50 && // Was it on the goal side of the field?
            ballPosition->z > -5 && ballPosition->z < 5) // Was it a goal?
        {
            end(true);
        }
        else end(false);
    }

    for(unsigned int i = 0; i < allOpponents.size(); i++)
    {
        if (player->collidingWith((Object) allOpponents[i]))
            end(false);
    }

    for(unsigned int i = 0; i < allOpponents.size(); i++)
    {
        if (ball->collidingWith((Object) allOpponents[i])) end(false);
    }

    for(unsigned int i = 0; i < opponents.size() - 1; i++)
    {
        for(unsigned int j = i + 1; j < opponents.size(); j++)
        {
            if (opponents[i].collidingWith((Object) opponents[j]))
            {
                opponents[i].move(Object::BACK, PLAYER_MOVEMENT_AMOUNT * 0.9);
                opponents[j].move(Object::FRONT, PLAYER_MOVEMENT_AMOUNT * 0.9);
            }
        }
    }
}

void Scene::end(bool success) {
    // TODO show results on the window
    game->endRound(success);
}
