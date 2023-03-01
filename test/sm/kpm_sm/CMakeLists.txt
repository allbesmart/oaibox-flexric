cmake_minimum_required(VERSION 3.15)


project (TEST_KPM_SM)
set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_C_FLAGS "-Wall -Wextra --std=gnu11 -g -fno-omit-frame-pointer") 
set(SM_ENCODING_KPM "PLAIN" CACHE STRING "The SM encoding to use")
set_property(CACHE SM_ENCODING_KPM PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected SM_ENCODING_KPM: ${SM_ENCODING_KPM} for tests")



if(SM_ENCODING_KPM STREQUAL "ASN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}../ie/asn/ )
  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  file(GLOB asn_sources "../../../src/sm/kpm_sm_v02.03/ie/asn/*.c")
  file(GLOB SRC_LIB_3GPP_DEC_ASN_COMMON
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/lib/e2sm_common_ie/3gpp_derived_ie_dec_asn/*.c)
  file(GLOB SRC_LIB_3GPP_ENC_ASN_COMMON
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/lib/e2sm_common_ie/3gpp_derived_ie_enc_asn/*.c)
  add_executable(test_kpm_sm 
                      main.c 
                      ../../../src/sm/sm_proc_data.c 
                      ../../../src/sm/kpm_sm_v02.03/kpm_sm_agent.c 
                      ../../../src/sm/kpm_sm_v02.03/kpm_sm_ric.c 
                      ../../../src/sm/kpm_sm_v02.03/enc/kpm_enc_asn.c 
                      ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_action_def_frm_1.c

                      ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_action_def_frm_2.c
                      ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_action_def_frm_3.c
                      ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_action_def_frm_4.c
                      ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_action_def_frm_5.c

                      ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_ind_hdr_frm_1.c
                      ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_ind_msg_frm_2.c

                      ${SRC_LIB_3GPP_DEC_ASN_COMMON}
                      ${SRC_LIB_3GPP_ENC_ASN_COMMON}

                      ../../../src/sm/kpm_sm_v02.03/dec/kpm_dec_asn.c 
                      ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie.c 
                      ../../../src/util/alg_ds/alg/defer.c
                      ../../../src/util/alg_ds/alg/eq_float.c
                      ../../../src/util/byte_array.c
                      ../../../src/util/conversions.c
                      fill_kpm_ind_data/fill_kpm_ind_data.c
                      ../../../src/sm/kpm_sm_v02.03/fill_ric_subscription_data/on_ric_subscription.c

                ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/kpm_ric_info/kpm_ric_ind_hdr_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/kpm_ric_info/kpm_ric_ind_msg_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/kpm_ric_info/kpm_ric_action_def_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/kpm_ric_info/kpm_ric_action_def_frm_2.c
                ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/data/label_info_lst.c
                ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/data/meas_info_frm_1_lst.c
                ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/data/meas_data_lst.c
		            ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/data/meas_type.c
                ../../../src/sm/kpm_sm_v02.03/ie/kpm_data_ie/kpm_ric_info/kpm_ran_function_def.c
                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_event_trigger_frm_1.c

                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_ind_msg_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_ind_msg_frm_2.c
                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn/enc_ric_ind_msg_frm_3.c

                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn_kpm_common/enc_meas_info_frm_1.c
                ../../../src/lib/e2sm_common_ie/enc_asn_sm_common/enc_cell_global_id.c

                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn_kpm_common/enc_meas_info_frm_3.c 
                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn_kpm_common/enc_matching_cond_frm_4.c

                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn_kpm_common/enc_meas_data.c
                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn_kpm_common/enc_meas_info_cond_ue.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_event_trigger_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_2.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_3.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_4.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_5.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_ind_hdr_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_ind_msg_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_ind_msg_frm_2.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_ind_msg_frm_3.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_2.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_3.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_4.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn/dec_ric_action_def_frm_5.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/plmn_identity.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/gnb.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/gnb_du.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/gnb_cu_up.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/ng_enb.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/ng_enb_du.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/en_gnb.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/enb.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/guami.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/gummei.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/global_enb_id.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/global_gnb_id.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/global_ng_enb_id.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/global_ng_ran_node_id.c
                ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/nr_cgi.c
		            ../../../src/lib/e2sm_common_ie/3gpp_derived_ie/eutra_cgi.c
                ../../../src/lib/e2sm_common_ie/sm_common_ie/ue_id.c
                ../../../src/lib/e2sm_common_ie/sm_common_ie/cell_global_id.c
                ../../../src/lib/e2sm_common_ie/enc_asn_sm_common/enc_ue_id.c
                ../../../src/lib/e2sm_common_ie/dec_asn_sm_common/dec_ue_id.c

                # Why test and src?
                ../../../test/sm/kpm_sm/fill_kpm_ind_data/fill_ind_hdr_frm_1.c
                ../../../test/sm/kpm_sm/fill_kpm_ind_data/fill_ind_msg_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/fill_ric_subscription_data/fill_kpm_event_trigger_frm_1.c

                ../../../src/sm/kpm_sm_v02.03/fill_ric_subscription_data/fill_kpm_action_def_frm_1.c
                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn_kpm_common/enc_label_info.c
                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn_kpm_common/enc_matching_cond_frm_3.c
                ../../../src/sm/kpm_sm_v02.03/enc/enc_asn_kpm_common/enc_test_info.c 
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_meas_info_frm_1.c
                ../../../src/lib/e2sm_common_ie/dec_asn_sm_common/dec_cell_global_id.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_meas_info_frm_3.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_matching_cond_frm_4.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_meas_data.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_meas_info_cond_ue.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_label_info.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_matching_cond_frm_3.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_matching_cond_frm_4.c
                ../../../src/sm/kpm_sm_v02.03/dec/dec_asn_kpm_common/dec_test_info.c




                      ${asn_sources}
                      )
                        
  # XXX-IMPROVE: maybe we can avoid recompiling objects like asn_sources. 
  target_compile_options(test_kpm_sm PUBLIC "-DASN_DISABLE_OER_SUPPORT")
  target_compile_options(test_kpm_sm PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter)
  target_include_directories(test_kpm_sm PRIVATE "../../../src/sm/kpm_sm_v02.03/ie/asn")
else()
  message(FATAL_ERROR "unsupported encoding type")
endif()

target_compile_definitions(test_kpm_sm PUBLIC ${SM_ENCODING_KPM})
target_link_libraries(test_kpm_sm PUBLIC -pthread)
target_link_libraries(test_kpm_sm PUBLIC m)

enable_testing()
add_test(Unit_test_KPM test_kpm_sm)
