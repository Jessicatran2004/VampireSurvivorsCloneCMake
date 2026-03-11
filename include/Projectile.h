#pragma once
#include "raylib.h"

class Projectile
{
public:
    Projectile(Vector2 startPos, Vector2 direction, int dmg);

    void Update(float dt);
    void Draw() const;

    Vector2 GetPosition() const;
    float GetRadius() const;

    bool IsAlive() const;
    void Destroy();

    int GetDamage() const;
   
private:
    Vector2 position;
    Vector2 velocity;

    float speed = 500.0f;
    float radius = 5.0f;

    int damage = 1;

    bool alive = true;
};