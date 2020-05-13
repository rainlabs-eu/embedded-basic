#include "rlib/placement_new_polymorphic_store.h"
#include "rlib/placement_new_typed_store.h"
#include "rlib/placement_new_universal_store.h"

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

struct PlacementNewTypedStoreTest : public ::testing::Test {
    rlib::PlacementNewTypedStore<A> store_a;
};

TEST_F(PlacementNewTypedStoreTest, SizeOverheadIsOnePtr) {
    EXPECT_THAT(sizeof(store_a), ::testing::Eq(sizeof(A) + sizeof(void*)));
}

TEST_F(PlacementNewTypedStoreTest, CanBeInstantiated) {
    auto* a = store_a.Create();
    store_a.Destroy();
}

TEST_F(PlacementNewTypedStoreTest, CannotBeInstantiatedTwiceWithoutDestroy) {
    auto* a = store_a.Create();

    EXPECT_DEATH_IF_SUPPORTED(store_a.Create(), "");

    store_a.Destroy();

    auto a_again = store_a.Create();
}

struct PlacementNewPolymorphicStoreTest : public ::testing::Test {
    rlib::PlacementNewPolymorphicStore<A, B, C> store_poly;
};

TEST_F(PlacementNewPolymorphicStoreTest, CanBeInstantiatedChildB) {
    auto b = store_poly.Create<B>();

    EXPECT_DEATH_IF_SUPPORTED(store_poly.Create<C>(), "");
    store_poly.Destroy();
}

TEST_F(PlacementNewPolymorphicStoreTest, CanBeInstantiatedChildC) {
    auto c = store_poly.Create<C>();
    store_poly.Destroy();
}

TEST_F(PlacementNewPolymorphicStoreTest, CannotMixTypesWithoutDestroy) {
    auto b = store_poly.Create<B>();

    EXPECT_DEATH_IF_SUPPORTED(store_poly.Create<C>(), "");
    store_poly.Destroy();

    auto c = store_poly.Create<C>();
}

struct PlacementNewUniversalStoreTest : public ::testing::Test {
    rlib::PlacementNewUniversalStore<sizeof(A), alignof(A)> store_uni;
};

TEST_F(PlacementNewUniversalStoreTest, CanBeInstantiatedWithCorrectSizeButOnlyOnce) {
    auto* a = store_uni.Create<A>();
    EXPECT_DEATH_IF_SUPPORTED(store_uni.Create<A>(), "");
    store_uni.Destroy(a);
}

TEST_F(PlacementNewUniversalStoreTest, SecondDestroyFails) {
    auto* a = store_uni.Create<A>();
    store_uni.Destroy(a);
    EXPECT_DEATH_IF_SUPPORTED(store_uni.Destroy(a), "");
}

TEST_F(PlacementNewUniversalStoreTest, CanBeReused) {
    auto* a = store_uni.Create<A>();
    store_uni.Destroy(a);
    auto* a_again = store_uni.Create<A>();
    store_uni.Destroy(a_again);
}
