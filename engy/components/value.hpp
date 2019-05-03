/**
  * @file
  */

#pragma once

#include "component.hpp"


namespace Engy
{

/**
 * @ingroup component
 * @brief The Mass class
 */
template <class T>
class Value
        : public Component {
public:
    using value_type = T;

    void setVal(T val);
    T val() const;

protected:
    Value(Id id, T val);

private:
    T val_;
};


template <class T>
Value<T>::Value(Id id, T val)
    : Component(id)
    , val_(std::move(val))
{}


template <class T>
void Value<T>::setVal(T val) {
    val_ = std::move(val);
}


template <class T>
T Value<T>::val() const {
    return val_;
}

} // Engy


















