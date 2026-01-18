/*
 * scope_overlay.c
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#include "scope_overlay.h"
#include "scope_config.h"
#include "scope_layout.h"
#include "tft_port.h"
#include <stdio.h>

static void clear_header(void){ TFT_FillRect(0, 0, SCOPE_SCREEN_W, SCOPE_HEADER_H, SCOPE_BG); }
static void clear_footer(void){ TFT_FillRect(0, SCOPE_SCREEN_H - SCOPE_FOOTER_H, SCOPE_SCREEN_W, SCOPE_FOOTER_H, SCOPE_BG); }

void ScopeOverlay_DrawStatic(void)
{
    clear_header();
    clear_footer();
    TFT_DrawLine(0, SCOPE_HEADER_H-1, SCOPE_SCREEN_W-1, SCOPE_HEADER_H-1, SCOPE_GRID);
    TFT_DrawLine(0, SCOPE_SCREEN_H - SCOPE_FOOTER_H, SCOPE_SCREEN_W-1, SCOPE_SCREEN_H - SCOPE_FOOTER_H, SCOPE_GRID);
}

void ScopeOverlay_Update(const ScopeOverlayState *s)
{
    char buf[64];

    clear_header();
    snprintf(buf, sizeof(buf), "FPS:%lu  CH1:%umV/div  CH2:%umV/div  %s",
             (unsigned long)s->fps,
             (unsigned)s->ch1_vdiv_mV,
             (unsigned)s->ch2_vdiv_mV,
             s->run ? "RUN" : "STOP");
    TFT_DrawString(6, 4, buf, SCOPE_TEXT, SCOPE_BG, 1);

    clear_footer();
    TFT_DrawString(6, SCOPE_SCREEN_H - SCOPE_FOOTER_H + 4, "Timebase: --   Trigger: --   Mode: Demo", SCOPE_TEXT, SCOPE_BG, 1);
}

