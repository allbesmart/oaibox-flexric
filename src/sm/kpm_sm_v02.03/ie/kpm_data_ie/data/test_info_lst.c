#include <assert.h>

#include "test_info_lst.h"

void free_test_info(test_info_lst_t* src)
{
  assert(src != NULL);

  if (src->test_cond != NULL)
    free(src->test_cond);

  if (src->test_cond_value != NULL)
  {
    if (src->int_value != NULL)
      free(src->int_value);

    if (src->enum_value != NULL)
      free(src->enum_value);

    if (src->bool_value != NULL)
      free(src->bool_value);

    if (src->bit_string_value != NULL)
    {
      free_byte_array(*src->bit_string_value);
      free(src->bit_string_value);
    }

    if (src->octet_string_value != NULL)
    {
      free_byte_array(*src->octet_string_value);
      free(src->octet_string_value);
    }

    if (src->printable_string_value != NULL)
    {
      free_byte_array(*src->printable_string_value);
      free(src->printable_string_value);
    }
    
    if (src->real_value_value != NULL)
      free(src->real_value_value);

  }


}

bool eq_test_info(const test_info_lst_t *m0, const test_info_lst_t *m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (m0->test_cond_type != m1->test_cond_type)
    return false;

  switch (m0->test_cond_type)
  {
  case GBR_TEST_COND_TYPE:
    if (m0->GBR != m1->GBR)
      return false;
    break;

  case AMBR_TEST_COND_TYPE:
    if (m0->AMBR != m1->AMBR)
      return false;
    break;

  case IsStat_TEST_COND_TYPE:
    if (m0->IsStat != m1->IsStat)
      return false;
    break;

  case IsCatM_TEST_COND_TYPE:
    if (m0->IsCatM != m1->IsCatM)
      return false;
    break;

  case DL_RSRP_TEST_COND_TYPE:
    if (m0->DL_RSRP != m1->DL_RSRP)
      return false;
    break;

  case DL_RSRQ_TEST_COND_TYPE:
    if (m0->DL_RSRQ != m1->DL_RSRQ)
      return false;
    break;

  case UL_RSRP_TEST_COND_TYPE:
    if (m0->UL_RSRP != m1->UL_RSRP)
      return false;
    break;

  case CQI_TEST_COND_TYPE:
    if (m0->CQI != m1->CQI)
      return false;
    break;

  case fiveQI_TEST_COND_TYPE:
    if (m0->fiveQI != m1->fiveQI)
      return false;
    break;

  case QCI_TEST_COND_TYPE:
    if (m0->QCI != m1->QCI)
      return false;
    break;

  case S_NSSAI_TEST_COND_TYPE:
    if (m0->S_NSSAI != m1->S_NSSAI)
      return false;
    break;
  
  default:
    assert(false && "Condition type out of the range");
  }


  if (m0->test_cond != NULL || m1->test_cond != NULL)
    assert(false && "Test Condition not yet implemented");

  if (m0->test_cond_value != NULL || m1->test_cond_value != NULL)
    assert(false && "Test Condition Value not yet implemented");

  return true;
}
