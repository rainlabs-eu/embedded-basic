#include "rlib/types/types.h"
#include "rlib/utils/math/modulo_index.hpp"
#include <cfloat>
#include <gmock/gmock.h>
#include <cmath>
#include <cstdint>
#include <vector>

using namespace::testing;

namespace  {

struct DoubleTestCase {
    double expected_double_value;

    uint8_t mmmmsb;
    uint8_t mmmlsb;
    uint8_t mmllsb;
    uint8_t mlllsb;
    uint8_t lmmmsb;
    uint8_t llmmsb;
    uint8_t lllmsb;
    uint8_t llllsb;
};

struct RlibUtilsBitconverterDoubleParamTests:
    public TestWithParam<DoubleTestCase> {
};

TEST_P(RlibUtilsBitconverterDoubleParamTests, CanCreateNumberFromSingleBytesTestCases) {
    const auto test = GetParam();

    double result = double_from_bytes(test.mmmmsb,
                                      test.mmmlsb,
                                      test.mmllsb,
                                      test.mlllsb,
                                      test.lmmmsb,
                                      test.llmmsb,
                                      test.lllmsb,
                                      test.llllsb);

    EXPECT_THAT(result, DoubleEq(test.expected_double_value));

}

TEST_P(RlibUtilsBitconverterDoubleParamTests, CanCreateNumberFromBytesArrayFromBigEndian) {
    const auto test = GetParam();
    uint8_t big_endian_representation[8] = {
        test.mmmmsb,
        test.mmmlsb,
        test.mmllsb,
        test.mlllsb,
        test.lmmmsb,
        test.llmmsb,
        test.lllmsb,
        test.llllsb
    };

    double result = double_from_be_table(big_endian_representation);
    EXPECT_THAT(result, DoubleEq(test.expected_double_value));
}

INSTANTIATE_TEST_CASE_P(RlibUtilsBitconverterDouble,
                        RlibUtilsBitconverterDoubleParamTests,
                            ::testing::Values(
                            DoubleTestCase { DBL_MAX,
                                             0x7F, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
                            DoubleTestCase { DBL_MIN,
                                             0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                            DoubleTestCase { DBL_EPSILON,
                                             0x3C, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                            DoubleTestCase { 1.0,
                                             0x3F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                            DoubleTestCase { 0.002255989192054412,
                                             0x3F, 0x62, 0x7B, 0x26, 0xF9, 0x99, 0xA0, 0x3C },
                            DoubleTestCase { -0.888440489330618,
                                             0xBF, 0xEC, 0x6E, 0x1A, 0xBF, 0xC3, 0xC0, 0x6D }
                            )
                        );

} //end namespace
