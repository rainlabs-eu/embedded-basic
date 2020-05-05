#pragma once
#include "detail/placement_new_storage_base.h"

#include <cstddef>
#include <type_traits>

namespace rlib {

namespace detail {
template <typename Head>
constexpr size_t max_sizeof() {
    return sizeof(Head);
}

template <typename Head, typename Next, typename... Tail>
constexpr size_t max_sizeof() {
    return max_sizeof<Head>() > max_sizeof<Next, Tail...>() ? max_sizeof<Head>() : max_sizeof<Next, Tail...>();
}

template <typename Head>
constexpr size_t max_alignof() {
    return alignof(Head);
}

template <typename Head, typename Next, typename... Tail>
constexpr size_t max_alignof() {
    return max_alignof<Head>() > max_alignof<Next, Tail...>() ? max_alignof<Head>() : max_alignof<Next, Tail...>();
}

template <typename Type>
constexpr bool is_within_list() {
    return false;
}

template <typename Type, typename ListHead, typename... TypesTail>
constexpr bool is_within_list() {
    return std::is_same<Type, ListHead>::value or is_within_list<Type, TypesTail...>();
}

template <typename Base>
constexpr bool are_children_of() {
    return true;
}

template <typename Base, typename FirstChild, typename... OtherChildren>
constexpr bool are_children_of() {
    return std::is_base_of<Base, FirstChild>::value and are_children_of<Base, OtherChildren...>();
}

}  // namespace detail

template <class BaseType, class... AllowedChildTypes>
class PlacementNewPolymorphicStore {
    static_assert(detail::are_children_of<BaseType, AllowedChildTypes...>(), "");

  private:
    typename std::aligned_storage<detail::max_sizeof<AllowedChildTypes...>(),
                                  detail::max_alignof<AllowedChildTypes...>()>::type m_data;

    detail::PlacementNewStorageBase m_storage_base;

  public:
    template <typename ChildType, typename... CtorParamsType>
    ChildType* Create(CtorParamsType... ctor_params);

    void Destroy();

    BaseType* get();

    ~PlacementNewPolymorphicStore();
};

template <class BaseType, class... AllowedChildTypes>
template <typename ChildType, typename... CtorParamsType>
inline ChildType* PlacementNewPolymorphicStore<BaseType, AllowedChildTypes...>::Create(CtorParamsType... ctor_params) {
    static_assert(detail::is_within_list<ChildType, AllowedChildTypes...>(),
                  "Created type must be one of allowed child types");
    m_storage_base.AssertIsInvalid();

    ChildType* ptr = new (&m_data) ChildType(ctor_params...);
    BaseType* base = ptr;
    m_storage_base.SetValid(base);

    return ptr;
}

template <class BaseType, class... AllowedChildTypes>
inline void PlacementNewPolymorphicStore<BaseType, AllowedChildTypes...>::Destroy() {
    BaseType* valid = get();
    valid->~BaseType();
    m_storage_base.Invalidate();
}

template <class BaseType, class... AllowedChildTypes>
inline BaseType* PlacementNewPolymorphicStore<BaseType, AllowedChildTypes...>::get() {
    return reinterpret_cast<BaseType*>(m_storage_base.GetValid());
}

template <class BaseType, class... AllowedChildTypes>
inline PlacementNewPolymorphicStore<BaseType, AllowedChildTypes...>::~PlacementNewPolymorphicStore() {
    if (m_storage_base.IsValid()) {
        Destroy();
    }
}

}  // namespace rlib
