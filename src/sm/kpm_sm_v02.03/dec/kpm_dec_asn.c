#include "../ie/asn/E2SM-KPM-EventTriggerDefinition-Format1.h"
#include "../ie/asn/E2SM-KPM-EventTriggerDefinition.h"
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
#include "../ie/asn/E2SM-KPM-ActionDefinition.h"
#include "../ie/asn/E2SM-KPM-ActionDefinition-Format1.h"
#include "../ie/asn/MeasurementInfoItem.h"
#include "../ie/asn/MeasurementType.h"
#include "../ie/asn/LabelInfoItem.h"
#include "../ie/asn/asn_constant.h"

#include "dec_asn/dec_ric_event_trigger_frm_1.h"

#include "dec_asn/dec_ric_action_def_frm_1.h"
#include "dec_asn/dec_ric_action_def_frm_2.h"
#include "dec_asn/dec_ric_action_def_frm_3.h"
#include "dec_asn/dec_ric_action_def_frm_4.h"
#include "dec_asn/dec_ric_action_def_frm_5.h"

#include "dec_asn/dec_ric_ind_hdr_frm_1.h"

#include "dec_asn/dec_ric_ind_msg_frm_1.h"
#include "dec_asn/dec_ric_ind_msg_frm_2.h"
#include "dec_asn/dec_ric_ind_msg_frm_3.h"

#include "kpm_dec_asn.h"
#include "../../../util/conversions.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


kpm_event_trigger_def_t kpm_dec_event_trigger_asn(size_t len, uint8_t const ev_tr[len])
{
  assert(len>0);
  assert(ev_tr != NULL);

  E2SM_KPM_EventTriggerDefinition_t *pdu = calloc(1, sizeof(E2SM_KPM_EventTriggerDefinition_t));
  assert( pdu !=NULL && "Memory exhausted" );

  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  const asn_dec_rval_t rval = asn_decode(NULL, syntax, &asn_DEF_E2SM_KPM_EventTriggerDefinition, (void**)&pdu, ev_tr, len);
  assert(rval.code == RC_OK && "Are you sending data in ATS_ALIGNED_BASIC_PER syntax?");

  xer_fprint(stderr, &asn_DEF_E2SM_KPM_EventTriggerDefinition, pdu);


  kpm_event_trigger_def_t ret = {0};


  switch (pdu->eventDefinition_formats.present)
  {
  case E2SM_KPM_EventTriggerDefinition__eventDefinition_formats_PR_eventDefinition_Format1:
    ret.type = FORMAT_1_RIC_EVENT_TRIGGER;
    ret.kpm_ric_event_trigger_format_1 = kpm_dec_event_trigger_def_frm_1_asn(pdu->eventDefinition_formats.choice.eventDefinition_Format1);
    break;
  
  default:
    assert("Non valid KPM RIC Event Trigger Format");
  }


  ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_E2SM_KPM_EventTriggerDefinition,pdu);
  free(pdu);

  return ret;
}


