#include "Particle.h"

Particle::Particle(Vector2 pos)
{
    position = pos;

    velocity.x = GetRandomValue(-100, 100);
    velocity.y = GetRandomValue(-100, 100);
}

void Particle::Update(float dt)
{
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    life -= dt;
}

void Particle::Draw() const
{
    DrawCircleV(position, 3, ORANGE);
}

bool Particle::IsAlive() const
{
    return life > 0;
}