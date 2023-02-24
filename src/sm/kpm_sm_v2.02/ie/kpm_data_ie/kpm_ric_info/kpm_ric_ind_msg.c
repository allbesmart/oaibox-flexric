#include <assert.h>
#include <stdlib.h>

#include "kpm_ric_ind_msg.h"

void free_kpm_ind_msg(kpm_ind_msg_t * src)
{
    assert(src != NULL);

    switch (src->type)
    {
    case FORMAT_1_INDICATION_MESSAGE:
        free_kpm_ind_msg_frm_1(&src->frm_1);
        break;

    case FORMAT_2_INDICATION_MESSAGE:
        free_kpm_ind_msg_frm_2(&src->frm_2);
        break;
    
    // to be filled with other formats

    default:
        assert(false && "Unknown Indication Message Type");
    }
}

bool eq_kpm_ind_msg(kpm_ind_msg_t const * m0, kpm_ind_msg_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);
    
    assert(m0->type == m1->type);

    switch (m0->type)
    {
    case FORMAT_1_INDICATION_MESSAGE:
        if (eq_kpm_ind_msg_frm_1(&m0->frm_1, &m1->frm_1) != true)
            return false;
        break;
    
    case FORMAT_2_INDICATION_MESSAGE:
        if (eq_kpm_ind_msg_frm_2(&m0->frm_2, &m1->frm_2) != true)
            return false;
        break;

    default:
        assert(false && "Unknown Indication Message Type");
    }

    return true;
}
