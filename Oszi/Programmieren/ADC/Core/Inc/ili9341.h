/*
 * ili9341.h
 *
 *  Modified for STM32L432KC + ILI9341 (SPI1)
 *  Pin Mapping:
 *    PA5  -> SPI1_SCK
 *    PA6  -> SPI1_MISO
 *    PA7  -> SPI1_MOSI
 *    PB7  -> CS (Chip Select)
 *    PB0  -> DC (Data/Command)
 *    PB4  -> RESET
 */

#ifndef LIB_ILI9341_ILI9341_H_
#define LIB_ILI9341_ILI9341_H_

#include "main.h"
#include "fonts.h"

//---------------- SPI Handle ----------------//
extern SPI_HandleTypeDef hspi1;

//---------------- Pin Zuordnung -------------//
#define ILI9341_SPI_PORT        hspi1

#define ILI9341_CS_GPIO_PORT    GPIOB
#define ILI9341_CS_PIN          GPIO_PIN_0   // DCS

#define ILI9341_DC_GPIO_PORT    GPIOB
#define ILI9341_DC_PIN          GPIO_PIN_1   // DD/C

#define ILI9341_RESET_GPIO_PORT GPIOB
#define ILI9341_RESET_PIN       GPIO_PIN_4   // DRS

//---------------- Displaygröße --------------//
#define ILI9341_WIDTH           240
#define ILI9341_HEIGHT          320

//---------------- Farben --------------------//
#define ILI9341_BLACK           0x0000
#define ILI9341_BLUE            0x001F
#define ILI9341_RED             0xF800
#define ILI9341_GREEN           0x07E0
#define ILI9341_CYAN            0x07FF
#define ILI9341_MAGENTA         0xF81F
#define ILI9341_YELLOW          0xFFE0
#define ILI9341_GRAY            0x528A
#define ILI9341_WHITE           0xFFFF
#define ILI9341_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

//---------------- Orientierung --------------//
#define ILI9341_MADCTL_MY       0x80
#define ILI9341_MADCTL_MX       0x40
#define ILI9341_MADCTL_MV       0x20
#define ILI9341_MADCTL_ML       0x10
#define ILI9341_MADCTL_RGB      0x00
#define ILI9341_MADCTL_BGR      0x08
#define ILI9341_MADCTL_MH       0x04

#define ILI9341_ORIENTATION_DEFAULT       (ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR)
#define ILI9341_ORIENTATION_ROTATE_RIGHT  (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
#define ILI9341_ORIENTATION_ROTATE_LEFT   (ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
#define ILI9341_ORIENTATION_UPSIDE_DOWN   (ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR)

//---------------- Display-Struct ------------//
typedef struct
{
    SPI_HandleTypeDef *spi;

    GPIO_TypeDef* cs_gpio_port;
    GPIO_TypeDef* dc_gpio_port;
    GPIO_TypeDef* reset_gpio_port;

    uint16_t cs_pin;
    uint16_t dc_pin;
    uint16_t reset_pin;

    uint16_t width;
    uint16_t height;
    uint8_t  orientation;
} ILI9341TypeDef;

//---------------- Makros --------------------//
// Chip-Select steuern
#define ILI9341_UNSELECT(display) (display)->cs_gpio_port->BSRR = (display)->cs_pin;
#define ILI9341_SELECT(display)   (display)->cs_gpio_port->BSRR = (uint32_t)((display)->cs_pin) << 16U;

// Daten-/Kommando-Pin
#define ILI9341_DATA(display)     (display)->dc_gpio_port->BSRR = (display)->dc_pin;
#define ILI9341_COMMAND(display)  (display)->dc_gpio_port->BSRR = (uint32_t)((display)->dc_pin) << 16U;

//---------------- Buffergröße ---------------//
#define ILI9341_BUFFER_MAX_SIZE   500

//---------------- Funktionsprototypen -------//
void ILI9341_Init(ILI9341TypeDef *display);
void ILI9341_InvertColors(ILI9341TypeDef *display, uint8_t invert);
void ILI9341_DrawPixel(ILI9341TypeDef *display, uint16_t x, uint16_t y, uint16_t color);
void ILI9341_FillScreen(ILI9341TypeDef *display, uint16_t color);
void ILI9341_FillRectangle(ILI9341TypeDef *display, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_Rectangle(ILI9341TypeDef *display, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_WriteString(ILI9341TypeDef *display, uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);

#endif /* LIB_ILI9341_ILI9341_H_ */
