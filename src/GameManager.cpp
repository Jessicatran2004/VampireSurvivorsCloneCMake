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

    currentWeapon = std::make_unique<DirectionWeapon>();
}

void GameManager::Update(float dt)
{
    // MENU
    if (gameState == GameState::Menu)
    {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, startButton) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            gameState = GameState::Playing;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            gameState = GameState::Playing;
        }

        return;
    }

    // GAME
    gameTime += dt;
    spawnTimer += dt;
    attackTimer += dt;
    waveTimer += dt;

    player->Update(dt);

    if (waveTimer >= waveDuration)
    {
        waveTimer = 0.0f;
        wave++;

        enemiesPerSpawn++;
        spawnInterval -= 0.2f;

        if (spawnInterval < 0.5f)
            spawnInterval = 0.5f;
    }

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
        static int lastBossMinute = -1;

        int minute = (int)(gameTime / 60);

        if (minute > lastBossMinute)
        {
            lastBossMinute = minute;

            enemies.push_back(
                std::make_unique<BossEnemy>(
                    screenWidth / 2,
                    0
                )
            );
        }
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
    for (auto& orb : orbs)
    {
        float dx = orb->GetPosition().x - player->GetPosition().x;
        float dy = orb->GetPosition().y - player->GetPosition().y;

        float dist = sqrt(dx * dx + dy * dy);

        if (dist < orb->GetRadius() + 20)
        {
            player->AddXP(1);
            orb->Collect();
        }
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
                damageNumbers.push_back(
                    std::make_unique<DamageNumber>(
                        enemy->GetPosition(),
                        projectile->GetDamage()
                    )
                );

                if (!enemy->IsAlive())
                {
                    orbs.push_back(
                        std::make_unique<ExperienceOrb>(
                            enemy->GetPosition()
                        )
                    );

                    for (int i = 0; i < 10; i++)
                    {
                        particles.push_back(
                            std::make_unique<Particle>(
                                enemy->GetPosition()
                            )
                        );
                    }
                }
            }
        }
    }
    for (auto& p : particles)
    {
        p->Update(dt);
    }

    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const std::unique_ptr<Particle>& p)
            {
                return !p->IsAlive();
            }),
        particles.end()
    );

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
    for (auto& dmg : damageNumbers)
{
    dmg->Update(dt);
}
    damageNumbers.erase(
        std::remove_if(
            damageNumbers.begin(),
            damageNumbers.end(),
            [](const std::unique_ptr<DamageNumber>& d)
            {
                return !d->IsAlive();
            }),
        damageNumbers.end()
    );

}

void GameManager::Draw()
{
    for (int x = 0; x < screenWidth; x += 40)
    {
        DrawLine(x, 0, x, screenHeight, Color{ 40,40,60,255 });
    }

    for (int y = 0; y < screenHeight; y += 40)
    {
        DrawLine(0, y, screenWidth, y, Color{ 40,40,60,255 });
    }
   if (gameState == GameState::Menu)
   {
    ClearBackground(BLACK);
    DrawRectangle(10, 10, 180, 170, Color{ 0,0,0,120 });
    DrawText("VAMPIRE SURVIVOR", 180, 200, 40, SKYBLUE);
    DrawText("Press ENTER to start", 260, 260, 20, WHITE);
    DrawText("WASD = Move", 260, 320, 20, WHITE);
    DrawText("TAB = Switch Weapon", 260, 350, 20, WHITE);
    DrawText("Press ESC to quit", 260, 380, 20, GRAY);
    return;
    }

    player->Draw();

    for (const auto& enemy : enemies)
    {
        enemy->Draw();
    }

    for (const auto& projectile : projectiles)
    {
        projectile->Draw();

    }
    for (const auto& p : particles)
    {
        p->Draw();
    }

    for (const auto& orb : orbs)
    {
        orb->Draw();
    }
    for (const auto& dmg : damageNumbers)
    {
        dmg->Draw();
    }

    DrawText(TextFormat("HP: %d", player->GetHP()), 20, 20, 20, WHITE);
    DrawText(TextFormat("Time: %.0f", gameTime), 20, 50, 20, WHITE);
    DrawText(TextFormat("Enemies: %i", enemies.size()), 20, 80, 20, WHITE);
    DrawText("TAB = Switch Weapon", 20, 110, 20, WHITE);
    DrawText(TextFormat("Wave: %i", wave), 20, 140, 20, WHITE);
    DrawText(TextFormat("Level: %i", player->GetLevel()), 20, 170, 20, WHITE);
}