#ifndef GUAMI_KPMV2_H
#define GUAMI_KPMV2_H

#include <stdint.h>

typedef struct{

  // Mandatory
  // PLMN Identity 6.2.3.1
  uint8_t plmn_id[3];

  // Mandatory
  // AMF Region ID BIT STRING (SIZE(8
  uint8_t amf_region_id;
  // Mandatory
  //  AMF Set ID BIT STRING (SIZE(10))
  uint16_t amf_set_id:10;

  // Mandatory
  // AMF Pointer BIT STRING (SIZE(6))
  uint16_t amf_ptr:6;

} guami_t;

#endif


