#############################
# E2E Test E2-AGENT NEAR-RIC 
#############################

add_executable(test_near_ric 
  test_near_ric.c 
                  ../../../test/rnd/fill_rnd_data_gtp.c                  
                  ../../../test/rnd/fill_rnd_data_tc.c                  
                  ../../../test/rnd/fill_rnd_data_mac.c                  
                  ../../../test/rnd/fill_rnd_data_rlc.c                  
                  ../../../test/rnd/fill_rnd_data_pdcp.c                  
                  ../../../test/rnd/fill_rnd_data_kpm.c                  
                  ../../../test/rnd/fill_rnd_data_rc.c                  
                  ../../../test/rnd/fill_rnd_data_slice.c                  
 


                  #  ../../src/sm/rc_sm/test/fill_rnd_data_rc.c
                  #  ../sm/common/fill_ind_data.c
                  # ../../../test/encode_decode/sm/kpm/fill_rnd_data_kpm.c
                  )

target_link_libraries(test_near_ric
                      PUBLIC 
                      e2_agent
                      ${FlatCC} 
                      #/home/mir/workspace/flatcc/lib/libflatccrt_d.a
                      near_ric_test
                      -pthread
                      -lsctp
                      -ldl)


