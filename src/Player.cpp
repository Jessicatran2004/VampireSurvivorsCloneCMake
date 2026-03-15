#include "Player.h"
#include <cmath>

Player::Player(float x, float y)
{
    position = { x, y };
    speed = 300.0f;
    hp = 100;
    radius = 20.0f;
}

void Player::Update(float dt)
{
    if (damageTimer > 0)
    {
        damageTimer -= dt;
    }
    Vector2 direction = { 0, 0 };

    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;
    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0)
    {
        direction.x /= length;
        direction.y /= length;

        lastMoveDirection = direction;  

        position.x += direction.x * speed * dt;
        position.y += direction.y * speed * dt;
    }
}

void Player::Draw() const
{
    DrawCircleV(position, radius, Color{ 245,255,98,255 });
}

Vector2 Player::GetPosition() const
{
    return position;
}

int Player::GetHP() const
{
    return hp;
}

void Player::TakeDamage(int amount)
{
    if (damageTimer > 0)
        return;

    hp -= amount;

    if (hp < 0)
        hp = 0;

    damageTimer = damageCooldown;
}
Vector2 Player::GetLastMoveDirection() const
{
    return lastMoveDirection;
}
void Player::AddXP(int amount)
{
    xp += amount;

    if (xp >= level * 10)
    {
        xp = 0;
        level++;
    }
}

int Player::GetLevel() const
{
    return level;
}