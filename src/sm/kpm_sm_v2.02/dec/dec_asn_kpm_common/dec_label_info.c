#include <assert.h>

#include "dec_label_info.h"

#include "../../../../util/conversions.h"

label_info_lst_t kpm_dec_label_info_asn(const LabelInfoItem_t * label_info_asn)
{
    label_info_lst_t label_info = {0};
    // calloc(1, sizeof(label_info_lst_t));
    // assert (label_info != NULL && "Memory exhausted");

    // if (label_info_asn->measLabel.noLabel == 0)
    // {
    //     label_info->noLabel = TRUE_ENUM_VALUE;
 
    //     /* specification mentions that if 'noLabel' is included, other elements in the same datastructure 
    //     * 'LabelInfoItem_t' shall not be included.
    //     */

    //     return label_info;
    // }


    if (label_info_asn->measLabel.plmnID != NULL) {
        label_info.plmn_id = calloc(1, sizeof(*label_info.plmn_id));
        PLMNID_TO_MCC_MNC(label_info_asn->measLabel.plmnID, label_info.plmn_id->mcc, label_info.plmn_id->mnc, label_info.plmn_id->mnc_digit_len);
    }

    if (label_info_asn->measLabel.sliceID != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.fiveQI != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.qFI != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.qCI != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.qCImax != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.qCImin != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.aRPmax != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.aRPmin != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.bitrateRange != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.layerMU_MIMO != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.sUM != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.distBinX != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.distBinY != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.distBinZ != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.preLabelOverride != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.startEndInd != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.min != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.max != NULL) {
        assert(false && "not implemented");
    }
    if (label_info_asn->measLabel.avg != NULL) {
        assert(false && "not implemented");
    }

    return label_info;
}