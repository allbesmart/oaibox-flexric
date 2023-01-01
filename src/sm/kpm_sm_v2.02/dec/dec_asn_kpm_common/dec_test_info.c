#include <assert.h>

#include "dec_test_info.h"

test_info_lst_t * kpm_dec_test_info_asn(const TestCondInfo_t * test_info_asn)
{
    test_info_lst_t * test_info = calloc(1,sizeof(test_info_lst_t));
    assert(test_info != NULL && "Memory exhausted");

    switch (test_info_asn->testType.present)
    {
    case TestCond_Type_PR_gBR:
        test_info->test_cond_type = GBR_TEST_COND_TYPE;
        test_info->GBR = test_info_asn->testType.choice.gBR;
        break;
    
    case TestCond_Type_PR_aMBR:
        test_info->test_cond_type = AMBR_TEST_COND_TYPE;
        test_info->AMBR = test_info_asn->testType.choice.aMBR;
        break;

    case TestCond_Type_PR_isStat:
        test_info->test_cond_type = IsStat_TEST_COND_TYPE;
        test_info->IsStat = test_info_asn->testType.choice.isStat;
        break;

    case TestCond_Type_PR_isCatM:
        test_info->test_cond_type = IsCatM_TEST_COND_TYPE;
        test_info->IsCatM = test_info_asn->testType.choice.isCatM;
        break;

    case TestCond_Type_PR_rSRP:
        test_info->test_cond_type = DL_RSRQ_TEST_COND_TYPE;
        test_info->DL_RSRQ = test_info_asn->testType.choice.rSRQ;
        break;

    case TestCond_Type_PR_rSRQ:
        test_info->test_cond_type = AMBR_TEST_COND_TYPE;
        test_info->GBR = test_info_asn->testType.choice.aMBR;
        break;

    case TestCond_Type_PR_ul_rSRP:
        test_info->test_cond_type = UL_RSRP_TEST_COND_TYPE;
        test_info->UL_RSRP = test_info_asn->testType.choice.ul_rSRP;
        break;

    case TestCond_Type_PR_cQI:
        test_info->test_cond_type = CQI_TEST_COND_TYPE;
        test_info->CQI = test_info_asn->testType.choice.cQI;
        break;

    case TestCond_Type_PR_fiveQI:
        test_info->test_cond_type = fiveQI_TEST_COND_TYPE;
        test_info->fiveQI = test_info_asn->testType.choice.fiveQI;
        break;

    case TestCond_Type_PR_qCI:
        test_info->test_cond_type = QCI_TEST_COND_TYPE;
        test_info->QCI = test_info_asn->testType.choice.qCI;
        break;

    case TestCond_Type_PR_sNSSAI:
        test_info->test_cond_type = S_NSSAI_TEST_COND_TYPE;
        test_info->S_NSSAI = test_info_asn->testType.choice.sNSSAI;
        break;

    default:
        assert(false && "Condition type out of the range");
        break;
    }

    if (test_info_asn->testExpr != NULL)
    {
        assert(false && "Test Condition not yet implemented");
    }

    if (test_info_asn->testValue != NULL)
    {
        assert(false && "Test Condition Value not yet implemented");
    }

    return &test_info;
}