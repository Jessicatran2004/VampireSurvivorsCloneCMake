#include "ExperienceOrb.h"

ExperienceOrb::ExperienceOrb(Vector2 pos)
{
    position = pos;
}

void ExperienceOrb::Update(float dt)
{
}

void ExperienceOrb::Draw() const
{
    DrawCircleV(position, radius + 3, Color{ 255,105,180,100 });
    DrawCircleV(position, radius, PINK);
}

Vector2 ExperienceOrb::GetPosition() const
{
    return position;
}

float ExperienceOrb::GetRadius() const
{
    return radius;
}

bool ExperienceOrb::IsCollected() const
{
    return collected;
}

void ExperienceOrb::Collect()
{
    collected = true;
}