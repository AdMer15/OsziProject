/*
 * scope_grid.c
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#include "scope_grid.h"
#include "scope_layout.h"
#include "scope_config.h"
#include "tft_port.h"

void ScopeGrid_DrawStatic(void)
{
    int32_t w = scope_grid_w();
    int32_t h = scope_grid_h();

    for(int32_t i=0;i<=SCOPE_DIV_X;i++){
        int32_t x = SCOPE_GRID_LEFT + (i*w)/SCOPE_DIV_X;
        uint16_t c = (i == (SCOPE_DIV_X/2)) ? SCOPE_GRID_BOLD : SCOPE_GRID;
        TFT_DrawLine(x, SCOPE_GRID_TOP, x, SCOPE_GRID_BOTTOM, c);
    }

    for(int32_t i=0;i<=SCOPE_DIV_Y;i++){
        int32_t y = SCOPE_GRID_TOP + (i*h)/SCOPE_DIV_Y;
        uint16_t c = (i == (SCOPE_DIV_Y/2)) ? SCOPE_GRID_BOLD : SCOPE_GRID;
        TFT_DrawLine(SCOPE_GRID_LEFT, y, SCOPE_GRID_RIGHT, y, c);
    }
}

