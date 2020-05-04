#pragma once
#include <stdint.h>
#include <new>
#include <type_traits>

namespace rlib {

namespace detail {

/*!
 * Class for holding placement new allocation results
 * needed mostly to avoid bloat if all asserts are located in template code
 */
class PlacementNewStorageBase {
  private:
    void* m_constructed;

  public:
    PlacementNewStorageBase() : m_constructed(nullptr) {}

    void AssertIsInvalid();
    void SetValid(void* constructed);
    void Invalidate();

    void* GetValid() const;
    bool IsValid() const;
};

}  // namespace detail
}  // namespace rlib
