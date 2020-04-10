#pragma once
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

uint8_t uint16_t_get_msb(const uint16_t val);
uint8_t uint16_t_get_lsb(const uint16_t val);

uint16_t uint16_t_from_bytes(const uint8_t msb, const uint8_t lsb);
uint16_t uint16_t_from_be_table(const uint8_t* betable);
uint16_t uint16_t_from_le_table(const uint8_t* letable);

uint8_t uint32_t_get_mmsb(const uint32_t val);
uint8_t uint32_t_get_mlsb(const uint32_t val);
uint8_t uint32_t_get_lmsb(const uint32_t val);
uint8_t uint32_t_get_llsb(const uint32_t val);

uint32_t uint32_t_from_bytes(const uint8_t mm_sb, const uint8_t ml_sb, const uint8_t lm_sb, const uint8_t ll_sb);

uint32_t uint32_t_from_uint16_t(uint16_t mshw, uint16_t lshw);

uint32_t uint32_t_from_le_table(const uint8_t* letable);
uint32_t uint32_t_from_be_table(const uint8_t* betable);

uint64_t uint64_from_bytes(const uint8_t mmm_sb,
                           const uint8_t mml_sb,
                           const uint8_t mlm_sb,
                           const uint8_t mll_sb,
                           const uint8_t lmm_sb,
                           const uint8_t lml_sb,
                           const uint8_t llm_sb,
                           const uint8_t lll_sb);

float float_from_bytes(const uint8_t mm_sb, const uint8_t ml_sb, const uint8_t lm_sb, const uint8_t ll_sb);
float float_from_be_table(const uint8_t* betable);

double double_from_bytes(const uint8_t mmm_sb,
                         const uint8_t mml_sb,
                         const uint8_t mlm_sb,
                         const uint8_t mll_sb,
                         const uint8_t lmm_sb,
                         const uint8_t lml_sb,
                         const uint8_t llm_sb,
                         const uint8_t lll_sb);
double double_from_be_table(const uint8_t* betable);

int32_t twos_complement_from_raw_24bits(uint32_t u2_raw_value);
int16_t twos_complement_from_raw_14bits(uint16_t u2_raw_value);
int16_t twos_complement_from_raw_12bits(uint16_t u2_raw_value);

#include "bitconverter.impl.h"
