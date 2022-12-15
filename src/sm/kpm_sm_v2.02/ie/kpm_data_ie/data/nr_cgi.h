#ifndef NR_CGI_KPM_V2_H
#define NR_CGI_KPM_V2_H

#include "plmn_kpmv2.h"

#include <stdbool.h>
#include <stdint.h>

// 
typedef struct{
  uint8_t plmn_id[3];
  uint64_t nr_cell_id; // 36 bits
} nr_cgi_t;

bool eq_nr_cgi(nr_cgi_t const* m0, nr_cgi_t const* m1);

void free_nr_cgi(nr_cgi_t* src);

#endif

