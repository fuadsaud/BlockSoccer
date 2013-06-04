#include "Scene.h"

Scene::Scene()
{
    player = new Person();
    camera = new Camera(player);
}

void Scene::init()
{
    camera->syncWithPerson();
}

void Scene::display()
{
    player->render();
}
