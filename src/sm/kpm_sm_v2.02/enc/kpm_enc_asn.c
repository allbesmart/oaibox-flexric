  /*
  * XXX-optimization: understand where do they come these values below for memory allocation of the byte arrays.
  * A tuning of those values would probably benefit this implementation
  * XXX-implementation, cfr: https://gitlab.eurecom.fr/mosaic5g/flexric/-/blob/rrc-sm/src/sm/rrc_sm/enc/rrc_enc_asn.c
  */
#include "../ie/asn/E2SM-KPM-EventTriggerDefinition-Format1.h"
#include "../ie/asn/E2SM-KPM-EventTriggerDefinition.h"
#include "../ie/asn/E2SM-KPM-ActionDefinition-Format1.h"
#include "../ie/asn/E2SM-KPM-ActionDefinition-Format2.h"
#include "../ie/asn/E2SM-KPM-ActionDefinition-Format3.h"
#include "../ie/asn/E2SM-KPM-ActionDefinition-Format4.h"
#include "../ie/asn/E2SM-KPM-ActionDefinition-Format5.h"
#include "../ie/asn/E2SM-KPM-ActionDefinition.h"
#include "../ie/asn/MeasurementInfoList.h"
#include "../ie/asn/MeasurementInfoItem.h"
#include "../ie/asn/LabelInfoItem.h"
#include "../ie/asn/asn_constant.h"
#include "../ie/asn/CGI.h"
#include "../ie/asn/EUTRA-CGI.h"
#include "../ie/asn/NR-CGI.h"
#include "../ie/asn/E2SM-KPM-IndicationHeader.h"
#include "../ie/asn/E2SM-KPM-IndicationHeader-Format1.h"
#include "../ie/asn/E2SM-KPM-IndicationMessage.h"
#include "../ie/asn/E2SM-KPM-IndicationMessage-Format1.h"
#include "../ie/asn/MeasurementDataItem.h"
#include "../ie/asn/MeasurementData.h"
#include "../ie/asn/MeasurementRecord.h"
#include "../ie/asn/MeasurementRecordItem.h"
#include "../ie/asn/E2SM-KPM-RANfunction-Description.h"
#include "../ie/asn/RANfunction-Name.h"

#include "enc_asn/enc_ric_event_trigger_frm_1.h"

#include "enc_asn/enc_ric_action_def_frm_1.h"
#include "enc_asn/enc_ric_action_def_frm_2.h"
#include "enc_asn/enc_ric_action_def_frm_3.h"
#include "enc_asn/enc_ric_action_def_frm_4.h"
#include "enc_asn/enc_ric_action_def_frm_5.h"

#include "enc_asn/enc_ric_ind_hdr_frm_1.h"

#include "kpm_enc_asn.h"
#include "../../../util/conversions.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* Encoding Event Trigger IE
 * Direction of the message: RIC --> E2 Node
 */
byte_array_t kpm_enc_event_trigger_asn(kpm_event_trigger_def_t const* event_trigger) {

  assert(event_trigger != NULL);

  E2SM_KPM_EventTriggerDefinition_t *pdu = calloc(1, sizeof(E2SM_KPM_EventTriggerDefinition_t));

  assert ( pdu != NULL && "Memory exhausted" );


  switch (pdu->eventDefinition_formats.present)
  {
  case E2SM_KPM_EventTriggerDefinition__eventDefinition_formats_PR_eventDefinition_Format1:
    pdu->eventDefinition_formats.choice.eventDefinition_Format1 = kpm_enc_event_trigger_def_frm_1_asn(&event_trigger->kpm_ric_event_trigger_format_1);
    break;
  
  default:
    assert("Non valid KPM RIC Event Trigger Format");
  }
  
  
  byte_array_t ba = {.buf = malloc(2048), .len = 2048}; 
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_KPM_EventTriggerDefinition, pdu, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;
  
  ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_EventTriggerDefinition, pdu);

  return ba;
}

/* Encoding Action Definition IE
 * Direction of the message: RIC -> E2 Node
 */
