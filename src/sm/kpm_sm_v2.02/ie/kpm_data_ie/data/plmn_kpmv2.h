#ifndef PLMN_KPM_V2_H
#define PLMN_KPM_V2_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint16_t mcc;
  uint16_t mnc;
  uint8_t mnc_digit_len;
} plmn_kpmv2_t;

bool eq_plmn_f1ap( plmn_kpmv2_t const* m0, plmn_kpmv2_t const* m1);

#endif
