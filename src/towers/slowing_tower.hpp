#include "tower.hpp"

class SlowingTower : public Tower {
    public:
        SlowingTower(const TextureHolder& textures);

    private:
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const;
};