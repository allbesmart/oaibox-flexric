#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
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


void free_kpm_ind_msg(kpm_ind_msg_t* src) 
{
  assert(src != NULL);
  
  size_t i;

  for (i=0; i<src->MeasData_len; i++)
    free(src->MeasData[i].measRecord);
  free(src->MeasData);
  
  /*OPTIONAL fields below*/
  if (src->MeasInfo != NULL){
    for (i=0; i<src->MeasInfo_len; i++)
    {
      if (src->MeasInfo[i].meas_type ==  KPM_V2_MEASUREMENT_TYPE_NAME)
        free_byte_array(src->MeasInfo[i].meas_name);
      for (size_t j = 0; j< src->MeasInfo[i].labelInfo_len; j++)
        free_label_info(&src->MeasInfo[i].labelInfo[j]);
      free(src->MeasInfo[i].labelInfo);
    }
    free(src->MeasInfo);
  }

  if (src->granulPeriod != NULL)
    free(src->granulPeriod);
}

bool eq_kpm_ind_msg(kpm_ind_msg_t const* m0, kpm_ind_msg_t const* m1)
{
  assert(m0 != NULL);
  assert(m1 != NULL);

  if (m0->MeasData_len != m1->MeasData_len)
    return false;
  for (size_t i = 0; i < m0->MeasData_len; ++i) {
    const MeasDataItem_t *mdi0 = &m0->MeasData[i];
    const MeasDataItem_t *mdi1 = &m1->MeasData[i];
    if (mdi0->measRecord_len != mdi1->measRecord_len)
      return false;
    for (size_t j = 0; j < mdi0->measRecord_len; ++j) {
      const MeasRecord_t *mr0 = &mdi0->measRecord[j];
      const MeasRecord_t *mr1 = &mdi1->measRecord[j];
      if (mr0->type != mr1->type)
        return false;
      if (mr0->int_val != mr1->int_val)
        return false;
      if (fabs(mr0->real_val - mr1->real_val) > 0.0001f)
        return false;
    }
    if (mdi0->incompleteFlag != mdi1->incompleteFlag)
      return false;
  }

  if (m0->MeasInfo_len != m1->MeasInfo_len)
    return false;
  for (size_t i = 0; i < m0->MeasInfo_len; ++i) {
    const MeasInfo_t *mi0 = &m0->MeasInfo[i];
    const MeasInfo_t *mi1 = &m1->MeasInfo[i];
    if (mi0->meas_type != mi1->meas_type)
      return false;
    if (mi0->meas_type == KPM_V2_MEASUREMENT_TYPE_NAME) {
      if (eq_byte_array(&(mi0->meas_name), &(mi1->meas_name)) != true)
        return false;
    } else {
      if (mi0->meas_id != mi1->meas_id)
        return false;
    }
    if (mi0->labelInfo_len != mi1->labelInfo_len)
      return false;
    for (size_t j = 0; j < mi0->labelInfo_len; ++j) {
      const LabelInformationItem_t *lii0 = &mi0->labelInfo[0];
      const LabelInformationItem_t *lii1 = &mi1->labelInfo[0];
      OPTIONAL_CHECK_EQUAL_SIMPLE_TYPE(lii0->noLabel, lii1->noLabel);
      // TODO additional checks missing
    }
  }

  OPTIONAL_CHECK_EQUAL_SIMPLE_TYPE(m0->granulPeriod, m1->granulPeriod);
  // otherwise they must both be NULL
  return true;
}

kpm_ind_msg_t cp_kpm_ind_msg(kpm_ind_msg_t const* src) {

  assert(src != NULL);
  kpm_ind_msg_t ret = {0};

  if (src->granulPeriod) {
    ret.granulPeriod = malloc (sizeof(ret.granulPeriod));
    *(ret.granulPeriod) = *(src->granulPeriod); 
  }

  if (src->MeasData_len) {
    ret.MeasData_len = src->MeasData_len;
    ret.MeasData = calloc(src->MeasData_len, sizeof(MeasDataItem_t));
    memcpy (ret.MeasData, src->MeasData, src->MeasData_len * sizeof(MeasDataItem_t));
    for (size_t i = 0; i<ret.MeasData_len; i++){
      ret.MeasData[i].measRecord = calloc(src->MeasData[i].measRecord_len, sizeof(MeasRecord_t));
      memcpy (ret.MeasData[i].measRecord, src->MeasData[i].measRecord, src->MeasData[i].measRecord_len * sizeof(MeasDataItem_t));
    }
  }

  if (src->MeasInfo_len) {
    ret.MeasInfo_len = src->MeasInfo_len;
    ret.MeasInfo = calloc(src->MeasInfo_len, sizeof(MeasInfo_t));
    memcpy (ret.MeasInfo, src->MeasInfo, src->MeasInfo_len * sizeof(MeasInfo_t));
    for (size_t i = 0; i<ret.MeasInfo_len; i++)
    {
      ret.MeasInfo[i].labelInfo_len = src->MeasInfo[i].labelInfo_len;
      ret.MeasInfo[i].labelInfo = calloc(src->MeasInfo[i].labelInfo_len, sizeof(LabelInformationItem_t));
      memcpy (ret.MeasInfo[i].labelInfo, src->MeasInfo[i].labelInfo, src->MeasInfo[i].labelInfo_len * sizeof(LabelInformationItem_t));
      for (size_t j = 0; j < src->MeasInfo[i].labelInfo_len; j++)
      {
        ret.MeasInfo[i].meas_type = src->MeasInfo[i].meas_type;
        if (ret.MeasInfo[i].meas_type == KPM_V2_MEASUREMENT_TYPE_NAME)
          ret.MeasInfo[i].meas_name = copy_byte_array(src->MeasInfo[i].meas_name);
        else
          ret.MeasInfo[i].meas_id = src->MeasInfo[i].meas_id;
        cp_label_info(&ret.MeasInfo[i].labelInfo[j], &src->MeasInfo[i].labelInfo[j]);  
      }
    }
  }
  
  return ret;
}