add_executable(oaibox_xapp_ue_measurements
        oaibox_xapp_ue_measurements.c
        ../../../../src/util/alg_ds/alg/defer.c
        ../../../../src/util/hashtable/hashtable.c
)

target_link_libraries(oaibox_xapp_ue_measurements
        PUBLIC
        e42_xapp
        -pthread
        -lsctp
        -ldl
)
