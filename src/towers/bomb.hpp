#include "../entity.hpp"

class Bomb : publiv Entity {
    public:
        Bomb(const TextureHolder& textures, float speed, int damage, int damageDuration);

    private:
        float distance_;            // how far will the bomb go?
        float speed_;               // how fast will it reach its destination
        float range_;               // the range within which enemies will be hit
        int damage_;                // damage inflicted on enemies
}