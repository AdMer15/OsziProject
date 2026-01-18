/*
 * tft_port.c
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#include "tft_port.h"
#include "ili9341.h"
#include "fonts.h"
#include <stdlib.h>

/* ---------- interne Helfer ---------- */

static FontDef font_from_size(uint8_t size)
{
    switch(size)
    {
        case 2: return Font_11x18;
        case 3: return Font_16x26;
        default: return Font_7x10;
    }
}

/* ---------- API ---------- */

void TFT_Init(void)
{
    ILI9341_Init();
}

void TFT_FillScreen(uint16_t color)
{
    ILI9341_FillScreen(color);
}

void TFT_FillRect(int32_t x, int32_t y,
                  int32_t w, int32_t h,
                  uint16_t color)
{
    ILI9341_FillRectangle(x, y, w, h, color);
}

/* ---------- Bresenham Line ---------- */

void TFT_DrawLine(int32_t x0, int32_t y0,
                  int32_t x1, int32_t y1,
                  uint16_t color)
{
    int32_t dx = abs(x1 - x0);
    int32_t sx = x0 < x1 ? 1 : -1;
    int32_t dy = -abs(y1 - y0);
    int32_t sy = y0 < y1 ? 1 : -1;
    int32_t err = dx + dy;

    while (1)
    {
        ILI9341_DrawPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int32_t e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void TFT_DrawString(int32_t x, int32_t y,
                    const char *s,
                    uint16_t fg,
                    uint16_t bg,
                    uint8_t size)
{
    FontDef font = font_from_size(size);
    ILI9341_WriteString((uint16_t)x,
                        (uint16_t)y,
                        s,
                        font,
                        fg,
                        bg);
}

