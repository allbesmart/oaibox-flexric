#ifndef KPM_V2_MEASUREMENT_TYPE_H
#define KPM_V2_MEASUREMENT_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "../../../../../util/byte_array.h"

typedef struct {
    enum {NAME_MEAS_TYPE, ID_MEAS_TYPE} type;
    union {
        byte_array_t name; // 8.3.9
        uint16_t id; // 8.3.10
    };

} meas_type_t;

#ifdef __cplusplus
}
#endif

#endif
