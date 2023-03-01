#include <assert.h>

#include "meas_info_frm_1_lst.h"

void free_meas_info_frm_1(meas_info_format_1_lst_t* src)
{
    assert(src != NULL);

    for (size_t i = 0; i<src->label_info_lst_len; i++)
      free_label_info(&src->label_info_lst[i]);
    free(src->label_info_lst);
        
    if (src->meas_type.type == NAME_MEAS_TYPE)
      free_byte_array(src->meas_type.name);

}

bool eq_meas_info_frm_1(meas_info_format_1_lst_t const * m0, meas_info_format_1_lst_t const * m1)
{
    assert(m0 != NULL);
    assert(m1 != NULL);

    // Meas Type

    if (eq_meas_type(&m0->meas_type, &m1->meas_type) != true)
        return false;


    // Label Info

    if (m0->label_info_lst_len != m1->label_info_lst_len)
      return false;
    
    for (size_t i = 0; i < m0->label_info_lst_len; i++)
    {
      if (eq_label_info(&m0->label_info_lst[i], &m1->label_info_lst[i]) != true)
        return false;
    }

    return true;
}
