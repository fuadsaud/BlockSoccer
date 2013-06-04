#include "Scene.h"

Scene::Scene()
{
    player = new Person();
    camera = new Camera(player);
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
    player->render();
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
    }

    camera->syncWithPerson();
}
