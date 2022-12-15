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
 * This interface implements the Information Elements (IE) data structures and algorithms according to O-RAN.WG3.E2SM-KPM-v02.02 and 
 * the 5 associate O-RAN Procedures. Note that IEs 'RIC Call Process ID, RIC Control Header, RIC Control Message and RIC Control 
 * Outcome' are not to be implemented.
 * 
 * IE for functional procedures:
 *  SEC 1. RIC Event Trigger Definition
 *  SEC 2. RIC Action Definition
 *  SEC 3. RIC Indication Header 
 *  SEC 4. RIC Indication Message 
 * IE for global procedures:
 *  SEC 5. RAN Function Definition
 * 
 * Procedures:
 * SEC 6. RIC Subscription, RIC Indication, RIC Control, E2 Setup and RIC Service Update 
 * 
 * Caveats
 * The data types inputs to the IE functions form an adapter layer from tradition C data types (i.e. string = char * ) to 
 * ASN1/Flatbuffer generated data types. It is done just for convenience so that the main code of the RIC or the one from RAN
 * can use traditional datatypes. In theory, if you have just ASN1, you could directly use the ASN1 generated datatypes in the 
 * encoding/decoding routines, obsoleting this adapter.
 */

#ifndef KPM_DATA_INFORMATION_ELEMENTS_H
#define KPM_DATA_INFORMATION_ELEMENTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "../../../util/byte_array.h"
//#include "../../../lib/ap/e2ap_types/common/e2ap_plmn.h"


/*******************************************************
 * SEC 1. RIC Event Trigger Definition as per $8.2.1.1
 *******************************************************/



/*******************************************************
 * SEC 2. RIC Action Definition as per $8.2.1.2
 *******************************************************/


/************************************************
 * SEC 3. RIC Indication Header as per $8.2.1.3.1
 ************************************************/

/**************************************************
 * SEC 4. RIC Indication Message as per $8.2.1.4.1
 **************************************************/







/*************************************************
 * SEC 5. RAN Function Definition as per $8.2.2.1
 *************************************************/
typedef struct {
  byte_array_t	 ShortName;   // “ORAN-E2SM-KPM” aka SM_KPM_STR
	byte_array_t	 E2SM_OID;    // see cfr. O-RAN.WG3.E2SM-v02.01.pdf, table 5.1
	byte_array_t	 Description; // “KPM Monitor”
	long	         *ranFunction_Instance;	// OPTIONAL: it is suggested to be used when E2 Node declares
                                                    // multiple RAN Function ID supporting the same  E2SM specification
} ranFunction_Name_t; // cfr. O-RAN.WG3.E2SM-v02.01.pdf, $6.2.2.1

typedef struct {
// TODO
} ric_EventTriggerStyleItem_t; 

typedef struct {
// TODO
} ric_ReportStyleItem_t;


typedef struct {
  ranFunction_Name_t ranFunction_Name;

  ric_EventTriggerStyleItem_t *ric_EventTriggerStyle_List; // OPTIONAL: used in action definition, only type 1 supported for the moment
  size_t ric_EventTriggerStyle_List_len; // 0..maxnoofRICStyles 
  
  ric_ReportStyleItem_t *ric_ReportStyle_List;    // OPTIONAL: used in indication message, only type 1 supported for the mome   
  size_t ric_ReportStyle_List_len; // 0..maxnoofRICStyles
} kpm_func_def_t;

/****************************************************************************************
 * SEC 6. RIC Subscription, RIC Indication, RIC Control, E2 Setup and RIC Service Update 
 ****************************************************************************************/
// RIC subscription
typedef struct {
  kpm_event_trigger_t et; 
  kpm_action_def_t    *ad;
} kpm_sub_data_t; 

// RIC indication
typedef struct {
  kpm_ind_hdr_t hdr;
  kpm_ind_msg_t msg;
} kpm_ind_data_t; 


void            free_kpm_ind_data(kpm_ind_data_t* ind);
kpm_ind_data_t  cp_kpm_ind_data(kpm_ind_data_t const* src);


// SETUP REQUEST and RIC SERVICE UPDATE use the 'RAN function definition' IE
typedef struct {
  kpm_func_def_t func_def;
} kpm_setup_data_t;
void free_kpm_func_def(kpm_func_def_t* src);

#ifdef __cplusplus
}
#endif

#endif
