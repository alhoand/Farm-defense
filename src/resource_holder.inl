#include <resource_holder.hpp>

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
	std::unique_ptr<Resource> texture(new Resource());
    if (!texture->loadFromFile(filename)) {
        throw std::runtime_error("ResourceMap::load - Failed to load " + filename);
    }
	auto inserted = resourceMap_.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam)) {
        throw std::runtime_error("ResourceMap::load - Failed to load " + filename);
    }
	auto inserted = resourceMap_.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
	auto found = resourceMap_.find(id);
    assert(found != resourceMap_.end());
	return *found->second;
}