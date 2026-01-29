/*
 * scope_ranges.c
 *
 *  Created on: Jan 29, 2026
 *      Author: chris
 */

#include "scope_ranges.h"

static float k_ch1_low  = 1.0f;
static float k_ch1_high = 1.0f;
static float k_ch2_low  = 1.0f;
static float k_ch2_high = 1.0f;

void scope_ranges_set_scale(float ch1_low, float ch1_high, float ch2_low, float ch2_high)
{
  k_ch1_low  = ch1_low;
  k_ch1_high = ch1_high;
  k_ch2_low  = ch2_low;
  k_ch2_high = ch2_high;
}

static float adc_to_v(uint16_t raw, float k)
{
  return ((float)raw * 3.3f / 4095.0f) * k;
}

scope_sample_t scope_ranges_convert(uint16_t r1, uint16_t r2, uint16_t r3, uint16_t r4)
{
  float ch1_low  = adc_to_v(r1, k_ch1_low);
  float ch1_high = adc_to_v(r2, k_ch1_high);
  float ch2_low  = adc_to_v(r3, k_ch2_low);
  float ch2_high = adc_to_v(r4, k_ch2_high);

  scope_sample_t s;

  s.ch1_v = (r1 > 3900) ? ch1_high : ch1_low;
  s.ch2_v = (r3 > 3900) ? ch2_high : ch2_low;

  return s;
}

