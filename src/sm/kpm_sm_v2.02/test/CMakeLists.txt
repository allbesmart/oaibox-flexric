cmake_minimum_required (VERSION 3.0)
project (test_kpm_mir C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unknown-pragmas  -g -std=gnu11 -fsanitize=address -fno-omit-frame-pointer")

#include_directories(${SOURCE_DIR})
include_directories("/usr/local/share/asn1c/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}../../ie/asn/)

file(GLOB SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/../ie/asn/*.c
)

# file(GLOB SRC_DEC_ASN
#     ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn/*.c
# )

# file(GLOB SRC_ENC_ASN
#     ${CMAKE_CURRENT_SOURCE_DIR}/../enc/enc_asn/*.c
# )


# file(GLOB SRC_DEC_ASN_COMMON
#     ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn_kpm_common/*.c
# )

# file(GLOB SRC_ENC_ASN_COMMON
#     ${CMAKE_CURRENT_SOURCE_DIR}/../enc/enc_asn_kpm_common/*.c
# )

# file(GLOB SRC_LIB_3GPP_DERIVED_IE
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/e2sm_common_ie/3gpp_derived_ie/*.c
# )

# file(GLOB SRC_LIB_SM_COMMON_IE
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/e2sm_common_ie/sm_common_ie/*.c
# )

# file(GLOB SRC_LIB_DEC_ASN_COMMON
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/e2sm_common_ie/dec_asn_sm_common/*.c
# )

# file(GLOB SRC_LIB_ENC_ASN_COMMON
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/e2sm_common_ie/enc_asn_sm_common/*.c
# )

# file(GLOB SRC_LIB_3GPP_DEC_ASN_COMMON
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/e2sm_common_ie/3gpp_derived_ie_dec_asn/*.c
# )

# file(GLOB SRC_LIB_3GPP_ENC_ASN_COMMON
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/e2sm_common_ie/3gpp_derived_ie_enc_asn/*.c
# )


# file(GLOB SRC_LIB_KPM_RIC_INFO
#     ${CMAKE_CURRENT_SOURCE_DIR}/../ie/kpm_data_ie/kpm_ric_info/*.c
# )

# file(GLOB SRC_LIB_KPM_RIC_INFO_COMMON
#     ${CMAKE_CURRENT_SOURCE_DIR}/../ie/kpm_data_ie/data/*.c
# )



option(CODE_COVERAGE "Code coverage" ON)
if(CODE_COVERAGE)
  add_compile_options("-fprofile-arcs;-ftest-coverage")
  add_link_options("-lgcov;-coverage")
  message(STATUS "Code Coverage ON. Example usage: lcov --capture --directory . --output-file coverage.info && genhtml coverage.info --output-directory out && cd out && firefox index.html")

  message(STATUS "Code Coverage ON. Example usage: lcov --capture --directory . --output-file coverage.info && genhtml coverage.info --output-directory out && cd out && firefox index.html")
  message(STATUS "To merge different coverages: lcov --add-tracefile coverage1.info -a coverage2.info ...coverageN -o merged.info")

endif()


# set(OBJECTS_FOR_KPM_TEST
#                           $<TARGET_OBJECTS:e2sm_common_ie_obj>
#                           $<TARGET_OBJECTS:kpm_data_ie_obj>
#                           $<TARGET_OBJECTS:kpm_e2sm_specific_ie_dec_asn_obj>
#                           $<TARGET_OBJECTS:kpm_e2sm_specific_ie_enc_asn_obj>)

add_executable(test_kpm_mir   
                          main.c 
                          fill_rnd_data_kpm.c 
                          ../ie/kpm_data_ie.c
                          ../enc/kpm_enc_asn.c 
                          ../dec/kpm_dec_asn.c 
                          ${SM_ENCODING_KPM_SRC}
                        #   ${OBJECTS_FOR_KPM_TEST}
                          $<TARGET_OBJECTS:e2sm_common_ie_obj>
                          $<TARGET_OBJECTS:kpm_data_ie_obj>
                          $<TARGET_OBJECTS:kpm_e2sm_specific_ie_dec_asn_obj>
                          $<TARGET_OBJECTS:kpm_e2sm_specific_ie_enc_asn_obj>


                        #   ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn/dec_ric_event_trigger_frm_1.c
                            
                        #   ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn/dec_ric_action_def.c
                        #   ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn/dec_ric_action_def_frm_1.c
                        #   ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn/dec_ric_action_def_frm_2.c
                        #   ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn/dec_ric_action_def_frm_3.c
                        #   ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn/dec_ric_action_def_frm_4.c
                        #   ${CMAKE_CURRENT_SOURCE_DIR}/../dec/dec_asn/dec_ric_action_def_frm_5.c

                        #   ${SRC_LIB_KPM_RIC_INFO}
                        #   ${SRC_LIB_KPM_RIC_INFO_COMMON}
                        #   ${SRC_LIB_SM_COMMON_IE}
                        #   ${SRC_LIB_3GPP_DERIVED_IE}


                        #   ${CMAKE_CURRENT_SOURCE_DIR}/../ie/kpm_data_ie/kpm_ric_info/kpm_ric_event_trigger_def.c
                          ${CMAKE_CURRENT_SOURCE_DIR}/../dec/kpm_dec_asn.c
                          ${CMAKE_CURRENT_SOURCE_DIR}/../enc/kpm_enc_asn.c
                          ${CMAKE_CURRENT_SOURCE_DIR}/../../../util/alg_ds/alg/defer.c
                          ${CMAKE_CURRENT_SOURCE_DIR}/../../../util/byte_array.c
              
                          ${SRC}

                        #   ${SRC_DEC_ASN}            
                        #   ${SRC_DEC_ASN_COMMON}            
                        #   ${SRC_LIB_DEC_ASN_COMMON}
                          
                        #   ${SRC_ENC_ASN}            
                        #   ${SRC_ENC_ASN_COMMON}            
                        #   ${SRC_LIB_ENC_ASN_COMMON}

                        #   ${SRC_LIB_3GPP_ENC_ASN_COMMON} 
                        #   ${SRC_LIB_3GPP_DEC_ASN_COMMON} 


                          #kpm_dec_action_def_frm_1_asn
                          #kpm_dec_event_trigger_def_frm_1_asn

                          #defer.c 
                          
                          #cp_ir_to_asn.c 
                          #cp_asn_to_ir.c 
                          #enc_dec_f1ap.c
                          #gen_rnd_data.c 
                          #$<TARGET_OBJECTS:f1ap_types_obj> 
                          )

target_link_libraries(test_kpm_mir PUBLIC -lm
                          $<TARGET_OBJECTS:e2sm_common_ie_obj>
                          $<TARGET_OBJECTS:kpm_data_ie_obj>
                          $<TARGET_OBJECTS:kpm_e2sm_specific_ie_dec_asn_obj>
                          $<TARGET_OBJECTS:kpm_e2sm_specific_ie_enc_asn_obj>)
 
                          
# target_link_libraries(test_kpm_mir  -lm)

target_compile_options(test_kpm_mir PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter)




  target_compile_options(test_kpm_mir PUBLIC "-DASN_DISABLE_OER_SUPPORT -DPDU")
