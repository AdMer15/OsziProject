/*
 * oszi_channels.c
 *
 *  Created on: Jan 30, 2026
 *      Author: chris
 */

#include "oszi_channels.h"
#include "scope_wave.h"
#include "scope_config.h"

#define ADC_MAX_F         4095.0f
#define ADC_MID_F         2047.5f
#define VREF_MV_F         3300.0f
#define VDIVS_Y_F         8.0f

#define CH1_NARROW_MAX_MV  1000.0f
#define CH1_WIDE_MAX_MV   10000.0f

#define CH2_NARROW_MAX_MV 36000.0f
#define CH2_WIDE_MAX_MV   10100.0f

static const uint16_t vdiv_table_mV[] = {
  50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000
};

typedef enum { R_NARROW = 0, R_WIDE = 1 } range_sel_t;

static range_sel_t ch1_sel = R_NARROW;
static range_sel_t ch2_sel = R_WIDE;

static uint16_t ch1_vdiv_mV = 1000;
static uint16_t ch2_vdiv_mV = 1000;

static float adc_to_vin_mV(uint16_t adc, float vin_max_mV)
{
  float x = ((float)adc - ADC_MID_F);
  return x * (vin_max_mV / (ADC_MAX_F * 0.5f));
}

static float adc_fullscale_frac(uint16_t adc)
{
  float x = (float)adc - ADC_MID_F;
  if (x < 0) x = -x;
  return x / (ADC_MAX_F * 0.5f);
}

static range_sel_t select_range(range_sel_t cur, float frac)
{
  if (cur == R_NARROW)
  {
    if (frac > 0.90f) return R_WIDE;
    return R_NARROW;
  }
  else
  {
    if (frac < 0.70f) return R_NARROW;
    return R_WIDE;
  }
}

static uint16_t pick_vdiv(uint16_t cur, float vin_abs_mV)
{
  float need = vin_abs_mV / 3.5f;
  if (need < 1.0f) need = 1.0f;

  uint16_t best = vdiv_table_mV[0];
  for (uint32_t i = 0; i < (sizeof(vdiv_table_mV)/sizeof(vdiv_table_mV[0])); i++)
  {
    if (vdiv_table_mV[i] >= (uint16_t)need) { best = vdiv_table_mV[i]; break; }
    best = vdiv_table_mV[i];
  }

  if (best > cur)
  {
    return best;
  }
  else
  {
    if (vin_abs_mV < (float)cur * 1.8f) return best;
    return cur;
  }
}

static uint16_t vin_to_disp_adc(float vin_mV, uint16_t vdiv_mV)
{
  float k = ADC_MAX_F / (VDIVS_Y_F * (float)vdiv_mV);
  float s = ADC_MID_F + vin_mV * k;

  if (s < 0.0f) s = 0.0f;
  if (s > ADC_MAX_F) s = ADC_MAX_F;

  return (uint16_t)(s + 0.5f);
}

void OsziChannels_Init(uint16_t init_ch1_vdiv_mV, uint16_t init_ch2_vdiv_mV)
{
  ch1_vdiv_mV = init_ch1_vdiv_mV;
  ch2_vdiv_mV = init_ch2_vdiv_mV;

  ScopeChannelCfg c1 = { .vdiv_mV = ch1_vdiv_mV, .color = SCOPE_CH1_COLOR, .y_offset = 0 };
  ScopeChannelCfg c2 = { .vdiv_mV = ch2_vdiv_mV, .color = SCOPE_CH2_COLOR, .y_offset = 0 };

  ScopeWave_SetChannelCfg(0, c1);
  ScopeWave_SetChannelCfg(1, c2);
}


void OsziChannels_OnAdcPacket(uint16_t a1, uint16_t a2, uint16_t a3, uint16_t a4)
{
  float f1n = adc_fullscale_frac(a1);
  float f1w = adc_fullscale_frac(a2);
  float f2n = adc_fullscale_frac(a3);
  float f2w = adc_fullscale_frac(a4);

  ch1_sel = select_range(ch1_sel, (ch1_sel == R_NARROW) ? f1n : f1w);
  ch2_sel = select_range(ch2_sel, (ch2_sel == R_NARROW) ? f2n : f2w);

  float ch1_vin_mV = (ch1_sel == R_NARROW) ? adc_to_vin_mV(a1, CH1_NARROW_MAX_MV)
                                           : adc_to_vin_mV(a2, CH1_WIDE_MAX_MV);

  float ch2_vin_mV = (ch2_sel == R_NARROW) ? adc_to_vin_mV(a3, CH2_NARROW_MAX_MV)
                                           : adc_to_vin_mV(a4, CH2_WIDE_MAX_MV);

  float ch1_abs = ch1_vin_mV; if (ch1_abs < 0) ch1_abs = -ch1_abs;
  float ch2_abs = ch2_vin_mV; if (ch2_abs < 0) ch2_abs = -ch2_abs;

  ch1_vdiv_mV = pick_vdiv(ch1_vdiv_mV, ch1_abs);
  ch2_vdiv_mV = pick_vdiv(ch2_vdiv_mV, ch2_abs);

  uint16_t s1 = vin_to_disp_adc(ch1_vin_mV, ch1_vdiv_mV);
  uint16_t s2 = vin_to_disp_adc(ch2_vin_mV, ch2_vdiv_mV);

  ScopeWave_PushSample(0, s1);
  ScopeWave_PushSample(1, s2);

  ScopeChannelCfg c1 = { .vdiv_mV = ch1_vdiv_mV, .color = SCOPE_CH1_COLOR, .y_offset = 0 };
  ScopeChannelCfg c2 = { .vdiv_mV = ch2_vdiv_mV, .color = SCOPE_CH2_COLOR, .y_offset = 0 };

  ScopeWave_SetChannelCfg(0, c1);
  ScopeWave_SetChannelCfg(1, c2);

}

