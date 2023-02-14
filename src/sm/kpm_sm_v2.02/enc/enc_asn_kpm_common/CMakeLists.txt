file(GLOB KPM_ENC_COMMON_ASN_SRCS *.c)
# file(GLOB asn_sources "../../ie/asn/*.c")

add_library(kpm_enc_common_asn_obj OBJECT
                                ${KPM_ENC_COMMON_ASN_SRCS}
                                $<TARGET_OBJECTS:e2sm_kpm_asn1_obj>)

target_link_libraries(kpm_enc_common_asn_obj PRIVATE
                                            e2sm_kpm_asn1_obj)

target_include_directories(kpm_enc_common_asn_obj PUBLIC
                                         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                         )
              
target_compile_options(kpm_enc_common_asn_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(kpm_enc_common_asn_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
