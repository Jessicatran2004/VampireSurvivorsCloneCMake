#include "Enemy.h"
#include <cmath>
#include <algorithm>


//konstructor for Enemy class
Enemy::Enemy(float x, float y, float s)
{
    position = { x, y };
    speed = s;
	radius = 15.0f;
}

void Enemy::Update(float dt, const Vector2& playerPos)
{
    Vector2 direction;
    direction.x = playerPos.x - position.x;
    direction.y = playerPos.y - position.y;

    float length = sqrt(direction.x * direction.x +
        direction.y * direction.y);

    if (length != 0)
    {
        direction.x /= length;
        direction.y /= length;

        position.x += direction.x * speed * dt;
        position.y += direction.y * speed * dt;
    }
}

void Enemy::Draw() const
{
    DrawCircleV(position, 15, RED);
}

// FastEnemy
FastEnemy::FastEnemy(float x, float y)
    : Enemy(x, y, 150.0f) {
}

void FastEnemy::Draw() const
{
    DrawCircleV(position, 15, ORANGE);
}

// TankEnemy
TankEnemy::TankEnemy(float x, float y)
    : Enemy(x, y, 50.0f) 
{
    radius = 25.0f;
}

void TankEnemy::Draw() const
{
    DrawCircleV(position, 25, PURPLE);
}
Vector2 Enemy::GetPosition() const
{
    return position;
}

float Enemy::GetRadius() const
{
    return radius;
}

bool Enemy::IsAlive() const
{
    return alive;
}
void Enemy::Destroy()
{
    alive = false;
}