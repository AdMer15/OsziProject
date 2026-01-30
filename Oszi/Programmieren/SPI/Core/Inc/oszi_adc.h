/*
 * oszi_adc.h
 *
 *  Created on: Jan 30, 2026
 *      Author: chris
 */

#ifndef INC_OSZI_ADC_H_
#define INC_OSZI_ADC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void OsziAdc_Init(void);
void OsziAdc_Loop(void);

int  OsziAdc_GetLatest(uint16_t out4[4]);

#ifdef __cplusplus
}
#endif

#endif /* INC_OSZI_ADC_H_ */
