#pragma once
#include "detail/placement_new_storage_base.h"

namespace rlib {

/*!
 * Handles memory storage for creating objects of single type T
 *
 * Object of this class *maintains actual ownership*, and its API enforces
 * correct sequence of use (Create, NxGet, Destroy).
 */
template <class T>
class PlacementNewTypedStore {
  private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type m_data;

    detail::PlacementNewStorageBase storage_;

  public:
    template <typename... CtorParamsType>
    T* Create(CtorParamsType... ctor_params);

    T* Get();

    void Destroy();

    ~PlacementNewTypedStore();
};

template <class T>
template <typename... CtorParamsType>
inline T* PlacementNewTypedStore<T>::Create(CtorParamsType... ctor_params) {
    static_assert(std::is_constructible<T, CtorParamsType...>::value,
                  "Underlying object's constructor parameter types must match this type's template parameters");
    storage_.AssertIsInvalid();
    auto* ptr = new (&m_data) T(ctor_params...);
    storage_.SetValid(ptr);
    return Get();
}

template <class T>
inline void PlacementNewTypedStore<T>::Destroy() {
    T* valid = Get();
    valid->~T();
    storage_.Invalidate();
}

template <class T>
inline PlacementNewTypedStore<T>::~PlacementNewTypedStore() {
    if (storage_.IsValid()) {
        Destroy();
    }
}

template <class T>
inline T* PlacementNewTypedStore<T>::Get() {
    return reinterpret_cast<T*>(storage_.GetValid());
}

}  // namespace rlib
