#ifndef KPM_V2_MATCHING_CONDITION_FORMAT_3_LIST_H
#define KPM_V2_MATCHING_CONDITION_FORMAT_3_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "label_info_lst.h"
#include "test_info_lst.h"

typedef struct {
    enum {LABEL_INFO, TEST_INFO} cond_type;
    union {
        label_info_lst_t label_info_lst;
        test_info_lst_t test_info_lst;
    };

    long *logical_OR;  /* OPTIONAL - If set to “true”, logical connection to the next condition is “or”. */

} matching_condition_format_3_lst_t;

#ifdef __cplusplus
}
#endif

#endif