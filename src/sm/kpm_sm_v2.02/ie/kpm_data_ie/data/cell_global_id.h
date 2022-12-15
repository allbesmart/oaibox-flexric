#ifndef CELL_GLOBAL_ID_KPM_V2
#define CELL_GLOBAL_ID_KPM_V2

#include "nr_cgi.h"
#include "eutra_cgi.h"

typedef enum {
	NR_CGI_RAT_TYPE,
	EUTRA_CGI_RAT_TYPE
} rat_type_e; 


typedef struct{
  // CHOICE RAT type
  // Mandatory
  rat_type_e type;

  union{
    nr_cgi_t nr_cgi; // 6.2.3.7
    eutra_cgi_t eutra; // 6.2.3.11
  };

} cell_global_id_t;





#endif
