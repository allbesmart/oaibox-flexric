cmake_minimum_required(VERSION 3.15) # setting this is required
project(kpm_sm)            # this sets the project name

add_subdirectory(dec)
add_subdirectory(enc)
add_subdirectory(ie)
add_subdirectory(test)
# KPM Service Model
#set(SM_ENCODING_KPM "ASN" CACHE STRING "The KPM SM encoding to use")
#set_property(CACHE SM_ENCODING_KPM PROPERTY STRINGS "ASN")
#message(STATUS "Selected KPM SM_ENCODING: ${SM_ENCODING_KPM}")


set(SM_ENCODING_KPM_SRC
                      ../sm_proc_data.c 
                      kpm_sm_ric.c 
                      kpm_sm_agent.c 
                      ../../util/byte_array.c 
                      ../../util/conversions.c
                      ../../util/alg_ds/alg/defer.c 
                      ../../util/alg_ds/alg/eq_float.c 
                      ../../util/alg_ds/ds/seq_container/seq_arr.c 
                      ../../util/alg_ds/ds/seq_container/seq_ring.c 
                      ../../util/alg_ds/ds/assoc_container/assoc_rb_tree.c
                      ../../util/alg_ds/ds/assoc_container/bimap.c
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
                      ${SM_ENCODING_KPM_SRC}
                      enc/kpm_enc_asn.c 
                      dec/kpm_dec_asn.c 
                      )


  target_link_libraries(kpm_sm PUBLIC
                                kpm_data_ie_shared
                                kpm_e2sm_specific_ie_dec_asn_shared
                                kpm_e2sm_specific_ie_enc_asn_shared
                                -lm)

  target_include_directories(kpm_sm PRIVATE "ie/asn")
  target_compile_options(kpm_sm PUBLIC "-DASN_DISABLE_OER_SUPPORT" -fPIC)
  target_compile_options(kpm_sm PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)


  #Nasty solution. Do it properly, Mikel!

  add_library(kpm_sm_static STATIC  #STATIC or SHARED


                      ${SM_ENCODING_KPM_SRC}
                      enc/kpm_enc_asn.c 
                      dec/kpm_dec_asn.c 
            )
  
  target_link_libraries(kpm_sm_static PUBLIC
                                kpm_data_ie_shared
                                kpm_e2sm_specific_ie_dec_asn_shared
                                kpm_e2sm_specific_ie_enc_asn_shared
                                -lm)

  target_include_directories(kpm_sm_static PRIVATE "ie/asn")
  target_compile_options(kpm_sm_static PRIVATE "-DASN_DISABLE_OER_SUPPORT")




elseif(SM_ENCODING_KPM STREQUAL "FLATBUFFERS" )
  message(FATAL_ERROR "KPM SM FB not implemented")
else()
  message(FATAL_ERROR "Unknown KPM SM encoding type")
endif()

target_compile_definitions(kpm_sm PUBLIC ${SM_ENCODING_KPM})
target_compile_definitions(kpm_sm_static PUBLIC ${SM_ENCODING_KPM})

