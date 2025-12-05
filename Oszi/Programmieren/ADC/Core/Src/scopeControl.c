#include "scopeControl.h"
#include <stdio.h>

// -------- GLOBALE VARIABLEN --------
ScopeControl scopeControl = {
    .mode = modeTimebase,
    .channel = channelBoth,
    .isRunning = 0,
    .timebaseMs = 1.0f,
    .voltScaleV = 1.0f,
    .triggerLevelV = 1.65f,
    .potVoltageV = 0.0f
};

// -------- PINDEFINITIONEN --------
#define BUTTON_MODE_PORT GPIOA
#define BUTTON_MODE_PIN  GPIO_PIN_10
#define BUTTON_CH_PORT   GPIOA
#define BUTTON_CH_PIN    GPIO_PIN_11
#define BUTTON_RUN_PORT  GPIOB
#define BUTTON_RUN_PIN   GPIO_PIN_5

#define POT_ADC_CHANNEL  ADC_CHANNEL_8 // PA9

#define VREF 3.3f
#define ADC_RES 4095.0f

extern ADC_HandleTypeDef hadc1;

// -------- INTERNE FUNKTIONEN --------
static void scopeReadButtons(void);
static void scopeReadPot(void);
static void scopeApplyPotValue(void);

// -------- INTERNE BUTTONZUSTÄNDE --------
static uint8_t lastModeState = 1;
static uint8_t lastChannelState = 1;
static uint8_t lastRunState = 1;

// -------- HAUPTFUNKTION --------
void ScopeUpdateLogic(void)
{
    scopeReadButtons();
    scopeReadPot();
    scopeApplyPotValue();
}

// -------- BUTTON-LOGIK MIT ENTPRELLUNG --------
static void scopeReadButtons(void)
{
    uint8_t modeState = HAL_GPIO_ReadPin(BUTTON_MODE_PORT, BUTTON_MODE_PIN);
    uint8_t channelState = HAL_GPIO_ReadPin(BUTTON_CH_PORT, BUTTON_CH_PIN);
    uint8_t runState = HAL_GPIO_ReadPin(BUTTON_RUN_PORT, BUTTON_RUN_PIN);

    // --- MODE ---
    if (lastModeState == 1 && modeState == 0) {
        scopeControl.mode = (scopeControl.mode + 1) % modeCount;
        printf("[MODE] %d -> %s\n", scopeControl.mode,
               (scopeControl.mode == modeTimebase) ? "TIMEBASE" :
               (scopeControl.mode == modeVoltScale) ? "VOLTSCALE" : "TRIGGER");
    }

    // --- CHANNEL ---
    if (lastChannelState == 1 && channelState == 0) {
        scopeControl.channel = (scopeControl.channel + 1) % channelCount;
        printf("[CHANNEL] ");
        if (scopeControl.channel == channelCh1Only) printf("CH1 only\n");
        else if (scopeControl.channel == channelCh2Only) printf("CH2 only\n");
        else printf("CH1 + CH2\n");
    }

    // --- RUN / STOP ---
    if (lastRunState == 1 && runState == 0) {
        scopeControl.isRunning = !scopeControl.isRunning;
        printf("[RUN] %s\n", scopeControl.isRunning ? "RUNNING" : "STOPPED");
    }

    lastModeState = modeState;
    lastChannelState = channelState;
    lastRunState = runState;
}

// -------- POTI AUSLESEN --------
static void scopeReadPot(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = POT_ADC_CHANNEL;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint16_t adcValue = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    scopeControl.potVoltageV = (adcValue / ADC_RES) * VREF;
}

// -------- POTI-WERT AUF AKTUELLE FUNKTION ANWENDEN --------
static void scopeApplyPotValue(void)
{
    switch (scopeControl.mode) {
        case modeTimebase:
            scopeControl.timebaseMs = 0.1f + (scopeControl.potVoltageV / VREF) * 9.9f;
            break;
        case modeVoltScale:
            scopeControl.voltScaleV = 0.5f + (scopeControl.potVoltageV / VREF) * 9.5f;
            break;
        case modeTrigger:
            scopeControl.triggerLevelV = scopeControl.potVoltageV;
            break;
    }

}
