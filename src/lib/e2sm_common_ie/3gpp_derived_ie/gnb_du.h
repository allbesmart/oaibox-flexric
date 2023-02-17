#ifndef GNB_DU_h
#define GNB_DU_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t gnb_cu_ue_f1ap;  // 6.2.3.21
    uint64_t *ran_ue_id;  // 6.2.3.25, OPTIONAL

} gnb_du_t;

void free_gnb_du_ue_id(gnb_du_t * src);

bool eq_gnb_du_ue_id(gnb_du_t const * m0, gnb_du_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
