cmake_minimum_required(VERSION 3.15) # setting this is required
project(rc_sm)            # this sets the project name

set(SM_ENCODING_RC_SRC
  ../sm_proc_data.c 
  rc_sm_agent.c 
  rc_sm_ric.c 
  ../../util/byte_array.c 
  ../../util/alg_ds/alg/defer.c 
  ../../util/alg_ds/alg/eq_float.c 
  ../../util/alg_ds/ds/seq_container/seq_arr.c 
  ../../util/alg_ds/ds/seq_container/seq_ring.c 
  ../../util/alg_ds/ds/assoc_container/assoc_rb_tree.c
  ../../util/alg_ds/ds/assoc_container/bimap.c
  ie/rc_data_ie.c 
  )


if(SM_ENCODING_RC STREQUAL "PLAIN")
  message(FATAL_ERROR "RC SM FB not implemented")
elseif(SM_ENCODING_RC STREQUAL "ASN" )
  add_subdirectory(ie/asn)
  add_subdirectory(ie/ir)

  add_library(rc_sm SHARED
                     ${SM_ENCODING_RC_SRC}
                      enc/rc_enc_asn.c 
                      dec/rc_dec_asn.c 
                      $<TARGET_OBJECTS:e2sm_rc_asn1_obj>
                      $<TARGET_OBJECTS:e2sm_rc_ir_obj>
                      )
  target_include_directories(rc_sm PRIVATE "ie/asn")
  target_compile_options(rc_sm PUBLIC "-DASN_DISABLE_OER_SUPPORT")
  target_compile_options(rc_sm PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter)

elseif(SM_ENCODING_RC STREQUAL "FLATBUFFERS" )
  message(FATAL_ERROR "RC SM FB not implemented")
  add_library(rc_sm SHARED
                     ${SM_ENCODING_RC_SRC}
                      enc/rc_enc_fb.c 
                      dec/rc_dec_fb.c 
                      )
else()
  message(FATAL_ERROR "Unknown SM encoding type ")
endif()

target_compile_definitions(rc_sm PUBLIC ${SM_ENCODING_RC})

