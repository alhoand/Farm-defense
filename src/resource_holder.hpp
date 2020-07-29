#include <map>
#include <memory>
#include <string>
#include <exception>
#pragma once

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    void Load(Identifier id, const std::string& filename);
    template <typename Parameter>
    void Load(Identifier id, const std::string& filename, const Parameter &secondParam);
    Resource& Get(Identifier id);
    const Resource& Get(Identifier id) const;
private:
    void InsertResource(Identifier id, std::unique_ptr<Resource> ptr);
    std::map<Identifier, std::unique_ptr<Resource> > resourceMap_;
};


#include "resource_holder.inl"