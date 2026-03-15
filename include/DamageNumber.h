#pragma once
#include "raylib.h"

class DamageNumber
{
public:

    DamageNumber(Vector2 pos, int dmg);

    void Update(float dt);
    void Draw() const;

    bool IsAlive() const;

private:

    Vector2 position;
    int damage;

    float lifetime = 1.0f;
    float timer = 0.0f;

    float speed = 40.0f;

    bool alive = true;
};