#include <assert.h>

#include "dec_matching_cond_frm_3.h"
#include "dec_label_info.h"
#include "dec_test_info.h"


matching_condition_format_3_lst_t kpm_dec_matching_cond_asn(const MatchingCondItem_t * matching_cond_asn)
{
    matching_condition_format_3_lst_t matching_cond={0};

    if (matching_cond_asn->present == MatchingCondItem_PR_measLabel)
    {
        matching_cond.cond_type = LABEL_INFO;
        LabelInfoItem_t * labels = calloc(1, sizeof(LabelInfoItem_t));
        labels->measLabel = *matching_cond_asn->choice.measLabel;
        matching_cond.label_info_lst = *kpm_dec_label_info_asn(labels);
    }
    else if (matching_cond_asn->present == MatchingCondItem_PR_testCondInfo)
    {
        matching_cond.cond_type = TEST_INFO;
        matching_cond.test_info_lst = *kpm_dec_test_info_asn(matching_cond_asn->choice.testCondInfo);
    }
    else {
        assert(false && "Condition type out of the range");
    }
    

    // logical_OR not yet implemented in ASN.1

    return matching_cond;
}