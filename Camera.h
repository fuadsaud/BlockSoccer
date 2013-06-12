#pragma once

#include "Includes.h"

#include "Person.h"

class Camera
{
public:
    Person * person;

    Camera(Person * p);

    void syncWithPerson();
};
