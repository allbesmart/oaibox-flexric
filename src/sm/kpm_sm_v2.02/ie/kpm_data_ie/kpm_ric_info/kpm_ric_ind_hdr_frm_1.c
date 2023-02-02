#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "kpm_ric_ind_hdr_frm_1.h"

void free_kpm_ind_hdr_frm_1(kpm_ric_ind_hdr_format_1_t* src)
{
  assert(src != NULL);
  if (src->fileformat_version->buf != NULL)
    free_byte_array(*src->fileformat_version);
  if (src->sender_name->buf != NULL)
    free_byte_array(*src->sender_name);
  if (src->sender_type->buf != NULL)
    free_byte_array(*src->sender_type);
  if (src->vendor_name->buf != NULL)
    free_byte_array(*src->vendor_name);
}

kpm_ric_ind_hdr_format_1_t cp_kpm_ind_hdr_frm_1(kpm_ric_ind_hdr_format_1_t const* src)
{
  assert(src != NULL);
  kpm_ric_ind_hdr_format_1_t ret = {0};

  ret.collectStartTime = src->collectStartTime;
  
  if (src->fileformat_version->buf)
    *ret.fileformat_version = copy_byte_array(*src->fileformat_version);
  if (src->sender_name->buf)
    *ret.sender_name = copy_byte_array(*src->sender_name);
  if (src->sender_type->buf)
    *ret.sender_type = copy_byte_array(*src->sender_type);
  if (src->vendor_name->buf)
    *ret.vendor_name = copy_byte_array(*src->vendor_name);
  return ret;
}

bool eq_kpm_ind_hdr_frm_1(kpm_ric_ind_hdr_format_1_t const* hdr0, kpm_ric_ind_hdr_format_1_t const* hdr1)
{
  assert(hdr0 != NULL);
  assert(hdr1 != NULL);

  if (hdr0 == hdr1) return true;

  if (hdr0->collectStartTime != hdr1->collectStartTime) return false;

  if (eq_byte_array(&hdr0->fileformat_version, &hdr1->fileformat_version) == false) return false;

  if (eq_byte_array(&hdr0->sender_name, &hdr1->sender_name) == false) return false;

  if (eq_byte_array(&hdr0->sender_type, &hdr1->sender_type) == false) return false;

  if (eq_byte_array(&hdr0->vendor_name, &hdr1->vendor_name) == false) return false;

  return true;
}