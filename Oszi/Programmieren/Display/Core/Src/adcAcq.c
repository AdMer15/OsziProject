#include "adcAcq.h"
#include "adc.h"        // CubeMX: für hadc1, HAL Funktionen
#include <string.h>

// interne Speicherung
static uint16_t raw_values[ADC_CHANNELS];
static const uint32_t adc_channels[ADC_CHANNELS] = {
    ADC_CHANNEL_5,   // PA0
    ADC_CHANNEL_6,   // PA1
    ADC_CHANNEL_8,   // PA3
    ADC_CHANNEL_9    // PA4
};

// Deine Spannungsteilerfaktoren HIER EINTRAGEN:
// echte_spannung = gemessene_spannung * faktor
static const float scale_factor[ADC_CHANNELS] = {
    10.0f,   // CH0 → PA0
    5.0f,    // CH1 → PA1
    8.0f,    // CH2 → PA3
    4.0f     // CH3 → PA4
};


extern ADC_HandleTypeDef hadc1;

// einen einzelnen Kanal messen
static uint16_t adc_read_channel(uint32_t channel)
{
    ADC_ChannelConfTypeDef sConfig;
    memset(&sConfig, 0, sizeof(sConfig));

    sConfig.Channel      = channel;
    sConfig.Rank         = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
    sConfig.SingleDiff   = ADC_SINGLE_ENDED;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    return HAL_ADC_GetValue(&hadc1);
}


// alle 4 Kanäle aktualisieren
void adc_update_all(void)
{
    for (int i = 0; i < ADC_CHANNELS; i++)
        raw_values[i] = adc_read_channel(adc_channels[i]);
}


uint16_t adc_get_raw(uint8_t ch)
{
    if (ch >= ADC_CHANNELS) return 0;
    return raw_values[ch];
}

float adc_get_voltage(uint8_t ch)
{
    if (ch >= ADC_CHANNELS) return 0.0f;
    return (3.3f * raw_values[ch]) / 4095.0f;
}

float adc_get_real_voltage(uint8_t ch)
{
    if (ch >= ADC_CHANNELS) return 0.0f;
    return adc_get_voltage(ch) * scale_factor[ch];
}
