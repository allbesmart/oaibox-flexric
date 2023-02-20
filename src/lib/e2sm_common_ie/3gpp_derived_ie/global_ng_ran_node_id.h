#ifndef GLOBAL_NG_RAN_NODE_ID_H
#define GLOBAL_NG_RAN_NODE_ID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "global_gnb_id.h"
#include "global_ng_enb_id.h"

//  6.2.3.3 Global gNB ID

typedef enum {
    GNB_GLOBAL_TYPE_ID,
    NG_ENB_GLOBAL_TYPE_ID,

    END_GLOBAL_TYPE_ID

} ng_ran_node_type_id_e;

typedef struct {
    ng_ran_node_type_id_e type;
    union {
        global_gnb_id_t global_gnb_id;  // 6.2.3.3
        global_ng_enb_id_t global_ng_enb_id;  // 6.2.3.2
    };
    

} global_ng_ran_node_id_t;

bool eq_global_ng_ran_node_id(global_ng_ran_node_id_t const * m0, global_ng_ran_node_id_t const * m1);

#ifdef __cplusplus
}
#endif

#endif
