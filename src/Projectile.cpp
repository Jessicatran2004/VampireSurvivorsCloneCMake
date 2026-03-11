#include "Projectile.h"

Projectile::Projectile(Vector2 startPos, Vector2 direction)
{
    position = startPos;

    velocity.x = direction.x * speed;
    velocity.y = direction.y * speed;
}

void Projectile::Update(float dt)
{
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void Projectile::Draw() const
{
    DrawCircleV(position, radius, YELLOW);
}

Vector2 Projectile::GetPosition() const
{
    return position;
}

float Projectile::GetRadius() const
{
    return radius;
}

bool Projectile::IsAlive() const
{
    return alive;
}

void Projectile::Destroy()
{
    alive = false;
}