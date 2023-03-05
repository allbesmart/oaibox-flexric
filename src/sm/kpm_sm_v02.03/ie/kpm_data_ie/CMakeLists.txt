add_subdirectory(data)
add_subdirectory(kpm_ric_info)

add_library(kpm_data_ie_shared SHARED
                            $<TARGET_OBJECTS:kpm_ric_info_common_obj>
                            $<TARGET_OBJECTS:kpm_ric_info_obj>)


target_compile_options(kpm_data_ie_shared PUBLIC "-DASN_DISABLE_OER_SUPPORT" -fPIC)
target_compile_options(kpm_data_ie_shared PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
                            