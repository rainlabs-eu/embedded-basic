#pragma once
#include "detail/placement_new_storage_base.h"

namespace rlib {
template <class T>
class PlacementNewStore {
  private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type m_data;

    detail::PlacementNewStorageBase m_storage_base;

  public:
    template <typename... CtorParamsType>
    T* Create(CtorParamsType... ctor_params);

    T* Get();

    void Destroy();

    ~PlacementNewStore();
};

template <class T>
template <typename... CtorParamsType>
inline T* PlacementNewStore<T>::Create(CtorParamsType... ctor_params) {
    static_assert(std::is_constructible<T, CtorParamsType...>::value,
                  "Underlying object's constructor parameter types must match this type's template parameters");
    m_storage_base.AssertIsInvalid();
    auto* ptr = new (&m_data) T(ctor_params...);
    m_storage_base.SetValid(ptr);
    return Get();
}

template <class T>
inline void PlacementNewStore<T>::Destroy() {
    T* valid = Get();
    valid->~T();
    m_storage_base.Invalidate();
}

template <class T>
inline PlacementNewStore<T>::~PlacementNewStore() {
    if (m_storage_base.IsValid()) {
        Destroy();
    }
}

template <class T>
inline T* PlacementNewStore<T>::Get() {
    return reinterpret_cast<T*>(m_storage_base.GetValid());
}

}  // namespace rlib
