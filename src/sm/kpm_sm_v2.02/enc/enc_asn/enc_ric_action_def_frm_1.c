#include <assert.h>

#include "enc_ric_action_def_frm_1.h"
#include "../../../../lib/e2sm_common_ie/enc_asn_sm_common/enc_cell_global_id.h"
#include "../enc_asn_kpm_common/enc_meas_info_frm_1.h"

#include "../../ie/asn/asn_constant.h"


E2SM_KPM_ActionDefinition_Format1_t * kpm_enc_action_def_frm_1_asn(const kpm_act_def_format_1_t * act_def_frm_1) {
    
    E2SM_KPM_ActionDefinition_Format1_t * act_def_frm_1_asn = calloc(1, sizeof(E2SM_KPM_ActionDefinition_Format1_t));
    assert (act_def_frm_1_asn != NULL && "Memory exhausted" );


    // 1. Measurement Information List Format 1 : [1, 65535]

    act_def_frm_1_asn->measInfoList = kpm_enc_meas_info_asn(act_def_frm_1->meas_info_lst, act_def_frm_1->meas_info_lst_len);


    // 2. Granularity Period : [1, 4294967295]
    
    act_def_frm_1_asn->granulPeriod = act_def_frm_1->gran_period_ms;
    assert(act_def_frm_1->gran_period_ms >= min_val_GranularityPeriod && act_def_frm_1->gran_period_ms <= max_val_GranularityPeriod);
     

    // 3. Cell Global ID - OPTIONAL
    if (act_def_frm_1->cell_global_id != NULL)
    {
      act_def_frm_1_asn->cellGlobalID = enc_cell_global_id_asn(act_def_frm_1->cell_global_id);
    }
    
    
    // 4. Measurement Bin Range Information List : [0, 65535]
    // not yet implemented in ASN, ask Mikel

    if (act_def_frm_1->meas_bin_info_lst != NULL) {
      assert(false && "Measurement Bin Range not yet implemented in ASN");
    }


    return act_def_frm_1_asn;
}