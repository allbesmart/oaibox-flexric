#include <assert.h>

#include "../../../util/conversions.h"

#include "enc_global_enb_id.h"

GlobalENB_ID_t * enc_global_enb_id_asn(const global_enb_id_t * global_enb_id)
{
    GlobalENB_ID_t * global_enb_id_asn = calloc(1, sizeof(GlobalENB_ID_t));
    assert (global_enb_id_asn != NULL && "Memory exhausted");


    // PLMN Identity
    MCC_MNC_TO_PLMNID(global_enb_id->plmn_id.mcc, global_enb_id->plmn_id.mnc, global_enb_id->plmn_id.mnc_digit_len, &global_enb_id_asn->pLMNIdentity);


    // eNB Type

    switch (global_enb_id->type)
    {
    case MACRO_ENB_TYPE_ID:

        global_enb_id_asn->eNB_ID.present = ENB_ID_PR_macro_eNB_ID;
        MACRO_ENB_ID_TO_BIT_STRING(global_enb_id->macro_enb_id, &global_enb_id_asn->eNB_ID.choice.macro_eNB_ID);
        break;
    
    case HOME_ENB_TYPE_ID:

        global_enb_id_asn->eNB_ID.present = ENB_ID_PR_home_eNB_ID;
        HOME_ENB_ID_TO_BIT_STRING(global_enb_id->home_enb_id, &global_enb_id_asn->eNB_ID.choice.home_eNB_ID);
        break;

    case SHORT_MACRO_ENB_TYPE_ID:

        global_enb_id_asn->eNB_ID.present = ENB_ID_PR_short_Macro_eNB_ID;
        SHORT_MACRO_ENB_ID_TO_BIT_STRING(global_enb_id->short_macro_enb_id, &global_enb_id_asn->eNB_ID.choice.short_Macro_eNB_ID);
        break;

    case LONG_MACRO_ENB_TYPE_ID:

        global_enb_id_asn->eNB_ID.present = ENB_ID_PR_long_Macro_eNB_ID;
        LONG_MACRO_ENB_ID_TO_BIT_STRING(global_enb_id->long_macro_enb_id, &global_enb_id_asn->eNB_ID.choice.long_Macro_eNB_ID);
        break;

    default:
        assert(false && "Unknown eNB Type");
    }


    return global_enb_id_asn;
}
