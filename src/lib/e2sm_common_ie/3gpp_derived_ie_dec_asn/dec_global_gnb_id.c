#include <assert.h>

#include "../../../../util/conversions.h"

#include "dec_global_gnb_id.h"

global_gnb_id_t * dec_global_gnb_id_asn(const GlobalGNB_ID_t * global_gnb_id_asn)
{
    global_gnb_id_t * global_gnb_id = calloc(1, sizeof(global_gnb_id_t));
    assert (global_gnb_id != NULL && "Memory exhausted");


    // PLMN Identity
    PLMNID_TO_MCC_MNC(&global_gnb_id_asn->pLMNIdentity, global_gnb_id->plmn_id.mcc, global_gnb_id->plmn_id.mnc, global_gnb_id->plmn_id.mnc_digit_len);


    // gNB Type
    if (global_gnb_id_asn->gNB_ID.present == GNB_ID_PR_gNB_ID)
    {
        global_gnb_id->type = GNB_TYPE_ID;
        BIT_STRING_TO_MACRO_GNB_ID(&global_gnb_id_asn->gNB_ID.choice.gNB_ID, global_gnb_id->gnb_id);
    }
    else
    {
        assert(false && "Unknown gNB Type");
    }
    

    return &global_gnb_id;
}