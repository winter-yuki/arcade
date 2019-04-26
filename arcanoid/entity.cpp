#include "entity.hpp"


void Entity::addComponent(Component * component)
{
    components_.insert({component->getId(), component});
}


void Entity::removeComponent(Component * component)
{
    components_.erase(component->getId());
}


std::optional<Component *> Entity::findComponent(Component::Id id)
{
    auto it = components_.find(id);
    if (it != components_.end()) {
        return { it->second };
    }
    return std::nullopt;
}
