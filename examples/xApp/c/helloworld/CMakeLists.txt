
add_executable(xapp_hw
				hw.c
				../../../../src/util/alg_ds/alg/defer.c
				../../../../src/util/ngran_type.c
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
		../../../../src/lib/e2sm_common_ie/3gpp_derived_ie/plmn_identity.c
		../../../../src/lib/e2sm_common_ie/sm_common_ie/ue_id.c

				)

target_link_libraries(xapp_hw
						PUBLIC
						e42_xapp
						-pthread
						-lsctp
						-ldl
						)

