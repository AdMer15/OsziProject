/*
 * scope_overlay.h
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#ifndef INC_SCOPE_OVERLAY_H_
#define INC_SCOPE_OVERLAY_H_

#include <stdint.h>

typedef struct {
    uint32_t fps;
    uint8_t  run;
    uint16_t ch1_vdiv_mV;
    uint16_t ch2_vdiv_mV;
} ScopeOverlayState;

void ScopeOverlay_DrawStatic(void);
void ScopeOverlay_Update(const ScopeOverlayState *s);


#endif /* INC_SCOPE_OVERLAY_H_ */
