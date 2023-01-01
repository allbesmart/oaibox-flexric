#include <assert.h>
#include "../../ie/asn/asn_constant.h"

#include "dec_ric_ind_msg_frm_3.h"
#include "dec_ric_ind_msg_frm_1.h"
#include "../../ie/asn/UEMeasurementReportItem.h"

kpm_ind_msg_format_3_t kpm_dec_ind_msg_frm_3_asn(const E2SM_KPM_IndicationMessage_Format3_t * ind_msg_asn)
{
    kpm_ind_msg_format_3_t ind_msg = {0};


    // List of UE Measurement Reports
    ind_msg.ue_meas_report_lst_len = ind_msg_asn->ueMeasReportList.list.count;
    assert(ind_msg.ue_meas_report_lst_len >= 1 && ind_msg.ue_meas_report_lst_len <= maxnoofUEMeasReport);

    for (size_t i = 0; i<ind_msg.ue_meas_report_lst_len; i++)
    {
        UEMeasurementReportItem_t * ue_item_asn = ind_msg_asn->ueMeasReportList.list.array[i];

        /* to be filled : UE_id */

        ind_msg.meas_report_per_ue->ind_msg_format_1 = kpm_dec_ind_msg_frm_1_asn(&ue_item_asn->measReport);

    }

    return ind_msg;
}