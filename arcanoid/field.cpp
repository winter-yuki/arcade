#include "field.hpp"

#include "stdafx.hpp"


void Field::addEntity(EntityW e)
{
    es_.push_back(e);
}


void Field::rmEntity(EntityW e)
{
    auto cmp = [e](const EntityW x) {
        auto pe = e.lock();
        auto px = x.lock();
        if (pe && px && pe == px) {
            return true;
        }
        return false;
    };

    es_.erase(std::remove_if(es_.begin(), es_.end(), cmp), es_.end());
}


void Field::filter()
{
    using namespace std::placeholders;
    es_.erase(remove_if(es_.begin(), es_.end(),
                        std::bind(&EntityW::expired, _1)), es_.end());
}


std::vector<EntityW> & Field::entities()
{
    return es_;
}


std::vector<EntityW> const & Field::entities() const
{
    return es_;
}








