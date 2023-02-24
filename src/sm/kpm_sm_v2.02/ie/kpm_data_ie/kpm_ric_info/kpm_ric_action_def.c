#include <assert.h>
#include <stdlib.h>

#include "kpm_ric_action_def.h"

void free_kpm_action_def(kpm_act_def_t * src)
{
    assert(src != NULL);

    switch (src->type)
    {
    case FORMAT_1_ACTION_DEFINITION:
        free_kpm_action_def_frm_1(&src->frm_1);
        break;

    case FORMAT_2_ACTION_DEFINITION:
        free_kpm_action_def_frm_2(&src->frm_2);
        break;

    case FORMAT_3_ACTION_DEFINITION:
        free_kpm_action_def_frm_3(&src->frm_3);
        break;
    
    // to be filled with other formats

    default:
        assert(false && "Unknown Action Definition Type");
    }


}



bool eq_kpm_action_def(kpm_act_def_t const * m0, kpm_act_def_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);
    
    assert(m0->type == m1->type);

    switch (m0->type)
    {
    case FORMAT_1_ACTION_DEFINITION:
        if (eq_kpm_action_def_frm_1(&m0->frm_1, &m1->frm_1) != true)
            return false;
        break;

    case FORMAT_2_ACTION_DEFINITION:
        if (eq_kpm_action_def_frm_2(&m0->frm_2, &m1->frm_2) != true)
            return false;
        break;

    case FORMAT_3_ACTION_DEFINITION:
        if (eq_kpm_action_def_frm_3(&m0->frm_3, &m1->frm_3) != true)
            return false;
        break;
    
    // to be filled with other formats

    default:
        assert(false && "Unknown Action Definition Type");
    }

    return true;
}
