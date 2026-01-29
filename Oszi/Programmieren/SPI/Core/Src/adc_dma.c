/*
 * adc_dma.c
 *
 *  Created on: Jan 29, 2026
 *      Author: chris
 */

#include "adc_dma.h"
#include "main.h"

extern ADC_HandleTypeDef hadc1;

static volatile uint8_t s_half_ready = 0;
static volatile uint8_t s_full_ready = 0;

static uint16_t s_buf[ADC_DMA_BUF_LEN];

void adc_dma_init(void)
{
}

void adc_dma_start(void)
{
  s_half_ready = 0;
  s_full_ready = 0;

  HAL_ADC_Stop_DMA(&hadc1);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)s_buf, ADC_DMA_BUF_LEN);
}

void adc_dma_stop(void)
{
  HAL_ADC_Stop_DMA(&hadc1);
}

int adc_dma_get_block(adc_dma_block_t *out)
{
  if (!out) return 0;

  if (s_half_ready)
  {
    s_half_ready = 0;
    out->data = &s_buf[0];
    out->packets = ADC_DMA_PACKETS / 2;
    return 1;
  }

  if (s_full_ready)
  {
    s_full_ready = 0;
    out->data = &s_buf[ADC_DMA_RANKS * (ADC_DMA_PACKETS / 2)];
    out->packets = ADC_DMA_PACKETS / 2;
    return 1;
  }

  return 0;
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1) s_half_ready = 1;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1) s_full_ready = 1;
}

