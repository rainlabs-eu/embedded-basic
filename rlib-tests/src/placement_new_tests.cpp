#include "rlib/placement_new_polymorphic_store.h"
#include "rlib/placement_new_store.h"

#include <gmock/gmock.h>
#include <array>

struct A {
    std::array<uint8_t, 16> data;
};

struct B : public A {
    std::array<uint8_t, 16> data;
};

struct C : public B {
    std::array<uint8_t, 16> data;
};

struct PlacementStore : public ::testing::Test {
    rlib::PlacementNewStore<A> store_a;
};

TEST_F(PlacementStore, SizeOverheadIsOnePtr) {
    EXPECT_THAT(sizeof(store_a), ::testing::Eq(sizeof(A) + sizeof(void*)));
}

TEST_F(PlacementStore, CanBeInstantiated) {
    auto* a = store_a.Create();
    store_a.Destroy();
}

TEST_F(PlacementStore, CannotBeInstantiatedTwiceWithoutDestroy) {
    auto* a = store_a.Create();

    EXPECT_DEATH_IF_SUPPORTED(store_a.Create(), "");

    store_a.Destroy();

    auto a_again = store_a.Create();
}

struct PlacementStorePolymorphic : public ::testing::Test {
    rlib::PlacementNewPolymorphicStore<A, B, C> store_poly;
};

TEST_F(PlacementStorePolymorphic, CanBeInstantiatedChildB) {
    auto b = store_poly.Create<B>();

    EXPECT_DEATH_IF_SUPPORTED(store_poly.Create<C>(), "");
    store_poly.Destroy();
}

TEST_F(PlacementStorePolymorphic, CanBeInstantiatedChildC) {
    auto c = store_poly.Create<C>();
    store_poly.Destroy();
}

TEST_F(PlacementStorePolymorphic, CannotMixTypesWithoutDestroy) {
    auto b = store_poly.Create<B>();

    EXPECT_DEATH_IF_SUPPORTED(store_poly.Create<C>(), "");
    store_poly.Destroy();

    auto c = store_poly.Create<C>();
}
