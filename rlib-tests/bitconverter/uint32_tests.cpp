#include "rlib/bitconverter.h"

#include <gmock/gmock.h>
#include <vector>

using namespace ::testing;

namespace {

struct Uint32TestCase {
    uint32_t number;
    uint8_t mmsb;
    uint8_t mlsb;
    uint8_t lmsb;
    uint8_t llsb;
};

struct RlibUtilsBitconverterUint32ParamTests : public TestWithParam<Uint32TestCase> {};

INSTANTIATE_TEST_CASE_P(RlibUtilsBitconverterUint32,
                        RlibUtilsBitconverterUint32ParamTests,
                        ::testing::Values(Uint32TestCase{0x00000000, 0x00, 0x00, 0x00, 0x00},
                                          Uint32TestCase{0x01020304, 0x01, 0x02, 0x03, 0x04},
                                          Uint32TestCase{0x4A3B2C1D, 0x4A, 0x3B, 0x2C, 0x1D}));

TEST_P(RlibUtilsBitconverterUint32ParamTests, CanRetrieveSingleBytesFromNumberTestCases) {
    const auto test = GetParam();

    EXPECT_THAT(uint32_t_get_mmsb(test.number), test.mmsb);
    EXPECT_THAT(uint32_t_get_mlsb(test.number), test.mlsb);
    EXPECT_THAT(uint32_t_get_lmsb(test.number), test.lmsb);
    EXPECT_THAT(uint32_t_get_llsb(test.number), test.llsb);
}

TEST_P(RlibUtilsBitconverterUint32ParamTests, CanCreateNumberFromSingleBytesTestCases) {
    const auto test = GetParam();

    uint32_t calculated = uint32_t_from_bytes(test.mmsb, test.mlsb, test.lmsb, test.llsb);

    EXPECT_THAT(calculated, test.number);
}

TEST_P(RlibUtilsBitconverterUint32ParamTests, CanCreateNumberFromBytesBigEndianArray) {
    const auto test = GetParam();

    uint8_t big_endian_representation[4] = {test.mmsb, test.mlsb, test.lmsb, test.llsb};

    EXPECT_EQ(uint32_t_from_be_table(big_endian_representation), test.number);
}
TEST_P(RlibUtilsBitconverterUint32ParamTests, CanCreateNumberFromBytesLittleEndianArray) {
    const auto test = GetParam();

    uint8_t little_endian_representation[4] = {test.llsb, test.lmsb, test.mlsb, test.mmsb};

    EXPECT_THAT(uint32_t_from_le_table(little_endian_representation), test.number);
}

}  // end namespace
