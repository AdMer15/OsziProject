#ifndef ADC_ACQ_H
#define ADC_ACQ_H

#include <stdint.h>

#define ADC_CHANNELS 4

void adc_update_all(void);
uint16_t adc_get_raw(uint8_t ch);
float adc_get_voltage(uint8_t ch);
float adc_get_real_voltage(uint8_t ch);

#endif
