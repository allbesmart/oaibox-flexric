set(SM_COMMON_ENC_ASN_SRCS
    enc_cell_global_id.c
    enc_ue_id.c)

add_library(sm_common_enc_asn_obj OBJECT ${SM_COMMON_ENC_ASN_SRCS})


target_include_directories(sm_common_enc_asn_obj PUBLIC
                                         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                         )
              
target_compile_options(sm_common_enc_asn_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(sm_common_enc_asn_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)