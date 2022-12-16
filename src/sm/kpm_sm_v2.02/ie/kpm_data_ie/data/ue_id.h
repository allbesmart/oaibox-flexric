#ifndef UE_ID_KPM_V2_H
#define UE_ID_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "gnb_ue_id.h"
#include "gnb_du.h"
#include "gnb_cu_up.h"
#include "ng_enb.h"
#include "ng_enb_du.h"
#include "en_gnb.h"
#include "enb.h"

typedef enum{
  GNB_UE_ID_KPMV2,
	GNB_DU_UE_ID_KPMV2,
	GNB_CU_UP_UE_ID_KPMV2,
	NG_ENB_UE_ID_KPMV2,
	NG_ENB_DU_UE_ID_KPMV2,
	EN_GNB_UE_ID_KPMV2,
} ue_id_kpmv2_e; 

typedef struct {
  ue_id_kpmv2_e type;
  union{
    gnb_ue_id_t gnb_ue_id;
    gnb_du_t  gnb_du;
    gnb_cu_up_t  gnb_cu_up;
    ng_enb_t ng_enb;
    ng_enb_du_t  ng_enb_du;
    en_gnb_t  en_gnb;
    enb_t enb;
  };
	
} ue_id_kpmv2_t;

#ifdef __cplusplus
}
#endif

#endif

// to finish