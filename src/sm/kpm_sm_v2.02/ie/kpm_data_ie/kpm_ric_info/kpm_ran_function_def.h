#ifndef KPM_V2_RAN_FUNCTION_DEFINITION_H
#define KPM_V2_RAN_FUNCTION_DEFINITION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../data/meas_info_lst.h"


typedef struct {
    byte_array_t	 ShortName;   // “ORAN-E2SM-KPM” aka SM_KPM_STR
	byte_array_t	 E2SM_OID;    // see cfr. O-RAN.WG3.E2SM-v02.01.pdf, table 5.1
	byte_array_t	 Description; // “KPM Monitor”
	long	         *ranFunction_Instance;	// OPTIONAL: it is suggested to be used when E2 Node declares
                                                    // multiple RAN Function ID supporting the same  E2SM specification
} ran_function_Name_t;


typedef struct {
    uint8_t ric_event_trigger_style_type; // see with Mikel what type you should use
    byte_array_t ric_event_trigger_style_name;
    uint8_t ric_event_trigger_format_type; // see with Mikel what type you should use
                                           // and it is the same as style type? 1,..,5
} ric_event_trigger_style_item_t;


// for format type => Table 7.8-1

typedef struct {
    uint8_t ric_report_style_type;
    byte_array_t ric_report_style_name;
    uint8_t ric_report_format_type;

    size_t meas_info_for_action; // ask Mikel !!!
    meas_type_e *meas_type_list;

    uint8_t ric_ind_hdr_format_type; // just one value => 1
    uint8_t ric_ind_msg_format_type; // 1,2,3


} ric_report_style_item_t;

typedef struct {
    ran_function_Name_t ran_function_Name;

    size_t ric_event_trigger_style_list_len;
    ric_event_trigger_style_item_t *ric_event_trigger_style_list;

    size_t ric_report_style_list_len;
    ric_report_style_item_t *ric_report_style_list;

} kpm_ran_function_def_t;



// add in c file ric_event_trigger_style_item default values, see 7.3.1

// do I need separate messages for RIC Subscription and RIC Indication as defined in kpm_data_ie.h
// and kpm_setup_data_t ???

#ifdef __cplusplus
}
#endif

#endif