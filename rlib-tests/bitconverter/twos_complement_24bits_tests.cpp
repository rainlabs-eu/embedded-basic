#include "rlib/bitconverter.h"

#include <gmock/gmock.h>
#include <vector>

using namespace ::testing;

namespace {

struct TwosComplement24BitsTestCase {
    int32_t expected;
    uint32_t input_value;
};

struct RlibUtilsBitconverterTwosComplement24BitsParamTests : public TestWithParam<TwosComplement24BitsTestCase> {};

INSTANTIATE_TEST_SUITE_P(RlibUtilsBitconverterTwosComplement24Bits,
                         RlibUtilsBitconverterTwosComplement24BitsParamTests,
                         ::testing::Values(TwosComplement24BitsTestCase{0, 0},
                                           TwosComplement24BitsTestCase{1, 1},
                                           TwosComplement24BitsTestCase{-1, 0xFFFFFF},
                                           TwosComplement24BitsTestCase{-8388608, 0x800000},
                                           TwosComplement24BitsTestCase{8388607, 0x7FFFFF}));

TEST_P(RlibUtilsBitconverterTwosComplement24BitsParamTests, ValidConversionResult) {
    const auto test = GetParam();

    int32_t result = twos_complement_from_raw_24bits(test.input_value);

    EXPECT_THAT(result, test.expected);
}

}  // end namespace
