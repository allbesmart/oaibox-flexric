#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie.h"
#include "../../src/sm/kpm_sm_v2.02/enc/kpm_enc_asn.h"
#include "../../src/sm/kpm_sm_v2.02/dec/kpm_dec_asn.h"


void test_indication_header()
{
  const uint32_t startTime = 21;
  
  byte_array_t fileFormatVersion = {0};
  const char* fileFormatVersion_str = "This is the format version";
  fileFormatVersion.buf = calloc(strlen(fileFormatVersion_str) + 1, sizeof(char));
  memcpy(fileFormatVersion.buf, fileFormatVersion_str, strlen(fileFormatVersion_str));
  fileFormatVersion.len = strlen(fileFormatVersion_str);

  byte_array_t senderName = {0};
  const char* senderName_str = "This is the sender name";
  senderName.buf = calloc(strlen(senderName_str) + 1, sizeof(char));
  memcpy(senderName.buf, senderName_str, strlen(senderName_str));
  senderName.len = strlen(senderName_str);

  byte_array_t senderType = {0};
  const char* senderType_str = "This is the sender type";
  senderType.buf = calloc(strlen(senderType_str) + 1, sizeof(char));
  memcpy(senderType.buf, senderType_str, strlen(senderType_str));
  senderType.len = strlen(senderType_str);

  byte_array_t vendorName = {0};
  const char* vendorName_str = "This is the vendor name";
  vendorName.buf = calloc(strlen(vendorName_str) + 1, sizeof(char));
  memcpy(vendorName.buf, vendorName_str, strlen(vendorName_str));
  vendorName.len = strlen(vendorName_str);

  kpm_ind_hdr_t kpm_ind_hdr_msg = {
    .collectStartTime = startTime,
    .fileformat_version = fileFormatVersion,
    .sender_name = senderName,
    .sender_type = senderType,
    .vendor_name = vendorName,
  };

  byte_array_t kpm_ind_hdr_enc = kpm_enc_ind_hdr_asn(&kpm_ind_hdr_msg);
  kpm_ind_hdr_t kpm_ind_hdr_dec = kpm_dec_ind_hdr_asn(kpm_ind_hdr_enc.len, kpm_ind_hdr_enc.buf);

  free_byte_array(kpm_ind_hdr_enc);

  assert(eq_kpm_ind_hdr(&kpm_ind_hdr_msg, &kpm_ind_hdr_dec) == true);

  free_kpm_ind_hdr(&kpm_ind_hdr_msg);
  free_kpm_ind_hdr(&kpm_ind_hdr_dec);

}

int main()
{
  test_indication_header();

  puts("Success running the encoding/decoding test");
  return 0;
}