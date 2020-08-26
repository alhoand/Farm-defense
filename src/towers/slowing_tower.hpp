#include "tower.hpp"

/* This is a slowing tower that
 * - slows down enemies in range, according to their type
 * - has a pretty good range, 300 units
*/

class SlowingTower : public Tower {
    public:
        SlowingTower(const TextureHolder& textures);

    private:
        void CreateBullet(SceneNode&, const TextureHolder&) const { }
};