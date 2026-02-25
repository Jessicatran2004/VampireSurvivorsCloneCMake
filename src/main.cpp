#include "raylib.h"
#include <vector>
#include <cmath>
#include <memory>
// ---------------- PLAYER ----------------
class Player
{
public:
    Vector2 position;
    float speed = 300.0f;

    Player(float x, float y)
    {
        position = { x, y };
    }

    void Update(float dt)
    {
        if (IsKeyDown(KEY_W)) position.y -= speed * dt;
        if (IsKeyDown(KEY_S)) position.y += speed * dt;
        if (IsKeyDown(KEY_A)) position.x -= speed * dt;
        if (IsKeyDown(KEY_D)) position.x += speed * dt;
    }

    void Draw() const
    {
        DrawCircleV(position, 20, WHITE);
    }
};

// ---------------- ENEMY ----------------
class Enemy
{
public:
    Vector2 position;
    float speed;

    Enemy(float x, float y, float s)
        : speed(s)
    {
        position = { x, y };
    }

    virtual void Update(float dt, const Vector2& playerPos)
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

    virtual void Draw() const
    {
        DrawCircleV(position, 15, RED);
    }

    virtual ~Enemy() = default;
};
class FastEnemy : public Enemy
{
public:
    FastEnemy(float x, float y)
        : Enemy(x, y, 150.0f) {
    }

    void Draw() const override
    {
        DrawCircleV(position, 15, ORANGE);
    }
};

class TankEnemy : public Enemy
{
public:
    TankEnemy(float x, float y)
        : Enemy(x, y, 50.0f) {
    }

    void Draw() const override
    {
        DrawCircleV(position, 25, PURPLE);
    }
};
// ---------------- MAIN ----------------
int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Vampire Clone");
    SetTargetFPS(60);

    Player player(400, 300);

    std::vector<std::unique_ptr<Enemy>> enemies;
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            enemies.push_back(
                std::make_unique<FastEnemy>(
                    (float)GetRandomValue(0, screenWidth),
                    (float)GetRandomValue(0, screenHeight)
                )
            );
        }
        else
        {
            enemies.push_back(
                std::make_unique<TankEnemy>(
                    (float)GetRandomValue(0, screenWidth),
                    (float)GetRandomValue(0, screenHeight)
                )
            );
        }
    }
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        player.Update(dt);

        for (auto& enemy : enemies)
        {
            enemy->Update(dt, player.position);
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);

        player.Draw();

        for (const auto& enemy : enemies)
        {
            enemy->Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}