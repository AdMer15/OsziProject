#ifndef INC_SCOPECONTROL_H_
#define INC_SCOPECONTROL_H_

#include "main.h"
#include <stdint.h>

// -------- ENUMS UND STRUKTUREN --------
typedef enum {
    modeTimebase = 0,
    modeVoltScale,
    modeTrigger,
    modeCount
} ScopeMode;

typedef enum {
    channelCh1Only = 0,
    channelCh2Only,
    channelBoth,
    channelCount
} ChannelMode;

typedef struct {
    ScopeMode mode;
    ChannelMode channel;
    uint8_t isRunning;
    float timebaseMs;      // ms/div
    float voltScaleV;      // V/div
    float triggerLevelV;   // Trigger-Level in V
    float potVoltageV;     // aktuelle Potispannung in V
} ScopeControl;

// -------- EXTERNE VARIABLEN UND FUNKTIONEN --------
extern ScopeControl scopeControl;

void ScopeUpdateLogic(void);

#endif /* INC_SCOPECONTROL_H_ */
