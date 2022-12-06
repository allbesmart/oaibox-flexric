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
#include "../../../lib/ap/e2ap_types/common/e2ap_plmn.h"
/* 
 * SEC 0: General data types that make the mapping between ASN data types and RIC ones
 */

typedef struct S_NSSAI {
	byte_array_t	  sST;
	byte_array_t	  *sD;	/* OPTIONAL */
} S_NSSAI_t;

/* 
 * Structure 'LabelInformationItem_t_t' defines the values of the subcounters that are applicable to an associated measurement type
 * identified by measName or measID. All the fields are indicated as optional. If value is != NULL, it means presence of the optional 
 * field.
 */
typedef struct LabelInformationItem_t {
  long	                        *noLabel;	/* OPTIONAL: looks like this is an enumeration datatype that accepts only true (0) */
	plmn_t                        *plmn_id;  /* OPTIONAL */
	S_NSSAI_t       	            *sliceID;	/* OPTIONAL */
	long                          *fiveQI;	/* OPTIONAL */
	long                      	  *qFI;	    /* OPTIONAL */
	long        	                *qCI;	    /* OPTIONAL */
	long        	                *qCImax;	/* OPTIONAL */
	long        	                *qCImin;	/* OPTIONAL */
	long	                        *aRPmax;	/* OPTIONAL */
	long	                        *aRPmin;	/* OPTIONAL */
	long	                        *bitrateRange;/* OPTIONAL */
	long	                        *layerMU_MIMO;/* OPTIONAL */
	long	                        *sUM;	    /* OPTIONAL */
	long	                        *distBinX;/* OPTIONAL */
	long	                        *distBinY;/* OPTIONAL */
	long	                        *distBinZ;/* OPTIONAL */
	long	                        *preLabelOverride;/* OPTIONAL */
	long	                        *startEndInd;	/* OPTIONAL */
	long	                        *min;	    /* OPTIONAL */
	long	                        *max;	    /* OPTIONAL */
	long	                        *avg;	    /* OPTIONAL */
} LabelInformationItem_t;

void free_label_info(LabelInformationItem_t *l);
void cp_label_info(LabelInformationItem_t *dst, LabelInformationItem_t const *src);
typedef enum {
    KPM_V2_MEASUREMENT_TYPE_NAME = 1, 
    KPM_V2_MEASUREMENT_TYPE_ID = 2
  }	meas_type_e;


typedef struct MeasInfo_t {
	meas_type_e meas_type;
  byte_array_t meas_name;
  long meas_id;
	LabelInformationItem_t	         *labelInfo;   // list implemented as array having a maximum of 'maxnoofLabelInfo' items
  size_t                           labelInfo_len;// length of the array labelInfo
} MeasInfo_t; 

/*******************************************************
 * SEC 1. RIC Event Trigger Definition as per $8.2.1.1
 *******************************************************/
typedef struct kpm_event_trigger_t {
  unsigned long ms; // reporting period in milliseconds
} kpm_event_trigger_t;



typedef enum { 
  KPMV2_CELL_ID_CHOICE_NOTHING = 0, 
  KPMV2_CELL_ID_CHOICE_NR_CGI, 
  KPMV2_CELL_ID_CHOICE_EUTRA_CGI 
} cell_global_id_t;

/*******************************************************
 * SEC 2. RIC Action Definition as per $8.2.1.2
 *******************************************************/
typedef struct kpm_action_def_t
{
  /*
   * RIC Style Type 1:  E2 Node Measurement. Used to carry measurement report from a target E2 Node. More in details, 
   *                    it contains measurement types that Near-RT RIC is requesting to subscribe followed by a list 
   *                    of subcounters to be measured for each measurement type, and a granularity period
   *                    indicating collection interval of those measurements.
   * RIC Style Type 2: Used to carry measurement report for a single UE of interest from a target E2 Node
   * RIC Style Type 3: Used to carry UE-level measurement report for a group of UEs per
   *                   measurement type matching subscribed conditions from a target E2 Node
   * RIC Style Type 4: Used to carry measurement report for a group of UEs across a set of
   *                   measurement types satisfying common subscribed conditions from a target E2 Node
   * RIC Style Type 5: Used to carry measurement report for multiple UE of interest from a target E2 Node
   */
  long                          ric_style_type; // values: 1..5. This number defines the action definition type
  
  unsigned long                 granularity_period; // Measurement collection interval expressed in unit of 1 millisecond.

  /* 
   * list implemented as array of length 'MeasInfo_len' containing measurement names like 'DL Transmitted Data Volume' or 
   * its correponding ID
   */
  size_t                        MeasInfo_len; // compulsory grater than 0
  MeasInfo_t                    *MeasInfo;    
  
  // If cellGlobalIDtype == choice_NOTHING, the field 'cellGlobalID' in asn format will be NULL
  cell_global_id_t cell_global_id;

  uint64_t            nRCellIdentity;
  byte_array_t	      pLMNIdentity;
	uint64_t            eUTRACellIdentity;


  /* 
   * XXX-extensions: below add all the info you might find in all the actions types . 
   * Still missing some fields for action_def_2, action_def_3, action_def_4, action_def_5.
   */
} kpm_action_def_t;

void free_kpm_action_def(kpm_action_def_t* src);
/************************************************
 * SEC 3. RIC Indication Header as per $8.2.1.3.1
 ************************************************/
typedef struct {
  uint32_t collectStartTime;
  byte_array_t fileformat_version;
  byte_array_t sender_name;
  byte_array_t sender_type;
  byte_array_t vendor_name;
} kpm_ind_hdr_t;

void          free_kpm_ind_hdr(kpm_ind_hdr_t* src);
kpm_ind_hdr_t cp_kpm_ind_hdr(kpm_ind_hdr_t const* src);
/**************************************************
 * SEC 4. RIC Indication Message as per $8.2.1.4.1
 **************************************************/

typedef struct MeasRecord_t {
  enum {MeasRecord_int=1, MeasRecord_real,  MeasRecord_noval} type;
	unsigned long	  int_val;
	double	        real_val;
} MeasRecord_t;

typedef struct MeasDataItem_t {
  size_t                    measRecord_len; // 1..
	MeasRecord_t        	    *measRecord; 
	long	                    *incompleteFlag;	// OPTIONAL: true(0) value indicates that the measurements record 
                                            // is not reliable asn we pass to ASN this info, -1 means that the flag is not present
} MeasDataItem_t;

typedef struct {
  size_t                    MeasData_len; // 1..
  MeasDataItem_t            *MeasData;

  /* 
   * list implemented as array of length 'MeasInfo_len' containing measurement names like 'DL Transmitted Data Volume' or 
   * its corresponding ID. It is the same mechanism used for 'action definition type 1'
   */
  size_t                    MeasInfo_len; 
  MeasInfo_t                *MeasInfo;    // OPTIONAL, MeasInfo_len can be zero

	unsigned long             *granulPeriod;	/* OPTIONAL */

  /* 
   * XXX-extensions: add all the info you might find in all the indication format types.
   * Still missing some fields for supporting format_2 and format_3
   */
} kpm_ind_msg_t;

void          free_kpm_ind_msg(kpm_ind_msg_t* src);
kpm_ind_msg_t cp_kpm_ind_msg(kpm_ind_msg_t const* src);
bool          eq_kpm_ind_msg(kpm_ind_msg_t const* m0, kpm_ind_msg_t const* m1);

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
