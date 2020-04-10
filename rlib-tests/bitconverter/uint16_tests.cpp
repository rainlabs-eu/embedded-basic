#include "rlib/bitconverter.h"


#include <gmock/gmock.h>
#include <vector>

using namespace::testing;

namespace {

struct Uint16TestCase {
    uint16_t number;
    uint8_t msb;
    uint8_t lsb;
};

struct RlibUtilsBitconverterUint16ParamTests:
    public TestWithParam<Uint16TestCase> {
};

INSTANTIATE_TEST_CASE_P(RlibUtilsBitconverterUint16,
                        RlibUtilsBitconverterUint16ParamTests,
                            ::testing::Values(
                            Uint16TestCase { 0x0000, 0x00, 0x00 },
                            Uint16TestCase { 0xFFFF, 0xFF, 0xFF },
                            Uint16TestCase { 0x0102, 0x01, 0x02 },
                            Uint16TestCase { 0x4A3B, 0x4A, 0x3B }
                            )
                        );

TEST_P(RlibUtilsBitconverterUint16ParamTests, CanRetrieveSingleBytesFromNumber) {
    const auto test = GetParam();

    EXPECT_THAT(uint16_t_get_msb(test.number), test.msb);
    EXPECT_THAT(uint16_t_get_lsb(test.number), test.lsb);

}

TEST_P(RlibUtilsBitconverterUint16ParamTests, CanCreateNumberFromSingleBytesTestCases) {
    const auto test = GetParam();
    uint16_t calculated = uint16_t_from_bytes(test.msb, test.lsb);
    EXPECT_THAT(calculated, test.number);

}

TEST_P(RlibUtilsBitconverterUint16ParamTests, CanCreateNumberFromBigEndianArray) {
    const auto test = GetParam();

    uint8_t big_endian_representation[2] = { test.msb, test.lsb };

    EXPECT_THAT(uint16_t_from_be_table(big_endian_representation), test.number);
}

TEST_P(RlibUtilsBitconverterUint16ParamTests, CanCreateNumberFromLittleEndianArray) {
    const auto test = GetParam();

    uint8_t little_endian_representation[2] = { test.lsb, test.msb };

    EXPECT_THAT(uint16_t_from_le_table(little_endian_representation), test.number);
}

} //end namespace
