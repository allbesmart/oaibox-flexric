#include <assert.h>

#include "../../../util/conversions.h"

#include "dec_global_ng_enb.h"

global_ng_enb_id_t * dec_global_ng_enb_asn(const GlobalNgENB_ID_t * global_ng_enb_id_asn)
{
    global_ng_enb_id_t * global_ng_enb_id = calloc(1, sizeof(global_ng_enb_id_t));
    assert (global_ng_enb_id != NULL && "Memory exhausted");


    // PLMN Identity
    PLMNID_TO_MCC_MNC(&global_ng_enb_id_asn->pLMNIdentity, global_ng_enb_id->plmn_id.mcc, global_ng_enb_id->plmn_id.mnc, global_ng_enb_id->plmn_id.mnc_digit_len);

    // NG eNB Type

    switch (global_ng_enb_id_asn->ngENB_ID.present)
    {
    case NgENB_ID_PR_macroNgENB_ID:
        global_ng_enb_id->type = MACRO_NG_ENB_TYPE_ID;
        BIT_STRING_TO_MACRO_NG_ENB_ID(&global_ng_enb_id_asn->ngENB_ID.choice.macroNgENB_ID, global_ng_enb_id->macro_ng_enb_id);
        break;
    
    case NgENB_ID_PR_shortMacroNgENB_ID:
        global_ng_enb_id->type = SHORT_MACRO_NG_ENB_TYPE_ID;
        BIT_STRING_TO_SHORT_MACRO_NG_ENB_ID(&global_ng_enb_id_asn->ngENB_ID.choice.shortMacroNgENB_ID, global_ng_enb_id->short_macro_ng_enb_id);
        break;

    case NgENB_ID_PR_longMacroNgENB_ID:
        global_ng_enb_id->type = LONG_MACRO_NG_ENB_TYPE_ID;
        BIT_STRING_TO_LONG_MACRO_NG_ENB_ID(&global_ng_enb_id_asn->ngENB_ID.choice.longMacroNgENB_ID, global_ng_enb_id->long_macro_ng_enb_id);
        break;

    default:
        assert(false && "Unknown NG eNB Type");
    }


    return global_ng_enb_id;
}
