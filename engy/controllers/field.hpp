#pragma once

#include "entity.hpp"


class Field final {
public:
    void addEntity(EntityW e);
    void rmEntity (EntityW e);

    // Removes all deleted entities
    void filter();

    std::vector<EntityW> & entities();
    std::vector<EntityW> const & entities() const;

private:
    std::vector<EntityW> es_;
};


using FieldP = std::shared_ptr<Field>;
inline FieldP makeField() {
    return std::make_shared<Field>();
}
