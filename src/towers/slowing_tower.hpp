#include "tower.hpp"
#include "slowing_bullet.hpp"

class SlowingTower : public Tower {
    public:
        SlowingTower(const TextureHolder& textures);

    private:
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const;
};