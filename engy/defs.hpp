#pragma once

#define ENGY_CREATABLE(type) \
    template <class T, class... Args> \
    friend T * type::create(Args && ...args);
#define ENGY_HEAP_ONLY_CONSTRUCTIBLE protected