byte_array_t kpm_enc_action_def_asn(kpm_act_def_t const* action_def) 
{
  assert(action_def != NULL);

  E2SM_KPM_ActionDefinition_t *pdu = calloc(1, sizeof(E2SM_KPM_ActionDefinition_t));
  
  assert (pdu != NULL && "Memory exhausted");
 
  assert ((action_def->type >= 1 && action_def->type <= 5) && "Not valid KPM RIC Action Definition Format");


  pdu->ric_Style_Type = action_def->type;
  
  pdu->actionDefinition_formats.present = action_def->type;

  /* Action Definition Formats */
  switch (pdu->actionDefinition_formats.present) 
  {
    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1:
      pdu->actionDefinition_formats.choice.actionDefinition_Format1 = kpm_enc_action_def_frm_1_asn(&action_def->frm_1);
      break;

    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format2:
      pdu->actionDefinition_formats.choice.actionDefinition_Format2 = kpm_enc_action_def_frm_2_asn(&action_def->frm_2);
      break;
      
    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format3:
      pdu->actionDefinition_formats.choice.actionDefinition_Format3 = kpm_enc_action_def_frm_3_asn(&action_def->frm_3);
      break;
    
    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format4:
      pdu->actionDefinition_formats.choice.actionDefinition_Format4 = kpm_enc_action_def_frm_4_asn(&action_def->frm_4);
      break;

    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format5:
      pdu->actionDefinition_formats.choice.actionDefinition_Format5 = kpm_enc_action_def_frm_5_asn(&action_def->frm_5);
      break;

    default:
      assert(false && "Non valid KPM RIC Action Definition Format");
  }




  /* XXX-tuning: 
   * below bytearray sizing needs to be reviewed and made dynamic. It looks too small for the general case of action definition.
   */

  // FIXME Create one function for encoding common to all the methods.
  byte_array_t ba = {.buf = malloc(2048), .len = 2048}; 
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_KPM_ActionDefinition, pdu, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_ActionDefinition, pdu);

  return ba;
}

/* 
 * Encoding of Indication Header IE
 * Direction: NodeE2 -> RIC 
 */
byte_array_t kpm_enc_ind_hdr_asn(kpm_ind_hdr_t const* ind_hdr)
{
  assert(ind_hdr != NULL);
  E2SM_KPM_IndicationHeader_t *pdu = calloc(1,sizeof(E2SM_KPM_IndicationHeader_t));
  assert( pdu !=NULL && "Memory exhausted" );


  switch (pdu->indicationHeader_formats.present)
  {
  case E2SM_KPM_IndicationHeader__indicationHeader_formats_PR_indicationHeader_Format1:
    pdu->indicationHeader_formats.choice.indicationHeader_Format1 = kpm_enc_ind_hdr_frm_1_asn(&ind_hdr->kpm_ric_ind_hdr_format_1);
    break;
  
  default:
    assert(false && "Non valid KPM RIC Indication Header Format");
  }
  
  

  byte_array_t  ba = {.buf = malloc(2048), .len = 2048};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_KPM_IndicationHeader, pdu, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;


  ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationHeader, pdu);

  return ba;
}



/* 
 * Encoding of Indication Message IE. 
 * Limitation: just format 1 is implemented further to Action Definition IE type 1 constraint
 * Direction: NodeE2 -> RIC 
 */
