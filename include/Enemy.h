#pragma once
#include "raylib.h"

class Enemy
{
public:
    Enemy(float x, float y, float speed);
    virtual ~Enemy() = default;

    virtual void Update(float dt, const Vector2& playerPos);
    virtual void Draw() const;

    Vector2 GetPosition() const;
    float GetRadius() const;

    bool IsAlive() const;
    void Destroy();

protected:
    Vector2 position;
    float speed;
    float radius;

    bool alive = true;
};

class FastEnemy : public Enemy
{
public:
    FastEnemy(float x, float y);
    void Draw() const override;
};

class TankEnemy : public Enemy
{
public:
    TankEnemy(float x, float y);
    void Draw() const override;

};