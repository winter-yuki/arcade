#include "field.hpp"


void Field::addEntity(EntityP e)
{
    es_.push_back(e);
}


void Field::rmEntity(EntityP e)
{
    es_.erase(std::remove(es_.begin(), es_.end(), e), es_.end());
}


std::vector<EntityP> & Field::entities()
{
    return es_;
}


std::vector<EntityP> const & Field::entities() const
{
    return es_;
}
