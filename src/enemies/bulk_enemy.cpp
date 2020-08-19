#include "bulk_enemy.hpp"

BulkEnemy::BulkEnemy(const TextureHolder& textures, float difficultyLevel, float travelledDistance, int directionIndex)
    : Enemy(Enemy::Bulk, textures, difficultyLevel, travelledDistance, directionIndex)
    { }
