/*
 * oszi_channels.h
 *
 *  Created on: Jan 30, 2026
 *      Author: chris
 */

#ifndef INC_OSZI_CHANNELS_H_
#define INC_OSZI_CHANNELS_H_

#include <stdint.h>

void OsziChannels_Init(uint16_t init_ch1_vdiv_mV, uint16_t init_ch2_vdiv_mV);
void OsziChannels_OnAdcPacket(uint16_t a1, uint16_t a2, uint16_t a3, uint16_t a4);

#endif /* INC_OSZI_CHANNELS_H_ */
