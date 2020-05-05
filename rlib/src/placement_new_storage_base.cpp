#include "placement_new_storage_base.h"

#include <cassert>

void rlib::detail::PlacementNewStorageBase::SetValid(void* constructed) {
    assert(constructed_ == nullptr);
    assert(constructed != nullptr);

    constructed_ = constructed;
}

void rlib::detail::PlacementNewStorageBase::Invalidate() {
    constructed_ = nullptr;
}

void* rlib::detail::PlacementNewStorageBase::GetValid() const {
    assert(IsValid());
    return constructed_;
}

void rlib::detail::PlacementNewStorageBase::AssertIsInvalid() {
    assert(constructed_ == nullptr);
}

bool rlib::detail::PlacementNewStorageBase::IsValid() const {
    return constructed_ != nullptr;
}
