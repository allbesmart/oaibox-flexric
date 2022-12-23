#include <assert.h>
#include <stdlib.h>
#include "../../ap/ie/asn/OCTET_STRING.h"
#include "../../../../util/conversions.h"

#include "enc_cell_global_id.h"


CGI_t * enc_cell_global_id_asn(const cell_global_id_t * cell_global_id)
{
    assert(cell_global_id->type == NR_CGI_RAT_TYPE || cell_global_id->type == EUTRA_CGI_RAT_TYPE);

    CGI_t * cell_global_id_asn = calloc(1, sizeof(CGI_t));
    assert(cell_global_id_asn != NULL && "Memory exhausted");

    int ret;

    switch (cell_global_id->type)
    {
      case NR_CGI_RAT_TYPE:
        cell_global_id_asn->present = CGI_PR_nR_CGI;
        cell_global_id_asn->choice.nR_CGI = calloc(1, sizeof(NR_CGI_t));


        ret = OCTET_STRING_fromBuf( &cell_global_id_asn->choice.nR_CGI->pLMNIdentity, 
                                      (const char *)cell_global_id->nr_cgi.plmn_id, 
                                      action_def->pLMNIdentity.len);
        assert(ret == 0);
        NR_CELL_ID_TO_BIT_STRING(cell_global_id->nr_cgi.nr_cell_id, &cell_global_id_asn->choice.nR_CGI.nr);

      case EUTRA_CGI_RAT_TYPE:
        cell_global_id_asn->present = CGI_PR_eUTRA_CGI;
        ret = OCTET_STRING_fromBuf(&cell_global_id_asn->choice.eUTRA_CGI->pLMNIdentity, 
                                   (const char *)action_def->pLMNIdentity.buf, 
                                   action_def->pLMNIdentity.len);
        assert(ret == 0);
        NR_CELL_ID_TO_BIT_STRING(action_def->eUTRACellIdentity, &cell_global_id_asn->choice.eUTRA_CGI->eUTRACellIdentity);
    }

    return &cell_global_id_asn;  // ask Mikel about reference

    // to finish


}