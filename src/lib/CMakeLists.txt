
add_subdirectory(ap)
add_subdirectory(ep)
add_subdirectory(msg_hand)
add_subdirectory(e2sm_common_ie)

add_library(pending_events_obj OBJECT 
                                pending_events.c 
                                pending_event_ric.c
                                ind_event.c
                                $<TARGET_OBJECTS:e2ap_types_obj> 
                                $<TARGET_OBJECTS:e2ap_ap_obj>
                                
                                # ../sm/kpm_sm_v02.03/ie/kpm_data_ie.c
                                # $<TARGET_OBJECTS:e2sm_kpm_asn1_obj>
                                # $<TARGET_OBJECTS:kpm_ric_info_common_obj>
                                # $<TARGET_OBJECTS:kpm_ric_info_obj>

                                # $<TARGET_OBJECTS:kpm_dec_common_asn_obj>
                                # $<TARGET_OBJECTS:kpm_dec_ie_asn_obj>

                                # $<TARGET_OBJECTS:kpm_enc_common_asn_obj>
                                # $<TARGET_OBJECTS:kpm_enc_ie_asn_obj>
                                )

# add_dependencies(pending_events_obj e2_agent)
