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
    
    // to be filled with other formats

    default:
        assert(false && "Unknown Action Definition Type");
    }

    return true;
}