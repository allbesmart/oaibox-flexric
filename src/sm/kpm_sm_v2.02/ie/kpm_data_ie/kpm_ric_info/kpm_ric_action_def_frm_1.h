#ifndef KPM_V2_ACTION_DEFINITION_FORMAT_1_H
#define KPM_V2_ACTION_DEFINITION_FORMAT_1_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "../data/meas_info_frm_1_lst.h"
#include "../data/meas_bin_range_info_lst.h"

typedef enum { 
  KPMV2_CELL_ID_CHOICE_NOTHING = 0, 
  KPMV2_CELL_ID_CHOICE_NR_CGI, 
  KPMV2_CELL_ID_CHOICE_EUTRA_CGI 
} cell_global_id_t;
/*
ask Mikel: it is not defined like this in spec
=> yes, he agreed, i need to redo this
*/ 


// 8.2.1.2.1
typedef struct{

  size_t meas_info_lst_len;  // [1, 65535]
  meas_info_format_1_lst_t *meas_info_lst; 
 
  uint32_t gran_period_ms;  // 8.3.8 [0, 4294967295]

  cell_global_id_t* cell_global_id; /* OPTIONAL - 8.3.20 */

  size_t meas_bin_range_info_lst_len; // [0, 65535]
  meas_bin_range_info_lst_t *meas_bin_info_lst;


} kpm_act_def_format_1_t ;

void free_kpm_action_def(kpm_act_def_format_1_t* src);

#ifdef __cplusplus
}
#endif

#endif