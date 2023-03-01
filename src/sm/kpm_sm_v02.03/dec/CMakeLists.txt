add_subdirectory(dec_asn)
add_subdirectory(dec_asn_kpm_common)

add_library(kpm_e2sm_specific_ie_dec_asn_obj OBJECT
                                            $<TARGET_OBJECTS:kpm_dec_common_asn_obj>
                                            $<TARGET_OBJECTS:kpm_dec_ie_asn_obj>)

target_link_libraries(kpm_e2sm_specific_ie_dec_asn_obj PUBLIC
                                                    kpm_dec_common_asn_obj
                                                    kpm_dec_ie_asn_obj)
                  
target_compile_options(kpm_e2sm_specific_ie_dec_asn_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(kpm_e2sm_specific_ie_dec_asn_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
