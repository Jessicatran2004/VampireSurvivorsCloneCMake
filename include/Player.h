#pragma once
#include "raylib.h"

class Player
{
public:
    Player(float x, float y);

    void Update(float dt);
    void Draw() const;

    Vector2 GetPosition() const;
    Vector2 GetLastMoveDirection() const;

    int GetHP() const;
    void TakeDamage(int amount);

private:
    Vector2 position;
    float speed;
    int hp;
    float radius;

    Vector2 lastMoveDirection = { 1, 0 };
};