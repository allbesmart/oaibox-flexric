cmake_minimum_required(VERSION 3.15) # setting this is required
project(kpm_sm)            # this sets the project name


# KPM Service Model
#set(SM_ENCODING_KPM "ASN" CACHE STRING "The KPM SM encoding to use")
#set_property(CACHE SM_ENCODING_KPM PROPERTY STRINGS "ASN")
#message(STATUS "Selected KPM SM_ENCODING: ${SM_ENCODING_KPM}")


set(SM_ENCODING_KPM_SRC
                      ../sm_proc_data.c 
                      kpm_sm_ric.c 
                      kpm_sm_agent.c 
                      ../../util/byte_array.c 
                      ../../util/alg_ds/alg/defer.c 
                      ../../util/alg_ds/alg/eq_float.c 
                      ../../util/alg_ds/ds/seq_container/seq_arr.c 
                      ../../util/alg_ds/ds/seq_container/seq_ring.c 
                      ../../util/alg_ds/ds/assoc_container/assoc_rb_tree.c
                      ../../util/alg_ds/ds/assoc_container/bimap.c
                      ie/kpm_data_ie.c

                      ie/kpm_data_ie/data/label_info_lst.c
                      ie/kpm_data_ie/kpm_ric_info/kpm_ran_function_def.c
                      ie/kpm_data_ie/kpm_ric_info/kpm_ric_action_def_frm_1.c
                      ie/kpm_data_ie/kpm_ric_info/kpm_ric_ind_hdr_frm_1.c
                      ie/kpm_data_ie/kpm_ric_info/kpm_ric_ind_msg_frm_1.c

                      )

if(SM_ENCODING_KPM STREQUAL "PLAIN")
  add_library(kpm_sm SHARED
                      ${SM_ENCODING_KPM_SRC}
                      enc/kpm_enc_plain.c 
                      dec/kpm_dec_plain.c 
                      )
elseif(SM_ENCODING_KPM STREQUAL "ASN")
  
  add_subdirectory(ie/asn)
  add_library(kpm_sm SHARED
                      $<TARGET_OBJECTS:e2sm_kpm_asn1_obj>
                      ${SM_ENCODING_KPM_SRC}
                      enc/kpm_enc_asn.c 
                      dec/kpm_dec_asn.c 
                      )
  target_link_libraries(kpm_sm PUBLIC -lm)
  target_include_directories(kpm_sm PRIVATE "ie/asn")
  target_compile_options(kpm_sm PUBLIC "-DASN_DISABLE_OER_SUPPORT" -fPIC)
  target_compile_options(kpm_sm PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)

elseif(SM_ENCODING_KPM STREQUAL "FLATBUFFERS" )
  message(FATAL_ERROR "KPM SM FB not implemented")
else()
  message(FATAL_ERROR "Unknown KPM SM encoding type")
endif()

target_compile_definitions(kpm_sm PUBLIC ${SM_ENCODING_KPM})
