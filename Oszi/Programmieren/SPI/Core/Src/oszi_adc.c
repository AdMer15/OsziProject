/*
 * oszi_adc.c
 *
 *  Created on: Jan 30, 2026
 *      Author: chris
 */

#include "oszi_adc.h"
#include "main.h"
#include "adc_dma.h"

#include <stdio.h>

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;

static uint16_t s_latest[4] = {0};
static volatile uint8_t s_has_latest = 0;

static uint32_t s_last_print_ms = 0;

static void uart_print4(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
  char msg[80];
  int n = snprintf(msg, sizeof(msg), "ADC: %u %u %u %u\r\n", a, b, c, d);
  HAL_UART_Transmit(&huart2, (uint8_t*)msg, n, 100);
}

void OsziAdc_Init(void)
{
  adc_dma_init();

  HAL_ADC_Stop_DMA(&hadc1);
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

  HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_Base_Start(&htim1);

  adc_dma_start();
}

void OsziAdc_Loop(void)
{
  adc_dma_block_t blk;

  if (adc_dma_get_block(&blk))
  {
    s_latest[0] = blk.data[0];
    s_latest[1] = blk.data[1];
    s_latest[2] = blk.data[2];
    s_latest[3] = blk.data[3];
    s_has_latest = 1;

    uint32_t now = HAL_GetTick();
    if (now - s_last_print_ms >= 200)
    {
      s_last_print_ms = now;
      uart_print4(s_latest[0], s_latest[1], s_latest[2], s_latest[3]);
    }
  }
}

int OsziAdc_GetLatest(uint16_t out4[4])
{
  if (!s_has_latest) return 0;
  out4[0] = s_latest[0];
  out4[1] = s_latest[1];
  out4[2] = s_latest[2];
  out4[3] = s_latest[3];
  return 1;
}

