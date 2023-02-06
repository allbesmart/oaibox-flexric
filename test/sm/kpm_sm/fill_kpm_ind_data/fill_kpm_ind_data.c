#include <assert.h>

#include "fill_kpm_ind_data.h"
#include "fill_ind_hdr_frm_1.h"
#include "fill_ind_msg_frm_1.h"


void fill_kpm_ind_data(kpm_ric_indication_t* ind)
{
    assert(ind != NULL);
  
    // CHOOSE THE RIC STYLE TYPE [1..5]

    int ric_style_type = 1;

    switch (ric_style_type)
    {
      case 1:
        ind->kpm_ind_hdr.type = FORMAT_1_INDICATION_HEADER;
        fill_kpm_ind_hdr_frm_1(&ind->kpm_ind_hdr.kpm_ric_ind_hdr_format_1);
        break;
    
      default:
        assert(false && "Unknown Indication Header Type");
    }


    if (ric_style_type == 1 || ric_style_type == 2)
    {
        ind->kpm_ind_msg.type = FORMAT_1_INDICATION_MESSAGE;
        fill_kpm_ind_msg_frm_1(&ind->kpm_ind_msg.frm_1);
    }
    // else if (ric_style_type == 3)
    // {
    //     ind->kpm_ind_msg.type = FORMAT_2_INDICATION_MESSAGE;
    //     fill_kpm_ind_msg_frm_2(&ind->kpm_ind_msg.frm_2);
    // }
    // else if (ric_style_type == 4 || ric_style_type == 5)
    // {
    //     ind->kpm_ind_msg.type = FORMAT_3_INDICATION_MESSAGE;
    //     fill_kpm_ind_msg_frm_3(&ind->kpm_ind_msg.frm_3);
    // }
    else
    {
        assert(false && "Unknown Indication Message Type");
    }

}