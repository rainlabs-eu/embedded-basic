static inline uint8_t uint16_t_get_msb(const uint16_t val) {
    return val >> 8;
}

static inline uint8_t uint16_t_get_lsb(const uint16_t val) {
    return val & 0xFF;
}

static inline uint16_t uint16_t_from_bytes(const uint8_t msb, const uint8_t lsb) {
    return ((uint16_t)msb) << 8 | lsb;
}

static inline uint16_t uint16_t_from_be_table(const uint8_t* betable) {
    return uint16_t_from_bytes(betable[0], betable[1]);
}
static inline void uint16_t_to_be_table(uint16_t value, uint8_t* betable) {
    betable[0] = uint16_t_get_msb(value);
    betable[1] = uint16_t_get_lsb(value);
}
static inline uint16_t uint16_t_from_le_table(const uint8_t* letable) {
    return uint16_t_from_bytes(letable[1], letable[0]);
}

static inline uint8_t uint32_t_get_mmsb(const uint32_t val) {
    return val >> 24;
}

static inline uint8_t uint32_t_get_mlsb(const uint32_t val) {
    return (val >> 16) & 0xFF;
}

static inline uint8_t uint32_t_get_lmsb(const uint32_t val) {
    return (val >> 8) & 0xFF;
}

static inline uint8_t uint32_t_get_llsb(const uint32_t val) {
    return val & 0xFF;
}

static inline uint32_t uint32_t_from_bytes(const uint8_t mmsb,
                                           const uint8_t mlsb,
                                           const uint8_t lmsb,
                                           const uint8_t llsb) {
    return ((uint32_t)mmsb) << 24 | ((uint32_t)mlsb) << 16 | ((uint32_t)lmsb) << 8 | llsb;
}

static inline double double_from_bytes(const uint8_t mmm_sb,
                                       const uint8_t mml_sb,
                                       const uint8_t mlm_sb,
                                       const uint8_t mll_sb,
                                       const uint8_t lmm_sb,
                                       const uint8_t lml_sb,
                                       const uint8_t llm_sb,
                                       const uint8_t lll_sb) {
    union {
        uint64_t u64;
        double dbl;
    } u;

    u.u64 = uint64_from_bytes(mmm_sb, mml_sb, mlm_sb, mll_sb, lmm_sb, lml_sb, llm_sb, lll_sb);

    return u.dbl;
}

static inline float float_from_bytes(const uint8_t mm_sb,
                                     const uint8_t ml_sb,
                                     const uint8_t lm_sb,
                                     const uint8_t ll_sb) {
    union {
        uint32_t u32;
        float flt;
    } u;

    u.u32 = uint32_t_from_bytes(mm_sb, ml_sb, lm_sb, ll_sb);
    return u.flt;
}

static inline uint32_t uint32_t_from_le_table(const uint8_t* letable) {
    return uint32_t_from_bytes(letable[3], letable[2], letable[1], letable[0]);
}

static inline uint32_t uint32_t_from_be_table(const uint8_t* betable) {
    return uint32_t_from_bytes(betable[0], betable[1], betable[2], betable[3]);
}

static inline double double_from_be_table(const uint8_t* betable) {
    return double_from_bytes(
            betable[0], betable[1], betable[2], betable[3], betable[4], betable[5], betable[6], betable[7]);
}

static inline float float_from_be_table(const uint8_t* betable) {
    return float_from_bytes(betable[0], betable[1], betable[2], betable[3]);
}

static inline int32_t twos_complement_from_raw_24bits(uint32_t u2_raw_value) {
    static const uint32_t INT24_MAX = 0x7FFFFF;
    static const uint32_t UINT24_MAX = 0xFFFFFF;

    if (u2_raw_value <= INT24_MAX) {
        return u2_raw_value;
    } else {
        return u2_raw_value - (UINT24_MAX + 1);
    }
}

static inline int16_t twos_complement_from_raw_14bits(uint16_t u2_raw_value) {
    static const uint16_t INT14_MAX = 0x1FFF;
    static const uint16_t UINT14_MAX = 0x3FFF;

    if (u2_raw_value <= INT14_MAX) {
        return u2_raw_value;
    } else {
        return u2_raw_value - (UINT14_MAX + 1);
    }
}

static inline uint32_t uint32_t_from_uint16_t(uint16_t mshw, uint16_t lshw) {
    return ((uint32_t)mshw << 16) | lshw;
}

static inline uint64_t uint64_t_from_be_table(const uint8_t* betable) {
    return uint64_from_bytes(
            betable[0], betable[1], betable[2], betable[3], betable[4], betable[5], betable[6], betable[7]);
}
static inline uint64_t uint64_from_bytes(const uint8_t mmm_sb,
                                         const uint8_t mml_sb,
                                         const uint8_t mlm_sb,
                                         const uint8_t mll_sb,
                                         const uint8_t lmm_sb,
                                         const uint8_t lml_sb,
                                         const uint8_t llm_sb,
                                         const uint8_t lll_sb) {
    uint64_t result = ((uint64_t)mmm_sb) << 56 | ((uint64_t)mml_sb) << 48 | ((uint64_t)mlm_sb) << 40 |
                      ((uint64_t)mll_sb) << 32 | ((uint64_t)lmm_sb) << 24 | ((uint64_t)lml_sb) << 16 |
                      ((uint64_t)llm_sb) << 8 | ((uint64_t)lll_sb);
    return result;
}
static inline void uint64_t_to_be_table(uint64_t value, uint8_t* betable) {
    betable[0] = (value >> 56) & 0xFF;
    betable[1] = (value >> 48) & 0xFF;
    betable[2] = (value >> 40) & 0xFF;
    betable[3] = (value >> 32) & 0xFF;
    betable[4] = (value >> 24) & 0xFF;
    betable[5] = (value >> 16) & 0xFF;
    betable[6] = (value >> 8) & 0xFF;
    betable[7] = (value >> 0) & 0xFF;
}

static inline uint64_t uint64_t_from_be_range(const uint8_t* betable, size_t bytes_to_read) {
    uint64_t ret_val = 0;
    int i = 0;
    for (; i < bytes_to_read; ++i) {
        ret_val <<= 8;
        ret_val |= betable[i];
    }
    return ret_val;
}

static inline void uint64_t_to_be_range(uint64_t value, uint8_t* betable, size_t bytes_to_write) {
    int i = bytes_to_write - 1;
    for (; i >= 0; --i) {
        betable[i] = value & 0xFF;
        value >>= 8;
    }
}

static inline uint8_t uint64_t_storage_bytes_needed(uint64_t value) {
    uint8_t bytes_to_store_value = 0;
    do {
        value >>= 8;
        bytes_to_store_value++;
    } while (value > 0);
    return bytes_to_store_value;
}

static inline int16_t twos_complement_from_raw_12bits(uint16_t u2_raw_value) {
    static const uint16_t INT12_MAX = 0x7FF;
    static const uint16_t UINT12_MAX = 0xFFF;

    if (u2_raw_value <= INT12_MAX) {
        return u2_raw_value;
    } else {
        return u2_raw_value - (UINT12_MAX + 1);
    }
}
