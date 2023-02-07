#include <assert.h>
#include "../../ie/asn/asn_constant.h"

#include "../../ie/kpm_data_ie/data/meas_type.h"
#include "../../ie/asn/MeasurementCondUEidItem.h"

#include "enc_meas_info_cond_ue.h"
#include "enc_matching_cond_frm_3.h"
MeasurementCondUEidList_t kpm_enc_meas_info_cond_ue_asn(const meas_info_cond_ue_lst_t * meas_cond_ue, const size_t meas_cond_ue_len)
{
    assert((meas_cond_ue_len <= maxnoofMeasurementInfo && meas_cond_ue_len >= 1) 
              && "Number of measures not allowed");
    
    MeasurementCondUEidList_t meas_cond_ue_asn={0};


    for (size_t i = 0; i<meas_cond_ue_len; i++)
    {
        MeasurementCondUEidItem_t * cond_ue_item = calloc(1, sizeof(MeasurementCondUEidItem_t));
        assert(cond_ue_item != NULL && "Memory exhausted");

        // Measurement Type
        const meas_type_t meas_type =  meas_cond_ue[i].meas_type;
        assert(meas_type.type == NAME_MEAS_TYPE || meas_type.type == ID_MEAS_TYPE);

        cond_ue_item->measType.present = meas_type.type == NAME_MEAS_TYPE 
                                             ? MeasurementType_PR_measName : MeasurementType_PR_measID; 
      
        if (cond_ue_item->measType.present == MeasurementType_PR_measName) {
          const size_t len = meas_cond_ue[i].meas_type.name.len;
          int ret = OCTET_STRING_fromBuf(&(cond_ue_item->measType.choice.measName), (char *)(meas_cond_ue[i].meas_type.name.buf), len);
          assert(ret == 0);
        }
        else {
          cond_ue_item->measType.choice.measID = meas_cond_ue[i].meas_type.id;
        }

        // Matching Condition
        assert((meas_cond_ue[i].matching_cond_lst_len <= maxnoofConditionInfo && meas_cond_ue[i].matching_cond_lst_len >= 1) 
                && "Number of labels not allowed");

        for (size_t j = 0; j<meas_cond_ue[i].matching_cond_lst_len; j++)
        {
            MatchingCondItem_t * matching_cond = kpm_enc_matching_cond_asn(&meas_cond_ue[i].matching_cond_lst[j]);
            int rc1 = ASN_SEQUENCE_ADD(&meas_cond_ue_asn.list, matching_cond);
            assert(rc1 == 0);
        }


        // UE_id Matched - OPTIONAL
        if (meas_cond_ue->ue_id_matched_lst_len != 0)
        {
            assert(false && "Non yet implemented");
        }
        else
        {
            cond_ue_item->matchingUEidList = NULL;
        }


        // UE_id Granularity Period - OPTIONAL
        if (meas_cond_ue->ue_id_gran_period_lst != NULL)
        {
            assert(false && "Not yet implemented, even in ASN.1");
        }


        int rc1 = ASN_SEQUENCE_ADD(&meas_cond_ue_asn.list, cond_ue_item);
        assert(rc1 == 0);
    }


    return meas_cond_ue_asn;

}
