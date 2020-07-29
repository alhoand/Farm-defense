#include <SFML/Graphics.hpp>

namespace Textures {
	enum ID { Tower, Enemy, Bullet };
}

class TextureHolder {
public:
	void load(Textures::ID id, const std::string& filename);
	sf::Texture& get(Textures::ID id);
	const sf::Texture& get(Textures::ID id) const;

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> textureMap_;
};

void TextureHolder::load(Textures::ID id, const std::string& filename) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(filename)) {
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    }
	auto inserted = textureMap_.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);
}

sf::Texture& TextureHolder::get(Textures::ID id) {
	auto found = textureMap_.find(id);
    assert(found != textureMap_.end());
	return *found->second;
}