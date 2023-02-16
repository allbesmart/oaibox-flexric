#ifndef NR_CGI_KPM_V2_H
#define NR_CGI_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "plmn_identity.h"

//  6.2.3.7  NR CGI

typedef struct{
  plmn_t plmn_id;  // 6.2.3.1
  uint64_t nr_cell_id; // bit string of 36 bits

} nr_cgi_t;


#ifdef __cplusplus
}
#endif

#endif

