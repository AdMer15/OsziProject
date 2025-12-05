/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9341.h"
#include "fonts.h"
#include "adcAcq.h"
#include "scopeControl.h"

#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern SPI_HandleTypeDef hspi1;

// ---- Pins ----
#define CS_LOW()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)
#define CS_HIGH()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)

#define DC_LOW()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)
#define DC_HIGH()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)

#define RST_LOW()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET)
#define RST_HIGH()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET)

// ---- Command ----
void ILI_cmd(uint8_t cmd)
{
    CS_LOW();
    DC_LOW();
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    CS_HIGH();
}

// ---- Data ----
void ILI_data(uint8_t data)
{
    CS_LOW();
    DC_HIGH();
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
    CS_HIGH();
}

// ---- 16-Bit Color ----
void ILI_data16(uint16_t data)
{
    uint8_t buf[2] = { data >> 8, data & 0xFF };
    CS_LOW();
    DC_HIGH();
    HAL_SPI_Transmit(&hspi1, buf, 2, HAL_MAX_DELAY);
    CS_HIGH();
}

// ---- Reset + Init ----
void ILI_reset()
{
    RST_LOW();
    HAL_Delay(20);
    RST_HIGH();
    HAL_Delay(20);
}

void ILI_init()
{
    ILI_reset();

    ILI_cmd(0x01);  // Software reset
    HAL_Delay(5);

    ILI_cmd(0x28);  // Display OFF

    ILI_cmd(0x3A);  // Pixel Format
    ILI_data(0x55); // 16-bit

    ILI_cmd(0x36);  // Memory Access Control
    ILI_data(0x48); // BGR, row/col order

    ILI_cmd(0x11);  // Sleep out
    HAL_Delay(120);

    ILI_cmd(0x29);  // Display ON
}

// ---- Set window ----
void ILI_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    ILI_cmd(0x2A);
    ILI_data(x1 >> 8); ILI_data(x1 & 0xFF);
    ILI_data(x2 >> 8); ILI_data(x2 & 0xFF);

    ILI_cmd(0x2B);
    ILI_data(y1 >> 8); ILI_data(y1 & 0xFF);
    ILI_data(y2 >> 8); ILI_data(y2 & 0xFF);

    ILI_cmd(0x2C);
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
//  ILI9341TypeDef display = {
//      .spi = &hspi1,
//      .cs_gpio_port = ILI9341_CS_GPIO_PORT,
//      .dc_gpio_port = ILI9341_DC_GPIO_PORT,
//      .reset_gpio_port = ILI9341_RESET_GPIO_PORT,
//      .cs_pin = ILI9341_CS_PIN,
//      .dc_pin = ILI9341_DC_PIN,
//      .reset_pin = ILI9341_RESET_PIN,
//      .width = ILI9341_WIDTH,
//      .height = ILI9341_HEIGHT,
//      .orientation = ILI9341_ORIENTATION_DEFAULT
//  };
//
//  ILI9341_Init(&display);
//  ILI9341_FillScreen(&display, ILI9341_BLACK);
//  ILI9341_WriteString(&display, 10, 10, "Display OK!", Font_11x18, ILI9341_WHITE, ILI9341_BLACK);
//
//  // optional: Display oder UART init, falls du debuggen willst
//  adcAcqInit();
//
//  char msg[100];
//
//  if (adcAcqStart() != HAL_OK) {
//     Error_Handler();
//  }
  // Display initialisieren
  ILI_init();

  // komplettes Fenster setzen
  ILI_set_window(0, 0, 239, 319);

  // ROT in RGB565
  uint16_t red = 0xF800;

  // gesamten Bildschirm rot füllen
  for(uint32_t i = 0; i < 240UL * 320UL; i++)
  {
      ILI_data16(red);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  adc_update_all();
//
//	          for (int ch = 0; ch < 4; ch++)
//	          {
//	              uint16_t raw = adc_get_raw(ch);
//	              float v_pin  = adc_get_voltage(ch);
//	              float v_real = adc_get_real_voltage(ch);
//
//	              snprintf(msg, sizeof(msg),
//	                  "CH%d  RAW=%u  Vin=%.3fV  Real=%.2fV\r\n",
//	                  ch, raw, v_pin, v_real);
//
//	              HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
//	          }
//
//	          HAL_Delay(500);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
	    ScopeUpdateLogic();   // <-- Steuerlogik ausführen
	    HAL_Delay(50);        // kleine Entprellpause
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
