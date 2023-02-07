#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "kpm_ric_ind_msg_frm_1.h"

// Equality implemented as euristics for the moment. This function is used in test framework.
#define OPTIONAL_CHECK_EQUAL_SIMPLE_TYPE(T0,T1) \
  do { \
    if ((T0) == NULL && (T1) != NULL) \
      return false; \
    if ((T0) != NULL && (T1) == NULL) \
      return false; \
    if ((T0) != NULL && (T1) != NULL) \
      if (*(T0) != *(T1)) \
        return false; \
  } while (0)


void free_kpm_ind_msg_frm_1(kpm_ind_msg_format_1_t* src) 
{
  assert(src != NULL);

  for (size_t i = 0; i < src->meas_data_lst_len; i++)
    free(src->meas_data_lst[i].meas_record_lst);
  free(src->meas_data_lst);
  

  /*OPTIONAL fields below*/
  if (src->meas_info_lst != NULL){
    for (size_t i=0; i<src->meas_info_lst_len; i++)
    {
      if (src->meas_info_lst[i].meas_type.type ==  NAME_MEAS_TYPE)
        free_byte_array(src->meas_info_lst[i].meas_type.name);
      for (size_t j = 0; j< src->meas_info_lst[i].label_info_lst_len; j++)
        free_label_info(&src->meas_info_lst[i].label_info_lst[j]);
      free(src->meas_info_lst[i].label_info_lst);
    }
    free(src->meas_info_lst);
  }

  if (src->gran_period_ms != NULL)
    free(src->gran_period_ms);
}


bool eq_kpm_ind_msg_frm_1(kpm_ind_msg_format_1_t const* m0, kpm_ind_msg_format_1_t const* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (m0->meas_data_lst_len != m1->meas_data_lst_len)
    return false;
  for (size_t i = 0; i < m0->meas_data_lst_len; ++i)
  {

    if (m0->meas_data_lst[i].meas_record_len != m1->meas_data_lst[i].meas_record_len)
      return false;
    for (size_t j = 0; j < m0->meas_data_lst[i].meas_record_len; ++j)
    {
      
      if (m0->meas_data_lst[i].meas_record_lst[j].value != m1->meas_data_lst[i].meas_record_lst[j].value)
        return false;

      switch (m0->meas_data_lst[i].meas_record_lst[j].value)
      {
        case INTEGER_MEAS_VALUE:
          if (m0->meas_data_lst[i].meas_record_lst[j].int_val != m1->meas_data_lst[i].meas_record_lst[j].int_val)
            return false;
          break;

        case REAL_MEAS_VALUE:
          if (fabs(m0->meas_data_lst[i].meas_record_lst[j].real_val - m1->meas_data_lst[i].meas_record_lst[j].real_val) > 0.0001f)
            return false;
          break;

        case NO_VALUE_MEAS_VALUE:
          if (m0->meas_data_lst[i].meas_record_lst[j].no_value != m1->meas_data_lst[i].meas_record_lst[j].no_value)
            return false;
          break;

        default:
          assert(false && "Unknown Measurement Value");
      }

      
    }


    if (m0->meas_data_lst[i].incomplete_flag != m1->meas_data_lst[i].incomplete_flag)
      return false;
    
  }



  if (m0->meas_info_lst_len != m1->meas_info_lst_len)
    return false;
  for (size_t i = 0; i < m0->meas_info_lst_len; ++i)
  {
    // Meas Type

    if (m0->meas_info_lst[i].meas_type.type != m1->meas_info_lst[i].meas_type.type)
      return false;
    if (m0->meas_info_lst[i].meas_type.type == NAME_MEAS_TYPE)
    {
      if (eq_byte_array(&m0->meas_info_lst[i].meas_type.name, &m1->meas_info_lst[i].meas_type.name) != true)
        return false;
    }
    else if (m0->meas_info_lst[i].meas_type.type == ID_MEAS_TYPE)
    {
      if (m0->meas_info_lst[i].meas_type.id != m1->meas_info_lst[i].meas_type.id)
        return false;
    }

    

    // Label Info

    if (m0->meas_info_lst[i].label_info_lst_len != m1->meas_info_lst[i].label_info_lst_len)
      return false;
    
    for (size_t j = 0; j < m0->meas_info_lst[i].label_info_lst_len; ++j)
    {
      if (eq_label_info(&m0->meas_info_lst[i].label_info_lst[j], &m1->meas_info_lst[i].label_info_lst[j]) != true)
        return false;
    }
  }

  if (m0->gran_period_ms != m1->gran_period_ms)
    return false;


  return true;
}


kpm_ind_msg_format_1_t cp_kpm_ind_msg_frm_1(kpm_ind_msg_format_1_t const* src) {

  assert(src != NULL);
  kpm_ind_msg_format_1_t ret = {0};

  if (src->gran_period_ms) {
    ret.gran_period_ms = malloc (sizeof(ret.gran_period_ms));
    ret.gran_period_ms = src->gran_period_ms; 
  }

  if (src->meas_data_lst_len)
  {
    ret.meas_data_lst_len = src->meas_data_lst_len;

    ret.meas_data_lst = calloc(src->meas_data_lst_len, sizeof(meas_data_lst_t));
    memcpy (ret.meas_data_lst, src->meas_data_lst, src->meas_data_lst_len * sizeof(meas_data_lst_t));
    
    for (size_t i = 0; i<ret.meas_data_lst_len; i++)
    {
      ret.meas_data_lst[i].meas_record_lst = calloc(src->meas_data_lst[i].meas_record_len, sizeof(meas_record_lst_t));
      memcpy (ret.meas_data_lst[i].meas_record_lst, src->meas_data_lst[i].meas_record_lst, src->meas_data_lst[i].meas_record_len * sizeof(meas_record_lst_t));
    }
  }

  if (src->meas_info_lst_len)
  {
    ret.meas_info_lst_len = src->meas_info_lst_len;
    
    ret.meas_info_lst = calloc(src->meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
    memcpy (ret.meas_info_lst, src->meas_info_lst, src->meas_info_lst_len * sizeof(meas_info_format_1_lst_t));
    
    
    for (size_t i = 0; i<ret.meas_info_lst_len; i++)
    {
      ret.meas_info_lst[i].meas_type.type = src->meas_info_lst[i].meas_type.type;

      if (ret.meas_info_lst[i].meas_type.type == NAME_MEAS_TYPE)
      {
        ret.meas_info_lst[i].meas_type.name = copy_byte_array(src->meas_info_lst[i].meas_type.name);
      }
      else if (ret.meas_info_lst[i].meas_type.type == ID_MEAS_TYPE)
      {
        ret.meas_info_lst[i].meas_type.id = src->meas_info_lst[i].meas_type.id;
      }
      


      ret.meas_info_lst[i].label_info_lst_len = src->meas_info_lst[i].label_info_lst_len;
      
      ret.meas_info_lst[i].label_info_lst = calloc(src->meas_info_lst[i].label_info_lst_len, sizeof(label_info_lst_t));
      memcpy (ret.meas_info_lst[i].label_info_lst, src->meas_info_lst[i].label_info_lst, src->meas_info_lst[i].label_info_lst_len * sizeof(label_info_lst_t));
      
      
      for (size_t j = 0; j < src->meas_info_lst[i].label_info_lst_len; j++)
      {
        cp_label_info(&ret.meas_info_lst[i].label_info_lst[j], &src->meas_info_lst[i].label_info_lst[j]);  
      }
    }
  }
  
  return ret;
}