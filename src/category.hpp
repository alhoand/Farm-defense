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
        Enemy = 1 << 3,
        Ghost = 1 << 4,
        BasicBullet = 1 << 5,
        SuperBullet = 1 << 6,

        Tower = ShootingTower | SlowingTower,
        Bullet = BasicBullet | SuperBullet
        
    };
}

