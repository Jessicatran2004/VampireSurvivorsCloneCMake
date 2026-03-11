#pragma once
#include "Weapon.h"

class DirectionWeapon : public Weapon
{
public:
    Vector2 GetFireDirection(Vector2 playerPos, Vector2 lastMoveDir) override;
};