#include "rlib/crc16.h"

#include <gmock/gmock.h>
#include <algorithm>
#include <boost/crc.hpp>
#include <climits>
#include <functional>
#include <random>
#include <vector>

using crc_modbus_type = boost::crc_optimal<16, 0x8005, 0xFFFF, 0, true, true>;

#define CRC_TEST_TYPE(name, function_name, boost_specialization_name)                                    \
    struct name : public ::testing::Test {                                                               \
        using result_type = uint16_t;                                                                    \
        using boost_specialization = boost_specialization_name;                                          \
        static result_type Calc(const void* data, size_t len) { return rlib::function_name(data, len); } \
        static result_type Calc(const void* data, size_t len, result_type initial) {                     \
            return rlib::function_name(data, len, initial);                                              \
        }                                                                                                \
    }

CRC_TEST_TYPE(Crc16Modbus, crc16_modbus, crc_modbus_type);
CRC_TEST_TYPE(Crc16CcittFfff, crc16_ccitt_ffff, boost::crc_ccitt_type);

template <typename CrcXxx>
struct CrcGenericTest : public ::testing::Test {
    void CalcCompleteAndCompare(std::vector<uint8_t> array) {
        auto result = CrcXxx::Calc(array.data(), array.size());
        typename CrcXxx::boost_specialization bcrc;
        bcrc.process_bytes(array.data(), array.size());
        EXPECT_THAT(result, ::testing::Eq(bcrc.checksum()));
    }
};

using CrcTypes = ::testing::Types<Crc16Modbus, Crc16CcittFfff>;
TYPED_TEST_SUITE(CrcGenericTest, CrcTypes);

TYPED_TEST(CrcGenericTest, Compiles) {}

TYPED_TEST(CrcGenericTest, CalculatesOkForZeroOrOneBytes) {
    this->CalcCompleteAndCompare({});
    this->CalcCompleteAndCompare({0x00});
}

TYPED_TEST(CrcGenericTest, CalculatesOkForRandom512) {
    using random_bytes_engine = std::independent_bits_engine<std::default_random_engine, CHAR_BIT, uint8_t>;
    random_bytes_engine rbe;
    std::vector<uint8_t> data(512);
    std::generate(begin(data), end(data), std::ref(rbe));

    this->CalcCompleteAndCompare(data);
}
