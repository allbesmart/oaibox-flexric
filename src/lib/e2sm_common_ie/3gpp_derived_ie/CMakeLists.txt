set(3GPP_DERIVED_IE_SRCS
    plmn_identity.c)

add_library(3gpp_derived_ie_obj OBJECT ${3GPP_DERIVED_IE_SRCS})


target_include_directories(3gpp_derived_ie_obj PUBLIC
                                         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                         )
              
target_compile_options(3gpp_derived_ie_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(3gpp_derived_ie_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
