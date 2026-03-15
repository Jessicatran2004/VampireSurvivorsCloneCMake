#include "ExperienceOrb.h"
#include <math.h>

ExperienceOrb::ExperienceOrb(Vector2 pos)
{
    position = pos;
}

void ExperienceOrb::Update(float dt)
{
}

void ExperienceOrb::Draw() const
{
    float pulse = sin(GetTime() * 5) * 3;

    DrawCircleV(position, radius + pulse, Color{ 255,100,200,120 });
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