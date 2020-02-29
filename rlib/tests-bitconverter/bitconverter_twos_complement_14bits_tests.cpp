#include "rlib/types/types.h"
#include "rlib/utils/math/modulo_index.hpp"
#include <cfloat>
#include <gmock/gmock.h>
#include <cmath>
#include <cstdint>
#include <vector>

using namespace::testing;

namespace {

struct TwosComplement14BitsTestCase {
    int16_t expected;
    uint16_t input_value;
};

struct RlibUtilsBitconverterTwosComplement14BitsParamTests:
    public TestWithParam<TwosComplement14BitsTestCase> {
};

INSTANTIATE_TEST_CASE_P(RlibUtilsBitconverterTwosComplement14Bits,
                        RlibUtilsBitconverterTwosComplement14BitsParamTests,
                            ::testing::Values(
                            TwosComplement14BitsTestCase { 0, 0 },
                            TwosComplement14BitsTestCase { 1, 1 },
                            TwosComplement14BitsTestCase { -1, 0x3FFF },
                            TwosComplement14BitsTestCase { -8192, 0x2000 },
                            TwosComplement14BitsTestCase { 8191, 0x1FFF }
                            )
                        );

TEST_P(RlibUtilsBitconverterTwosComplement14BitsParamTests, ValidConversionResult) {
    const auto test = GetParam();

    int16_t result = twos_complement_from_raw_14bits(test.input_value);

    EXPECT_THAT(result, test.expected);
}

} //end namespace
