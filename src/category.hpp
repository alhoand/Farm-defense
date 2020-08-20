#pragma once
// Represents groups that are likely to receive similar commands
// e.g. towers receive shoot-commands and enemies move-commands
// c. f. Command and CommandQueue classes for more info
namespace Category {
    enum Type {
        None = 0,
        Scene = 1 << 0,
        ShootingTower = 1 << 1,
        SlowingTower = 1 << 2,
        BombingTower = 1 << 3,
        Enemy = 1 << 4,
        Ghost = 1 << 5,
        BasicBullet = 1 << 6,
        SuperBullet = 1 << 7,
        Bomb = 1 << 8,

        Tower = ShootingTower | SlowingTower | BombingTower,
        Bullet = BasicBullet | SuperBullet
        
    };
}

