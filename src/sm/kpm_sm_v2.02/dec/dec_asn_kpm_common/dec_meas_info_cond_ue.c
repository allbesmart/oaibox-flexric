#include <assert.h>
#include "../../ie/asn/asn_constant.h"

#include "dec_meas_info_cond_ue.h"
#include "../../ie/asn/MeasurementCondUEidItem.h"
#include "../../ie/asn/MatchingUEidList.h"
#include "../../ie/asn/MatchingUEidItem.h"

#include "../dec_asn_kpm_common/dec_matching_cond_frm_3.h"
#include "../../../../lib/e2sm_common_ie/dec_asn_sm_common/dec_ue_id.h"

meas_info_cond_ue_lst_t * kpm_dec_meas_info_cond_ue_asn(const MeasurementCondUEidList_t meas_cond_ue_asn, const size_t meas_cond_ue_len)
{
    meas_info_cond_ue_lst_t * meas_cond_ue = calloc(meas_cond_ue_len, sizeof(meas_info_cond_ue_lst_t));
    assert(meas_cond_ue != NULL && "Memory exhausted");

    for (size_t i = 0; i<meas_cond_ue_len; i++)
    {
        // const MeasurementCondUEidItem_t * cond_ue_item_asn = &meas_cond_ue_asn.list.array[i][0];

        // Measurement Type
        assert(meas_cond_ue_asn.list.array[i]->measType.present == MeasurementType_PR_measName || meas_cond_ue_asn.list.array[i]->measType.present == MeasurementType_PR_measID);

        switch (meas_cond_ue_asn.list.array[i]->measType.present)
        {
        case MeasurementType_PR_measName:
            meas_cond_ue[i].meas_type.type = NAME_MEAS_TYPE;
            meas_cond_ue[i].meas_type.name.buf = calloc(meas_cond_ue_asn.list.array[i]->measType.choice.measName.size + 1, sizeof(char));
            assert(meas_cond_ue[i].meas_type.name.buf != NULL && "Memory exhausted");
            memcpy(meas_cond_ue[i].meas_type.name.buf, meas_cond_ue_asn.list.array[i]->measType.choice.measName.buf, meas_cond_ue_asn.list.array[i]->measType.choice.measName.size);
            meas_cond_ue[i].meas_type.name.len = meas_cond_ue_asn.list.array[i]->measType.choice.measName.size;
            break;
        
        case MeasurementType_PR_measID:
            meas_cond_ue[i].meas_type.type = ID_MEAS_TYPE;
            meas_cond_ue[i].meas_type.id = meas_cond_ue_asn.list.array[i]->measType.choice.measID;
            break;

        default:
            assert(0!=0 && "Unknown Measurement Type" );
        }


        // Matching Condition
        meas_cond_ue[i].matching_cond_lst_len = meas_cond_ue_asn.list.array[i]->matchingCond.list.count;
        assert(meas_cond_ue[i].matching_cond_lst_len >= 1 && meas_cond_ue[i].matching_cond_lst_len <= maxnoofConditionInfo);

        meas_cond_ue[i].matching_cond_lst = calloc(meas_cond_ue[i].matching_cond_lst_len, sizeof(matching_condition_format_3_lst_t));
        assert(meas_cond_ue[i].matching_cond_lst != NULL && "Memory exhausted");

        for (size_t j = 0; j<meas_cond_ue[i].matching_cond_lst_len; j++)
        {
            meas_cond_ue[i].matching_cond_lst[j] = kpm_dec_matching_cond_asn(meas_cond_ue_asn.list.array[i]->matchingCond.list.array[j]);
        }


        // UE_id Matched - OPTIONAL
        if (meas_cond_ue_asn.list.array[i]->matchingUEidList != NULL)
        {
            meas_cond_ue[i].ue_id_matched_lst_len = meas_cond_ue_asn.list.array[i]->matchingUEidList->list.count;
            assert(meas_cond_ue[i].ue_id_matched_lst_len >= 1 && meas_cond_ue[i].ue_id_matched_lst_len <= maxnoofUEID);

            meas_cond_ue[i].ue_id_matched_lst = calloc(meas_cond_ue[i].ue_id_matched_lst_len, sizeof(ue_id_t));
            assert(meas_cond_ue[i].ue_id_matched_lst != NULL && "Memory exhausted");

            for (size_t j = 0; j<meas_cond_ue[i].ue_id_matched_lst_len; j++)
            {
                meas_cond_ue[i].ue_id_matched_lst[j] = dec_ue_id_asn(&meas_cond_ue_asn.list.array[i]->matchingUEidList->list.array[j]->ueID);
            }
        }
        else
        {
            meas_cond_ue[i].ue_id_matched_lst_len = 0;
        }


        // UE_id Granularity Period - OPTIONAL
        // not yet implemented in ASN.1

    }


    return meas_cond_ue;
}
