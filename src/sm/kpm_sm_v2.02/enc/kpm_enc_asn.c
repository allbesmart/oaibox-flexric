  /*
  * XXX-optimization: understand where do they come these values below for memory allocation of the byte arrays.
  * A tuning of those values would probably benefit this implementation
  * XXX-implementation, cfr: https://gitlab.eurecom.fr/mosaic5g/flexric/-/blob/rrc-sm/src/sm/rrc_sm/enc/rrc_enc_asn.c
  */

#include "../ie/asn/E2SM-KPM-EventTriggerDefinition.h"
#include "../ie/asn/E2SM-KPM-ActionDefinition.h"
#include "../ie/asn/E2SM-KPM-IndicationHeader.h"
#include "../ie/asn/E2SM-KPM-IndicationMessage.h"
#include "../ie/asn/E2SM-KPM-RANfunction-Description.h"
#include "../ie/asn/RANfunction-Name.h"

#include "enc_asn/enc_ric_event_trigger_frm_1.h"

#include "enc_asn/enc_ric_action_def_frm_1.h"
#include "enc_asn/enc_ric_action_def_frm_2.h"
#include "enc_asn/enc_ric_action_def_frm_3.h"
#include "enc_asn/enc_ric_action_def_frm_4.h"
#include "enc_asn/enc_ric_action_def_frm_5.h"

#include "enc_asn/enc_ric_ind_hdr_frm_1.h"

#include "enc_asn/enc_ric_ind_msg_frm_1.h"
#include "enc_asn/enc_ric_ind_msg_frm_2.h"
#include "enc_asn/enc_ric_ind_msg_frm_3.h"

#include "kpm_enc_asn.h"
#include "../../../util/conversions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* Encoding Event Trigger IE
 * Direction of the message: RIC --> E2 Node
 */
byte_array_t kpm_enc_event_trigger_asn(kpm_event_trigger_def_t const* event_trigger) {

  assert(event_trigger != NULL);

  E2SM_KPM_EventTriggerDefinition_t *pdu = calloc(1, sizeof(E2SM_KPM_EventTriggerDefinition_t));
  assert(pdu != NULL && "Memory exhausted" );


  switch (event_trigger->type)
  {
  case FORMAT_1_RIC_EVENT_TRIGGER:{
    pdu->eventDefinition_formats.present = E2SM_KPM_EventTriggerDefinition__eventDefinition_formats_PR_eventDefinition_Format1;
    pdu->eventDefinition_formats.choice.eventDefinition_Format1 = kpm_enc_event_trigger_def_frm_1_asn(&event_trigger->kpm_ric_event_trigger_format_1);
    break;
                                  }
  default:{
    assert("Non valid KPM RIC Event Trigger Format");
          }
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

  pdu->ric_Style_Type = (long)action_def->type;
 
  /* Action Definition Formats */
  switch (action_def->type) 
  {
    case FORMAT_1_ACTION_DEFINITION:
    {
      pdu->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1;
      pdu->actionDefinition_formats.choice.actionDefinition_Format1 = kpm_enc_action_def_frm_1_asn(&action_def->frm_1);
      break;
    }
    case FORMAT_2_ACTION_DEFINITION:
    {
      pdu->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format2;
      pdu->actionDefinition_formats.choice.actionDefinition_Format2 = kpm_enc_action_def_frm_2_asn(&action_def->frm_2);
      break;
    }
    case FORMAT_3_ACTION_DEFINITION:
    {
      pdu->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format3;
      pdu->actionDefinition_formats.choice.actionDefinition_Format3 = kpm_enc_action_def_frm_3_asn(&action_def->frm_3);
      break;
    }
    case FORMAT_4_ACTION_DEFINITION:
    {
      pdu->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format4;
      pdu->actionDefinition_formats.choice.actionDefinition_Format4 = kpm_enc_action_def_frm_4_asn(&action_def->frm_4);
      break;
    }
    case FORMAT_5_ACTION_DEFINITION:
    {
      pdu->actionDefinition_formats.present = E2SM_KPM_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format5;
      pdu->actionDefinition_formats.choice.actionDefinition_Format5 = kpm_enc_action_def_frm_5_asn(&action_def->frm_5);
      break;
    }
    default:
    {
      assert(false && "Non valid KPM RIC Action Definition Format");
    }
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


  switch (ind_hdr->type)
  {
  case FORMAT_1_INDICATION_HEADER:
    pdu->indicationHeader_formats.present = E2SM_KPM_IndicationHeader__indicationHeader_formats_PR_indicationHeader_Format1;
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

  switch (ind_msg->type)
  {
  case FORMAT_1_INDICATION_MESSAGE:
    pdu->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format1;
    pdu->indicationMessage_formats.choice.indicationMessage_Format1 = kpm_enc_ind_msg_frm_1_asn(&ind_msg->frm_1);
    break;
  
  case FORMAT_2_INDICATION_MESSAGE:
    pdu->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format2;
    pdu->indicationMessage_formats.choice.indicationMessage_Format2 = kpm_enc_ind_msg_frm_2_asn(&ind_msg->frm_2);
    break;

  case FORMAT_3_INDICATION_MESSAGE:
    pdu->indicationMessage_formats.present = E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format3;
    pdu->indicationMessage_formats.choice.indicationMessage_Format3 = kpm_enc_ind_msg_frm_3_asn(&ind_msg->frm_3);
    break;

  default:
    assert(false && "Non valid KPM RIC Indication Message Format");
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
  

  //  RAN Function Name
  int ret = OCTET_STRING_fromBuf(&pdu->ranFunction_Name.ranFunction_Description, 
                              (char *)func_def->ran_function_Name.description.buf, 
                              func_def->ran_function_Name.description.len);
  assert(ret == 0);
  
  ret = OCTET_STRING_fromBuf(&pdu->ranFunction_Name.ranFunction_E2SM_OID, 
                              (char *)func_def->ran_function_Name.E2SM_OID.buf, 
                              func_def->ran_function_Name.E2SM_OID.len);
  assert(ret == 0);
  
  ret = OCTET_STRING_fromBuf(&pdu->ranFunction_Name.ranFunction_ShortName, 
                              (char *)func_def->ran_function_Name.short_name.buf, 
                              func_def->ran_function_Name.short_name.len);
  assert(ret == 0);
  
  if (func_def->ran_function_Name.instance != NULL)
  {
    pdu->ranFunction_Name.ranFunction_Instance = malloc(sizeof(*pdu->ranFunction_Name.ranFunction_Instance));
    pdu->ranFunction_Name.ranFunction_Instance = func_def->ran_function_Name.instance;
  }
  else
  {
    pdu->ranFunction_Name.ranFunction_Instance = NULL;
  }
  


  //  RIC Event Trigger Style Item
  if (func_def->ric_event_trigger_style_list_len != 0)
  {
    assert(false && "RIC Event Style not yet implemented");
  }
  else
  {
    pdu->ric_EventTriggerStyle_List = NULL;
  }



  // RIC Report Style Item
  if (func_def->ric_report_style_list_len != 0)
  {
    assert(false && "RIC Report Style not yet implemented");
  }
  else
  {
    pdu->ric_ReportStyle_List = NULL;
  }



  byte_array_t  ba = {.buf = malloc(2048), .len = 2048};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_KPM_RANfunction_Description, pdu, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;


  ASN_STRUCT_FREE(asn_DEF_E2SM_KPM_RANfunction_Description, pdu);

  return ba;
}
