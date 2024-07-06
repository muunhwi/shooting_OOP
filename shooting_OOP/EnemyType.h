#pragma once
#include "Movement.h"

struct EnemyType
{
    char shape;
    char attackShape;
    int cooldown;
    int perAttackCount;
    int timer = 0;
    Movement _mv;
};