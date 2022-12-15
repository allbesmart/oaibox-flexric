#ifndef KPM_V2_MEASUREMENT_BIN_INFORMATION_H
#define KPM_V2_MEASUREMENT_BIN_INFORMATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  enum {BIN_RANGE_INTEGER, BIN_RANGE_REAL} value;
  unsigned long int_value;
  double real_value;
  
} bin_range_value_t;


typedef struct {
  uint16_t bin_index;

  bin_range_value_t start_value;
  bin_range_value_t end_value;

} bin_distr_t;


typedef struct {
  size_t bin_x_lst_len;  // [1, 65535]
  bin_distr_t bin_x_lst;

  size_t bin_y_lst_len;  // [0, 65535]
  bin_distr_t bin_y_lst;

  size_t bin_z_lst_len;  // [0, 65535]
  bin_distr_t bin_z_lst;

} bin_range_def_t;



#ifdef __cplusplus
}
#endif

#endif