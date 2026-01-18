/*
 * scope_fps.h
 *
 *  Created on: Jan 18, 2026
 *      Author: chris
 */

#ifndef INC_SCOPE_FPS_H_
#define INC_SCOPE_FPS_H_

#include <stdint.h>

void ScopeFPS_Init(void);
void ScopeFPS_FrameTick(void);
uint32_t ScopeFPS_Get(void);

#endif /* INC_SCOPE_FPS_H_ */
