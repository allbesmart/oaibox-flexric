#include <assert.h>

#include "enc_test_info.h"

TestCondInfo_t * kpm_enc_test_info_asn(const test_info_lst_t * test_info)
{
    TestCondInfo_t * test_info_asn = calloc(1, sizeof(TestCondInfo_t));
    assert(test_info_asn != NULL && "Memory exhausted");


    if (test_info->test_cond_type == GBR_TEST_COND_TYPE) 
    {
        test_info_asn->testType.present = TestCond_Type_PR_gBR;
        test_info_asn->testType.choice.gBR = test_info->GBR;
    }
    else if (test_info->test_cond_type == AMBR_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_aMBR;
        test_info_asn->testType.choice.aMBR = test_info->AMBR;
    }
    else if (test_info->test_cond_type == IsStat_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_isStat;
        test_info_asn->testType.choice.isStat = test_info->IsStat;
    }
    else if (test_info->test_cond_type == IsCatM_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_isCatM;
        test_info_asn->testType.choice.isCatM = test_info->IsCatM;
    }
    else if (test_info->test_cond_type == DL_RSRP_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_rSRP;
        test_info_asn->testType.choice.rSRP = test_info->DL_RSRP;
    }
    else if (test_info->test_cond_type == DL_RSRQ_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_rSRQ;
        test_info_asn->testType.choice.rSRQ = test_info->DL_RSRQ;
    }
    else if (test_info->test_cond_type == UL_RSRP_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_ul_rSRP;
        test_info_asn->testType.choice.ul_rSRP = test_info->UL_RSRP;
    }
    else if (test_info->test_cond_type == CQI_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_cQI;
        test_info_asn->testType.choice.cQI = test_info->CQI;
    }
    else if (test_info->test_cond_type == fiveQI_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_fiveQI;
        test_info_asn->testType.choice.fiveQI = test_info->fiveQI;
    }
    else if (test_info->test_cond_type == QCI_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_qCI;
        test_info_asn->testType.choice.qCI = test_info->QCI;
    }
    else if (test_info->test_cond_type == S_NSSAI_TEST_COND_TYPE)
    {
        test_info_asn->testType.present = TestCond_Type_PR_sNSSAI;
        test_info_asn->testType.choice.sNSSAI = test_info->S_NSSAI;
    }
    else {
        assert(false && "Condition type out of the range");
    }
    


    if (test_info->test_cond >= 0 && test_info->test_cond < END_TEST_COND) {
        assert(false && "Test Condition not yet implemented");
    }

    if (test_info->test_cond_value >= 0 && test_info->test_cond_value <= 6) {
        assert(false && "Test Condition Value not yet implemented");
    }


    return &test_info_asn;

}