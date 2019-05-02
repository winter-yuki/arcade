/**
  * @file
  */

#pragma once

#include "entity.hpp"


namespace Engy
{

/**
 * @ingroup core
 * @brief Registry of tangible items.
 *
 * It is needed because we want to get whole entity which our entity
 * collided with, so we cannot use QGraphicsScene::collidingItems.
 */
class Field final {
public:
    void addEntity(EntityW e);
    void rmEntity (EntityW e);

    /**
     * @brief filter Removes all deleted entities
     */
    void filter();

    std::vector<EntityW> & entities();
    std::vector<EntityW> const & entities() const;

private:
    std::vector<EntityW> es_;
};


using FieldS = std::shared_ptr<Field>;
inline FieldS makeField() {
    return std::make_shared<Field>();
}

} // Engy
