#include "placement_new_storage_base.h"

#include <cassert>

void rlib::detail::PlacementNewStorageBase::SetValid(void* constructed) {
    assert(m_constructed == nullptr);
    assert(constructed != nullptr);

    m_constructed = constructed;
}

void rlib::detail::PlacementNewStorageBase::Invalidate() {
    m_constructed = nullptr;
}

void* rlib::detail::PlacementNewStorageBase::GetValid() const {
    assert(IsValid());
    return m_constructed;
}

void rlib::detail::PlacementNewStorageBase::AssertIsInvalid() {
    assert(m_constructed == nullptr);
}

bool rlib::detail::PlacementNewStorageBase::IsValid() const {
    return m_constructed != nullptr;
}
