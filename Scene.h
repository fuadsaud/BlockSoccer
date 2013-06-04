#ifndef PERSON_H
#include "Person.h"
#endif

#ifndef CAMERA_H
#include "Camera.h"
#endif

class Scene
{
public:
    Scene();

    void init();
    void display();

private:
    Person * player;
    Camera * camera;
};
