#pragma once

#include "entity.hpp"


class Field final {
public:
    void addEntity(EntityP e);
    void rmEntity (EntityP e);
    std::vector<EntityP> & entities();
    std::vector<EntityP> const & entities() const;

private:
    std::vector<EntityP> es_;
};


using FieldP = std::shared_ptr<Field>;
inline FieldP makeField() {
    return std::make_shared<Field>();
}
