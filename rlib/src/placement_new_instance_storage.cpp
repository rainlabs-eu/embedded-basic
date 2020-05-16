#include "placement_new_instance_storage.h"

#include <cassert>

void rlib::detail::PlacementNewInstanceStorage::SetValid(void* constructed) {
    assert(constructed_ == nullptr);
    assert(constructed != nullptr);

    constructed_ = constructed;
}

void rlib::detail::PlacementNewInstanceStorage::Invalidate() {
    constructed_ = nullptr;
}

void* rlib::detail::PlacementNewInstanceStorage::GetValid() const {
    assert(IsValid());
    return constructed_;
}

void rlib::detail::PlacementNewInstanceStorage::AssertIsInvalid() {
    assert(constructed_ == nullptr);
}

void rlib::detail::PlacementNewInstanceStorage::AssertIsValid() {
    assert(constructed_ != nullptr);
}

bool rlib::detail::PlacementNewInstanceStorage::IsValid() const {
    return constructed_ != nullptr;
}
