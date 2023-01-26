#include <assert.h>
#include <stdlib.h>
#include "../../ap/ie/asn/OCTET_STRING.h"
#include "../../../../util/conversions.h"

#include "../../../sm/kpm_sm_v2.02/ie/asn/NR-CGI.h"
#include "../../../sm/kpm_sm_v2.02/ie/asn/EUTRA-CGI.h"

#include "enc_cell_global_id.h"


cell_global_id_t * dec_cell_global_id_asn(const CGI_t * cell_global_id_asn)
{
    assert(cell_global_id_asn->present == CGI_PR_nR_CGI || cell_global_id_asn->present == CGI_PR_eUTRA_CGI);

    cell_global_id_t * cell_global_id = calloc(1, sizeof(cell_global_id_t));
    assert(cell_global_id != NULL && "Memory exhausted");

    switch (cell_global_id_asn->present)
    {
    case CGI_PR_nR_CGI:
        cell_global_id->type = NR_CGI_RAT_TYPE;
        
        PLMNIdentity_t * plmnID = calloc(1, sizeof(cell_global_id_asn->choice.nR_CGI->pLMNIdentity));
        plmnID = &cell_global_id_asn->choice.nR_CGI->pLMNIdentity;

        PLMNID_TO_MCC_MNC(plmnID, cell_global_id->nr_cgi.plmn_id.mcc, cell_global_id->nr_cgi.plmn_id.mnc, cell_global_id->nr_cgi.plmn_id.mnc_digit_len);
        BIT_STRING_TO_NR_CELL_IDENTITY(&cell_global_id_asn->choice.nR_CGI->nRCellIdentity, cell_global_id->nr_cgi.nr_cell_id);

        break;
    
    case CGI_PR_eUTRA_CGI:
        cell_global_id->type = EUTRA_CGI_RAT_TYPE;

        PLMNIdentity_t * plmnID = calloc(1, sizeof(cell_global_id_asn->choice.eUTRA_CGI->pLMNIdentity));
        plmnID = &cell_global_id_asn->choice.eUTRA_CGI->pLMNIdentity;

        PLMNID_TO_MCC_MNC(plmnID, cell_global_id->eutra.plmn_id.mcc, cell_global_id->eutra.plmn_id.mnc, cell_global_id->eutra.plmn_id.mnc_digit_len);
        BIT_STRING_TO_CELL_IDENTITY(&cell_global_id_asn->choice.eUTRA_CGI->eUTRACellIdentity, cell_global_id->eutra.eutra_cell_id);
        break;
    }

    return &cell_global_id;
}

// to finish, check conversion of cell identity