#include <assert.h>

#include "kpm_ran_function_def.h"

void free_kpm_ran_function_def(kpm_ran_function_def_t* src)
{
  assert(src != NULL);
  
  // RAN Function Name
  free_kpm_ran_function_name(&src->ran_function_Name);

  // RIC Event Trigger Style List
  if (src->ric_event_trigger_style_list != NULL || src->ric_event_trigger_style_list_len != 0)
    assert(false && "Not yet implemented");

  // RIC Report Style List
  if (src->ric_report_style_list != NULL || src->ric_report_style_list_len != 0)
    assert(false && "Not yet implemented");

}

bool eq_kpm_ran_function_def(kpm_ran_function_def_t const * m0, kpm_ran_function_def_t const * m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  // RAN Function Name
  if (eq_kpm_ran_function_name(&m0->ran_function_Name, &m1->ran_function_Name) != true)
    return false;

  // RIC Event Trigger Style List
  if (m0->ric_event_trigger_style_list != NULL || m1->ric_event_trigger_style_list != NULL)
    assert(false && "Not yet implemented");

  // RIC Report Style List
  if (m0->ric_report_style_list != NULL || m1->ric_report_style_list != NULL)
    assert(false && "Not yet implemented");

  return true;
}
