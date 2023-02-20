
add_executable(xapp_slice_moni_ctrl 
             xapp_slice_moni_ctrl.c
                ../../../../src/util/alg_ds/alg/defer.c
                ../../../../src/sm/mac_sm/ie/mac_data_ie.c
                ../../../../src/sm/rlc_sm/ie/rlc_data_ie.c
                ../../../../src/sm/pdcp_sm/ie/pdcp_data_ie.c
                ../../../../src/sm/slice_sm/ie/slice_data_ie.c
                ../../../../src/sm/tc_sm/ie/tc_data_ie.c
                ../../../../src/sm/gtp_sm/ie/gtp_data_ie.c
                ../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie.c
        ../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie/kpm_ric_info/kpm_ric_ind_hdr_frm_1.c
        ../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie/kpm_ric_info/kpm_ric_ind_msg_frm_1.c
        ../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie/kpm_ric_info/kpm_ric_action_def_frm_1.c
        ../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie/kpm_ric_info/kpm_ric_action_def_frm_2.c
        ../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie/data/label_info_lst.c
        ../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie/data/meas_info_frm_1_lst.c
        ../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie/data/meas_data_lst.c
	../../../../src/sm/kpm_sm_v2.02/ie/kpm_data_ie/data/meas_type.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/plmn_identity.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/gnb.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/gnb_du.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/gnb_cu_up.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/ng_enb.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/ng_enb_du.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/en_gnb.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/enb.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/guami.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/gummei.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/global_enb_id.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/global_gnb_id.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/global_ng_enb_id.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/global_ng_ran_node_id.c
        ../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/nr_cgi.c
	../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/eutra_cgi.c
        ../../../../src/lib/e2sm_common_ie/sm_common_ie/ue_id.c
        ../../../../src/lib/e2sm_common_ie/sm_common_ie/cell_global_id.c

                )




target_link_libraries(xapp_slice_moni_ctrl
                      PUBLIC
                      e42_xapp
                      -pthread
                      -lsctp
                      -ldl
                      )



