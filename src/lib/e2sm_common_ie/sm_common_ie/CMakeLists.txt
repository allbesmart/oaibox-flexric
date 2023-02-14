set(SM_COMMON_IE_SRCS
    ue_id.c)

add_library(sm_common_ie_obj OBJECT ${SM_COMMON_IE_SRCS})


target_include_directories(sm_common_ie_obj PUBLIC
                                         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                         )
              
target_compile_options(sm_common_ie_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(sm_common_ie_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
