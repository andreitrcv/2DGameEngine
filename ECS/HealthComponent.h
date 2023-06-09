#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"


class HealthComponent : public Component{

public:
    HealthComponent(){}
    ~HealthComponent(){}

    int decHealth(int dec){
        health = health - dec;
        return health;
    }

    int getHealth(){
        return health;
    }
private:

    int health = 100;

};