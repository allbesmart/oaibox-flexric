#ifndef RIC_EVENT_TRIGGER_DEFINITION_KPM_V2_H
#define RIC_EVENT_TRIGGER_DEFINITION_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    STYLE_1_RIC_EVENT_TRIGGER = 1,

    END_STYLE_RIC_EVENT_TRIGGER

} style_ric_event_trigger_e;

typedef enum {
    FORMAT_1_RIC_EVENT_TRIGGER = 1,

    END_FORMAT_RIC_EVENT_TRIGGER

} format_ric_event_trigger_e;

// 8.2.1.1    RIC EVENT TRIGGER DEFINITION IE
// 8.2.1.1.1  E2SM-KPM Event Trigger Definition Format 1

typedef struct {
    uint32_t report_period_ms; // [1, 4294967295] reporting period in milliseconds

} kpm_event_trigger_def_t;



#ifdef __cplusplus
}
#endif

#endif

// done