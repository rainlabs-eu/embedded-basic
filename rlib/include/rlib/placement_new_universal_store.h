#pragma once
#include <cstddef>
#include "detail/placement_new_storage_base.h"

namespace rlib {

/*!
 * Handles memory storage for creating objects of arbitrary type.
 *
 * Since it is not even aware of object type, its user responsibility
 * to maintain actual ownership of created object.
 */
template <size_t size, size_t alignment = alignof(max_align_t)>
class PlacementNewUniversalStore {
  protected:
    typename std::aligned_storage<size, alignment>::type m_data;

    detail::PlacementNewStorageBase storage_;

  public:
    ~PlacementNewUniversalStore() { storage_.AssertIsInvalid(); }

    template <class T, typename... CtorParamsType>
    T* Create(CtorParamsType... ctor_params) {
        static_assert(std::is_constructible<T, CtorParamsType...>::value,
                      "Underlying object's constructor parameter types must match this type's template parameters");

        storage_.AssertIsInvalid();
        auto* ptr = new (&m_data) T(ctor_params...);
        storage_.SetValid(ptr);
        return ptr;
    }

    template <class T>
    void Destroy(T* valid) {
        storage_.AssertIsValid();
        valid->~T();
        storage_.Invalidate();
    }
};

}  // namespace rlib
