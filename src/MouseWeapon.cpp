#include "MouseWeapon.h"

Vector2 MouseWeapon::GetFireDirection(Vector2 playerPos, Vector2 lastMoveDir)
{
    Vector2 mouse = GetMousePosition();

    Vector2 dir;
    dir.x = mouse.x - playerPos.x;
    dir.y = mouse.y - playerPos.y;

    return dir;
}