set(SM_ENCODING_KPM "ASN" CACHE STRING "The KPM SM encoding to use")
set_property(CACHE SM_ENCODING_KPM PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected KPM SM_ENCODING: ${SM_ENCODING_KPM}")


if(SM_ENCODING_KPM  STREQUAL "PLAIN")
  message(FATAL_ERROR "Not implemented PLAIN encoding")

elseif(SM_ENCODING_KPM STREQUAL "ASN")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../src/sm/kpm_sm_v03/ie/asn/ )
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../src/lib/ap/ie/asn/ )
  
  file(GLOB asn_sources "../../../src/sm/kpm_sm_v03.00/ie/asn/*.c")
  file(GLOB ir_sources "../../../src/sm/kpm_sm_v03.00/ie/ir/*.c")
  file(GLOB 3gpp_derived_ie "../../../src/lib/sm/3gpp_derived_ie/*.c")
  file(GLOB 3gpp_derived_ie_dec_asn "../../../src/lib/sm/3gpp_derived_ie_dec_asn/*.c")
  file(GLOB 3gpp_derived_ie_enc_asn "../../../src/lib/sm/3gpp_derived_ie_enc_asn/*.c")
  file(GLOB sm_common_ie "../../../src/lib/sm/sm_common_ie/*.c")


  file(GLOB kpm_data "../../../src/sm/kpm_sm_v03.00/ie/kpm_data_ie/data/*.c")
  file(GLOB kpm_info "../../../src/sm/kpm_sm_v03.00/ie/kpm_data_ie/kpm_ric_info/*.c")
  file(GLOB enc_asn "../../../src/sm/kpm_sm_v03.00/enc/enc_asn/*.c")
  file(GLOB enc_asn_common "../../../src/sm/kpm_sm_v03.00/enc/enc_asn_kpm_common/*c")
  file(GLOB dec_asn "../../../src/sm/kpm_sm_v03.00/dec/dec_asn/*c")
  file(GLOB dec_asn_common "../../../src/sm/kpm_sm_v03.00/dec/dec_asn_kpm_common/*c")

  file(GLOB enc_sm_common_ie "../../../src/lib/sm/enc_asn_sm_common/*.c")
  file(GLOB dec_sm_common_ie "../../../src/lib/sm/dec_asn_sm_common/*.c")

  include_directories("/usr/local/share/asn1c/")
  add_executable(test_kpm_sm
                      main.c 
                      ../common/fill_ind_data.c
                      ../../../src/sm/sm_proc_data.c 
                      ../../../src/sm/kpm_sm_v03.00/kpm_sm_agent.c
                      ../../../src/sm/kpm_sm_v03.00/kpm_sm_ric.c
                      ../../../src/sm/kpm_sm_v03.00/ie/kpm_data_ie.c
                      ../../../src/sm/kpm_sm_v03.00/ie/kpm_data_ie.c
                      ../../../src/sm/rc_sm/test/fill_rnd_data_rc.c
                      ../../../src/sm/kpm_sm_v03.00/enc/kpm_enc_asn.c
                      ../../../src/sm/kpm_sm_v03.00/dec/kpm_dec_asn.c
                      ../../../src/util/alg_ds/alg/defer.c
                      ../../../src/util/byte_array.c
                      ../../../src/util/conversions.c

                      ${dec_asn}
                      ${dec_asn_common}
                      ${enc_asn}
                      ${enc_asn_common}
                      ${kpm_data}
                      ${kpm_info}
                      ${ir_sources}
                      ${ir_sources}
                      ${3gpp_derived_ie}          
                      ${3gpp_derived_ie_dec_asn}          
                      ${3gpp_derived_ie_enc_asn}          
                      ${sm_common_ie}
                      ${asn_sources}
                      ${enc_sm_common_ie}
                      ${dec_sm_common_ie}
                      )

  target_compile_options(test_kpm_sm PUBLIC "-DASN_DISABLE_OER_SUPPORT" )
  target_compile_definitions(test_kpm_sm  PRIVATE ${SM_ENCODING_KPM})

elseif(SM_ENCODING_KPM STREQUAL "FLATBUFFERS")
  message(FATAL_ERROR "Not implemented FLATBUFFERS encoding")

endif()

target_compile_definitions(test_kpm_sm PUBLIC ${SM_ENCODING_KPM})
target_link_libraries(test_kpm_sm PUBLIC -pthread -lm)


enable_testing()
add_test(Unit_test_KPM test_kpm_sm)
