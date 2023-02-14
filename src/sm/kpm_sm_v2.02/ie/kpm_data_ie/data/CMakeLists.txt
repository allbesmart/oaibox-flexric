file(GLOB KPM_RIC_INFO_COMMON_SRCS *.c)

add_library(kpm_ric_info_common_obj OBJECT ${KPM_RIC_INFO_COMMON_SRCS})


target_include_directories(kpm_ric_info_common_obj PUBLIC
                                         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                         )
              
target_compile_options(kpm_ric_info_common_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(kpm_ric_info_common_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
