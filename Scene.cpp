#include "Scene.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

Scene::Scene(Game *g)
{
    freeze = false;
    game = g;
    player = new Person();
    camera = new Camera(player);
    ball = new Ball(player);
    opponents.push_back(Person(new Point(10, 0,   0)));
    opponents.push_back(Person(new Point(10, 0, -10)));
    opponents.push_back(Person(new Point(10, 0,  10)));
    opponents.push_back(Person(new Point(15, 0,   0)));

    goalKepper = new Person(new Point(48, 0, 0));
}

void Scene::init()
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
    {
        opponents[i].render();
    }

    ball->render();
    player->render();
    showData();
    camera->syncWithPerson();
}

void Scene::background()
{
    ballBehavior();
    adversaryTeamBehavior();
    collisionMonitor();
    game->getCurrentRound();
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
            freeze = true;
            break;
        case 'c':
        case 'C':
            if (freeze) {
                game->endRound(finalStatus);
            }
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
        Point * p = ball->getPosition();

        srand(time(0));
        for(unsigned int i = 0; i < opponents.size(); i++)
        {
            opponents[i].lookAt(p);
            opponents[i].move(Person::FRONT, PLAYER_MOVEMENT_AMOUNT*0.8);
        }

        goalKepper->lookAt(p);

        Point * kp = goalKepper->getPosition();
        float move = PLAYER_MOVEMENT_AMOUNT*3;
        if (kp->z+move < p->z) {
            kp->z += move;
        } else if (kp->z-move > p->z) {
            kp->z -= move;
        }


        if (kp->z > 5)
        {
            kp->z = 5;
        } else if (kp->z < -5)
        {
            kp->z = -5;
        }

}

void Scene::ballBehavior()
{
    if (!ball->attached())
    {
        ball->go();
    }
}

void Scene::collisionMonitor()
{
    Point * p = player->getPosition();

    std::vector<Person> allOpponents(opponents);
    allOpponents.push_back(*goalKepper);

    if (p->x < -50 || p->x > 50 || p->z < -25 || p->z > 25 ) {
        end(false);
    }


    Point * ballPoint = ball->getPosition();
    if (ballPoint->x < -50 || ballPoint->x > 50 || ballPoint->z < -25 || ballPoint->z > 25 ) {
        if (ballPoint->x > 50 && ballPoint->z > -5 && ballPoint->z < 5) {
            end(true);
        } else {
            end(false);
        }
    }

    for(unsigned int i = 0; i < allOpponents.size(); i++)
    {
        if (player->collidingWith((Object) allOpponents[i]))
        {
            end(false);
        }
    }

    for(unsigned int i = 0; i < allOpponents.size(); i++)
    {
        if (ball->collidingWith((Object) allOpponents[i]))
        {
            end(false);
        }
    }

    for(unsigned int i = 0; i < opponents.size() - 1; i++)
    {
        for(unsigned int j = i + 1; j < opponents.size(); j++)
        {
            if (opponents[i].collidingWith((Object) opponents[j]))
            {
                opponents[i].move(Object::BACK, PLAYER_MOVEMENT_AMOUNT*0.9);
                opponents[j].move(Object::FRONT, PLAYER_MOVEMENT_AMOUNT*0.9);
            }
        }
    }
}

void Scene::showData() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,800,0,600,0,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    char s[200];
    sprintf(s,"Gols: %d", game->getScore());
    putTextInWindow(s,-0.9,0.9);
    sprintf(s,"Tentativas: %d", game->getRounds());
    putTextInWindow(s,-0.9,0.8);
    if (showFinalMessage) {
        glColor3f(0,0,0);
        putTextInWindow(finalMessage,-0.095,0.098);
        glColor3f(1,1,0);
        putTextInWindow(finalMessage,-0.1,0.1);
        sprintf(s,"Presione C para continuar");
        glColor3f(0,0,0);
        putTextInWindow(s,-0.295,-0.102);
        glColor3f(1,1,0);
        putTextInWindow(s,-0.3,-0.1);
    }
}

void Scene::stopScene() {
    ball->stop();
    player->stop();
    freeze = true;
    for(unsigned int i = 0; i < opponents.size(); i++)
    {
        opponents[i].stop();
    }
}

void Scene::end(bool success) {
    stopScene();
    showFinalMessage = true;
    if (success) {
        sprintf(finalMessage,"GOOOOL");
    } else {
        sprintf(finalMessage,"Que Pena!");
    }
    finalStatus = success;
}


void Scene::putTextInWindow(char*s, float x, float y) {
    glRasterPos2f(x,y);
    for(int i =0; i< strlen(s); i++) {

        glutBitmapCharacter(
            //GLUT_BITMAP_TIMES_ROMAN_24,
            GLUT_BITMAP_HELVETICA_18,
            s[i]);
    }
}
