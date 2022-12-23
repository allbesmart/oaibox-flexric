#ifndef GUMMEI_h
#define GUMMEI_h

#ifdef __cplusplus
extern "C" {
#endif

#include "plmn_identity.h"

//  6.2.3.18  GUMMEI  -  This IE indicates the globally unique MME identity.

typedef struct {

    // all are mandatory

    plmn_t plmn_id;

    uint8_t mme_group_id[2];

    uint8_t mme_code;


} gummei_t;

#ifdef __cplusplus
}
#endif

#endif

// done