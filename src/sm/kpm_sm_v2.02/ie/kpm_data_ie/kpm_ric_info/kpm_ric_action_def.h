#ifndef KPM_V2_RIC_ACTION_DEFINITION_MIR_H
#define KPM_V2_RIC_ACTION_DEFINITION_MIR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "kpm_ric_action_def_frm_1.h"
#include "kpm_ric_action_def_frm_2.h"

 // 8.3.3
 // 6.2.2.2 RIC Style Type
 // Defined as an INTEGER
typedef enum{
  FORMAT_1_RIC_STYLE_KPM = 1,
  FORMAT_2_RIC_STYLE_KPM,
  FORMAT_3_RIC_STYLE_KPM,
  FORMAT_4_RIC_STYLE_KPM,
  FORMAT_5_RIC_STYLE_KPM,

  END_RIC_STYLE_KPM,

}  kpm_ric_style_e ;

/*
* RIC Style Type 1:  E2 Node Measurement. Used to carry measurement report from a target E2 Node. More in details, 
*                    it contains measurement types that Near-RT RIC is requesting to subscribe followed by a list 
*                    of subcounters to be measured for each measurement type, and a granularity period
*                    indicating collection interval of those measurements.
* RIC Style Type 2: Used to carry measurement report for a single UE of interest from a target E2 Node
* RIC Style Type 3: Used to carry UE-level measurement report for a group of UEs per
*                   measurement type matching subscribed conditions from a target E2 Node
* RIC Style Type 4: Used to carry measurement report for a group of UEs across a set of
*                   measurement types satisfying common subscribed conditions from a target E2 Node
* RIC Style Type 5: Used to carry measurement report for multiple UE of interest from a target E2 Node
*/

typedef struct{
    kpm_ric_style_e type; 
    union{
        kpm_act_def_format_1_t frm_1; 
        kpm_act_def_format_2_t frm_2; 
        // act_def_format_3_t frm_3; 
        // act_def_format_4_t frm_4; 
        // act_def_format_5_t frm_5; 
    };

} kpm_ric_act_def_t;
/*
* ask Mikel: which formats does he want?
* format 3 contains a little bit different Meas_Information
* format 2 is a subset of format 5
* format 4 is relatively easy to implement
* => 4 and 5?

* UE-specific: many choices, which ones?
* test condition information: all of them I suppose?
*/

#ifdef __cplusplus
}
#endif

#endif
