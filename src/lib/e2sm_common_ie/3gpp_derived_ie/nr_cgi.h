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
  uint8_t nr_cell_id[5]; // bit string of 36 bits

} nr_cgi_t;

bool eq_nr_cgi(nr_cgi_t const* m0, nr_cgi_t const* m1);

void free_nr_cgi(nr_cgi_t* src);


#ifdef __cplusplus
}
#endif

#endif

// done