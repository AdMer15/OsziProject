/*
 * oszi_adc.c
 *
 *  Created on: Jan 30, 2026
 *      Author: chris
 */

#include "oszi_adc.h"
#include "main.h"
#include "adc_dma.h"
#include "oszi_channels.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;

void OsziAdc_Init(void)
{
  if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED) != HAL_OK)
  {
    Error_Handler();
  }

  adc_dma_init();

  if (HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1) != HAL_OK) Error_Handler();
  if (HAL_TIM_Base_Start(&htim1) != HAL_OK) Error_Handler();

  adc_dma_start();

  OsziChannels_Init(1000, 1000);
}

void OsziAdc_Loop(void)
{
  adc_dma_block_t blk;

  if (adc_dma_get_block(&blk))
  {
    uint16_t a1 = blk.data[0];
    uint16_t a2 = blk.data[1];
    uint16_t a3 = blk.data[2];
    uint16_t a4 = blk.data[3];

    OsziChannels_OnAdcPacket(a1, a2, a3, a4);
  }
}


