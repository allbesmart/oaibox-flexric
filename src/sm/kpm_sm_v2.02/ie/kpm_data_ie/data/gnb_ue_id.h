#ifndef GNB_UE_ID_KPMV2_h
#define GNB_UE_ID_KPMV2_h

#include <stdint.h>
#include <stdlib.h>

#include "gnb_cu_ue_f1ap_lst.h"
#include "guami.h"


typedef struct{

  // 6.2.3.16
  // Mandatory
  // AMF UE NGAP ID
  uint64_t amf_ue_ngapid; // [0, 2^40 ]

  // Mandatory
  //GUAMI 6.2.3.17 
  guami_t guami;

  // gNB-CU UE F1AP ID List
  // C-ifCUDUseparated [1,4]
  size_t sz_gnb_cu_ue_f1ap_lst; 
  gnb_cu_ue_f1ap_lst_t* gnb_cu_ue_f1ap_lst;

  //gNB-CU-CP UE E1AP
  //ID List
  //C-ifCPUPseparated [1, 65535]


  // RAN UE ID
  // Optional
  // 6.2.3.25


  //  M-NG-RAN node UE XnAP ID
  // C- ifDCSetup
  // 6.2.3.19



  // Global gNB ID
  // 6.2.3.3
  // Optional



  // Global NG-RAN Node ID
  // C-ifDCSetup
  // 6.2.3.2




} gnb_ue_id_t ;


#endif

