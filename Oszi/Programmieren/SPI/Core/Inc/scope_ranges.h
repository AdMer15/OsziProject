/*
 * scope_ranges.h
 *
 *  Created on: Jan 29, 2026
 *      Author: chris
 */

#ifndef INC_SCOPE_RANGES_H_
#define INC_SCOPE_RANGES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  float ch1_v;
  float ch2_v;
} scope_sample_t;

void scope_ranges_set_scale(float ch1_low, float ch1_high, float ch2_low, float ch2_high);
scope_sample_t scope_ranges_convert(uint16_t r1, uint16_t r2, uint16_t r3, uint16_t r4);

#ifdef __cplusplus
}
#endif

#endif /* INC_SCOPE_RANGES_H_ */
