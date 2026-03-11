#pragma once
#include "raylib.h"

class Weapon
{
public:
    virtual ~Weapon() = default;

    virtual Vector2 GetFireDirection(Vector2 playerPos, Vector2 lastMoveDir) = 0;
};