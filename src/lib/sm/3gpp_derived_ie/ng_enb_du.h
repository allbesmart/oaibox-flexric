#ifndef NG_ENB_DU_h
#define NG_ENB_DU_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    // 6.2.3.22
    // C-if CU DU separated
    // ng-eNB-CU UE W1AP ID
    uint32_t ng_enb_cu_ue_w1ap_id;

} ng_enb_du_t;


#ifdef __cplusplus
}
#endif

#endif

// done