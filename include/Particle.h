#pragma once
#include "raylib.h"

class Particle
{
public:
    Particle(Vector2 pos);

    void Update(float dt);
    void Draw() const;
    bool IsAlive() const;

private:
    Vector2 position;
    Vector2 velocity;

    float life = 1.0f;
};
