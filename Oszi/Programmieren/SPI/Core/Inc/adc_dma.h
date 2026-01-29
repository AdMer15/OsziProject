/*
 * adc_dma.h
 *
 *  Created on: Jan 29, 2026
 *      Author: chris
 */

#ifndef INC_ADC_DMA_H_
#define INC_ADC_DMA_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_DMA_RANKS              4
#define ADC_DMA_PACKETS            512
#define ADC_DMA_BUF_LEN            (ADC_DMA_RANKS * ADC_DMA_PACKETS)

typedef struct
{
  const uint16_t *data;
  uint32_t packets;
} adc_dma_block_t;

void adc_dma_init(void);
void adc_dma_start(void);
void adc_dma_stop(void);

int  adc_dma_get_block(adc_dma_block_t *out);

#ifdef __cplusplus
}
#endif



#endif /* INC_ADC_DMA_H_ */
