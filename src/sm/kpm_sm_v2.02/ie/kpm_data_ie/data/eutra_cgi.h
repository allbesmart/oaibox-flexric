#ifndef EUTRA_CGI_KPM_V2_H
#define EUTRA_CGI_KPM_V2_H

#include <stdint.h>
#include "../../../../../util/byte_array.h"

typedef struct{

  byte_array_t plmn_id; 
  uint8_t eutra_cell_id[4]; // bit string of 28

} eutra_cgi_t ;

#endif

