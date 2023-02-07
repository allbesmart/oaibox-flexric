#include <assert.h>
#include <stdlib.h>
#include "../../ap/ie/asn/OCTET_STRING.h"
#include "../../../../util/conversions.h"

#include "../../../sm/kpm_sm_v2.02/ie/asn/CGI.h"
#include "../../../sm/kpm_sm_v2.02/ie/asn/NR-CGI.h"
#include "../../../sm/kpm_sm_v2.02/ie/asn/EUTRA-CGI.h"

#include "enc_cell_global_id.h"


CGI_t * enc_cell_global_id_asn(const cell_global_id_t * cell_global_id)
{
    assert(cell_global_id->type == NR_CGI_RAT_TYPE || cell_global_id->type == EUTRA_CGI_RAT_TYPE);

    CGI_t * cell_global_id_asn = calloc(1, sizeof(CGI_t));
    assert(cell_global_id_asn != NULL && "Memory exhausted");


    switch (cell_global_id->type)
    {
      case NR_CGI_RAT_TYPE:
        {
        cell_global_id_asn->present = CGI_PR_nR_CGI;
        cell_global_id_asn->choice.nR_CGI = calloc(1, sizeof(NR_CGI_t));
        PLMNIdentity_t * plmnID = calloc(1, sizeof(cell_global_id_asn->choice.nR_CGI->pLMNIdentity));
        plmnID = &cell_global_id_asn->choice.nR_CGI->pLMNIdentity;

        MCC_MNC_TO_PLMNID(cell_global_id->nr_cgi.plmn_id.mcc, cell_global_id->nr_cgi.plmn_id.mnc, cell_global_id->nr_cgi.plmn_id.mnc_digit_len, plmnID);
        NR_CELL_ID_TO_BIT_STRING(cell_global_id->nr_cgi.nr_cell_id, &cell_global_id_asn->choice.nR_CGI->nRCellIdentity);
        break;
      }


      case EUTRA_CGI_RAT_TYPE:{
        cell_global_id_asn->present = CGI_PR_eUTRA_CGI;
        cell_global_id_asn->choice.eUTRA_CGI = calloc(1, sizeof(EUTRA_CGI_t));
        PLMNIdentity_t * plmnID = calloc(1, sizeof(cell_global_id_asn->choice.eUTRA_CGI->pLMNIdentity));
        plmnID = &cell_global_id_asn->choice.eUTRA_CGI->pLMNIdentity;

        MCC_MNC_TO_PLMNID(cell_global_id->eutra.plmn_id.mcc, cell_global_id->eutra.plmn_id.mnc, cell_global_id->eutra.plmn_id.mnc_digit_len, plmnID);
        EUTRA_CELL_ID_TO_BIT_STRING(cell_global_id->eutra.eutra_cell_id, &cell_global_id_asn->choice.eUTRA_CGI->eUTRACellIdentity);

        break;
        }
      default:
          assert(0!=0 && "Unknown type");
    }

    return cell_global_id_asn;

}
