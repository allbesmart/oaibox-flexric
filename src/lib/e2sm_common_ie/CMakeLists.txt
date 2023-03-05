add_subdirectory(3gpp_derived_ie)
add_subdirectory(3gpp_derived_ie_dec_asn)
add_subdirectory(3gpp_derived_ie_enc_asn)
add_subdirectory(sm_common_ie)
add_subdirectory(dec_asn_sm_common)
add_subdirectory(enc_asn_sm_common)


add_library(e2sm_common_ie_shared SHARED
                                $<TARGET_OBJECTS:3gpp_derived_ie_obj>
                                $<TARGET_OBJECTS:3gpp_derived_ie_dec_asn_obj>
                                $<TARGET_OBJECTS:3gpp_derived_ie_enc_asn_obj>
                                $<TARGET_OBJECTS:sm_common_ie_obj>
                                $<TARGET_OBJECTS:sm_common_dec_asn_obj>
                                $<TARGET_OBJECTS:sm_common_enc_asn_obj>
                                )

target_compile_options(e2sm_common_ie_shared PUBLIC "-DASN_DISABLE_OER_SUPPORT" -fPIC)
target_compile_options(e2sm_common_ie_shared PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
