#include "GameManager.h"
#include "DirectionWeapon.h"
#include "MouseWeapon.h"
#include <cmath>
#include <algorithm>

GameManager& GameManager::GetInstance()
{
    static GameManager instance;
    return instance;
}

void GameManager::Init(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    player = new Player(400, 300);

    // Start enemies
    for (int i = 0; i < 5; i++)
    {
        enemies.push_back(
            std::make_unique<FastEnemy>(
                (float)GetRandomValue(0, screenWidth),
                (float)GetRandomValue(0, screenHeight)
            )
        );
    }

    gameTime = 0.0f;
    spawnTimer = 0.0f;
    attackTimer = 0.0f;

    currentWeapon = std::move(std::make_unique<DirectionWeapon>());
}

void GameManager::Update(float dt)
{
    gameTime += dt;
    spawnTimer += dt;
    attackTimer += dt;

    player->Update(dt);

    // =============================
    // Endless Enemy Spawn
    // =============================
    if (spawnTimer >= spawnInterval)
    {
        spawnTimer = 0.0f;

        int side = GetRandomValue(0, 3);

        float x;
        float y;

        if (side == 0) // left
        {
            x = 0;
            y = GetRandomValue(0, screenHeight);
        }
        else if (side == 1) // right
        {
            x = screenWidth;
            y = GetRandomValue(0, screenHeight);
        }
        else if (side == 2) // top
        {
            x = GetRandomValue(0, screenWidth);
            y = 0;
        }
        else // bottom
        {
            x = GetRandomValue(0, screenWidth);
            y = screenHeight;
        }

        enemies.push_back(
            std::make_unique<FastEnemy>(x, y)
        );
    }

    // =============================
    // Weapon Switching
    // =============================
    if (IsKeyPressed(KEY_TAB))
    {
        if (dynamic_cast<DirectionWeapon*>(currentWeapon.get()))
            currentWeapon = std::make_unique<MouseWeapon>();
        else
            currentWeapon = std::make_unique<DirectionWeapon>();
    }

    // =============================
    // Auto Shooting (Strategy Pattern)
    // =============================
    if (attackTimer >= attackCooldown)
    {
        attackTimer = 0.0f;

        Vector2 dir = currentWeapon->GetFireDirection(
            player->GetPosition(),
            player->GetLastMoveDirection()
        );

        float length = sqrt(dir.x * dir.x + dir.y * dir.y);

        if (length != 0)
        {
            dir.x /= length;
            dir.y /= length;

            int damage = 1;

            if (dynamic_cast<MouseWeapon*>(currentWeapon.get()))
            {
                damage = 3;
            }

            projectiles.push_back(
                std::make_unique<Projectile>(
                    player->GetPosition(),
                    dir,
                    damage
                )
            );
        }
    }

    // =============================
    // Update Enemies
    // =============================
    for (auto& enemy : enemies)
    {
        enemy->Update(dt, player->GetPosition());

        float dx = enemy->GetPosition().x - player->GetPosition().x;
        float dy = enemy->GetPosition().y - player->GetPosition().y;

        float distance = sqrt(dx * dx + dy * dy);

        if (distance < enemy->GetRadius() + 20.0f)
        {
            player->TakeDamage(1);
        }
    }

    // =============================
    // Update Projectiles
    // =============================
    for (auto& projectile : projectiles)
    {
        projectile->Update(dt);
    }

    // =============================
    // Projectile -> Enemy Collision
    // =============================
    for (auto& projectile : projectiles)
    {
        for (auto& enemy : enemies)
        {
            float dx = enemy->GetPosition().x - projectile->GetPosition().x;
            float dy = enemy->GetPosition().y - projectile->GetPosition().y;

            float distance = sqrt(dx * dx + dy * dy);

            if (distance < enemy->GetRadius() + projectile->GetRadius())
            {
                enemy->TakeDamage(projectile->GetDamage());
                projectile->Destroy();
            }
        }
    }

    // =============================
    // Remove Dead Enemies
    // =============================
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& e)
            {
                return !e->IsAlive();
            }),
        enemies.end()
    );

    // =============================
    // Remove Dead Projectiles
    // =============================
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [](const std::unique_ptr<Projectile>& p)
            {
                return !p->IsAlive();
            }),
        projectiles.end()
    );
}

void GameManager::Draw()
{
    player->Draw();

    for (const auto& enemy : enemies)
    {
        enemy->Draw();
    }

    for (const auto& projectile : projectiles)
    {
        projectile->Draw();
    }

    DrawText(TextFormat("HP: %d", player->GetHP()), 20, 20, 20, WHITE);
    DrawText(TextFormat("Time: %.0f", gameTime), 20, 50, 20, WHITE);
    DrawText(TextFormat("Enemies: %i", enemies.size()), 20, 80, 20, WHITE);
    DrawText("TAB = Switch Weapon", 20, 110, 20, WHITE);
}