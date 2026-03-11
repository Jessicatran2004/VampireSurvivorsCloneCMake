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
    DrawCircleV(position, 15, BLACK);
}

// FastEnemy
FastEnemy::FastEnemy(float x, float y)
    : Enemy(x, y, 150.0f) 
{
    health = 2;
}

void FastEnemy::Draw() const
{
    DrawCircleV(position, radius + 6, Color{ 100, 200, 255, 80 });
    DrawCircleV(position, radius + 3, Color{ 100, 200, 255, 150 });
    DrawCircleV(position, radius, Color{ 120, 220, 255, 255 });
}

// TankEnemy
TankEnemy::TankEnemy(float x, float y)
    : Enemy(x, y, 50.0f) 
{
    radius = 25.0f;
    health = 5;
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

void Enemy::TakeDamage(int damage)
{
    health -= damage;

    if (health <= 0)
    {
        alive = false;
    }
}

BossEnemy::BossEnemy(float x, float y)
    : Enemy(x, y, 40.0f)
{
    radius = 40;
    health = 20;
}

void BossEnemy::Draw() const
{
    DrawCircleV(position, 40, DARKPURPLE);
}