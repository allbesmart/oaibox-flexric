#ifndef KPM_V2_TEST_INFO_LIST_H
#define KPM_V2_TEST_INFO_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    GBR,
    AMBR,
    IsStat,
    IsCatM,
    DL_RSRP,
    DL_RSRQ,
    UL_RSRP,
    CQI,
    fiveQI,
    QCI,
    S_NSSAI

} test_cond_type_t;

typedef enum {
    equal,
    greaterthan,
    lessthan,
    contains,
    present

    /* This type is extensible */

} test_cond_t;

typedef enum {
    
    /* To be filled */

} test_cond_value_t;

typedef struct {
    
    test_cond_type_t test_cond_type;
    union {
        long *GBR;
        long *AMBR;
        long *IsStat;
        long *IsCatM;
        long *DL_RSRP;
        long *DL_RSRQ;
        long *UL_RSRP;
        long *CQI;
        long *fiveQI;
        long *QCI;
        long *S_NSSAI;

    };
    
    test_cond_t test_cond;  /* OPTIONAL */

    test_cond_value_t test_cond_value;  /* OPTIONAL */

} test_info_lst_t;


#ifdef __cplusplus
}
#endif

#endif