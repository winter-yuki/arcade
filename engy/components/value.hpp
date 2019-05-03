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
template <class C, class ValueType>
class Value
        : public ComponentC<C> {
public:
    using value_type = ValueType;

    void setVal(ValueType val);
    ValueType val() const;

protected:
    explicit Value(ValueType val);

private:
    ValueType val_;
};


template <class C, class ValueType>
Value<C, ValueType>::Value(ValueType val)
    : val_(std::move(val))
{}


template <class C, class ValueType>
void Value<C, ValueType>::setVal(ValueType val) {
    val_ = std::move(val);
}


template <class C, class ValueType>
ValueType Value<C, ValueType>::val() const {
    return val_;
}

} // Engy


















