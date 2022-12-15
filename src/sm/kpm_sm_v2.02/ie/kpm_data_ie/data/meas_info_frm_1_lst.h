#ifndef KPM_V2_MEASUREMENT_INFORMATIOIN_FORMAT_1_LIST_H
#define KPM_V2_MEASUREMENT_INFORMATIOIN_FORMAT_1_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "label_info_lst.h"
#include "meas_type.h"

typedef enum{
  NAME_MEAS_TYPE,
  ID_MEAS_TYPE ,

  END_MEAS_TYPE

} meas_type_e ;


typedef struct{

  meas_type_e type;
  union{
    byte_array_t name; // 8.3.9
    uint16_t id; // 8.3.10
  };
 
  size_t label_info_lst_len;
  label_info_lst_t* label_info_lst;  // list implemented as array having label_info_lst_len items

} meas_info_format_1_lst_t;

// **************************
//  maybe this way is better ???

typedef struct{

  meas_type_t meas_type;
 
  size_t label_info_lst_len;
  label_info_lst_t* label_info_lst;  // list implemented as array having label_info_lst_len items

} meas_info_format_1_lst_t;



#ifdef __cplusplus
}
#endif

#endif