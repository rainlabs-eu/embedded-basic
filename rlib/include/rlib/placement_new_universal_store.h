#pragma once

#include <cstddef>
#include <utility>

#include "detail/placement_new_instance_storage.h"

namespace rlib {

/*!
 * Handles memory storage for creating objects of arbitrary type.
 *
 * Since it is not even aware of object type, its user responsibility
 * to maintain actual ownership of created object.
 *
 * It still prevents memory reuse and use after destroy scenarios.
 */
template <size_t size, size_t alignment = alignof(max_align_t)>
class PlacementNewUniversalStore {
  public:
    ~PlacementNewUniversalStore() = default;

    template <class T, typename... CtorParamsType>
    T* Create(CtorParamsType&&... ctor_params);

    template <class T>
    void Destroy(T* valid);

  private:
    typename std::aligned_storage<size, alignment>::type buffer_;
    detail::PlacementNewInstanceStorage instance_storage_;
};

template <size_t size, size_t alignment>
template <class T, typename... CtorParamsType>
T* PlacementNewUniversalStore<size, alignment>::Create(CtorParamsType&&... ctor_params) {
    static_assert(std::is_constructible<T, CtorParamsType...>::value,
                  "Underlying object's constructor parameter types must match this type's template parameters");
    static_assert(sizeof(T) <= size, "Type doesn't fit into buffer_");

    instance_storage_.AssertIsInvalid();
    auto* ptr = new (&buffer_) T(std::forward<CtorParamsType>(ctor_params)...);
    instance_storage_.SetValid(ptr);
    return ptr;
}

template <size_t size, size_t alignment>
template <class T>
void PlacementNewUniversalStore<size, alignment>::Destroy(T* valid) {
    instance_storage_.AssertIsValid();
    valid->~T();
    instance_storage_.Invalidate();
}
}  // namespace rlib
