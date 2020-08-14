#include "tower.hpp"
#include "bomb.hpp"

class BombingTower : public Tower {
    public:
        BombingTower();

    private:
        // same as for others, except will create bombs
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const;
}