/*
 * app_scope.c
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#include "app_scope.h"
#include "tft_port.h"
#include "scope_grid.h"
#include "scope_wave.h"
#include "scope_fps.h"
#include "scope_overlay.h"
#include "scope_config.h"

static ScopeOverlayState ov;

void AppScope_Init(void)
{
    TFT_Init();
    TFT_FillScreen(SCOPE_BG);

    ScopeOverlay_DrawStatic();
    ScopeGrid_DrawStatic();

    ScopeWave_Init();
    ScopeFPS_Init();

    ov.fps = 0;
    ov.run = 1;
    ov.ch1_vdiv_mV = 1000;
    ov.ch2_vdiv_mV = 100;
    ScopeOverlay_Update(&ov);
}

void AppScope_Loop(void)
{
    ScopeWave_RenderStep();
    ScopeFPS_FrameTick();

    uint32_t fps = ScopeFPS_Get();
    if(fps != ov.fps){
        ov.fps = fps;
        ScopeOverlay_Update(&ov);
    }
}