byte_array_t kpm_enc_ind_msg_asn(kpm_ind_msg_t const* ind_msg) 
{
  assert(ind_msg != NULL);
  
  E2SM_KPM_IndicationMessage_t *pdu = calloc(1, sizeof(E2SM_KPM_IndicationMessage_t));
  assert( pdu !=NULL && "Memory exhausted" );

  pdu->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format1;
  pdu->indicationMessage_formats.choice.indicationMessage_Format1 = calloc(1, sizeof(E2SM_KPM_IndicationMessage_Format1_t));
  E2SM_KPM_IndicationMessage_Format1_t *msg = pdu->indicationMessage_formats.choice.indicationMessage_Format1;
  assert( msg !=NULL && "Memory exhausted" );

  // 1. measData
  assert((ind_msg->MeasData_len <= maxnoofMeasurementRecord && ind_msg->MeasData_len > 0) 
          && "Number of records not allowed");
  for (size_t i = 0; i<ind_msg->MeasData_len; i++)
  {
    MeasurementDataItem_t *mData = calloc(1, sizeof(MeasurementDataItem_t));
    assert (mData != NULL && "Memory exhausted");
    assert (ind_msg->MeasData[i].measRecord_len <= maxnoofMeasurementValue && ind_msg->MeasData[i].measRecord_len >0
            && "Number of Values not allowed");
    if (ind_msg->MeasData[i].incompleteFlag == MeasurementDataItem__incompleteFlag_true){
      mData->incompleteFlag = malloc (sizeof( *mData->incompleteFlag));
      assert(mData->incompleteFlag != NULL && "Memory exhausted");
      *(mData->incompleteFlag) = MeasurementDataItem__incompleteFlag_true; 
    }
    for (size_t j=0; j<ind_msg->MeasData[i].measRecord_len; j++){
      MeasurementRecordItem_t *mRecord = calloc(1, sizeof(MeasurementRecordItem_t));
      assert (mRecord != NULL && "Memory exhausted");
      switch (ind_msg->MeasData[i].measRecord[j].type){
        case MeasRecord_int:
          mRecord->choice.integer = ind_msg->MeasData[i].measRecord[j].int_val;
          mRecord->present = MeasurementRecordItem_PR_integer;
          break;
        case MeasRecord_real:
          mRecord->present = MeasurementRecordItem_PR_real;
          mRecord->choice.real = ind_msg->MeasData[i].measRecord[j].real_val;
          break;
        case MeasRecord_noval:
          mRecord->present = MeasurementRecordItem_PR_noValue;
          mRecord->choice.noValue = 0;
          break;
        default:
          assert(0!= 0 && "unexpected Record type");
      }

      int rc1 = ASN_SEQUENCE_ADD(&mData->measRecord.list, mRecord);
      assert(rc1 == 0);
    }
    int rc2 = ASN_SEQUENCE_ADD(&msg->measData.list, mData);
    assert(rc2 == 0);
  }

  // 2. measInfoList (OPTIONAL)
  if (ind_msg->MeasInfo_len > 0){
    assert((ind_msg->MeasInfo_len <= maxnoofMeasurementInfo) && "Number of records not allowed");
    msg->measInfoList = calloc(1, sizeof(MeasurementInfoList_t));
    for (size_t i = 0; i<ind_msg->MeasInfo_len; i++) 
    {
      MeasurementInfoItem_t *mInfo = calloc(1, sizeof(MeasurementInfoItem_t));
      assert (mInfo != NULL && "Memory exhausted");
      int ret1;
      switch (ind_msg->MeasInfo[i].meas_type){
        case KPM_V2_MEASUREMENT_TYPE_NAME:
          mInfo->measType.present = MeasurementType_PR_measName;
          const size_t len = ind_msg->MeasInfo[i].meas_name.len;
          ret1 = OCTET_STRING_fromBuf(&(mInfo->measType.choice.measName), (char *)(ind_msg->MeasInfo[i].meas_name.buf), len);
          assert(ret1 == 0);
          break;
        case  KPM_V2_MEASUREMENT_TYPE_ID:
          mInfo->measType.present = MeasurementType_PR_measID;
          mInfo->measType.choice.measID = ind_msg->MeasInfo[i].meas_id;
          break;
        default:
            assert(0!= 0 && "unexpected Measurement type");
      }

      for (size_t j=0; j<ind_msg->MeasInfo[i].labelInfo_len; j++)
      {
        LabelInfoItem_t *lInfo = cp_label_info_item_into_asn(&ind_msg->MeasInfo[i].labelInfo[j]);
        int rc1 = ASN_SEQUENCE_ADD(&mInfo->labelInfoList.list, lInfo);    
        assert(rc1 == 0);
      }

      int rc2 = ASN_SEQUENCE_ADD(&msg->measInfoList->list, mInfo);
      assert(rc2 == 0);
    }
  }
  // 3. granulPeriod (OPTIONAL)
  if (ind_msg->granulPeriod) {
    msg->granulPeriod = malloc(sizeof(*(msg->granulPeriod)));
    *(msg->granulPeriod)=*(ind_msg->granulPeriod);
  }

  xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationMessage, pdu);

  byte_array_t  ba = {.buf = malloc(2048), .len = 2048};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_KPM_IndicationMessage, pdu, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;


  ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_IndicationMessage, pdu);

  return ba;
}


/*
 * Encoding of Function Definition IE. 
 * Direction: NodeE2 -> RIC 
 */
byte_array_t kpm_enc_func_def_asn(kpm_ran_function_def_t const* func_def)  
{
  assert(func_def != NULL);
  
  E2SM_KPM_RANfunction_Description_t *pdu = calloc(1, sizeof(E2SM_KPM_RANfunction_Description_t));
  assert( pdu !=NULL && "Memory exhausted" );
  
// Let's encode the minimum compulsory arguments 
  int ret = OCTET_STRING_fromBuf(&pdu->ranFunction_Name.ranFunction_Description, 
                              (const char *)func_def->ranFunction_Name.Description.buf, 
                              func_def->ranFunction_Name.Description.len);
  assert(ret == 0);
  
  ret = OCTET_STRING_fromBuf(&pdu->ranFunction_Name.ranFunction_E2SM_OID, 
                              (const char *)func_def->ranFunction_Name.E2SM_OID.buf, 
                              func_def->ranFunction_Name.E2SM_OID.len);
  assert(ret == 0);
  
  ret = OCTET_STRING_fromBuf(&pdu->ranFunction_Name.ranFunction_ShortName, 
                              (const char *)func_def->ranFunction_Name.ShortName.buf, 
                              func_def->ranFunction_Name.ShortName.len);
  assert(ret == 0);
  
  pdu->ranFunction_Name.ranFunction_Instance = NULL;

  byte_array_t  ba = {.buf = malloc(2048), .len = 2048};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_KPM_RANfunction_Description, pdu, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;


  ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_RANfunction_Description, pdu);

  return ba;
}
