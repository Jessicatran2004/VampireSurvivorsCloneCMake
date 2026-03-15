#include "Enemy.h"
#include <cmath>
#include <algorithm>


//konstructor for Enemy class
Enemy::Enemy(float x, float y, float s)
{
    position = { x, y };
    speed = s;
    radius = 15.0f;

    maxHp = 5;
    hp = maxHp;

}

void Enemy::Update(float dt, const Vector2& playerPos)
{
    if (hitFlashTimer > 0)
    {
        hitFlashTimer -= dt;
    }
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
    DrawCircleLines(position.x, position.y, radius + 2, BLACK);
    Color enemyColor = RED;

    if (hitFlashTimer > 0)
    {
        enemyColor = WHITE;
    }

    DrawCircleV(position, radius, enemyColor);
    float barWidth = radius * 2;
    float barHeight = 4;

    float healthPercent = (float)hp / maxHp;

    Vector2 barPos =
    {
        position.x - barWidth / 2,
        position.y - radius - 10
    };

    DrawRectangle(barPos.x, barPos.y, barWidth, barHeight, DARKGRAY);

    DrawRectangle(
        barPos.x,
        barPos.y,
        barWidth * healthPercent,
        barHeight,
        LIME
    );
}


// FastEnemy
FastEnemy::FastEnemy(float x, float y)
    : Enemy(x, y, 150.0f)
{
    maxHp = 2;
    hp = maxHp;
}

void FastEnemy::Draw() const
{
    Color c = Color{ 120,220,255,255 };

    if (hitFlashTimer > 0)
        c = WHITE;
  
   
    DrawCircleV(position, radius + 6, Color{ 100, 200, 255, 80 });
    DrawCircleV(position, radius + 3, Color{ 100, 200, 255, 150 });
    DrawCircleV(position, radius, Color{ 120, 220, 255, 255 });

    DrawHealthBar();
}

// TankEnemy
TankEnemy::TankEnemy(float x, float y)
    : Enemy(x, y, 50.0f)
{
    radius = 25.0f;

    maxHp = 20;
    hp = maxHp;
}

void TankEnemy::Draw() const
{
    if (hitFlashTimer > 0)
    DrawCircleV(position, 25, YELLOW);
    DrawHealthBar();
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
    hp -= damage;

    hitFlashTimer = hitFlashDuration;

    if (hp <= 0)
    {
        alive = false;
    }
}

BossEnemy::BossEnemy(float x, float y)
    : Enemy(x, y, 40.0f)
{
    radius = 40;

    maxHp = 50;
    hp = maxHp;
}

void BossEnemy::Draw() const
{
    DrawCircleV(position, 40, DARKGREEN);
    DrawHealthBar();
}
void Enemy::DrawHealthBar() const
{
    float barWidth = radius * 2;
    float barHeight = 4;

    float healthPercent = (float)hp / maxHp;

    Vector2 barPos =
    {
        position.x - barWidth / 2,
        position.y - radius - 10
    };

    DrawRectangle(barPos.x, barPos.y, barWidth, barHeight, DARKGRAY);

    DrawRectangle(
        barPos.x,
        barPos.y,
        barWidth * healthPercent,
        barHeight,
        LIME
    );
}