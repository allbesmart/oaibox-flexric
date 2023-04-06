#ifndef GLOBAL_NG_ENB_ID_H
#define GLOBAL_NG_ENB_ID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "plmn_identity.h"

//  6.2.3.8 Global ng-eNB ID


typedef enum {
    MACRO_NG_ENB_TYPE_ID,
    SHORT_MACRO_NG_ENB_TYPE_ID,
    LONG_MACRO_NG_ENB_TYPE_ID,

    END_NG_ENB_TYPE_ID

} ng_enb_type_id_e;


typedef struct {
    plmn_t plmn_id;

    ng_enb_type_id_e type;
    union {
        uint32_t  macro_ng_enb_id:20;  // BIT STRING (SIZE(20))
        uint32_t  short_macro_ng_enb_id:18;  // BIT STRING (SIZE(18))
        uint32_t  long_macro_ng_enb_id:21;  // BIT STRING (SIZE(21))
    };

} global_ng_enb_id_t;

bool eq_global_ng_enb_id(global_ng_enb_id_t const * m0, global_ng_enb_id_t const * m1);

global_ng_enb_id_t cp_global_ng_enb_id(const global_ng_enb_id_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
