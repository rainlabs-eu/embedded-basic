#pragma once
#include <stddef.h>
#include <stdint.h>

/*
 * This file contains conversion between different binary types, taking endiannes into account.
 *
 * Byte naming convention:
 *
 * Double Word: |           Complete 64 bit value (double/uint64_t)             |
 *
 * Word:        |   M - Most significant Word   |   L - Least Significant Word  |
 * 32 bits      |    (Within Unit Above)        |     (Within Unit Above)       |
 *
 * HalfWord     |   M - MS HW   |   L - LS HW   |   M - MS HW   |   L - LS HW   |
 * 16 bits      |      WUA      |      WUA      |      WUA      |      WUA      |
 *
 * Byte (8 bits)|  MSB  |  LSB  |  MSB  |  LSB  |  MSB  |  LSB  |  MSB  |  LSB  |
 *
 * Encoding:    |  MMM  |  MML  |  MLM  |  MLL  |  LMM  |  LML  |  LLM  |  LLL  |
 */

static inline uint8_t uint16_t_get_msb(const uint16_t val);
static inline uint8_t uint16_t_get_lsb(const uint16_t val);

static inline uint16_t uint16_t_from_bytes(const uint8_t msb, const uint8_t lsb);
static inline uint16_t uint16_t_from_be_table(const uint8_t* betable);
static inline void uint16_t_to_be_table(uint16_t value, uint8_t* betable);
static inline uint16_t uint16_t_from_le_table(const uint8_t* letable);

static inline uint8_t uint32_t_get_mmsb(const uint32_t val);
static inline uint8_t uint32_t_get_mlsb(const uint32_t val);
static inline uint8_t uint32_t_get_lmsb(const uint32_t val);
static inline uint8_t uint32_t_get_llsb(const uint32_t val);

static inline uint32_t uint32_t_from_bytes(const uint8_t mm_sb,
                                           const uint8_t ml_sb,
                                           const uint8_t lm_sb,
                                           const uint8_t ll_sb);

static inline uint32_t uint32_t_from_uint16_t(uint16_t mshw, uint16_t lshw);

static inline uint32_t uint32_t_from_le_table(const uint8_t* letable);
static inline uint32_t uint32_t_from_be_table(const uint8_t* betable);

static inline uint64_t uint64_t_from_be_table(const uint8_t* betable);
static inline uint64_t uint64_from_bytes(const uint8_t mmm_sb,
                                         const uint8_t mml_sb,
                                         const uint8_t mlm_sb,
                                         const uint8_t mll_sb,
                                         const uint8_t lmm_sb,
                                         const uint8_t lml_sb,
                                         const uint8_t llm_sb,
                                         const uint8_t lll_sb);
static inline void uint64_t_to_be_table(uint64_t value, uint8_t* betable);

static inline uint64_t uint64_t_from_be_range(const uint8_t* betable, size_t bytes_to_read);
static inline void uint64_t_to_be_range(uint64_t value, uint8_t* betable, size_t bytes_to_write);
static inline uint8_t uint64_t_storage_bytes_needed(uint64_t value);

static inline float float_from_bytes(const uint8_t mm_sb,
                                     const uint8_t ml_sb,
                                     const uint8_t lm_sb,
                                     const uint8_t ll_sb);
static inline float float_from_be_table(const uint8_t* betable);

static inline double double_from_bytes(const uint8_t mmm_sb,
                                       const uint8_t mml_sb,
                                       const uint8_t mlm_sb,
                                       const uint8_t mll_sb,
                                       const uint8_t lmm_sb,
                                       const uint8_t lml_sb,
                                       const uint8_t llm_sb,
                                       const uint8_t lll_sb);
static inline double double_from_be_table(const uint8_t* betable);

static inline int32_t twos_complement_from_raw_24bits(uint32_t u2_raw_value);
static inline int16_t twos_complement_from_raw_14bits(uint16_t u2_raw_value);
static inline int16_t twos_complement_from_raw_12bits(uint16_t u2_raw_value);

#include "bitconverter.impl.h"