kpm_act_def_t kpm_dec_action_def_asn(size_t len, uint8_t const action_def[len]) 
{
  assert(len>0);
  assert(action_def != NULL);

  kpm_act_def_t ret = {0};

  E2SM_KPM_ActionDefinition_t *pdu = calloc(1, sizeof(E2SM_KPM_ActionDefinition_t));
  assert( pdu !=NULL && "Memory exhausted" );
  
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  const asn_dec_rval_t rval = asn_decode(NULL, syntax, &asn_DEF_E2SM_KPM_ActionDefinition, (void**)&pdu, action_def, len);
  assert(rval.code == RC_OK && "Are you sending data in ATS_ALIGNED_BASIC_PER syntax?");
  // note that constraints checking on data extracted is already performed by asn_decode()

  xer_fprint(stderr, &asn_DEF_E2SM_KPM_ActionDefinition, pdu);

  
  switch (pdu->actionDefinition_formats.present)
  {
    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1:
      ret.type = FORMAT_1_ACTION_DEFINITION;
      ret.frm_1 = kpm_dec_action_def_frm_1_asn(pdu->actionDefinition_formats.choice.actionDefinition_Format1);
      break;

    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format2:
      ret.type = FORMAT_2_ACTION_DEFINITION;
      ret.frm_2 = kpm_dec_action_def_frm_2_asn(pdu->actionDefinition_formats.choice.actionDefinition_Format2);
      break;

    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format3:
      ret.type = FORMAT_3_ACTION_DEFINITION;
      ret.frm_3 = kpm_dec_action_def_frm_3_asn(pdu->actionDefinition_formats.choice.actionDefinition_Format3);
      break;

    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format4:
      ret.type = FORMAT_4_ACTION_DEFINITION;
      ret.frm_4 = kpm_dec_action_def_frm_4_asn(pdu->actionDefinition_formats.choice.actionDefinition_Format4);
      break;
      
    case E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format5:
      ret.type = FORMAT_5_ACTION_DEFINITION;
      ret.frm_5 = kpm_dec_action_def_frm_5_asn(pdu->actionDefinition_formats.choice.actionDefinition_Format5);
      break;

    default:
      assert(false && "Non valid KPM RIC Action Definition Format");
  }
  
  ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_E2SM_KPM_ActionDefinition, pdu);
  free(pdu);
  return ret;
  
}

kpm_ind_hdr_t kpm_dec_ind_hdr_asn(size_t len, uint8_t const ind_hdr[len])
{
  assert(len>0);
  assert(ind_hdr != NULL);

  kpm_ind_hdr_t ret = {0};

  E2SM_KPM_IndicationHeader_t *pdu = calloc(1, sizeof(E2SM_KPM_IndicationHeader_t));
  assert( pdu !=NULL && "Memory exhausted" );

  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  const asn_dec_rval_t rval = asn_decode(NULL, syntax, &asn_DEF_E2SM_KPM_IndicationHeader, (void**)&pdu, ind_hdr, len);
  assert(rval.code == RC_OK && "Are you sending data in ATS_ALIGNED_BASIC_PER syntax?");

  xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationHeader, pdu);


  switch (pdu->indicationHeader_formats.present)
  {
  case E2SM_KPM_IndicationHeader__indicationHeader_formats_PR_indicationHeader_Format1:
    ret.type = FORMAT_1_INDICATION_HEADER;
    ret.kpm_ric_ind_hdr_format_1 = kpm_dec_ind_hdr_frm_1_asn(pdu->indicationHeader_formats.choice.indicationHeader_Format1);
    break;
  
  default:
    assert(false && "Non valid KPM RIC Indication Header Format");
  }


	ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_E2SM_KPM_IndicationHeader, pdu);
  free(pdu);

  return ret;
}



kpm_ind_msg_t kpm_dec_ind_msg_asn(size_t len, uint8_t const ind_msg[len])
{
  assert(ind_msg != NULL);
  assert(len>0);

  kpm_ind_msg_t ret = {0};

  E2SM_KPM_IndicationMessage_t *pdu = calloc(1, sizeof(E2SM_KPM_IndicationMessage_t));
  assert( pdu !=NULL && "Memory exhausted" );

  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  const asn_dec_rval_t rval = asn_decode(NULL, syntax, &asn_DEF_E2SM_KPM_IndicationMessage, (void**)&pdu, ind_msg, len);
  assert(rval.code == RC_OK && "Are you sending data in ATS_ALIGNED_BASIC_PER syntax?");

  xer_fprint(stderr, &asn_DEF_E2SM_KPM_IndicationMessage, pdu);


  switch (pdu->indicationMessage_formats.present)
  {
  case E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format1:
    ret.type = FORMAT_1_INDICATION_MESSAGE;
    ret.frm_1 = kpm_dec_ind_msg_frm_1_asn(pdu->indicationMessage_formats.choice.indicationMessage_Format1);
    break;
  
  case E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format2:
    ret.type = FORMAT_2_INDICATION_MESSAGE;
    ret.frm_2 = kpm_dec_ind_msg_frm_2_asn(pdu->indicationMessage_formats.choice.indicationMessage_Format2);
    break;

  case E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format3:
    ret.type = FORMAT_3_INDICATION_MESSAGE;
    ret.frm_3 = kpm_dec_ind_msg_frm_3_asn(pdu->indicationMessage_formats.choice.indicationMessage_Format3);
    break;

  default:
    assert(false && "Non valid KPM RIC Indication Message Format");
  }


  ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_E2SM_KPM_IndicationMessage, pdu);
  free(pdu); 

  return ret;
}

