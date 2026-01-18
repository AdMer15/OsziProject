/*
 * scope_config.h
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#ifndef INC_SCOPE_CONFIG_H_
#define INC_SCOPE_CONFIG_H_

#include <stdint.h>

#define SCOPE_SCREEN_W 320
#define SCOPE_SCREEN_H 240

#define SCOPE_BG        0x0000
#define SCOPE_TEXT      0xFFFF
#define SCOPE_GRID      0x4208
#define SCOPE_GRID_BOLD 0x8410

#define SCOPE_CH1_COLOR 0xFFE0
#define SCOPE_CH2_COLOR 0x07FF

#define SCOPE_MAX_CH 2
#define SCOPE_ADC_MAX 4095

#endif /* INC_SCOPE_CONFIG_H_ */
