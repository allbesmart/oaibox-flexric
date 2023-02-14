add_subdirectory(kpm_data_ie)

add_library(kpm_ie_obj OBJECT
    kpm_data_ie.c
    $<TARGET_OBJECTS:kpm_data_ie_obj>
  )

target_link_libraries(kpm_ie_obj PUBLIC
                                e2sm_kpm_asn1_obj)
 
