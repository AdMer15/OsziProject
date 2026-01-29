/*
 * scope_fps.c
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#include "scope_fps.h"
#include "stm32l4xx_hal.h"

static uint32_t last_ms;
static uint32_t frames;
static uint32_t fps;

void ScopeFPS_Init(void)
{
    last_ms = HAL_GetTick();
    frames = 0;
    fps = 0;
}

void ScopeFPS_FrameTick(void)
{
    frames++;
    uint32_t now = HAL_GetTick();
    if((now - last_ms) >= 1000){
        fps = frames;
        frames = 0;
        last_ms = now;
    }
}

uint32_t ScopeFPS_Get(void)
{
    return fps;
}

