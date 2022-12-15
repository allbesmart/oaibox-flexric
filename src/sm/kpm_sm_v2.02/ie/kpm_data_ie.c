/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/* 
 * This file contains free/copy/equals methods implementation for the data structures defined in the associated header file 
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../../../util/alg_ds/alg/eq_float.h"
#include "../../../util/byte_array.h"
#include "kpm_data_ie.h"
















void free_kpm_ind_data(kpm_ind_data_t* ind) 
{
  assert(ind != NULL);
  free_kpm_ind_hdr(&ind->hdr);
  free_kpm_ind_msg(&ind->msg);
}

kpm_ind_data_t cp_kpm_ind_data(kpm_ind_data_t const* src) 
{

  assert(src != NULL);
  kpm_ind_data_t ret = {.hdr = cp_kpm_ind_hdr(&src->hdr), .msg = cp_kpm_ind_msg(&src->msg)};
  return ret;
}

/* FUNCTION DEFINITION*/
void free_kpm_func_def(kpm_func_def_t* src)
{
  assert(src != NULL);
  
  free(src->ric_ReportStyle_List); 
  free(src->ric_EventTriggerStyle_List); 
  free(src->ranFunction_Name.ranFunction_Instance);
  free_byte_array(src->ranFunction_Name.Description);
  free_byte_array(src->ranFunction_Name.E2SM_OID);
  free_byte_array(src->ranFunction_Name.ShortName);
}

