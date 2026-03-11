#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <memory>
#include "Projectile.h"
#include "Weapon.h"
#include "ExperienceOrb.h"


class GameManager
{
public:
    static GameManager& GetInstance();

    void Init(int screenWidth, int screenHeight);
    void Update(float dt);
    void Draw();

private:
    GameManager() = default;

    Player* player = nullptr;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<std::unique_ptr<ExperienceOrb>> orbs;

    float attackTimer = 0.0f;
    float attackCooldown = 1.0f;

    int screenWidth = 0;
    int screenHeight = 0;


    float gameTime = 0.0f;        // in-game timer

    float spawnTimer = 0.0f;      // endless spawn timer
    float spawnInterval = 2.0f;   // spawn every 2 seconds
    int enemiesPerSpawn = 1;

    int wave = 1;
    float waveTimer = 0.0f;
    float waveDuration = 20.0f;


    std::unique_ptr<Weapon> currentWeapon;  // Strategy pattern
};

