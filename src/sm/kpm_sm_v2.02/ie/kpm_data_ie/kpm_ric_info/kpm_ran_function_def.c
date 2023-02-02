#include <assert.h>

#include "kpm_ran_function_def.h"

void free_kpm_func_def(kpm_ran_function_def_t* src)
{
    assert(src != NULL);
  
    free(src->ric_report_style_list);
    free(src->ric_event_trigger_style_list); 
    free(src->ran_function_Name.instance);
    free_byte_array(src->ran_function_Name.description);
    free_byte_array(src->ran_function_Name.E2SM_OID);
    free_byte_array(src->ran_function_Name.short_name);

}