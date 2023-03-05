add_subdirectory(enc_asn)
add_subdirectory(enc_asn_kpm_common)

add_library(kpm_e2sm_specific_ie_enc_asn_shared SHARED
                                            $<TARGET_OBJECTS:kpm_enc_common_asn_obj>
                                            $<TARGET_OBJECTS:kpm_enc_ie_asn_obj>)


target_compile_options(kpm_e2sm_specific_ie_enc_asn_shared PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(kpm_e2sm_specific_ie_enc_asn_shared PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
