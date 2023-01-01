#include <assert.h>
#include "../../ie/asn/asn_constant.h"

#include "dec_meas_info_cond_ue.h"
#include "../../ie/asn/MeasurementCondUEidItem.h"
#include "dec_asn_kpm_common/dec_matching_cond_frm_3.h"

meas_info_cond_ue_lst_t * kpm_dec_meas_info_cond_ue_asn(const MeasurementCondUEidList_t meas_cond_ue_asn, const size_t meas_cond_ue_len)
{
    meas_info_cond_ue_lst_t * meas_cond_ue = calloc(1,sizeof(meas_info_cond_ue_lst_t));
    assert(meas_cond_ue != NULL && "Memory exhausted");

    for (size_t i = 0; i<meas_cond_ue_len; i++)
    {
        MeasurementCondUEidItem_t * cond_ue_item_asn = meas_cond_ue_asn.list.array[i];

        // Measurement Type
        assert(cond_ue_item_asn->measType.present == MeasurementType_PR_measName || cond_ue_item_asn->measType.present == MeasurementType_PR_measID);

        switch (cond_ue_item_asn->measType.present)
        {
        case MeasurementType_PR_measName:
            meas_cond_ue[i].meas_type.type = NAME_MEAS_TYPE;
            meas_cond_ue[i].meas_type.name.buf = calloc(cond_ue_item_asn->measType.choice.measName.size + 1, sizeof(char));
            assert(meas_cond_ue[i].meas_type.name.buf != NULL && "Memory exhausted");
            memcpy(meas_cond_ue[i].meas_type.name.buf, cond_ue_item_asn->measType.choice.measName.buf, cond_ue_item_asn->measType.choice.measName.size);
            meas_cond_ue[i].meas_type.name.len = cond_ue_item_asn->measType.choice.measName.size;
            break;
        
        case MeasurementType_PR_measID:
            meas_cond_ue[i].meas_type.type = ID_MEAS_TYPE;
            meas_cond_ue[i].meas_type.id = cond_ue_item_asn->measType.choice.measID;
            break;
        }


        // Matching Condition
        meas_cond_ue[i].matching_cond_lst_len = cond_ue_item_asn->matchingCond.list.count;
        assert(meas_cond_ue[i].matching_cond_lst_len >= 1 && meas_cond_ue[i].matching_cond_lst_len <= maxnoofConditionInfo);

        for (size_t j = 0; j<meas_cond_ue[i].matching_cond_lst_len; j++)
        {
            meas_cond_ue[i].matching_cond_lst[j] = *kpm_dec_matching_cond_asn(&cond_ue_item_asn->matchingCond.list.array[j]);
        }


        // UE_id Matched - OPTIONAL
        if (cond_ue_item_asn->matchingUEidList != NULL)
        {
            assert(false && "Non yet implemented");
        }
        else
        {
            meas_cond_ue[i].ue_id_matched_lst_len = 0;
        }


        // UE_id Granularity Period - OPTIONAL
        // not yet implemented in ASN.1

    }


    return &meas_cond_ue;
}