/*
 * scope_layout.h
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#ifndef INC_SCOPE_LAYOUT_H_
#define INC_SCOPE_LAYOUT_H_

#include <stdint.h>
#include "scope_config.h"

#define SCOPE_HEADER_H 20
#define SCOPE_FOOTER_H 20

#define SCOPE_GRID_TOP    (SCOPE_HEADER_H)
#define SCOPE_GRID_BOTTOM (SCOPE_SCREEN_H - SCOPE_FOOTER_H)

#define SCOPE_GRID_LEFT   10
#define SCOPE_GRID_RIGHT  (SCOPE_SCREEN_W - 10)

#define SCOPE_DIV_X 10
#define SCOPE_DIV_Y 8

static inline int32_t scope_grid_w(void){ return (SCOPE_GRID_RIGHT - SCOPE_GRID_LEFT); }
static inline int32_t scope_grid_h(void){ return (SCOPE_GRID_BOTTOM - SCOPE_GRID_TOP); }

#endif /* INC_SCOPE_LAYOUT_H_ */
