#include "rlib/bitconverter.h"

#include <gmock/gmock.h>
#include <array>

using namespace ::testing;

namespace {

struct Uint64TestCase {
    uint64_t number;
    std::array<uint8_t, 9> expected_be_range;
    std::size_t bytes_to_write;
};

struct RlibUtilsUint64ToBeRangeParamsTests : public TestWithParam<Uint64TestCase> {};

INSTANTIATE_TEST_SUITE_P(
        RlibUtilsUint64ToBeRange,
        RlibUtilsUint64ToBeRangeParamsTests,
        ::testing::Values(
                Uint64TestCase{0xFFFFFFFFFFFFFFFF, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 0},
                Uint64TestCase{0x0807060504030201, {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1},
                Uint64TestCase{0x0807060504030201, {0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 2},
                Uint64TestCase{0x0807060504030201, {0x00, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01}, 9}));

TEST_P(RlibUtilsUint64ToBeRangeParamsTests, ConvertsUint64ToRangeOfBytes) {
    const auto test = GetParam();
    std::array<uint8_t, 9> actual{0};
    uint64_t_to_be_range(test.number, &actual[0], test.bytes_to_write);
    EXPECT_THAT(actual, test.expected_be_range);
}

}  // namespace
