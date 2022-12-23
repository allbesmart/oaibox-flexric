#ifndef EUTRA_CGI_KPM_V2_H
#define EUTRA_CGI_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "plmn_identity.h"


//  6.2.3.11  E-UTRA CGI
typedef struct{

  plmn_t plmn_id; // 6.2.3.1
  uint8_t eutra_cell_id[4]; // bit string of 28 bits

} eutra_cgi_t ;

#ifdef __cplusplus
}
#endif

#endif

// done