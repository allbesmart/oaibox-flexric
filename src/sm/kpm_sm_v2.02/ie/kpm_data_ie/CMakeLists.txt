add_subdirectory(data)
add_subdirectory(kpm_ric_info)

add_library(kpm_data_ie_obj OBJECT
                            $<TARGET_OBJECTS:kpm_ric_info_common_obj>
                            $<TARGET_OBJECTS:kpm_ric_info_obj>)

target_link_libraries(kpm_data_ie_obj PUBLIC
                                    kpm_ric_info_common_obj
                                    kpm_ric_info_obj)
                                    