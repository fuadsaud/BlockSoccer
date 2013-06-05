#include "Scene.h"

Scene::Scene()
{
    player = new Person();
    camera = new Camera(player);
    opponents.push_back(Person(new Point(10,0,0)));
    opponents.push_back(Person(new Point(10,0,-10)));
    opponents.push_back(Person(new Point(10,0,10)));
    opponents.push_back(Person(new Point(15,0,0)));
}

void Scene::init()
{
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    camera->syncWithPerson();
}

void Scene::display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawScenario();
    for (unsigned i=0; i<opponents.size(); i++) {
        opponents[i].render();
    }
    player->render();
}

void Scene::moveOpponents() {
    for (unsigned i=0; i<opponents.size(); i++) {
        Point * p = player->getPosition();
        opponents[i].lookAt(p);
        opponents[i].move(Person::FRONT,1);
    }
}

void Scene::drawScenario() {
    float w=100;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.14, 0.34, 0.02);
    glBegin(GL_QUADS);
        glVertex3f(-w/2, 0, -w/4);
        glVertex3f(-w/2, 0,  w/4);
        glVertex3f( w/2, 0,  w/4);
        glVertex3f( w/2, 0, -w/4);

    glEnd();

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);

    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-w/2 + 1.5, 0.01, -w/4+1.5);
        glVertex3f( w/2 - 1.5, 0.01, -w/4+1.5);
        glVertex3f( w/2 - 1.5, 0.01,  w/4-1.5);
        glVertex3f(-w/2 + 1.5, 0.01,  w/4-1.5);
        glVertex3f(-w/2 + 1.5, 0.01, -w/4+1.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0.01, -w/4+1.5);
        glVertex3f(0, 0.01,  w/4-1.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
        for (int i=0; i<360; i++) {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle)*4, 0.01, sin(angle)*4);
        }
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(-w/2 + 1.5, 0.01, -13);
        glVertex3f(-w/2 + 15,  0.01, -13);
        glVertex3f(-w/2 + 15,  0.01,  13);
        glVertex3f(-w/2 + 1.5, 0.01,  13);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-w/2 + 1.5, 0.01, -7);
        glVertex3f(-w/2 + 8,   0.01, -7);
        glVertex3f(-w/2 + 8,   0.01,  7);
        glVertex3f(-w/2 + 1.5, 0.01,  7);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(w/2 - 1.5, 0.01, -7);
        glVertex3f(w/2 - 8,   0.01, -7);
        glVertex3f(w/2 - 8,   0.01,  7);
        glVertex3f(w/2 -1.5, 0.01,  7);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(w/2 - 1.5, 0.01, -13);
        glVertex3f(w/2 - 15,  0.01, -13);
        glVertex3f(w/2 - 15,  0.01,  13);
        glVertex3f(w/2 - 1.5, 0.01,  13);
    glEnd();

    glBegin(GL_LINE_LOOP);
        for (int i=90; i<270; i++) {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle)*2+w/2-15, 0.01, sin(angle)*4);
        }
    glEnd();

    glBegin(GL_LINE_LOOP);
        for (int i=270; i<450; i++) {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle)*2-w/2+15, 0.01, sin(angle)*4);
        }
    glEnd();
    glPushMatrix();
        glTranslatef(w/2-1.5,0,-5);
        glRotatef(-90,1,0,0);
        GLUquadricObj *quadObj = gluNewQuadric();
        gluCylinder(quadObj, 0.1, 0.1, 3.5, 10, 10);
        glTranslatef(0,-10,0);
        gluCylinder(quadObj, 0.1, 0.1, 3.5, 10, 10);
        glTranslatef(0,0,3.4);
        glRotatef(-90,1,0,0);
        gluCylinder(quadObj, 0.1, 0.1, 10, 10, 10);
    glPopMatrix();

}

void Scene::keyboardAction(const char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            player->move(Person::FRONT, 1);
            break;
        case 's':
        case 'S':
            player->move(Person::BACK, 1);
            break;
        case 'a':
        case 'A':
            player->move(Person::LEFT, 1);
            break;
        case 'd':
        case 'D':
            player->move(Person::RIGHT, 1);
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
    }

    camera->syncWithPerson();
}
