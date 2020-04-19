#include "rlib/bitconverter.h"

#include <gmock/gmock.h>
#include <cfloat>
#include <cmath>
#include <vector>

using namespace ::testing;

namespace {

struct FloatTestCase {
    float expected_float_value;

    uint8_t mmsb;
    uint8_t mlsb;
    uint8_t lmsb;
    uint8_t llsb;
};

struct RlibUtilsBitconverterFloatParamTests : public TestWithParam<FloatTestCase> {};

TEST_P(RlibUtilsBitconverterFloatParamTests, CanCreateNumberFromSingleBytesTestCases) {
    const auto test = GetParam();

    float result = float_from_bytes(test.mmsb, test.mlsb, test.lmsb, test.llsb);

    EXPECT_THAT(result, FloatEq(test.expected_float_value));
}

TEST_P(RlibUtilsBitconverterFloatParamTests, CanCreateNumberFromBigEndianArray) {
    const auto test = GetParam();
    uint8_t big_endian_representation[4] = {test.mmsb, test.mlsb, test.lmsb, test.llsb};

    float result = float_from_be_table(big_endian_representation);

    EXPECT_THAT(result, FloatEq(test.expected_float_value));
}

INSTANTIATE_TEST_SUITE_P(RlibUtilsBitconverterFloat,
                         RlibUtilsBitconverterFloatParamTests,
                         ::testing::Values(FloatTestCase{FLT_MAX, 0x7F, 0x7F, 0xFF, 0xFF},
                                           FloatTestCase{FLT_MIN, 0x00, 0x80, 0x00, 0x00},
                                           FloatTestCase{FLT_EPSILON, 0x34, 0x00, 0x00, 0x00},
                                           FloatTestCase{3.14159265358979323846, 0x40, 0x49, 0x0F, 0xDB}));

}  // end namespace
