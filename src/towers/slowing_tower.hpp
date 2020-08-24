#include "tower.hpp"

/* This is a slowing tower that
 * - slows down enemies in range, according to their type
 * - has a pretty good range, 400 units
*/

class SlowingTower : public Tower {
    public:
        SlowingTower(const TextureHolder& textures);

    private:
        void CreateBullet(SceneNode& node, const TextureHolder& textures) const { }
};