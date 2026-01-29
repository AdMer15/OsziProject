/*
 * scope_wave.c
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#include "scope_wave.h"
#include "scope_layout.h"
#include "scope_config.h"
#include "tft_port.h"
#include <math.h>

#define LUT_SIZE 256

static uint16_t sin_lut[LUT_SIZE];

static ScopeChannelCfg chcfg[SCOPE_MAX_CH];

static uint16_t sample_ch[SCOPE_MAX_CH];
static int32_t  last_x;
static int32_t  last_y[SCOPE_MAX_CH];
static uint32_t tick;

static int32_t map_y(uint16_t v, int16_t y_offset)
{
    int32_t gh = scope_grid_h();
    int32_t y = SCOPE_GRID_TOP + gh - (int32_t)((uint32_t)v * (uint32_t)gh / SCOPE_ADC_MAX);
    y += y_offset;
    if(y < SCOPE_GRID_TOP) y = SCOPE_GRID_TOP;
    if(y > SCOPE_GRID_BOTTOM) y = SCOPE_GRID_BOTTOM;
    return y;
}

void ScopeWave_Init(void)
{
    for(int32_t i=0;i<LUT_SIZE;i++){
        float s = sinf(2.0f * 3.1415926f * (float)i / (float)LUT_SIZE);
        float n = (s + 1.0f) * 0.5f;
        sin_lut[i] = (uint16_t)(n * (float)SCOPE_ADC_MAX);
    }

    chcfg[0].color = SCOPE_CH1_COLOR;
    chcfg[0].y_offset = 0;
    chcfg[0].vdiv_mV = 1000;

    chcfg[1].color = SCOPE_CH2_COLOR;
    chcfg[1].y_offset = 0;
    chcfg[1].vdiv_mV = 100;

    ScopeWave_Reset();
}

void ScopeWave_SetChannelCfg(uint8_t ch, ScopeChannelCfg cfg)
{
    if(ch >= SCOPE_MAX_CH) return;
    chcfg[ch] = cfg;
}

void ScopeWave_Reset(void)
{
    last_x = SCOPE_GRID_LEFT;
    for(uint8_t ch=0; ch<SCOPE_MAX_CH; ch++){
        last_y[ch] = map_y(0, chcfg[ch].y_offset);
        sample_ch[ch] = 0;
    }
    tick = 0;
}

void ScopeWave_PushSample(uint8_t ch, uint16_t sample)
{
    if(ch >= SCOPE_MAX_CH) return;
    sample_ch[ch] = sample;
}

static uint16_t test_signal(uint32_t t, uint8_t ch)
{
    uint32_t idx = (t + (ch ? LUT_SIZE/4 : 0)) % LUT_SIZE;
    return sin_lut[idx];
}

void ScopeWave_RenderStep(void)
{
    int32_t width = scope_grid_w();
    int32_t x = SCOPE_GRID_LEFT + (int32_t)(tick % (uint32_t)width);

    if(x == SCOPE_GRID_LEFT){
        for(uint8_t ch=0; ch<SCOPE_MAX_CH; ch++){
            uint16_t v = test_signal(tick, ch);
            int32_t y = map_y(v, chcfg[ch].y_offset);
            last_y[ch] = y;
        }
        last_x = x;
    }

    for(uint8_t ch=0; ch<SCOPE_MAX_CH; ch++){
        uint16_t v = test_signal(tick, ch);
        int32_t y = map_y(v, chcfg[ch].y_offset);
        TFT_DrawLine(last_x, last_y[ch], x, y, chcfg[ch].color);
        last_y[ch] = y;
    }

    last_x = x;
    tick++;
}

