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

static void restore_grid_column(int32_t x)
{
    int32_t w = scope_grid_w();
    int32_t h = scope_grid_h();

    for(int32_t i=0;i<=SCOPE_DIV_X;i++){
        int32_t gx = SCOPE_GRID_LEFT + (i*w)/SCOPE_DIV_X;
        if(gx == x){
            uint16_t c = (i == (SCOPE_DIV_X/2)) ? SCOPE_GRID_BOLD : SCOPE_GRID;
            TFT_DrawLine(x, SCOPE_GRID_TOP, x, SCOPE_GRID_BOTTOM, c);
        }
    }

    for(int32_t i=0;i<=SCOPE_DIV_Y;i++){
        int32_t y = SCOPE_GRID_TOP + (i*h)/SCOPE_DIV_Y;
        uint16_t c = (i == (SCOPE_DIV_Y/2)) ? SCOPE_GRID_BOLD : SCOPE_GRID;
        TFT_DrawLine(x, y, x, y, c);
    }
}

void ScopeWave_Init(void)
{
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
        sample_ch[ch] = 0;
        last_y[ch] = map_y(0, chcfg[ch].y_offset);
    }
    tick = 0;
}

void ScopeWave_PushSample(uint8_t ch, uint16_t sample)
{
    if(ch >= SCOPE_MAX_CH) return;
    sample_ch[ch] = sample;
}

int ScopeWave_RenderStep(void)
{
    int32_t width = scope_grid_w();
    int32_t x = SCOPE_GRID_LEFT + (int32_t)(tick % (uint32_t)width);

    int frame_start = (x == SCOPE_GRID_LEFT);

    TFT_FillRect(x, SCOPE_GRID_TOP, 1, scope_grid_h(), SCOPE_BG);
    restore_grid_column(x);

    if(frame_start){
        for(uint8_t ch=0; ch<SCOPE_MAX_CH; ch++){
            last_y[ch] = map_y(sample_ch[ch], chcfg[ch].y_offset);
        }
        last_x = x;
    }

    for(uint8_t ch=0; ch<SCOPE_MAX_CH; ch++){
        int32_t y = map_y(sample_ch[ch], chcfg[ch].y_offset);
        TFT_DrawLine(last_x, last_y[ch], x, y, chcfg[ch].color);
        last_y[ch] = y;
    }

    last_x = x;
    tick++;

    return frame_start;
}


