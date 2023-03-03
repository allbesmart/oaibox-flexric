#ifndef ENB_h
#define ENB_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "gummei.h"
#include "global_enb_id.h"

typedef struct {

    // 6.2.3.26
    // Mandatory
    // MME UE S1AP ID
    uint32_t mme_ue_s1ap_id;

    // 6.2.3.18
    // Mandatory
    // GUMMEI
    gummei_t gummei;

    // 6.2.3.23
    // C-ifDCSetup
    // MeNB UE X2AP ID
    uint16_t *enb_ue_x2ap_id;  // INTEGER (0..4095), ask Mikel

    // 6.2.3.24
    // C-ifDCSetup
    // MeNB UE X2AP ID Extension
    uint16_t *enb_ue_x2ap_id_extension;  // INTEGER (0..4095), ask Mikel

    // 6.2.3.9
    // C-ifDCSetup
    global_enb_id_t *global_enb_id;

} enb_t;

void free_enb_ue_id(enb_t * src);

bool eq_enb_ue_id(enb_t const * m0, enb_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
