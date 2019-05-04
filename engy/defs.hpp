#pragma once

#define ENGY_CREATABLE(type) \
    template <class C, class... Args> \
    friend C * type::create(Args && ...args);

#define ENGY_HEAP_ONLY_CONSTRUCTIBLE protected
