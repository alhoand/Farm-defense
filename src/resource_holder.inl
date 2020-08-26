#include <cassert>
#include <iostream>
template <class Resource, class Identifier>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename) {
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("Failing to load file " + filename);
    }
    InsertResource(id, std::move(resource));

}

template <class Resource, class Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename, const Parameter &secondParam) {
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, secondParam)) {
        throw std::runtime_error("Failing to load file " + filename);
    }
    InsertResource(id, std::move(resource));
}

template <class Resource, class Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id) {
    auto found = resourceMap_.find(id);
    assert(found != resourceMap_.end());
    //std::cout << "Got a resource" << std::endl;
    return *found->second;
}


template <class Resource, class Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id) const {
    auto found = resourceMap_.find(id);
    assert(found != resourceMap_.end());
    return *found->second;
}

template <class Resource, class Identifier>
void ResourceHolder<Resource, Identifier>::InsertResource(Identifier id, std::unique_ptr<Resource> ptr) {
    auto inserted = resourceMap_.insert(std::make_pair(id, std::move(ptr)));
    assert(inserted.second);
    //std::cout << "Loaded a resource " << std::endl;
}