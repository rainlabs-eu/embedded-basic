#include "rlib/crc16.h"

#include <gmock/gmock.h>

struct Crc16TestCase {
    std::vector<uint8_t> data;
    uint16_t crc;
};

struct Crc16ModbusParamTests : public ::testing::TestWithParam<Crc16TestCase> {};

INSTANTIATE_TEST_SUITE_P(Crc16ModbusSampleVectors,
                         Crc16ModbusParamTests,
                         ::testing::Values(Crc16TestCase{{0x12, 0x34, 0x56, 0x70}, 0xD67A},
                                           Crc16TestCase{{0x5A, 0x26, 0x19, 0x77}, 0x81B8}));

TEST_P(Crc16ModbusParamTests, CalculatesOkFromWholeData) {
    const auto test = GetParam();
    EXPECT_THAT(rlib::crc16_modbus(test.data.data(), test.data.size()), test.crc);
}

TEST_P(Crc16ModbusParamTests, CalculatesOkWithFirst3BytesSkipped) {
    const auto test = GetParam();
    if (test.data.size() > 3) {
        auto crc3 = rlib::crc16_modbus(test.data.data(), 3);
        auto crc_all = rlib::crc16_modbus(test.data.data() + 3, test.data.size() - 3, crc3);
        EXPECT_THAT(crc_all, test.crc);
    }
}
