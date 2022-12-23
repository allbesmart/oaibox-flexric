#ifndef GNB_CU_UP_h
#define GNB_CU_UP_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
    uint32_t gnb_cu_cp_ue_e1ap;  // 6.2.3.20
    uint64_t *ran_ue_id;  // 6.2.3.25, OPTIONAL

} gnb_cu_up_t;

#ifdef __cplusplus
}
#endif

#endif

// done