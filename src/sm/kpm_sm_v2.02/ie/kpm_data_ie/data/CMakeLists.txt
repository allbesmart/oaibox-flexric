file(GLOB KPM_RIC_INFO_COMMON_SRCS *.c)

set(KPM_RIC_INFO_COMMON_SRCS 
  label_info_lst.c
  )

add_library(kpm_ric_info_common_obj OBJECT ${KPM_RIC_INFO_COMMON_SRCS})

              
target_compile_options(kpm_ric_info_common_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(kpm_ric_info_common_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC)
