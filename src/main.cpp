#include "raylib.h"
#include "GameManager.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Vampire Clone");
    SetTargetFPS(60);

    GameManager::GetInstance().Init(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        GameManager::GetInstance().Update(dt);

        BeginDrawing();
        ClearBackground(DARKPURPLE);

        GameManager::GetInstance().Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}