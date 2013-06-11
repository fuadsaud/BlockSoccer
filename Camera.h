#pragma once

#include "Includes.h"

#include "Person.h"
#include <math.h>

class Camera
{
public:
    Person * person;

    Camera(Person * p);

    void syncWithPerson();
};
