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

/*!
 * Handles memory storage for creating objects of types inheriting BaseType,
 * Excplicitely listed as possible variants.
 *
 * Object of this class *maintains actual ownership*, and its API enforces
 * correct sequence of use (Create, NxGet, Destroy).
 */
template <class BaseType, class... AllowedChildTypes>
class PlacementNewPolymorphicStore {
    static_assert(detail::are_children_of<BaseType, AllowedChildTypes...>(), "");

  private:
    typename std::aligned_storage<detail::max_sizeof<AllowedChildTypes...>(),
                                  detail::max_alignof<AllowedChildTypes...>()>::type data_;

    detail::PlacementNewStorageBase storage_;

  public:
    template <typename ChildType, typename... CtorParamsType>
    ChildType* Create(CtorParamsType... ctor_params);

    void Destroy();

    BaseType* Get();

    ~PlacementNewPolymorphicStore();
};

template <class BaseType, class... AllowedChildTypes>
template <typename ChildType, typename... CtorParamsType>
inline ChildType* PlacementNewPolymorphicStore<BaseType, AllowedChildTypes...>::Create(CtorParamsType... ctor_params) {
    static_assert(detail::is_within_list<ChildType, AllowedChildTypes...>(),
                  "Created type must be one of allowed child types");
    storage_.AssertIsInvalid();

    ChildType* ptr = new (&data_) ChildType(ctor_params...);
    BaseType* base = ptr;
    storage_.SetValid(base);

    return ptr;
}

template <class BaseType, class... AllowedChildTypes>
inline void PlacementNewPolymorphicStore<BaseType, AllowedChildTypes...>::Destroy() {
    BaseType* valid = Get();
    valid->~BaseType();
    storage_.Invalidate();
}

template <class BaseType, class... AllowedChildTypes>
inline BaseType* PlacementNewPolymorphicStore<BaseType, AllowedChildTypes...>::Get() {
    return reinterpret_cast<BaseType*>(storage_.GetValid());
}

template <class BaseType, class... AllowedChildTypes>
inline PlacementNewPolymorphicStore<BaseType, AllowedChildTypes...>::~PlacementNewPolymorphicStore() {
    if (storage_.IsValid()) {
        Destroy();
    }
}

}  // namespace rlib
