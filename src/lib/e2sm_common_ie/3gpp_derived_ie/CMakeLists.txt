set(3GPP_DERIVED_IE_SRCS
    gnb.c
    gnb_du.c
    gnb_cu_up.c
    ng_enb.c
    ng_enb_du.c
    en_gnb.c
    enb.c
    plmn_identity.c
    guami.c
    gummei.c
    global_enb_id.c
    nr_cgi.c
    eutra_cgi.c)

add_library(3gpp_derived_ie_obj OBJECT ${3GPP_DERIVED_IE_SRCS})
              
