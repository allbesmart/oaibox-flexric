#include <assert.h>

#include "dec_ric_event_trigger_frm_1.h"

kpm_ric_event_trigger_format_1_t * kpm_dec_event_trigger_def_frm_1_asn(const E2SM_KPM_EventTriggerDefinition_Format1_t * event_trigger_asn)
{
    kpm_ric_event_trigger_format_1_t * event_trigger = calloc(1, sizeof(kpm_ric_event_trigger_format_1_t));
    assert(event_trigger != NULL && "Memory exhausted");


    event_trigger->report_period_ms = event_trigger_asn->reportingPeriod;

    return &event_trigger;

}