#ifndef GLOBAL_GNB_ID_H
#define GLOBAL_GNB_ID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "plmn_identity.h"

typedef enum {
    GNB_TYPE_ID,

    END_TYPE_ID

} gnb_type_id_e;

typedef struct {
    plmn_t plmn_id;

    gnb_type_id_e type;
    union {
        uint32_t gnb_id;  // bit string size (22..32) ask Mikel
    };
    

} global_gnb_id_t;


#ifdef __cplusplus
}
#endif

#endif

// done