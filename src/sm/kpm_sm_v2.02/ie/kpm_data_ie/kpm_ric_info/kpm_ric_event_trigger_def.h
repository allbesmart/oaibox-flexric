#ifndef KPM_V2_RIC_EVENT_TRIGGER_DEFINITION_H
#define KPM_V2_RIC_EVENT_TRIGGER_DEFINITION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned long ms; // reporting period in milliseconds
} kpm_ric_event_trigger_def_t;

// add free_event_trigger()
// add cp_event_trigger() maybe


#ifdef __cplusplus
}
#endif

#endif