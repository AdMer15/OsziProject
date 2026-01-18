/*
 * scope_wave.h
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#ifndef INC_SCOPE_WAVE_H_
#define INC_SCOPE_WAVE_H_

#include <stdint.h>

typedef struct {
    uint16_t color;
    int16_t  y_offset;
    uint16_t vdiv_mV;
} ScopeChannelCfg;

void ScopeWave_Init(void);
void ScopeWave_SetChannelCfg(uint8_t ch, ScopeChannelCfg cfg);
void ScopeWave_Reset(void);

void ScopeWave_PushSample(uint8_t ch, uint16_t sample);
void ScopeWave_RenderStep(void);

#endif /* INC_SCOPE_WAVE_H_ */