kpm_ran_function_def_t kpm_dec_func_def_asn(size_t len, uint8_t const func_def[len])
{
  assert(func_def != NULL);
  assert(len>0);

  kpm_ran_function_def_t ret = {0};

  E2SM_KPM_RANfunction_Description_t *pdu = calloc(1, sizeof(E2SM_KPM_RANfunction_Description_t));
  assert( pdu !=NULL && "Memory exhausted" );

  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  const asn_dec_rval_t rval = asn_decode(NULL, syntax, &asn_DEF_E2SM_KPM_RANfunction_Description, (void**)&pdu, func_def, len);
  assert(rval.code == RC_OK && "Are you sending data in ATS_ALIGNED_BASIC_PER syntax?");

  xer_fprint(stderr, &asn_DEF_E2SM_KPM_RANfunction_Description, pdu);
  

  //  RAN Function Name
  ret.ran_function_Name.description.len = pdu->ranFunction_Name.ranFunction_Description.size;
  ret.ran_function_Name.description.buf = malloc(ret.ran_function_Name.description.len);
  memcpy(ret.ran_function_Name.description.buf, pdu->ranFunction_Name.ranFunction_Description.buf, ret.ran_function_Name.description.len);

  ret.ran_function_Name.E2SM_OID.len = pdu->ranFunction_Name.ranFunction_E2SM_OID.size;
  ret.ran_function_Name.E2SM_OID.buf = malloc(ret.ran_function_Name.E2SM_OID.len);
  memcpy(ret.ran_function_Name.E2SM_OID.buf, pdu->ranFunction_Name.ranFunction_E2SM_OID.buf, ret.ran_function_Name.E2SM_OID.len);
  
  ret.ran_function_Name.short_name.len = pdu->ranFunction_Name.ranFunction_ShortName.size;
  ret.ran_function_Name.short_name.buf = malloc(ret.ran_function_Name.short_name.len);
  memcpy(ret.ran_function_Name.short_name.buf, pdu->ranFunction_Name.ranFunction_ShortName.buf, ret.ran_function_Name.short_name.len);
  
  if (pdu->ranFunction_Name.ranFunction_Instance != NULL)
  {
    ret.ran_function_Name.instance = malloc(sizeof(*ret.ran_function_Name.instance));
    ret.ran_function_Name.instance = pdu->ranFunction_Name.ranFunction_Instance;
  }
  else
  {
    ret.ran_function_Name.instance = NULL;
  }


  //  RIC Event Trigger Style Item
  if (pdu->ric_EventTriggerStyle_List != NULL)
  {
    assert(false && "RIC Event Style not yet implemented");
  }
  else
  {
    ret.ric_event_trigger_style_list_len = 0;
    ret.ric_event_trigger_style_list = NULL;
  }


  // RIC Report Style Item
  if (pdu->ric_ReportStyle_List != NULL)
  {
    assert(false && "RIC Report Style not yet implemented");
  }
  else
  {
    ret.ric_report_style_list_len = 0;
    ret.ric_report_style_list = NULL;
  }


  ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_E2SM_KPM_RANfunction_Description, pdu);
  free(pdu); 
  
  return ret;
}
