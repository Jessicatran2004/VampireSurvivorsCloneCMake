#include "DamageNumber.h"

DamageNumber::DamageNumber(Vector2 pos, int dmg)
{
    position = pos;
    damage = dmg;
}

void DamageNumber::Update(float dt)
{
    timer += dt;

    position.y -= speed * dt;

    if (timer >= lifetime)
    {
        alive = false;
    }
}

void DamageNumber::Draw() const
{
    DrawText(
        TextFormat("%i", damage),
        position.x,
        position.y,
        20,
        YELLOW
    );
}

bool DamageNumber::IsAlive() const
{
    return alive;
}