#pragma once
#include "raylib.h"

class ExperienceOrb
{
public:
    ExperienceOrb(Vector2 pos);

    void Update(float dt);
    void Draw() const;

    Vector2 GetPosition() const;
    float GetRadius() const;
    bool IsCollected() const;
    void Collect();

private:
    Vector2 position;
    float radius = 6.0f;
    bool collected = false;
}; 
