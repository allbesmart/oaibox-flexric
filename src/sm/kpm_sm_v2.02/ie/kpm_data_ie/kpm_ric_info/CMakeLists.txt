file(GLOB KPM_RIC_INFO_SRCS *.c)

add_library(kpm_ric_info_obj OBJECT
                            ${KPM_RIC_INFO_SRCS}
                            $<TARGET_OBJECTS:e2sm_common_ie_obj>)

target_link_libraries(kpm_ric_info_obj PUBLIC
                                    e2sm_common_ie_obj)

target_include_directories(kpm_ric_info_obj PUBLIC
                                         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                         )
              
target_compile_options(kpm_ric_info_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(kpm_ric_info_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
