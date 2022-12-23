#ifndef UE_ID_H
#define UE_ID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "../3gpp_derived_ie/gnb.h"
#include "../3gpp_derived_ie/gnb_du.h"
#include "../3gpp_derived_ie/gnb_cu_up.h"
#include "../3gpp_derived_ie/ng_enb.h"
#include "../3gpp_derived_ie/ng_enb_du.h"
#include "../3gpp_derived_ie/en_gnb.h"
#include "../3gpp_derived_ie/enb.h"

typedef enum{
  GNB_UE_ID,
	GNB_DU_UE_ID,
	GNB_CU_UP_UE_ID,
	NG_ENB_UE_ID,
	NG_ENB_DU_UE_ID,
	EN_GNB_UE_ID,
  E_NB_UE_ID,

  END_UE_ID

} ue_id_e; 

typedef struct {
  ue_id_e type;
  union{
    gnb_t gnb;
    gnb_du_t  gnb_du;
    gnb_cu_up_t  gnb_cu_up;
    ng_enb_t ng_enb;
    ng_enb_du_t  ng_enb_du;
    en_gnb_t  en_gnb;
    enb_t enb;
  };
	
} ue_id_t;

#ifdef __cplusplus
}
#endif

#endif

// done