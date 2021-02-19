#pragma once
#include "detail/placement_new_instance_storage.h"

namespace rlib {

/*!
 * Handles memory storage for creating objects of single type T
 *
 * Object of this class *maintains actual ownership*, and its API enforces
 * correct sequence of use (Create, Get, Destroy).
 */
template <class T>
class PlacementNewTypedStore {
  public:
    ~PlacementNewTypedStore();

    template <typename... CtorParamsType>
    T* Create(CtorParamsType... ctor_params);
    T* Get() const;
    bool IsValid() const;
    void Destroy();
    T* operator->() const;

  private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type buffer_;

    detail::PlacementNewInstanceStorage instance_storage_;
};

template <class T>
template <typename... CtorParamsType>
inline T* PlacementNewTypedStore<T>::Create(CtorParamsType... ctor_params) {
    static_assert(std::is_constructible<T, CtorParamsType...>::value,
                  "Underlying object's constructor parameter types must match this type's template parameters");
    instance_storage_.AssertIsInvalid();
    auto* ptr = new (&buffer_) T(ctor_params...);
    instance_storage_.SetValid(ptr);
    return Get();
}

template <class T>
inline void PlacementNewTypedStore<T>::Destroy() {
    T* valid = Get();
    valid->~T();
    instance_storage_.Invalidate();
}

template <class T>
inline PlacementNewTypedStore<T>::~PlacementNewTypedStore() {
    if (instance_storage_.IsValid()) {
        Destroy();
    }
}

template <class T>
inline T* PlacementNewTypedStore<T>::Get() const {
    return static_cast<T*>(instance_storage_.GetValid());
}

template <class T>
bool PlacementNewTypedStore<T>::IsValid() const {
    return instance_storage_.IsValid();
}

template <class T>
inline T* PlacementNewTypedStore<T>::operator->() const {
    return Get();
}

}  // namespace rlib
