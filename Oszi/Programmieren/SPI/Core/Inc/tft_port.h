/*
 * tft_port.h
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#ifndef INC_TFT_PORT_H_
#define INC_TFT_PORT_H_

#include <stdint.h>

void TFT_Init(void);
void TFT_FillScreen(uint16_t color);
void TFT_FillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t color);
void TFT_DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint16_t color);

/*
 size:
 1 = small
 2 = medium
 3 = large
*/
void TFT_DrawString(int32_t x, int32_t y,
                    const char *s,
                    uint16_t fg,
                    uint16_t bg,
                    uint8_t size);



#endif /* INC_TFT_PORT_H_ */
